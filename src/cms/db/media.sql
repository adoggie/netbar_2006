/*
MySQL Backup
Source Host:           localhost
Source Server Version: 5.0.16
Source Database:       mpms
Date:                  2006-05-21 17:53:26
*/

use mpms;
SET FOREIGN_KEY_CHECKS=0;
#----------------------------
# Table structure for media
#----------------------------
CREATE TABLE `media` (
  `ID` varchar(256) NOT NULL,
  `URL` varchar(512) default NULL,
  `NAME` varchar(512) default NULL,
  `PLAYER` varchar(32) default NULL,
  `WIDTH` int(11) default NULL,
  `HEIGHT` int(11) default NULL,
  `AUTO_NAME` varchar(256) default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
#----------------------------
# Records for table media
#----------------------------


insert  into media values 
('1', 'www.google.com', 'google��ҳ', 'ie', 400, 400, null), 
('2', 'www.baidu.com', '�ڶ���ҳ', 'ie', 400, 400, null), 
('3', 'abc.mpg', '����Ƭ', 'mp', 400, 400, 'auto_abc.mpg'), 
('4', 'www.gnu.org', '��Դ����gnu.org', 'ie', 400, 400, null), 
('5', 'http://news.baidu.com/', '�ڶ�����', 'ie', 400, 400, null), 
('6', 'desktop.bmp', '���汳��ͼ', 'mp', 0, 0, 'desktop.bmp');

