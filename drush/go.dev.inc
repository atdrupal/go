<?php

/**
 * Define constant to enable godev command.
 * Define in settings.php
 * Temporary define in here for dev step
 */
define('GODEV', '1');

/**
 * Command to enable dev environment.
 */
function drush_go_dev() {
  // This command is runnable if GODEV constant is defined in settings.php 
  if (defined('GODEV') && GODEV) {
    $options = array(
      'devel' => array(
        'name' => 'devel',
        'type' => 'module',
        'meaning' => 'Devel Module',
        'default_value' => 1,
      ),
      'update' => array(
        'name' => 'update',
        'type' => 'module',
        'meaning' => 'Update Module',
        'default_value' => 0,
      ),
      'page_cache' => array(
        'name' => 'cache',
        'type' => 'setting',
        'meaning' => 'Cache pages for anonymous users',
        'default_value' => 0,
      ),
      'block_cache' => array(
        'name' => 'block_cache',
        'type' => 'setting',
        'meaning' => 'Cache blocks',
        'default_value' => 0,
      ),
      'compress_css' => array(
        'name' => 'css',
        'type' => 'setting',
        'meaning' => 'Css aggregation',
        'default_value' => 0,
      ),
      'compress_js' => array(
        'name' => 'js',
        'type' => 'setting',
        'meaning' => 'Js aggregation',
        'default_value' => 0,
      ),
      'views-preview' => array(
        'name' => 'views-preview',
        'type' => 'setting',
        'meaning' => 'Automatically update preview on changes',
        'default_value' => 0,
      ),
      'views-sql' => array(
        'name' => 'views-sql',
        'type' => 'setting',
        'meaning' => 'Show the SQL query',
        'default_value' => 1,
      ),
      'views-queries' => array(
        'name' => 'views-queries',
        'type' => 'setting',
        'meaning' => 'Show other queries run during render during live preview',
        'default_value' => 1,
      ),
      'views-help' => array(
        'name' => 'views-help',
        'type' => 'setting',
        'meaning' => 'Show advanced help warning',
        'default_value' => 0,
      ),
    );

    foreach ($options as $option) {
      $option_value = drush_get_option($option['name'], $option['default_value']);
      switch ($option['type']) {
        case 'module':
          drush_go_dev_set_module($option, $option_value);
          break;

        case 'setting':
          drush_go_dev_set_setting($option, $option_value);
          break;
      }
    }
  }
  else {
    return drush_set_error('godev command\'s not available in current site.');
  }
}

/**
 * Apply setting for module
 * 
 * @param type $option
 * @param type $option_value
 */
function drush_go_dev_set_module($option, $option_value) {
  if ($option_value) {
    if (!module_exists($option['name'])) {
      module_enable(array($option['name']));
    }
    drush_log(dt("Enabled '@value'.", array('@value' => $option['meaning'])), "success");
  }
  else {
    module_disable(array($option_name));
    drush_log(dt("Disabled '@value'.", array('@value' => $option['meaning'])), "success");
  }
}

/**
 * Apply setting for variable
 * 
 * @param type $option
 * @param type $option_value
 */
function drush_go_dev_set_setting($option, $option_value) {
  if ($option_value) {
    variable_set($option['name'], 1);
    drush_log(dt("Enabled '@value'.", array('@value' => $option['meaning'])), "success");
  }
  else {
    variable_set($option['name'], 0);
    drush_log(dt("Disabled '@value'.", array('@value' => $option['meaning'])), "success");
  }
}
