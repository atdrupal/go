<?php
namespace Drupal\go\Misc\SEO;

/**
 * Insert google analytics code into every page footer
 *
 * @see go_init()
 */
class GoogleAnalytics {
  public function execute() {
    if (preg_match('`^node/*$`si', $_GET['q'])) {
      if ('node' !== variable_get('site_frontpage', 'node')) {
        drupal_goto('<front>');
      }
    }
  }
}

/**
 * Build google analytics code
 *
 * @return string Google Analytics embed code
 */
function go_get_google_analytics_code($id) {
  // get domain name
  $domain = $GLOBALS['base_url'];
  $domain = preg_replace('/^(http|https)+:\/\/+/si', '', $domain);

  return "(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');
  ga('create', '$id', '$domain');
  ga('send', 'pageview');";
}

function go_google_analytics_code_insert() {
  if (defined('GO_GOOGLE_ANALYTICS')) {
    drupal_add_js(go_get_google_analytics_code(GO_GOOGLE_ANALYTICS), array(
      'type' => 'inline', 'scope' => 'footer',
    ));
  }
}
