# -*- coding: gb2312 -*-


'''
summary	:	
author 	:	zhangbin
date	:	2006.03.04
company	:	ultrapower.com.cn
'''

import os
import sys
import socket
import time
import traceback
import string
import re
import ftplib
import os.path

class SyncFtp:
	''' 同步ftp文件到本地
	支持文件列表和模式列表
	通过文件大小检查决定是否下载更新
	'''
	def __init__(self,entry,**args):
		''' 构造函数'''
		self._callback = None
		self._en = entry
		if args.has_key('callback'):
			self._callback  = args['callback']
			
		self._ftp = ftplib.FTP(self._en['host'],self._en['user'],self._en['passwd'])	#连接ftp服务器
		if self._en['rdir']:
			self.ftp.cwd( self._en['rdir'])			#切换文件目录

		if self._en.has_key('files'):				#判别文件是否存在,并开始下载
			if self._en['files']:
				for f in self._en['files']: 
					self.__sync_file(f)	
		self._ftp.close()		

		
	def __sync_file(self,file):	
		sync = False
		self._currfile = self._en['ldir']+'/'+file
		self._handle = open(self._currfile,'wb')	#打开本地文件
		self._ftp.retrbinary('RETR %s'%file,self.__ftp_recv)
		self._handle.close()
		if self._callback:		#完成下载,通知外部使用者
			self._callback(self._currfile)
		
	def __ftp_recv(self,line):
		'''write data into local file'''
		self._handle.write(line)
