<?php

class mysql {
    var $debug;
    var $host;
    var $name;
    var $user;
    var $pass;
    var $linkid;
    var $queryid;
    var $affected_rows;
    var $result;
    var $sql;
    var $errno;
    var $error;
    var $sqls = array();

    function mysql($host = '', $name = '', $user = '', $pass = '', $charset = 'UTF8', $debug = false) {
        if (!extension_loaded('mysql')) {
            if (strtoupper(substr(PHP_OS, 0, 3) == 'WIN')) {
                dl('php_mysql.dll');
            } else {
                dl('mysql.so');
            }
        }
        $this->debug = $debug;
        if ($host != '') {
            if (is_resource($this->connect($host, $user, $pass))) {
                if (mysql_get_server_info() >= "4.1") {
                    mysql_query("set names $charset", $this->linkid);
                }
                if ($name != '') {
                    $this->select_db($name);
                }
            }
        }
        register_shutdown_function(array(&$this, "shutdown"));
    }

    function connect($host, $user, $pass) {
        $this->host = $host;
        $this->user = $user;
        $this->pass = $pass;
        if ($this->debug) {
            $this->linkid = mysql_connect($this->host, $this->user, $this->pass);
        }
        else {
            $this->linkid = @mysql_connect($this->host, $this->user, $this->pass);
        }
        $this->errno = mysql_errno();
        $this->error = mysql_error();
        return $this->linkid;
    }

    function select_db($name) {
        $this->name = $name;
        if (is_resource($this->linkid)) {
            if ($this->debug) {
                if (!mysql_select_db($this->name, $this->linkid)) {
                    $this->errno = mysql_errno($this->linkid);
                    $this->error = mysql_error($this->linkid);
                }
            }
            else {
                if (!@mysql_select_db($this->name, $this->linkid)) {
                    $this->errno = mysql_errno($this->linkid);
                    $this->error = mysql_error($this->linkid);
                }
            }
        }
    }

    function query($sql = '', $type = 'assoc') {
        if (is_array($sql)) {
            $err = false;
            foreach($sql as $s) {
                if ($this->debug) {
                    if (!mysql_query($s, $this->linkid)) {
                        $this->errno = mysql_errno($this->linkid);
                        $this->error = mysql_error($this->linkid);
                        $err = true;
                    }
                }
                else {
                    if (!@mysql_query($s, $this->linkid)) {
                        $this->errno = mysql_errno($this->linkid);
                        $this->error = mysql_error($this->linkid);
                        $err = true;
                    }
                }
                if (preg_match("/^\s*(delete|insert|replace|update)/i", $s)) {
                    $this->affected_rows = mysql_affected_rows($this->linkid);
                }
            }
            return !$err;
        }
        if ($sql != '') {
            $this->sql = $sql;
        }
        if ($this->debug) {
            $this->queryid = mysql_query($this->sql, $this->linkid);
        }
        else {
            $this->queryid = @mysql_query($this->sql, $this->linkid);
        }
        if (preg_match("/^\s*(delete|insert|replace|update)/i", $this->sql)) {
            $this->affected_rows = mysql_affected_rows($this->linkid);
        }
        if (is_resource($this->queryid)) {
            if (mysql_num_rows($this->queryid) == 0) {
                $this->result = 0;
            }
            else if ((mysql_num_rows($this->queryid) == 1) and
                    preg_match("/limit\s+1\s*$|limit\s+1\s*[^,]+/i", $this->sql)) {
                $this->result = call_user_func("mysql_fetch_" . $type, $this->queryid);
            }
            else {
                $this->result = array();
                while ($row = call_user_func("mysql_fetch_" . $type, $this->queryid)) {
                    array_push($this->result, $row);
                }
            }
            return $this->result;
        }
        else if ($this->queryid === false) {
            $this->errno = mysql_errno($this->linkid);
            $this->error = mysql_error($this->linkid);
        }
        return $this->queryid;
    }

    function explain($sql = '') {
        if ($sql != '') {
            $this->sql = $sql;
        }
        if ($this->debug) {
            $this->queryid = mysql_query("EXPLAIN " . $this->sql, $this->linkid);
        }
        else {
            $this->queryid = @mysql_query("EXPLAIN " . $this->sql, $this->linkid);
        }
        if (is_resource($this->queryid)) {
            $this->result = array();
            while ($row = mysql_fetch_array($this->queryid)) {
                array_push($this->result, $row);
            }
            return $this->result;
        }
        else {
            $this->errno = mysql_errno($this->linkid);
            $this->error = mysql_error($this->linkid);
            return false;
        }
    }

    function last_insert_id() {
        if ($this->debug) {
            $result = mysql_query("select LAST_INSERT_ID() as `last_insert_id`", $this->linkid);
        }
        else {
            $result = @mysql_query("select LAST_INSERT_ID() as `last_insert_id`", $this->linkid);
        }
        if (is_resource($result)) {
            $row =  mysql_fetch_object($result);
            return $row->last_insert_id;
        }
        else {
            $this->errno = mysql_errno($this->linkid);
            $this->error = mysql_error($this->linkid);
            return false;
        }
    }

    function affected_rows() {
        return $this->affected_rows;
    }

    function register_shutdown_query($sql) {
        array_push($this->sqls, $sql);
    }

    function shutdown() {
        if (is_resource($this->linkid)) {
            foreach($this->sqls as $sql) {
                if ($this->debug) {
                    mysql_query($sql, $this->linkid);
                }
                else {
                    @mysql_query($sql, $this->linkid);
                }
            }
        }
    }

    function close() {
        if ($this->debug) {
            mysql_close($this->linkid);
        }
        else {
            @mysql_close($this->linkid);
        }
    }
    
    function escape_string($string) {
        if (version_compare(phpversion(), "4.3.0") == "-1") {
            return mysql_escape_string($string);
        }
        else if (is_resource($this->linkid)) {
            return mysql_real_escape_string($string, $this->linkid);
        }
        else {
            return false;
        }
    }
}
?>
