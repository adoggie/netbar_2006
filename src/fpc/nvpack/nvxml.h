
/**
	last updated	2005.03.17	zbin
	2005.11.25	scott	update

*/

#ifndef _NV_XML_PARSE_H
#define _NV_XML_PARSE_H

#include <list>
#include "nv_vartype.h"
#include "nvobject.h"
#include "expat.h"

#include "nvdll.h"

typedef XML_Parser (*NV_XML_ParserCreate)(const XML_Char *encoding);
typedef void (*NV_XML_SetUserData)(XML_Parser p,void *userData);
typedef void *(*NV_XML_GetUserData)(XML_Parser p);
typedef void (*NV_XML_SetElementHandler)(XML_Parser p,XML_StartElementHandler start,XML_EndElementHandler end);
typedef XML_Status (*NV_XML_Parse)(XML_Parser p,const char *s,int len,int isFinal);
typedef void (*NV_XML_ParserFree)(XML_Parser p);
typedef XML_Status (*NV_XML_SetEncoding)(XML_Parser p,const XML_Char *encoding);

typedef void (*NV_XML_SetCharacterDataHandler)(XML_Parser p,XML_CharacterDataHandler charhndl);



typedef struct{
	XML_Parser (*XML_ParserCreate)(const XML_Char *encoding);
	void (*XML_SetUserData)(XML_Parser p,void *userData);
	void *(*XML_GetUserData)(XML_Parser p);
	void (*XML_SetElementHandler)(XML_Parser p,XML_StartElementHandler start,XML_EndElementHandler end);
	XML_Status (*XML_Parse)(XML_Parser p,const char *s,int len,int isFinal);
	void (*XML_ParserFree)(XML_Parser p);
	XML_Status (*XML_SetEncoding)(XML_Parser p,const XML_Char *encoding);
	void (*XML_SetCharacterDataHandler)(XML_Parser p,XML_CharacterDataHandler charhndl);
}XML_Func;

class NVXmlTreeNode;
class NVXmlAttrs;
//--属性
class NVXmlAttr{
public:
	NVXmlAttr();
	~NVXmlAttr();
	NVXmlAttr(NVString name,NVString value);
	NVString *	GetValue();
	NVString *	GetName();
	void		SetValue(NVString value);
	void		SetName(NVString name);	
	int			AsInteger();

	float		AsFloat();
	unsigned int AsUInteger();
	void		operator = (int v);
	void		operator = (unsigned int v);
	void		operator = (float v);

	NVXmlAttr*	GetNext();	
	NVXmlTreeNode*	GetNode();
	friend class NVXmlAttrs;
private:		
	void		SetNode(NVXmlTreeNode*);	
private:	
	NVString _name,_value;
	NVXmlTreeNode	*_node;

};

typedef std::list<NVXmlAttr*> XmlAttrs_List;
//--属性集合
class NVXmlAttrs{//:public NVObject{
public:
	NVXmlAttrs();
	~NVXmlAttrs();
	friend class NVXmlTreeNode;
	unsigned short  GetCount();
	void			DeleteAttr(NVString  name);
	void			AddAttr(NVXmlTreeNode*,NVXmlAttr*);
	NVXmlAttr *		AddAttr(NVXmlTreeNode*,NVString ,NVString );
	NVXmlAttr *		AddAttr(NVXmlTreeNode*);	
	NVXmlAttr *		GetAttr(NVString name);	
	void			Empty();	//erase all items
	XmlAttrs_List * GetList();
 
	NVXmlAttr*		GetFirstAttr();
	
private:
	XmlAttrs_List	_attr_list;
	
};


typedef std::list<NVXmlTreeNode*> XmlTreeNode_List;

class NVXmlTreeNodes{//:public NVObject{
public:
	NVXmlTreeNodes();
	~NVXmlTreeNodes();
	friend class NVXmlTreeNode;
	void			AddChildNode(NVXmlTreeNode*);	
	NVXmlTreeNode*	AddChildNode();
	void			DeleteChildNode(NVString &name);
	void			Empty();
	unsigned int	GetCount();
	NVXmlTreeNode * GetFirstNode();
	XmlTreeNode_List* GetList();
	NVXmlTreeNode * GetNode(NVString name);	
private:
	XmlTreeNode_List _node_list;
	
};


class NVXmlTreeNode{
public:
	NVXmlTreeNode();	
	~NVXmlTreeNode();	
	NVXmlTreeNode*  GetNext();		/** Get next node*/

	NVXmlTreeNode * GetParent();
	void			SetParent(NVXmlTreeNode * );
	NVString *		GetName();
	void			SetName(NVString);
//////////////////////////////////////////////////////////////////////////
	bool			ToXMLBuffer(char *buff,unsigned int len);
	void			CalcBufferSize(unsigned int	*size);	
//////////////////////////////////////////////////////////////////////////
	void			AddChildNode(NVXmlTreeNode*);	
	NVXmlTreeNode*	AddChildNode();
	void			DeleteNode(NVString &name);
	void			EmptyNodes();
	unsigned int	GetChildNodeCount();
	NVXmlTreeNode * GetFirstNode();
	NVXmlTreeNode * GetChildNode(NVString name);	
	NVXmlTreeNode * SearchNode(NVString name,int *deep);
//////////////////////////////////////////////////////////////////////////
	unsigned short  GetAttrCount();
	void			DeleteAttr(NVString  name);
	void			AddAttr(NVXmlAttr*);
	void			AddAttr(NVString ,NVString );
	NVXmlAttr *		AddAttr();	
	NVXmlAttr *		GetAttr(NVString name);	
	void			EmptyAttrs();	//erase all items
	NVXmlAttr*		GetFirstAttr();
//////////////////////////////////////////////////////////////////////////
	NVXmlTreeNodes* GetChildNodes();
	NVXmlAttrs*		GetAttrs();
	
	NVString*	GetCharData();	// add on 2005.07.12
	void		SetCharData(NVString chars);
private:
	bool			GatherBuff(char *buff ,unsigned int len,NVXmlTreeNode* node);
protected:	
	NVXmlAttrs		_attrs;
	NVXmlTreeNodes  _nodes;		
	NVXmlTreeNode * _parent;	
	NVString 		_name;		/**node's name*/	
	NVString		_chars;	// add on 2005.07.12 
};



class NVXmlTree{
public:
	NVXmlTree(const char * charset="UTF-8");
	~NVXmlTree();
	bool		XMLParse(const char * buff,unsigned int len);
	bool		ToXMLBuffer(char *buff,unsigned int len);
	void		SetXML_Func(XML_Func xmlf);
	NVXmlTreeNode *GetRootNode();
	void		SetRootNode(NVXmlTreeNode*);
	XML_Func*	GetXML_Func(){	return &_xmlf;}	
	/*initialse xmllib,to load libexpat.dll,before every operation,it must be invoked first*/
	static bool	Init_XmlLib(const char * libexpat);			//-- update 051125
	static	XML_Func			_xmlf;	
	/*test if xml data valid*/
	static bool	CheckXml(const char * buff,unsigned int len,const char * charset="UTF-8");	//-- add on 051125
protected:	
	static void StartElement(void *userData, const char *name, const char **atts);
	static void EndElement(void *userData, const char *name);	
	static void CharacterDataHandler(void *userData,const XML_Char *s,int len);
protected:
	NVXmlTreeNode **	GetRoot();
	XmlTreeNode_List *	GetStackList();	
	NVXmlTreeNode *		_root;
	XmlTreeNode_List 	_nodes_stack;
	char * 				_charset;
	static NVDll 		_xml_dll;
	
};

#define NVXML_INLINE inline
#include "nvxml.ii"


// micro define
#define USING_XML_EXPAT	\
		XML_Func NVXmlTree::_xmlf ={0};\
		NVDll	NVXmlTree::_xml_dll;

#endif



