<?php
// $Id: phpmailer.drupal.inc,v 1.1.2.1.2.4 2009/06/10 13:07:48 smk Exp $

/**
 * @file
 * Implements PHPMailer support on behalf of Drupal core.
 */

require_once drupal_get_path('module', 'phpmailer') . '/includes/phpmailer.class.inc';

/**
 * Send out an e-mail.
 *
 * @param $to
 *   The mail address or addresses where the message will be send to.
 * @param $subject
 *   Subject of the e-mail to be sent.
 * @param $body
 *   Message to be sent.
 * @param $from
 *   Sender e-mail address.
 * @param $headers
 *   Associative array containing the headers to add.
 */
function phpmailer_send($to, $subject, $body, $from, $headers) {
  static $mail;

  if (!isset($mail)) {
    $mail = new DrupalPHPMailer();
  }

  // Fix empty From address. This resembles the behavior of Drupal 6 and later.
  if (!$from) {
    $from = variable_get('site_mail', ini_get('sendmail_from'));
  }

  // Parse 'From' e-mail address.
  $address = phpmailer_parse_address($from);
  $mail->From = $address[0]['mail'];
  if ($address[0]['name'] != '') {
    $mail->FromName = $address[0]['name'];
  }
  unset($headers['From']);

  if (variable_get('phpmailer_debug_email', '') === '') {
    // Set recipients.
    foreach (phpmailer_parse_address($to) as $address) {
      $mail->AddAddress($address['mail'], $address['name']);
    }
    // Extract CCs and BCCs from headers.
    if (isset($headers['CC'])) {
      foreach (phpmailer_parse_address($headers['CC']) as $address) {
        $mail->AddCC($address['mail'], $address['name']);
      }
    }
    if (isset($headers['BCC'])) {
      foreach (phpmailer_parse_address($headers['BCC']) as $address) {
        $mail->AddBCC($address['mail'], $address['name']);
      }
    }
  }
  else {
    // Reroute to debug e-mail address.
    $mail->AddAddress(variable_get('phpmailer_debug_email', ''));
  }
  unset($headers['CC'], $headers['BCC']);

  // Extract Content-Type and charset.
  if (isset($headers['Content-Type'])) {
    $content_type = explode(';', $headers['Content-Type']);
    $mail->ContentType = trim(array_shift($content_type));
    foreach ($content_type as $param) {
      $param = explode('=', $param, 2);
      $key = trim($param[0]);
      if ($key == 'charset') {
        $mail->CharSet = trim($param[1]);
      }
      else {
        $mail->ContentType .= '; ' . $key . '=' . trim($param[1]);
      }
    }
    unset($headers['Content-Type']);
  }

  // Set additional properties.
  $properties = array(
    'X-Priority'                => 'Priority',
    'Content-Transfer-Encoding' => 'Encoding',
    'Sender'                    => 'Sender',
    'Message-ID'                => 'MessageID',
    // Custom property.
    // @see DrupalPHPMailer::CreateHeader()
    'Return-Path'               => 'ReturnPath',
  );
  foreach ($properties as $source => $property) {
    if (isset($headers[$source])) {
      $mail->$property = $headers[$source];
      unset($headers[$source]);
    }
  }

  // This one is always set by PHPMailer.
  unset($headers['MIME-Version']);

  // Add remaining header lines.
  // Note: Any header lines MUST already be checked by the caller for unwanted
  // newline characters to avoid header injection.
  // @see PHPMailer::SecureHeader()
  foreach ($headers as $key => $value) {
    $mail->AddCustomHeader("$key:$value");
  }

  $mail->Subject = $subject;
  $mail->Body = $body;

  if ($mail->SMTPDebug) {
    ob_start();
  }

  if (!($result = $mail->Send())) {
    watchdog('phpmailer', t('Error sending e-mail (from %from to %to): %error.', array('%from' => $from, '%to' => $to, '%error' => $mail->ErrorInfo)), WATCHDOG_ERROR);
  }

  // Reset object properties.
  $mail->Reset();

  if ($mail->SMTPDebug) {
    if ($debug = ob_get_contents()) {
      drupal_set_message($debug);
    }
    ob_end_clean();
  }

  return $result;
}

