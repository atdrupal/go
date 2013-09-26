<?php
namespace Drupal\godoc\Controller;

/**
 * Controller for /admin/go-doc/content-types/*
 */
class Module {
  public function pageCallback($part) {
    $files = system_rebuild_module_data();
    return '<pre><code>'. print_r($files, TRUE) .'</code></pre>';


    return array(
      '#theme' => 'table',
      '#header' => array('Packpage', 'Module'),
      '#rows' => array(),
    );
  }
}
