<?php
    require_once 'db_mysql.php';

	function util_get_uuid(){
		return trim(com_create_guid(),'{}');
	}

	function util_str2time($date){
		$t=0;
       // if(!isset($data)){
        //	return 0;
        //}
		if (ereg("([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})", $date, $regs)) {
            $y = intval($regs[1]);
		   $m = intval($regs[2]);
		   $d = intval($regs[3] );

           if( $y >=2069){
           	 $y=2069;
           }
           if( $y<2000){
           		$y=2000;
           }

           $y=$y-2000;
           if( $d >31 ){
           	$d = 31;
           }
           if( $m >12){
           		$m = 12;
           }
         //  print $date.'=>'.$y.'-'.$m.'-'.$d ;
          	try{
		   		$t= mktime(0,0,0,$m,$d,$y);
           }catch(Exception $e){
           	$t=0;
           }
		}
		return $t;
	}

	function GetPolicyAsscNum($pid){
    	$db = db_open();
        $sql = sprintf("select count(*) as cnt from  fdc_policy where policy_id='%s'",$pid);
		$r = mysql_query($sql);
        $row = mysql_fetch_array($r,$db);
        return intval($row['cnt']);
    }

?>
