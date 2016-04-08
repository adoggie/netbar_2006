<?php 
	require 'config.php';
	require_once 'util.php';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">
var cnt=0;
function cast1(){
	alert(cnt++);
	cnt++;
}
function OnMediaSelect( which){

	w =window.open('/policy/media_query','media_query','menubar=no,status=no,toolbar=no');
	form1.cur_select_type.value = which;
}

function GetWeekDay(){
	weekday ="";
	
	if( form1.weekday[0].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[1].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[2].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[3].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[4].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[5].checked ) { weekday+='1';}else{weekday+='0';}
	if( form1.weekday[6].checked ) { weekday+='1';}else{weekday+='0';}
	
	return weekday;
}

function FormCheck(){
	if( form1.name.value==""){
		alert("请输入策略名称!");
		return false;
	}
	return true;
}

function OnSave(){
	var url;
	if( !FormCheck()){
		return ;
	}
	url = "/policy/save?id="+form1.id.value;
	url+="&name="+form1.name.value;
	url+="&stime="+form1.stime.value;
	url+="&etime="+form1.etime.value;
	url+="&weekday="+GetWeekDay();
	url+="&shour="+form1.shour.value;
	url+="&ehour="+form1.ehour.value;
	url+="&ieaddr="+form1.ieaddr.value;
	url+="&mid_ieaddr="+form1.mid_ieaddr.value;
	url+="&bg="+form1.bg.value;
	url+="&mid_bg="+form1.mid_bg.value;
	url+="&login="+form1.login.value;
	url+="&mid_login="+form1.mid_login.value;
	url+="&msn="+form1.msn.value;
	url+="&mid_msn="+form1.mid_msn.value;
	url+="&qq="+form1.qq.value;
	url+="&mid_qq="+form1.mid_qq.value;
	tbr_mid =""
	for( i=0;i<cell_ietbr.rows.length;i++){
		r = cell_ietbr.rows(i);
		tbr_mid+=r.childNodes(0).childNodes(0).value+",";
		
	}
	url+="&ietbr_media_list="+tbr_mid;
	url+="&back_url="+form1.back_url.value;
	//alert(url);
	window.location=url;
	//alert(url);
}
</script>
<body>
<form name="form1" method="post" action="/policy/save">
<table width="664" border="1" cellspacing="2" cellpadding="1">
  <tr>
    <td width="121">名称
      <input type="hidden" name="id" value="<?php echo $this->id; ?>">      </td>
    <td colspan="2"><input type="text" id="name" value="<?php echo $this->escape($this->name);?>">      </td>
    </tr>
  <tr>
    <td>有效期</td>
    <td colspan="2">      
	<input name="stime" type="text" size="10" maxlength="10" value="<?php echo $this->stime;?>">
      ~      
      <input name="etime" type="text" size="10" maxlength="10" value="<?php echo $this->etime;?>"></td>
    </tr>
  <tr>
    <td>周效期</td>
    <td colspan="2">
	<?php 
		$check = '';
		if( !$this->id){
			$check=' checked ';
		}
	?>
	一
      <input type="checkbox" name="weekday" value="1" 
	  <?php if($this->weekday){
	  			if($this->weekday[0]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
			>
      二
      <input type="checkbox" name="weekday" value="2" 
	    <?php if($this->weekday){
	  			if($this->weekday[1]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      三
      <input type="checkbox" name="weekday" value="3" 
	   <?php if($this->weekday){
	  			if($this->weekday[2]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      四
      <input type="checkbox" name="weekday" value="4" 
	   <?php if($this->weekday){
	  			if($this->weekday[3]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      五
      <input type="checkbox" name="weekday" value="5"  
	   <?php if($this->weekday){
	  			if($this->weekday[4]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      六
      <input type="checkbox" name="weekday" value="6" 
	   <?php if($this->weekday){
	  			if($this->weekday[5]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  >
      日
      <input type="checkbox" name="weekday" value="7"
	   <?php if($this->weekday){
	  			if($this->weekday[6]=='1') {
					echo ' checked ';
				}
			}else{
				echo ' checked ';
			}?>
	  ></td>
    </tr>
  <tr>
    <td>日效期</td>
    <td colspan="2"><input name="shour" type="text" value="<?php echo $this->shour;?>" size="4" maxlength="2" >
      ~
      <input name="ehour" type="text" value="<?php echo $this->ehour;?>" size="4" maxlength="2"></td>
    </tr>
  <tr>
    <td colspan="3"><input type="hidden" name="cur_select_type"></td>
    </tr>
  <tr>
    <td>IE浏览器首地址 
      <input type="hidden" name="ieaddr" value="<?php echo $this->ieaddr;?>">
      <input type="hidden" name="mid_ieaddr" value="<?php echo $this->mid_ieaddr;?>"></td>
    <td width="462" id="cell_ieaddr">
	<?php 
		echo $this->ieaddr_value;
	?>
	</td>
    <td width="59"><input type="button" name="Submit" value="选择" onClick="OnMediaSelect('ieaddr')">      </td>
  </tr>
  <tr>
    <td>桌面背景图
      <input type="hidden" name="bg" value="<?php echo $this->bg;?>">
      <input type="hidden" name="mid_bg" value="<?php echo $this->mid_bg;?>"></td>
    <td id="cell_bg"><?php echo $this->bg_value;?>       </td>
    <td><input type="button" name="Submit2" value="选择" onClick="OnMediaSelect('bg')"></td>
  </tr>
  <tr>
    <td height="28">系统登陆
      <input type="hidden" name="login" value="<?php echo $this->login;?>">
      <input type="hidden" name="mid_login" value="<?php echo $this->mid_login;?>"></td>
    <td height="28"  id="cell_login"><?php echo $this->login_value;?>     </td>
    <td height="28"><input type="button" name="Submit22" value="选择" onClick="OnMediaSelect('login')"></td>
  </tr>
  <tr>
    <td id='test' height="28">MSN登陆
      <input type="hidden" name="msn" value="<?php echo $this->msn;?>">
      <input type="hidden" name="mid_msn" value="<?php echo $this->mid_msn;?>"></td>
    <td height="28" id="cell_msn"><?php echo $this->msn_value;?>   </td>
    <td height="28"><input type="button" name="Submit23" value="选择" onClick="OnMediaSelect('msn')"></td>
  </tr>
  <tr>
    <td height="28">QQ登陆
      <input type="hidden" name="qq" value="<?php echo $this->qq;?>">
      <input type="hidden" name="mid_qq" value="<?php echo $this->mid_qq;?>"></td>
    <td height="28" id="cell_qq"><?php echo $this->qq_value;?>    </td>
    <td height="28"><input type="button" name="Submit24" value="选择" onClick="OnMediaSelect('qq')"></td>
  </tr>
  <tr>
    <td>IE浏览器工具条 
      <input type="hidden" name="ietbr" value="<?php echo $this->ietbr;?>"></td>
    <td   height="26" >
	<table id="cell_ietbr" width="447" border="1" cellspacing="0" cellpadding="0">
     <?php  
	 	if( $this->id) {
		foreach($this->ietbr_media_list as $item){
	 		echo "<tr>";
	 		echo sprintf("<td><input type='hidden' value='%s'></d>",$item['ID']);
			echo sprintf("<td><input type='button'  value='删除' onclick='cell_ietbr.deleteRow(this.parentNode.parentNode.rowIndex)'></d>",$item['ID']);
			echo sprintf("<td>%s,%s",$item['NAME'],$item['URL']);
			echo "</tr>";
	 	}
		}
	  ?>
    </table>	  </td>
    <td height="26" ><input type="button" name="Submit242" value="选择" onClick="OnMediaSelect('ietbr')"></td>
  </tr>
  <tr>
    <td>广告主机
      <input type="hidden" name="adve"></td>
    <td ></td>
    <td><input type="button" name="Submit2422" value="选择" onClick="OnMediaSelect('advertisment')"></td>
  </tr>
  <tr>
    <td colspan="3"><div align="center">
      <input type="button" name="Submit3" value="保存" onClick="OnSave()">
    </div></td>
    </tr>
</table>

<input type="hidden" name="back_url" value="<?php echo $this->back_url;?>">
</form>
</body>
</html>

