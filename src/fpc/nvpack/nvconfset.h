
#ifndef _NVCONFSET_H
#define _NVCONFSET_H

#include "nv_vartype.h"
#include "nvxml.h"


class NVXmlConfigSet:public NVObject{
public:
	NVXmlConfigSet();
	bool Reload(const char * confile = NVNULL);
	bool SaveTo(const char * confile = NVNULL);
	NVXmlAttr * GetValue(const char * node,const char *attr);
	NVXmlAttr * GetValue(const char * node1,const char *node2,const char *attr);
public:
	NVXmlTree	_tree;
private:
	XML_Func	_xmlfunc;
	NVString	_confile;	
};

inline 
NVXmlConfigSet::NVXmlConfigSet(){

}

inline 
bool NVXmlConfigSet::Reload(const char * confile){
	FILE *file;	
	NVString cf;
	int len,ret;
	char *buff;
	if( confile == NVNULL){
		cf = _confile;
	}else{
		cf = confile;
		_confile = confile;
	}
	file = fopen(cf.c_str(),"rb");
	if( file == NVNULL){
		return false;
	}
	len = NVFile::Length(file);
	buff = new char[len];
	ret = fread(buff,len,1,file);
	fclose(file);
	if( ret <=0){		
		delete [] buff;
		return false;
	}
	if(_tree.XMLParse(buff,len) == false){
		delete [] buff;
		return false;
	}
	delete [] buff;

	return true;
}


inline 
bool NVXmlConfigSet::SaveTo(const char * confile){
	NVXmlTreeNode * node;
	unsigned int size;
	char *buff;
	int ret;
	NVString cf;
	FILE * file;
	if( confile == NVNULL){
		cf = _confile;
	}else{
		cf = confile;
	}
	
//	Lock();
	node = _tree.GetRootNode();
	if( node == NVNULL){
//		Unlock();
		return false;
	}
	node->CalcBufferSize(&size);
	buff = new char[size];
	node->ToXMLBuffer(buff,size);
	file = fopen(cf.c_str(),"wb");
	if( file == NVNULL){
		delete [] buff;
//		Unlock();
		return false;
	}
	ret = fwrite(buff,size,1,file);
	delete [] buff;
	fclose(file);
	if( ret <= 0){
//		Unlock();
		return false;
	}	
//	Unlock();
	return true;
}

inline 
NVXmlAttr * NVXmlConfigSet::GetValue(const char * node_n,const char *attr_n){
	NVXmlAttr * xattr= NVNULL;
	NVXmlTreeNode * node;
//	Lock();
	node = _tree.GetRootNode();
	if( node == NVNULL){
//		Unlock();
		return NVNULL;
	}
	node = node->GetChildNode(node_n);
	if( node == NVNULL){
//		Unlock();
		return NVNULL;
	}
	xattr =  node->GetAttr(attr_n);	
//	Unlock();

	return xattr;
}

inline 
NVXmlAttr * NVXmlConfigSet::GetValue(const char * node1,const char*node2,const char *attr){
	NVXmlAttr * xattr= NVNULL;
	NVXmlTreeNode * node;
//	Lock();
	node = _tree.GetRootNode();
	if( node == NVNULL){
//		Unlock();
		return NVNULL;
	}
	node = node->GetChildNode(node1);
	if( node == NVNULL){
//		Unlock();
		return NVNULL;
	}
	node = node->GetChildNode(node2);
	if( node == NVNULL){
//		Unlock();
		return NVNULL;
	}
	xattr = node->GetAttr(attr);	
//	Unlock();	
	return xattr;	
}

#endif
