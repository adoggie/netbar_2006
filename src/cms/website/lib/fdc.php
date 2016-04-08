
<?php
	require_once 'db_mysql.php';

    function GetFpcCount($fdc){
       $db = db_open();
       $sql= sprintf("select count(*) as cnt from fpc where fdc_id='%s'",$fdc);
       $r = mysql_query($sql,$db);
       $r = mysql_fetch_array($r);
       return intval($r['CNT']);
    }

    function GetGroupInfo($id){
    	$ret=array();
        $sql="select * from fdc_group " ;
        if($id!=''){
            $sql.=sprintf(" where id='%s' ",$id);
        }
        $sql.=' order by name';
       // print $sql;
        $db = db_open();
        $rs = mysql_query($sql,$db);
        while( $r= mysql_fetch_array($rs) ){
        	array_push($ret,$r);
        }
        return $ret;
    }

    function GetPolicyCountByFdc($fdc){
    	$db = db_open();
        $sql = sprintf("select count(*) as cnt from fdc_policy where fdc_id='%s'",$fdc);
        $r = mysql_query($sql,$db);
        $row = mysql_fetch_array($r);

        return intval($row['cnt']);
    }

    function GetFdcCountByGroup($gid){
    	$db = db_open();
        $sql = sprintf("select count(*) as cnt from fdc where group_id='%s'",$gid);
        $r = mysql_query($sql,$db);
        $row = mysql_fetch_array($r);

        return intval($row['cnt']);

    }



?>
