<?php

function drush_go_require() {
  // // Using native drush make function, require drush 5
  // if (version_compare(DRUSH_MAJOR_VERSION, 5) < 0) {
  //   return drush_set_error('DRUSH_REQUIREMENTS_ERROR', dt('Your drush version is too old. go-require requires at least drush !version.', array('!version' => 5)));
  // }
  // Parse info file
  // Get option file
  $make_file = drush_get_option('file', '.gorequire');
  $gitignore = '.gitignore'; // @TODO, add to option
  // drush reset getcwd, it'll return DRUPAL_ROOT here => file will invaild
  // Set current_dir and build_path to current directory
  $current_dir = $build_path = drush_get_context(DRUSH_OLDCWD);
  // Get DrupalRoot context
  $drupal_root = drush_get_context(DRUSH_DRUPAL_ROOT);
  $parser = new Go1RequireParseInfo($make_file, $gitignore);
  // Get projects need to build;
  $info = $parser->getInfoContent();
  // Prevent download core
  drush_set_option('no-core', 1);
  // Begin build
  $make_project_callback = 'make_projects';
  $make_libraries_callback = 'make_libraries';
  if (version_compare(DRUSH_MAJOR_VERSION, 5) < 0) {
    $make_project_callback = 'drush_make_projects';
    $make_libraries_callback = 'drush_make_libraries';
  }
  if ($make_project_callback(FALSE, './', $info, $build_path)) {
    $make_libraries_callback('./', $info, $build_path);
  }
  return $info;
}

/**
 * Implements drush_hook_post_COMMAND() for the go_require command.
 *   Move build project + libraries to correct directory
 */
function drush_go_post_go_require() {
  $build_path = drush_get_context(DRUSH_OLDCWD);
  $make_move_build_callback = 'make_move_build';
  if (version_compare(DRUSH_MAJOR_VERSION, 5) < 0) {
    $make_move_build_callback = 'drush_make_move_build';
  }
  $make_move_build_callback($build_path);
}

// Class to parse info file
class Go1RequireParseInfo {
  // Storage make file content
  protected $make_file;
  // Store ignore file
  protected $ignore_file;

  private $_info;
  private $_projects;
  private $_libraries;
  private $_drupal_root;
  private $_site_root;
  private $_current_dir;
  private $_parsed;

  // Contruct, save value
  public function __construct($make_file, $ignore_file) {
    $this->make_file = $make_file;
    $this->ignore_file = $ignore_file;
    $this->_parsed = FALSE;
  }

  // Function to get modules list
  public function getProjects() {
    $this->parseInfo();
    return $this->_projects;
  }

  // Function to get libraries list
  public function getLibraries() {
    $this->parseInfo();
    return $this->_libraries;
  }

  public function getInfoContent() {
    $this->parseInfo();
    return $this->_info;
  }

  // Parse info file, using native drush make
  private function parseInfo() {
    // Only continue when we haven't parse file
    if (!$this->_parsed) {
      // Set some context
      $this->_drupal_root = drush_get_context(DRUSH_DRUPAL_ROOT);
      $this->_site_root = drush_get_context(DRUSH_DRUPAL_SITE);
      $this->_current_dir = drush_get_context(DRUSH_OLDCWD);
      // Get drush version to use correct parse function
      if (version_compare(DRUSH_MAJOR_VERSION, 5) < 0) {
        // We are in drush 4, using drush_make_parse_info_file
        $make_parse_info_file = 'drush_make_parse_info_file';
        $make_validate_info_file = 'drush_make_validate_info_file';
        $make_version = DRUSH_MAKE_API;
      }
      else {
        // Drush >=5, using native function make_parse_info_file
        $make_parse_info_file = 'make_parse_info_file';
        $make_validate_info_file = 'make_validate_info_file';
        $make_version = MAKE_API;
      }
      $info = $make_parse_info_file($this->_current_dir . '/' . $this->make_file);
      // Before continue, we using make_validate_info_file, and the native make file require core and api attribute
      $info['core'] = '7.x';
      $info['api'] = $make_version;
      if ($info === FALSE || ($info = $make_validate_info_file($info)) === FALSE) {
        return FALSE;
      }
      $this->_info = $info;
      // Clean some module or libraries we have
      $this->cleanInfoFile();
      // Hard code to prevent download core
      $this->_parsed = TRUE;
    }
  }
  // Clean project (module + theme) and libraries we have
  public function cleanInfoFile() {
    // Get all modules we have
    // Get all know projects
    if (version_compare(DRUSH_MAJOR_VERSION, 5) < 0) {
      $extension_info = drush_pm_get_extensions();
    }
    else {
      $extension_info = drush_get_extensions();
    }
    uasort($extension_info, '_drush_pm_sort_extensions');
    // Check and unset project we have
    foreach ($extension_info as $key => $extension) {
      _go_require_clean($this->_info, $key, 'projects');
    }
    // Clear memory
    unset($extension_info);
    // Get all know libraries
    $libraries = array();
    foreach (array($this->_drupal_root . '/sites/all/libraries', $this->_drupal_root . '/sites/' . $this->_site_root . '/libraries', $this->_current_dir . '/libraries') as $scan_dir) {
      if (is_dir($scan_dir)) {
        $libraries = array_merge(array_diff(scandir($scan_dir), array('..', '.')), $libraries);
      }
    }
    // Check and unset library we have
    foreach ($libraries as $library) {
      _go_require_clean($this->_info, $library, 'libraries');
    }
    // Read content from .gitignore file
    if (is_file($this->_current_dir . '/' . $this->ignore_file)) {
      $contents = explode("\n", trim(file_get_contents($this->_current_dir . '/' . $this->ignore_file)));
      foreach ($contents as $name) {
        _go_require_clean($this->_info, $name, 'projects');
        _go_require_clean($this->_info, $name, 'libraries');
      }
    }
  }
}

// Clean library or project from build file
function _go_require_clean(&$info, $key, $type) {
  if (isset($info[$type][$key])) {
    unset($info[$type][$key]);
  }
}
