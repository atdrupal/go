<?php
namespace Drupal\go\Hook;

class Init {
  public function execute() {
    if (go_enabled('go_google_analytics')) {
      return at_id(new \Drupal\go\Misc\SEO\GoogleAnalytics())->execute();
    }

    if (go_enabled('go_skip_node_to_front')) {
      return at_id(new \Drupal\go\Misc\SEO\RedirectNodeToFront())->execute();
    }
  }
}
