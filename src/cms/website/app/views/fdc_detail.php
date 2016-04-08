<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
function OnSave(){
	if( form1.fdc_name.value==""){
		alert("请输入客户名称!");
		return ;
	}
	if( form1.fdc_ip.value==""){
		alert("IP地址不能为空!");
		return;
	}
	form1.submit();
}

</script>
<body>

<div align="center">客户信息
</div>
<form name="form1" method="post" action="/fdc/save">
<table width="400" border="2" align="center" cellpadding="1" cellspacing="1">
  <tr>
    <td width="88">名称</td>
    <td><input type="text" name="fdc_name" value="<?php echo $this->fdc_name;?>"></td>
    </tr>
  <tr>
    <td>编号</td>
    <td><input type="text" name="fdc_id" value="<?php echo $this->fdc_id;?>"></td>
    </tr>
  <tr>
    <td>IP地址</td>
    <td><input type="text" name="fdc_ip" value="<?php echo $this->fdc_ip;?>"></td>
    </tr>
  <tr>
    <td>组</td>
    <td><select name="fdc_group">
	<?php 
		foreach( $this->groups as $item){
			$c='';
			if( $this->fdc_group==$item['ID'] ){
				$c=' selected ';
			}
			echo sprintf("<option value='%s' %s>%s</option>",$item['ID'],$c,$item['NAME']);
		}
	?>
    </select></td>
    </tr>
  <tr>
    <td>联系人</td>
    <td><input type="text" name="fdc_admin" value="<?php echo $this->fdc_admin;?>"></td>
    </tr>
  <tr>
    <td>电话</td>
    <td><input type="text" name="fdc_tel" value="<?php echo $this->fdc_tel;?>"></td>
    </tr>
  <tr>
    <td>地址</td>
    <td><input type="text" name="fdc_addr" value="<?php echo $this->fdc_addr;?>"></td>
    </tr>
  <tr>
    <td colspan="2"><div align="center">
        <input type="button" name="Submit" value="保存" onclick="OnSave()">
    </div></td>
    </tr>
</table>

<input type="hidden" name="id" value="<?php echo $this->id;?>">
<input type="hidden" name="back_url" value="<?php echo $this->back_url;?>">
<input type="hidden" name="hiddenField3">
<input type="hidden" name="hiddenField4">
<input type="hidden" name="hiddenField5">
</form>
</body>
</html>

