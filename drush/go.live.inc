<?php

/*
 * command golive
 */

function drush_go_live() {

  $js_option = intval(drush_get_option('js', 1));
  $update_option = intval(drush_get_option('update', 1));
  $cache_option = intval(drush_get_option('cache', 1));

  // print warning if godev be defined in setting.php
  if (defined('GODEV')) {
    drush_log(dt("dev feature is not recommended when using this command. you need to remove GODEV constant in setting.php. \n"), "warning");
  }

  // validate text input from user
  if ($js_option != 0 && $js_option != 1 || $update_option != 0 && $update_option != 1 || $cache_option != 0 && $cache_option != 1) {
    drush_set_error(dt('Data input invalid!'));
  }

  // enable page caching and block caching if cache option equal 1
  if ($cache_option == 1) {
    // enable  block/page caching
    go_golive_action('enable', 'cache');
  }
  elseif ($cache_option == 0) {
    // disable caching
    go_golive_action('disable', 'cache');
  }

  // enable aggregate css/js files
  if ($js_option == 1) {
    go_golive_action('enable', 'js_css');
  }
  elseif ($js_option == 0) {
    go_golive_action('disable', 'js_css');
  }

  // disable UI modules
  go_disable_ui_module();

  // enable module update if value input for --update option 1
  if ($update_option == 1) {
    // enable
    go_update_module('enable');
  }
  elseif ($update_option == 0) {
    // disable module update
    go_update_module('disable');
  }

  //disable module environment_indicator
  go_disable_environment_indicator_module();
}

/**
 * @param string $action value is enable if you want to enable or vice versa
 * @package string $type value cache or js_css
 * @return
 */
function go_golive_action($action, $type) {
  // if action enable config vaule equal 0 and vice versa 1
  $value_config = $action == 'enable' ? 1 : 0;

  if ($type == 'cache') {
    if (go_live_confirm('You want to enable block/page caching?')) {

      // enable page caching
      variable_set('cache', $value_config);
      // enable block caching
      variable_set('block_cache', $value_config);
      // config cache life time
      $life_time = $action == 'enable' ? 1800 : 0;
      variable_set('cache_lifetime', $life_time);
      variable_set('page_cache_maximum_age', $life_time);

      if ($action == 'disable') {
        // print message
        drush_log(dt('Block/page caching disabled.'), "success");
      }
      elseif ($action == 'enable') {
        // print message
        drush_log(dt('Block/page caching enabled.'), "success");
      }
    }
  }
  elseif ($type == 'js_css') {
    if (go_live_confirm('You want to enable js/css aggregation?')) {
      // enable aggregation css
      variable_set('preprocess_css', $value_config);
      // enable aggragation js
      variable_set('preprocess_js', $value_config);

      if ($action == 'enable') {
        // print message
        drush_log(dt('Js/css aggregation enabled.'), "success");
      }
      elseif ($action == 'disable') {
        drush_log(dt('Js/css aggregation disabled.'), "success");
      }
    }
  }
}

/**
 * the UI module will disable
 * add UI module will disable here
 */
function go_ui_modules() {
  return array(
    'field_ui', 'context_ui', 'migrate_ui', 'feeds_ui', 'og_ui',
    'boxes_admin_ui', 'rules_admin', 'views_ui', 'context_ui',
  );
}

/**
 * disable ui module have on go_ui_modules
 * @return string list the module ui be disable
 */
function go_disable_ui_module() {
  if (go_live_confirm('You want to disable all UI module?')) {
    // get list ui module to disable
    $ui_modules = go_ui_modules();
    $ui_modules_after_checked = array();

    foreach ($ui_modules as $ui_module) {
      // module exists will disable
      if (module_exists($ui_module)) {
        $ui_modules_after_checked[] = $ui_module;
      }
    }

    if (count($ui_modules_after_checked) > 0) {
      module_disable($ui_modules_after_checked);
      $disable_ui_modules = implode(', ', $ui_modules_after_checked);
      drush_log(dt('UI modules be disable @modules_ui', array('@modules_ui' => $disable_ui_modules)), "success");
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * enable module Update module
 * @param string $action enable or disable
 */
function go_update_module($action) {
  if ($action == 'enable') {
    if (!module_exists('update')) {
      // enable update module
      if (go_live_confirm('You want to enable update module?')) {
        module_enable(array('update'));
        drush_log(dt('Module update has been enable success.'), "success");
      }
    }
  }
  elseif ($action == 'disable') {
    // disable module update
    if (module_exists('update')) {
      if (go_live_confirm('You want to enable update module?')) {
        module_disable(array('update'));
        drush_log(dt('Module update has been disable.'), 'success');
      }
    }
  }
}

/**
 * Disable module environment_indicator if it's enable
 */
function go_disable_environment_indicator_module() {
  if (module_exists('environment_indicator')) {
    // disable module environment_indicator
    if (go_live_confirm('You want to disable environment_indicator module?')) {
      module_disable(array('environment_indicator'));
    }
  }
}

/**
 * Request confirmation from the user
 * @param string $msg message will print
 */
function go_live_confirm($msg) {
  $y_option = drush_get_option('y');
  if ($y_option != 1) {
    return drush_confirm($msg);
  }

  return TRUE;
}