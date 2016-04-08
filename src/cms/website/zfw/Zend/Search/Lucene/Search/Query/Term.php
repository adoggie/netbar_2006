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
 * @package    Zend_Search_Lucene
 * @subpackage Search
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/** Zend_Search_Lucene_Search_Query */
require_once 'Zend/Search/Lucene/Search/Query.php';

/** Zend_Search_Lucene_Search_Weight_Term */
require_once 'Zend/Search/Lucene/Search/Weight/Term.php';


/**
 * @package    Zend_Search_Lucene
 * @subpackage Search
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Search_Lucene_Search_Query_Term extends Zend_Search_Lucene_Search_Query
{
    /**
     * Term to find.
     *
     * @var Zend_Search_Lucene_Index_Term
     */
    private $_term;

    /**
     * Term sign.
     * If true then term is required
     * If false then term is prohibited.
     *
     * @var bool
     */
    private $_sign;

    /**
     * Documents vector.
     * Bitset or array of document IDs
     * (depending from Bitset extension availability).
     *
     * @var mixed
     */
    private $_docVector = null;

    /**
     * Term positions vector.
     * Array: docId => array( pos1, pos2, ... )
     *
     * @var array
     */
    private $_termPositions;


    /**
     * Zend_Search_Lucene_Search_Query_Term constructor
     *
     * @param Zend_Search_Lucene_Index_Term $term
     * @param boolean $sign
     */
    public function __construct( $term, $sign = true )
    {
        $this->_term = $term;
        $this->_sign = $sign;
    }


    /**
     * Constructs an appropriate Weight implementation for this query.
     *
     * @param Zend_Search_Lucene $reader
     * @return Zend_Search_Lucene_Search_Weight
     */
    protected function _createWeight($reader)
    {
        return new Zend_Search_Lucene_Search_Weight_Term($this->_term, $this, $reader);
    }

    /**
     * Score specified document
     *
     * @param integer $docId
     * @param Zend_Search_Lucene $reader
     * @return float
     */
    public function score( $docId, $reader )
    {
        if($this->_docVector===null) {
            if (extension_loaded('bitset')) {
                $this->_docVector = bitset_from_array( $reader->termDocs($this->_term) );
            } else {
                $this->_docVector = array_flip($reader->termDocs($this->_term));
            }

            $this->_termPositions = $reader->termPositions($this->_term);
            $this->_initWeight($reader);
        }

        $match = extension_loaded('bitset') ?  bitset_in($this->_docVector, $docId) :
                                               isset($this->_docVector[$docId]);
        if ($this->_sign && $match) {
            return $reader->getSimilarity()->tf(count($this->_termPositions[$docId]) ) *
                   $this->_weight->getValue() *
                   $reader->norm($docId, $this->_term->field);
        } else {
            return 0;
        }
    }
}


