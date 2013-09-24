<?php

/**
 * @file ./drush/go.dev.inc
 *
 * @author Chau Pham, Andy Truong
 */

/**
 * Command to enable dev environment.
 */
function drush_go_dev() {
  // This command is runnable if GODEV constant is defined in settings.php
  if (!defined('GODEV') && !GODEV) {
    return drush_set_error('godev command\'s not available in current site.');
  }

  $modules['devel'] = 1;
  $modules['environment_indicator'] = 1;
  $modules['update'] = 0;

  $config['page_cache'] = 0;
  $config['block_cache'] = 0;
  $config['compress_css'] = 0;
  $config['compress_js'] = 0;
  $config['views_ui_always_live_preview'] = 0;
  $config['views_ui_show_sql_query'] = 1;
  $config['views_show_additional_queries'] = 1;
  $config['views_ui_show_advanced_help_warning'] = 0;

  foreach ($modules as $module => $default_value) {
    $value = drush_get_option($module, $default_value);
    _drush_invoke_hooks($value ? 'pm-enable' : 'pm-disable', array($module));
  }

  foreach ($config as $config_entry => $default_value) {
    $value = drush_get_option($config_entry, $default_value);
    variable_set($config_entry, $value);
  }
}
