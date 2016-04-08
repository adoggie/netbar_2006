/*
MySQL Backup
Source Host:           localhost
Source Server Version: 5.0.16
Source Database:       mpms
Date:                  2006-05-21 17:53:03
*/

use mpms;
SET FOREIGN_KEY_CHECKS=0;
#----------------------------
# Table structure for fdc_policy
#----------------------------
CREATE TABLE `fdc_policy` (
  `FDC_ID` varchar(256) NOT NULL,
  `POLICY_ID` varchar(256) NOT NULL,
  PRIMARY KEY  (`FDC_ID`,`POLICY_ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
#----------------------------
# Records for table fdc_policy
#----------------------------


insert  into fdc_policy values 
('1', '1');

