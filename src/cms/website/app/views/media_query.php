<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>
<body>

<?php
	require('config.php');
	//print_r($MEDIA_PLAYER_LIST);
	/*
	foreach($MEDIA_PLAYER_LIST as $k=>$v){
		print $k.'=>'.$v.'<br>;
	}*/
	
?>
<form name="form1" method="post" action="/media/query_exec">
<table width="442" border="1" cellpadding="1" cellspacing="1">
  <tr>
    <td width="84" height="30">����</td>
    <td width="194"><input type="text" name="name"></td>
    <td width="156">&nbsp;</td>
  </tr>
  <tr>
    <td>����</td>
    <td><select name="player">
	<option value="all" selected>��������</option>
	<?php 
		foreach( $MEDIA_PLAYER_LIST as $k=>$v){ ?>
			<option value="<?php echo $k;?>"><?php echo $v;?></option>
	<?php }?>
    </select></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td height="24">ʱ����</td>
    <td><input type="text" name="stime"></td>
    <td>YY-MM-DD</td>
  </tr>
  <tr>
    <td height="24">ʱ��ֹ</td>
    <td><input type="text" name="etime"></td>
    <td>YY-MM-DD</td>
  </tr>
  <tr>
    <td height="24">&nbsp;</td>
    <td><input type="submit" name="Submit" value="�ύ"></td>
    <td>&nbsp;</td>
  </tr>
</table>

</form>
</body>
</html>

