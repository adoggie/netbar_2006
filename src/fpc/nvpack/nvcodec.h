
#ifndef _NV_CODEC_H
#define _NV_CODEC_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

class NVCodec{
public:
	static void BuffToHex(const char *ibuff,unsigned int ilen,char * hexbuff);
	/**< 二进制转换成16进制*/
	static int 	HexToBuff(const char *ibuff,unsigned int ilen,char * obuff);
	/**< 16进制转换成二进制数据*/
	static bool DigestCalc(const char *ibuf,unsigned int ilen,const char * isecret,char * digest/*16 bytes*/);
	/**< 计算md5 digest*/
};

						 

extern "C" void  md5_calc(unsigned char *output,unsigned char *input,unsigned int inlen);
#define MD5_DIGEST_LEN 16
inline 
bool NVCodec::DigestCalc(const char *ibuf,unsigned int ilen,const char * isecret,char * obuf){
	char *newbuf;

//	char *pcurr;	
	char authen[MD5_DIGEST_LEN];
	unsigned int authenlen =  MD5_DIGEST_LEN;
	unsigned int secretlen = strlen(isecret);
	unsigned int newlen = ilen+secretlen;
	newbuf = new char[newlen];
	memcpy(newbuf,ibuf,ilen);
	memcpy(newbuf+ilen,isecret,secretlen);
	md5_calc((unsigned char*)authen,(unsigned char*)newbuf,newlen);
	memcpy(obuf,authen,MD5_DIGEST_LEN);
	delete[] newbuf;
	return true;
}		


//////////////////////////////////////////////////////////////////////////
//字节流转换为16进制字符
inline
void char_hex(unsigned char ch,unsigned char *hexbuff){
	unsigned char v;
	v = ch /16;
	if( v <= 9){
		*hexbuff = v + '0';
	}else{
		*hexbuff = v - 10 + 'A';
	}
	hexbuff++;
	v = ch % 16;
	if( v <= 9){
		*hexbuff = v + '0';
	}else{
		*hexbuff = v - 10 + 'A';
	}
}

inline
void  NVCodec::BuffToHex(const char *ibuff,unsigned int ilen,char * hexbuff){
	for (unsigned int i=0; i < ilen; i++){
		char_hex(*(unsigned char *)ibuff++,(unsigned char*)(hexbuff+i*2));
	}
}

inline
unsigned char  hex_char(unsigned char * hex){
	unsigned char ch;
	unsigned char val;	
	ch = toupper(*hex);
	if( ch >='0' && ch <= '9'){
		ch =  (ch -'0');
	}else if (ch >='A' && ch <='F'){
		ch = (ch - 'A' + 10);
	}else {
		ch =0;
	}
	val = ch *16;
	
	ch = toupper(*(hex+1));
	if( ch >='0' && ch <= '9'){
		ch =  (ch -'0');
	}else if (ch >='A' && ch <='F'){
		ch = (ch - 'A' + 10);
	}else {
		ch =0;
	}
	val +=ch ;
	return val;
}

inline
int NVCodec::HexToBuff(const char *ibuff,unsigned int ilen,char * obuff){
	unsigned int len;
	if( ilen %2 ){
		return -1;
	}
	len = ilen / 2;
	for (unsigned int i =0 ; i< len;i++){
		*(unsigned char*)(obuff+i) = hex_char( (unsigned char *)(ibuff + i*2) );
	}
	return 0;
}

				 
#endif

