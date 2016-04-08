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
 * @package    Zend_Mime
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/**
 * Support class for MultiPart Mime Messages
 *
 * @package    Zend_Mime
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Mime
{
    const TYPE_OCTETSTREAM = 'application/octet-stream';
    const TYPE_TEXT = 'text/plain';
    const TYPE_HTML = 'text/html';
    const ENCODING_7BIT = '7bit';
    const ENCODING_8BIT = '8bit';
    const ENCODING_QUOTEDPRINTABLE = 'quoted-printable';
    const ENCODING_BASE64 = 'base64';
    const DISPOSITION_ATTACHMENT = 'attachment';
    const DISPOSITION_INLINE = 'inline';
    const LINELENGTH = 74;
    const LINEEND = "\r\n";

    protected $_boundary;
    protected static $makeUnique = 0;

    // lookup-Tables for QuotedPrintable
    static public $qpKeys = array(
        "\x00","\x01","\x02","\x03","\x04","\x05","\x06","\x07",
        "\x08","\x09","\x0A","\x0B","\x0C","\x0D","\x0E","\x0F",
        "\x10","\x11","\x12","\x13","\x14","\x15","\x16","\x17",
        "\x18","\x19","\x1A","\x1B","\x1C","\x1D","\x1E","\x1F",
        "\x7F","\x80","\x81","\x82","\x83","\x84","\x85","\x86",
        "\x87","\x88","\x89","\x8A","\x8B","\x8C","\x8D","\x8E",
        "\x8F","\x90","\x91","\x92","\x93","\x94","\x95","\x96",
        "\x97","\x98","\x99","\x9A","\x9B","\x9C","\x9D","\x9E",
        "\x9F","\xA0","\xA1","\xA2","\xA3","\xA4","\xA5","\xA6",
        "\xA7","\xA8","\xA9","\xAA","\xAB","\xAC","\xAD","\xAE",
        "\xAF","\xB0","\xB1","\xB2","\xB3","\xB4","\xB5","\xB6",
        "\xB7","\xB8","\xB9","\xBA","\xBB","\xBC","\xBD","\xBE",
        "\xBF","\xC0","\xC1","\xC2","\xC3","\xC4","\xC5","\xC6",
        "\xC7","\xC8","\xC9","\xCA","\xCB","\xCC","\xCD","\xCE",
        "\xCF","\xD0","\xD1","\xD2","\xD3","\xD4","\xD5","\xD6",
        "\xD7","\xD8","\xD9","\xDA","\xDB","\xDC","\xDD","\xDE",
        "\xDF","\xE0","\xE1","\xE2","\xE3","\xE4","\xE5","\xE6",
        "\xE7","\xE8","\xE9","\xEA","\xEB","\xEC","\xED","\xEE",
        "\xEF","\xF0","\xF1","\xF2","\xF3","\xF4","\xF5","\xF6",
        "\xF7","\xF8","\xF9","\xFA","\xFB","\xFC","\xFD","\xFE",
        "\xFF"
        );

    static public $qpReplaceValues = array(
        "=00","=01","=02","=03","=04","=05","=06","=07",
        "=08","=09","=0A","=0B","=0C","=0D","=0E","=0F",
        "=10","=11","=12","=13","=14","=15","=16","=17",
        "=18","=19","=1A","=1B","=1C","=1D","=1E","=1F",
        "=7F","=80","=81","=82","=83","=84","=85","=86",
        "=87","=88","=89","=8A","=8B","=8C","=8D","=8E",
        "=8F","=90","=91","=92","=93","=94","=95","=96",
        "=97","=98","=99","=9A","=9B","=9C","=9D","=9E",
        "=9F","=A0","=A1","=A2","=A3","=A4","=A5","=A6",
        "=A7","=A8","=A9","=AA","=AB","=AC","=AD","=AE",
        "=AF","=B0","=B1","=B2","=B3","=B4","=B5","=B6",
        "=B7","=B8","=B9","=BA","=BB","=BC","=BD","=BE",
        "=BF","=C0","=C1","=C2","=C3","=C4","=C5","=C6",
        "=C7","=C8","=C9","=CA","=CB","=CC","=CD","=CE",
        "=CF","=D0","=D1","=D2","=D3","=D4","=D5","=D6",
        "=D7","=D8","=D9","=DA","=DB","=DC","=DD","=DE",
        "=DF","=E0","=E1","=E2","=E3","=E4","=E5","=E6",
        "=E7","=E8","=E9","=EA","=EB","=EC","=ED","=EE",
        "=EF","=F0","=F1","=F2","=F3","=F4","=F5","=F6",
        "=F7","=F8","=F9","=FA","=FB","=FC","=FD","=FE",
        "=FF"
        );

    static public $qpKeysString = 
         "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x7F\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

    /**
     * check if the given string is "printable" i.e. contains no
     * non-printable characters. if this returns false, encode the
     * string for secure delivery
     *
     * @param String $str
     * @return Boolean
     */
    static public function isPrintable($str)
    {
        return (strcspn($str, self::$qpKeysString) == strlen($str));
    }


    /**
     * Encode a given String with the QUOTED_PRINTABLE mechanism.
     *
     * @param String $str
     * @param int $lineLength
     * @param int $lineEnd
     * @return String
     */
    static public function encodeQuotedPrintable($str,
        $lineLength = self::LINELENGTH, $lineEnd = self::LINEEND)
    {
        // Now let us break the String into different lines and encode line by line:
        $out = '';
        $lines = explode($lineEnd, $str);

        foreach ($lines as $line) {
            /**
             * now replace all unprintable characters by their encodings
             * as defined in the lookup table:
             */
            $line = str_replace('=', '=3D', $line);
            $line = str_replace(self::$qpKeys, self::$qpReplaceValues, $line);

            // line break when line length>74
            preg_match_all( '/.{1,'.$lineLength.'}([^=]{0,2})?/', $line, $aMatch );

            /**
             * now check if there is a space at the end of the line and replace it
             * by =20 and implode with =<CRLF>
             */
            for ($i=0; $i<count($aMatch[0]); $i++) {
                if (substr($aMatch[0][$i], -1) == ' ') {
                    $line = substr($aMatch[0][$i], 0, -1) . '=20';
                } else {
                    $line = $aMatch[0][$i];
                }

                if ($i+1 < count($aMatch[0])) {
                    $line.='=';
                }

                // single dot on a line is handled by ZMailTransportSmtp::data().
                $out .= $line.$lineEnd;
            }
        }

        if ($out == '') {
            return '';
        }

        return substr($out, 0, -(strlen($lineEnd))); // cut LINEEND from last line.
    }


    /**
     * Encode a given string in base64 encoding and break lines
     * according to the maximum linelength.
     *
     * @param String $str
     * @return String
     */
    static public function encodeBase64($str)
    {
        return rtrim(chunk_split(base64_encode($str), self::LINELENGTH, self::LINEEND));
    }

    public function __construct($boundary=null)
    {
        // this string needs to be somewhat unique
        if ($boundary === null) {
            $this->_boundary = '=_' . md5(microtime(1).self::$makeUnique++);
        } else {
            $this->_boundary = $boundary;
        }
    }


    /**
     * Encode the given String with the given encoding.
     *
     * @param String $str
     * @param String $encoding
     * @return String
     */
    public function encode($str, $encoding)
    {
        switch ($encoding) {
            case self::ENCODING_BASE64:
                return self::encodeBase64($str);
                
            case self::ENCODING_QUOTEDPRINTABLE:
                return self::encodeQuotedPrintable($str);
                
            default:
                /**
                 * @todo 7Bit and 8Bit is currently handled the same way.
                 */
                return $str;
        }
    }


    public function boundary()
    {
        return $this->_boundary;
    }


    public function boundaryLine()
    {
        return self::LINEEND . '--' . $this->_boundary . self::LINEEND;
    }


    public function mimeEnd()
    {
        return self::LINEEND . '--' . $this->_boundary . '--' . self::LINEEND;
    }
}

