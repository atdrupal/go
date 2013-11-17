<?php
namespace Drupal\go\Misc\SEO;

/**
 * Redirect /node to front page if no GO_SKIP_NODE_TO_FRONT defined.
 *
 * @see go_init()
 */
class RedirectNodeToFront {
  public function execute() {
    if (preg_match('`^node/*$`si', $_GET['q'])) {
      if ('node' !== variable_get('site_frontpage', 'node')) {
        drupal_goto('<front>');
      }
    }
  }
}
