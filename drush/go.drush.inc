<?php

/**
 * @file
 *   Go Drush commands
 */

require_once dirname(__FILE__) . '/go.download.inc';
/**
 * Implements hook_drush_command()
 * @return array
 */
function go_drush_command() {
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
