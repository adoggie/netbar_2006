<?php
session_start();
include 'Zend.php';
Zend::loadClass('Zend_Controller_Front');
class box{
	var $name;
}

$b = new box;
$b->name='scott';
Zend::register('name',$b);

if( !isset($_SESSION['userxx'])){
	print $_SERVER['REMOTE_ADDR'];
	//header("Location: info.php"); 
	exit;
}

$controller = Zend_Controller_Front::getInstance();
$controller->setControllerDirectory('../app/controllers');
$controller->dispatch();
?>
