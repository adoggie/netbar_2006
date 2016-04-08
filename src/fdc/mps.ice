// media play management system
// sing up agreement is not suitable for me , delay sometimes,some days
// before 5.8,i should complete fpc,fdc and a part of cms about communicating
// archive built on 2006.05.04
// i love coding,i will get be top of roof 

module MPMS{
	struct fpcSetting{
		string		ieDefaultAddr;
		string		wallpaper;
		string		alNotification;
		string		alAdvertisement;
	};
	struct fpcParameter{
		string ip;
		string mac;
	};
	struct MediaControlInfo{		//
		string  url;		
		string	player;		// mediaplayer(mp),realplayer(rp),flash(fl),ie
		int 	width;
		int		height;
	};
	sequence<MediaControlInfo> MediaControlInfoList;
	
	struct PlayPolicy{		//
		fpcSetting	fpcs;
		MediaControlInfo 	qq;		//now ,just qq,msn be thinked about,in feature ,it will use array hold these cases,now is useless
		MediaControlInfo	msn;	
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
	};
	
	sequence<byte>	ByteList;
	// fdc invoke fpc.ChangeSetting() periodically
	// implementation with python 
	interface FrontDispatchController{
		void			RegisterFPC(FrontPlayController* fpc,string anystr,ByteList digest);	// i love it ,so cool!
		MediaControlInfoList 	GetMediaControlInfo(fpcCatchedEvent event);	// 
	};
	// python + xmlrpc + php + zend_framework
	interface CentreMangementSystem{
		MediaControlInfoList 		GetMediaControlInfo(fpcCatchedEvent event);
		PlayPolicyList				GetPlayPolicies(string fdcID); 
	};

};