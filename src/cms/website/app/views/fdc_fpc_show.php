<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>

<body>
<p><a href="/fdc/QueryExec">返回</a>
</p>
<table width="400" border="2" cellspacing="1" cellpadding="1">
  <tr>
    <td>编号</td>
    <td>IP地址</td>
    <td>MAC地址</td>
    <td>客户名称</td>
    <td>&nbsp;</td>
  </tr>
  <?php 
  $cnt=0;
  while( $row=mysql_fetch_array($this->result)){
  	$cnt++;
  ?>
  <tr>
    <td><?php echo $cnt;?></td>
    <td><?php echo $row['IP'];?></td>
    <td><?php echo $row['MAC'];?></td>
    <td><?php echo $row['FDC_IP'];?></td>
    <td>&nbsp;</td>
  </tr>
  <?php } ?>
</table>
<p>&nbsp;</p>
</body>
</html>

