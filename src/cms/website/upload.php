��<html>

����<head>

����<title>���������ļ�</title>

����</head>

����<body>

����<?php 
	$userfile=$_FILES['userfile']['tmp_name'];
	echo $userfile;
	move_uploaded_file($userfile,'c:/tmp/abc.mp3');
//		echo  gettype($userfile);
		/*
	copy($userfile,"newfile");
//	echo $userfile;
��//��echo $userfile."-�û��ϴ����������ϵ��ļ���ʱ��ŵ�����";
����echo $userfile_name."-���û������ϸ��ļ���ԭʼ����";
����echo $userfile_size."-�ϴ��ļ���ʵ���ֽ���";
����echo $userfile_type."-����û���������ṩ�������Ϣ�Ļ�������ʾmime�����͡�����image/gif";
*/
����?>

����</body>

����</html> 
