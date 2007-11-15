<?php

require_once("../../../include/autoload.inc");
restore_error_handler();
session_start();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Blubb</title>
<style type="text/css">@import url('../ObjectListViewport.css');</style>


  <meta name="generator" content="my hands">
  <meta name="description" content="GOsa - Login">
  <meta name="author" lang="de" content="Cajus Pollmeier">

  <meta http-equiv="Expires" content="Mon, 26 Jul 1997 05:00:00 GMT">

  <meta http-equiv="Last-Modified" content="Friday, 09th November 2007 09:14:31 +0000 GMT">
  <meta http-equiv="Cache-Control" content="no-cache">
  <meta http-equiv="Pragma" content="no-cache">
  <meta http-equiv="Cache-Control" content="post-check=0, pre-check=0">
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

  <style type="text/css">@import url('themes/default/style.css');</style>
  <link rel="shortcut icon" href="favicon.ico">

<script language="javascript" src="../ObjectListViewport.js" type="text/javascript"></script>
  <script language="javascript" src="include/png.js" type="text/javascript"></script>
  <script language="javascript" src="include/calendar.js" type="text/javascript"></script>
  <script language="javascript" src="include/focus.js" type="text/javascript"></script>
  <script language="javascript" src="include/warning.js" type="text/javascript"></script>
</head>
<body>
<button onclick='updateObjectListViewportSize();'>Tester</button>
<?php

/* This is good for testing... */
error_reporting (E_ALL | E_STRICT);

function get_smarty()
{
    echo "Smarty fake in each ./tests/ListTest[1-9]/index.php";
    date_default_timezone_set("europe/berlin");
    $smarty = new smarty;
    /* Set template compile directory */
    $smarty->compile_dir= '/var/spool/gosa/';
    $smarty->template_dir = '../';
    $smarty->caching= false;
    $smarty->php_handling= SMARTY_PHP_REMOVE;
    return($smarty);
}



/* Escape all preg_* relevant characters */
function normalizePreg($input)
{
  return (addcslashes($input, '[]()|/.*+-'));
}


/* Initiate autoloader... */
try {

	/* Get new test instance of the Configuration */
	$cr= Registry::getInstance("ConfigManager");
	$cr->load("../../../gosa.conf");

	/* Get a new test instance of ObjectListViewports */
	if(!isset($_SESSION['vp'])){
		$_SESSION['vp'] = new ObjectListViewport("plugin/sample");
	}
	$vp = $_SESSION['vp'];
	$content= $vp->render();

	echo preg_replace("/%LIST%/",$content,file_get_contents('tpl'));	

} catch (Exception $e) {
	echo "\n-GOsa Exception-----------------------------------------------------------\n\n".
		 $e->__toString().
		 "\n\n--------------------------------------------------------------------------\n\n";
}

?>
</body>
</html>