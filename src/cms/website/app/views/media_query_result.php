

<?php  
require_once 'util.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>

<body>
<table border="1" cellspacing="0" cellpadding="0">
  <tr>
    <td width="49">����</td>
    <td width="130">����</td>
    <td width="68">��Դ</td>
    <td width="68">��������</td>
    <td width="29">���</td>
    <td width="44">�߶�</td>
    <td width="103">�������ļ�����</td>
    <td width="64">����ʱ��</td>
  </tr>
  <?php 
		require 'config.php';
  		$count=1;
		while( $row = mysql_fetch_array( $this->db_result,MYSQL_ASSOC)){
  ?>
  <tr>
    <td>   
	<a href="/media/delete?id=<?php echo $row['ID'];?>">ɾ��</a>
	</td>
    <td><a href="/media/edit?id=<?php echo $row['ID'];?>" ><?php echo $row['NAME'];?></a></td>
    <td><?php echo $row['URL'];?></td>
    <td><?php echo $MEDIA_PLAYER_LIST[$row['PLAYER']];?></td>
    <td><?php echo $row['WIDTH'];?></td>
    <td><?php echo $row['HEIGHT'];?></td>
    <td><?php echo $row['AUTO_NAME'];?></td>
    <td><?php echo strftime('%Y-%m-%d %H:%M:%S' ,intval($row['CTIME']));?></td>
  </tr>
  <?php } 
  	mysql_free_result($this->db_result);
	?>
</table>
</body>
</html>

