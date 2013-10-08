<?php
/**
 * @file includes/go.hooks.form.inc
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function go_form_system_cron_settings_alter(&$form, $form_state) {
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

  if (!empty($_GET['module'])) {
    if (module_exists($_GET['module'])) {
      call_user_func("{$_GET['module']}_cron");
    }
  }
}
