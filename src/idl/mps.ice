// media play management system
// sing up agreement is not suitable for me , delay sometimes,some days
// before 5.8,i should complete fpc,fdc and a part of cms about communicating
// archive built on 2006.05.04
// i love coding,i will get be top of roof 
#include <Ice/Identity.ice>


module MPMS{
	struct fpcControlInfo{
		int		policySyncTime;		//策略同步时间间隔
	};
	struct MediaControlInfo{		//
		string 	id;			//media file id
		string	name;
		string  url;				
		string	player;		// mediaplayer(mp),realplayer(rp),flash(fl),(ie),toolbar(ietb)
		int 	width;
		int		height;
	};
	sequence<MediaControlInfo> MediaControlInfoList;
	
	struct IEToolbarControlInfo{
		MediaControlInfoList	mciList;
	};
	
	struct fdcParameter{
		string 	id;
		string	gateway;
	};
	
	
	struct fpcSetting{
		string		ieDefaultAddr;
		string		wallpaper;	//可以是位图或者url连接
		IEToolbarControlInfo	ieToolbar;		//
		MediaControlInfo		alNotification;
		MediaControlInfo		alAdvertisement;
		MediaControlInfo 	qq;		//now ,just qq,msn be thinked about,in feature ,it will use array hold these cases,now is useless
		MediaControlInfo	msn;			
	};
	
	
	
	struct fpcParameter{
		string ip;
		string mac;
	};
	sequence<fpcParameter> fpcParameterList;

	
	
	sequence<bool>	WeekDayEnable;
	//策略起效时间
	struct PolicyTime{
		int	stime;			//起效时间 time_t
		int	etime;
		string	weekday;	//周启用标志 1111111
		int shour;			
		int ehour;			//一天内起效时间
	};
	
	struct PlayPolicy{		//
		PolicyTime			pTime;
		fpcSetting			fpcs;
	};
	sequence<PlayPolicy> PlayPolicyList;	
	
	struct fpcCatchedEvent{
		string app;		// -- qq,msn
		string fpcType;
	};
	
	// when fpc dectect the condition that msn,qq have starting ,invoke fdc.GetMediaInfo() immediately
	// implementaion with c++
	interface FrontPlayController{
		void 	ChangeSetting(fpcSetting setting);
		string	GetType();	// pcType 1 - normal,2- advertisement
		fpcParameter GetParameter();
	};

	
	sequence<byte>	ByteList;

	struct NetFile{
		string		file;
		string		instdir; //$system,$windows,$temp
	};
	sequence<NetFile> NetFileList;
	

	
	struct EventMediaPlay{
		string 	midiaId;	//媒体资料文件编号
		string	event;		//事件类别 msn,qq,ietbr,login
		string	fpcIp;		
		string  fpcMac;	
		int		startTime;	//播放开始时间
		int		endTime;	//结束时间
	};
	sequence<EventMediaPlay> EventMediaPlayList;
	
	// fdc invoke fpc.ChangeSetting() periodically
	// implementation with python 
	interface FrontDispatchController{
		bool					RegisterFPC(Ice::Identity fpcIdent,fpcParameter fpc);	// 目前只支持fpc到cms的单向调用,所以注册时将fpcParameter带入 i love it ,so cool!
		fpcSetting				GetFPCSettings();						//cms处理时将判别连接进入的ip地址是否已经匹配指定客户ip，因为客户ip是固定的		
		fdcParameter			GetParameter();
		void					ReportMideaPlayEvent(string fdcid,EventMediaPlayList list); 
								// fpc与cms连接时将fdcid带入,fpc与fdc连接时fdcid忽略
	};
	
	struct FtpServer{
		string 	host;
		string 	port;
		string	user;
		string	passwd;
	};
	
	struct SystemDistribution{
		string				subsys;			//子系统
		string 				version;		//进入ftp server ,进入subsys目录，进入version目录下载
		NetFileList			fileList;		//
	};
	// python + xmlrpc + php + zend_framework
	interface CentreMangementSystem extends FrontDispatchController{		
		PlayPolicyList				GetPlayPolicies(string fdcID); 
		fpcControlInfo				GetfpcControlInfo(string fdcID);
		bool						RegisterFDC(Ice::Identity fdcIdent); //cms<->fdc 支持单连接双向通讯,目前只实现fdc->cms
		SystemDistribution			SyncSystem(string moduleType,string version); // type='fpc','fdc'; version='1.0.1'
		FtpServer					GetFtpServer();
	};

};