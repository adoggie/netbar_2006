*=====================================================
*ftp_login: ��¼ftp������
DECLARE INTEGER ftp_login IN ftpsync.dll  STRING ,INTEGER, STRING,STRING
*ftp_logoff: �˳�ftp
DECLARE  ftp_logoff IN ftpsync.dll  
*ftp_cwd: �л�ftp������Ŀ¼
DECLARE INTEGER ftp_cwd IN ftpsync.dll  STRING
*ftp_getfile: ����ftp�ļ��������ļ�
DECLARE INTEGER ftp_getfile IN ftpsync.dll  STRING ,STRING
*=====================================================

*���´�����foxpro6,winxp������linux(vsftp)���Գɹ�
* set default to c:\
*=====================================================
?ftp_login('192.168.14.1',21,'scott','runonce')
?ftp_getfile('clip0019.avi','c:\my.avi')
?ftp_logoff()


