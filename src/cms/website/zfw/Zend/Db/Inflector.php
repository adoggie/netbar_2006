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
 * @package    Zend_Db
 * @subpackage Inflector
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */

/**
 * Class for name inflections.
 *
 * @todo Look up pluralization rules for English.  E.g.: 'y' =>
 * 'ies', etc. "Porter stemming algorithm". See if Richard Heyes will
 * license his stemmer to us under BSD.
 *
 * @package    Zend_Db
 * @copyright  Copyright (c) 2005-2006 Zend Technologies Inc. (http://www.zend.com)
 * @license    Zend Framework License version 1.0
 */
class Zend_Db_Inflector {

    /**
     * Convert underscore_words to camelCaps.
     */
    public function camelize($name)
    {
        // lowercase all, underscores to spaces, and prefix with underscore.
        // (the prefix is to keep the first letter from getting uppercased
        // in the next statement.)
        $name = '_' . str_replace('_', ' ', strtolower($name));

        // uppercase words, collapse spaces, and drop initial underscore
        return ltrim(str_replace(' ', '', ucwords($name)), '_');
    }


    /**
     * Convert camelCaps to underscore_words.
     */
    public function underscore($name)
    {
        return strtolower(preg_replace('/([a-z])([A-Z])/', "$1_$2", $name));
    }

    /**
     * Singularize a name.
     *
     * @param string $name Plural name.
     * @return string Singular form of the original plural name.
     */
    public function singular($name)
    {
        $len = strlen($name);
        if ($len > 0) {
            $last1 = strtolower($name[$len-1]);
            $last3 = strtolower(substr($name, -3));
            if (strtolower($last3) == 'ies') {
                // entities => entity
                $name = substr($name, 0, -3) . 'y';
            } elseif ($last1 == 's') {
                // things => thing
                $name = substr($name, 0, $len-1);
            }
        }
        return $name;
    }


    /**
     * Pluralize a name.
     *
     * @param string $name Singular name
     * @return string Plural form of the original singular name
     */
    public function plural($name)
    {
        $len = strlen($name);
        if ($len > 0) {
            $last = strtolower($name[$len-1]);
            if ($last == 'y') {
                // entity => entities
                $name = substr($name, 0, -1) . 'ies';
            } elseif ($last != 's') {
                // thing => things
                $name .= 's';
            }
        }
        return $name;
    }

}

