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

#include "mps.h"
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 300
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

void
IceInternal::incRef(::MPMS::FrontPlayController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::MPMS::FrontPlayController* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::MPMS::FrontPlayController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::MPMS::FrontPlayController* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::MPMS::FrontDispatchController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::MPMS::FrontDispatchController* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::MPMS::FrontDispatchController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::MPMS::FrontDispatchController* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::MPMS::CentreMangementSystem* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::MPMS::CentreMangementSystem* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::MPMS::CentreMangementSystem* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::MPMS::CentreMangementSystem* p)
{
    p->__decRef();
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::FrontPlayControllerPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::FrontPlayControllerPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::MPMS::FrontPlayController;
	v->__copyFrom(proxy);
    }
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::FrontPlayControllerPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::FrontDispatchControllerPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::FrontDispatchControllerPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::MPMS::FrontDispatchController;
	v->__copyFrom(proxy);
    }
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::FrontDispatchControllerPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::CentreMangementSystemPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::CentreMangementSystemPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::MPMS::CentreMangementSystem;
	v->__copyFrom(proxy);
    }
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::CentreMangementSystemPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

bool
MPMS::fpcControlInfo::operator==(const fpcControlInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::fpcControlInfo::operator!=(const fpcControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(policySyncTime != __rhs.policySyncTime)
    {
	return true;
    }
    return false;
}

bool
MPMS::fpcControlInfo::operator<(const fpcControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(policySyncTime < __rhs.policySyncTime)
    {
	return true;
    }
    else if(__rhs.policySyncTime < policySyncTime)
    {
	return false;
    }
    return false;
}

void
MPMS::fpcControlInfo::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(policySyncTime);
}

void
MPMS::fpcControlInfo::__read(::IceInternal::BasicStream* __is)
{
    __is->read(policySyncTime);
}

bool
MPMS::MediaControlInfo::operator==(const MediaControlInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::MediaControlInfo::operator!=(const MediaControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id != __rhs.id)
    {
	return true;
    }
    if(name != __rhs.name)
    {
	return true;
    }
    if(url != __rhs.url)
    {
	return true;
    }
    if(player != __rhs.player)
    {
	return true;
    }
    if(width != __rhs.width)
    {
	return true;
    }
    if(height != __rhs.height)
    {
	return true;
    }
    return false;
}

bool
MPMS::MediaControlInfo::operator<(const MediaControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id < __rhs.id)
    {
	return true;
    }
    else if(__rhs.id < id)
    {
	return false;
    }
    if(name < __rhs.name)
    {
	return true;
    }
    else if(__rhs.name < name)
    {
	return false;
    }
    if(url < __rhs.url)
    {
	return true;
    }
    else if(__rhs.url < url)
    {
	return false;
    }
    if(player < __rhs.player)
    {
	return true;
    }
    else if(__rhs.player < player)
    {
	return false;
    }
    if(width < __rhs.width)
    {
	return true;
    }
    else if(__rhs.width < width)
    {
	return false;
    }
    if(height < __rhs.height)
    {
	return true;
    }
    else if(__rhs.height < height)
    {
	return false;
    }
    return false;
}

void
MPMS::MediaControlInfo::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(id);
    __os->write(name);
    __os->write(url);
    __os->write(player);
    __os->write(width);
    __os->write(height);
}

void
MPMS::MediaControlInfo::__read(::IceInternal::BasicStream* __is)
{
    __is->read(id);
    __is->read(name);
    __is->read(url);
    __is->read(player);
    __is->read(width);
    __is->read(height);
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::MediaControlInfoList& v, ::MPMS::__U__MediaControlInfoList)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::MPMS::MediaControlInfoList::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
	(*p).__write(__os);
    }
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::MediaControlInfoList& v, ::MPMS::__U__MediaControlInfoList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 12);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}

bool
MPMS::IEToolbarControlInfo::operator==(const IEToolbarControlInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::IEToolbarControlInfo::operator!=(const IEToolbarControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(mciList != __rhs.mciList)
    {
	return true;
    }
    return false;
}

bool
MPMS::IEToolbarControlInfo::operator<(const IEToolbarControlInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(mciList < __rhs.mciList)
    {
	return true;
    }
    else if(__rhs.mciList < mciList)
    {
	return false;
    }
    return false;
}

void
MPMS::IEToolbarControlInfo::__write(::IceInternal::BasicStream* __os) const
{
    ::MPMS::__write(__os, mciList, ::MPMS::__U__MediaControlInfoList());
}

void
MPMS::IEToolbarControlInfo::__read(::IceInternal::BasicStream* __is)
{
    ::MPMS::__read(__is, mciList, ::MPMS::__U__MediaControlInfoList());
}

bool
MPMS::fdcParameter::operator==(const fdcParameter& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::fdcParameter::operator!=(const fdcParameter& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id != __rhs.id)
    {
	return true;
    }
    if(gateway != __rhs.gateway)
    {
	return true;
    }
    return false;
}

bool
MPMS::fdcParameter::operator<(const fdcParameter& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id < __rhs.id)
    {
	return true;
    }
    else if(__rhs.id < id)
    {
	return false;
    }
    if(gateway < __rhs.gateway)
    {
	return true;
    }
    else if(__rhs.gateway < gateway)
    {
	return false;
    }
    return false;
}

void
MPMS::fdcParameter::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(id);
    __os->write(gateway);
}

void
MPMS::fdcParameter::__read(::IceInternal::BasicStream* __is)
{
    __is->read(id);
    __is->read(gateway);
}

bool
MPMS::fpcSetting::operator==(const fpcSetting& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::fpcSetting::operator!=(const fpcSetting& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(ieDefaultAddr != __rhs.ieDefaultAddr)
    {
	return true;
    }
    if(wallpaper != __rhs.wallpaper)
    {
	return true;
    }
    if(ieToolbar != __rhs.ieToolbar)
    {
	return true;
    }
    if(alNotification != __rhs.alNotification)
    {
	return true;
    }
    if(alAdvertisement != __rhs.alAdvertisement)
    {
	return true;
    }
    if(qq != __rhs.qq)
    {
	return true;
    }
    if(msn != __rhs.msn)
    {
	return true;
    }
    return false;
}

bool
MPMS::fpcSetting::operator<(const fpcSetting& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(ieDefaultAddr < __rhs.ieDefaultAddr)
    {
	return true;
    }
    else if(__rhs.ieDefaultAddr < ieDefaultAddr)
    {
	return false;
    }
    if(wallpaper < __rhs.wallpaper)
    {
	return true;
    }
    else if(__rhs.wallpaper < wallpaper)
    {
	return false;
    }
    if(ieToolbar < __rhs.ieToolbar)
    {
	return true;
    }
    else if(__rhs.ieToolbar < ieToolbar)
    {
	return false;
    }
    if(alNotification < __rhs.alNotification)
    {
	return true;
    }
    else if(__rhs.alNotification < alNotification)
    {
	return false;
    }
    if(alAdvertisement < __rhs.alAdvertisement)
    {
	return true;
    }
    else if(__rhs.alAdvertisement < alAdvertisement)
    {
	return false;
    }
    if(qq < __rhs.qq)
    {
	return true;
    }
    else if(__rhs.qq < qq)
    {
	return false;
    }
    if(msn < __rhs.msn)
    {
	return true;
    }
    else if(__rhs.msn < msn)
    {
	return false;
    }
    return false;
}

void
MPMS::fpcSetting::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(ieDefaultAddr);
    __os->write(wallpaper);
    ieToolbar.__write(__os);
    alNotification.__write(__os);
    alAdvertisement.__write(__os);
    qq.__write(__os);
    msn.__write(__os);
}

void
MPMS::fpcSetting::__read(::IceInternal::BasicStream* __is)
{
    __is->read(ieDefaultAddr);
    __is->read(wallpaper);
    ieToolbar.__read(__is);
    alNotification.__read(__is);
    alAdvertisement.__read(__is);
    qq.__read(__is);
    msn.__read(__is);
}

bool
MPMS::fpcParameter::operator==(const fpcParameter& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::fpcParameter::operator!=(const fpcParameter& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(ip != __rhs.ip)
    {
	return true;
    }
    if(mac != __rhs.mac)
    {
	return true;
    }
    return false;
}

bool
MPMS::fpcParameter::operator<(const fpcParameter& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(ip < __rhs.ip)
    {
	return true;
    }
    else if(__rhs.ip < ip)
    {
	return false;
    }
    if(mac < __rhs.mac)
    {
	return true;
    }
    else if(__rhs.mac < mac)
    {
	return false;
    }
    return false;
}

void
MPMS::fpcParameter::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(ip);
    __os->write(mac);
}

void
MPMS::fpcParameter::__read(::IceInternal::BasicStream* __is)
{
    __is->read(ip);
    __is->read(mac);
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::fpcParameterList& v, ::MPMS::__U__fpcParameterList)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::MPMS::fpcParameterList::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
	(*p).__write(__os);
    }
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::fpcParameterList& v, ::MPMS::__U__fpcParameterList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 2);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}

bool
MPMS::PolicyTime::operator==(const PolicyTime& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::PolicyTime::operator!=(const PolicyTime& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(stime != __rhs.stime)
    {
	return true;
    }
    if(etime != __rhs.etime)
    {
	return true;
    }
    if(weekday != __rhs.weekday)
    {
	return true;
    }
    if(shour != __rhs.shour)
    {
	return true;
    }
    if(ehour != __rhs.ehour)
    {
	return true;
    }
    return false;
}

bool
MPMS::PolicyTime::operator<(const PolicyTime& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(stime < __rhs.stime)
    {
	return true;
    }
    else if(__rhs.stime < stime)
    {
	return false;
    }
    if(etime < __rhs.etime)
    {
	return true;
    }
    else if(__rhs.etime < etime)
    {
	return false;
    }
    if(weekday < __rhs.weekday)
    {
	return true;
    }
    else if(__rhs.weekday < weekday)
    {
	return false;
    }
    if(shour < __rhs.shour)
    {
	return true;
    }
    else if(__rhs.shour < shour)
    {
	return false;
    }
    if(ehour < __rhs.ehour)
    {
	return true;
    }
    else if(__rhs.ehour < ehour)
    {
	return false;
    }
    return false;
}

void
MPMS::PolicyTime::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(stime);
    __os->write(etime);
    __os->write(weekday);
    __os->write(shour);
    __os->write(ehour);
}

void
MPMS::PolicyTime::__read(::IceInternal::BasicStream* __is)
{
    __is->read(stime);
    __is->read(etime);
    __is->read(weekday);
    __is->read(shour);
    __is->read(ehour);
}

bool
MPMS::PlayPolicy::operator==(const PlayPolicy& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::PlayPolicy::operator!=(const PlayPolicy& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(pTime != __rhs.pTime)
    {
	return true;
    }
    if(fpcs != __rhs.fpcs)
    {
	return true;
    }
    return false;
}

bool
MPMS::PlayPolicy::operator<(const PlayPolicy& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(pTime < __rhs.pTime)
    {
	return true;
    }
    else if(__rhs.pTime < pTime)
    {
	return false;
    }
    if(fpcs < __rhs.fpcs)
    {
	return true;
    }
    else if(__rhs.fpcs < fpcs)
    {
	return false;
    }
    return false;
}

void
MPMS::PlayPolicy::__write(::IceInternal::BasicStream* __os) const
{
    pTime.__write(__os);
    fpcs.__write(__os);
}

void
MPMS::PlayPolicy::__read(::IceInternal::BasicStream* __is)
{
    pTime.__read(__is);
    fpcs.__read(__is);
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::PlayPolicyList& v, ::MPMS::__U__PlayPolicyList)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::MPMS::PlayPolicyList::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
	(*p).__write(__os);
    }
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::PlayPolicyList& v, ::MPMS::__U__PlayPolicyList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 68);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}

bool
MPMS::fpcCatchedEvent::operator==(const fpcCatchedEvent& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::fpcCatchedEvent::operator!=(const fpcCatchedEvent& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(app != __rhs.app)
    {
	return true;
    }
    if(fpcType != __rhs.fpcType)
    {
	return true;
    }
    return false;
}

bool
MPMS::fpcCatchedEvent::operator<(const fpcCatchedEvent& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(app < __rhs.app)
    {
	return true;
    }
    else if(__rhs.app < app)
    {
	return false;
    }
    if(fpcType < __rhs.fpcType)
    {
	return true;
    }
    else if(__rhs.fpcType < fpcType)
    {
	return false;
    }
    return false;
}

void
MPMS::fpcCatchedEvent::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(app);
    __os->write(fpcType);
}

void
MPMS::fpcCatchedEvent::__read(::IceInternal::BasicStream* __is)
{
    __is->read(app);
    __is->read(fpcType);
}

bool
MPMS::NetFile::operator==(const NetFile& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::NetFile::operator!=(const NetFile& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(file != __rhs.file)
    {
	return true;
    }
    if(instdir != __rhs.instdir)
    {
	return true;
    }
    return false;
}

bool
MPMS::NetFile::operator<(const NetFile& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(file < __rhs.file)
    {
	return true;
    }
    else if(__rhs.file < file)
    {
	return false;
    }
    if(instdir < __rhs.instdir)
    {
	return true;
    }
    else if(__rhs.instdir < instdir)
    {
	return false;
    }
    return false;
}

void
MPMS::NetFile::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(file);
    __os->write(instdir);
}

void
MPMS::NetFile::__read(::IceInternal::BasicStream* __is)
{
    __is->read(file);
    __is->read(instdir);
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::NetFileList& v, ::MPMS::__U__NetFileList)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::MPMS::NetFileList::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
	(*p).__write(__os);
    }
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::NetFileList& v, ::MPMS::__U__NetFileList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 2);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}

bool
MPMS::EventMediaPlay::operator==(const EventMediaPlay& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::EventMediaPlay::operator!=(const EventMediaPlay& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(midiaId != __rhs.midiaId)
    {
	return true;
    }
    if(event != __rhs.event)
    {
	return true;
    }
    if(fpcIp != __rhs.fpcIp)
    {
	return true;
    }
    if(fpcMac != __rhs.fpcMac)
    {
	return true;
    }
    if(startTime != __rhs.startTime)
    {
	return true;
    }
    if(endTime != __rhs.endTime)
    {
	return true;
    }
    return false;
}

bool
MPMS::EventMediaPlay::operator<(const EventMediaPlay& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(midiaId < __rhs.midiaId)
    {
	return true;
    }
    else if(__rhs.midiaId < midiaId)
    {
	return false;
    }
    if(event < __rhs.event)
    {
	return true;
    }
    else if(__rhs.event < event)
    {
	return false;
    }
    if(fpcIp < __rhs.fpcIp)
    {
	return true;
    }
    else if(__rhs.fpcIp < fpcIp)
    {
	return false;
    }
    if(fpcMac < __rhs.fpcMac)
    {
	return true;
    }
    else if(__rhs.fpcMac < fpcMac)
    {
	return false;
    }
    if(startTime < __rhs.startTime)
    {
	return true;
    }
    else if(__rhs.startTime < startTime)
    {
	return false;
    }
    if(endTime < __rhs.endTime)
    {
	return true;
    }
    else if(__rhs.endTime < endTime)
    {
	return false;
    }
    return false;
}

void
MPMS::EventMediaPlay::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(midiaId);
    __os->write(event);
    __os->write(fpcIp);
    __os->write(fpcMac);
    __os->write(startTime);
    __os->write(endTime);
}

void
MPMS::EventMediaPlay::__read(::IceInternal::BasicStream* __is)
{
    __is->read(midiaId);
    __is->read(event);
    __is->read(fpcIp);
    __is->read(fpcMac);
    __is->read(startTime);
    __is->read(endTime);
}

void
MPMS::__write(::IceInternal::BasicStream* __os, const ::MPMS::EventMediaPlayList& v, ::MPMS::__U__EventMediaPlayList)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::MPMS::EventMediaPlayList::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
	(*p).__write(__os);
    }
}

void
MPMS::__read(::IceInternal::BasicStream* __is, ::MPMS::EventMediaPlayList& v, ::MPMS::__U__EventMediaPlayList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 12);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}

bool
MPMS::FtpServer::operator==(const FtpServer& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::FtpServer::operator!=(const FtpServer& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(host != __rhs.host)
    {
	return true;
    }
    if(port != __rhs.port)
    {
	return true;
    }
    if(user != __rhs.user)
    {
	return true;
    }
    if(passwd != __rhs.passwd)
    {
	return true;
    }
    return false;
}

bool
MPMS::FtpServer::operator<(const FtpServer& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(host < __rhs.host)
    {
	return true;
    }
    else if(__rhs.host < host)
    {
	return false;
    }
    if(port < __rhs.port)
    {
	return true;
    }
    else if(__rhs.port < port)
    {
	return false;
    }
    if(user < __rhs.user)
    {
	return true;
    }
    else if(__rhs.user < user)
    {
	return false;
    }
    if(passwd < __rhs.passwd)
    {
	return true;
    }
    else if(__rhs.passwd < passwd)
    {
	return false;
    }
    return false;
}

void
MPMS::FtpServer::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(host);
    __os->write(port);
    __os->write(user);
    __os->write(passwd);
}

void
MPMS::FtpServer::__read(::IceInternal::BasicStream* __is)
{
    __is->read(host);
    __is->read(port);
    __is->read(user);
    __is->read(passwd);
}

bool
MPMS::SystemDistribution::operator==(const SystemDistribution& __rhs) const
{
    return !operator!=(__rhs);
}

bool
MPMS::SystemDistribution::operator!=(const SystemDistribution& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(subsys != __rhs.subsys)
    {
	return true;
    }
    if(version != __rhs.version)
    {
	return true;
    }
    if(fileList != __rhs.fileList)
    {
	return true;
    }
    return false;
}

bool
MPMS::SystemDistribution::operator<(const SystemDistribution& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(subsys < __rhs.subsys)
    {
	return true;
    }
    else if(__rhs.subsys < subsys)
    {
	return false;
    }
    if(version < __rhs.version)
    {
	return true;
    }
    else if(__rhs.version < version)
    {
	return false;
    }
    if(fileList < __rhs.fileList)
    {
	return true;
    }
    else if(__rhs.fileList < fileList)
    {
	return false;
    }
    return false;
}

void
MPMS::SystemDistribution::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(subsys);
    __os->write(version);
    ::MPMS::__write(__os, fileList, ::MPMS::__U__NetFileList());
}

void
MPMS::SystemDistribution::__read(::IceInternal::BasicStream* __is)
{
    __is->read(subsys);
    __is->read(version);
    ::MPMS::__read(__is, fileList, ::MPMS::__U__NetFileList());
}

void
IceProxy::MPMS::FrontPlayController::ChangeSetting(const ::MPMS::fpcSetting& setting)
{
    ChangeSetting(setting, __defaultContext());
}

void
IceProxy::MPMS::FrontPlayController::ChangeSetting(const ::MPMS::fpcSetting& setting, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontPlayController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontPlayController*>(__delBase.get());
	    __del->ChangeSetting(setting, __ctx);
	    return;
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::std::string
IceProxy::MPMS::FrontPlayController::GetType()
{
    return GetType(__defaultContext());
}

::std::string
IceProxy::MPMS::FrontPlayController::GetType(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetType");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontPlayController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontPlayController*>(__delBase.get());
	    return __del->GetType(__ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::fpcParameter
IceProxy::MPMS::FrontPlayController::GetParameter()
{
    return GetParameter(__defaultContext());
}

::MPMS::fpcParameter
IceProxy::MPMS::FrontPlayController::GetParameter(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetParameter");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontPlayController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontPlayController*>(__delBase.get());
	    return __del->GetParameter(__ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

const ::std::string&
IceProxy::MPMS::FrontPlayController::ice_staticId()
{
    return ::MPMS::FrontPlayController::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::MPMS::FrontPlayController::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::MPMS::FrontPlayController);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::MPMS::FrontPlayController::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::MPMS::FrontPlayController);
}

bool
IceProxy::MPMS::operator==(const ::IceProxy::MPMS::FrontPlayController& l, const ::IceProxy::MPMS::FrontPlayController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator!=(const ::IceProxy::MPMS::FrontPlayController& l, const ::IceProxy::MPMS::FrontPlayController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator<(const ::IceProxy::MPMS::FrontPlayController& l, const ::IceProxy::MPMS::FrontPlayController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::FrontDispatchController::RegisterFPC(const ::Ice::Identity& fpcIdent, const ::MPMS::fpcParameter& fpc)
{
    return RegisterFPC(fpcIdent, fpc, __defaultContext());
}

bool
IceProxy::MPMS::FrontDispatchController::RegisterFPC(const ::Ice::Identity& fpcIdent, const ::MPMS::fpcParameter& fpc, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("RegisterFPC");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontDispatchController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontDispatchController*>(__delBase.get());
	    return __del->RegisterFPC(fpcIdent, fpc, __ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::fpcSetting
IceProxy::MPMS::FrontDispatchController::GetFPCSettings()
{
    return GetFPCSettings(__defaultContext());
}

::MPMS::fpcSetting
IceProxy::MPMS::FrontDispatchController::GetFPCSettings(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetFPCSettings");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontDispatchController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontDispatchController*>(__delBase.get());
	    return __del->GetFPCSettings(__ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::fdcParameter
IceProxy::MPMS::FrontDispatchController::GetParameter()
{
    return GetParameter(__defaultContext());
}

::MPMS::fdcParameter
IceProxy::MPMS::FrontDispatchController::GetParameter(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetParameter");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontDispatchController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontDispatchController*>(__delBase.get());
	    return __del->GetParameter(__ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

void
IceProxy::MPMS::FrontDispatchController::ReportMideaPlayEvent(const ::std::string& fdcid, const ::MPMS::EventMediaPlayList& list)
{
    ReportMideaPlayEvent(fdcid, list, __defaultContext());
}

void
IceProxy::MPMS::FrontDispatchController::ReportMideaPlayEvent(const ::std::string& fdcid, const ::MPMS::EventMediaPlayList& list, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::FrontDispatchController* __del = dynamic_cast< ::IceDelegate::MPMS::FrontDispatchController*>(__delBase.get());
	    __del->ReportMideaPlayEvent(fdcid, list, __ctx);
	    return;
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

const ::std::string&
IceProxy::MPMS::FrontDispatchController::ice_staticId()
{
    return ::MPMS::FrontDispatchController::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::MPMS::FrontDispatchController::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::MPMS::FrontDispatchController);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::MPMS::FrontDispatchController::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::MPMS::FrontDispatchController);
}

bool
IceProxy::MPMS::operator==(const ::IceProxy::MPMS::FrontDispatchController& l, const ::IceProxy::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator!=(const ::IceProxy::MPMS::FrontDispatchController& l, const ::IceProxy::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator<(const ::IceProxy::MPMS::FrontDispatchController& l, const ::IceProxy::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

::MPMS::PlayPolicyList
IceProxy::MPMS::CentreMangementSystem::GetPlayPolicies(const ::std::string& fdcID)
{
    return GetPlayPolicies(fdcID, __defaultContext());
}

::MPMS::PlayPolicyList
IceProxy::MPMS::CentreMangementSystem::GetPlayPolicies(const ::std::string& fdcID, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetPlayPolicies");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::CentreMangementSystem* __del = dynamic_cast< ::IceDelegate::MPMS::CentreMangementSystem*>(__delBase.get());
	    return __del->GetPlayPolicies(fdcID, __ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::fpcControlInfo
IceProxy::MPMS::CentreMangementSystem::GetfpcControlInfo(const ::std::string& fdcID)
{
    return GetfpcControlInfo(fdcID, __defaultContext());
}

::MPMS::fpcControlInfo
IceProxy::MPMS::CentreMangementSystem::GetfpcControlInfo(const ::std::string& fdcID, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetfpcControlInfo");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::CentreMangementSystem* __del = dynamic_cast< ::IceDelegate::MPMS::CentreMangementSystem*>(__delBase.get());
	    return __del->GetfpcControlInfo(fdcID, __ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

bool
IceProxy::MPMS::CentreMangementSystem::RegisterFDC(const ::Ice::Identity& fdcIdent)
{
    return RegisterFDC(fdcIdent, __defaultContext());
}

bool
IceProxy::MPMS::CentreMangementSystem::RegisterFDC(const ::Ice::Identity& fdcIdent, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("RegisterFDC");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::CentreMangementSystem* __del = dynamic_cast< ::IceDelegate::MPMS::CentreMangementSystem*>(__delBase.get());
	    return __del->RegisterFDC(fdcIdent, __ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::SystemDistribution
IceProxy::MPMS::CentreMangementSystem::SyncSystem(const ::std::string& moduleType, const ::std::string& version)
{
    return SyncSystem(moduleType, version, __defaultContext());
}

::MPMS::SystemDistribution
IceProxy::MPMS::CentreMangementSystem::SyncSystem(const ::std::string& moduleType, const ::std::string& version, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("SyncSystem");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::CentreMangementSystem* __del = dynamic_cast< ::IceDelegate::MPMS::CentreMangementSystem*>(__delBase.get());
	    return __del->SyncSystem(moduleType, version, __ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::MPMS::FtpServer
IceProxy::MPMS::CentreMangementSystem::GetFtpServer()
{
    return GetFtpServer(__defaultContext());
}

::MPMS::FtpServer
IceProxy::MPMS::CentreMangementSystem::GetFtpServer(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly("GetFtpServer");
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::MPMS::CentreMangementSystem* __del = dynamic_cast< ::IceDelegate::MPMS::CentreMangementSystem*>(__delBase.get());
	    return __del->GetFtpServer(__ctx);
	}
	catch(const ::IceInternal::NonRepeatable& __ex)
	{
	    __rethrowException(*__ex.get());
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

const ::std::string&
IceProxy::MPMS::CentreMangementSystem::ice_staticId()
{
    return ::MPMS::CentreMangementSystem::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::MPMS::CentreMangementSystem::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::MPMS::CentreMangementSystem);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::MPMS::CentreMangementSystem::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::MPMS::CentreMangementSystem);
}

bool
IceProxy::MPMS::operator==(const ::IceProxy::MPMS::CentreMangementSystem& l, const ::IceProxy::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator!=(const ::IceProxy::MPMS::CentreMangementSystem& l, const ::IceProxy::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::MPMS::operator<(const ::IceProxy::MPMS::CentreMangementSystem& l, const ::IceProxy::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

static const ::std::string __MPMS__FrontPlayController__ChangeSetting_name = "ChangeSetting";

void
IceDelegateM::MPMS::FrontPlayController::ChangeSetting(const ::MPMS::fpcSetting& setting, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontPlayController__ChangeSetting_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	setting.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontPlayController__GetType_name = "GetType";

::std::string
IceDelegateM::MPMS::FrontPlayController::GetType(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontPlayController__GetType_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::std::string __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontPlayController__GetParameter_name = "GetParameter";

::MPMS::fpcParameter
IceDelegateM::MPMS::FrontPlayController::GetParameter(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontPlayController__GetParameter_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::fpcParameter __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontDispatchController__RegisterFPC_name = "RegisterFPC";

bool
IceDelegateM::MPMS::FrontDispatchController::RegisterFPC(const ::Ice::Identity& fpcIdent, const ::MPMS::fpcParameter& fpc, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontDispatchController__RegisterFPC_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	fpcIdent.__write(__os);
	fpc.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	bool __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontDispatchController__GetFPCSettings_name = "GetFPCSettings";

::MPMS::fpcSetting
IceDelegateM::MPMS::FrontDispatchController::GetFPCSettings(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontDispatchController__GetFPCSettings_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::fpcSetting __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontDispatchController__GetParameter_name = "GetParameter";

::MPMS::fdcParameter
IceDelegateM::MPMS::FrontDispatchController::GetParameter(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontDispatchController__GetParameter_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::fdcParameter __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__FrontDispatchController__ReportMideaPlayEvent_name = "ReportMideaPlayEvent";

void
IceDelegateM::MPMS::FrontDispatchController::ReportMideaPlayEvent(const ::std::string& fdcid, const ::MPMS::EventMediaPlayList& list, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__FrontDispatchController__ReportMideaPlayEvent_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(fdcid);
	::MPMS::__write(__os, list, ::MPMS::__U__EventMediaPlayList());
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__CentreMangementSystem__GetPlayPolicies_name = "GetPlayPolicies";

::MPMS::PlayPolicyList
IceDelegateM::MPMS::CentreMangementSystem::GetPlayPolicies(const ::std::string& fdcID, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__CentreMangementSystem__GetPlayPolicies_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(fdcID);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::PlayPolicyList __ret;
	::MPMS::__read(__is, __ret, ::MPMS::__U__PlayPolicyList());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__CentreMangementSystem__GetfpcControlInfo_name = "GetfpcControlInfo";

::MPMS::fpcControlInfo
IceDelegateM::MPMS::CentreMangementSystem::GetfpcControlInfo(const ::std::string& fdcID, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__CentreMangementSystem__GetfpcControlInfo_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(fdcID);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::fpcControlInfo __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__CentreMangementSystem__RegisterFDC_name = "RegisterFDC";

bool
IceDelegateM::MPMS::CentreMangementSystem::RegisterFDC(const ::Ice::Identity& fdcIdent, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__CentreMangementSystem__RegisterFDC_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	fdcIdent.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	bool __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__CentreMangementSystem__SyncSystem_name = "SyncSystem";

::MPMS::SystemDistribution
IceDelegateM::MPMS::CentreMangementSystem::SyncSystem(const ::std::string& moduleType, const ::std::string& version, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__CentreMangementSystem__SyncSystem_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(moduleType);
	__os->write(version);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::SystemDistribution __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

static const ::std::string __MPMS__CentreMangementSystem__GetFtpServer_name = "GetFtpServer";

::MPMS::FtpServer
IceDelegateM::MPMS::CentreMangementSystem::GetFtpServer(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __MPMS__CentreMangementSystem__GetFtpServer_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::MPMS::FtpServer __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::NonRepeatable(__ex);
    }
}

void
IceDelegateD::MPMS::FrontPlayController::ChangeSetting(const ::MPMS::fpcSetting& setting, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "ChangeSetting", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontPlayController* __servant = dynamic_cast< ::MPMS::FrontPlayController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    __servant->ChangeSetting(setting, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::std::string
IceDelegateD::MPMS::FrontPlayController::GetType(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetType", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontPlayController* __servant = dynamic_cast< ::MPMS::FrontPlayController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetType(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::fpcParameter
IceDelegateD::MPMS::FrontPlayController::GetParameter(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetParameter", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontPlayController* __servant = dynamic_cast< ::MPMS::FrontPlayController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetParameter(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

bool
IceDelegateD::MPMS::FrontDispatchController::RegisterFPC(const ::Ice::Identity& fpcIdent, const ::MPMS::fpcParameter& fpc, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "RegisterFPC", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontDispatchController* __servant = dynamic_cast< ::MPMS::FrontDispatchController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->RegisterFPC(fpcIdent, fpc, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::fpcSetting
IceDelegateD::MPMS::FrontDispatchController::GetFPCSettings(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetFPCSettings", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontDispatchController* __servant = dynamic_cast< ::MPMS::FrontDispatchController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetFPCSettings(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::fdcParameter
IceDelegateD::MPMS::FrontDispatchController::GetParameter(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetParameter", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontDispatchController* __servant = dynamic_cast< ::MPMS::FrontDispatchController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetParameter(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

void
IceDelegateD::MPMS::FrontDispatchController::ReportMideaPlayEvent(const ::std::string& fdcid, const ::MPMS::EventMediaPlayList& list, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "ReportMideaPlayEvent", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::FrontDispatchController* __servant = dynamic_cast< ::MPMS::FrontDispatchController*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    __servant->ReportMideaPlayEvent(fdcid, list, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::PlayPolicyList
IceDelegateD::MPMS::CentreMangementSystem::GetPlayPolicies(const ::std::string& fdcID, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetPlayPolicies", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::CentreMangementSystem* __servant = dynamic_cast< ::MPMS::CentreMangementSystem*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetPlayPolicies(fdcID, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::fpcControlInfo
IceDelegateD::MPMS::CentreMangementSystem::GetfpcControlInfo(const ::std::string& fdcID, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetfpcControlInfo", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::CentreMangementSystem* __servant = dynamic_cast< ::MPMS::CentreMangementSystem*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetfpcControlInfo(fdcID, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

bool
IceDelegateD::MPMS::CentreMangementSystem::RegisterFDC(const ::Ice::Identity& fdcIdent, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "RegisterFDC", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::CentreMangementSystem* __servant = dynamic_cast< ::MPMS::CentreMangementSystem*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->RegisterFDC(fdcIdent, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::SystemDistribution
IceDelegateD::MPMS::CentreMangementSystem::SyncSystem(const ::std::string& moduleType, const ::std::string& version, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "SyncSystem", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::CentreMangementSystem* __servant = dynamic_cast< ::MPMS::CentreMangementSystem*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->SyncSystem(moduleType, version, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::MPMS::FtpServer
IceDelegateD::MPMS::CentreMangementSystem::GetFtpServer(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, "GetFtpServer", ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::MPMS::CentreMangementSystem* __servant = dynamic_cast< ::MPMS::CentreMangementSystem*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->GetFtpServer(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::NonRepeatable(__ex);
	}
    }
}

::Ice::ObjectPtr
MPMS::FrontPlayController::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
}

static const ::std::string __MPMS__FrontPlayController_ids[2] =
{
    "::Ice::Object",
    "::MPMS::FrontPlayController"
};

bool
MPMS::FrontPlayController::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__MPMS__FrontPlayController_ids, __MPMS__FrontPlayController_ids + 2, _s);
}

::std::vector< ::std::string>
MPMS::FrontPlayController::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__MPMS__FrontPlayController_ids[0], &__MPMS__FrontPlayController_ids[2]);
}

const ::std::string&
MPMS::FrontPlayController::ice_id(const ::Ice::Current&) const
{
    return __MPMS__FrontPlayController_ids[1];
}

const ::std::string&
MPMS::FrontPlayController::ice_staticId()
{
    return __MPMS__FrontPlayController_ids[1];
}

::IceInternal::DispatchStatus
MPMS::FrontPlayController::___ChangeSetting(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::MPMS::fpcSetting setting;
    setting.__read(__is);
    ChangeSetting(setting, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::FrontPlayController::___GetType(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = GetType(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::FrontPlayController::___GetParameter(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::MPMS::fpcParameter __ret = GetParameter(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

static ::std::string __MPMS__FrontPlayController_all[] =
{
    "ChangeSetting",
    "GetParameter",
    "GetType",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
MPMS::FrontPlayController::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__MPMS__FrontPlayController_all, __MPMS__FrontPlayController_all + 7, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __MPMS__FrontPlayController_all)
    {
	case 0:
	{
	    return ___ChangeSetting(in, current);
	}
	case 1:
	{
	    return ___GetParameter(in, current);
	}
	case 2:
	{
	    return ___GetType(in, current);
	}
	case 3:
	{
	    return ___ice_id(in, current);
	}
	case 4:
	{
	    return ___ice_ids(in, current);
	}
	case 5:
	{
	    return ___ice_isA(in, current);
	}
	case 6:
	{
	    return ___ice_ping(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
MPMS::FrontPlayController::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
MPMS::FrontPlayController::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
MPMS::FrontPlayController::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::FrontPlayController was not generated with stream support";
    throw ex;
}

void
MPMS::FrontPlayController::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::FrontPlayController was not generated with stream support";
    throw ex;
}

void 
MPMS::__patch__FrontPlayControllerPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::MPMS::FrontPlayControllerPtr* p = static_cast< ::MPMS::FrontPlayControllerPtr*>(__addr);
    assert(p);
    *p = ::MPMS::FrontPlayControllerPtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::MPMS::FrontPlayController::ice_staticId();
	throw e;
    }
}

bool
MPMS::operator==(const ::MPMS::FrontPlayController& l, const ::MPMS::FrontPlayController& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator!=(const ::MPMS::FrontPlayController& l, const ::MPMS::FrontPlayController& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator<(const ::MPMS::FrontPlayController& l, const ::MPMS::FrontPlayController& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

::Ice::ObjectPtr
MPMS::FrontDispatchController::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
}

static const ::std::string __MPMS__FrontDispatchController_ids[2] =
{
    "::Ice::Object",
    "::MPMS::FrontDispatchController"
};

bool
MPMS::FrontDispatchController::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__MPMS__FrontDispatchController_ids, __MPMS__FrontDispatchController_ids + 2, _s);
}

::std::vector< ::std::string>
MPMS::FrontDispatchController::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__MPMS__FrontDispatchController_ids[0], &__MPMS__FrontDispatchController_ids[2]);
}

const ::std::string&
MPMS::FrontDispatchController::ice_id(const ::Ice::Current&) const
{
    return __MPMS__FrontDispatchController_ids[1];
}

const ::std::string&
MPMS::FrontDispatchController::ice_staticId()
{
    return __MPMS__FrontDispatchController_ids[1];
}

::IceInternal::DispatchStatus
MPMS::FrontDispatchController::___RegisterFPC(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Identity fpcIdent;
    ::MPMS::fpcParameter fpc;
    fpcIdent.__read(__is);
    fpc.__read(__is);
    bool __ret = RegisterFPC(fpcIdent, fpc, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::FrontDispatchController::___GetFPCSettings(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::MPMS::fpcSetting __ret = GetFPCSettings(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::FrontDispatchController::___GetParameter(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::MPMS::fdcParameter __ret = GetParameter(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::FrontDispatchController::___ReportMideaPlayEvent(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string fdcid;
    ::MPMS::EventMediaPlayList list;
    __is->read(fdcid);
    ::MPMS::__read(__is, list, ::MPMS::__U__EventMediaPlayList());
    ReportMideaPlayEvent(fdcid, list, __current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __MPMS__FrontDispatchController_all[] =
{
    "GetFPCSettings",
    "GetParameter",
    "RegisterFPC",
    "ReportMideaPlayEvent",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
MPMS::FrontDispatchController::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__MPMS__FrontDispatchController_all, __MPMS__FrontDispatchController_all + 8, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __MPMS__FrontDispatchController_all)
    {
	case 0:
	{
	    return ___GetFPCSettings(in, current);
	}
	case 1:
	{
	    return ___GetParameter(in, current);
	}
	case 2:
	{
	    return ___RegisterFPC(in, current);
	}
	case 3:
	{
	    return ___ReportMideaPlayEvent(in, current);
	}
	case 4:
	{
	    return ___ice_id(in, current);
	}
	case 5:
	{
	    return ___ice_ids(in, current);
	}
	case 6:
	{
	    return ___ice_isA(in, current);
	}
	case 7:
	{
	    return ___ice_ping(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
MPMS::FrontDispatchController::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
MPMS::FrontDispatchController::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
MPMS::FrontDispatchController::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::FrontDispatchController was not generated with stream support";
    throw ex;
}

void
MPMS::FrontDispatchController::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::FrontDispatchController was not generated with stream support";
    throw ex;
}

void 
MPMS::__patch__FrontDispatchControllerPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::MPMS::FrontDispatchControllerPtr* p = static_cast< ::MPMS::FrontDispatchControllerPtr*>(__addr);
    assert(p);
    *p = ::MPMS::FrontDispatchControllerPtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::MPMS::FrontDispatchController::ice_staticId();
	throw e;
    }
}

bool
MPMS::operator==(const ::MPMS::FrontDispatchController& l, const ::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator!=(const ::MPMS::FrontDispatchController& l, const ::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator<(const ::MPMS::FrontDispatchController& l, const ::MPMS::FrontDispatchController& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

::Ice::ObjectPtr
MPMS::CentreMangementSystem::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
}

static const ::std::string __MPMS__CentreMangementSystem_ids[3] =
{
    "::Ice::Object",
    "::MPMS::CentreMangementSystem",
    "::MPMS::FrontDispatchController"
};

bool
MPMS::CentreMangementSystem::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__MPMS__CentreMangementSystem_ids, __MPMS__CentreMangementSystem_ids + 3, _s);
}

::std::vector< ::std::string>
MPMS::CentreMangementSystem::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__MPMS__CentreMangementSystem_ids[0], &__MPMS__CentreMangementSystem_ids[3]);
}

const ::std::string&
MPMS::CentreMangementSystem::ice_id(const ::Ice::Current&) const
{
    return __MPMS__CentreMangementSystem_ids[1];
}

const ::std::string&
MPMS::CentreMangementSystem::ice_staticId()
{
    return __MPMS__CentreMangementSystem_ids[1];
}

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::___GetPlayPolicies(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string fdcID;
    __is->read(fdcID);
    ::MPMS::PlayPolicyList __ret = GetPlayPolicies(fdcID, __current);
    ::MPMS::__write(__os, __ret, ::MPMS::__U__PlayPolicyList());
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::___GetfpcControlInfo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string fdcID;
    __is->read(fdcID);
    ::MPMS::fpcControlInfo __ret = GetfpcControlInfo(fdcID, __current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::___RegisterFDC(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Identity fdcIdent;
    fdcIdent.__read(__is);
    bool __ret = RegisterFDC(fdcIdent, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::___SyncSystem(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string moduleType;
    ::std::string version;
    __is->read(moduleType);
    __is->read(version);
    ::MPMS::SystemDistribution __ret = SyncSystem(moduleType, version, __current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::___GetFtpServer(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::MPMS::FtpServer __ret = GetFtpServer(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

static ::std::string __MPMS__CentreMangementSystem_all[] =
{
    "GetFPCSettings",
    "GetFtpServer",
    "GetParameter",
    "GetPlayPolicies",
    "GetfpcControlInfo",
    "RegisterFDC",
    "RegisterFPC",
    "ReportMideaPlayEvent",
    "SyncSystem",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
MPMS::CentreMangementSystem::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__MPMS__CentreMangementSystem_all, __MPMS__CentreMangementSystem_all + 13, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __MPMS__CentreMangementSystem_all)
    {
	case 0:
	{
	    return ___GetFPCSettings(in, current);
	}
	case 1:
	{
	    return ___GetFtpServer(in, current);
	}
	case 2:
	{
	    return ___GetParameter(in, current);
	}
	case 3:
	{
	    return ___GetPlayPolicies(in, current);
	}
	case 4:
	{
	    return ___GetfpcControlInfo(in, current);
	}
	case 5:
	{
	    return ___RegisterFDC(in, current);
	}
	case 6:
	{
	    return ___RegisterFPC(in, current);
	}
	case 7:
	{
	    return ___ReportMideaPlayEvent(in, current);
	}
	case 8:
	{
	    return ___SyncSystem(in, current);
	}
	case 9:
	{
	    return ___ice_id(in, current);
	}
	case 10:
	{
	    return ___ice_ids(in, current);
	}
	case 11:
	{
	    return ___ice_isA(in, current);
	}
	case 12:
	{
	    return ___ice_ping(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
MPMS::CentreMangementSystem::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
MPMS::CentreMangementSystem::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
MPMS::CentreMangementSystem::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::CentreMangementSystem was not generated with stream support";
    throw ex;
}

void
MPMS::CentreMangementSystem::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type MPMS::CentreMangementSystem was not generated with stream support";
    throw ex;
}

void 
MPMS::__patch__CentreMangementSystemPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::MPMS::CentreMangementSystemPtr* p = static_cast< ::MPMS::CentreMangementSystemPtr*>(__addr);
    assert(p);
    *p = ::MPMS::CentreMangementSystemPtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::MPMS::CentreMangementSystem::ice_staticId();
	throw e;
    }
}

bool
MPMS::operator==(const ::MPMS::CentreMangementSystem& l, const ::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator!=(const ::MPMS::CentreMangementSystem& l, const ::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
MPMS::operator<(const ::MPMS::CentreMangementSystem& l, const ::MPMS::CentreMangementSystem& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}
