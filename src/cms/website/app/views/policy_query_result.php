
<?php require 'config.php';
	require_once  'policy.php';
	require_once 'fdc.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>

<body>
<a href="/policy/QueryReflush" > 刷新</a>

<table width="100%" height="57" border="1" cellpadding="0" cellspacing="0">
  <tr>
    <td width="92" height="26">&nbsp;</td>
    <td width="142">名称</td>
    <td width="158">时间范围</td>
    <td width="140">周时间</td>
    <td width="98">日时间</td>
    <td width="89">关联数</td>
  </tr>
  <?php   foreach( $this->result as $row ){
  	$p = ParsePolicy($row);
  ?>
  <tr>
    <td height="29"><a href="/policy/delete?id=<?php echo $p['ID'];?>">删除</a></td>
    <td><a href="/policy/edit?id=<?php echo $p['ID'];?>"><?php echo $p['NAME'];?></a></td>
    <td><?php echo $p['TIME_RANGE'];?></td>
    <td><table width="0" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td>一</td>
    <td>二</td>
    <td>三</td>
    <td>四</td>
    <td>五</td>
    <td>六</td>
    <td>日</td>
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

