<?php

/**
 * @file
 *   Go Drush commands
 */

require_once dirname(__FILE__) . '/../includes/go.autoload.inc';
require_once dirname(__FILE__) . '/go.cron.inc';
require_once dirname(__FILE__) . '/go.hipchat.inc';
require_once dirname(__FILE__) . '/go.dev.inc';
require_once dirname(__FILE__) . '/go.live.inc';
require_once dirname(__FILE__) . '/go.mail.inc';

if (version_compare(DRUSH_MAJOR_VERSION, 5) >= 0) {
  require_once dirname(__FILE__) . '/go.download.inc';
  require_once dirname(__FILE__) . '/go.require.inc';
}

/**
 * Implements hook_drush_command()
 *
 * @return array
 */
function go_drush_command() {
  $items  = array();
  $items += go_drush_live_command_info();
  $items += go_drush_dev_command_info();
  $items += go_drush_mail_command_info();
  $items += go_drush_hipchat_command_info();

  if (version_compare(DRUSH_MAJOR_VERSION, 5) >= 0) {
    $items += go_drush_download_command_info();
    $items += go_drush_require_command_info();
  }

  return $items;
}

/**
 * Request confirmation from the user
 *
 * @param string $msg message will print
 */
function go_drush_confirm($msg) {
  $y_option = drush_get_option('y');
  if ($y_option != 1) {
    return drush_confirm($msg);
  }

  return TRUE;
}
