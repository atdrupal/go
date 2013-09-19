<?php
/**
 * @file go.config.sample.php
 *
 * Sample configuration for features of go.module
 */

// #####################
// Select default format for formatted text fields.
//
// 0, 1, 2 is ID of user role.
// #####################

// Defaut for all fields
$conf['go_text_formats']['roles'] = array(
  0 => 'plain_text',
  1 => 'filtered_html',
  2 => 'full_html',
);

// Get prefered text-format for user on specific field.
$conf['go_text_formats']['node']['article']['body'] = array(
  0 => 'plain_text',
  1 => 'filtered_html',
  2 => 'full_html',
);
