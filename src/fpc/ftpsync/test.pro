*=====================================================
*ftp_login: 登录ftp服务器
DECLARE INTEGER ftp_login IN ftpsync.dll  STRING ,INTEGER, STRING,STRING
*ftp_logoff: 退出ftp
DECLARE  ftp_logoff IN ftpsync.dll  
*ftp_cwd: 切换ftp服务器目录
DECLARE INTEGER ftp_cwd IN ftpsync.dll  STRING
*ftp_getfile: 下载ftp文件到本地文件
DECLARE INTEGER ftp_getfile IN ftpsync.dll  STRING ,STRING
*=====================================================

*以下代码在foxpro6,winxp下连接linux(vsftp)测试成功
* set default to c:\
*=====================================================
?ftp_login('192.168.14.1',21,'scott','runonce')
?ftp_getfile('clip0019.avi','c:\my.avi')
?ftp_logoff()


