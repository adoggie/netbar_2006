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
 * @package    Zend_Uri
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * Zend Framework utility class
 */
require_once 'Zend.php';

/**
 * Zend_Uri_Exception
 */
require_once 'Zend/Uri/Exception.php';

/**
 * Zend_Uri_Http
 */
require_once 'Zend/Uri/Http.php';

/**
 * Zend_Uri_Mailto
 */
require_once 'Zend/Uri/Mailto.php';


/**
 * @package    Zend_Uri
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
abstract class Zend_Uri
{


	/**
	 * Scheme of this URI (http, ftp, etc.)
	 * @var string
	 */
	protected $_scheme = '';


    /**
     * Return a string representation of this URI.
     *
     * @see     getUri()
     * @return  string
     */
    public function __toString()
    {
        return $this->getUri();
    }


    /**
     * Convenience function, checks that a $uri string is well-formed
     * by validating it but not returning an object.  Returns TRUE if
     * $uri is a well-formed URI, or FALSE otherwise.
     *
     * @param string $uri
     * @return boolean
     */
    static public function check($uri)
    {
        try {
            $uri = self::factory($uri);
        } catch (Exception $e) {
            return false;
        }

        return $uri->valid();
    }


    /**
     * Create a new Zend_Uri object for a URI.  If building a new URI, then $uri should contain
     * only the scheme (http, ftp, etc).  Otherwise, supply $uri with the complete URI.
     *
     * @param string $uri
     * @throws Zend_Uri_Exception
     * @return Zend_Uri
     */
    static public function factory($uri = 'http')
    {
        /**
         * Separate the scheme from the scheme-specific parts
         * @link http://www.faqs.org/rfcs/rfc2396.html
         */
        $uri = explode(':', $uri, 2);
        $scheme = strtolower($uri[0]);
        $schemeSpecific = isset($uri[1]) ? $uri[1] : '';

        if (!strlen($scheme)) {
            throw new Zend_Uri_Exception('An empty string was supplied for the scheme');
        }

        // Security check: $scheme is used to load a class file, so only alphanumerics are allowed.
        if (!ctype_alnum($scheme)) {
            throw new Zend_Uri_Exception('Illegal scheme supplied, only alphanumeric characters are permitted');
        }


        /**
         * Create a new Zend_Uri object for the $uri. If a subclass of Zend_Uri exists for the
         * scheme, return an instance of that class. Otherwise, a Zend_Uri_Exception is thrown.
         */
        switch ($scheme) {
            case 'mailto':
                // fall through to next case
            case 'http':
                // fall through to next case
            case 'https':
                if ($scheme == 'https' or $scheme == 'http') {
                    $className = 'Zend_Uri_Http';
                } else {
                    $className = 'Zend_Uri_' . ucfirst($scheme);
                }
                return new $className($scheme, $schemeSpecific);
            default:
				throw new Zend_Uri_Exception("Scheme \"$scheme\" is not supported");
        }

    }

    public function getScheme()
    {
    	if (!empty($this->_scheme)) {
    		return $this->_scheme;
    	} else {
    		return false;
    	}
    }


    /******************************************************************************
     * Abstract Methods
     *****************************************************************************/


    /**
     * Zend_Uri and its subclasses cannot be instantiated directly.
     * Use Zend_Uri::factory() to return a new Zend_Uri object.
     */
    abstract protected function __construct($scheme, $schemeSpecific = '');


    /**
     * Return a string representation of this URI.
     *
     * @return string
     */
    abstract public function getUri();


    /**
     * Returns TRUE if this URI is valid, or FALSE otherwise.
     *
     * @return boolean
     */
    abstract public function valid();

}


