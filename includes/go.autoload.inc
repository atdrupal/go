<?php

/**
 * You can tell go.module to find your directory by define go_autoload() in your
 * settings.php
 */
if (!function_exists('go_autoload')) {
  /**
   * Wrapper for _go_autoload()
   *
   * @param  string $class
   * @return boolean
   */
  function go_autoload($class) {
    return _go_autoload($class, array('all'));
  }
}

/**
 * Simple PSR-0 autoloader.
 *
 * - \Drupal\%module\Class: If the %module is enabled, go will load the file
 *     /path/to/%module/lib/Drupal/%module/Class.php
 * - \Drupal\Components\Foo: go will load the file
 *     /sites/%site/Drupal/Components/Foo.php
 * - Other cases, please use composer autoloader.
 *
 * @param  string $class
 * @param  array  $sites
 * @return boolean
 */
function _go_autoload($class, $sites) {
  // #####################
  // Validating
  // #####################

  // PSR-0 loader, do not support normal class
  $no_supported = strpos($class, '\\') !== FALSE;

  // Only Drupal namespace
  $no_supported = $no_supported || (strpos($class, 'Drupal\\') === FALSE);
  if ($no_supported) {
    return FALSE;
  }

  // #####################
  // Global \Drupal
  // #####################

  // Convert \ to DIRECTORY_SEPARATOR
  $path = str_replace('\\', DIRECTORY_SEPARATOR, $class);
  $path = DRUPAL_ROOT . "/sites/%s/libraries/{$path}.php";
  foreach ($sites as $site) {
    $file = sprintf($path, $site);
    if (is_file($file)) {
      include_once $file;
      return TRUE;
    }
  }

  // #####################
  // \Drupal\%module
  // #####################
  $path = str_replace('\\', DIRECTORY_SEPARATOR, $class);
  $path = DRUPAL_ROOT . "/%s/lib/{$path}.php";
  foreach (go_get_module_apis() as $module => $info) {
    if (strpos($suffix, "Drupal/{$module}/") !== FALSE) {
      $file = sprintf($path, drupal_get_path('module', $module));
      if (file_exists($file)) {
        include_once $file;
        return TRUE;
      }
    }
  }

  return FALSE;
}
