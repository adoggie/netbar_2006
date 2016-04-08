

class EventBase{

};

/*定时事件*/
class TimerEvent{

};

class AppEvent{
public:
	
};

class EventCatcher{
};



/*
两种触发fpc进行媒体资料的操作
1.监视进程，发现关心的进程启动就触发媒体资料的播放
2.接收fdc发送来的播放策略，对系统进行修改，比如墙纸，ie地址
	fdc定时发送播放策略
	cms产生策略变更通知fdc，fdc发送播放策略到fpc
	
fpc监控进程能主动产生媒体播放请求到fdc，fdc返回媒体资料信息到fpc


fpc启动时向fdc主动注册

*/