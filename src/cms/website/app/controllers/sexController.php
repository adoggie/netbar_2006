<?php

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
require_once 'util.php';


class sexController extends Zend_Controller_Action 
{
    public function indexAction()
    {
    	for($i=0;$i<100;$i++){
    		echo util_get_uuid().'<br>';
    	}
    	 $view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->title1='ÖÐ¹úÈË';
        echo $view->render('show.php');
        echo 'sex::indexAction()';
    }

    public function barAction()
    {
        echo 'sex::barAction()';
        echo Zend::registry('name')->name;
    }
    
    public function showAction(){
    	//if( Zend::isRegistered('name') ){
    	echo Zend::registry('name')->name;
    	//	echo 'new line';
    	//}
	}
}


?>
