<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
function OnSave(){
	url ='/fdc/GroupSave?id='+form1.id.value;
	url+='&name='+form1.gname.value;
	url+='&desc='+form1.gdesc.value;
	window.location= url;
		
}
</script>
<body>
<form name="form1" method="post" action="">
<table width="294" border="1" cellspacing="1" cellpadding="1">
  <tr>
    <td width="72">&nbsp;</td>
    <td width="209">&nbsp;</td>
  </tr>
  <tr>
    <td>名称
      <input type="hidden" name="id" value="<?php echo $this->id;?>"></td>
    <td><input type="text" name="gname" value="<?php echo $this->name;?>"></td>
  </tr>
  <tr>
    <td>说明</td>
    <td><input type="text" name="gdesc" value="<?php echo $this->desc;?>"></td>
  </tr>
  <tr>
    <td colspan="2"><div align="center">
      <input type="button" name="Submit" value="保存" onClick="OnSave()">
    </div></td>
    </tr>
</table>

</form>
</body>
</html>

