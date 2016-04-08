<?php
/**
 * Zend Framework
 *
 * LICENSE
 *
 * This source file is subject to version 1.0 of the Zend Framework
 * license, that is bundled with this package in the file LICENSE,
 * and is available through the world-wide-web at the following URL:
 * http://www.zend.com/license/framework/1_0.txt. If you did not
 * receive a copy of the Zend Framework license and are unable to
 * obtain it through the world-wide-web, please send a note to
 * license@zend.com so we can mail you a copy immediately.
 *
 * @package    Zend_Json
 * @copyright  Copyright (c) 2006 Zend Technologies USA Inc. (http://www.zend.com/)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * Zend_Json_Exception
 */
require_once 'Zend/Json/Exception.php';


/**
 * Encode PHP constructs to JSON
 *
 * @package    Zend_Json
 * @copyright  Copyright (c) 2006 Zend Technologies USA Inc. (http://www.zend.com/)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Json_Encoder
{
    /**
     * Array of visited objects; used to prevent cycling.
     *
     * @var array
     */
    protected $_visited = array();

    /**
     * Constructor
     */
    protected function __construct()
    {
    }

    /**
     * Use the JSON encoding scheme for the value specified
     *
     * @param mixed $value  value the object to be encoded
     * @return string  The encoded value
     */
    public static function encode($value)
    {
        $encoder = new Zend_Json_Encoder();

        return $encoder->_encodeValue($value);
    }

    /**
     * Recursive driver which determines the type of value to be encoded
     * and then dispatches to the appropriate method. $values are either
     *    - objects (returns from {@link _encodeObject()})
     *    - arrays (returns from {@link _encodeArray()})
     *    - basic datums (e.g. numbers or strings) (returns from {@link _encodeDatum()})
     *
     * @param $value mixed The value to be encoded
     * @return string Encoded value
     */
    protected function _encodeValue(&$value)
    {
    	if (is_object($value)) {
            return $this->_encodeObject($value);
    	} else if (is_array($value)) {
            return $this->_encodeArray($value);
    	}

        return $this->_encodeDatum($value);
    }



    /**
     * Encode an object to JSON by encoding each of the public properties
     *
     * A special property is added to the JSON object called '__className'
     * that contains the name of the class of $value. This is used to decode
     * the object on the client into a specific class.
     *
     * @param $value object
     * @return string
     * @throws Zend_Json_Exception
     */
    protected function _encodeObject(&$value)
    {
        if ($this->_wasVisited($value)) {
    	    throw new Zend_Json_Exception(
                'Cycles not supported in JSON encoding, cycle introduced by '
                . 'class "' . get_class($value) . '"'
            );
    	}

        $this->_visited[] = $value;

    	$props = '';
    	foreach (get_object_vars($value) as $name => $propValue) {
    	    if (isset($propValue)) {
        		$props .= ', '
                        . $this->_encodeValue($name)
        		        . ' : '
                        . $this->_encodeValue($propValue);
    	    }
    	}

    	return '{' . '"__className": "' . get_class($value) . '"'
                . $props . '}';
    }


    /**
     * Determine if an object has been serialized already
     *
     * @access protected
     * @param mixed $value
     * @return boolean
     */
    protected function _wasVisited(&$value)
    {
        if (in_array($value, $this->_visited, true)) {
            return true;
        }

        return false;
    }


    /**
     * JSON encode an array value
     *
     * Recursively encodes each value of an array and returns a JSON encoded
     * array string.
     *
     * @param $array array
     * @return string
     */
    protected function _encodeArray(&$array)
    {
        $tmpArray = array();
        $assoc = false;

        // Check for associative array
        foreach (array_keys($array) as $key) {
            if (!is_int($key)) {
                $assoc = true;
                break;
            }
        }
        
        if ($assoc) {
            $result = '{';
            foreach ($array as $key => $value) {
                $key = (string) $key;
        		$tmpArray[] = $this->_encodeString($key)
        		            . ' : '
                            . $this->_encodeValue($value);
            }
            $result .= implode(', ', $tmpArray);
            $result .= '}';
        } else {
            $result = '[';
            $length = count($array);
            for ($i = 0; $i < $length; $i++) {
                $tmpArray[] = $this->_encodeValue($array[$i]);
            }
            $result .= implode(', ', $tmpArray);
            $result .= ']';
        }

    	return $result;
    }


    /**
     * JSON encode a basic data type (string, number, boolean, null)
     *
     * If value type is not a string, number, boolean, or null, the string
     * 'null' is returned.
     *
     * @param $value mixed
     * @return string
     */
    protected function _encodeDatum(&$value)
    {
        $result = 'null';

    	if (is_numeric($value)) {
    	    $result = (string)$value;
        } elseif (is_string($value)) {
            $result = $this->_encodeString($value);
    	} elseif (is_bool($value)) {
    	    $result = $value ? 'true' : 'false';
        }

    	return $result;
    }


    /**
     * JSON encode a string value by escaping characters as necessary
     *
     * @param $value string
     * @return string
     */
    protected function _encodeString(&$string)
    {
        // Escape these characters with a backslash:
        // " \ / \n \r \t \b \f
        $search  = array('\\', "\n", "\t", "\r", "\b", "\f", '"');
        $replace = array('\\\\', '\\n', '\\t', '\\r', '\\b', '\\f', '\"');
        $string  = str_replace($search, $replace, $string);

        // Escape certain ASCII characters:
        // 0x08 => \b
        // 0x0c => \f
        $string = str_replace(array(chr(0x08), chr(0x0C)), array('\b', '\f'), $string);

    	return '"' . $string . '"';
    }


    /**
     * Encode the constants associated with the ReflectionClass
     * parameter. The encoding format is based on the class2 format
     *
     * @param $cls ReflectionClass
     * @return string Encoded constant block in class2 format
     */
    static private function _encodeConstants(ReflectionClass $cls)
    {
    	$result    = "constants : {";
    	$constants = $cls->getConstants();

        $tmpArray = array();
    	if (!empty($constants)) {
            foreach ($constants as $key => $value) {
                $tmpArray[] = "$key: " . self::encode($value);
            }

            $result .= implode(', ', $tmpArray);
        }

    	return $result . "}";
    }


    /**
     * Encode the public methods of the ReflectionClass in the
     * class2 format
     *
     * @param $cls ReflectionClass
     * @return string Encoded method fragment
     *
     */
    static private function _encodeMethods(ReflectionClass $cls)
    {
    	$methods = $cls->getMethods();
    	$result = 'methods : {';

        $started = false;
        foreach ($methods as $method) {
    	    if (! $method->isPublic() || !$method->isUserDefined()) {
        		continue;
    	    }

    	    if ($started) {
        		$result .= ", ";
    	    }
            $started = true;

    	    $result .= " " .$method->getName(). ': function(';

    	    if ('__construct' != $method->getName()) {
        		$parameters  = $method->getParameters();
                $paramCount  = count($parameters);
                $argsStarted = false;

        		$argNames = "var argNames = [";
                foreach ($parameters as $param) {
        		    if ($argsStarted) {
            			$result .= ', ';
        		    }

        		    $result .= $param->getName();

        		    if ($argsStarted) {
            			$argNames .= ', ';
        		    }

        		    $argNames .= '"' . $param->getName() . '"';

                    $argsStarted = true;
        		}
        		$argNames .= "];";

        		$result .= ") {"
        		         . $argNames
            		     . "var result = ZAjaxEngine.invokeRemoteMethod("
            		     . "this, '" . $method->getName()
                         . "', argNames, arguments);"
                		 . "return(result);}";
    	    } else {
        		$result .= ") {}";
    	    }
    	}

    	return $result . "}";
    }


    /**
     * Encode the public properties of the ReflectionClass in the class2
     * format.
     *
     * @param $cls ReflectionClass
     * @return string Encode properties list
     *
     */
    static private function _encodeVariables(ReflectionClass $cls)
    {
    	$properties = $cls->getProperties();
    	$propValues = get_class_vars($cls->getName());
    	$result = "variables : {";
    	$cnt = 0;

        $tmpArray = array();
    	foreach ($properties as $prop) {
    	    if (! $prop->isPublic()) {
        		continue;
    	    }

            $tmpArray[] = $prop->getName()
                        . self::encode($propValues[$prop->getName()]);
        }
        $result .= implode(',', $tmpArray);

    	return $result . "}";
    }

    /**
     * Encodes the given $className into the class2 model of encoding PHP
     * classes into JavaScript class2 classes.
     * NOTE: Currently only public methods and variables are proxied onto
     * the client machine
     *
     * @param $className string The name of the class, the class must be
     * instantiable using a null constructor
     * @param $package string Optional package name appended to JavaScript
     * proxy class name
     * @return string The class2 (JavaScript) encoding of the class
     * @throws Zend_Json_Exception
     */
    static public function encodeClass($className, $package = '')
    {
    	$cls = new ReflectionClass($className);
    	if (! $cls->isInstantiable()) {
    	    throw new Zend_Json_Exception("$className must be instantiable");
    	}

    	return "Class.create('$package$className', {"
    	        . self::_encodeConstants($cls)    .", "
    	        . self::_encodeMethods($cls)      .", "
    	        . self::_encodeVariables($cls)    .'});';
    }


    /**
     * Encode several classes at once
     *
     * Returns JSON encoded classes, using {@link encodeClass()}.
     *
     * @param array $classNames
     * @param string $package
     * @return string
     */
    static public function encodeClasses($classNames, $package = '')
    {
    	$result = '';
    	foreach ($classNames as $className) {
    	    $result .= self::encodeClass($className, $package);
    	}

    	return $result;
    }

}


