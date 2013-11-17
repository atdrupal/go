<?php
namespace Drupal\go\Hook\FormAlter;

class SystemCronSettings {
  public function __construct() {
    if (!empty($_GET['module'])) {
      $this->runCronTask($module);
    }
  }

  private function runCronTask($module) {
    if (module_exists($module)) {
      timer_start('go_cron_links');
      $function = "{$_GET['module']}_cron";
      $function();
      $time = timer_read('go_cron_links');
      drupal_set_message("Ran <strong>{$function}()</strong> in {$time} ms");
      drupal_goto('admin/config/system/cron');
    }
  }

  public function alter(&$form, $form_state) {
    foreach (module_implements('cron') as $module) {
      $items[] = l($module, 'admin/config/system/cron', array('query' => array('module' => $module)));
    }

    $form['go_cron_jobs'] = array(
      '#type' => 'markup',
      'links' => array(
        '#theme' => 'item_list',
        '#title' => t('You can run a specific cron job by clicking the following links'),
        '#items' => $items,
      )
    );
  }
}
