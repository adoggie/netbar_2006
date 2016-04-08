/*
	file:	nvcharset.h
	desc:   字符集转换封装
	support:
			UTF-8
			GB2312
	histroy:
			2005.11.25	scott	力图修改为支持任何字符集之间的转换
	notes:	
			默认windows字符集 GBK,GB2312
			对于uft-8文件中读取数据并进行转换成其他字符集时，必须去除utf-8的头(前3个字节)
			在程序中直接将GB2312字符串转换成UTF-8成功
*/


#ifndef _NV_CHARSET_H
#define _NV_CHARSET_H

#include "nv.h"
//#include "iconv.h"

typedef void* iconv_t;

#define USING_CHARSET_CONVERT	iconv_procs NVCharset::_iconv_procs={0};\
									NVDll NVCharset::_iconv_dll;

struct iconv_procs{
	iconv_t (*iconv_open)(const char* tocode, const char* fromcode);
	size_t 	(*iconv)(iconv_t cd, const char* * inbuf, size_t *inbytesleft, char* * outbuf, size_t *outbytesleft);
	int 	(*iconv_close)(iconv_t cd);
};


class NVCharset{
	NVCharset(){}
public:
	static bool	Convert(const char * charset1,const char * charset2,NVString &str1,NVString &str2);
	static bool Init_IconvLib(const char * lib);		
private:
	static iconv_procs	_iconv_procs;	
	static NVDll 		_iconv_dll;
};
inline 
bool NVCharset::Init_IconvLib(const char * lib){	
	if ( !NVCharset::_iconv_dll.LoadDll(lib)){
		return false;	
	}	
	
	_iconv_procs.iconv_open = (iconv_t (*)(const char* , const char* ))
							_iconv_dll.LoadSymbol("libiconv_open");
	_iconv_procs.iconv = (size_t (*)(iconv_t , const char* * , size_t *, char* * , size_t *))
							_iconv_dll.LoadSymbol("libiconv");
	_iconv_procs.iconv_close = (int (*)(iconv_t ))_iconv_dll.LoadSymbol("libiconv_close");
	
	return true;
}

inline
bool	NVCharset::Convert(const char * cs_from,const char * cs_to,NVString &from,NVString &to){
	unsigned int need_len = from.size() * 3;
	char *out;		
	char *buff ;
	char *in;	
	unsigned int out_len;
	unsigned int in_len;
	bool ret;
	
	ret = false;
	
	buff = new char[ need_len];
	if( buff == 0){		
		return false;						
	}
	memset(buff,0,need_len);
	iconv_t ic = NVCharset::_iconv_procs.iconv_open (cs_to,cs_from);
	
//	iconv_t ic = NVCharset::_iconv_procs.iconv_open ("GB2312","UTF-8");
	if( ic == iconv_t(-1)){
		delete [] buff;
		return false;
	}
	out = buff;
	out_len = need_len;
	
	in = (char*)from.c_str();
	in_len = from.size();
	NVCharset::_iconv_procs.iconv(ic,NULL,NULL,NULL,NULL);
	size_t result = NVCharset::_iconv_procs.iconv(ic,(const char**)&in,&in_len,(char**)&out,&out_len);						
	NVCharset::_iconv_procs.iconv_close(ic);
	
	if( result != (size_t)-1){		/// convert ok
		to.assign( buff,need_len-out_len );
		ret = true;
	}
	delete[] buff;		
	return ret;
}

/*  example:

  USING_CHARSET_CONVERT;
	  int main(int argc, char* argv[])
	  {	
	  NVCharset::Init_IconvLib("libiconv.dll");
	  NVString s1="中国";
	  NVString s2,s3;
	  FILE *fp = fopen("c:/temp/joke.txt","rb");
	  char buff[1024*10];
	  int ret;
	  ret =fread(buff,1,sizeof(buff),fp);
	  fclose(fp);
	  s1.assign(buff+3,ret-3);
		if( !NVCharset::Convert("UTF-8","GB2312",s1,s3) ){
		perror("error");
		}
	  
	  s1="中国";			
	  if( !NVCharset::Convert("GB2312","UTF-8",s1,s2) ){
	  perror("error");
	  }
	  
		if( !NVCharset::Convert("UTF-8","GB2312",s2,s3) ){
		perror("error");
		}
		
		  fp = fopen("c:/temp/joke2.txt","w");
		  fwrite(s2.c_str(),s2.size(),1,fp);
		  fclose(fp);
		  printf("Hello World!\n");
		  return 0;
		  }
		  
			

 */


#endif

