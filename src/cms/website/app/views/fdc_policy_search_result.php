<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>
<script language="javascript">
function OnSelect( pid){
	url = '/fdc/PolicyAdd?pid='+pid;
	url+='&fid='+parent.opener.fid.value;
	parent.opener.location=url;

}
</script>
<body>

<?php 
	foreach( $this->result as $row){
		$p = ParsePolicy($row);

?>
<table width="100%" border="2" cellspacing="1" cellpadding="1">
  <tr>
    <td width="47" rowspan="2"><input type="button" name="Submit" value="ѡ��" onClick="OnSelect('<?php echo $p['ID'];?>')"></td>
    <td height="19">������</td>
    <td height="19"><?php echo $p['NAME'];?></td>
  </tr>
  <tr>
    <td width="139">ʱ�䷶Χ</td>
    <td width="511"><?php echo $p['TIME_RANGE'];?></td>
  </tr>
  <tr>
    <td width="47" rowspan="8">&nbsp;</td>
    <td>��ʱ��</td>
    <td>һ
        <input type="checkbox" name="weekday" disabled="true" value="1" 
	  <?php if($p['WEEKDAY'][0]){
	  			if($p['WEEKDAY'][0]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
			>
      ��
      <input type="checkbox" name="weekday2" value="2"  disabled="true"
	    <?php if($p['WEEKDAY'][1]){
	  			if($p['WEEKDAY'][1]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      ��
      <input type="checkbox" name="weekday2" value="3"  disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][2]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      ��
      <input type="checkbox" name="weekday2" value="4" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][3]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      ��
      <input type="checkbox" name="weekday2" value="5"  disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][4]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      ��
      <input type="checkbox" name="weekday2" value="6" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][5]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      ��
      <input type="checkbox" name="weekday2" value="7" disabled="true"
	   <?php if($p['WEEKDAY']){
	  			if($p['WEEKDAY'][6]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
  </tr>
  <tr>
    <td>��ʱ��</td>
    <td><?php echo $p['HOUR_RANGE'];?></td>
  </tr>
  <tr>
    <td>����ǽֽ</td>
    <td><?php echo $p['BG']['text'];?></td>
  </tr>
  <tr>
    <td>ϵͳ��½</td>
    <td><?php echo $p['LOGIN']['text'];?></td>
  </tr>
  <tr>
    <td>IE�׵�ַ</td>
    <td><?php echo $p['IE_ADDR']['text'];?></td>
  </tr>
  <tr>
    <td>MSN��½</td>
    <td><?php echo $p['MSN']['text'];?></td>
  </tr>
  <tr>
    <td>QQ��½</td>
    <td><?php echo $p['QQ']['text'];?></td>
  </tr>
  <tr>
    <td>IE������</td>
    <td><?php echo $p['IE_TBR']['text'];?></td>
  </tr>
</table>
<?php } ?>
</body>
</html>

