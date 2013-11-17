<?php
namespace Drupal\go\Hook\FormAlter;

/**
 * Remove the current password field from the user_profile_form form (user/%/edit).
 *
 * @see nocurrent_pass_form_user_profile_form_alter().
 */
class UserProfile {
  public funtion alter(&$form, &$form_state) {
    // searches the #validate array for the current_pass validation function, and removes it
    $key = array_search('user_validate_current_pass', $form['#validate']);
    if ($key !== FALSE) {
      unset($form['#validate'][$key]);
    }
    // hide the current password fields
    $form['account']['current_pass_required_value']['#access'] = FALSE;
    $form['account']['current_pass']['#access'] = FALSE;
  }
}
