<?php

namespace GosaLdapManager\addons\ldapmanager;

bindtextdomain("ldapManager", dirname(dirname(__FILE__)) . "/locale/compiled");

function __($GETTEXT) {
    return dgettext("ldapManager", $GETTEXT);
}
