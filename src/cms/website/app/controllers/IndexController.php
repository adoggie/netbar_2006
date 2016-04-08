<?php

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');

class IndexController extends Zend_Controller_Action 
{
    public function indexAction(){
     	$view = new Zend_View();
        $view->setScriptPath('app/views');        
        echo $view->render('mainframe.php');
        //$this->_redirect('www.google.com');
    }
}

?>
