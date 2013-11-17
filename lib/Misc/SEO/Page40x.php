<?php
namespace \Drupal\go\Misc\SEO;

/**
 * Simple 403/404 handler
 *
 * @see    go_preprocess_page()
 * @author Thai Nguyen
 */
class Page40x {
  public function execute() {
    unset($_GET['destination']);

    $header = drupal_get_http_header();

    if (defined('GO_403') && ($header['status'] == '403 Forbidden')) {
      if (user_is_anonymous()) {
        drupal_goto('user/login', array('query' => array('destination'=>$_GET['q'])));
      }
    }

    if (defined('GO_404') && ($header['status'] == '404 Not Found')) {
      $keyword = str_replace(array('/', '-', '_', '.html'), ' ', $_GET['q']);
      $keyword = filter_xss_admin(trim($keyword));

      $path = is_numeric(GO_404) ? 'search/node/' : GO_404;
      $path = "{$path}/{$keyword}";
      drupal_goto($path);
    }
  }
}
