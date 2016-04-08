<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
function OnAppend(fid){
	url = '/policy/FdcAdd?pid='+parent.opener.pid.value;
	url+='&fid='+fid;
	parent.opener.location= url;
}
</script>
<body>
<table width="100%" border="2" cellspacing="1" cellpadding="1">
  <tr>
    <td width="53">&nbsp;</td>
    <td width="146">名称</td>
    <td width="116">编号</td>
    <td width="206"> ip 地址</td>
    <td width="156">组</td>
  </tr>
  <?php 
  	while( $row=mysql_fetch_array($this->result) ){
  ?>
  <tr>
    <td><input type="button" name="Submit" value="添加" 
	onClick="OnAppend('<?php echo $row['ID'];?>')"></td>
    <td><a href=/fdc/edit?id=<?php echo $row['ID'];?>><?php echo $row['NAME'];?></a></td>
    <td><?php echo $row['FDC_ID'];?></td>
    <td><?php echo $row['IP'];?></td>
    <td><?php echo $row['GNAME'];?></td>
  </tr>
  <?php } ?>
</table>
</body>
</html>

