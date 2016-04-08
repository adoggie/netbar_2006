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
 * @subpackage Storage
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */


/** Zend_Search_Lucene_Storage_Directory */
require_once 'Zend/Search/Lucene/Storage/Directory.php';

/** Zend_Search_Lucene_Storage_File_Filesystem */
require_once 'Zend/Search/Lucene/Storage/File/Filesystem.php';


/**
 * FileSystem implementation of Directory abstraction.
 *
 * @package    Zend_Search_Lucene
 * @subpackage Storage
 * @copyright  Copyright (c) 2005-2006 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://www.zend.com/license/framework/1_0.txt Zend Framework License version 1.0
 */
class Zend_Search_Lucene_Storage_Directory_Filesystem extends Zend_Search_Lucene_Storage_Directory
{
    /**
     * Filesystem path to the directory
     *
     * @var string
     */
    private $_dirPath = null;

    /**
     * Cache for Zend_Search_Lucene_Storage_File_Filesystem objects
     * Array: filename => Zend_Search_Lucene_Storage_File object
     *
     * @var array
     * @throws Zend_Search_Lucene_Exception
     */
    private $_fileHandlers;


    /**
     * Utility function to recursive directory creation
     *
     * @param string $dir
     * @param integer $mode
     * @param boolean $recursive
     * @return boolean
     */

    static public function mkdirs($dir, $mode = 0777, $recursive = true)
    {
        if (is_null($dir) || $dir === '') {
            return false;
        }
        if (is_dir($dir) || $dir === '/') {
            return true;
        }
        if (self::mkdirs(dirname($dir), $mode, $recursive)) {
            return mkdir($dir, $mode);
        }
        return false;
    }


    /**
     * Object constructor
     * Checks if $path is a directory or tries to create it.
     *
     * @param string $path
     * @throws Zend_Search_Lucene_Exception
     */
    public function __construct($path)
    {
        if (!is_dir($path)) {
            if (file_exists($path)) {
                throw new Zend_Search_Lucene_Exception('Path exists, but it\'s not a directory');
            } else {
                if (!self::mkdirs($path)) {
                    throw new Zend_Search_Lucene_Exception("Can't create directory '$path'.");
                }
            }
        }
        $this->_dirPath = $path;
        $this->_fileHandlers = array();
    }


    /**
     * Closes the store.
     *
     * @return void
     */
    public function close()
    {
        foreach ($this->_fileHandlers as $fileObject) {
            $fileObject->close();
        }

        unset($this->_fileHandlers);
    }


    /**
     * Returns an array of strings, one for each file in the directory.
     *
     * @return array
     */
    public function fileList()
    {
        $result = array();

        $dirContent = opendir( $this->_dirPath );
        while ($file = readdir($dirContent)) {
            if (($file == '..')||($file == '.'))   continue;

            $fullName = $this->_dirPath . '/' . $file;

            if( !is_dir($this->_dirPath . '/' . $file) ) {
                $result[] = $file;
            }
        }

        return $result;
    }

    /**
     * Creates a new, empty file in the directory with the given $filename.
     *
     * @param string $filename
     * @return Zend_Search_Lucene_Storage_File
     */
    public function createFile($filename)
    {
        if (isset($this->_fileHandlers[$filename])) {
            $this->_fileHandlers[$filename]->close();
        }
        unset($this->_fileHandlers[$filename]);
        $this->_fileHandlers[$filename] = new Zend_Search_Lucene_Storage_File_Filesystem($this->_dirPath . '/' . $filename, 'w+b');
        return $this->_fileHandlers[$filename];
    }


    /**
     * Removes an existing $filename in the directory.
     *
     * @param string $filename
     * @return void
     */
    public function deleteFile($filename)
    {
        if (isset($this->_fileHandlers[$filename])) {
            $this->_fileHandlers[$filename]->close();
        }
        unset($this->_fileHandlers[$filename]);
        unlink($this->_dirPath .'/'. $filename);
    }


    /**
     * Returns true if a file with the given $filename exists.
     *
     * @param string $filename
     * @return boolean
     */
    public function fileExists($filename)
    {
        return file_exists($this->_dirPath .'/'. $filename);
    }


    /**
     * Returns the length of a $filename in the directory.
     *
     * @param string $filename
     * @return integer
     */
    public function fileLength($filename)
    {
        if (isset( $this->_fileHandlers[$filename] )) {
            return $this->_fileHandlers[$filename]->size();
        }
        return filesize($this->_dirPath .'/'. $filename);
    }


    /**
     * Returns the UNIX timestamp $filename was last modified.
     *
     * @param string $filename
     * @return integer
     */
    public function fileModified($filename)
    {
        return filemtime($this->_dirPath .'/'. $filename);
    }


    /**
     * Renames an existing file in the directory.
     *
     * @param string $from
     * @param string $to
     * @return void
     */
    public function renameFile($from, $to)
    {
        if ($this->_fileHandlers[$from] !== null) {
            $this->_fileHandlers[$from]->close();
        }
        unset($this->_fileHandlers[$from]);

        if ($this->_fileHandlers[$to] !== null) {
            $this->_fileHandlers[$to]->close();
        }
        unset($this->_fileHandlers[$to]);

        if (file_exists($this->_dirPath . '/' . $to)) {
            unlink($this->_dirPath . '/' . $to);
        }

        return @rename($this->_dirPath . '/' . $from, $this->_dirPath . '/' . $to);
    }


    /**
     * Sets the modified time of $filename to now.
     *
     * @param string $filename
     * @return void
     */
    public function touchFile($filename)
    {
        return touch($this->_dirPath .'/'. $filename);
    }


    /**
     * Returns a Zend_Search_Lucene_Storage_File object for a given $filename in the directory.
     *
     * @param string $filename
     * @return Zend_Search_Lucene_Storage_File
     */
    public function getFileObject($filename)
    {
        if (isset( $this->_fileHandlers[$filename] )) {
            $this->_fileHandlers[$filename]->seek(0);
            return $this->_fileHandlers[$filename];
        }

        $this->_fileHandlers[$filename] = new Zend_Search_Lucene_Storage_File_Filesystem($this->_dirPath . '/' . $filename, 'rb');
        return $this->_fileHandlers[$filename];
    }
}


