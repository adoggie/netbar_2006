#ifndef _DULEX_H
#define _DULEX_H

#include <windows.h>

#pragma  pack(1)

struct   PlayTraits;

typedef void (*CB_PlayEnd_T)(PlayTraits*);

struct PlayTraits{
    char *  mid;    //media file identity
	char *  url;
    char *  player;
	int     width;
	int     height;
	int     center;
	int     topmost;
    int     stime ;   // start time
    int     etime ;   // end time
    void *  delta;      //±£¡Ùœﬂ≥Ã±‡∫≈
    DWORD   thread;
    DWORD   backMsg;
  //  CB_PlayEnd_T cb_playend;
    PlayTraits(){
        backMsg =  NULL;
        thread = NULL;
        delta = NULL;
    }
};


typedef void  (*ParamConfigT)(DWORD notifyThread,DWORD MsgChanged);
typedef void   (*PlayMediaT)(PlayTraits*);


struct DeluxProc{
	PlayMediaT    PlayMedia;
	ParamConfigT	ParamConfig;
};



#pragma  pack(8)

#define Html_Format_MediaPlayer "<html>"\
                                "<style type=\"text/css\">"\
                                "<!--body {margin-left: 0px;margin-top: 0px;margin-right: 0px;margin-bottom: 0px;}-->"\
                                "</style>"\
                                "<body style=\"overflow:hidden\">"\
                                "<OBJECT ID=\"WMPlay\" WIDTH=%d HEIGHT=%d CLASSID=\"CLSID:22D6f312-B0F6-11D0-94AB-0080C74C7E95\" " \
								"CODEBASE=\"http://activex.microsoft.com/activex/controls/mplayer/en/nsmp2inf.cab#Version=6,4,5,715\" "\
								"STANDBY=\"Loading Microsoft? Windows Media? Player components...\" " \
								"TYPE=\"application/x-oleobject\"> " \
								"<PARAM NAME=\"FileName\" VALUE=\"%s\"> " \
								"<PARAM NAME=\"ShowControls\" VALUE=\"False\"> " \
								"<PARAM NAME=\"AutoRewind\" VALUE=\"True\"> " \
								"<PARAM NAME=\"AutoStart\" VALUE=\"True\"> " \
                                "<PARAM NAME=\"playCount\" VALUE=\"0\">" \
								"</OBJECT>"\
                                "</body></html>"

#define Html_Format_RealPlayer  "<html>"\
                                "<style type=\"text/css\">"\
                                "<!--body {	margin-left: 0px;"\
                                "	margin-top: 0px;"\
                                "	margin-right: 0px;"\
                                "	margin-bottom: 0px; }-->"\
                                "    </style>"\
                                "<body style=\"overflow:hidden\">"\
                                "<object classid=\"clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA\" width=\"%d\" height=\"%d\" id=\"Player\"  viewastext>"\
                                "<param name=\"_ExtentX\" value=\"12726\">"\
                                "<param name=\"_ExtentY\" value=\"8520\">"\
                                "<param name=\"AUTOSTART\" value=\"1\">"\
                                "<param name=\"SHUFFLE\" value=\"0\">"\
                                "<param name=\"PREFETCH\" value=\"0\">"\
                                "<param name=\"NOLABELS\" value=\"0\">"\
                                "<param name=\"CONTROLS\" value=\"ImageWindow\">"\
                                "<param name=\"CONSOLE\" value=\"_master\">"\
                                "<param name=\"LOOP\" value=\"1\">"\
                                "<param name=\"NUMLOOP\" value=\"0\">"\
                                "<param name=\"CENTER\" value=\"0\">"\
                                "<param name=\"MAINTAINASPECT\" value=\"1\">"\
                                "<param name=\"BACKGROUNDCOLOR\" value=\"#000000\">"\
                                "<param name=\"src\" value=\"%s\">"\
                                "</object><br>"\
                                "</body>"\
                                "</html>"


#define Html_Format_Flash       "<html>"\
                                "<style type=\"text/css\">"\
                                "<!--body {	margin-left: 0px;"\
                                "	margin-top: 0px;"\
                                "	margin-right: 0px;"\
                                "	margin-bottom: 0px; }-->"\
                                "    </style>"\
                                "<body style=\"overflow:hidden\">"\
                                "<object classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,29,0\" width=\"%d\" height=\"%d\">"\
                                "<param name=\"movie\" value=\"file://%s\">"\
                                "<param name=\"quality\" value=\"high\">"\
                                "</object>"\
                                "</body>"\
                                "</html>"

#endif
