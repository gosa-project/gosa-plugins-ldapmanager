<?php

class ldif extends plugin
{
  /* Definitions */
  var $plHeadline= "LDAP tools";
  var $plDescription= "Export LDIF or Excel snapshots of the LDAP tree";
  var $plIcon = "plugins/ldapmanager/images/ldif.png";

  /* attribute list for save action */
  var $attributes= array();
  var $objectclasses= array();
  var $ldif;

  function ldif (&$config)
  {
    /* Include config object */
    $this->ldif= new ldiftab($config, $config->data['TABS']['LDIFTAB'], "");
  }

  function execute()
  {
	/* Call parent execute */
	plugin::execute();

    /* Show main page */
    return ($this->ldif->execute());
  }

  /* Return plugin informations for acl handling
     #FIXME You can only read attributes within this report plugin */
  static function plInfo()
  {
    return (array(
        "plShortName"   => _("Ldap manager"),
        "plDescription" => _("Ldap manager")."&nbsp;("._("import")."/"._("export").")",
        "plSelfModify"  => FALSE,
        "plDepends"     => array(),
        "plPriority"    => 1,
        "plSection"     => array("addon"),
        "plCategory"    => array("ldapmanager" => array("objectClass" => "none", "description" => _("Ldap manager"))),

        "plProvidedAcls" => array()
        ));
  }



}


// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>
