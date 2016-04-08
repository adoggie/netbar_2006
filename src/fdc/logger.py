
import time,sys,os,traceback,threading,copy,datetime
import socket
import win32gui

class Logger:
	def __init__(self,app=''):
		self._file=None
		self._udp =None
		self._dest=None
		self._win=''
		self._app = app
		self._lock = threading.Lock()
	
	def SetLogUdp(self,host,port):
		self._udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		self._dest = (host,int(port))
	def SetLogWindow(self,win):
		self._win = win
	def SetLogFile(self,name):
		self._file = open(name,'a')
		self._lock = threading.Lock()
	def Debug(self,msg):
		self.Write('DEBUG '+msg)
	def Warning(self,msg):
		self.Write('WARNING '+msg)
	def Error(self,msg):
		self.Write('ERROR '+ msg)
		
	def Write(self,msg):
		self._lock.acquire()
		try:			
			now = time.localtime()
			msg=self._app+' '+msg
			msg = "%s-%s-%s %s:%s:%s  "%(now[0],now[1],now[2],now[3],now[4],now[5])+msg
			print msg
			if self._file:							
				self._file.write(msg+"\n")			
			if self._udp:
				self._udp.sendto(msg,self._dest)			
			if self._win:
				try:
					pass
					#w = win32gui.FindWindow(None,self._win)					
				except:
					pass
		except:
			print traceback.print_exc()
		self._lock.release()