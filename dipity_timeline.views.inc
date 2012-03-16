<?php

/**
 * @file
 * Defines the View Style Plugins for Views Slideshow module.
 */

/**
 * Implements hook_views_plugins().
 */
function dipity_timeline_views_plugins() {
  return array(
    'style' => array(
      'dipity_timeline' => array(
        'title' => t('Dipity Timeline'),
        'help' => t('Dipity timeline widget.'),
        'handler' => 'dipity_timeline_plugin_style_timeline',
        'uses row plugin' => FALSE,
        'uses row class' => FALSE,
        'uses grouping' => FALSE,
        'uses fields' => TRUE,
        'uses options' => FALSE,
        'type' => 'normal',
      ),
    ),
  );
}
