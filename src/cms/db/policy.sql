/*
MySQL Backup
Source Host:           localhost
Source Server Version: 5.0.16
Source Database:       mpms
Date:                  2006-05-21 17:53:20
*/

use mpms;
SET FOREIGN_KEY_CHECKS=0;
#----------------------------
# Table structure for policy
#----------------------------
CREATE TABLE `policy` (
  `ID` varchar(256) NOT NULL,
  `NAME` varchar(256) default NULL,
  `_STATUS` int(11) default NULL,
  `START_TIME` int(11) default NULL,
  `END_TIME` int(11) default NULL,
  `WEEKDAY` varchar(7) default NULL,
  `START_HOUR` int(11) default NULL,
  `END_HOUR` int(11) default NULL,
  `FPC_IE_DEFAULT_ADDR` varchar(256) default NULL,
  `FPC_BG` varchar(256) default NULL,
  `FPC_IE_TOOLBAR` varchar(256) default NULL,
  `FPC_AFTER_LOGIN` varchar(256) default NULL,
  `FPC_MSN_LOGIN` varchar(256) default NULL,
  `FPC_QQ_LOGIN` varchar(256) default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
#----------------------------
# Records for table policy
#----------------------------


insert  into policy values 
('1', 'policy_001', 1, 1048145991, 1948145991, '1111111', 0, 24, '1', '2', '3', '4', '5', '5');

