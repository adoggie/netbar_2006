<?php
require_once 'util.php';
require_once 'db_mysql.php';
require_once 'policy.php';

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
Zend::loadClass('Zend_InputFilter');

class FdcController extends Zend_Controller_Action
{
    public function indexAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('fdc_bar.php');
    }

    public function MainAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('fdc_main.php');
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

    //根据过滤规则，查询fdc列表
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

    //删除fdc
	public function DeleteAction(){
		$db = db_open();
		$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');

        $sql = sprintf("delete from fdc where id='%s'",$id);
        mysql_query($sql,$db);

        $this->QueryReflushAction();
	}

    //显示fdc的所有网吧客户机器
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
    //显示某一个fdc的策略列表
    public function PolicyShowAction(){
       	$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');

        $view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->id = $id;
      	echo $view->render('fdc_policy_show.php');
    }

    function PolicySelectAction(){
    	$post = new Zend_InputFilter($_GET);
		$fid= $post->getRaw('fid');

        $view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->fid = $fid;
      	echo $view->render('fdc_policy_select.php');
    }

    //弹出界面进行选择policy
    function PolicySearchAction(){
		$post = new Zend_InputFilter($_GET);

     	$ret = PolicyQuery($post);
        $view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $ret[1];
      	echo $view->render('fdc_policy_search_result.php');
    }
   	//选择策略并写入poilicy_media表
    //返回到fdc得策略显示界面
    function PolicyAddAction(){
    	$post = new Zend_InputFilter($_GET);
        $pid=$post->getRaw('pid');
        $fid =$post->getRaw('fid');

        $sql = sprintf("insert into fdc_policy values('%s','%s')",$fid,$pid) ;
        $db = db_open();
        mysql_query($sql,$db);
        $_GET['id']= $fid;
        $this->PolicyShowAction();
    }

    function PolicyDeleteAction(){
    	$post = new Zend_InputFilter($_GET);
        $pid=$post->getRaw('pid');
        $fid =$post->getRaw('fid');
        $sql = sprintf("delete  from fdc_policy where fdc_id='%s' and policy_id='%s'",$fid,$pid) ;
        $db = db_open();
        mysql_query($sql,$db);
        $_GET['id']= $fid;
        $this->PolicyShowAction();
    }

    public function GroupMainAction(){
        $view = new Zend_View();
        $sql = 'select * from fdc_group order by name';
        $db = db_open();
        $r = mysql_query($sql,$db);
        $view->setScriptPath('app/views');
        $view->result=$r;
      	echo $view->render('fdc_group_main.php');
    }

    public function GroupDeleteAction(){
       	$post = new Zend_InputFilter($_GET);
        $id=$post->getRaw('id');
        $db = db_open();
        /*
        $sql = sprintf("select count(*) as cnt from fdc where group_id='%s'",$id);
        $r = mysql_query($sql,$db);
        $r = mysql_fetch_array($r);
        if( intval($r['cnt']) ){
           	$view = new Zend_View();
        	$view->setScriptPath('app/views');
        	$view->message='组内存在客户，不能删除'
            $view->name=$row['NAME'];
            $view->desc=$row['DESCRIPTION'];
        }
      	echo $view->render('fdc_group_detail.php');
        } */
        $sql = sprintf("delete from fdc_group where id='%s'",$id);

        mysql_query($sql,$db);
        $this->GroupMainAction();
    }

    public function GroupNewAction(){
        $view = new Zend_View();
        $view->setScriptPath('app/views');
      	echo $view->render('fdc_group_detail.php');
    }

    public function GroupEditAction(){
		$post = new Zend_InputFilter($_GET);
        $id=$post->getRaw('id');
        $sql = sprintf("select * from fdc_group where id='%s' ",$id);
        $db = db_open();
        $r = mysql_query($sql,$db);
        $row=mysql_fetch_array($r);
        $view = new Zend_View();
        if($row){
        	$view->setScriptPath('app/views');
        	$view->id=$row['ID'];
            $view->name=$row['NAME'];
            $view->desc=$row['DESCRIPTION'];
        }
      	echo $view->render('fdc_group_detail.php');

    }

    public function GroupSaveAction(){
      	$post = new Zend_InputFilter($_GET);
        $id=$post->getRaw('id');
        $name=$post->getRaw('name');
        $desc=$post->getRaw('desc');
        $name = mysql_escape_string($name);
        $desc=mysql_escape_string($desc);
        $sql='';
        if( !$id){
        	$sql=sprintf("insert into fdc_group values('%s','%s','%s')",util_get_uuid(),$name,$desc);
        }else{
        	$sql=sprintf("update fdc_group set name='%s',description='%s' where id='%s'",$name,$desc,$id);
        }
      //  print $sql;
        $db = db_open();
        mysql_query($sql,$db);
        $this->GroupMainAction();


    }

}
