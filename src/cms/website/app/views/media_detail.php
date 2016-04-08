<?php 
require 'config.php'; 
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
 <script language="javascript">
 	function SetUrlType(){	
		if( form1.rbType[0].checked){
			form1.btnSelectFile.style.visibility='hidden';	
			//form1.player.selectedIndex =0;	
		}else {
			form1.btnSelectFile.style.visibility='visible';		
		}
	}
	function FromCheck(){
		if( form1.name.value==""){
			alert("名称不能为空 ");
			return ;
		}
		if( form1.url.value==""){
			alert("地址不能为空");
			return ;
		}
		//if( form1.player
		
		return true;
	}
 	function OnSave(){
 		if( !FromCheck()){
			return;
		}
		form1.submit();
 	}
 </script>
 
<body  onLoad="SetUrlType()">
<form name="form1" method="post" action="/media/save">
  <table width="482" height="189" border="1">
    <tr>
      <td width="98">&nbsp;</td>
      <td>&nbsp;</td>
      <td width="80">&nbsp;</td>
    </tr>
    <tr>
      <td>名称</td>
      <td><input name="name" type="text" value="<?php echo $this->escape($this->name);?>" maxlength="128">
      <input type="hidden" name="temp_file" value="<?php echo $this->escape($this->auto_name);?>">
      <input type="hidden" name="id" value='<?php echo $this->escape($this->id);?>'></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td rowspan="2">地址</td>
      <td height="24"><input name="rbType" type="radio" value="url" 
	  <?php if (!$this->auto_name) {
	  			echo ' checked ';
	  		}	  	
	  ;?> onClick="SetUrlType()">URL
          <input type="radio" name="rbType" value="file" onClick="SetUrlType()"
		  <?php if ($this->auto_name) {
					echo ' checked ';
				}	  	
		 ?>		  
		  >
          文件</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td height="24"><p>
        <label>        </label>
        <input type="text" name="url" value="<?php echo $this->escape($this->url);?>">
        <input type="button" name="btnSelectFile" value="选择"  onClick="window.open('/media/upload','media_upload','menubar=no,status=no,toolbar=no,width=400,height=200')">
</p></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td>播放类型      </td>
      <td>
	  <select name="player" >
	  <?php foreach($MEDIA_PLAYER_LIST as $k=>$v){ ?>
	  	<option value="<?php echo $k; ?>" <?php if($this->player==$k){echo ' selected ';}?>>
		<?php echo $v;?></option>
	  <?php }?>
      </select></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td>高度</td>
      <td><input name="width" type="text" value="<?php if($this->width) {echo $this->escape($this->width);}else{ echo 400;}?>" maxlength="4"></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td>宽度</td>
      <td><input name="height" type="text"  value="<?php if($this->height) {echo $this->escape($this->height);}else{ echo 400;}?>" maxlength="4"></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><div align="center">
        <input type="button" name="btnAdd" value="保存" onClick="OnSave()">
      </div></td>
    </tr>
  </table>
</form>
</body>
</html>

