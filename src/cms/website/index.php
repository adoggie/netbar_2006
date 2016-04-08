<?php
session_start();
include 'Zend.php';
include 'config.php';

Zend::loadClass('Zend_Controller_Front');
//Zend::register('name',$b);

if( !isset( $_SESSION['dbconn'])  ){
	//$dbconn = @mysql_connect($DB_HOST, $DB_USER, $DB_PASSWD) ;
	$dbconn = @mysql_connect('127.0.0.1', 'root','') ;
	mysql_select_db('mpms');
	//mysql_select_db($dbconn	,$DB_NAME) or  ('Can\'t use foo : ' . mysql_error());
	
}
/*
if( !isset($_SESSION['userxx'])){
	print $_SERVER['REMOTE_ADDR'];
	//header("Location: info.php"); 
	exit;
}
*/
$controller = Zend_Controller_Front::getInstance();
$controller->setControllerDirectory('app/controllers');
$controller->dispatch();

?>
