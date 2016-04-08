
/**
	多动态库文件管理
	2005.11.16	add "UnloadAll()"
*/
#ifndef _DLLMGR_H
#define _DLLMGR_H

#include <vector>


class NVDLLMGR:public NVObject{
public:
	typedef std::vector<NVDll*> Dll_List;
	
	NVDLLMGR(){
	}
	
	void	LoadList(char ** dlls){
		char * file;
		int i=0;
		while( file = dlls[i++]){
			LoadDll(file);
		}
	}

	virtual NVDll* 	LoadDll(const char * file){
			NVDll * dll = new NVDll;
			if( dll->LoadDll(file) ){
				_dll_list.push_back(dll);
				return dll;
			}
			delete dll;							
			return NULL;
	}
	
	NVDll * GetDll(const char * file){
		NVDll * dll;
		Dll_List::iterator itr;		
		for( itr = _dll_list.begin();itr!=_dll_list.end();itr++){
			dll = *itr;
			if( dll->GetFileName() == file){
				return dll;
			}
		}
		return NULL;
	}
	
	virtual void Unload(NVDll *dll){
		dll->FreeDll();
	}

	void UnloadAll(){
		Dll_List::iterator itr;
		NVDll * dll;
		for( itr = _dll_list.begin();itr!=_dll_list.end();itr++){
			dll = *itr;
			Unload(dll);
			delete dll;
		}
	}

	~NVDLLMGR(){
		UnloadAll();
	}	
private:		
	Dll_List	_dll_list;
};

#endif
