<?php
require_once 'util.php';
require_once 'db_mysql.php';

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
Zend::loadClass('Zend_InputFilter');

class BasicController extends Zend_Controller_Action
{
    public function indexAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('basic_bar.php');
    }

    public function MainAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('basic_main.php');
    }

    public function NewAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->groups = $this->GetGroupInfo('');
        echo $view->render('fdc_detail.php');
    }



	public function SaveAction(){
		require 'config.php';

		$post = new Zend_InputFilter($_POST);
		$id = $post->getRaw('id');
		$name = $post->getRaw('fdc_name');
        $fdc_id =$post->getRaw('fdc_id');
        $ip = $post->getRaw('fdc_ip');
        $group=$post->getRaw('fdc_group');
        $admin=$post->getRaw('fdc_admin');
        $tel = $post->getRaw('fdc_tel');
        $addr= $post->getRaw('fdc_addr');

        $view = new Zend_View();
        $view->setScriptPath('app/views');
        if(!$group){
          	$view->message="无效的组编号";
            $view->back_url='';
            echo $view->render('message.php');
            return;
        }
        $name = mysql_escape_string($name);
        $fdc_id = mysql_escape_string($fdc_id);
        $ip = mysql_escape_string($ip);
        $group = mysql_escape_string($group);
        $admin=mysql_escape_string($admin);
        $tel=mysql_escape_string($tel);
        $addr=mysql_escape_string($addr);
        $db = db_open();
		if(!$id){	 //-- add record
            $sql = sprintf("insert into fdc values('%s','%s','%s','%s','%s','%s','%s','%s')",
            			util_get_uuid(),$fdc_id,$ip,$name,$group,$tel,$admin,$addr);
            mysql_query($sql,$db);
            $view->message='操作成功';
        	$view->back_url= '';
       		echo $view->render('message.php');
        }else{

            $sql = sprintf("update  fdc set fdc_id='%s',ip='%s',name='%s',group_id='%s',
            			tel='%s',admin='%s',addr='%s' where id='%s'",
            			$fdc_id,$ip,$name,$group,$tel,$admin,$addr,$id);
            mysql_query($sql,$db);
            $_SESSION['FDC_QUERY_ORDER']='name';
        	$this->QueryReflushAction();
        }
	}

   	public function GetGroupInfo($id){
    	$ret=array();
        $sql="select * from fdc_group " ;
        if($id!=''){
            $sql.=sprintf(" where id='%s' ",$id);
        }
        $sql.=' order by name';
        $db = db_open();
        $rs = mysql_query($sql,$db);
        while( $r= mysql_fetch_array($rs) ){
        	array_push($ret,$r);
        }
        return $ret;
    }

	public function EditAction(){
	 	$post = new Zend_InputFilter($_GET);
		$id  =$post->getRaw('id');
        $sql = sprintf("select * from fdc where id='%s'",$id);
        $db = db_open();
        $r = mysql_query($sql,$db);

        $view = new Zend_View();
        $view->setScriptPath('app/views');

        $row = mysql_fetch_array($r);
        $view->id = $id;
        $view->fdc_name=$row['NAME'];
        $view->fdc_id=$row['FDC_ID'];
        $view->fdc_ip=$row['IP'];
        $view->fdc_group=$row['GROUP_ID'];
        $view->fdc_admin=$row['ADMIN'];
        $view->fdc_tel=$row['TEL'];
        $view->fdc_addr=$row['ADDR'];
        $view->groups = $this->GetGroupInfo('');
        $view->back_url='/fdc/QueryReflush';
      	echo $view->render('fdc_detail.php');
	}

	public function QueryAction(){
		$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->name=$_SESSION['FDC_QUERY_NAME'];
        $view->fdc_id=$_SESSION['FDC_QUERY_FDC_ID'];
        $view->ip=$_SESSION['FDC_QUERY_IP'];
        $view->group=$_SESSION['FDC_QUERY_GROUP'];
        $db = db_open();
        $sql = 'select * from fdc_group order by name';
        $result = mysql_query($sql,$db);
        $view->result = $result;
      	echo $view->render('fdc_query.php');
	}

    public function QueryReflushAction(){
		$dbconn = db_open();
        $sql = $_SESSION['FDC_QUERY_SQL'];
        if( $_GET['order'] ){
            $_SESSION['FDC_QUERY_ORDER'] = $_GET['order'];
        }
        if( $_SESSION['FDC_QUERY_ORDER']){
        	$sql.=' order by '.$_SESSION['FDC_QUERY_ORDER'];
        }
		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $result;
      	echo $view->render('fdc_query_result.php');
    }

	public function QueryExecAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_POST);
		$name = $post->getRaw('fdc_name');
		$fdc_id = $post->getRaw('fdc_id');
		$ip = $post->getRaw('fdc_ip');
		$group =$post->getRaw('fdc_group');

		$_SESSION['FDC_QUERY_NAME'] = $name;
        $_SESSION['FDC_QUERY_FDC_ID'] = $fdc_id;
        $_SESSION['FDC_QUERY_IP']=$ip;
        $_SESSION['FDC_QUERY_GROUP'] =$group;

		$sql = "select a.* from fdc a,fdc_group b where a.group_id = b.id  ";
		$tail = '';
		if( $name ){
			$sql.=sprintf(" and a.name like '%%%s%%' ",mysql_escape_string($name));
		}
		if( $fdc_id ){
			$sql.=sprintf(" and a.fdc_id like '%%%s%%' ",mysql_escape_string($fdc_id));
		}

		if( $ip ){
			$sql.=sprintf(" and a.ip like '%%%s%%' ",mysql_escape_string($ip));
		}

        if( $group && $group !='all' ){
             $sql.=sprintf(" and  b.id='%s' ",$group);
        }
        $_SESSION['FDC_QUERY_SQL']=$sql;
		$sql.=' order by a.name ';

		$dbconn = db_open();

		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $result;

      	echo $view->render('fdc_query_result.php');
	}

	public function DeleteAction(){
		$db = db_open();
		$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');

        $sql = sprintf("delete from fdc where id='%s'",$id);
        mysql_query($sql,$db);

        $this->QueryReflushAction();
	}

    public function FpcShowAction(){
       	$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');
        $sql = sprintf("select a.*,b.name as fdc_name,b.ip as fdc_ip from fpc a,fdc b
        			where  a.fdc_id=b.id and a.fdc_id='%s'  order by ip",$id);
        $db = db_open();
        $r = mysql_query($sql,$db);
        $view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $r;
      	echo $view->render('fdc_fpc_show.php');
    }
}
