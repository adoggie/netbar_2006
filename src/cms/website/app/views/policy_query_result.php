
<?php require 'config.php';
	require_once  'policy.php';
	require_once 'fdc.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>

<body>
<a href="/policy/QueryReflush" > ˢ��</a>

<table width="100%" height="57" border="1" cellpadding="0" cellspacing="0">
  <tr>
    <td width="92" height="26">&nbsp;</td>
    <td width="142">����</td>
    <td width="158">ʱ�䷶Χ</td>
    <td width="140">��ʱ��</td>
    <td width="98">��ʱ��</td>
    <td width="89">������</td>
  </tr>
  <?php   foreach( $this->result as $row ){
  	$p = ParsePolicy($row);
  ?>
  <tr>
    <td height="29"><a href="/policy/delete?id=<?php echo $p['ID'];?>">ɾ��</a></td>
    <td><a href="/policy/edit?id=<?php echo $p['ID'];?>"><?php echo $p['NAME'];?></a></td>
    <td><?php echo $p['TIME_RANGE'];?></td>
    <td><table width="0" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td>һ</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
  </tr>
  <tr>
    <td><input type="checkbox" name="weekday" disabled="true" value="1" 
	  <?php if($p['WEEKDAY'][0]){
	  			if($p['WEEKDAY'][0]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
			></td>
    <td><input type="checkbox" name="weekday22" value="2"  disabled="true"
	    <?php if($p['WEEKDAY'][1]){
	  			if($p['WEEKDAY'][1]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    <td><input type="checkbox" name="weekday23" value="3"  disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][2]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    <td><input type="checkbox" name="weekday24" value="4" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][3]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    <td><input type="checkbox" name="weekday25" value="5"  disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][4]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    <td><input type="checkbox" name="weekday26" value="6" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][5]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    <td><input type="checkbox" name="weekday2" value="7" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][6]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
  </tr>
</table></td>
    <td><?php echo $p['HOUR_RANGE'];?></td>
    <td><a href="/policy/FdcShow?pid=<?echo $p['ID'];?>"> <?php echo GetPolicyAsscNum($p['ID']);?> </a></td>
  </tr>
  <?php }?>
</table>
</body>
</html>

