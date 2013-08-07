<?php

/**
 * Command to sent mail.
 */
function drush_go_mail() {
  $module = 'go';
  $key = 'key';
  $language = language_default();
  $params = array();
  $from = drush_get_option('from', variable_get('site_mail', ini_get('sendmail_from')));
  $message = drupal_mail($module, $key, $to, $language, $params, $from, TRUE);

  $message['subject'] = drush_get_option('subject', 'Test e-mail');
  $message['body'] = drush_get_option('body', 'This is a test e-mail.');
  
  $to = drush_get_option('to');
  if(empty($to)) {
    return drush_set_error('--to option is required.');
  } 
  else {
    // Retrieve the responsible implementation for this message.
    $system = drupal_mail_system($module, $key);

    // Format the message body.
    $message = $system->format($message);

    // Send e-mail.
    $message['result'] = $system->mail($message);

    if($message['result']) {
      drush_log(dt("Test e-mail sent to @to success.", array('@to' => $to)), "success");
    }
    else { 
      return drush_set_error('An error occurred while sending the test e-mail.');
    }
  }  
}
