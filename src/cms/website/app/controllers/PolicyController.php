<?php
require_once 'util.php';
require_once 'db_mysql.php';
require_once 'policy.php';
require_once 'fdc.php';

Zend::loadClass('Zend_Controller_Action');
Zend::loadClass('Zend_View');
Zend::loadClass('Zend_InputFilter');

class PolicyController extends Zend_Controller_Action
{
    public function indexAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('policy_bar.php');
    }

    public function MainAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('policy_main.php');
    }

    public function NewAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->stime=date('Y-m-d',time());
        $view->etime=date('Y-m-d',time());
        $view->shour='00';
        $view->ehour='24';
        echo $view->render('policy_detail.php');
    }

    public function AddPolicyMedia($pid,$mid_list){
    	$db = db_open();
        foreach( $mid_list as $mid){
        	if( trim($mid) ){
        		$sql = sprintf("insert into policy_media values( '%s','%s')",$pid,$mid);
        		mysql_query($sql,$db);
            }
        }
    }

    public function UpdatePolicyMedia($pid,$mid_list){
    	$db = db_open();
        $sql = sprintf("delete from policy_media where policy_id='%s'",$pid);
        mysql_query($sql,$db);
        foreach ( $mid_list as $mid){
           $sql = sprintf("insert into policy_media values( '%s','%s')",$pid,$mid);
           mysql_query($sql,$db);
        }

    }

	public function SaveAction(){
		require 'config.php';

		$post = new Zend_InputFilter($_GET);
      //   print_r($post);
		$id = $post->getRaw('id');
		$name = $post->getRaw('name');
		$stime = util_str2time($post->getRaw('stime'));
		$etime = util_str2time($post->getRaw('etime'));
      // print $post->getRaw('stime').'<br>'.$post->getRaw('etime');
      //  print $etime;
      //  return ;
      //  $etime+=60*60*24;
		$weekday=$post->getRaw('weekday');
		$shour=intval($post->getRaw('shour'));
		$ehour=intval($post->getRaw('ehour'));

        $ieaddr = $post->getRaw('ieaddr');
        $bg = $post->getRaw('bg');
        $login = $post->getRaw('login');
        $msn = $post->getRaw('msn');
        $qq = $post->getRaw('qq');

        $mid_ieaddr = $post->getRaw('mid_ieaddr');
        $mid_bg = $post->getRaw('mid_bg');
        $mid_login = $post->getRaw('mid_login');
        $mid_msn = $post->getRaw('mid_msn');
        $mid_qq = $post->getRaw('mid_qq');

        $ietbr = $post->getRaw('ietbr');
        $ietbr_media_list = $post->getRaw('ietbr_media_list');
        $back_url = $post->getRaw('back_url');
        $status=1;

        $db = db_open();

        if( !$id ){
        	$ieaddr =util_get_uuid();
            $bg =util_get_uuid();
            $ietbr=util_get_uuid();
            $login=util_get_uuid();
            $msn=util_get_uuid();
            $qq=util_get_uuid() ;
			$sql = sprintf("insert into policy values('%s','%s',%d,%d,%d,'%s',
            	%d,%d,'%s','%s','%s','%s','%s','%s')",
				util_get_uuid(),$name,$status,intval($stime),intval($etime),$weekday,
                $shour,$ehour,$ieaddr,$bg,$ietbr,$login,$msn,$qq);
            mysql_query($sql,$db);
            //--单条插入
            if( $mid_ieaddr ){
            	$this->AddPolicyMedia($ieaddr,array($mid_ieaddr));
            }
            if( $mid_bg ){
            	$this->AddPolicyMedia($bg,array($mid_bg));
            }
            if( $mid_login ){
            	$this->AddPolicyMedia($login,array($mid_login));
            }
            if( $mid_msn ){
            	$this->AddPolicyMedia($msn,array($mid_msn));
            }
            if( $mid_qq ){
            	$this->AddPolicyMedia($qq,array($mid_qq));
            }
            if( sizeof( split(',',$ietbr_media_list ))){
            	$this->AddPolicyMedia($ietbr,split(',',$ietbr_media_list ));
            }
        }else{
        	$sql=sprintf("select * from policy where id='%s'",$id);
            $r = mysql_query($sql,$db);
            $row = mysql_fetch_array($r);
        	$sql = sprintf("update policy set name='%s',_status=1,start_time=%d,
            			end_time=%d,weekday='%s',start_hour=%d,end_hour=%d
                        where id='%s'",$name,$stime,$etime,$weekday,$shour,$ehour,$id);
         //	print $sql;
            mysql_query($sql,$db);
            if( $mid_ieaddr ){
            	$this->UpdatePolicyMedia($row['FPC_IE_DEFAULT_ADDR'],array($mid_ieaddr));
            }
            if( $mid_bg ){
            	$this->UpdatePolicyMedia($row['FPC_BG'],array($mid_bg));
            }
            if( $mid_login ){
            	$this->UpdatePolicyMedia($row['FPC_AFTER_LOGIN'],array($mid_login));
            }
            if( $mid_msn ){
            	$this->UpdatePolicyMedia($row['FPC_MSN_LOGIN'],array($mid_msn));
            }
             if( $mid_qq ){
            	$this->UpdatePolicyMedia($row['FPC_QQ_LOGIN'],array($mid_qq));
            }
           // print $ietbr_media_list;
            if( sizeof( split(',',$ietbr_media_list ))){
            	$this->UpdatePolicyMedia($row['FPC_IE_TOOLBAR'],split(',',$ietbr_media_list ));
            }
        }

        if( $back_url){
        	$this->QueryReflushAction();
			//$this->_redirect($back_url);
        }else{

     	$view = new Zend_View();
        $view->setScriptPath('app/views');
           	$view->title='';
            $view->message='插入数据成功';

       	echo $view->render('message.php');
        }
	}



   public function GetPolicyMedia($pid){
       $db = db_open();
       $ret = array();
       $sql = sprintf("select b.* from policy_media a,media b where a.media_id=b.id and policy_id='%s'",$pid);
       $r = mysql_query($sql,$db);
     //  print $sql;
       while( $row=mysql_fetch_array($r)){
       		array_push($ret,$row);
       }
       return $ret;
   }

   public function GetMediaInfo($mid){
       $db = db_open();
       $sql = sprintf("select * from media where id='%s'",$mid);
       $r = mysql_query($sql,$db);
       $row=mysql_fetch_array($r);
       return $row;
   }

	public function EditAction(){
	 	$post = new Zend_InputFilter($_GET);
		$id  =$post->getRaw('id');
		$sql = sprintf("select * from policy where id='%s'",$id);
        $db = db_open();
        $r = mysql_query($sql,$db);
        $row = mysql_fetch_array($r);
   		$view = new Zend_View();
        $view->setScriptPath('app/views');

        $view->id = $row['ID'];
        $view->name=$row['NAME'];
        $view->status = $row['STATUS'];
        $view->stime=date('Y-m-d',$row['START_TIME']);
        $view->etime=date('Y-m-d',$row['END_TIME']);
        $view->weekday = $row['WEEKDAY'];
        $view->shour = $row['START_HOUR'];
        $view->ehour = $row['END_HOUR'];

        $view->ieaddr= $row['FPC_IE_DEFAULT_ADDR'];
        $ret =  $this->GetPolicyMedia($view->ieaddr);
        if( sizeof($ret) ){
        	$view->mid_ieaddr = $ret[0]['ID'];
        	$view->ieaddr_value= $ret[0]['NAME'].','.$ret[0]['URL'] ;
        }

        $view->bg= $row['FPC_BG'];
       // print $view->bg;
       // return;
        $ret =  $this->GetPolicyMedia($view->bg);
        if( sizeof($ret) ){
        	$view->mid_bg = $ret[0]['ID'];
        	$view->bg_value= $ret[0]['NAME'].','.$ret[0]['URL'] ;
        }
        $view->login= $row['FPC_AFTER_LOGIN'];
        $ret =  $this->GetPolicyMedia($view->login);
        if( sizeof($ret) ){
        	$view->mid_login = $ret[0]['ID'];
        	$view->login_value= $ret[0]['NAME'].','.$ret[0]['URL'] ;
        }
        $view->msn= $row['FPC_MSN_LOGIN'];
        $ret =  $this->GetPolicyMedia($view->msn);
        if( sizeof($ret) ){
        	$view->mid_msn = $ret[0]['ID'];
        	$view->msn_value=$ret[0]['NAME'].','.$ret[0]['URL'] ;
        }
        $view->qq= $row['FPC_QQ_LOGIN'];
        $ret =  $this->GetPolicyMedia($view->qq);
        if( sizeof($ret) ){
        	$view->mid_qq = $ret[0]['ID'];
        	$view->qq_value= $ret[0]['NAME'].','.$ret[0]['URL'] ;
        }

        $view->ietbr=$row['FPC_IE_TOOLBAR'];
        $view->ietbr_media_list= $this->GetPolicyMedia($view->ietbr);

        $view->back_url='/policy/QueryReflush';
      	echo $view->render('policy_detail.php');
	}
	public function upload_processAction(){
		require 'config.php';
		$userfile = $_FILES['uploadfile']['tmp_name'];
		$str = pathinfo($_FILES['uploadfile']['name']);
		$ext = $str['extension'];
		$save_name = util_get_uuid().'.'.$ext;
		move_uploaded_file($userfile,$save_name);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->temp_name=$save_name;
		$view->name=$_FILES['uploadfile']['name'];
      	echo $view->render('media_after_upload.php');
	}

	public function QueryAction(){
		$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->stime=date('Y-m-d',time());
        $view->etime=date('Y-m-d',time());
      	echo $view->render('policy_query.php');
	}



    public function media_queryAction(){
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        echo $view->render('policy_media_query.php');

    }

   	public function media_query_execAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_GET);
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
		$dbconn = db_open();
		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->db_result = $result;
      	echo $view->render('policy_media_query_result.php');	}


    public function QueryReflushAction(){
		$dbconn = db_open();
     //   $sql = $_SESSION['POLICY_QUERY_SQL'];
     //   print $sql;
     //   return;
     	$ret = PolicyQuery();
		//$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $ret[1];
      	echo $view->render('policy_query_result.php');
    }
	public function query_execAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_GET);
        $_SESSION['POLICY_QUERY_WHERE_NAME'] = $post->getRaw('name');
        $_SESSION['POLICY_QUERY_WHERE_WEEKDAY'] = $post->getRaw('weekday');
        $_SESSION['POLICY_QUERY_WHERE_STIME'] = $post->getRaw('stime');
        $_SESSION['POLICY_QUERY_WHERE_ETIME'] =  $post->getRaw('etime');
        $_SESSION['POLICY_QUERY_WHERE_SHOUR'] =  $post->getRaw('shour');
        $_SESSION['POLICY_QUERY_WHERE_EHOUR'] = $post->getRaw('ehour');
        $ret = PolicyQuery();
		$view = new Zend_View();
        $view->setScriptPath('app/views');
       // print_r($ret);
		$view->result = $ret[1];
       // $_SESSION['POLICY_QUERY_SQL']=$ret[0];
      	echo $view->render('policy_query_result.php');
	}

	public function DeleteAction(){
     	//1. 删除 policy_media
        //2.删除fdc_policy
        //3.删除policy

		$db = db_open();
		$post = new Zend_InputFilter($_GET);
		$id= $post->getRaw('id');

//		$sql = sprintf("delete from policy where id='%s'",mysql_escape_string($id));
        $sql = sprintf(" select * from policy where id='%s'",$id);
		$r =  mysql_query($sql,$db);
        $row = mysql_fetch_array($r);
        $sql = sprintf("delete from policy_media where policy_id='%s' or policy_id='%s'
        			or policy_id='%s' or policy_id='%s' or policy_id='%s'
                    or policy_id='%s'",$row['FPC_IE_DEFAULT_ADDR'],$row['FPC_BG'],
                    $row['FPC_IE_TOOLBAR'],$row['FPC_AFTER_LOGIN'],
                    $row['FPC_MSN_LOGIN'],$row['FPC_QQ_LOGIN']);
        mysql_query($sql,$db);
        $sql = sprintf("delete from fdc_policy where policy_id='%s'",$row['ID']);
        mysql_query($sql,$db);
        $sql = sprintf(" delete from policy where id='%s'",$row['ID']);
        mysql_query($sql,$db);

        $this->QueryReflushAction();
        /*
        //-- restore sense
        $sql = $_SESSION['POLICY_QUERY_SQL'];
        if( !$sql ){
            return ;
        }
 		$dbconn = db_open();
		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->db_result = $result;
        $_SESSION['POLICY_QUERY_SQL']=$sql;
      	echo $view->render('policy_query_result.php');
        */
	}


    public function FdcShowAction(){
    	$post = new Zend_InputFilter($_GET);
		$pid = $post->getRaw('pid');
        $sql = sprintf("select a.*,c.name as GNAME from fdc a,fdc_policy b,fdc_group c
        			where a.group_id=c.id and b.fdc_id=a.id and  b.policy_id='%s'",
        			mysql_escape_string($pid));
        $db = db_open();
        $r = mysql_query($sql);

    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->result=$r;
        $view->pid = $pid;
        echo $view->render('policy_fdc_show.php');
    }

    public function FdcSelectAction(){
    	$post = new Zend_InputFilter($_GET);
		$pid = $post->getRaw('pid');
    	$view = new Zend_View();
        $view->setScriptPath('app/views');
        $view->pid = $pid;
        echo $view->render('policy_fdc_select.php');
    }

    public function FdcSelectSearchAction(){
		require 'config.php';
		$post = new Zend_InputFilter($_GET);
		$name = $post->getRaw('fdc_name');
		$fdc_id = $post->getRaw('fdc_id');
		$ip = $post->getRaw('fdc_ip');
		$group =$post->getRaw('fdc_group');



		$sql = "select a.*,b.name as GNAME from fdc a,fdc_group b where a.group_id = b.id  ";
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

		$sql.=' order by a.name ';

		$dbconn = db_open();

		$result = mysql_query($sql,$dbconn);
		$view = new Zend_View();
        $view->setScriptPath('app/views');
		$view->result = $result;

      	echo $view->render('policy_fdc_select_search_result.php');
    }

    public function FdcAddAction(){
		$post = new Zend_InputFilter($_GET);
		$fid = $post->getRaw('fid');
        $pid = $post->getRaw('pid');
        $db = db_open();
        $sql=sprintf("insert into fdc_policy values('%s','%s') ",
        		mysql_escape_string($fid),mysql_escape_string($pid));

        mysql_query($sql,$db);
        $_GET['pid']=$pid;
        //-- to reflush
        $this->FdcShowAction();
    }

    public function FdcDeleteAction(){
    	$post = new Zend_InputFilter($_GET);
		$pid = $post->getRaw('pid');
        $fid = $post->getRaw('fid');
		$db = db_open();
        $sql = sprintf("delete from fdc_policy where fdc_id='%s' and policy_id='%s'",
        			mysql_escape_string($fid),mysql_escape_string($pid));
        mysql_query($sql,$db);
        $_GET['pid']=$pid;
        $this->FdcShowAction();
    }

}
