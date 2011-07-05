<?php

/**
 * @file
 * Extension for Domain module, which allows showing/hiding menu items per domain.
 */

/**
 * Implementation of hook_form_FORM_ID_alter().
 */
function domain_menu_access_form_menu_edit_item_alter(&$form, &$form_state) {
  if (user_access('administer menus per domain')) {
    // Load default values.
    $show_default_value = (isset($form['menu']['options']['#value']['domains']['show'])) ? $form['menu']['options']['#value']['domains']['show'] : array();
    $hide_default_value = (isset($form['menu']['options']['#value']['domains']['hide'])) ? $form['menu']['options']['#value']['domains']['hide'] : array();
    // If any of domain boxes are selected, display fieldset as expanded.
    $collapsed = (count($show_default_value) || count($hide_default_value)) ? FALSE : TRUE;
    $form['domain_menu_access']['manage'] = array(
      '#type'           => 'fieldset',
      '#title'          => t('Manage item visibility per domain'),
      '#collapsible'    => TRUE,
      '#collapsed'      => $collapsed,
    );
    // Get list of all available domains.
    // Add 'd' to array keys so it is saved properly even for domain_id = 0.
    $options = array();
    foreach (domain_domains() as $domain) {
      $options['d' . $domain['domain_id']] = $domain['sitename'];
    }
    // Show menu item per domain config.
    $form['domain_menu_access']['manage']['domain_menu_access_show'] = array(
      '#type'           => 'checkboxes',
      '#title'          => t('Show menu item only on selected domains'),
      '#options'        => $options,
      '#default_value'  => $show_default_value,
      '#description'    => t('Show this menu item only on selected domain(s). If you select no domains, the menu item will be visible on all domains.'),
    );
    // Hide menu item per domain config.
    $form['domain_menu_access']['manage']['domain_menu_access_hide'] = array(
      '#type'           => 'checkboxes',
      '#title'          => t('Hide menu item on selected domains'),
      '#options'        => $options,
      '#default_value'  => $hide_default_value,
      '#description'    => t('Hide this menu item on selected domain(s). If you select no domains, the menu item will be visible on all domains.'),
    );
    $form['#validate'][] = 'domain_menu_access_form_menu_edit_item_validate';
    // Make sure that our submit is called before menu_edit_item_submit()
    // from Drupal core menu.admin.inc, as there the changes are being saved.
    array_unshift($form['#submit'], 'domain_menu_access_form_menu_edit_item_submit');
  }
}

/**
 * Processes updated form submission and adds extra
 * information to menu $item['options'] element.
 */
function domain_menu_access_form_menu_edit_item_validate($form, &$form_state) {
  if ($form_state['submitted'] && user_access('administer menus per domain')) {
    // Make sure that menu item is not marked to be both shown and hidden for the same domain.
    foreach ($form_state['values']['domain_menu_access_hide'] as $key => $value) {
      if ($value && isset($form_state['values']['domain_menu_access_show'][$key]) && $form_state['values']['domain_menu_access_show'][$key]) {
        form_set_error('domain_menu_access_hide', t('Cannot both show and hide menu item for the same domain.'));
      }
    }
  }
}

/**
 * Processes updated form submission and adds extra
 * information to menu $item['options'] element.
 */
function domain_menu_access_form_menu_edit_item_submit($form, &$form_state) {
  if ($form_state['submitted'] && user_access('administer menus per domain')) {
    // Clear previous domain access values.
    $form_state['values']['menu']['options']['domains'] = array(
      'show' => array(),
      'hide' => array(),
    );
    // Process showing menu item per domain.
    foreach ($form_state['values']['domain_menu_access_show'] as $key => $value) {
      if ($value) {
        $form_state['values']['menu']['options']['domains']['show'][$key] = $key;
      }
    }
    // Process hiding menu item per domain.
    foreach ($form_state['values']['domain_menu_access_hide'] as $key => $value) {
      if ($value) {
        $form_state['values']['menu']['options']['domains']['hide'][$key] = $key;
      }
    }
  }
}
