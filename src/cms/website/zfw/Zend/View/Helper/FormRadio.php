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
 * @package    Zend_View
 * @subpackage Helpers
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * Abstract class for extension
 */
require_once 'Zend/View/Helper/FormElement.php';


/**
 * Helper to generate a set of radio button elements
 * 
 * @package    Zend_View
 * @subpackage Helpers
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_View_Helper_FormRadio extends Zend_View_Helper_FormElement {
    
    /**
     * Generates a set of radio button elements.
     * 
     * @access public
     * 
     * @param string|array $name If a string, the element name.  If an
     * array, all other parameters are ignored, and the array elements
     * are extracted in place of added parameters.
     * 
     * @param mixed $value The radio value to mark as 'checked'.
     * 
     * @param array $options An array of key-value pairs where the array
     * key is the radio value, and the array value is the radio text.
     * 
     * @param array|string $attribs Attributes added to each radio.
     * 
     * @return string The radio buttons XHTML.
     */
    public function formRadio($name, $value = null, $attribs = null, 
        $options = null, $listsep = "<br />\n")
    {
        
        $info = $this->_getInfo($name, $value, $attribs, $options, $listsep);
        extract($info); // name, value, attribs, options, listsep, disable
        
        // retrieve attributes for labels (prefixed with 'label_')
        $label_attribs = array('style' => 'white-space: nowrap;');
        foreach ($attribs as $key => $val) {
            if (substr($key, 0, 6) == 'label_') {
                $tmp = substr($key, 6);
                $label_attribs[$tmp] = $val;
                unset($attribs[$key]);
            }
        }
        
        // the radio button values and labels
        settype($options, 'array');
        
        // default value if none are checked
        $xhtml = $this->_hidden($name, null);
        
        // build the element
        if ($disable) {
        
            // disabled.
            // show the radios as a plain list.
            $list = array();
            
            // create the list of radios.
            foreach ($options as $opt_value => $opt_label) {
                if ($opt_value == $value) {
                    // add a return value, and a checked text.
                    $opt = $this->_hidden($name, $opt_value) . '[x]';
                } else {
                    // not checked
                    $opt = '[&nbsp;]';
                }
                $list[] = $opt . '&nbsp;' . $opt_label;
            }
            
            $xhtml .= implode($listsep, $list);
            
        } else {
        
            // enabled.
            // the array of all radios.
            $list = array();
            
            // add radio buttons to the list.
            foreach ($options as $opt_value => $opt_label) {
            
                // begin the label wrapper
                $radio = '<label'
                       . $this->_htmlAttribs($label_attribs) . '>'
                       . '<input type="radio"'
                       . ' name="' . htmlspecialchars($name) . '"'
                       . ' value="' . htmlspecialchars($opt_value) . '"';
                
                // is it checked?
                if ($opt_value == $value) {
                    $radio .= ' checked="checked"';
                }
                
                // add attribs, end the radio, end the label
                $radio .= $this->_htmlAttribs($attribs) .
                          ' />' .
                          htmlspecialchars($opt_label) .
                          '</label>';
                
                // add to the array of radio buttons
                $list[] = $radio;
            }
            
            // done!
            $xhtml .= implode($listsep, $list);
        }
        
        return $xhtml;
    }
}

