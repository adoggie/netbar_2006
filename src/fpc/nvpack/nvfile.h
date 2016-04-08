#ifndef _NVFILE_H_
#define _NVFILE_H_

#include "nv_vartype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
SEEK_CUR 
	Current position of file pointer 
SEEK_END 
	End of file 
SEEK_SET 
	Beginning of file 
*/


class NVFile{
enum NVFILE_MODE{
	TEXT,
	BINARY
};

public:
	NVFile();
	~NVFile();
	bool 	Open(NVString file,const char * mode );
	void 	Close();
	bool 	Seek(unsigned int offset,int origin);
	int 	Read(char *buff,unsigned int len);
	int 	Write(char *buff,unsigned int len);
	void 	Flush();
	FILE *  GetFileHandle();
	int		GetFD();
	static unsigned int Length(FILE*);
	
private:
	FILE *	_fh;

};

inline NVFile::NVFile(){
	_fh = 0;
}

inline NVFile::~NVFile(){
	Close();
}

inline 
bool 	NVFile::Open(NVString file,const char * mode ){
	_fh = fopen(file.c_str(),mode);
	if(!_fh){
		return false;
	}
	return true;
}

inline 
void 	NVFile::Close(){
	if(_fh){
		fclose(_fh);
		_fh = 0;
	}
}

inline 
bool 	NVFile::Seek(unsigned int offset,int origin){
	fseek(_fh,offset,origin);
	return true;
}

inline 
int 	NVFile::Read(char *buff,unsigned int len){
	int ret;
	ret = fread(buff,1,len,_fh);
	return ret;
}

inline
int 	NVFile::Write(char *buff,unsigned int len){
	int ret;
	fwrite(buff,1,len,_fh);
	return ret;
}

inline 
void 	NVFile::Flush(){
	fflush(_fh);
}

inline 
FILE *  NVFile::GetFileHandle(){
	return _fh;		
}

inline 
int NVFile::GetFD(){
	int fd;
	fd = fileno(_fh);
	return fd;
}

inline
unsigned int NVFile::Length(FILE* fp){
	unsigned int pos,off;
	off = (unsigned int)ftell(fp);
	fseek(fp,0,SEEK_END);
	pos = (unsigned int)ftell(fp);
	fseek(fp,off,0);
	return pos;
}

#endif
