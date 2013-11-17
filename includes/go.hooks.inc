<?php
/**
 * @file includes/go.hooks.inc
 */

/**
 * Implements hook_init().
 */
function go_init() {
  at_id(new \Drupal\go\Hook\Init())->execute();
}

/**
 * Implements of hook_element_info_alter().
 */
function go_element_info_alter(&$type) {
  if (go_enabled('go_google_analytics')) {
    at_id(new \Drupal\go\Hook\ElementInfoAlter())->alter($type);
  }
}

/**
 * Implements hook_preprocess_page().
 * Simple 403/404 handlers
 */
function go_preprocess_page() {
  at_id(new \Drupal\go\Misc\SEO\Page40x())->execute();
}

/**
 * Implements hook_view_pre_render().
 */
function go_views_pre_render(&$view) {
  $view_id = "{$view->name}__{$view->current_display}";
  $slideshow_id = "go_slideshow__views__{$view_id}";
  $slideshow_config = variable_get($slideshow_id);
  if (!is_null($slideshow_config)) {
    module_load_include('inc', 'go', 'includes/go.slideshow');
    go_views_pre_render__slideshow($view->name, $view->current_display, $slideshow_config);
  }
}

/**
 * Implements hook_flush_caches()
 *
 * @see go_autoload_get_file()
 */
function go_flush_caches() {
  if (function_exists('apc_clear_cache')) {
    apc_clear_cache('user');
  }
}
