/*==============================================================*/
/* Database name:  PhysicalDataModel_1                          */
/* DBMS name:      MySQL 3.23                                   */
/* Created on:     2006-5-25 16:13:34                           */
/*==============================================================*/


drop table if exists SYS_USER;

drop table if exists SYS_SETTING;

drop table if exists SYS_ROLE_RIGHT;

drop table if exists SYS_ROLE;

drop table if exists SYS_RIGHTS;

drop table if exists PRODUCT_RELEASE;

drop table if exists POLICY_MEDIA;

drop table if exists POLICY;

drop table if exists MEDIA;

drop table if exists FPC_PLAYEVENT;

drop table if exists FPC;

drop table if exists FDC_POLICY;

drop table if exists FDC_GROUP;

drop table if exists FDC;

/*==============================================================*/
/* Table: FDC                                                   */
/*==============================================================*/
create table if not exists FDC
(
   ID                             varchar(128)                   not null,
   FDC_ID                         varchar(128),
   IP                             varchar(32),
   NAME                           varchar(128),
   GROUP_ID                       varchar(128),
   ADMIN                          varchar(32),
   TEL                            varchar(128),
   ADDR                           TEXT,
   primary key (ID)
);

/*==============================================================*/
/* Table: FDC_GROUP                                             */
/*==============================================================*/
create table if not exists FDC_GROUP
(
   ID                             varchar(128)                   not null,
   NAME                           TEXT,
   DESCRIPTION                    TEXT,
   primary key (ID)
);

/*==============================================================*/
/* Table: FDC_POLICY                                            */
/*==============================================================*/
create table if not exists FDC_POLICY
(
   FDC_ID                         varchar(128)                   not null,
   POLICY_ID                      varchar(128)                   not null,
   primary key (FDC_ID, POLICY_ID)
);

/*==============================================================*/
/* Table: FPC                                                   */
/*==============================================================*/
create table if not exists FPC
(
   ID                             varchar(128)                   not null,
   FDC_ID                         varchar(128),
   IP                             varchar(32),
   MAC                            varchar(32),
   primary key (ID)
);

/*==============================================================*/
/* Table: FPC_PLAYEVENT                                         */
/*==============================================================*/
create table if not exists FPC_PLAYEVENT
(
   ID                             varchar(128)                   not null,
   MID                            varchar(128),
   STIME                          int,
   ETIME                          int,
   FPC_IP                         varchar(32),
   FPC_MAC                        varchar(32),
   EVENT                          varchar(32),
   primary key (ID)
);

/*==============================================================*/
/* Table: MEDIA                                                 */
/*==============================================================*/
create table if not exists MEDIA
(
   ID                             varchar(128)                   not null,
   URL                            TEXT,
   NAME                           TEXT,
   PLAYER                         varchar(32),
   WIDTH                          INT,
   HEIGHT                         INT,
   AUTO_NAME                      TEXT,
   CTIME                          INT,
   primary key (ID)
);

/*==============================================================*/
/* Table: POLICY                                                */
/*==============================================================*/
create table if not exists POLICY
(
   ID                             varchar(128)                   not null,
   NAME                           text,
   _STATUS                        int,
   START_TIME                     int,
   END_TIME                       INT,
   WEEKDAY                        varchar(16),
   START_HOUR                     int,
   END_HOUR                       int,
   FPC_IE_DEFAULT_ADDR            TEXT,
   FPC_BG                         TEXT,
   FPC_IE_TOOLBAR                 TEXT,
   FPC_AFTER_LOGIN                TEXT,
   FPC_MSN_LOGIN                  TEXT,
   FPC_QQ_LOGIN                   TEXT,
   primary key (ID)
);

/*==============================================================*/
/* Table: POLICY_MEDIA                                          */
/*==============================================================*/
create table if not exists POLICY_MEDIA
(
   POLICY_ID                      varchar(128)                   not null,
   MEDIA_ID                       varchar(128)                   not null,
   primary key (POLICY_ID, MEDIA_ID)
);

/*==============================================================*/
/* Table: PRODUCT_RELEASE                                       */
/*==============================================================*/
create table if not exists PRODUCT_RELEASE
(
   ID                             int                            not null,
   SYSTEM                         varchar(128),
   VERSION                        varchar(32),
   MODULE_FILE                    TEXT,
   INST_PATH                      TEXT,
   primary key (ID)
);

/*==============================================================*/
/* Table: SYS_RIGHTS                                            */
/*==============================================================*/
create table if not exists SYS_RIGHTS
(
   ID                             INT                            not null,
   NAME                           TEXT,
   primary key (ID)
);

/*==============================================================*/
/* Table: SYS_ROLE                                              */
/*==============================================================*/
create table if not exists SYS_ROLE
(
   ID                             INT                            not null,
   NAME                           varchar(32)                    not null,
   primary key (ID, NAME)
);

/*==============================================================*/
/* Table: SYS_ROLE_RIGHT                                        */
/*==============================================================*/
create table if not exists SYS_ROLE_RIGHT
(
   ROLE_ID                        INT                            not null,
   RIGHT_ID                       INT                            not null,
   primary key (ROLE_ID, RIGHT_ID)
);

/*==============================================================*/
/* Table: SYS_SETTING                                           */
/*==============================================================*/
create table if not exists SYS_SETTING
(
   CATEGORY                       varchar(32)                    not null,
   KEY_NAME                       varchar(32)                    not null,
   VALUE                          TEXT,
   primary key (CATEGORY, KEY_NAME)
);

/*==============================================================*/
/* Table: SYS_USER                                              */
/*==============================================================*/
create table if not exists SYS_USER
(
   ID                             varchar(128)                   not null,
   USER                           varchar(32)                    not null,
   NAME                           varchar(32),
   PASSWD                         varchar(32),
   ROLE_ID                        int,
   TEL                            varchar(32),
   CONTACT                        TEXT,
   primary key (ID, USER)
);

