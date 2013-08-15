<?php

/*
 * Command golive
 */

function drush_go_live() {
  $js_option = intval(drush_get_option('js', 1));
  $update_option = intval(drush_get_option('update', 1));
  $cache_option = intval(drush_get_option('cache', 1));

  // Print warning if godev be defined in setting.php
  if (defined('GODEV')) {
    drush_log("dev feature is not recommended when using this command. you need to remove GODEV constant in setting.php. \n", "warning");
    // Exit
    return;
  }

  // Validate text input from user
  if ($js_option != 0 && $js_option != 1 || $update_option != 0 && $update_option != 1 || $cache_option != 0 && $cache_option != 1) {
    drush_set_error('Data input invalid!');
    // Exit
    return;
  }

  // Enable page caching and block caching
  go_live_context_callback($cache_option, 'go_live_cache');

  // Enable aggregate css/js files
  go_live_context_callback($js_option, 'go_live_js_css');

  // Disable UI modules
  go_disable_ui_module();

  // Enable module update
  go_live_context_callback($update_option, 'go_live_toggle_update_module');

  // Disable module environment_indicator
  go_disable_environment_indicator_module();
}

/**
 * Call a function with action depending on the option input from user
 */
function go_live_context_callback($value_option, $function_name_callback) {
  if ($value_option == 0) {
    $function_name_callback('disable');
  }
  elseif ($value_option == 1) {
    $function_name_callback('enable');
  }
}

/**
 * Enable or disable page/block cache if $action is enable then enable and vice versa
 * 
 * @param string $action type of action only receive two values enable or disable
 * @return
 */
function go_live_cache($action) {
  if (go_live_confirm('You want to enable block/page caching?')) {

    // If action enable config vaule equal 0 and vice versa 1
    $value_config = $action == 'enable' ? 1 : 0;

    // Enable page caching
    variable_set('cache', $value_config);
    // Enable block caching
    variable_set('block_cache', $value_config);
    // Config cache life time
    $life_time = $action == 'enable' ? 1800 : 0;
    variable_set('cache_lifetime', $life_time);
    variable_set('page_cache_maximum_age', $life_time);

    if ($action == 'disable') {
      // Print message
      drush_log('Block/page caching disabled.', "success");
    }
    elseif ($action == 'enable') {
      // Print message
      drush_log('Block/page caching enabled.', "success");
    }
  }
}

/**
 * Enable or disable Js/css aggregation depend on $active vaule
 * 
 * @param String $action value is enable if you want to enable or vice versa
 * @return
 */
function go_live_js_css($action) {
  // If action enable config vaule equal 0 and vice versa 1
  $value_config = $action == 'enable' ? 1 : 0;

  if (go_live_confirm('You want to enable js/css aggregation?')) {
    // Enable aggregation css
    variable_set('preprocess_css', $value_config);
    // Enable aggragation js
    variable_set('preprocess_js', $value_config);

    if ($action == 'enable') {
      // Print message
      drush_log('Js/css aggregation enabled.', "success");
    }
    elseif ($action == 'disable') {
      drush_log('Js/css aggregation disabled.', "success");
    }
  }
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
 * Disable ui module have on go_ui_modules
 * 
 * @return boolean
 */
function go_disable_ui_module() {
  if (go_live_confirm('You want to disable all UI module?')) {
    // Get list ui module to disable
    $ui_modules = go_live_ui_modules_list();
    $ui_modules_after_checked = array();

    foreach ($ui_modules as $ui_module) {
      // Module exists will disable
      if (module_exists($ui_module)) {
        $ui_modules_after_checked[] = $ui_module;
      }
    }

    if (count($ui_modules_after_checked) > 0) {
      // Disable list the UI modules
      module_disable($ui_modules_after_checked);
      $disable_ui_modules = implode(', ', $ui_modules_after_checked);
      drush_log('UI modules be disable @modules_ui', array('@modules_ui' => $disable_ui_modules), "success");
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Enable Update module
 * 
 * @param string $action enable or disable
 */
function go_live_toggle_update_module($action) {
  if ($action == 'enable') {
    if (!module_exists('update')) {
      if (go_live_confirm('You want to enable update module?')) {
        // Enable update module
        module_enable(array('update'));
        drush_log('Module update has been enable success.', "success");
      }
    }
  }
  elseif ($action == 'disable') {
    if (module_exists('update')) {
      if (go_live_confirm('You want to enable update module?')) {
        // Disable module update
        module_disable(array('update'));
        drush_log('Module update has been disable.', 'success');
      }
    }
  }
}

/**
 * Disable module environment_indicator if it's enable
 */
function go_disable_environment_indicator_module() {
  if (module_exists('environment_indicator')) {
    if (go_live_confirm('You want to disable environment_indicator module?')) {
      // Disable module environment_indicator
      module_disable(array('environment_indicator'));
    }
  }
}