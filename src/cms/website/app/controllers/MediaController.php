<?php
//session_start();
require_once 'util.php';
require_once 'db_mysql.php';

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
Zend::loadClass('Zend_InputFilter');

class MediaController extends Zend_Controller_Action
{
    public function indexAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('media_file_bar.php');
    }

    public function MainAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('media_main.php');
    }

    public function NewAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('media_detail.php');
    }

	public function SaveAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_POST);
		$name = $post->getRaw('name');
		$url = $post->getRaw('url');
		$id = $post->getRaw('id');
		$player = $post->getRaw('player');
		$width=intval($post->getRaw('width'));
		$height=intval($post->getRaw('height'));
		$auto_name=$post->getRaw('temp_file');
		$type = $post->getRaw('rbType');
		if( $type == 'file'){
			;//move_uploaded_file(
		}
        $name=mysql_escape_string($name);
        $url = mysql_escape_string($url);
        if( !$id ){
			$sql = sprintf("insert into media values('%s','%s','%s','%s',%d,%d,'%s',%d)",
				util_get_uuid(),$url,$name,$player,intval($width),intval($height),$auto_name,time());
        }else{
        	$sql = sprintf("update media set url='%s',name='%s',player='%s',width=%d,height=%d,
            		auto_name='%s' where id='%s'",$url,$name,$player,intval($width),intval($height),
                    $auto_name,$id);
        }

        $dbconn = db_open();
        $result = mysql_query($sql,$dbconn) or die("Invalid query: " . mysql_error());
      	$view = new Zend_View();
        $view->setScriptPath('app/views');
		if( mysql_affected_rows( $dbconn ) !=-1){
           	$view->title='';
            $view->message='更新数据成功';
        }
      	echo $view->render('message.php');
	}

	public function UploadAction(){
   		$view = new Zend_View();
        $view->setScriptPath('app/views');
      	echo $view->render('media_upload.php');
	}
	public function EditAction(){
	 	$post = new Zend_InputFilter($_GET);
		$id  =$post->getRaw('id');
		$sql = sprintf("select * from media where id='%s'",$id);
        $db = db_open();
        $r = mysql_query($sql,$db);
        $row = mysql_fetch_array($r);

   		$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->id = $id;
        $view->name= $row['NAME'];
        $view->url = $row['URL'];
        $view->player=$row['PLAYER'];
        $view->height = intval($row['HEIGHT']);
        $view->width = intval($row['WIDTH']);
        $view->auto_name=$row['AUTO_NAME'];
      	echo $view->render('media_detail.php');
	}
	public function upload_processAction(){
		require 'config.php';
		$userfile = $_FILES['uploadfile']['tmp_name'];
		$str = pathinfo($_FILES['uploadfile']['name']);
		$ext = $str['extension'];
		$save_name = util_get_uuid().'.'.$ext;
		move_uploaded_file($userfile,$MEDIA_SAVE_PATH.'/'.$save_name);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->temp_name=$save_name;
		$view->name=$_FILES['uploadfile']['name'];
      	echo $view->render('media_after_upload.php');
	}

	public function QueryAction(){
		$view = new Zend_View();
        $view->setScriptPath('app/views');
      	echo $view->render('media_query.php');
	}

	public function QueryExec(){
		$sql = $_SESSION['MEDIA_QUERY_SQL'];
		$dbconn = db_open();
		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->db_result = $result;
      	echo $view->render('media_query_result.php');
	}

	public function query_execAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_POST);
		$name = $post->getRaw('name');
		$player = $post->getRaw('player');
		$stime = util_str2time($post->getRaw('stime'));
		$etime = util_str2time($post->getRaw('etime'));
		$sql = "select * from media ";
		$tail = '';
		if( $name ){
			if ($tail){
				$tail.=' and ';
			}
			$tail.=sprintf(" name like '%%%s%%' ",mysql_escape_string($name));
		}
		if( array_key_exists($player,$MEDIA_PLAYER_LIST) ){
			if ($tail){
				$tail.=' and ';
			}
			$tail.=sprintf(" player = '%s' ",$player);
		}

		if( $stime ){
			if ($tail){
				$tail.=' and ';
			}
			$tail.=sprintf(" ctime between %d and %d ",$stime,$etime);
		}
		if($tail){
			$sql.=' where '.$tail;
		}
		$sql.=' order by ctime desc';
		$_SESSION['MEDIA_QUERY_SQL']= $sql;
		$this->QueryExec();
	}

	public function DeleteAction(){
		$dbconn = db_open();
		$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');

		$sql = sprintf("delete from media where id='%s'",mysql_escape_string($id));
		mysql_query($sql,$dbconn);
		$this->QueryExec();
	}


}
