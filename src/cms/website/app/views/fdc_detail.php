<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>
<script language="javascript">
function OnSave(){
	if( form1.fdc_name.value==""){
		alert("������ͻ�����!");
		return ;
	}
	if( form1.fdc_ip.value==""){
		alert("IP��ַ����Ϊ��!");
		return;
	}
	form1.submit();
}

</script>
<body>

<div align="center">�ͻ���Ϣ
</div>
<form name="form1" method="post" action="/fdc/save">
<table width="400" border="2" align="center" cellpadding="1" cellspacing="1">
  <tr>
    <td width="88">����</td>
    <td><input type="text" name="fdc_name" value="<?php echo $this->fdc_name;?>"></td>
    </tr>
  <tr>
    <td>���</td>
    <td><input type="text" name="fdc_id" value="<?php echo $this->fdc_id;?>"></td>
    </tr>
  <tr>
    <td>IP��ַ</td>
    <td><input type="text" name="fdc_ip" value="<?php echo $this->fdc_ip;?>"></td>
    </tr>
  <tr>
    <td>��</td>
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
    <td>��ϵ��</td>
    <td><input type="text" name="fdc_admin" value="<?php echo $this->fdc_admin;?>"></td>
    </tr>
  <tr>
    <td>�绰</td>
    <td><input type="text" name="fdc_tel" value="<?php echo $this->fdc_tel;?>"></td>
    </tr>
  <tr>
    <td>��ַ</td>
    <td><input type="text" name="fdc_addr" value="<?php echo $this->fdc_addr;?>"></td>
    </tr>
  <tr>
    <td colspan="2"><div align="center">
        <input type="button" name="Submit" value="����" onclick="OnSave()">
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

