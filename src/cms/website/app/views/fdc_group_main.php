
<?php require_once 'fdc.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>

<body>
<table width="100">
  <tr>
    <td>&nbsp;</td>
    <td><a href="/fdc/GroupNew">����</a></td>
  </tr>
</table>
<table width="400" border="1" cellpadding="1" cellspacing="1">
  <tr>
    <td width="52">&nbsp;</td>
    <td width="154">����</td>
    <td width="176">˵��</td>
  </tr>
  <?php 
  	while( $row=mysql_fetch_array($this->result)){
  ?>
  <tr>
    <td>
	<?php if(!GetFdcCountByGroup($row['ID'])){?>
	<a href="/fdc/GroupDelete?id=<?php echo $row['ID'];?>">ɾ��</a>
	<?php } ?>
	</td>
    <td><a href="/fdc/GroupEdit?id=<?php echo $row['ID'];?>"><?php echo $row['NAME']?></a></td>
    <td><?php echo $row['DESCRIPTION']?></td>
  </tr>
  <?php }?>
</table>
<p>&nbsp; </p>
</body>
</html>

