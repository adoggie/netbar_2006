<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
function OnSelect(id,name,url,player,width,height){

	//alert(parent.opener.form1.cur_select_type.value);
	//alert(parent.opener.test.outerText);
	if( parent.opener.form1.cur_select_type.value=='ieaddr'){
		parent.opener.cell_ieaddr.innerHTML=name+","+url+","+player;
		parent.opener.form1.mid_ieaddr.value=id;
	}
	if( parent.opener.form1.cur_select_type.value=='msn'){
		parent.opener.cell_msn.innerHTML = name+","+url+","+player;
		parent.opener.form1.mid_msn.value=id;
	}
	if( parent.opener.form1.cur_select_type.value=='bg'){
		parent.opener.cell_bg.innerHTML =name+","+url+","+player;
		parent.opener.form1.mid_bg.value=id;
	}
	if( parent.opener.form1.cur_select_type.value=='login'){
		parent.opener.cell_login.innerHTML = name+","+url+","+player;
		parent.opener.form1.mid_login.value=id;
	}	
	if( parent.opener.form1.cur_select_type.value=='qq'){
		parent.opener.cell_qq.innerHTML = name+","+url+","+player;
		parent.opener.form1.mid_qq.value=id;
	}	
	if( parent.opener.form1.cur_select_type.value=='ietbr'){
		var row = parent.opener.cell_ietbr.insertRow();
		var cell = row.insertCell();
		cell.innerHTML="<input type='hidden' value='"+id+"'>";
		cell = row.insertCell();
		cell.innerHTML="<input type='button'  value='删除' onclick='cell_ietbr.deleteRow(this.parentNode.parentNode.rowIndex)'>";
		//cell.innerHTML="<input type='button'  value='删除' onclick='alert(this.parentNode.parentNode.childNodes(0).childNodes(0).value)'>";
		cell = row.insertCell();
		cell.innerHTML= name+","+url+","+player;
		return;
	}	

	parent.close();
}
</script>
<body>
<table width="100%" border="1" cellpadding="0" cellspacing="0">
  <tr >
    <td width="95">&nbsp;</td>

    <td width="212">名称</td>
    <td width="141">资源</td>
    <td width="102">播放类型</td>
    <td width="62">宽度</td>
    <td width="49">高度</td>

    <td width="104">创建时间</td>
  </tr>
  <?php 
		require 'config.php';
  		$count=1;
		while( $row = mysql_fetch_array( $this->db_result,MYSQL_ASSOC)){
  ?>
  <tr >
    <td><input type="button" name="Submit" value="添加" 
		onClick="OnSelect('<?php echo $row['ID'];?>','<?php echo $row['NAME'];?>','<?php echo $row['URL'];?>','<?php echo $row['PLAYER'];?>',<?php echo $row['WIDTH'];?>,<?php echo $row['HEIGHT'];?>)"
	></td>

    <td><?php echo $row['NAME'];?> </td>
    <td><?php echo $row['URL'];?></td>
    <td><?php echo $MEDIA_PLAYER_LIST[$row['PLAYER']];?></td>
    <td><?php echo $row['WIDTH'];?></td>
    <td><?php echo $row['HEIGHT'];?></td>
  
    <td><?php echo strftime('%Y-%m-%d %H:%M:%S' ,intval($row['CTIME']));?></td>
  </tr>
  <?php } 
  	mysql_free_result($this->db_result);
	?>
</table>
</body>
</html>

