<?php

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
require_once 'util.php';


class FrameController extends Zend_Controller_Action 
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

  
    public function topAction(){
     	$view = new Zend_View();
        $view->setScriptPath('app/views');  
        //echo 'dfdfdf'      ;
        echo $view->render('top.php');
    }
    public function leftAction(){
     	$view = new Zend_View();
        $view->setScriptPath('app/views');        
        echo $view->render('left.php');
    }
    public function rightAction(){
     	$view = new Zend_View();
        $view->setScriptPath('app/views');        
        echo $view->render('right.php');
    }
    
    public function noRouteAction()
    {
        //$this->_redirect('/');
        echo 'scott testing';
    }
}


?>
