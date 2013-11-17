<?php
namespace Drupal\go\Hook;

class ElementInfoAlter {
  public function alter(&$type) {
    // Our process callback must run immediately after filter_process_format().
    $filter_process_format_location = array_search('filter_process_format', $type['text_format']['#process']);
    $replacement = array('filter_process_format', 'go_filter_process_format');
    array_splice($type['text_format']['#process'], $filter_process_format_location, 1, $replacement);
  }
}

/**
 * This callback runs after filter_process_format() and performs additional
 * modifications to the form element.
 *
 * @see  go_element_info_alter()
 */
function go_filter_process_format($element) {
  global $user;

  if (!empty($element['#entity_type']) && !empty($element['#bundle']) && !empty($element['#field_name'])) {
    $intersect = go_get_user_text_formats_for_field($user, $element['#entity_type'], $element['#bundle'], $element['#field_name']);
  }

  if (empty($intersect)) {
    $intersect = go_get_user_text_formats($user);
  }

  if (!empty($intersect)) {
    $element['#format'] = array_shift($intersect);
    $element['format']['format']['#default_value'] = $element['#format'];
  }

  return $element;
}

/**
 * Get prefered text-format for user on specific field.
 *
 * @param  Object $account
 * @param  string $entity_type
 * @param  string $bundle
 * @param  string $field
 * @return array
 * @see    go_filter_process_format
 */
function go_get_user_text_formats_for_field($account, $entity_type = '', $bundle = '', $field = '') {
  if ($tf_config = variable_get('go_text_formats')) {
    if (!empty($tf_config[$entity_type][$bundle][$field])) {
      return go_get_user_text_formats($account, $tf_config[$entity_type][$bundle][$field]);
    }
  }
  return array();
}

/**
 * Get prefered text-format for user.
 *
 * @param  object $account
 * @return array
 * @see    go_filter_process_format
 * @see    go_get_user_text_formats_for_field
 */
function go_get_user_text_formats($account, $text_format_configure = array()) {
  if (!$text_format_configure) {
    if (!$tf_config = variable_get('go_text_formats')) {
      return array();
    }

    if (!empty($tf_config['roles'])) {
      return array();
    }

    $text_format_configure = $tf_config['roles'];
  }

  // List allowed text formats from Drupal config
  $available_formats = array_keys(filter_formats($user));

  // Get list of text formats in settings
  $array_formats = array();
  $user_roles = array_keys($account->roles);

  foreach ($text_format_configure as $role_id => $text_format) {
    if (in_array($role_id, $user_roles)) {
      $array_formats[] = $text_format;
    }
  }

  if ($intersect = array_intersect($array_formats, $available_formats)) {
    return $intersect;
  }

  return array();
}
