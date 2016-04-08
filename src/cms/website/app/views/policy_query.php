<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>无标题文档</title>
</head>
<script language="javascript">

function GetWeekDay(){
	wd="";
	if( document.all.weekday[0].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[1].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[2].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[3].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[4].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[5].checked ) { wd+='1';}else{wd+='0';}
	if( document.all.weekday[6].checked ) { wd+='1';}else{wd+='0';}
	 
	return wd;
}

function OnQuery(){
	url ="/policy/query_exec?name="+document.all.name.value;
	url+="&weekday="+GetWeekDay();
	url+="&stime="+document.all.stime.value;
	url+="&etime="+document.all.etime.value;
	url+="&shour="+document.all.shour.value;
	url+="&ehour="+document.all.ehour.value;
	window.location=url;
}

</script>
<body>
<table width="664" border="1" cellspacing="2" cellpadding="1">
  <tr>
    <td width="121">名称
        <input type="hidden" name="id">
    </td>
    <td><input name="name" type="text"  >
    </td>
  </tr>
  <tr>
    <td>有效期</td>
    <td>
      <input name="stime" type="text" size="10" maxlength="10" >
      ~
      <input name="etime" type="text" size="10" maxlength="10" ></td>
  </tr>
  <tr>
    <td>周效期</td>
    <td>
   
      一
        <input name="weekday" type="checkbox" value="1" checked 
	
			>
      二
      <input id="weekday" type="checkbox" value="2" checked 
	   
	  >
      三
      <input id="weekday" type="checkbox" value="3" checked 
	  
	  >
      四
      <input id="weekday" type="checkbox" value="4" checked 
	   
	  >
      五
      <input id="weekday" type="checkbox" value="5" checked  
	 
	  >
      六
      <input id="weekday" type="checkbox" value="6" checked 
	  
	  >
      日
      <input id="weekday" type="checkbox" value="7" checked
	  
	  ></td>
  </tr>
  <tr>
    <td>日效期</td>
    <td><input name="shour" type="text" value="0" size="4" maxlength="2" >
      ~
        <input name="ehour" type="text" value="24" size="4" maxlength="2"></td>
  </tr>
  <tr>
    <td colspan="2"><div align="center">
        <input type="button" name="Submit3" value="确定" onClick="OnQuery()">
    </div></td>
  </tr>
</table>
</body>
</html>

