1.ftpsync.dll用于下载ftp文件使用，功能函数封装进动态库并以c的接口导出，可以在不同编程语言中使用
2. 接口:
extern "C" int ftp_login(const char * ip,int port,char * user,char * passwd);
extern "C" void ftp_logoff();
extern "C" int ftp_cwd(const char * path);
extern "C" int ftp_getfile(char* from ,char * to);

3. foxpro 使用

	
