<?php

class ldiftab extends tabs
{

    function __construct($config, $data, $dn)
    {
        parent::__construct($config, $data, $dn);
    }

    function save_object($save_current = FALSE)
    {
        parent::save_object($save_current);
    }


    function save($ignore_account = FALSE)
    {
    }
}
