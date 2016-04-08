
<?php
	require_once 'db_mysql.php';

    function GetMediaInfoByPolicy($pid){
    	$db=db_open();
        $sql = sprintf("select b.* from policy_media a,media b where
        			a.media_id=b.id and a.policy_id='%s'",$pid);
        $r = mysql_query($sql,$db);
        $text='';
        while( $row = mysql_fetch_array($r)){
			$text.= $row['NAME'].','.$row['URL'];
            $text.='<br>';
        }
        return $text;
    }


    function ParsePolicy($row){
       		$policy=array();
            $policy['ID']=$row['ID'];
            $policy['NAME']=$row['NAME'];
            $policy['_STATUS']=$row['_STATUS'];
            $policy['TIME_RANGE']= date('Y-m-d',$row['START_TIME']).'=>'.date('Y-m-d',$row['END_TIME']);;
            $policy['WEEKDAY']=$row['WEEKDAY'];
            $policy['HOUR_RANGE']=$row['START_HOUR'].':00'.'-'.$row['END_HOUR'].':00';
            $policy['IE_ADDR']=array('id'=>$row['FPC_IE_DEFAULT_ADDR'],'text'=>GetMediaInfoByPolicy($row['FPC_IE_DEFAULT_ADDR']));
			$policy['BG']=array('id'=>$row['FPC_BG'],'text'=>GetMediaInfoByPolicy($row['FPC_BG']));
            $policy['IE_TBR']=array('id'=>$row['FPC_IE_TOOLBAR'],'text'=>GetMediaInfoByPolicy($row['FPC_IE_TOOLBAR']));
            $policy['LOGIN']=array('id'=>$row['FPC_AFTER_LOGIN'],'text'=>GetMediaInfoByPolicy($row['FPC_AFTER_LOGIN']));
            $policy['MSN']=array('id'=>$row['FPC_MSN_LOGIN'],'text'=>GetMediaInfoByPolicy($row['FPC_MSN_LOGIN']));
            $policy['QQ']=array('id'=>$row['FPC_QQ_LOGIN'],'text'=>GetMediaInfoByPolicy($row['FPC_QQ_LOGIN']));
            return $policy;
    }

 	function GetPolicyDetailByFdc($fdc){
    	$ret=array();
    	$db= db_open();
        $sql = sprintf("select b.* from fdc_policy a,policy b where a.policy_id=b.id
        		and a.fdc_id='%s' order by start_time ,name" ,$fdc);
        $r = mysql_query($sql);
        while( $row=mysql_fetch_array($r) ){
          	array_push($ret,ParsePolicy($row));
        }
        return $ret;
    }



    function GetPolicy($pid,$order){
    	$ret=array();
    	$db= db_open();
        $sql ="select * from policy";
        if($pid!=''){
        	$sql = sprintf("select * from policy  where id='%s'",$pid);
        }
        $sql.=' order by '.$order;
        $r = mysql_query($sql);
        while( $row=mysql_fetch_array($r) ){
        	array_push($ret,ParsePolicy($row));
        }
        return $ret;
    }

    function PolicyQuery(){
    	require 'config.php';
    	$name = $_SESSION['POLICY_QUERY_WHERE_NAME'];
        $weekday=$_SESSION['POLICY_QUERY_WHERE_WEEKDAY'];
        $stime=util_str2time($_SESSION['POLICY_QUERY_WHERE_STIME']);
        $etime =util_str2time($_SESSION['POLICY_QUERY_WHERE_ETIME']);
        $shour =intval($_SESSION['POLICY_QUERY_WHERE_SHOUR']);
        $ehour =intval($_SESSION['POLICY_QUERY_WHERE_EHOUR']);

		$sql = "select * from policy ";
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

		if( $stime || $etime ){
			if ($tail){
				$tail.=' and ';
			}
			$tail.=sprintf(" start_time <=%d and  end_time >=%d",$stime,$etime);
		}

        if( $shour || $ehour){
         	if( $tail ){
            	$tail.= ' and ';
            }
            $tail.=sprintf(" start_hour>=%d and end_hour <=%d",$shour,$ehour);
        }
		if($tail){
			$sql.=' where '.$tail;
		}
		$sql.=' order by end_time desc';

		$dbconn = db_open();
		$r = mysql_query($sql,$dbconn);
        $list=array();
        while( $row= mysql_fetch_array($r) ){
            $matched = 1;
        	for($i=0;$i<7;$i++){
            	if( $weekday[$i]=='0' && $row['WEEKDAY'][$i]=='1' ){
                 	$matched = 0;
                }
            }
            if( $matched ){
            	array_push($list,$row);
            }
        }
        return array($sql,$list);
    }

?>
