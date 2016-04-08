// media play management system
// sing up agreement is not suitable for me , delay sometimes,some days
// before 5.8,i should complete fpc,fdc and a part of cms about communicating
// archive built on 2006.05.04
// i love coding,i will get be top of roof 
#include <Ice/Identity.ice>


module MPMS{
	struct fpcControlInfo{
		int		policySyncTime;		//����ͬ��ʱ����
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
		string		wallpaper;	//������λͼ����url����
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
	//������Чʱ��
	struct PolicyTime{
		int	stime;			//��Чʱ�� time_t
		int	etime;
		string	weekday;	//�����ñ�־ 1111111
		int shour;			
		int ehour;			//һ������Чʱ��
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
		string 	midiaId;	//ý�������ļ����
		string	event;		//�¼���� msn,qq,ietbr,login
		string	fpcIp;		
		string  fpcMac;	
		int		startTime;	//���ſ�ʼʱ��
		int		endTime;	//����ʱ��
	};
	sequence<EventMediaPlay> EventMediaPlayList;
	
	// fdc invoke fpc.ChangeSetting() periodically
	// implementation with python 
	interface FrontDispatchController{
		bool					RegisterFPC(Ice::Identity fpcIdent,fpcParameter fpc);	// Ŀǰֻ֧��fpc��cms�ĵ������,����ע��ʱ��fpcParameter���� i love it ,so cool!
		fpcSetting				GetFPCSettings();						//cms����ʱ���б����ӽ����ip��ַ�Ƿ��Ѿ�ƥ��ָ���ͻ�ip����Ϊ�ͻ�ip�ǹ̶���		
		fdcParameter			GetParameter();
		void					ReportMideaPlayEvent(string fdcid,EventMediaPlayList list); 
								// fpc��cms����ʱ��fdcid����,fpc��fdc����ʱfdcid����
	};
	
	struct FtpServer{
		string 	host;
		string 	port;
		string	user;
		string	passwd;
	};
	
	struct SystemDistribution{
		string				subsys;			//��ϵͳ
		string 				version;		//����ftp server ,����subsysĿ¼������versionĿ¼����
		NetFileList			fileList;		//
	};
	// python + xmlrpc + php + zend_framework
	interface CentreMangementSystem extends FrontDispatchController{		
		PlayPolicyList				GetPlayPolicies(string fdcID); 
		fpcControlInfo				GetfpcControlInfo(string fdcID);
		bool						RegisterFDC(Ice::Identity fdcIdent); //cms<->fdc ֧�ֵ�����˫��ͨѶ,Ŀǰֻʵ��fdc->cms
		SystemDistribution			SyncSystem(string moduleType,string version); // type='fpc','fdc'; version='1.0.1'
		FtpServer					GetFtpServer();
	};

};