<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>

<body>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="10%"><input type="button" name="Submit4" value="ˢ��" onClick="window.location='/policy/fdcshow?pid=<?php echo $this->pid;?>'"></td>
    <td width="10%"><input type="hidden" id="pid" value="<?php echo $this->pid;?>"></td>
    <td width="80%">&nbsp; </td>
  </tr>
  <tr>
    <td><input type="button" name="Submit2" value="����" 
	onClick="window.open('/policy/FdcSelect?pid=<?php echo $this->pid;?>','PolicyFdcSelect','height=500,width=550,menubar=no,status=no,toolbar=no,resizable=yes,scrollbars =yes');">
	</td>
    <td><input type="button" name="Submit3" value="����"></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
</table>
<table width="100%" border="1" cellspacing="0" cellpadding="1">
  <tr>
    <td>&nbsp;</td>
    <td>����</td>
    <td>���</td>
    <td>ip��ַ</td>
    <td>������</td>
  </tr>

  	<?php  while($row=mysql_fetch_array($this->result)){
  ?>
  <tr>
    <td width="10%"><a href="/policy/FdcDelete?fid=<?php echo $row['ID'];?>&pid=<?php echo $this->pid;?>">ɾ��</a></td>
    <td width="25%"><?php echo $row['NAME'];?></td>
    <td width="24%"><?php echo $row['FDC_ID'];?></td>
    <td width="20%"><?php echo $row['IP'];?></td>
    <td width="21%"><?php echo $row['GNAME'];?></td>
  </tr>
 <?php } ?>
</table>
<p>&nbsp;</p>
</body>
</html>

