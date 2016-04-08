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
 * Base helper for form elements.  Extend this, don't use it on its own.
 * 
 * @package    Zend_View
 * @subpackage Helpers
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
abstract class Zend_View_Helper_FormElement {
    
    /**
     * Converts an associative array to a string of tag attributes.
     * 
     * @access public
     * 
     * @param array $attribs From this array, each key-value pair is 
     * converted to an attribute name and value.
     * 
     * @return string The XHTML for the attributes.
     */
    protected function _htmlAttribs($attribs)
    {
        $xhtml = '';
        foreach ((array) $attribs as $key => $val) {
            $key = htmlspecialchars($key);
            if (is_array($val)) {
                $val = implode(' ', $val);
            }
            $val = htmlspecialchars($val);
            $xhtml .= " $key=\"$val\"";
        }
        return $xhtml;
    }
    
    /**
     * Converts parameter arguments to an element info array.
     * 
     * E.g, formExample($name, $value, $attribs, $options, $listsep) is
     * the same thing as formExample(array('name' => ...)).
     * 
     * Note that you cannot pass a 'disable' param; you need to pass
     * it as an 'attribs' key.  A "'readonly' => 'readonly'" attribs
     * key-value pair has the same effect as "'disable' => true".
     * 
     * @access protected
     * 
     * @return array An element info array with keys for name, value,
     * attribs, options, listsep, and disable.
     */
    protected function _getInfo($name, $value = null, $attribs = null, 
        $options = null, $listsep = null)
    {
        // the baseline info.  note that $name serves a dual purpose;
        // if an array, it's an element info array that will override
        // these baseline values.  as such, ignore it for the 'name' 
        // if it's an array.
        $info = array(
            'name'    => is_array($name) ? '' : $name,
            'value'   => $value,
            'attribs' => $attribs,
            'options' => $options,
            'listsep' => $listsep,
            'disable' => false,
        );
        
        // override with named args
        if (is_array($name)) {
            // only set keys that are already in info
            foreach ($info as $key => $val) {
                if (isset($name[$key])) {
                    $info[$key] = $name[$key];
                }
            }
        }
        
        // force attribs to an array, per note from Orjan Persson.
        settype($info['attribs'], 'array');
        
        // disable if readonly
        if (isset($info['attribs']['readonly']) &&
            $info['attribs']['readonly'] == 'readonly') {
            // disable the element
            $info['disable'] = true;
            unset($info['attribs']['readonly']);
        }
        
        // normal disable, overrides readonly
        if (isset($info['attribs']['disable']) &&
            $info['attribs']['disable']) {
            // disable the element
            $info['disable'] = true;
            unset($info['attribs']['disable']);
        }
        
        // remove attribs that might overwrite the other keys.
        // we do this LAST because we needed the other attribs
        // values earlier.
        foreach ($info as $key => $val) {
            if (isset($info['attribs'][$key])) {
                unset($info['attribs'][$key]);
            }
        }
        
        // done!
        return $info;
    }
    
    /**
     * Creates a hidden element.
     * 
     * We have this as a common method because other elements often
     * need hidden elements for their operation.
     * 
     * @access protected
     * 
     * @param $name The element name.
     * 
     * @param $value The element value.
     * 
     * @param $attribs Attributes for the element.
     * 
     * @return string A hidden element.
     */
    protected function _hidden($name, $value = null, $attribs = null)
    {
        return '<input type="hidden"'
             . ' name="' . htmlspecialchars($name) . '"'
             . ' value="' . htmlspecialchars($value) . '"'
             . $this->_htmlAttribs($attribs) . ' />';
    }
}

