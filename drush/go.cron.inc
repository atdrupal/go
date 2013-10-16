<?php

function go_drush_cron_command_info() {
  $items['go-cron'] = array(
    'description' => 'Run specific cron job',
    'arguments' => array(
      'module' => 'Machine name of the module.',
    ),
    'aliases' => array('goc'),
    'examples' => array(
      'drush goc system' => 'Fire system_cron() function.',
    ),
  );
  return $items;
}

/**
 * Callback function to send a message to Hipchat room.
 *
 * @param  string $module
 */
function drush_go_cron($module) {
  if (module_exists($module)) {
    timer_start('go_cron_links');
    $function = "{$module}_cron";
    $function();
    $time = timer_read('go_cron_links');
    drupal_set_message("Ran <strong>{$function}()</strong> in {$time} ms");
  }
}
