<?php
/**
 *  +----------------------------------------------------------------------+
 *  | Zend Framework                                                       |
 *  +----------------------------------------------------------------------+
 *  | Copyright (c) 2005-2006 Zend Technologies Inc. (http://www.zend.com) |
 *  +----------------------------------------------------------------------+
 *  | This source file is subject to version 1.0 of the Zend Framework     |
 *  | license, that is bundled with this package in the file LICENSE, and  |
 *  | is available through the world-wide-web at the following url:        |
 *  | http://www.zend.com/license/framework/1_0.txt.                       |
 *  | If you did not receive a copy of the Zend license and are unable to  |
 *  | obtain it through the world-wide-web, please send a note to          |
 *  | license@zend.com so we can mail you a copy immediately.              |
 *  +----------------------------------------------------------------------+
 *
 * @package    Zend_Db
 * @subpackage Profiler
 * @copyright  Copyright (c) 2005-2006 Zend Technologies Inc. (http://www.zend.com)
 * @license    Zend Framework License version 1.0
 */


/**
 * @package    Zend_Db
 * @subpackage Profiler
 * @copyright  Copyright (c) 2005-2006 Zend Technologies Inc. (http://www.zend.com)
 * @license    Zend Framework License version 1.0
 */
class Zend_Db_Profiler_Query
{

    /**
     * SQL query string or user comment, set by $query argument in constructor.
     *
     * @var string
     */
    protected $_query ='';

    /**
     * One of the Zend_Db_Profiler constants for query type, set by $queryType argument in constructor.
     *
     * @var integer
     */
    protected $_queryType = 0;

    /**
     * Unix timestamp with microseconds when instantiated.
     *
     * @var float
     */
    protected $_startedMicrotime = null;

    /**
     * Unix timestamp with microseconds when self::queryEnd() was called.
     *
     * @var null|integer
     */
    protected $_endedMicrotime = null;


    /**
     * Class constructor.  A query is about to be started, save the query text ($query) and its
     * type (one of the Zend_Db_Profiler::* constants).
     *
     * @param string $query
     * @param int $queryType
     * @return bool
     */
    public function __construct($query, $queryType)
    {
        $this->_query = $query;
        $this->_queryType = $queryType;
        $this->_startedMicrotime = microtime(true);
        return true;
    }


    /**
     * The query has ended.  Record the time so that the elapsed time can be determined later.
     *
     * @return bool
     */
    public function end()
    {
        $this->_endedMicrotime = microtime(true);
        return true;
    }


    /**
     * Has this query ended?
     *
     * @return bool
     */
    public function hasEnded()
    {
        return ($this->_endedMicrotime != null);
    }


    /**
     * Get the original SQL text of the query.
     *
     * @return string
     */
    public function getQuery()
    {
        return $this->_query;
    }


    /**
     * Get the type of this query (one of the Zend_Db_Profiler::* constants)
     *
     * @return int
     */
    public function getQueryType()
    {
        return $this->_queryType;
    }


    /**
     * Get the elapsed time (in seconds) that the query ran.  If the query has
     * not yet ended, return false.
     *
     * @return mixed
     */
    public function getElapsedSecs()
    {
        if (is_null($this->_endedMicrotime)) {
            return false;
        }

        return ($this->_endedMicrotime - $this->_startedMicrotime);
    }
}


