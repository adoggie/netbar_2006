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
 * @package    Zend_Mail
 * @subpackage Transport
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */

/**
 * Zend_Mail_Transport_Exception
 */
require_once 'Zend/Mail/Transport/Exception.php';

/**
 * Zend_Mail_Transport_Interface
 */
require_once 'Zend/Mail/Transport/Interface.php';

/**
 * SMTP connection object
 * minimum implementation according to RFC2821:
 * EHLO, MAIL FROM, RCPT TO, DATA, RSET, NOOP, QUIT
 *
 * @package    Zend_Mail
 * @subpackage Transport
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Mail_Transport_Smtp implements Zend_Mail_Transport_Interface {

    const CONNECTION_TIMEOUT = 30;
    const COMMUNICATION_TIMEOUT = 2;
    const LINEEND = "\r\n";
    const DEBUG = false;

    protected $_host;
    protected $_port;
    protected $_myName;

    /**
     * Last Response from the SMTP server, 1 Array Element per line
     *
     * @var array of strings
     */
    public $lastResponse = array();

    /**
     * Stream to SMTP Server
     *
     * @var Stream
     */
    protected $_con = null;

    /**
     * Constructor.
     *
     * @param string $host
     * @param int $port
     * @param string $myName  (for use with HELO)
     */
    public function __construct($host, $port=25, $myName='127.0.0.1')
    {
        $this->_host = $host;
        $this->_port = $port;
        $this->_myName = $myName;
    }


    /**
     * Connect to the server with the parameters given
     * in the constructor and send "HELO". The connection
     * is immediately closed if an error occurs.
     *
     * @throws Zend_Mail_Transport_Exception
     */
    public function connect()
    {
        $errno  = null;
        $errstr = null;

        // open connection
        $fp = stream_socket_client('tcp://'.$this->_host.':'.$this->_port, $errno, $errstr, self::CONNECTION_TIMEOUT);

        if ($fp===false) {
            if ($errno==0) {
                $msg = 'Could not open socket';
            } else {
                $msg = $errstr;
            }
            throw new Zend_Mail_Transport_Exception($msg);
        }

        $this->_con = $fp;

        try {
            $res = stream_set_timeout($this->_con, self::COMMUNICATION_TIMEOUT );
            if ($res === false) {
                throw new Zend_Mail_Transport_Exception('Could not set Stream Timeout');
            }

            /**
             * Now the connection is open. Wait for the welcome message:
             *   welcome message has error code 220
             */
            $this->_expect(220);
            $this->helo($this->_myName);
        } catch (Zend_Mail_Transport_Exception $e) {
            fclose($fp);
            throw $e;
        }
    }


    /**
     * Sends EHLO along with the given machine name and
     * validates server response. If EHLO fails, HELO is
     * sent for compatibility with older MTAs.
     *
     * @param string $myname
     * @throws Zend_Mail_Transport_Exception
     */
    public function helo($myname)
    {
        $this->_send('EHLO '.$myname);

        try {
            $this->_expect(250);  // Hello OK is code 250
        } catch (Zend_Mail_Transport_Exception $e) {
            // propably wrong status code, RFC 2821 requires sending HELO in this case:
            $this->_send('HELO '.$myname);
            $this->_expect(250); // if we get an exception here, we give up...
        }
    }


    /**
     * sends a MAIL command for the senders address
     * and validates the response.
     *
     * @param string $from_email
     * @throws Zend_Mail_Transport_Exception
     */
    public function mail_from($from_email)
    {
        $this->_send('MAIL FROM: <'.$from_email.'>');
        $this->_expect(250);
    }


    /**
     * sends a RCPT command for a recipient address
     * and validates the response.
     *
     * @param string $to
     * @throws Zend_Mail_Transport_Exception
     */
    public function rcpt_to($to)
    {
        $this->_send('RCPT TO: <' .$to. '>');
        $this->_expect(250,251);
    }


    /**
     * sends the DATA command followed by the
     * email content (headers plus body) folowed
     * by a dot and validates the response of the
     * server.
     *
     * @param string $data
     * @throws Zend_Mail_Transport_Exception
     */
    public function data($data)
    {
        $this->_send('DATA');
        $this->_expect(354);
        foreach(explode(self::LINEEND ,$data) AS $line) {
            if($line=='.') $line='..'; // important. replace single dot on a line
            $this->_send($line);
        }
        $this->_send('.');
        $this->_expect(250);
    }


    /**
     * Sends the RSET command end validates answer
     * Not used by Zend_Mail, can be used to restore a clean
     * smtp communication state when a transaction has
     * been cancelled.
     *
     * @throws Zend_Mail_Transport_Exception
     */
    public function rset()
    {
        $this->_send('RSET');
        $this->_expect(250);
    }


    /**
     * Sends the NOOP command end validates answer
     * Not used by Zend_Mail, could be used to keep a connection
     * alive or check if it is still open.
     *
     * @throws Zend_Mail_Transport_Exception
     */
    public function noop()
    {
        $this->_send('NOOP');
        $this->_expect(250);
    }


    /**
     * Sends the VRFY command end validates answer
     * The calling method needs to evaluate $this->lastResponse
     * This function was implemented for completeness only.
     * It is not used by Zend_Mail.
     *
     * @param string $user User Name or eMail to verify
     * @throws Zend_Mail_Transport_Exception
     */
    public function vrfy($user)
    {
        $this->_send('VRFY ' . $user);
        $this->_expect(250,251,252);
    }


    /**
     * Sends the QUIT command and validates answer
     *
     * @throws Zend_Mail_Transport_Exception
     */
    public function quit()
    {
        $this->_send('QUIT');
        $this->_expect(221);
    }


    /**
     * close an existing connection.
     * sends QUIT and closes stream.
     *
     * @throws Zend_Mail_Transport_Exception
     */
    public function disconnect()
    {
        $this->quit();
        fclose($this->_con);
        $this->_con = NULL;
    }


    /**
     * Read the response from the stream and
     * check for expected return code. throws
     * a Zend_Mail_Transport_Exception if an unexpected code
     * is returned
     *
     * @param int $val1
     * @param int $val2
     * @param int $val3
     * @throws Zend_Mail_Transport_Exception
     */
    protected function _expect($val1, $val2=null, $val3=null)
    {
        /**
         * according to the new RFC2821, a multiline response can be sent
         * so we now check if it is the case here.
         * a multiline response is structured as follows:
         *   250-ok welcome 127.0.0.1
         *   250-PIPELINING
         *   250 HELP
         * normal answer would be:
         *
         * 250 ok.
         */
        $this->lastResponse = array();

        do {
            // blocking
            $res = $this->_receive();

            // we might need this later
            $this->lastResponse[] = $res;

            // returncode is always 3 digits at the beginning of the line
            $errorcode = substr($res,0,3);
            if ($errorcode === NULL || ( ($errorcode!=$val1) && ($errorcode!=$val2) && ($errorcode!=$val3)) ) {
                throw new Zend_Mail_Transport_Exception($res);
            }
        } while($res[3]=='-');
    }


    /**
     * Get a line from the stream. includes error checking and debugging
     *
     * @return string
     * @throws Zend_Mail_Transport_Exception
     */
    protected function _receive()
    {
        $res = fgets($this->_con, 1024);

        if ($res === false) {
            throw new Zend_Mail_Transport_Exception('Could not read from SMTP server');
        }

        if (self::DEBUG) {
            echo "R: $res<br>\n";
        }

        return $res;
    }


    /**
     * Send the given string followed by a LINEEND to the server
     *
     * @param string $str
     * @throws Zend_Mail_Transport_Exception
     */
    protected function _send($str)
    {
        $res = fwrite($this->_con, $str.self::LINEEND);
        if ($res === false) {
            throw new Zend_Mail_Transport_Exception('Could not write to SMTP server');
        }

        if (self::DEBUG) {
            echo "S: $str<br>\n";
        }
    }

    /**
     * send an email
     *
     * @param Zend_Mail $mail
     * @param string $body
     * @param string $headers
     */
    public function sendMail(Zend_Mail $mail, $body, $headers)
    {
        $wasConnected = ($this->_con!==null); // check if the connection is already there
        if(!$wasConnected) $this->connect();// if not, establish a connection
        else $this->rset(); // if already connected, reset connection
        try {
            $this->mail_from($mail->getFrom());
            foreach($mail->getRecipients() AS $recipient) {
                $this->rcpt_to($recipient);
            }
            $this->data($headers."\r\n".$body);
        }
        catch (Zend_Mail_Transport_Exception $e) {
            if(!$wasConnected) $this->disconnect(); // remove connection if we made one
            throw $e;
        }
        if(!$wasConnected) $this->disconnect(); // remove connection if we made one
    }
}

