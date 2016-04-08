<?php
/**
 * Zend Framework
 *
 * LICENSE
 *
 * This source file is subject to version 1.0 of the Zend Framework
 * license, that is bundled with this package in the file LICENSE, and
 * is available through the world-wide-web at the following URL:
 * http://www.zend.com/license/framework/1_0.txt. If you did not receive
 * a copy of the Zend Framework license and are unable to obtain it
 * through the world-wide-web, please send a note to license@zend.com
 * so we can mail you a copy immediately.
 *
 * @package    Zend_Controller
 * @subpackage Plugins
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/** Zend_Controller_Plugin_Abstract */
require_once 'Zend/Controller/Plugin/Abstract.php';

/** Zend_Controller_Dispatcher_Token */
require_once 'Zend/Controller/Dispatcher/Token.php';


/**
 * @package    Zend_Controller
 * @subpackage Plugins
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Controller_Plugin_Broker extends Zend_Controller_Plugin_Abstract
{

    /**
     * Array of instance of objects implementing Zend_Controller_Plugin_Interface
     *
     * @var Zend_Controller_Plugin_Interface
     */
    protected $_plugins = array();


    /**
     * Register a plugin.
     *
     * @param Zend_Controller_Plugin_Interface $plugin
     * @return Zend_Controller_Plugin_Broker
     */
    public function registerPlugin(Zend_Controller_Plugin_Interface $plugin)
    {
        if (array_search($plugin, $this->_plugins, true) !== false) {
            throw new Zend_Controller_Exception('Plugin already registered.');
        }
        $this->_plugins[] = $plugin;
        return $this;
    }


    /**
     * Unregister a plugin.
     *
     * @param Zend_Controller_Plugin_Interface $plugin
     * @return Zend_Controller_Plugin_Broker
     */
    public function unregisterPlugin(Zend_Controller_Plugin_Interface $plugin)
    {
        $key = array_search($plugin, $this->_plugins, true);
        if ($key===false) {
            throw new Zend_Controller_Exception('Plugin never registered.');
        }
        unset($this->_plugins[$key]);
        return $this;
    }


	/**
	 * Called before Zend_Controller_Front begins evaluating the
	 * request against its routes.
	 *
	 * @return void
	 */
	public function routeStartup()
	{
	    foreach ($this->_plugins as $plugin) {
	        $plugin->routeStartup();
	    }
	}


	/**
	 * Called before Zend_Controller_Front exists its iterations over
	 * the route set.
	 *
	 * @param  Zend_Controller_Dispatcher_Token|boolean $action
	 * @return Zend_Controller_Dispatcher_Token|boolean
	 */
	public function routeShutdown($action)
	{
	    foreach ($this->_plugins as $plugin) {
	        $action = $plugin->routeShutdown($action);
	    }
	    return $action;
	}


	/**
	 * Called before Zend_Controller_Front enters its dispatch loop.
	 * During the dispatch loop, Zend_Controller_Front keeps a stack of
	 * Zend_Controller_Dispatcher_Token objects, and uses Zend_Controller_Dispatcher to dispatch the
	 * Zend_Controller_Dispatcher_Token objects to controllers/actions.
	 *
	 * @param  Zend_Controller_Dispatcher_Token|boolean $action
	 * @return Zend_Controller_Dispatcher_Token|boolean
	 */
	public function dispatchLoopStartup($action)
	{
	    foreach ($this->_plugins as $plugin) {
	        $action = $plugin->dispatchLoopStartup($action);
	    }
	    return $action;
	}


	/**
	 * Called before an action is dispatched by Zend_Controller_Dispatcher.
	 *
	 * @param  Zend_Controller_Dispatcher_Token|boolean $action
	 * @return Zend_Controller_Dispatcher_Token|boolean
	 */
	public function preDispatch($action)
	{
	    foreach ($this->_plugins as $plugin) {
	        $action = $plugin->preDispatch($action);
	    }
	    return $action;
	}


	/**
	 * Called after an action is dispatched by Zend_Controller_Dispatcher.
	 *
	 * @param  Zend_Controller_Dispatcher_Token|boolean $action
	 * @return Zend_Controller_Dispatcher_Token|boolean
	 */
	public function postDispatch($action)
	{
	    foreach ($this->_plugins as $plugin) {
	        $action = $plugin->postDispatch($action);
	    }
	    return $action;
	}


	/**
	 * Called before Zend_Controller_Front exists its dispatch loop.
	 *
	 * @param  Zend_Controller_Dispatcher_Token|boolean $action
	 * @return Zend_Controller_Dispatcher_Token|boolean
	 */
	public function dispatchLoopShutdown()
	{
	   foreach ($this->_plugins as $plugin) {
	       $action = $plugin->dispatchLoopShutdown();
	   }
	}
}
