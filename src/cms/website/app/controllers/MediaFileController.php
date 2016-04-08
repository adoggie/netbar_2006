<?php

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
require_once 'util.php';


class MediaFileController extends Zend_Controller_Action 
{
    public function indexAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('media_file_bar.php');
    }

    public function NewAction()
    {
        for($i=0;$i<10;$i++){
        	print util_get_uuid().'<br>';
        }
        
    }
    
    public function showAction(){
    	//if( Zend::isRegistered('name') ){
    	echo Zend::registry('name')->name;
    	//	echo 'new line';
    	//}
	}
}

