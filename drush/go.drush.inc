<?php

/**
 * @file
 *   Go Drush commands
 */

require_once dirname(__FILE__) . '/go.download.inc';
require_once dirname(__FILE__) . '/go.hipchat.inc';
require_once dirname(__FILE__) . '/go.dev.inc';
require_once dirname(__FILE__) . '/go.live.inc';

/**
 * Implements hook_drush_command()
 *
 * @return array
 */
function go_drush_command() {
  $items['go-hipchat'] = array(
    'description' => 'Send message to Hipchat room.',
    'arguments' => array(
      'room_id' => 'ID of the chatroom.',
      'message' => 'Message to be sent to the room.',
    ),
    'options' => array(
      'from' => 'Sender name, default: Go Module',
      'token' => 'API Token, default: value of GO_HIPCHAT_API_TOKEN constant',
      'color' => 'Background color for the message (yellow, red, green, purple or random - default: yellow)',
      'nofity' => 'Trigger notification for people in the room, default: 0',
    ),
    'aliases' => array('gohc'),
    'examples' => array(
      'drush gohc p.GoCMS "Hello room!"' => 'Send "Hello room!" to p.GoCMS chatroom.',
      'drush gohc Go1 "Log time please guys!" --from="Daniel Freshwater" --notify=1' => 'Freshy notify all people in Go1 room to log time.',
    ),
  );

  $items['go-download'] = array(
    'description' => 'Command to download libraries for you Drupal',
    'arguments' => array(
      'library' => 'Name of library to be downloaded.',
    ),
    'options' => array(
      'list' => 'List all supported libraries',
      'destination' => 'Directory you would like to download the library to.',
      'working-copy' => 'Preserves VCS directories, like .git, for projects downloaded using such methods.',
    ),
    'examples' => array(
      'drush godl --list' => 'List supported libraries.',
      'drush godl jquery.cycle' => 'Download the jquery.cycle library.',
    ),
    'aliases' => array('godl'),
    // No bootstrap is needed
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['go-dev'] = array(
    'description' => dt('Special drush commands, provided by Go1, execute some dev configurations.'),
    'options' => array(
      'devel' => dt('Enable or disable devel module, default = 1'),
      'page_cache' => dt('Enable or disable page caching, default = 0'),
      'block_cache' => dt('Enable or disable block caching, default = 0'),
      'compress_js' => dt('Enable or disable js aggregation, default = 0'),
      'compress_css' => dt('Enable or disable js aggregation, default = 0'),
      'update' => dt('Enable or disable update module, default=0'),
      'views-preview' => dt('Enable or disable "Automatically update preview on changes", default = 0'),
      'views-sql' => dt('Enable or disable "Show the SQL query", default = 1'),
      'views-queries' => dt('Enable or disable "Show other queries run during render during live preview", default = 1'),
      'views-help' => dt('Enable or disable "Show advanced help warning", default = 0'),
    ),
    'examples' => array(
      'drush godev --devel' => 'Enable devel module.',
      'drush godev --devel=0' => 'Disable devel module.',
    ),
    'aliases' => array('godev'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['go-mail'] = array(
    'description' => dt('Command to sent email.'),
    'options' => array(
      'subject' => dt('Mail subject'),
      'body' => dt('Mail body'),
      'from' => dt('Mail sender'),
      'to' => dt('Mail receiver'),
    ),
    'examples' => array(
      'drush gomail --subject="Test email" --body="Test content" --from=admin@example.com --to=tester@example.com' => 'Enable devel module.',
    ),
    'aliases' => array('gomail'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['go-live'] = array(
    'description' => dt('Command to enable page/block caching and js/css aggregation Simultaneous Disable UI modules enable module Update!'),
    'option' => array(
      'cache' => dt('value equal 1 is enable cache or equal 0 not enable cache'),
      'js' => dt('value equal 1 is enable js aggregation or 0 if vice versa'),
      'update' => dt('value 1 if enable Module Update or 0 to vice versa not enable'),
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
