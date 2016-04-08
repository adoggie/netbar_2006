　<html>

　　<head>

　　<title>处理上载文件</title>

　　</head>

　　<body>

　　<?php 
	$userfile=$_FILES['userfile']['tmp_name'];
	echo $userfile;
	move_uploaded_file($userfile,'c:/tmp/abc.mp3');
//		echo  gettype($userfile);
		/*
	copy($userfile,"newfile");
//	echo $userfile;
　//　echo $userfile."-用户上传到服务器上的文件临时存放的名称";
　　echo $userfile_name."-在用户机器上该文件的原始名称";
　　echo $userfile_size."-上传文件的实际字节数";
　　echo $userfile_type."-如果用户的浏览器提供了这个信息的话，它表示mime的类型。例如image/gif";
*/
　　?>

　　</body>

　　</html> 
