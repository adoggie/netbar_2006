
####
# @file:
# @desc:		implement CMS
# @author:		scott 2006.05.19
# @revision:	
#

import time,sys,os,traceback,threading,copy,datetime,re,os.path,array
import socket
from logger import *
import util
import Ice
from MPMS import *
import MySQLdb
import MySQLdb.cursors

FILE_PLAYERS=['mp','rm','fl','image']
# image just support 'bitmap',as xxx.bmp

class cmsI(CentreMangementSystem):
	def __init__(self,server):
		self._server = server	
		self._lock_fdcs=threading.Lock()		
		self._fdcs=[]
		
	def GetRemoteIpAddress(self,conn):
		ret =''
		try:
			s = conn.toString().replace('\n',' ')
			r = re.match('.*remote.*=(.*):.*',s)
			if r:
				ret = r.group(1)
		except:
			pass
		return ret
	
	def RegisterFDC(self, ident, ctx):
		ip = self.GetRemoteIpAddress(ctx.con)
		try:
			print 'RegisterFDC ::<%s>!'%ip
		except:
			print 'RegisterFDC exception occurred!'
			return False
		return True
	
	def RegisterFPC(self,ident,param,ctx):
		ip = self.GetRemoteIpAddress(ctx.con)
		fdcID = self._server.GetFdcIDByAddress(ip)
		if not fdcID:
			self._server._logger.Error('Invalide Client Reigister! Reject: <%s>'%ip)
			return False
		conn = self._server.GetDBConn()
		try:
			cur  = conn.cursor()
			cur.execute("select id from fpc where mac='%s'"%param.mac)
			rs = cur.fetchall()
			if len(rs) == 0:
				#to insert new record
				cur.execute("insert into fpc values(%s,%s,%s,%s)",(util.util_get_uuid(),fdcID,param.ip,param.mac))
				cur.close()
		except:
			self._server._logger.Debug('RegisterFPC:: <%s>'%traceback.print_exc())
		self._server.FreeDBConn(conn)
		return True
		
	def GetfpcControlInfo(self,fdcID,ctx):
		ip = self.GetRemoteIpAddress(ctx.con)
		fdcID = self._server.GetFdcIDByAddress(ip)
		ci = fpcControlInfo()
		if not fdcID:
			return ci
		ci.policySyncTime = self._server._cnf['fdc_sync_time']
		return ci
	
		#c = self._server.GetDBConn()
		#try:
		#	cur = c.cursor()
		#	cur.execute("select CONTROL_POLICY_SYNC_TIME from NETBAR where ID='%s'"%fdcID)
		#	rs = cur.fetchall()
		#	if len(rs):
		#		ci.policySyncTime = int( rs[0]['CONTROL_POLICY_SYNC_TIME'] )
		#except:
		#	self._server._logger.Debug('GetfpcControlInfo:: <%s>'%traceback.print_exc())
		#self._server.FreeDBConn(c)
		#return ci
	
	def _GetMediaInfo(self,dbconn,pid):
		''' Return MediaInfo List '''
		list = []
		try:
			cur = dbconn.cursor()
			cur.execute("select a.* from media a,policy_media b where b.media_id=a.id and policy_id='%s'"%pid)
			rs = cur.fetchall()
			for r in rs:
				mci = MediaControlInfo()
				mci.id = r['ID']
				mci.name=r['NAME']
				mci.url ="%s"%(r['URL']) #cms return url with httpxxx url
				mci.player=r['PLAYER']
				mci.width=int(r['WIDTH'])
				mci.height=int(r['HEIGHT'])
				if self._server.IsFilePlayer( mci.player ):
					mci.url = r['AUTO_NAME'] #saved on local disck that be renamed automaticly
				list.append(mci)
		except:
				self._server._logger.Debug('GetMediaInfo Failed!<%s>'%traceback.print_exc())
		if len(list) == 0 :
			list.append(MediaControlInfo()) # if not defined,then return defult
		return list
			
	def GetFPCSettings(self,ctx):
		''' fdc/fpc will initial this command to request play settings  '''
		set = fpcSetting()
		ip = self.GetRemoteIpAddress(ctx.con)
		fdcID = self._server.GetFdcIDByAddress(ip)
		conn = self._server.GetDBConn()
		try:
			cur = conn.cursor()
			cur.execute("select b.* from fdc_policy a ,policy b where a.policy_id=b.id and b._status=1 and  a.fdc_id='%s'"%fdcID)
			now = time.time()
			for r in cur.fetchall():
				if int(r['START_TIME']) >= now or int(r['END_TIME']) <= now:
					continue
				#check day of week enabled
				weekflag=str(r['WEEKDAY'])
				if len(weekflag) !=7:
					self._server._logger.Debug('WEEKDAY context is invalid (%d)'%r['ID'])
					continue
				if weekflag[datetime.datetime.now().weekday()] !='1': # week day is not enabled
					continue
				#check day time
				now_hour = datetime.datetime.now().hour
				if int(r['START_HOUR']) > now_hour or int(r['END_HOUR']) < now_hour :
					continue	#time not in effiective range
				##########################################3
				ie_addr = r['FPC_IE_DEFAULT_ADDR']
				bg=r['FPC_BG']
				ie_tbr=r['FPC_IE_TOOLBAR']
				login=r['FPC_AFTER_LOGIN']
				msn = r['FPC_MSN_LOGIN']
				qq = r['FPC_QQ_LOGIN']
				##
				set.ieDefaultAddr = self._GetMediaInfo(conn,ie_addr)[0].url
				set.wallpaper = self._GetMediaInfo(conn,bg)[0].url
				set.ieToolbar = IEToolbarControlInfo()
				set.ieToolbar.mciList = self._GetMediaInfo(conn,ie_tbr)
				set.alNotification = self._GetMediaInfo(conn,login)[0]
				set.msn = self._GetMediaInfo(conn,msn)[0]
				set.qq = self._GetMediaInfo(conn,qq)[0]
				break
		except:
			self._server._logger.Debug('GetFPCSettings() Failed! <%s>'%traceback.print_exc())
		self._server.FreeDBConn(conn)
		return set
	
	def GetNetFile(self,fname,ctx):
		''' fname=MedieControlInfo.url. read file context from storage dir'''
		nf = NetFile()
		return nf
		## read file 
		try:
			dest = self._server._cnf['media_dir']+'/'+fname
			print dest
			if os.path.exists(dest):
				f = open(dest,'rb')
				ar = array.array('B')
				ar.fromstring(f.read())
				nf.context = ar.tolist()
				f.close()
				nf.file = fname
			else:
				self._server._logger.Debug('%s not existed!'%dest)
		except:
			self._server._logger.Debug('GetNetFile:: ReadFile Failed! <%s>'%traceback.print_exc())
		print len(nf.context)
		return nf
	
	def GetPlayPolicies(self,fdcID,ctx):
		'''	 fdc will initial this command to request policies for fpc playing'''
		ip = self.GetRemoteIpAddress(ctx.con)
		fdcID = self._server.GetFdcIDByAddress(ip)
		conn = self._server.GetDBConn()
		list=[]
		try:
			cur = conn.cursor()
			sql = "select b.* from fdc_policy a ,policy b where a.policy_id=b.id and b._status=1 and  a.fdc_id='%s'"%fdcID
			print sql
			cur.execute(sql)
			for r in cur.fetchall():
				pp = PlayPolicy()
				set = fpcSetting()
				pt = PolicyTime()
				pt.stime=r['START_TIME']
				pt.etime =r['END_TIME']
				pt.weekday =r['WEEKDAY']
				pt.shour =r['START_HOUR']
				pt.ehour=r['END_HOUR']
				##########################################3
				ie_addr = r['FPC_IE_DEFAULT_ADDR']
				bg=r['FPC_BG']
				ie_tbr=r['FPC_IE_TOOLBAR']
				login=r['FPC_AFTER_LOGIN']
				msn = r['FPC_MSN_LOGIN']
				qq = r['FPC_QQ_LOGIN']
				##
				set.ieDefaultAddr = self._GetMediaInfo(conn,ie_addr)[0].url
				set.wallpaper = self._GetMediaInfo(conn,bg)[0].url
				print set.wallpaper
				set.ieToolbar = IEToolbarControlInfo()
				set.ieToolbar.mciList = self._GetMediaInfo(conn,ie_tbr)
				set.alNotification = self._GetMediaInfo(conn,login)[0]
				set.msn = self._GetMediaInfo(conn,msn)[0]
				set.qq = self._GetMediaInfo(conn,qq)[0]
				###########################333
				pp.pTime = pt
				pp.fpcs = set
				list.append(pp)
				
		except:
			list=[]
			self._server._logger.Debug('GetPlayPolicies:: <%s>'%traceback.print_exc())
		self._server.FreeDBConn(conn)
		return list
		
	def SystemSync(self,subsys,v,ctx):
		dist = SystemUpgradeDistribution()
		s = self._server.getSysSetting('product_version','fpc') # here hold subsystem's version fro subsequnce access
		if s==v:
			return dist
		conn = self._server.GetDBConn()
		try:
			cur = conn.cursor()
			rs = cur.execute('select * from product_release where system=%s and version=%s',(subsys,v))
			for r in rs:
				file = '%s/%s/%s/%s'%(self._server._cnf['product.release'],subsys,v,r['MODULE_FILE'])
				if not os.path.exists( file ):
					raise ''
				f = open(file,'rb')
				nf = NetFile()
				nf.file = r['MODULE_FILE']
				nf.instdir=r['INST_PATH']
				nf.context = f.readlines()
				dist.filelist.append(nf)
				f.close()
			dist.version=v
		except:
			dist = SystemUpgradeDistribution()
		self._server.FreeDBConn(conn)
		return dist

	def GetParameter(self,ctx):
		return fdcParameter()
		
	def ReportMideaPlayEvent(self,fdcid,emplist,ctx):
		ip = self.GetRemoteIpAddress(ctx.con)
		fdcID = self._server.GetFdcIDByAddress(ip)
		if not fdcID:
			self._server._logger.Debug('ReportMideaPlayEvent:unknown client request<%s>',ip)
			return 
		conn = self._server.GetDBConn()
		try:
			cur = conn.cursor()
			for e in emplist:
				cur.execute('insert into fpc_playevent values(%s,%s,%s,%s,%s,%s,%s)',(util.util_get_uuid(),e.midiaId,e.startTime,e.endTime,e.fpcIp,e.fpcMac,e.event))
		except:
			self._server._logger.Debug('ReportMideaPlayEvent:: <%s>'%traceback.print_exc())
		self._server.FreeDBConn(conn)
	
	def GetFtpServer(self,ctx):
		ftp = FtpServer()
		ftp.host = self._server._cnf['ftp_host']
		ftp.port = self._server._cnf['ftp_port']
		ftp.user = self._server._cnf['ftp_user']
		ftp.passwd = self._server._cnf['ftp_passwd']
		return ftp
	
class MainApp(Ice.Application):
	def __init__(self):
		self._cms=None		
		self._adp_cms = None	
		self._logger = Logger('CMS')
		self._lock_dbconn = threading.Lock()
		self._dbconn=None
		self._cnf ={}
		self._properties=None;
	
	def	IsFilePlayer(self,player):
		try:
			FILE_PLAYERS.index(player)
		except:
			return False
		return True
	
	def GetDBConn(self):
		self._lock_dbconn.acquire()
		return self._dbconn
	
	def GetSysSetting(self,cat,key):
		''' return value'''
		ret=''
		c =self.GetDBConn()
		try:
			cur = c.cursor()
			cur.execute('select value from sys_setting where category=%s and key_name=%s',(cat,key))
			rs = cur.fetchall()
			if len(rs):
				ret = rs[0]['value']
		except:
			pass
		self.FreeDBConn(c)
		return ret
	
	def FreeDBConn(self,conn=None):
		self._lock_dbconn.release()
		
	def init(self):
		try:
			self._properties = self.communicator().getProperties();
			self._cnf['db_name']=self.communicator().getProperties().getProperty('cms.db.name')
			self._cnf['db_host']=self.communicator().getProperties().getProperty('cms.db.host')
			self._cnf['db_user']=self.communicator().getProperties().getProperty('cms.db.user')
			self._cnf['db_passwd']=self.communicator().getProperties().getProperty('cms.db.passwd')
			self._cnf['media_dir']=self.communicator().getProperties().getProperty('cms.media_dir')
			self._cnf['log_udp_host']=self.communicator().getProperties().getProperty('cms.log.udp.host')
			self._cnf['log_udp_port']=self.communicator().getProperties().getProperty('cms.log.udp.port')
			self._cnf['cms_endpoints'] = self.communicator().getProperties().getProperty('cms.Endpoints')
			self._cnf['log_file_name']=self.communicator().getProperties().getProperty('cms.log.file.name')
			self._cnf['product.release']=self.communicator().getProperties().getProperty('product.release')
			self._cnf['ftp_host'] =self.communicator().getProperties().getProperty('cms.ftp.host')
			self._cnf['ftp_port'] =self.communicator().getProperties().getProperty('cms.ftp.port')
			self._cnf['ftp_user']=self.communicator().getProperties().getProperty('cms.ftp.user')
			self._cnf['ftp_passwd']=self.communicator().getProperties().getProperty('cms.ftp.passwd')
			self._cnf['fdc_sync_time']=self.communicator().getProperties().getPropertyAsIntWithDefault('fdc.sync_time',10*60)	#60 minutes
			self._cnf['media_url']=self._properties.getProperty('cms.media_url')
			print self._cnf
			## connect system database
			if not self.ConnectDB():
				self._logger.Debug('connect db failed!')
				return False
			self._logger.SetLogUdp(self._cnf['log_udp_host'],self._cnf['log_udp_port'])
			self._logger.SetLogFile('cms.log')
		except:
			self._logger.Error(traceback.print_exc())
			print False
		return True
		
	
	def ConnectDB(self):
		try:
			self._dbconn = MySQLdb.Connect(host=self._cnf['db_host'],user=self._cnf['db_user'],
						passwd=self._cnf['db_passwd'],cursorclass=MySQLdb.cursors.DictCursor)
			self._dbconn.select_db(self._cnf['db_name'])
		except:
			self._logger.Error('connect db failed! msg:%s'%traceback.print_exc())
			return False
		return True
	
	def run(self,argv):
		try:
			
			if not self.init():
				return -1
			self._adp_cms = self.communicator().createObjectAdapter("cms")
			self._cms = self._adp_cms.add(cmsI(self),Ice.stringToIdentity("cms"))
			self._adp_cms.activate()
			self.shutdownOnInterrupt()
			self._logger.Debug("cms start up")
			self.communicator().waitForShutdown()
		except:
			self._logger.Error(traceback.print_exc())
		return 0
		
	def GetFdcIDByAddress(self,remote):
		ret =''
		c = self.GetDBConn()
		try:
			c = self._dbconn.cursor()
			sql = "select * from fdc where ip='%s'"%remote.strip()
			c.execute(sql)
			rs = c.fetchall()
			if len(rs):
				ret =  rs[0]['ID']
		except:
			self._logger.Error(traceback.print_exc())
		self.FreeDBConn(c)
		return ret
		
		
	def GetMediaControlInfo(self, event):
			
		return []
	
	def GetFPCSettings(self):
		settings = fpcSetting()
		return settings
##################################################
	
app = MainApp()
sys.exit(app.main(sys.argv,"cms.conf"))
