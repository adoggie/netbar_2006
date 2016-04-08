
<?php 
	function db_open(){
		$dbconn = @mysql_connect('127.0.0.1', 'root','') ;
		mysql_select_db('mpms',$dbconn);
		return $dbconn;
	}
	
?>
