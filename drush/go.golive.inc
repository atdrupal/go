<?php

/*
 * command golive
 */

function drush_go_live() {
  $js_option = intval(drush_get_option('js', 1));
  $update_option = intval(drush_get_option('update', 1));
  $cache_option = intval(drush_get_option('cache', 1));

  //validate text input from user
  if ($js_option != 0 && $js_option != 1 || $update_option != 0 && $update_option != 1 || $cache_option != 0 && $cache_option != 1) {
    drush_set_error(dt('data input invalid!'));
  }

  //enable page caching and block caching if cache option equal 1
  if ($cache_option == 1) {
    //enable  block/page caching
    go_golive_action('enable', 'cache');
    //print message
    drush_log(dt('block/page caching enabled.'), "success");
  }
  elseif ($cache_option == 0) {
    //disable caching
    go_golive_action('disable', 'cache');

    //print message
    drush_log(dt('block/page caching disabled.'), "success");
  }

  //enable aggregate css/js files
  if ($js_option == 1) {
    go_golive_action('enable', 'js_css');
    //print message
    drush_log(dt('js/css aggregation enabled.'), "success");
  }
  elseif ($js_option == 0) {
    go_golive_action('disable', 'js_css');
    drush_log(dt('js/css aggregation disabled.'), "success");
  }
}

/**
 * @param string $action value is enable if you want to enable or vice versa
 * @package string $type value cache or js_css
 * @return
 */
function go_golive_action($action, $type) {
  //if action enable config vaule equal 0 and vice versa 1
  $value_config = $action == 'enable' ? 1 : 0;

  if ($type == 'cache') {
    //enable page caching
    variable_set('cache', $value_config);
    //enable block caching
    variable_set('block_cache', $value_config);
    //config cache life time
    $life_time = $action == 'enable' ? 1800 : 0;
    variable_set('cache_lifetime', $life_time);
    variable_set('page_cache_maximum_age', $life_time);
  }
  elseif ($type == 'js_css') {
    //enable aggregation css
    variable_set('preprocess_css', $value_config);
    //enable aggragation js
    variable_set('preprocess_js', $value_config);
  }
}

