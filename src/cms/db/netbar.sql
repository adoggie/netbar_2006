/*
MySQL Backup
Source Host:           localhost
Source Server Version: 5.0.16
Source Database:       mpms
Date:                  2006-05-21 17:52:55
*/

use mpms;
SET FOREIGN_KEY_CHECKS=0;
#----------------------------
# Table structure for netbar
#----------------------------
CREATE TABLE `netbar` (
  `ID` varchar(256) NOT NULL,
  `FDC_ID` varchar(128) NOT NULL,
  `IP_ADDR` varchar(32) default NULL,
  `NAME` varchar(128) default NULL,
  `GROUP_ID` varchar(256) default NULL,
  `CONTROL_POLICY_SYNC_TIME` int(11) default NULL,
  PRIMARY KEY  (`ID`,`FDC_ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
#----------------------------
# Records for table netbar
#----------------------------


insert  into netbar values 
('1', 'fdc1', '192.168.14.10', '≤‚ ‘± º«±æfdc', '1', 10);

