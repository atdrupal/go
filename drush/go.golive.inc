<?php

/*
 * command golive
 */

function drush_go_live() {
  $js_option = drush_get_option('js', 1);
  $update_option = drush_get_option('update', 1);
  $cache_option = drush_get_option('cache', 1);

  //validate text input from user
  if ($js_option != 0 && $js_option != 1 || $update_option != 0 && $update_option != 1 || $cache_option != 0 && $cache_option != 1) {
    drush_set_error(dt('data input invalid!'));
  }

  //enable page caching and block caching if cache option equal 1
  if ($cache_option == 1) {
  //enable page caching
    variable_set('cache', 1);
  //enable block caching
    variable_set('block_cache', 1);

  //print message
    drush_log(dt('block/page caching enabled.'), "success");
  }



  //enable aggregate css/js files
  if ($js_option) {
  //enable aggregation css
    variable_set('preprocess_css', 1);

  //enable aggragation js
    variable_set('preprocess_js', 1);

  //print message
    drush_log(dt('js/css aggregation enabled.'), "success");
  }
}
?>
