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
 * @subpackage Adapter
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 *
 *
 * @todo XXX - Needs to be updated to use Zend_Db_Adapter_Abstract
 *
 */


/** Zend_Db_Adapter_Abstract */
require_once 'Zend/Db/Adapter/Abstract.php';

/** Zend_Db_Adapter_Oracle_Exception */
require_once 'Zend/Db/Adapter/Oracle/Exception.php';

/** Zend_Db_Statement_Oracle */
require_once 'Zend/Db/Statement/Oracle.php';


/**
 * @package    Zend_Db
 * @copyright  Copyright (c) 2005-2006 Zend Technologies Inc. (http://www.zend.com)
 * @license    Zend Framework License version 1.0
 */
class Zend_Db_Adapter_Oracle extends Zend_Db_Adapter_Abstract
{
    /**
     * User-provided configuration.
     *
     * Basic keys are:
     *
     * username => (string) Connect to the database as this username.
     * password => (string) Password associated with the username.
     * host     => (string) What host to connect to (default 127.0.0.1)
     * dbname   => (string) The name of the database to user
     *
     * Additional keys are processed as key-value pairs for a PDO DSN string.
     *
     * @var array
     */
    protected $_config = array(
        'database' => null,
        'username' => null,
        'password' => null,
    );

	protected $_execute_mode = OCI_COMMIT_ON_SUCCESS;

    /**
     * Constructor.
     *
     * $config is an array of key/value pairs containing configuration
     * options.  These options are common to most adapters:
     *
     * username => (string) Connect to the database as this username.
     * password => (string) Password associated with the username.
     * host     => (string) What host to connect to (default 127.0.0.1)
     * dbname   => (string) The name of the database to user
     *
     * @param array $config An array of configuration keys.
     */
    public function __construct($config)
    {
        // make sure the config array exists
        if (! is_array($config)) {
            throw new Zend_Db_Adapter_Exception('must pass a config array');
        }

        // we need at least a dbname
        if (! array_key_exists('password', $config) || ! array_key_exists('username', $config)) {
            throw new Zend_Db_Adapter_Exception('config array must have at least a username and a password');
        }

        // keep the config
        $this->_config = array_merge($this->_config, (array) $config);

        // create a profiler object
        $enabled = false;
        if (array_key_exists('profiler', $this->_config)) {
            $enabled = (bool) $this->_config['profiler'];
            unset($this->_config['profiler']);
        }

        $this->_profiler = new Zend_Db_Profiler($enabled);
    }
	
    /**
     * Creates a connection resource.
     *
     * @return void
     */
    protected function _connect()
    {
        /**
         * @todo should check resource here
         */
        if ($this->_connection) {
            return;
        }
		
		if (isset($this->_config['database'])) {
			$this->_connection = oci_connect($this->_config['username'], $this->_config['password'], $this->_config['database']);
		} else {
			$this->_connection = oci_connect($this->_config['username'], $this->_config['password']);
		}

        // check the connection
		if (!$this->_connection) {
            throw new Zend_Db_Adapter_Oracle_Exception(oci_error());
        }
    }


    /**
     * Returns an SQL statement for preparation.
     *
     * @param string $sql The SQL statement with placeholders.
     * @return Zend_Db_Statement_Oracle
     */
    public function prepare($sql)
    {
        $this->_connect();
        $stmt = new Zend_Db_Statement_Oracle($this, $sql);
        $stmt->setFetchMode($this->_fetchMode);
        return $stmt;
    }

    /**
     * Gets the last inserted ID.
     *
     * @return int
     */
    public function lastInsertId($name = null)
    {
		if (!$name) {
			throw new Zend_Db_Adapter_Exception("Sequence name must be specified");
		}
        $this->_connect();
		$data = $this->fetchCol("SELECT $name.currval FROM dual");
		return $data[0]; //we can't fail here, right? if the sequence doesn't exist we should fail earlier.
    }

    /**
     * Returns a list of the tables in the database.
     *
     * @return array
     */
    public function listTables()
    {
        $this->_connect();
		$data = $stmt->fetchCol('SELECT table_name FROM all_tables');
		return $data;
    }

    /**
     * Returns the column descriptions for a table.
     *
     * @return array
     */
    public function describeTable($table)
    {
        $sql = "DESCRIBE $table";
        $result = $this->fetchAll($sql);
        foreach ($result as $key => $val) {
            $descr[$val['Field']] = array(
                'name'    => $val['Field'],
                'notnull' => (bool) ($val['Null'] === ''), // not null is empty, null is yes
                'type'    => $val['Type'],
            );
        }
        return $descr;
    }


    /**
     * Leave autocommit mode and begin a transaction.
     *
     * @return void
     */
    protected function _beginTransaction()
    {
        $this->_setExecuteMode(OCI_DEFAULT);
    }

    /**
     * Commit a transaction and return to autocommit mode.
     *
     */
    protected function _commit()
    {
		if (!oci_commit($this->_connection)) {
			throw new Zend_Db_Adapter_Oracle_Exception(oci_error($this->_connection));
		}
        $this->_setExecuteMode(OCI_COMMIT_ON_SUCCESS);
    }

    /**
     * Roll back a transaction and return to autocommit mode.
     *
     * @return void
     */
    protected function _rollBack()
    {
		if (!oci_rollback($this->_connection)) {
			throw new Zend_Db_Adapter_Oracle_Exception(oci_error($this->_connection));
		}
        $this->_setExecuteMode(OCI_COMMIT_ON_SUCCESS);
    }


    /**
     * Set the fetch mode.
     *
     * @param int $mode A fetch mode.
     * @return void
     * @todo Support FETCH_CLASS and FETCH_INTO.
     */
    public function setFetchMode($mode)
    {
        switch ($mode) {
            case Zend_Db::FETCH_NUM:   // seq array
            case Zend_Db::FETCH_ASSOC: // assoc array
            case Zend_Db::FETCH_BOTH:  // seq+assoc array
            case Zend_Db::FETCH_OBJ:   // object
                $this->_fetchMode = $mode;
                break;
            default:
                throw new Zend_Db_Adapter_Exception('Invalid fetch mode specified');
                break;
        }
    }


    /**
     * Quote a raw string.
     *
     * @param string $value     Raw string
     * @return string           Quoted string
     */
    protected function _quote($value)
    {
        //@todo should we throw an exception here?
		return $value;
    }


    /**
     * Quotes an identifier.
     *
     * @param string $ident The identifier.
     * @return string The quoted identifier.
     */
    public function quoteIdentifier($ident)
    {
        //@todo should we throw an exception here?
		return $ident;
    }


    /**
     * Adds an adapter-specific LIMIT clause to the SELECT statement.
     *
     * @return string
     */
    public function limit($sql, $count, $offset)
    {
        /*
        Oracle doesn't have a LIMIT statement implementation, so we have to "emulate" it using rnum
        */
        $limit_sql = "SELECT
                            zsubselect2.*
                        FROM
                            (
                             SELECT
                                   rownum zrownum,
                                   zsubselect1.*
                               FROM
                                   (
                                    ".$sql."
                                   )
                                   zsubselect1
                            )
                            zsubselect2
                       WHERE
                            zrownum BETWEEN ".$offset." AND ".($offset+$count)."
                      ";
        return $limit_sql;
    }

	private function _setExecuteMode($mode) {
		switch($mode) {
			case OCI_COMMIT_ON_SUCCESS:
			case OCI_DEFAULT:
			case OCI_DESCRIBE_ONLY:
				$this->_execute_mode = $mode;
				break;
			default:
				throw new Zend_Db_Adapter_Exception('wrong execution mode specified');
				break;
		}
	}

	public function _getExecuteMode() {
		return $this->_execute_mode;
	}
}



