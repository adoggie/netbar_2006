# -*- coding: gb2312 -*-
import time,sys,os,traceback,threading,copy,datetime,array
import socket
from logger import *
import Ice
from MPMS import *
import szftp

FILE_PLAYERS=['mp','rm','fl','image']

class fdcI(FrontDispatchController):
	def __init__(self,server):
		self._server = server	
		self._lock_fpcs=threading.Lock()
		self._fpcs=[]
		
	def RegisterFPC(self, ident,fpc,ctx):
		try:
			pass
		except:
			return False
		return True			
		
	
	def GetFPCSettings(self,_ctx):
		return self._server.GetFPCSettings()
	
	def GetParameter(self,ctx):
		param = fdcParameter()
		param.id = self._server._cnf['id']
		param.gateway= self._server._cnf['gateway']
		return param
	
	def ReportMideaPlayEvent(self,fdcid,list,ctx):
		''' fdc recieve playEvent from fpc,dely send to cms'''
		self._server.ReportMideaPlayEvent(list)
			


class fdcWorkThread(threading.Thread):
	def __init__(self,app):
		threading.Thread.__init__(self)
		self._app = app
		self._running = False
	
	def run(self):
		self._running = True
		while self._running:
			self._app.SyncServer()						
			time.sleep( self._app._cnf['sync_interval'])
						


class MainApp(Ice.Application):
	def __init__(self):
		self._cms=None
		self._adp_fpc = None
		self._adp_cms = None	# bidirection on one connection
		self._fdc = None
		self._workThread = fdcWorkThread(self)
		self._logger = Logger()
		self._cnf={}
		########
		self._play_events=[]
		self._lock_playevent=threading.Lock()
		########
		self._play_policies=[]
		self._lock_playpolicies = threading.Lock()
		
	def init(self):
		self._cnf['save_path']=self.communicator().getProperties().getProperty('fdc.save_path')
		self._cnf['access_path']=self.communicator().getProperties().getProperty('fdc.access_path')
		self._cnf['id']=self.communicator().getProperties().getProperty('fdc.id')
		self._cnf['gateway']=self.communicator().getProperties().getProperty('fdc.gateway')
		self._cnf['log.udp.host'] = self.communicator().getProperties().getPropertyWithDefault('ftp.log.udp.host','127.0.0.1')
		self._cnf['log.udp.port'] =self.communicator().getProperties().getPropertyAsIntWithDefault('fdc.log.udp.port',5002)
		self._cnf['sync_interval']=self.communicator().getProperties().getPropertyAsIntWithDefault('fdc.sync_interval',5)
		self._cnf['ftp_server']={}
		
		self._logger.SetLogUdp(self._cnf['log.udp.host'],self._cnf['log.udp.port'])
		self._logger.SetLogFile('fdc.log')
		
		print self._cnf
	
		
	def run(self,argv):
		try:
			self.init()
					
			self._adp_fpc = self.communicator().createObjectAdapter("fdc")			 
			self._fdc = self._adp_fpc.add(fdcI(self),Ice.stringToIdentity("fdc"))
			self._adp_fpc.activate()			
			self.ConnectServer()
			self._workThread.start()						
			self.shutdownOnInterrupt()
			try:
				pass #print self._cms.GetfpcControlInfo('')
			except:
				print traceback.print_exc()
			print "fdc start up"
			self.communicator().waitForShutdown()
			self._workThread._running = False
			print "==*==*"*10
			#sys.exit(0)
		except:
			print traceback.print_exc()
		return 0
		
	def ConnectServer(self):
		try:
			text = self.communicator().getProperties().getProperty('cms.servant')
			self._logger.Debug('emit ice request to:%s'%text)
			self._cms = CentreMangementSystemPrx.checkedCast(self.communicator().stringToProxy(text))
			self._cms.ice_connection().setAdapter(self._adp_fpc)			
			self._cms.RegisterFDC(self._fdc.ice_getIdentity())
			ci = self._cms.GetfpcControlInfo('')
			if ci.policySyncTime <=10:
				self._cnf['sync_interval'] =10
			else:
				self._cnf['sync_interval']= ci.policySyncTime
		except:
			self._cms = None
			self._logger.Debug('connect cms server failed!')
			#print traceback.print_exc()
	
	def ReportMideaPlayEvent(self,list):
		try:
			self._cms.ReportMideaPlayEvent('',list)
		except:
			self._logger.Debug("ReportMideaPlayEvent Failed! Discard playEvent")
			self.ConnectServer()

	
	def SavePlayEvent(self,emplist):
		self._lock_playevent.acquire()
		for e in emplist:
			self._play_events.append(e)
		self._lock_playevent.release()
		
	def SaveFile(self,save_dir,file):
		try:
			if file.file:					
				f = open( save_dir+'/'+ file,'w')
				ar = array.array('b')
				ar.fromlist( file.context)
				#f.write( file.context)
				ar.tofile(f)
				f.close()	
		except:
			self._logger.Error('save file %s failed!'%(save_dir+file))
			
	def	IsFilePlayer(self,player):
		try:
			FILE_PLAYERS.index(player)
		except:
			return False
		return True
	
	def SyncMediaFile(self,file):
		try:
			save_path = self._cnf['save_path']
			if os.path.exists( save_path+'/'+file):
				if os.stat(save_path+'/'+file)[6]==0:
					pass
				else:
					return  # now,think file's size is not zero ,shouldn't downfile from ftp server
			fs = self._cms.GetFtpServer()
			ftp = {'host':fs.host,'user':fs.user,'passwd':fs.passwd,'rdir':'','ldir':save_path,'files':[file]}
			szftp.SyncFtp(ftp)
			self._logger.Debug('file:%s be downloaded to local system'%file)
		except:
			self._logger.Error('sync media file failed <%s>'%traceback.print_exc())

	def SyncServer(self):
		''' download play policy periodically, test file if existed in local system,otherwise download media file from cms directly'''
		#self._logger.Debug('SyncServer')
		policies=[]
		self._lock_playpolicies.acquire()
		try:
			try:
				self._play_policies = self._cms.GetPlayPolicies('')
				policies = copy.deepcopy(self._play_policies)
			finally:
				self._lock_playpolicies.release()
		except:
			self._logger.Debug('SysnServer Failed! maybe cms access denied! %s'%traceback.print_exc())
			self.ConnectServer()
		print policies
		#download mediafile if file not be found in share_dir
		save_path = self._cnf['save_path']
		try:
			for p in policies:
				#-- get desktop bg
				if not os.path.exists( save_path+'/'+p.fpcs.wallpaper):
					self._logger.Debug('downloading [%s] from cms'%p.fpcs.wallpaper)
					self.SyncMediaFile(p.fpcs.wallpaper)
				#-- login stuff sync
				if self.IsFilePlayer(p.fpcs.alNotification.player) and (not os.path.exists( save_path+'/'+p.fpcs.alNotification.url)):
					self.SyncMediaFile(p.fpcs.alNotification.url)
				#-- sync qq stuff
				if self.IsFilePlayer(p.fpcs.qq.player) and (not os.path.exists( save_path+'/'+p.fpcs.qq.url)):
					self.SyncMediaFile(p.fpcs.qq.url)
				#-- sync msn stuff
				if self.IsFilePlayer(p.fpcs.msn.player) and (not os.path.exists( save_path+'/'+p.fpcs.msn.url)):
					self.SyncMediaFile(p.fpcs.msn.url)
				#-- sync ietoolbar,tbr have manay media info,so should be iterated
				for m in p.fpcs.ieToolbar.mciList:
					if self.IsFilePlayer(m.player) and ( not os.path.exists(save_path+'/'+m.url)):
						self.SyncMediaFile(m.url)
		except:			
			self._logger.Error('SyncServer exception occurred! %s'%traceback.print_exc())				
			self.ConnectServer()
	
	def GetFPCSettings(self):
		#
		settings = fpcSetting()
		now = time.time()
		self._lock_playpolicies.acquire()
		for p in self._play_policies:
			if p.pTime.stime > now or p.pTime.etime < now:
				continue
			if len(p.pTime.weekday) !=7:
				continue
			if p.pTime.weekday[datetime.datetime.now().weekday()] !='1':
				continue
			now_hour = datetime.datetime.now().hour
			if p.pTime.shour > now_hour or p.pTime.ehour < now_hour :
				continue
			settings = copy.deepcopy( p.fpcs )
		self._lock_playpolicies.release()
		#print 'GetFPCSettings::',settings
		
		if settings.wallpaper:
			settings.wallpaper = self._cnf['access_path'] + '\\'+settings.wallpaper
		if settings.ieToolbar.mciList:
			for m in settings.ieToolbar.mciList:
				if self.IsFilePlayer(m.player):
					m.url = self._cnf['access_path'] + '\\'+m.url
		if self.IsFilePlayer( settings.alNotification.player ):
			settings.alNotification.url = self._cnf['access_path'] + '\\' +settings.alNotification.url
		if self.IsFilePlayer( settings.qq.player ):
			settings.qq.url = self._cnf['access_path'] + '\\' +settings.qq.url
		if self.IsFilePlayer( settings.msn.player ):
			settings.msn.url = self._cnf['access_path'] + '\\' +settings.msn.url
		return settings			
##################################################
	
app = MainApp()
sys.exit(app.main(sys.argv,"fdc.conf"))
