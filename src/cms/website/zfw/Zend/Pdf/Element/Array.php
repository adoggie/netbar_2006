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
 * @package    Zend_Pdf
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/** Zend_Pdf_Element */
require_once 'Zend/Pdf/Element.php';

/** Zend_Pdf_PHPArray */
require_once 'Zend/Pdf/PHPArray.php';



/**
 * PDF file 'array' element implementation
 *
 * @package    Zend_Pdf
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Pdf_Element_Array extends Zend_Pdf_Element
{
    /**
     * Object value
     * Array of Zend_Pdf_Element objects.
     * Appropriate methods must (!) be used to modify it to provide correct
     * work with objects and references.
     *
     * @var Zend_Pdf_PHPArray
     */
    private $_items;


    /**
     * Object constructor
     *
     * @param array $val   - array of Zend_Pdf_Element objects
     * @throws Zend_Pdf_Exception
     */
    public function __construct($val = null)
    {
        $this->_items = new Zend_Pdf_PHPArray();

        if ($val !== null  &&  is_array($val)) {
            foreach ($val as $element) {
                if (!$element instanceof Zend_Pdf_Element) {
                    throw new Zend_Pdf_Exception('Array elements must be Zend_Pdf_Element objects');
                }
                $this->_items[] = $element;
            }
        } else if ($val !== null){
            throw new Zend_Pdf_Exception('Argument must be an array');
        }
    }


    /**
     * Provides access to $this->_items
     *
     * @param string $property
     * @return Zend_Pdf_PHPArray
     */
    public function __get($property) {
        if ($property=='items') {
            return $this->_items;
        }
        throw new Exception('Undefined property: Zend_Pdf_Element_Array::$' . $property);
    }


    /**
     * Provides read-only access to $this->_items;
     *
     * @param unknown_type $offset
     * @param unknown_type $value
     */
    public function __set($property, $value) {
        if ($property=='items') {
            throw new Exception('Array container cannot be overwritten');
        }
        throw new Exception('Undefined property: Zend_Pdf_Element_Array::$' . $property);
    }

    /**
     * Return type of the element.
     *
     * @return integer
     */
    public function getType()
    {
        return Zend_Pdf_Element::TYPE_ARRAY;
    }


    /**
     * Return object as string
     *
     * @param Zend_Pdf_Factory $factory
     * @return string
     */
    public function toString($factory = null)
    {
        $outStr = '[';
        $lastNL = 0;

        foreach ($this->_items as $element) {
            if (strlen($outStr) - $lastNL > 128)  {
                $outStr .= "\n";
                $lastNL = strlen($outStr);
            }

            $outStr .= $element->toString($factory) . ' ';
        }
        $outStr .= ']';

        return $outStr;
    }
}

