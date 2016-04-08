
/*
	updated 2005.11.18	scott
		当转换多字节字符集时，先用NVCharset将字符即转换为UTF-8,然后再进行base64编码
		汉字转UTF-8 ， NVCharset::Convert("GBK","UTF-8",..,..)
	2006.01.05	scott	
		1. 从ice工程中取来的base64编码会出现0D,0A字符，现修改为正确的base64编码
*/ 
#ifndef NV_BASE_64_H
#define NV_BASE_64_H


#include <string>
#include <vector>
#include <functional>
#include "nvcharset.h"

/*
class NVBase64
{
public:

    static std::string encode(const std::vector<unsigned char>&);
    static std::vector<unsigned char> decode(const std::string&);
	struct convert_helper{
		char operator()(unsigned char c){
			return (char)c;
		}
	};
private:
    static char encode(unsigned char);
    static unsigned char decode(char);
    static bool isBase64(char);
};*/

class NVBase64
{
public:
    static std::string encode(const std::vector<unsigned char>&);
    static std::vector<unsigned char> decode(const std::string&);
	struct convert_helper{
		char operator()(unsigned char c){
			return (char)c;
		}
	};
private:
	static int Base64Encode(char * base64code, const char * src, int src_len);
	static char GetB64Char(int index);
	static int	GetB64Index(char ch);
	static int Base64Decode(char * buf, const char * base64code, int src_len);
};


#define BASE64_INLINE	inline
#include "nvbase64.i2"

inline
bool BASE64_ENCODE_STRING(NVString &ret,NVString &str){
		std::vector<unsigned char> _vc;
		std::string _msg = str;
		std::copy(_msg.begin(),_msg.end(),std::back_inserter(_vc));
		ret = NVBase64::encode(_vc);
		return true;
}


inline 
bool BASE64_DECODE_STRING(NVString &ret,NVString &str){
		std::vector<unsigned char> _vc;
		std::string _msg = str;
		_vc = NVBase64::decode(_msg);
		ret.assign(_vc.size(),'-');
		std::transform(_vc.begin(),_vc.end(),ret.begin(),NVBase64::convert_helper());
		//ret.assign((char*)_vc.begin(),(char*)_vc.end());
		return true;
}

inline 
bool TEXT_UTF8_BASE64(NVString &ret,NVString&text){
		NVString utf8;
		NVCharset::Convert("GBK","UTF-8",text,utf8);
		BASE64_ENCODE_STRING(ret,utf8);
		return true;
}

inline 
bool BASE64_UTF8_TEXT(NVString &ret,NVString & text){
		NVString utf8;
		BASE64_DECODE_STRING(utf8,text);
		NVCharset::Convert("UTF-8","GBK",utf8,ret);
		return true;
}

#endif
