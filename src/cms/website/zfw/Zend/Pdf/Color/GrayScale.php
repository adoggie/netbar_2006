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

/** Zend_Pdf_Exception */
require_once 'Zend/Pdf/Exception.php';

/** Zend_Pdf_Color */
require_once 'Zend/Pdf/Color.php';

/** Zend_Pdf_Element_Numeric */
require_once 'Zend/Pdf/Element/Numeric.php';

/**
 * GrayScale color implementation
 *
 * @package    Zend_Pdf
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Pdf_Color_GrayScale extends Zend_Pdf_Color
{
    /**
     * GrayLevel.
     * 0.0 (black) - 1.0 (white)
     *
     * @var Zend_Pdf_Element_Numeric
     */
    private $_grayLevel;

    /**
     * Object constructor
     *
     * @param float $grayLevel
     */
    public function __construct($grayLevel)
    {
        $this->_grayLevel = new Zend_Pdf_Element_Numeric($grayLevel);

        if ($this->_grayLevel->value < 0) {
            $this->_grayLevel->value = 0;
        }

        if ($this->_grayLevel->value > 1) {
            $this->_grayLevel->value = 1;
        }
    }

    /**
     * Instructions, which can be directly inserted into content stream
     * to switch color.
     * Color set instructions differ for stroking and nonstroking operations.
     *
     * @param boolean $stroking
     * @return string
     */
    public function instructions($stroking)
    {
        return $this->_grayLevel->toString() . ($stroking? " G\n" : " g\n");
    }
}


