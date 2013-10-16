<?php

/**
 * @file ./drush/go.dev.inc
 *
 * @author Chau Pham, Andy Truong
 */

function go_drush_dev_command_info() {
  $items['go-dev'] = array(
    'description' => dt('Special drush commands, provided by Go1, execute some dev configurations.'),
    'options' => array(
      'devel'                 => '0 to disable devel.module. Default: 1',
      'environment_indicator' => '0 to disable environment_indicator.module. Default: 1',
      'update'                => '1 to enable update.module. Default: 0',
      'page_cache'            => 'Enable or disable page caching, default = 0',
      'block_cache'           => 'Enable or disable block caching, default = 0',
      'compress_js'           => 'Enable or disable js aggregation, default = 0',
      'compress_css'          => 'Enable or disable js aggregation, default = 0',
      'views-preview'         => 'Enable or disable "Automatically update preview on changes", default = 0',
      'views-sql'             => 'Enable or disable "Show the SQL query", default = 1',
      'views-queries'         => 'Enable or disable "Show other queries run during render during live preview", default = 1',
      'views-help'            => 'Enable or disable "Show advanced help warning", default = 0',
    ),
    'examples' => array(
      'drush godev --devel' => 'Enable devel module.',
      'drush godev --devel=0' => 'Disable devel module.',
    ),
    'aliases' => array('godev'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

/**
 * Command to enable dev environment.
 */
function drush_go_dev() {
  // This command is runnable if GODEV constant is defined in settings.php
  if (!defined('GODEV') && !GODEV) {
    return drush_set_error('godev command\'s not available in current site.');
  }

  $commands = drush_get_commands();

  // #####################
  // Core modules
  // #####################
  $modules['update'] = 0;
  foreach ($modules as $module => $default_value) {
    $value = drush_get_option($module, $default_value);
    $command = $commands[$value ? 'pm-enable' : 'pm-disable'];
    drush_dispatch($command, array($module));
  }

  // #####################
  // Contrib modules
  // #####################
  drush_go_dev__module('devel', 1);

  drush_go_dev__module('environment_indicator', 1, '7.x-1.1', array(
    'environment_indicator_text' => 'DEVELOPMENT ENVIRONMENT',
    'environment_indicator_position' => 'left',
  ));

  $command = $commands['role-add-perm'];
  _drush_invoke_hooks($command, array('anonymous user', 'access environment indicator'));

  // #####################
  // Dev options
  // #####################
  $config['page_cache'] = 0;
  $config['block_cache'] = 0;
  $config['compress_css'] = 0;
  $config['compress_js'] = 0;
  $config['views_ui_always_live_preview'] = 0;
  $config['views_ui_show_sql_query'] = 1;
  $config['views_show_additional_queries'] = 1;
  $config['views_ui_show_advanced_help_warning'] = 0;
  foreach ($config as $config_entry => $default_value) {
    $value = drush_get_option($config_entry, $default_value);
    variable_set($config_entry, $value);
  }
}

/**
 * Helper function to download and install module.
 *
 * @param  string  $module
 * @param  boolean $default_install
 * @param  string  $version
 * @param  array   $options
 */
function drush_go_dev__module($module, $default_install = TRUE, $version = NULL, $options = array()) {
  $commands = drush_get_commands();

  $action = drush_get_option($options, $default_install) ? 'pm-enable' : 'pm-disable';
  if ($action === 'pm-enable') {
    if (!module_exists($module)) {
      $cmd = $commands['pm-download'];

      $release = !empty($version) ? "{$module}-{$version}" : $module;

      $cmd['arguments'] = array($release);
      drush_dispatch($cmd, array($release));
    }

    foreach ($options as $key => $val) {
      variable_set($key, $val);
    }
  }
  else {
    foreach (array_keys($options) as $key) {
      variable_del($key);
    }
  }

  $cmd = $commands[$action];
  _drush_invoke_hooks($cmd, array($module));
}
