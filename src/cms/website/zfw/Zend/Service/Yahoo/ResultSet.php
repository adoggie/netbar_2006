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
 * @package    Zend_Service
 * @subpackage Yahoo
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * @todo Discussed this with Chuck and other Zenders.  Why was SeekableIterator
 *       implemented here?  Does seek() gain us anything in this context?  Why
 *       not use just Iterator or ArrayAccess + Iterator?
 * 
 * @package    Zend_Service
 * @subpackage Yahoo
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Service_Yahoo_ResultSet implements SeekableIterator {
    /**
     * @var DomNodeList $_result A DomNodeList of results
     */
    protected $_results;

    /**
     * @var DomDocument Yahoo Web Service Return Document
     */
    protected $_dom;

    /**
     * @var DOMXpath Xpath Object for $this->_dom
     */
    protected $_xpath;

    /**
     * @var int Current Item
     */
    protected $_currentItem = 0;

    /**
     * @var int  $totalResultsAvailable the total number of results available
     */
    public $totalResultsAvailable;
    
    /*
     * @var int $totalResultsReturned the number of results in this result set
     */
    public $totalResultsReturned;
    
    /*
     * @var int $firstResultPosition the offset in the total result set of this search set
     */
    public $firstResultPosition;

    
    /**
     * Parse the search response and retrieve the results for iteration
     *
     * @param DomDocument $dom the ReST fragment for this object
     */
    public function __construct(DomDocument $dom) {
        $this->totalResultsAvailable = (int) $dom->documentElement->getAttribute('totalResultsAvailable');
        $this->totalResultsReturned = (int) $dom->documentElement->getAttribute('totalResultsReturned');
        $this->firstResultPosition = (int) $dom->documentElement->getAttribute('firstResultPosition');

        $this->_dom = $dom;
    	$this->_xpath = new DOMXPath($dom);

    	$this->_xpath->registerNamespace("yh", $this->_namespace);

    	$this->_results = $this->_xpath->query("//yh:Result");
    }

    
    /**
     * Total Number of results returned
     *
     * @return int Total number of results returned
     */
    public function totalResults()
    {
		return (int) $this->totalResultsReturned;
    }

    
    /**
     * Implement SeekableIterator::current
     *
     * @return Zend_Service_Yahoo_Result
     */
    public function current()
    {
    	throw new Zend_Service_Exception("Zend_Service_Yahoo_ResultSet::current() should be overwritten in child classes");
    	//return new Zend_Service_Yahoo_Result($this->_results->item($this->_currentItem));
    }

    
    /**
     * Implement SeekableIterator::key
     *
     * @return int
     */
    public function key()
    {
    	return $this->_currentItem;
    }

    
    /**
     * Implement SeekableIterator::next
     */
    public function next()
    {
    	$this->_currentItem += 1;
    }

    
    /**
     * Implement SeekableIterator::rewind
     *
     * @return boolean
     */
    public function rewind()
    {
    	$this->_currentItem = 0;
    	return true;
    }

    
    /**
     * Implement SeekableIterator::sek
     *
     * @param int $item
     * @return Zend_Service_Yahoo_Result
     * @throws Zend_Service_Exception
     */
    public function seek($item)
    {
    	if ($this->valid($item)) {
    		$this->_currentItem = $item;
    		return $this->current();
    	} else {
    		/* @todo Should be an OutOfBoundsException but that was only added in PHP 5.1 */
    		throw new Zend_Service_Exception('Item not found');
    	}
    }

    
    /**
     * Implement SeekableIterator::valid
     *
     * @param int $item
     * @return boolean
     */
    public function valid($item = null)
    {
    	if (is_null($item) && $this->_currentItem < $this->_results->length) {
    		return true;
    	} elseif (!is_null($item) && $item <= $this->_results->length) {
    		return true;
    	} else {
    		return false;
    	}
    }
}

