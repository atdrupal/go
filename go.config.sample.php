<?php
/**
 * @file go.config.sample.php
 *
 * Sample configuration for features of go.module
 */

// #####################
// Disable autoload feature
// #####################
define('GO_DISABLE_AUTOLOAD', TRUE);

// #####################
// Simple Google Analytics
// #####################
define('GO_GOOGLE_ANALYTICS', 'UA-12345');

// #####################
// Simple 403/404
//
//  403 => Redirect to Login page
//  404 => Redirect to Search page
// #####################
define('GO_403', 1);
define('GO_404', 'search/content');

// #####################
// Keep /node page, do not redirect to front page
// #####################
define('GO_SKIP_NODE_TO_FRONT', 1);

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
