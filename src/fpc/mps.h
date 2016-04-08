// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.0.1
// Generated from file `mps.ice'

#ifndef _____fpc_mps_h__
#define _____fpc_mps_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/Identity.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 300
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace MPMS
{

class FrontPlayController;
bool operator==(const FrontPlayController&, const FrontPlayController&);
bool operator!=(const FrontPlayController&, const FrontPlayController&);
bool operator<(const FrontPlayController&, const FrontPlayController&);

class FrontDispatchController;
bool operator==(const FrontDispatchController&, const FrontDispatchController&);
bool operator!=(const FrontDispatchController&, const FrontDispatchController&);
bool operator<(const FrontDispatchController&, const FrontDispatchController&);

class CentreMangementSystem;
bool operator==(const CentreMangementSystem&, const CentreMangementSystem&);
bool operator!=(const CentreMangementSystem&, const CentreMangementSystem&);
bool operator<(const CentreMangementSystem&, const CentreMangementSystem&);

}

}

namespace MPMS
{

class FrontPlayController;
bool operator==(const FrontPlayController&, const FrontPlayController&);
bool operator!=(const FrontPlayController&, const FrontPlayController&);
bool operator<(const FrontPlayController&, const FrontPlayController&);

class FrontDispatchController;
bool operator==(const FrontDispatchController&, const FrontDispatchController&);
bool operator!=(const FrontDispatchController&, const FrontDispatchController&);
bool operator<(const FrontDispatchController&, const FrontDispatchController&);

class CentreMangementSystem;
bool operator==(const CentreMangementSystem&, const CentreMangementSystem&);
bool operator!=(const CentreMangementSystem&, const CentreMangementSystem&);
bool operator<(const CentreMangementSystem&, const CentreMangementSystem&);

}

namespace IceInternal
{

void incRef(::MPMS::FrontPlayController*);
void decRef(::MPMS::FrontPlayController*);

void incRef(::IceProxy::MPMS::FrontPlayController*);
void decRef(::IceProxy::MPMS::FrontPlayController*);

void incRef(::MPMS::FrontDispatchController*);
void decRef(::MPMS::FrontDispatchController*);

void incRef(::IceProxy::MPMS::FrontDispatchController*);
void decRef(::IceProxy::MPMS::FrontDispatchController*);

void incRef(::MPMS::CentreMangementSystem*);
void decRef(::MPMS::CentreMangementSystem*);

void incRef(::IceProxy::MPMS::CentreMangementSystem*);
void decRef(::IceProxy::MPMS::CentreMangementSystem*);

}

namespace MPMS
{

typedef ::IceInternal::Handle< ::MPMS::FrontPlayController> FrontPlayControllerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::MPMS::FrontPlayController> FrontPlayControllerPrx;

void __write(::IceInternal::BasicStream*, const FrontPlayControllerPrx&);
void __read(::IceInternal::BasicStream*, FrontPlayControllerPrx&);
void __write(::IceInternal::BasicStream*, const FrontPlayControllerPtr&);
void __patch__FrontPlayControllerPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::MPMS::FrontDispatchController> FrontDispatchControllerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::MPMS::FrontDispatchController> FrontDispatchControllerPrx;

void __write(::IceInternal::BasicStream*, const FrontDispatchControllerPrx&);
void __read(::IceInternal::BasicStream*, FrontDispatchControllerPrx&);
void __write(::IceInternal::BasicStream*, const FrontDispatchControllerPtr&);
void __patch__FrontDispatchControllerPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::MPMS::CentreMangementSystem> CentreMangementSystemPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::MPMS::CentreMangementSystem> CentreMangementSystemPrx;

void __write(::IceInternal::BasicStream*, const CentreMangementSystemPrx&);
void __read(::IceInternal::BasicStream*, CentreMangementSystemPrx&);
void __write(::IceInternal::BasicStream*, const CentreMangementSystemPtr&);
void __patch__CentreMangementSystemPtr(void*, ::Ice::ObjectPtr&);

}

namespace MPMS
{

struct fpcControlInfo
{
    ::Ice::Int policySyncTime;

    bool operator==(const fpcControlInfo&) const;
    bool operator!=(const fpcControlInfo&) const;
    bool operator<(const fpcControlInfo&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct MediaControlInfo
{
    ::std::string id;
    ::std::string name;
    ::std::string url;
    ::std::string player;
    ::Ice::Int width;
    ::Ice::Int height;

    bool operator==(const MediaControlInfo&) const;
    bool operator!=(const MediaControlInfo&) const;
    bool operator<(const MediaControlInfo&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::MPMS::MediaControlInfo> MediaControlInfoList;

class __U__MediaControlInfoList { };
void __write(::IceInternal::BasicStream*, const MediaControlInfoList&, __U__MediaControlInfoList);
void __read(::IceInternal::BasicStream*, MediaControlInfoList&, __U__MediaControlInfoList);

struct IEToolbarControlInfo
{
    ::MPMS::MediaControlInfoList mciList;

    bool operator==(const IEToolbarControlInfo&) const;
    bool operator!=(const IEToolbarControlInfo&) const;
    bool operator<(const IEToolbarControlInfo&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct fdcParameter
{
    ::std::string id;
    ::std::string gateway;

    bool operator==(const fdcParameter&) const;
    bool operator!=(const fdcParameter&) const;
    bool operator<(const fdcParameter&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct fpcSetting
{
    ::std::string ieDefaultAddr;
    ::std::string wallpaper;
    ::MPMS::IEToolbarControlInfo ieToolbar;
    ::MPMS::MediaControlInfo alNotification;
    ::MPMS::MediaControlInfo alAdvertisement;
    ::MPMS::MediaControlInfo qq;
    ::MPMS::MediaControlInfo msn;

    bool operator==(const fpcSetting&) const;
    bool operator!=(const fpcSetting&) const;
    bool operator<(const fpcSetting&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct fpcParameter
{
    ::std::string ip;
    ::std::string mac;

    bool operator==(const fpcParameter&) const;
    bool operator!=(const fpcParameter&) const;
    bool operator<(const fpcParameter&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::MPMS::fpcParameter> fpcParameterList;

class __U__fpcParameterList { };
void __write(::IceInternal::BasicStream*, const fpcParameterList&, __U__fpcParameterList);
void __read(::IceInternal::BasicStream*, fpcParameterList&, __U__fpcParameterList);

typedef ::std::vector<bool> WeekDayEnable;

struct PolicyTime
{
    ::Ice::Int stime;
    ::Ice::Int etime;
    ::std::string weekday;
    ::Ice::Int shour;
    ::Ice::Int ehour;

    bool operator==(const PolicyTime&) const;
    bool operator!=(const PolicyTime&) const;
    bool operator<(const PolicyTime&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct PlayPolicy
{
    ::MPMS::PolicyTime pTime;
    ::MPMS::fpcSetting fpcs;

    bool operator==(const PlayPolicy&) const;
    bool operator!=(const PlayPolicy&) const;
    bool operator<(const PlayPolicy&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::MPMS::PlayPolicy> PlayPolicyList;

class __U__PlayPolicyList { };
void __write(::IceInternal::BasicStream*, const PlayPolicyList&, __U__PlayPolicyList);
void __read(::IceInternal::BasicStream*, PlayPolicyList&, __U__PlayPolicyList);

struct fpcCatchedEvent
{
    ::std::string app;
    ::std::string fpcType;

    bool operator==(const fpcCatchedEvent&) const;
    bool operator!=(const fpcCatchedEvent&) const;
    bool operator<(const fpcCatchedEvent&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::Ice::Byte> ByteList;

struct NetFile
{
    ::std::string file;
    ::std::string instdir;

    bool operator==(const NetFile&) const;
    bool operator!=(const NetFile&) const;
    bool operator<(const NetFile&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::MPMS::NetFile> NetFileList;

class __U__NetFileList { };
void __write(::IceInternal::BasicStream*, const NetFileList&, __U__NetFileList);
void __read(::IceInternal::BasicStream*, NetFileList&, __U__NetFileList);

struct EventMediaPlay
{
    ::std::string midiaId;
    ::std::string event;
    ::std::string fpcIp;
    ::std::string fpcMac;
    ::Ice::Int startTime;
    ::Ice::Int endTime;

    bool operator==(const EventMediaPlay&) const;
    bool operator!=(const EventMediaPlay&) const;
    bool operator<(const EventMediaPlay&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::MPMS::EventMediaPlay> EventMediaPlayList;

class __U__EventMediaPlayList { };
void __write(::IceInternal::BasicStream*, const EventMediaPlayList&, __U__EventMediaPlayList);
void __read(::IceInternal::BasicStream*, EventMediaPlayList&, __U__EventMediaPlayList);

struct FtpServer
{
    ::std::string host;
    ::std::string port;
    ::std::string user;
    ::std::string passwd;

    bool operator==(const FtpServer&) const;
    bool operator!=(const FtpServer&) const;
    bool operator<(const FtpServer&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct SystemDistribution
{
    ::std::string subsys;
    ::std::string version;
    ::MPMS::NetFileList fileList;

    bool operator==(const SystemDistribution&) const;
    bool operator!=(const SystemDistribution&) const;
    bool operator<(const SystemDistribution&) const;

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

}

namespace IceProxy
{

namespace MPMS
{

class FrontPlayController : virtual public ::IceProxy::Ice::Object
{
public:

    void ChangeSetting(const ::MPMS::fpcSetting&);
    void ChangeSetting(const ::MPMS::fpcSetting&, const ::Ice::Context&);

    ::std::string GetType();
    ::std::string GetType(const ::Ice::Context&);

    ::MPMS::fpcParameter GetParameter();
    ::MPMS::fpcParameter GetParameter(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class FrontDispatchController : virtual public ::IceProxy::Ice::Object
{
public:

    bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&);
    bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&, const ::Ice::Context&);

    ::MPMS::fpcSetting GetFPCSettings();
    ::MPMS::fpcSetting GetFPCSettings(const ::Ice::Context&);

    ::MPMS::fdcParameter GetParameter();
    ::MPMS::fdcParameter GetParameter(const ::Ice::Context&);

    void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&);
    void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class CentreMangementSystem : virtual public ::IceProxy::MPMS::FrontDispatchController
{
public:

    ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&);
    ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&, const ::Ice::Context&);

    ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&);
    ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&, const ::Ice::Context&);

    bool RegisterFDC(const ::Ice::Identity&);
    bool RegisterFDC(const ::Ice::Identity&, const ::Ice::Context&);

    ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&);
    ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ::MPMS::FtpServer GetFtpServer();
    ::MPMS::FtpServer GetFtpServer(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

namespace IceDelegate
{

namespace MPMS
{

class FrontPlayController : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void ChangeSetting(const ::MPMS::fpcSetting&, const ::Ice::Context&) = 0;

    virtual ::std::string GetType(const ::Ice::Context&) = 0;

    virtual ::MPMS::fpcParameter GetParameter(const ::Ice::Context&) = 0;
};

class FrontDispatchController : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&, const ::Ice::Context&) = 0;

    virtual ::MPMS::fpcSetting GetFPCSettings(const ::Ice::Context&) = 0;

    virtual ::MPMS::fdcParameter GetParameter(const ::Ice::Context&) = 0;

    virtual void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&, const ::Ice::Context&) = 0;
};

class CentreMangementSystem : virtual public ::IceDelegate::MPMS::FrontDispatchController
{
public:

    virtual ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool RegisterFDC(const ::Ice::Identity&, const ::Ice::Context&) = 0;

    virtual ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::MPMS::FtpServer GetFtpServer(const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace MPMS
{

class FrontPlayController : virtual public ::IceDelegate::MPMS::FrontPlayController,
			    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void ChangeSetting(const ::MPMS::fpcSetting&, const ::Ice::Context&);

    virtual ::std::string GetType(const ::Ice::Context&);

    virtual ::MPMS::fpcParameter GetParameter(const ::Ice::Context&);
};

class FrontDispatchController : virtual public ::IceDelegate::MPMS::FrontDispatchController,
				virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&, const ::Ice::Context&);

    virtual ::MPMS::fpcSetting GetFPCSettings(const ::Ice::Context&);

    virtual ::MPMS::fdcParameter GetParameter(const ::Ice::Context&);

    virtual void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&, const ::Ice::Context&);
};

class CentreMangementSystem : virtual public ::IceDelegate::MPMS::CentreMangementSystem,
			      virtual public ::IceDelegateM::MPMS::FrontDispatchController
{
public:

    virtual ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&, const ::Ice::Context&);

    virtual ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&, const ::Ice::Context&);

    virtual bool RegisterFDC(const ::Ice::Identity&, const ::Ice::Context&);

    virtual ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::MPMS::FtpServer GetFtpServer(const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace MPMS
{

class FrontPlayController : virtual public ::IceDelegate::MPMS::FrontPlayController,
			    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void ChangeSetting(const ::MPMS::fpcSetting&, const ::Ice::Context&);

    virtual ::std::string GetType(const ::Ice::Context&);

    virtual ::MPMS::fpcParameter GetParameter(const ::Ice::Context&);
};

class FrontDispatchController : virtual public ::IceDelegate::MPMS::FrontDispatchController,
				virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&, const ::Ice::Context&);

    virtual ::MPMS::fpcSetting GetFPCSettings(const ::Ice::Context&);

    virtual ::MPMS::fdcParameter GetParameter(const ::Ice::Context&);

    virtual void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&, const ::Ice::Context&);
};

class CentreMangementSystem : virtual public ::IceDelegate::MPMS::CentreMangementSystem,
			      virtual public ::IceDelegateD::MPMS::FrontDispatchController
{
public:

    virtual ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&, const ::Ice::Context&);

    virtual ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&, const ::Ice::Context&);

    virtual bool RegisterFDC(const ::Ice::Identity&, const ::Ice::Context&);

    virtual ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::MPMS::FtpServer GetFtpServer(const ::Ice::Context&);
};

}

}

namespace MPMS
{

class FrontPlayController : virtual public ::Ice::Object
{
public:

    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void ChangeSetting(const ::MPMS::fpcSetting&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ChangeSetting(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::fpcParameter GetParameter(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetParameter(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__FrontPlayControllerPtr(void*, ::Ice::ObjectPtr&);

class FrontDispatchController : virtual public ::Ice::Object
{
public:

    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool RegisterFPC(const ::Ice::Identity&, const ::MPMS::fpcParameter&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RegisterFPC(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::fpcSetting GetFPCSettings(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetFPCSettings(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::fdcParameter GetParameter(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetParameter(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void ReportMideaPlayEvent(const ::std::string&, const ::MPMS::EventMediaPlayList&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ReportMideaPlayEvent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__FrontDispatchControllerPtr(void*, ::Ice::ObjectPtr&);

class CentreMangementSystem : virtual public ::MPMS::FrontDispatchController
{
public:

    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::MPMS::PlayPolicyList GetPlayPolicies(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPlayPolicies(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::fpcControlInfo GetfpcControlInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetfpcControlInfo(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RegisterFDC(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RegisterFDC(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::SystemDistribution SyncSystem(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SyncSystem(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::MPMS::FtpServer GetFtpServer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetFtpServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__CentreMangementSystemPtr(void*, ::Ice::ObjectPtr&);

}

#endif
