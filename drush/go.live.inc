<?php

/**
 * @file ./drush/go.live.inc
 *
 * @author Quyen Bui
 */

function go_drush_live_command_info() {
  $items['go-live'] = array(
    'description' => dt('Command to enable page/block caching and js/css aggregation Simultaneous Disable UI modules enable module Update!'),
    'option' => array(
      'cache'  => '0 to disable site caching. Default: 1',
      'js'     => '0 to disable JS aggregation. Default: 1',
      'css'    => '0 to disable CSS aggregation. Default: 1',
      'dev'    => '1 to enable devel module. Default: 0',
      'update' => '0 to disable update.module. Default: 1',
    ),
    'examples' => array(
      'drush golive --cache=1 --js=1 --update=1',
      'description' => "--cache=1 if enable page/block caching or --cache=0 not enable \n\r--js=1 if enable js/css aggregation --js=0 to vice versa \n\r--update=1 if enable module update or --update=0 if not enable \n\rNotes: Do not use option will to the default value is 1",
    ),
    'aliases' => array('golive'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

/**
 * Drush callback function.
 */
function drush_go_live() {
  // Print warning if godev be defined in setting.php
  if (defined('GODEV')) {
    $msg = 'Dev feature is not recommended when using this command. you need to remove GODEV constant in setting.php.';
    drush_log("{$msg}\n", 'warning');
    return;
  }

  $js_option      = (int)(drush_get_option('js',      1));
  $css_option     = (int)(drush_get_option('css',     1));
  $devel_option   = (int)(drush_get_option('devel',   0));
  $update_option  = (int)(drush_get_option('update',  1));
  $cache_option   = (int)(drush_get_option('cache',   1));

  go_live_cache($cache_option ? 'enable' : 'disable');
  variable_set('preprocess_css', $css_option);
  variable_set('preprocess_js', $js_option);

  _drush_invoke_hooks('pm-disable', go_live_ui_modules_list());
  _drush_invoke_hooks($update_option ? 'pm-enable' : 'pm-disable', array('update'));
  _drush_invoke_hooks($devel_option ? 'pm-enable' : 'pm-disable', array('devel'));
}

/**
 * Call a function with action depending on the option input from user
 */
function go_live_context_callback($value_option, $function_name_callback) {
  $function_name_callback($value_option ? 'enable' : 'disable');
}

/**
 * Enable or disable page/block cache if $action is enable then enable and vice versa
 *
 * @param string $action type of action only receive two values enable or disable
 */
function go_live_cache($action) {
  // Enable page caching
  variable_set('cache', $action === 'enable');

  // Enable block caching
  variable_set('block_cache', $action === 'enable');

  // Config cache life time
  $life_time = $action === 'enable' ? 1800 : 0;
  variable_set('cache_lifetime', $life_time);
  variable_set('page_cache_maximum_age', $life_time);
}

/**
 * The UI module will disable
 * Add UI module to be disable here
 *
 * @return array
 */
function go_live_ui_modules_list() {
  return array(
    'field_ui', 'context_ui', 'migrate_ui', 'feeds_ui', 'og_ui',
    'boxes_admin_ui', 'rules_admin', 'views_ui', 'context_ui',
  );
}

/**
 * Disable module environment_indicator if it's enable
 */
function go_live_disable_environment_indicator_module() {
  if (module_exists('environment_indicator')) {
    _drush_invoke_hooks('pm-disable', array('environment_indicator'));
  }
}
