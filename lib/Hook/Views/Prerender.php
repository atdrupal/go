<?php
namespace Drupal\go\Hook\Views;

class PreRender {
  /**
   * @var \view
   */
  private $view;

  public function __construct($view) {
    $this->view = $view;
  }

  public function execute() {
    $slideshow_id = "go_slideshow__views__{$this->view->name}__{$this->view->current_display}";
    $slideshow_config = variable_get($slideshow_id);
    if (!is_null($slideshow_config)) {
      $this->prepareSlideShow($slideshow_config);
    }
  }

  private function prepareSlideShow($config = array()) {
    // Supuport lazy config
    if (is_callable($config)) {
      $config = $config($this->view->name, $this->view->current_display);
    }

    if (!is_array($config)) {
      return;
    }

    if (empty($config['#attached']['js']['jquery.cycle'])) {
      $config['#attached']['js']['jquery.cycle'] = 'sites/all/libraries/jquery.cycle/jquery.cycle.all.min.js';
    }

    if (empty($config['#attached']['js']['go.slideshow'])) {
      $config['#attached']['js']['go.slideshow'] = drupal_get_path('module', 'go') . '/misc/js/go.slideshow.js';
    }

    $config['#attached']['js'][] = array(
      'type' => 'setting',
      'data' => array('go_slideshow' => array('views' => array($this->view->name => array($this->view->current_display => $config)))),
    );

    drupal_process_attached($config);
  }
}
