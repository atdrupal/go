<?php

/**
 * @file
 *   Go Drush commands
 */

require_once dirname(__FILE__) . '/go.download.inc';
require_once dirname(__FILE__) . '/go.hipchat.inc';

/**
 * Implements hook_drush_command()
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

  return $items;
}
