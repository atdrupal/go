<?php
namespace Drupal\go\Hook;

class Init {
  public function execute() {
    if (at_valid('go_google_analytics')) {
      return at_id(new \Drupal\go\Misc\SEO\GoogleAnalytics())->execute();
    }

    if (at_valid('go_skip_node_to_front')) {
      return at_id(new \Drupal\go\Misc\SEO\RedirectNodeToFront())->execute();
    }
  }
}
