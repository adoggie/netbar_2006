
<?php 
	require_once 'fdc.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
function OnSearch(){
	url = "/policy/FdcSelectSearch";
	url+="?fdc_name="+form1.fdc_name.value;
	url+="&fdc_id="+form1.fdc_id.value;
	url+="&fdc_ip="+form1.fdc_ip.value;
	url+="&fdc_group="+form1.fdc_group.value;
 
 	document.all.FrameResult.src=url;
 
}
</script>
<body>
<form name="form1" method="post" action="/policy/fdcSelectSearch">
<table width="100%" border="2" align="center" cellpadding="1" cellspacing="1">
  <tr>
    <td width="67">名称</td>
    <td width="200"><input type="text" name="fdc_name" value="<?php echo $this->name;?>"></td>
  </tr>
  <tr>
    <td>编号</td>
    <td><input type="text" name="fdc_id" value="<?php echo $this->id;?>"></td>
  </tr>
  <tr>
    <td>IP地址</td>
    <td><input type="text" name="fdc_ip" value="<?php echo $this->ip;?>"></td>
  </tr>
  <tr>
    <td>组</td>
    <td><select name="fdc_group">
        <option value="all">所有组</option>
        <?php 
		$list = GetGroupInfo('');

	  foreach( $list as $row){
	  			$v = $row['ID'];
				$s = $row['NAME'];

				$c='';
				if( $v == $this->group){
					$c = ' selected ';
				}
				echo sprintf("<option value='%s' %s>%s</option>",$v,$c,$s);
			}
	  ?>
    </select></td>
  </tr>
  <tr>
    <td colspan="2">
      <div align="left">
        <input type="button" name="Submit" value="搜索" onClick="OnSearch()">
        </div></td></tr>
</table>
</form>

<iframe id='FrameResult'  width="100%" height="100%">

</iframe>
</body>
</html>

