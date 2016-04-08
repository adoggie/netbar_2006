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
 * @package    Zend_XmlRpc
 * @subpackage Value
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * Zend_XmlRpc_Value_Scalar
 */
require_once 'Zend/XmlRpc/Value/Scalar.php';


/**
 * @package    Zend_XmlRpc
 * @subpackage Value
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_XmlRpc_Value_DateTime extends Zend_XmlRpc_Value_Scalar
{

    /**
     * Set the value of a dateTime.iso8601 native type, The value is in iso8601 format
     *
     * @param mixed $value Integer of the unix timestamp or any string that can be parsed 
     *                     to a unix timestamp using the PHP strtotime() function
     */
    public function __construct($value)
    {
        $this->_type = self::XMLRPC_TYPE_DATETIME;

        // If the value is not numeric, we try to convert it to a timestamp (using the strtotime function)
        if (is_numeric($value)) {   // The value is numeric, we make sure it is an integer
            $value = (int)$value;
        } else {
            $value = strtotime($value);
            if ($value === false || $value == -1) { // cannot convert the value to a timestamp
                throw new Zend_Xml_Rpc_Value_Exception('Cannot convert given value \''. $value .'\' to a timestamp');
            }
        }
        $this->_value = date('c', $value);    // Convert the timestamp to iso8601 format
    }

    /**
     * Return the value of this object, convert the XML-RPC native dateTime value into a PHP integer (unix timestamp representation of the iso8601 date format)
     *
     * @return int As a Unix timestamp
     */
    public function getValue()
    {
        return strtotime($this->_value);
    }

}


