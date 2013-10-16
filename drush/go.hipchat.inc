<?php

/**
 * @file ./drush/go.hipchat.inc
 *
 * @author Andy Truong
 */

function go_drush_hipchat_command_info() {
  $items['go-hipchat'] = array(
    'description' => 'Send message to Hipchat room.',
    'arguments' => array(
      'room_id' => 'ID of the chatroom.',
      'message' => 'Message to be sent to the room.',
    ),
    'options' => array(
      'from' => 'Sender name, default: Go Module',
      'token' => 'API Token, default: value of GO_HIPCHAT_API_TOKEN constant',
      'color' => 'Background color for the message (yellow, red, green, purple or random - default: yellow)',
      'notify' => 'Trigger notification for people in the room, default: 0',
    ),
    'aliases' => array('gohc'),
    'examples' => array(
      'drush gohc p.GoCMS "Hello room!"' => 'Send "Hello room!" to p.GoCMS chatroom.',
      'drush gohc Go1 "Log time please guys!" --from="Daniel Freshwater" --notify=1' => 'Freshy notify all people in Go1 room to log time.',
    ),
  );
  return $items;
}

/**
 * Callback function to send a message to Hipchat room.
 *
 * @param  string $room_id
 * @param  string $msg
 */
function drush_go_hipchat($room_id, $msg) {
  // #####################
  // Get params
  // #####################
  $token = drush_get_option('token', '');
  $from = drush_get_option('from', 'Go Module');
  $color = drush_get_option('color', 'yellow');
  $notify = drush_get_option('notify', 0);

  if (!$token) {
    if (!defined('GO_HIPCHAT_API_TOKEN')) {
      drush_set_error('No API Token specified.', 'Please run the command with --token value, or define GO_HIPCHAT_API_TOKEN constant in your settings.php');
    }
    $token = GO_HIPCHAT_API_TOKEN;
  }

  go_drush_hipchat($token, $room_id, $from, $msg, $color, $notify);
}

/**
 * Function to send hipchat message.
 */
function go_drush_hipchat($token, $room_id, $from, $msg = '', $color = 'yellow', $notify = 0) {
  $ch = curl_init("https://api.hipchat.com/v1/rooms/message");
  curl_setopt_array($ch, array(
    CURLOPT_RETURNTRANSFER => 1,
    CURLOPT_SSL_VERIFYPEER => FALSE,
    CURLOPT_POSTFIELDS => array(
      'auth_token'  => $token,
      'room_id'     => $room_id,
      'from'        => $from,
      'color'       => $color,
      'message'     => go_drush_hipchat_format_message($msg),
      'notify'      => $notify,
    ),
  ));

  $output = curl_exec($ch);
  if ($error = curl_error($ch)) {
    throw new Exception($error);
  }
}

/**
 * Format the message before sending…
 *
 * @param  string $msg
 * @return string
 */
function go_drush_hipchat_format_message($msg) {
  $filter = new stdClass();
  $filter->settings['filter_url_length'] = 25;
  $msg = filter_xss_admin($msg);
  $msg = _filter_url($msg, $filter);
  $msg = _filter_autop($msg);
  return $msg;
}
