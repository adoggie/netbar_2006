<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>

<head><link href="csdn.css" type="text/css" rel="stylesheet">
  <style>#CFContent a:link {	color: #000;	text-decoration: none;}#CFContent a:visited {	color: #000;	text-decoration: none;}#CFContent a:hover {	color: #F00;	text-decoration: underline;}#CFContent a:active {	color: #000;	text-decoration: none;}	#CFBig {		width: 760px;		clear: both;		margin: auto;		font-family: Tahoma, sans-serif;		text-align: center;background-color: #FFF;	}		#CFBig #CFContent {		margin: auto;		width: 500px;		text-align: center;	}	#CFBig #CFContent p {		margin: 2px;font-size:9pt; 	}	#CFBig hr {		height: 1px;		color: #4682B4;	}	#CFBig #CFBiaoShi {		width: 40px;		float: right;	}	</style>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�ޱ����ĵ�</title>
</head>

<body>
<form name="form1" method="post" action="/fdc/QueryExec">
  <table width="308" border="2" align="center" cellpadding="1" cellspacing="1">
    <tr>
      <td width="67">����</td>
      <td width="200"><input type="text" name="fdc_name" value="<?php echo $this->name;?>"></td>
    </tr>
    <tr>
      <td>���</td>
      <td><input type="text" name="fdc_id" value="<?php echo $this->id;?>"></td>
    </tr>
    <tr>
      <td>IP��ַ</td>
      <td><input type="text" name="fdc_ip" value="<?php echo $this->ip;?>"></td>
    </tr>
    <tr>
      <td>��</td>
      <td><select name="fdc_group">
	  <option value="all">������</option>
	  <?php 

	  while( $row=mysql_fetch_array($this->result)){
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
      <td colspan="2"><div align="center">
          <input type="submit" name="Submit" value="��ѯ">
      </div></td>
    </tr>
  </table>
  <input type="hidden" name="back_url">
</form>
</body>
</html>

