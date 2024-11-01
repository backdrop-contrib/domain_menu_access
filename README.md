Domain Menu Access
=======

Domain Menu Access is an extension to Domain module, allowing
administrators to configure visitors' access to selected
menu items based on current domain they are viewing.

It lets administrators decide whether a specific menu item
should be hidden on selected domains (regardless of it being enabled
by default using standard Backdrop CMS functionality), or should it be
displayed on selected domains even if disabled by default.


Installation
------------

 - Install this module using the [official Backdrop CMS instructions](https://backdropcms.org/guide/modules).

 - Grant 'Administer menus per domain' permission to relevant
   admin users using Administer / People / Permissions
   (/configuration/people/permissions)


Usage
-----

Access to all menu items is managed on standard admin "Edit menu item"
pages in Admin / Structure / Menus, separately for each menu item,
using domain checkboxes in "Manage item visibility per domain" fieldset.

Use "Show menu item" checkboxes to force displaying items which by default
are disabled by Enabled checkbox in Menu settings section.

Use "Hide menu item" checkboxes to force hiding items which by default
are enabled.

Note that these settings will be ignored in administration area,
which means that all menu items will be enabled or disabled based
on default Backdrop CMS settings only, as otherwise default state
of a menu item could be changed by accident.


Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/domain_menu_access/issues.


Current Maintainers
-------------------

- [Tim Erickson](https://github.com/stpaultim)
- [Sudipto Kumar Mitra (sudipto68)](https://github.com/sudipto68)

Credits
-------

- Domain Menu Access was [ported from Drupal](https://www.drupal.org/project/domain_menu_access) where is was created by Maciej Zgadzaj [Zgadzaj](http://drupal.org/user/271491).
