<?php

/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in a slideshow of an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class dipity_timeline_plugin_style_timeline extends views_plugin_style {

  function init(&$view, &$display, $options = NULL) {
    parent::init(&$view, &$display, $options);

    $api_key = variable_get('dipity_timeline_api_key', '');
    $api_signature = variable_get('dipity_timeline_api_signature', '');
    drupal_add_js('http://www.dipity.com/js/api.js?key=' . $api_key . '&sig=' . $api_signature, 'external');
  }

  // Set default options
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  // Build the settings form for the view.
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['key'] = array(
      '#type' => 'textfield',
      '#title' => t('API key'),
      '#default_value' => variable_get('dipity_timeline_api_key', ''),
    );
    $form['sig'] = array(
      '#type' => 'textfield',
      '#title' => t('Signature'),
      '#default_value' => variable_get('dipity_timeline_api_signature', ''),
    );
  }

  function render() {
    $options = $events = array();

    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      debug('views_plugin_style_default: Missing row plugin');
      return;
    }

    $dom_id = md5($this->view->name . REQUEST_TIME . rand());

    $options = array(
      'key' => variable_get('dipity_timeline_api_key', ''),
      'sig' => variable_get('dipity_timeline_api_signature', ''),
      //'defaultDate' => '',
      //'defaultEventImage' => '',
      //'defaultZoom' => '',
      //'gmtOffset' => '',
      //'intl' => '',
      //'theme' => array(),
      //'themes' => array(),
      'data' => array(),
    );

    foreach ($this->view->result as $key => $item) {
      $events[] = array(
        'eid' => $item->nid,
        'x' => $item->node_created,
        'title' => $item->node_title,
        'author' => $item->users_node_name,
        'authorURL' => url('user/' . $item->users_node_uid, array('absolute' => TRUE)),
        'date' => format_date($item->node_created),
        'description' => $item->field_body[0]['rendered']['#markup'],
        'img' => file_create_url($item->field_field_image[0]['rendered']['#item']['uri']),
        'll' => $item->field_field_geofield[0]['raw']['lat'] . ',' . $item->field_field_geofield[0]['raw']['lon'],
        //'specificity' => '',
        //'theme' => '',
        //'v' => 0,
      );
    }

    $options['data']['events'] = $events;

    drupal_add_js(array('dipity_timeline' => array($dom_id => $options)), 'setting');
    drupal_add_js(drupal_get_path('module', 'dipity_timeline') . '/js/dipity_timeline.drupal.js');
    return '<div id="dipity-timeline-dom-id-' . $dom_id . '" style="height:500px;"></div>';
  }
}
