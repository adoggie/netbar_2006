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
	''' ͬ��ftp�ļ�������
	֧���ļ��б��ģʽ�б�
	ͨ���ļ���С�������Ƿ����ظ���
	'''
	def __init__(self,entry,**args):
		''' ���캯��'''
		self._callback = None
		self._en = entry
		if args.has_key('callback'):
			self._callback  = args['callback']
			
		self._ftp = ftplib.FTP(self._en['host'],self._en['user'],self._en['passwd'])	#����ftp������
		if self._en['rdir']:
			self.ftp.cwd( self._en['rdir'])			#�л��ļ�Ŀ¼

		if self._en.has_key('files'):				#�б��ļ��Ƿ����,����ʼ����
			if self._en['files']:
				for f in self._en['files']: 
					self.__sync_file(f)	
		self._ftp.close()		

		
	def __sync_file(self,file):	
		sync = False
		self._currfile = self._en['ldir']+'/'+file
		self._handle = open(self._currfile,'wb')	#�򿪱����ļ�
		self._ftp.retrbinary('RETR %s'%file,self.__ftp_recv)
		self._handle.close()
		if self._callback:		#�������,֪ͨ�ⲿʹ����
			self._callback(self._currfile)
		
	def __ftp_recv(self,line):
		'''write data into local file'''
		self._handle.write(line)
