<?php  
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
<table width="100%" border="2" cellspacing="1" cellpadding="1">
  <tr>
    <td width="39">&nbsp;</td>
    <td width="46"><a href="/fdc/QueryReflush?order=name">����</a></td>
    <td width="52"><a href="/fdc/QueryReflush?order=fdc_id">���</a></td>
    <td width="94"><a href="/fdc/QueryReflush?order=ip">ip��ַ</a></td>
    <td width="69">��</td>
    <td width="69">����Ա</td>
    <td width="97"><a href="/fdc/QueryReflush?order=tel">�绰</a></td>
    <td width="79">����</td>
    <td width="79">FPC����</td>
  </tr>
  <?php 
  	while( $row=mysql_fetch_array($this->result) ){
  ?>
  <tr>
    <td><a href=/fdc/delete?id=<?php echo $row['ID'];?>>ɾ��</a></td>
    <td><a href=/fdc/edit?id=<?php echo $row['ID'];?>><?php echo $row['NAME'];?></a></td>
    <td><?php echo $row['FDC_ID'];?></td>
    <td><?php echo $row['IP'];?></td>
    <td><?php 
	$ret = GetGroupInfo($row['GROUP_ID']);
	if(  sizeof($ret) ){
				echo $ret[0]['NAME'];
				}?></td>
    <td><?php echo $row['ADMIN'];?></td>
    <td><?php echo $row['TEL'];?></td>
    <td><a href="/fdc/PolicyShow?id=<?php echo $row['ID'];?>" >
	<?php echo GetPolicyCountByFdc( $row['ID']);?></a></td>
    <td>
	<a href="/fdc/FpcShow?id=<?php echo $row['ID'];?>" > <?php echo GetFpcCount($row['ID']);?> </td>
  </tr>
  <?php } ?>
</table>
</body>
</html>

