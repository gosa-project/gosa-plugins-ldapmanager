<?php

/*
   This code is part of GOsa (https://gosa.gonicus.de)
   Copyright (C) 2007 Fabian Hickert

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


class Step_Config2 extends setup_step
{
  var $governmentmode = FALSE;
  var $sambaidmapping = FALSE;
  var $header_image = "images/ldapserver.png";

  var $cyrusunixstyle = FALSE;
  var $mail       = "none";
  var $mail_methods   = array();
  var $mail_settings = array("vacationdir"        => "/etc/gosa/vacation",
                             "vacationdir_active" => FALSE);

  var $generic_settings  = array( "enableCopyPaste" => false,
                                  "wws_ou"        => "ou=winstations",
                                  "wws_ou_active" => FALSE,
                                  "snapshot_active"     => FALSE,
                                  "snapshot_base"       => "ou=snapshots,%base%",
                                  "snapshot_user"       => "cn=ldapadmin,%base%",
                                  "snapshot_password"   => "",
                                  "snapshot_server"     => "%connection%");

  var $samba_settings    = array( "samba_sid"        => "0-815-4711",
                                  "samba_sid_active" => FALSE,
                                  "samba_rid"        => 1000,
                                  "smbhash"          => 'SMBHASH',
                                  "samba_rid_active" => FALSE); 

  var $attributes = array("governmentmode","sambaidmapping","cyrusunixstyle","mail");

  function Step_Config2()
  {
    $this->update_strings();
    $tmp = $this->get_available_mail_classes();
    foreach($tmp['name'] as $name){
      $this->mail_methods[$name] = $name;
    }

    /* Look for samba password generation method */
    if(file_exists("/usr/bin/mkntpasswd")){
      $pwdhash  = "/usr/bin/mkntpasswd";
    } elseif (preg_match("/^Usage: mkntpwd /", shell_exec ("mkntpwd 2>&1"))){
      $pwdhash= "mkntpwd";
    } else {
      $pwdhash= 'perl -MCrypt::SmbHash -e "print join(q[:], ntlmgen \$ARGV[0]), $/;"';
    }

    $this->samba_settings['smbhash'] = $pwdhash;
  }

 
  function update_strings()
  {
    $this->s_title      = _("GOsa settings 2/3");
    $this->s_title_long = _("GOsa settings 2/3");
    $this->s_info       = _("Customize special parameters");
  }

 
  function execute()
  {
    /* Update snapshot values, with already collected values */
    foreach($this->generic_settings as $key => $value){
      foreach(array("snapshot_base","snapshot_user","snapshot_server") as $attr){
        foreach($this->parent->captured_values as $replace_name => $replace_value){
          if(is_string($replace_value))  {
            $this->generic_settings[$attr] = preg_replace("/%".$replace_name."%/",$replace_value,$this->generic_settings[$attr]);
          }
        }
      }
    }

    $smarty = get_smarty();
    $smarty->assign("generic_settings",$this->generic_settings);
    $smarty->assign("mail_settings",$this->mail_settings);
    $smarty->assign("mail_methods",$this->mail_methods);
    $smarty->assign("samba_settings",$this->samba_settings);
    $smarty->assign("bool",array(FALSE => _("No"), TRUE => _("Yes")));
        foreach($this->attributes as $attr){
      $smarty->assign($attr,$this->$attr);
    }
    return($smarty -> fetch (get_template_path("../setup/setup_config2.tpl")));
  }

  function save_object()
  {
    if(isset($_POST['step6_posted'])){

      /* Get attributes */
      foreach($this->attributes as $attr){
        if(isset($_POST[$attr])){
          $this->$attr = validate($_POST[$attr]);
        }
      }

      /* Mail settings */
      if(isset($_POST['vacationdir_active'])){
        $this->mail_settings['vacationdir_active'] = TRUE;
        if(isset($_POST['vacationdir'])){
          $this->mail_settings['vacationdir'] = $_POST['vacationdir'];
        }
      }else{
        $this->mail_settings['vacationdir_active'] = FALSE;
      }

      if(isset($_POST['enableCopyPaste'])){
        $this->generic_settings['enableCopyPaste'] = $_POST['enableCopyPaste'];
      }

      if(isset($_POST['wws_ou_active'])){
        $this->generic_settings['wws_ou_active'] = TRUE;
        if(isset($_POST['wws_ou'])){
          $this->generic_settings['wws_ou'] = $_POST['wws_ou'];
        }
      }else{
        $this->generic_settings['wws_ou_active'] = FALSE;
      }

      if(isset($_POST['snapshot_active'])){
        $this->generic_settings['snapshot_active'] = TRUE;
        if(isset($_POST['snapshot_base'])){
          $this->generic_settings['snapshot_base'] = $_POST['snapshot_base'];
        }
        if(isset($_POST['snapshot_user'])){
          $this->generic_settings['snapshot_user'] = $_POST['snapshot_user'];
        }
        if(isset($_POST['snapshot_password'])){
          $this->generic_settings['snapshot_password'] = $_POST['snapshot_password'];
        }
        if(isset($_POST['snapshot_server'])){
          $this->generic_settings['snapshot_server'] = $_POST['snapshot_server'];
        }
      }else{
        $this->generic_settings['snapshot_active'] = FALSE;
      }

      /* Samba settings */
      if(isset($_POST['samba_sid_active'])){
        $this->samba_settings['samba_sid_active'] = TRUE;
        if(isset($_POST['samba_sid'])){
          $this->samba_settings['samba_sid'] = $_POST['samba_sid'];
        }
      }else{
        $this->samba_settings['samba_sid_active'] = FALSE;
      }
      if(isset($_POST['samba_rid_active'])){
        $this->samba_settings['samba_rid_active'] = TRUE;
        if(isset($_POST['samba_rid'])){
          $this->samba_settings['samba_rid'] = $_POST['samba_rid'];
        }
      }else{
        $this->samba_settings['samba_rid_active'] = FALSE;
      }
      if(isset($_POST['smbhash'])){
        $this->samba_settings['smbhash'] = $_POST['smbhash'];
      }

    }

    $tmp = $this->check();
    if(count($tmp) == 0){
      $this->is_completed = TRUE;
    }else{
      $this->is_completed = FALSE;
    }
  }


  function check()
  {
    $message = array();
    return($message);
  }
  

  /* Attributes that are interesting for configuration generation */
  function get_attributes()
  {
    $tmp = setup_step::get_attributes();
    foreach(array("samba_settings","generic_settings","mail_settings") as $attr){
      $tmp[$attr]= $this->$attr;
    }
    return($tmp);
  }

/* Returns the classnames auf the mail classes */
  function get_available_mail_classes()
  {
    $dir = opendir( "../include");
    $methods = array();
    $suffix = "class_mail-methods-";
    $lensuf = strlen($suffix);
    $prefix = ".inc";
    $lenpre = strlen($prefix);
    $i = 0;
    while (($file = readdir($dir)) !== false){

      if(stristr($file,$suffix)) {
        $lenfile = strlen($file);
        $methods['name'][$i] = substr($file,$lensuf,($lenfile-$lensuf)-$lenpre);
        $methods['file'][$i] = $file;
        $methods[$i]['file'] = $file;
        $methods[$i]['name'] = substr($file,$lensuf,($lenfile-$lensuf)-$lenpre);
        $i++;
      }
    }
    return($methods);
  }

}

// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>