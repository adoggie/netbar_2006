//---------------------------------------------------------------------------

#include "sliderText.h"

bool	RegReadString(HKEY root,std::string subdir,std::string key,std::string &value){
	char buff[1024];
	DWORD size=sizeof(buff);
	HKEY subkey= NULL;
	value ="";
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subdir.c_str(),0,KEY_ALL_ACCESS,&subkey)!=ERROR_SUCCESS){
		return false;
	}
	memset(buff,0,sizeof(buff));
	DWORD type = REG_SZ;
	if( RegQueryValueEx(  subkey,key.c_str(),(LPDWORD)NULL,(LPDWORD )&type,(LPBYTE)buff,(LPDWORD)&size) !=ERROR_SUCCESS){
		RegCloseKey(subkey);
		return false;
	}
	value = buff;
	RegCloseKey(subkey);
	return true;
}


//---------------------------------------------------------------------------
 
SliderText::SliderText(){

    _running = false;
}

void    SliderText::OnMouseClicked(){
	if( _er )
	_er->TextClicked(&_selected);
   // Form1->Memo1->Lines->Add(AnsiString(_selected.text.c_str())+"==>" + AnsiString(_selected.link.c_str()));    
}

#define CREATE_FONT   \
		HFONT font = CreateFont(13,8,0,0,FW_THIN,FALSE,FALSE,FALSE,GB2312_CHARSET,\
                OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,/*FF_SWISS*/FF_MODERN,"宋体");

void    SliderText::ReloadText(){
    int index = 0;
 
    char  buff[512];
    int size;
    _text_list.clear();
   // ShowMessage("dasf");
    std::string root = "SOFTWARE\\MPMS\\FPC\\SLIDETEXT";
    HKEY hKey;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, root.c_str(), 0, KEY_ALL_ACCESS, &hKey);
    while( 1 ){
        SlideText st;
		size = sizeof(buff);
        //
        if( RegEnumKey(hKey,index,buff,size) !=ERROR_SUCCESS ) {
            break;
        }

        std::string sub,value;
        sub = buff;
        st.text = sub;
		RegReadString(hKey, root+"\\"+sub,"id",st.id);
		RegReadString(hKey, root+"\\"+sub,"url",st.link);
		RegReadString(hKey, root+"\\"+sub,"player",st.player);

		RegReadString(hKey, root+"\\"+sub,"width",value);
        st.width = atoi(value.c_str());
		RegReadString(hKey, root+"\\"+sub,"height",value);
		st.height = atoi(value.c_str());
        
        _text_list.push_back(st);
		//-- add seperator
        st.text="  ";
        st.link="";
        _text_list.push_back(st);
		index++   ;      
    }
    RegCloseKey(hKey);
    //-- 计算每个文本块的区域
   
    GetClientRect(_wnd,&_logrc);
    HDC dc;
    SIZE sz;
    dc = GetDC(_wnd);

	CREATE_FONT
    SelectObject(dc,font);
    memset(&_logrc,0,sizeof(_logrc));
    _line = "";
    for( SlideTextList::iterator itr = _text_list.begin();itr!=_text_list.end();itr++){
        GetTextExtentPoint32(dc, (*itr).text.c_str(), (*itr).text.length(), &sz);
        _logrc.bottom = sz.cy;
        (*itr).logrect = _logrc;
        (*itr).logrect.left = _logrc.right;
        (*itr).logrect.right+= sz.cx;
        _logrc.right+=sz.cx;
        _line+=(*itr).text;
    }
	DeleteObject(font);
	ReleaseDC(_wnd,dc);
}

DWORD SliderText::ShowThread(void * p ){
    SliderText * st = (SliderText*)p;
    HDC dc;
    RECT rc;
    POINT pt;
    
    GetClientRect(st->_wnd,&rc);
    
    st->_running = true;
    pt.x = -0xffffff;
    st->ReloadText();

    char buff[256];
    WNDCLASS wcls;
    GetClassName(st->_wnd, buff,sizeof(buff));

    GetClassInfo((HINSTANCE )GetWindowLong(st->_wnd,GWL_HINSTANCE),buff,&wcls);
    //br = wcls.hbrBackground;
    

    while ( st->_running ){
        Sleep(20);

        if ( pt.x <0 && abs(pt.x)>=st->_logrc.right ){
			GetClientRect(st->_wnd,&rc);
            pt.x = rc.right;
            pt.y = st->_logrc.bottom;
            st->ReloadText();
        }
        memset(&st->_drc,0,sizeof(st->_drc));
        st->_drc.left = pt.x;
        pt.x-=1;
        st->_drc.right=st->_drc.left+ st->_logrc.right;
        st->_drc.bottom = pt.y;

        dc = GetDC(st->_wnd);
        st->DrawText(dc);
        ReleaseDC(st->_wnd,dc);
    }
    return NULL;
}

void    SliderText::DrawText(HDC dc){
    POINT pt;
    RECT rc;
//    HBITMAP bitmap;
  //  HDC CompDC;  

	CREATE_FONT
    HBRUSH br = CreateSolidBrush(_dt.bgcolor);
	if( !IsWindow(_wnd)){
		//MessageBox(0,"dfkd","",MB_OK);
		return;
	}
	GetClientRect(_wnd,&rc);
//	bitmap = CreateCompatibleBitmap( dc,rc.right-rc.left,rc.bottom-rc.top);
//	CompDC = CreateCompatibleDC(dc);
	//SelectObject(dc,bitmap);  
    SelectObject(dc,font);
	SetTextColor(dc, _dt.ctext);
    SetBkMode(dc, TRANSPARENT);

    
    FillRect(dc,&rc,br);
    FillRect(dc,&_drc,br);
    ::DrawText(dc,_line.c_str(), -1, &_drc, DT_SINGLELINE|DT_LEFT);

    GetCursorPos(&pt);
    ScreenToClient(_wnd,&pt);
    
    if( !PtInRect(&rc,pt) ){
        _selected.text ="";
        _selected.link = "";        
    }else{    
		for( SlideTextList::iterator itr=_text_list.begin();itr!=_text_list.end();itr++){
			if( ((*itr).logrect.left + _drc.left) <= pt.x && ((*itr).logrect.right + _drc.left) >=pt.x){
				//-- cursor  在一文本段内
				RECT rci;
				rci = _drc;
				rci.left = (*itr).logrect.left + _drc.left;
				rci.right = (*itr).logrect.right + _drc.left;
				FillRect(dc,&rci,br);
				//HPEN pen =CreatePen(PS_SOLID,1,RGB(255,0,0));
				SetTextColor(dc,_dt.chover);
				//SelectObject(CompDC,pen);
				::DrawText(dc,(*itr).text.c_str(), -1, &rci, DT_SINGLELINE|DT_LEFT);
				_selected = *itr;
			}
		}
	}
	DeleteObject(br);
	DeleteObject(font);
//	::BitBlt(dc,0,0,rc.right-rc.left,rc.bottom-rc.top,CompDC,0,0,SRCCOPY );
//	ReleaseDC(_wnd,CompDC);
}

void    SliderText::OnPaint(HDC dc){
    DrawText(dc);    
}

bool    SliderText::Create(EventReciever* er,HWND wnd,DrawTraits dt){
    DWORD id;
    _er = er;
    _wnd = wnd;
    _dt = dt;
    //_cursor = GetCursor();
    HCURSOR c = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
    SetCursor( c);
    SetClassLong(_wnd,GCL_HCURSOR,(LONG)c);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SliderText::ShowThread,(void*)this,0,&id);
    return true;
}

void    SliderText::Destroy(){
    _running = false;
    Sleep(500);
}




