//---------------------------------------------------------------------------

#ifndef sliderTextH
#define sliderTextH
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include <map>
#include <windows.h>



struct SlideText{
	std::string id;
    std::string text; // equal name
    std::string link; // equal url
	std::string player;
	int			width;
	int			height;
	RECT    logrect;

};
typedef std::vector<SlideText> SlideTextList;


class SliderText{
public:
    struct EventReciever{
        virtual void TextClicked(SlideText* text){}
    };
    struct DrawTraits{
        int         freq;
        COLORREF    ctext;
        COLORREF    chover;
        COLORREF    bgcolor;
        std::string font;
        int         size;
    };

    SliderText();
    void    OnMouseClicked();
    void    OnPaint(HDC);
    bool    Create(EventReciever* er,HWND wnd,DrawTraits dt);
    void    Destroy();
protected:
    static DWORD ShowThread(void *);
    void    ReloadText();
    void    DrawText(HDC);

private:
    DrawTraits      _dt;
    HWND            _wnd;
    EventReciever*  _er ;
    bool            _running;
    SlideTextList   _text_list;
    std::string     _line;
     RECT           _logrc;
    RECT            _drc;   //当前绘制区域
    HCURSOR         _cursor;
    SlideText       _selected;
    
};


#endif
