/*
MySQL Backup
Source Host:           localhost
Source Server Version: 5.0.16
Source Database:       mpms
Date:                  2006-05-21 17:53:12
*/

use mpms;
SET FOREIGN_KEY_CHECKS=0;
#----------------------------
# Table structure for policy_media
#----------------------------
CREATE TABLE `policy_media` (
  `POLICY_ID` varchar(256) NOT NULL,
  `MEDIA_ID` char(10) NOT NULL,
  PRIMARY KEY  (`POLICY_ID`,`MEDIA_ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
#----------------------------
# Records for table policy_media
#----------------------------


insert  into policy_media values 
('1', '5'), 
('2', '6'), 
('3', '1'), 
('3', '2'), 
('4', '4'), 
('5', '3');

