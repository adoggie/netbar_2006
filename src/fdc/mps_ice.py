# **********************************************************************
#
# Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

# Ice version 3.0.1
# Generated from file `mps.ice'

import Ice, IcePy, __builtin__
import Ice_Identity_ice

# Included module Ice
_M_Ice = Ice.openModule('Ice')

# Start of module MPMS
_M_MPMS = Ice.openModule('MPMS')
__name__ = 'MPMS'

if not _M_MPMS.__dict__.has_key('fpcControlInfo'):
    _M_MPMS.fpcControlInfo = Ice.createTempClass()
    class fpcControlInfo(object):
        def __init__(self, policySyncTime=0):
            self.policySyncTime = policySyncTime

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.policySyncTime)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.policySyncTime == other.policySyncTime:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_fpcControlInfo)

        __repr__ = __str__

    _M_MPMS._t_fpcControlInfo = IcePy.defineStruct('::MPMS::fpcControlInfo', fpcControlInfo, (("policySyncTime", IcePy._t_int),))

    _M_MPMS.fpcControlInfo = fpcControlInfo
    del fpcControlInfo

if not _M_MPMS.__dict__.has_key('MediaControlInfo'):
    _M_MPMS.MediaControlInfo = Ice.createTempClass()
    class MediaControlInfo(object):
        def __init__(self, id='', name='', url='', player='', width=0, height=0):
            self.id = id
            self.name = name
            self.url = url
            self.player = player
            self.width = width
            self.height = height

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.id)
            _h = 5 * _h + __builtin__.hash(self.name)
            _h = 5 * _h + __builtin__.hash(self.url)
            _h = 5 * _h + __builtin__.hash(self.player)
            _h = 5 * _h + __builtin__.hash(self.width)
            _h = 5 * _h + __builtin__.hash(self.height)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.id == other.id:
                return False
            if not self.name == other.name:
                return False
            if not self.url == other.url:
                return False
            if not self.player == other.player:
                return False
            if not self.width == other.width:
                return False
            if not self.height == other.height:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_MediaControlInfo)

        __repr__ = __str__

    _M_MPMS._t_MediaControlInfo = IcePy.defineStruct('::MPMS::MediaControlInfo', MediaControlInfo, (
        ("id", IcePy._t_string),
        ("name", IcePy._t_string),
        ("url", IcePy._t_string),
        ("player", IcePy._t_string),
        ("width", IcePy._t_int),
        ("height", IcePy._t_int)
    ))

    _M_MPMS.MediaControlInfo = MediaControlInfo
    del MediaControlInfo

if not _M_MPMS.__dict__.has_key('_t_MediaControlInfoList'):
    _M_MPMS._t_MediaControlInfoList = IcePy.defineSequence('::MPMS::MediaControlInfoList', _M_MPMS._t_MediaControlInfo)

if not _M_MPMS.__dict__.has_key('IEToolbarControlInfo'):
    _M_MPMS.IEToolbarControlInfo = Ice.createTempClass()
    class IEToolbarControlInfo(object):
        def __init__(self, mciList=None):
            self.mciList = mciList

        def __hash__(self):
            _h = 0
            if self.mciList:
                for _i0 in self.mciList:
                    _h = 5 * _h + __builtin__.hash(_i0)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.mciList == other.mciList:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_IEToolbarControlInfo)

        __repr__ = __str__

    _M_MPMS._t_IEToolbarControlInfo = IcePy.defineStruct('::MPMS::IEToolbarControlInfo', IEToolbarControlInfo, (("mciList", _M_MPMS._t_MediaControlInfoList),))

    _M_MPMS.IEToolbarControlInfo = IEToolbarControlInfo
    del IEToolbarControlInfo

if not _M_MPMS.__dict__.has_key('fdcParameter'):
    _M_MPMS.fdcParameter = Ice.createTempClass()
    class fdcParameter(object):
        def __init__(self, id='', gateway=''):
            self.id = id
            self.gateway = gateway

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.id)
            _h = 5 * _h + __builtin__.hash(self.gateway)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.id == other.id:
                return False
            if not self.gateway == other.gateway:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_fdcParameter)

        __repr__ = __str__

    _M_MPMS._t_fdcParameter = IcePy.defineStruct('::MPMS::fdcParameter', fdcParameter, (
        ("id", IcePy._t_string),
        ("gateway", IcePy._t_string)
    ))

    _M_MPMS.fdcParameter = fdcParameter
    del fdcParameter

if not _M_MPMS.__dict__.has_key('fpcSetting'):
    _M_MPMS.fpcSetting = Ice.createTempClass()
    class fpcSetting(object):
        def __init__(self, ieDefaultAddr='', wallpaper='', ieToolbar=_M_MPMS.IEToolbarControlInfo(), alNotification=_M_MPMS.MediaControlInfo(), alAdvertisement=_M_MPMS.MediaControlInfo(), qq=_M_MPMS.MediaControlInfo(), msn=_M_MPMS.MediaControlInfo()):
            self.ieDefaultAddr = ieDefaultAddr
            self.wallpaper = wallpaper
            self.ieToolbar = ieToolbar
            self.alNotification = alNotification
            self.alAdvertisement = alAdvertisement
            self.qq = qq
            self.msn = msn

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.ieDefaultAddr)
            _h = 5 * _h + __builtin__.hash(self.wallpaper)
            _h = 5 * _h + __builtin__.hash(self.ieToolbar)
            _h = 5 * _h + __builtin__.hash(self.alNotification)
            _h = 5 * _h + __builtin__.hash(self.alAdvertisement)
            _h = 5 * _h + __builtin__.hash(self.qq)
            _h = 5 * _h + __builtin__.hash(self.msn)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.ieDefaultAddr == other.ieDefaultAddr:
                return False
            if not self.wallpaper == other.wallpaper:
                return False
            if not self.ieToolbar == other.ieToolbar:
                return False
            if not self.alNotification == other.alNotification:
                return False
            if not self.alAdvertisement == other.alAdvertisement:
                return False
            if not self.qq == other.qq:
                return False
            if not self.msn == other.msn:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_fpcSetting)

        __repr__ = __str__

    _M_MPMS._t_fpcSetting = IcePy.defineStruct('::MPMS::fpcSetting', fpcSetting, (
        ("ieDefaultAddr", IcePy._t_string),
        ("wallpaper", IcePy._t_string),
        ("ieToolbar", _M_MPMS._t_IEToolbarControlInfo),
        ("alNotification", _M_MPMS._t_MediaControlInfo),
        ("alAdvertisement", _M_MPMS._t_MediaControlInfo),
        ("qq", _M_MPMS._t_MediaControlInfo),
        ("msn", _M_MPMS._t_MediaControlInfo)
    ))

    _M_MPMS.fpcSetting = fpcSetting
    del fpcSetting

if not _M_MPMS.__dict__.has_key('fpcParameter'):
    _M_MPMS.fpcParameter = Ice.createTempClass()
    class fpcParameter(object):
        def __init__(self, ip='', mac=''):
            self.ip = ip
            self.mac = mac

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.ip)
            _h = 5 * _h + __builtin__.hash(self.mac)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.ip == other.ip:
                return False
            if not self.mac == other.mac:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_fpcParameter)

        __repr__ = __str__

    _M_MPMS._t_fpcParameter = IcePy.defineStruct('::MPMS::fpcParameter', fpcParameter, (
        ("ip", IcePy._t_string),
        ("mac", IcePy._t_string)
    ))

    _M_MPMS.fpcParameter = fpcParameter
    del fpcParameter

if not _M_MPMS.__dict__.has_key('_t_fpcParameterList'):
    _M_MPMS._t_fpcParameterList = IcePy.defineSequence('::MPMS::fpcParameterList', _M_MPMS._t_fpcParameter)

if not _M_MPMS.__dict__.has_key('_t_WeekDayEnable'):
    _M_MPMS._t_WeekDayEnable = IcePy.defineSequence('::MPMS::WeekDayEnable', IcePy._t_bool)

if not _M_MPMS.__dict__.has_key('PolicyTime'):
    _M_MPMS.PolicyTime = Ice.createTempClass()
    class PolicyTime(object):
        def __init__(self, stime=0, etime=0, weekday='', shour=0, ehour=0):
            self.stime = stime
            self.etime = etime
            self.weekday = weekday
            self.shour = shour
            self.ehour = ehour

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.stime)
            _h = 5 * _h + __builtin__.hash(self.etime)
            _h = 5 * _h + __builtin__.hash(self.weekday)
            _h = 5 * _h + __builtin__.hash(self.shour)
            _h = 5 * _h + __builtin__.hash(self.ehour)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.stime == other.stime:
                return False
            if not self.etime == other.etime:
                return False
            if not self.weekday == other.weekday:
                return False
            if not self.shour == other.shour:
                return False
            if not self.ehour == other.ehour:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_PolicyTime)

        __repr__ = __str__

    _M_MPMS._t_PolicyTime = IcePy.defineStruct('::MPMS::PolicyTime', PolicyTime, (
        ("stime", IcePy._t_int),
        ("etime", IcePy._t_int),
        ("weekday", IcePy._t_string),
        ("shour", IcePy._t_int),
        ("ehour", IcePy._t_int)
    ))

    _M_MPMS.PolicyTime = PolicyTime
    del PolicyTime

if not _M_MPMS.__dict__.has_key('PlayPolicy'):
    _M_MPMS.PlayPolicy = Ice.createTempClass()
    class PlayPolicy(object):
        def __init__(self, pTime=_M_MPMS.PolicyTime(), fpcs=_M_MPMS.fpcSetting()):
            self.pTime = pTime
            self.fpcs = fpcs

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.pTime)
            _h = 5 * _h + __builtin__.hash(self.fpcs)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.pTime == other.pTime:
                return False
            if not self.fpcs == other.fpcs:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_PlayPolicy)

        __repr__ = __str__

    _M_MPMS._t_PlayPolicy = IcePy.defineStruct('::MPMS::PlayPolicy', PlayPolicy, (
        ("pTime", _M_MPMS._t_PolicyTime),
        ("fpcs", _M_MPMS._t_fpcSetting)
    ))

    _M_MPMS.PlayPolicy = PlayPolicy
    del PlayPolicy

if not _M_MPMS.__dict__.has_key('_t_PlayPolicyList'):
    _M_MPMS._t_PlayPolicyList = IcePy.defineSequence('::MPMS::PlayPolicyList', _M_MPMS._t_PlayPolicy)

if not _M_MPMS.__dict__.has_key('fpcCatchedEvent'):
    _M_MPMS.fpcCatchedEvent = Ice.createTempClass()
    class fpcCatchedEvent(object):
        def __init__(self, app='', fpcType=''):
            self.app = app
            self.fpcType = fpcType

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.app)
            _h = 5 * _h + __builtin__.hash(self.fpcType)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.app == other.app:
                return False
            if not self.fpcType == other.fpcType:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_fpcCatchedEvent)

        __repr__ = __str__

    _M_MPMS._t_fpcCatchedEvent = IcePy.defineStruct('::MPMS::fpcCatchedEvent', fpcCatchedEvent, (
        ("app", IcePy._t_string),
        ("fpcType", IcePy._t_string)
    ))

    _M_MPMS.fpcCatchedEvent = fpcCatchedEvent
    del fpcCatchedEvent

if not _M_MPMS.__dict__.has_key('FrontPlayController'):
    _M_MPMS.FrontPlayController = Ice.createTempClass()
    class FrontPlayController(Ice.Object):
        def __init__(self):
            if __builtin__.type(self) == _M_MPMS.FrontPlayController:
                raise RuntimeError('MPMS.FrontPlayController is an abstract class')

        def ice_ids(self, current=None):
            return ('::Ice::Object', '::MPMS::FrontPlayController')

        def ice_id(self, current=None):
            return '::MPMS::FrontPlayController'

        #
        # Operation signatures.
        #
        # def ChangeSetting(self, setting, current=None):
        # def GetType(self, current=None):
        # def GetParameter(self, current=None):

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_FrontPlayController)

        __repr__ = __str__

    _M_MPMS.FrontPlayControllerPrx = Ice.createTempClass()
    class FrontPlayControllerPrx(Ice.ObjectPrx):

        def ChangeSetting(self, setting, _ctx=None):
            return _M_MPMS.FrontPlayController._op_ChangeSetting.invoke(self, (setting, ), _ctx)

        def GetType(self, _ctx=None):
            return _M_MPMS.FrontPlayController._op_GetType.invoke(self, (), _ctx)

        def GetParameter(self, _ctx=None):
            return _M_MPMS.FrontPlayController._op_GetParameter.invoke(self, (), _ctx)

        def checkedCast(proxy, facetOrCtx=None, _ctx=None):
            return _M_MPMS.FrontPlayControllerPrx.ice_checkedCast(proxy, '::MPMS::FrontPlayController', facetOrCtx, _ctx)
        checkedCast = staticmethod(checkedCast)

        def uncheckedCast(proxy, facet=''):
            return _M_MPMS.FrontPlayControllerPrx.ice_uncheckedCast(proxy, facet)
        uncheckedCast = staticmethod(uncheckedCast)

    _M_MPMS._t_FrontPlayControllerPrx = IcePy.defineProxy('::MPMS::FrontPlayController', FrontPlayControllerPrx)

    _M_MPMS._t_FrontPlayController = IcePy.defineClass('::MPMS::FrontPlayController', FrontPlayController, True, None, (), ())
    FrontPlayController.ice_type = _M_MPMS._t_FrontPlayController

    FrontPlayController._op_ChangeSetting = IcePy.Operation('ChangeSetting', Ice.OperationMode.Normal, False, (_M_MPMS._t_fpcSetting,), (), None, ())
    FrontPlayController._op_GetType = IcePy.Operation('GetType', Ice.OperationMode.Normal, False, (), (), IcePy._t_string, ())
    FrontPlayController._op_GetParameter = IcePy.Operation('GetParameter', Ice.OperationMode.Normal, False, (), (), _M_MPMS._t_fpcParameter, ())

    _M_MPMS.FrontPlayController = FrontPlayController
    del FrontPlayController

    _M_MPMS.FrontPlayControllerPrx = FrontPlayControllerPrx
    del FrontPlayControllerPrx

if not _M_MPMS.__dict__.has_key('_t_ByteList'):
    _M_MPMS._t_ByteList = IcePy.defineSequence('::MPMS::ByteList', IcePy._t_byte)

if not _M_MPMS.__dict__.has_key('NetFile'):
    _M_MPMS.NetFile = Ice.createTempClass()
    class NetFile(object):
        def __init__(self, file='', instdir=''):
            self.file = file
            self.instdir = instdir

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.file)
            _h = 5 * _h + __builtin__.hash(self.instdir)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.file == other.file:
                return False
            if not self.instdir == other.instdir:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_NetFile)

        __repr__ = __str__

    _M_MPMS._t_NetFile = IcePy.defineStruct('::MPMS::NetFile', NetFile, (
        ("file", IcePy._t_string),
        ("instdir", IcePy._t_string)
    ))

    _M_MPMS.NetFile = NetFile
    del NetFile

if not _M_MPMS.__dict__.has_key('_t_NetFileList'):
    _M_MPMS._t_NetFileList = IcePy.defineSequence('::MPMS::NetFileList', _M_MPMS._t_NetFile)

if not _M_MPMS.__dict__.has_key('EventMediaPlay'):
    _M_MPMS.EventMediaPlay = Ice.createTempClass()
    class EventMediaPlay(object):
        def __init__(self, midiaId='', event='', fpcIp='', fpcMac='', startTime=0, endTime=0):
            self.midiaId = midiaId
            self.event = event
            self.fpcIp = fpcIp
            self.fpcMac = fpcMac
            self.startTime = startTime
            self.endTime = endTime

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.midiaId)
            _h = 5 * _h + __builtin__.hash(self.event)
            _h = 5 * _h + __builtin__.hash(self.fpcIp)
            _h = 5 * _h + __builtin__.hash(self.fpcMac)
            _h = 5 * _h + __builtin__.hash(self.startTime)
            _h = 5 * _h + __builtin__.hash(self.endTime)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.midiaId == other.midiaId:
                return False
            if not self.event == other.event:
                return False
            if not self.fpcIp == other.fpcIp:
                return False
            if not self.fpcMac == other.fpcMac:
                return False
            if not self.startTime == other.startTime:
                return False
            if not self.endTime == other.endTime:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_EventMediaPlay)

        __repr__ = __str__

    _M_MPMS._t_EventMediaPlay = IcePy.defineStruct('::MPMS::EventMediaPlay', EventMediaPlay, (
        ("midiaId", IcePy._t_string),
        ("event", IcePy._t_string),
        ("fpcIp", IcePy._t_string),
        ("fpcMac", IcePy._t_string),
        ("startTime", IcePy._t_int),
        ("endTime", IcePy._t_int)
    ))

    _M_MPMS.EventMediaPlay = EventMediaPlay
    del EventMediaPlay

if not _M_MPMS.__dict__.has_key('_t_EventMediaPlayList'):
    _M_MPMS._t_EventMediaPlayList = IcePy.defineSequence('::MPMS::EventMediaPlayList', _M_MPMS._t_EventMediaPlay)

if not _M_MPMS.__dict__.has_key('FrontDispatchController'):
    _M_MPMS.FrontDispatchController = Ice.createTempClass()
    class FrontDispatchController(Ice.Object):
        def __init__(self):
            if __builtin__.type(self) == _M_MPMS.FrontDispatchController:
                raise RuntimeError('MPMS.FrontDispatchController is an abstract class')

        def ice_ids(self, current=None):
            return ('::Ice::Object', '::MPMS::FrontDispatchController')

        def ice_id(self, current=None):
            return '::MPMS::FrontDispatchController'

        #
        # Operation signatures.
        #
        # def RegisterFPC(self, fpcIdent, fpc, current=None):
        # def GetFPCSettings(self, current=None):
        # def GetParameter(self, current=None):
        # def ReportMideaPlayEvent(self, fdcid, list, current=None):

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_FrontDispatchController)

        __repr__ = __str__

    _M_MPMS.FrontDispatchControllerPrx = Ice.createTempClass()
    class FrontDispatchControllerPrx(Ice.ObjectPrx):

        def RegisterFPC(self, fpcIdent, fpc, _ctx=None):
            return _M_MPMS.FrontDispatchController._op_RegisterFPC.invoke(self, (fpcIdent, fpc), _ctx)

        def GetFPCSettings(self, _ctx=None):
            return _M_MPMS.FrontDispatchController._op_GetFPCSettings.invoke(self, (), _ctx)

        def GetParameter(self, _ctx=None):
            return _M_MPMS.FrontDispatchController._op_GetParameter.invoke(self, (), _ctx)

        def ReportMideaPlayEvent(self, fdcid, list, _ctx=None):
            return _M_MPMS.FrontDispatchController._op_ReportMideaPlayEvent.invoke(self, (fdcid, list), _ctx)

        def checkedCast(proxy, facetOrCtx=None, _ctx=None):
            return _M_MPMS.FrontDispatchControllerPrx.ice_checkedCast(proxy, '::MPMS::FrontDispatchController', facetOrCtx, _ctx)
        checkedCast = staticmethod(checkedCast)

        def uncheckedCast(proxy, facet=''):
            return _M_MPMS.FrontDispatchControllerPrx.ice_uncheckedCast(proxy, facet)
        uncheckedCast = staticmethod(uncheckedCast)

    _M_MPMS._t_FrontDispatchControllerPrx = IcePy.defineProxy('::MPMS::FrontDispatchController', FrontDispatchControllerPrx)

    _M_MPMS._t_FrontDispatchController = IcePy.defineClass('::MPMS::FrontDispatchController', FrontDispatchController, True, None, (), ())
    FrontDispatchController.ice_type = _M_MPMS._t_FrontDispatchController

    FrontDispatchController._op_RegisterFPC = IcePy.Operation('RegisterFPC', Ice.OperationMode.Normal, False, (_M_Ice._t_Identity, _M_MPMS._t_fpcParameter), (), IcePy._t_bool, ())
    FrontDispatchController._op_GetFPCSettings = IcePy.Operation('GetFPCSettings', Ice.OperationMode.Normal, False, (), (), _M_MPMS._t_fpcSetting, ())
    FrontDispatchController._op_GetParameter = IcePy.Operation('GetParameter', Ice.OperationMode.Normal, False, (), (), _M_MPMS._t_fdcParameter, ())
    FrontDispatchController._op_ReportMideaPlayEvent = IcePy.Operation('ReportMideaPlayEvent', Ice.OperationMode.Normal, False, (IcePy._t_string, _M_MPMS._t_EventMediaPlayList), (), None, ())

    _M_MPMS.FrontDispatchController = FrontDispatchController
    del FrontDispatchController

    _M_MPMS.FrontDispatchControllerPrx = FrontDispatchControllerPrx
    del FrontDispatchControllerPrx

if not _M_MPMS.__dict__.has_key('FtpServer'):
    _M_MPMS.FtpServer = Ice.createTempClass()
    class FtpServer(object):
        def __init__(self, host='', port='', user='', passwd=''):
            self.host = host
            self.port = port
            self.user = user
            self.passwd = passwd

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.host)
            _h = 5 * _h + __builtin__.hash(self.port)
            _h = 5 * _h + __builtin__.hash(self.user)
            _h = 5 * _h + __builtin__.hash(self.passwd)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.host == other.host:
                return False
            if not self.port == other.port:
                return False
            if not self.user == other.user:
                return False
            if not self.passwd == other.passwd:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_FtpServer)

        __repr__ = __str__

    _M_MPMS._t_FtpServer = IcePy.defineStruct('::MPMS::FtpServer', FtpServer, (
        ("host", IcePy._t_string),
        ("port", IcePy._t_string),
        ("user", IcePy._t_string),
        ("passwd", IcePy._t_string)
    ))

    _M_MPMS.FtpServer = FtpServer
    del FtpServer

if not _M_MPMS.__dict__.has_key('SystemDistribution'):
    _M_MPMS.SystemDistribution = Ice.createTempClass()
    class SystemDistribution(object):
        def __init__(self, subsys='', version='', fileList=None):
            self.subsys = subsys
            self.version = version
            self.fileList = fileList

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.subsys)
            _h = 5 * _h + __builtin__.hash(self.version)
            if self.fileList:
                for _i0 in self.fileList:
                    _h = 5 * _h + __builtin__.hash(_i0)
            return _h % 0x7fffffff

        def __eq__(self, other):
            if not self.subsys == other.subsys:
                return False
            if not self.version == other.version:
                return False
            if not self.fileList == other.fileList:
                return False
            return True

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_SystemDistribution)

        __repr__ = __str__

    _M_MPMS._t_SystemDistribution = IcePy.defineStruct('::MPMS::SystemDistribution', SystemDistribution, (
        ("subsys", IcePy._t_string),
        ("version", IcePy._t_string),
        ("fileList", _M_MPMS._t_NetFileList)
    ))

    _M_MPMS.SystemDistribution = SystemDistribution
    del SystemDistribution

if not _M_MPMS.__dict__.has_key('CentreMangementSystem'):
    _M_MPMS.CentreMangementSystem = Ice.createTempClass()
    class CentreMangementSystem(_M_MPMS.FrontDispatchController):
        def __init__(self):
            if __builtin__.type(self) == _M_MPMS.CentreMangementSystem:
                raise RuntimeError('MPMS.CentreMangementSystem is an abstract class')

        def ice_ids(self, current=None):
            return ('::Ice::Object', '::MPMS::CentreMangementSystem', '::MPMS::FrontDispatchController')

        def ice_id(self, current=None):
            return '::MPMS::CentreMangementSystem'

        #
        # Operation signatures.
        #
        # def GetPlayPolicies(self, fdcID, current=None):
        # def GetfpcControlInfo(self, fdcID, current=None):
        # def RegisterFDC(self, fdcIdent, current=None):
        # def SyncSystem(self, moduleType, version, current=None):
        # def GetFtpServer(self, current=None):

        def __str__(self):
            return IcePy.stringify(self, _M_MPMS._t_CentreMangementSystem)

        __repr__ = __str__

    _M_MPMS.CentreMangementSystemPrx = Ice.createTempClass()
    class CentreMangementSystemPrx(_M_MPMS.FrontDispatchControllerPrx):

        def GetPlayPolicies(self, fdcID, _ctx=None):
            return _M_MPMS.CentreMangementSystem._op_GetPlayPolicies.invoke(self, (fdcID, ), _ctx)

        def GetfpcControlInfo(self, fdcID, _ctx=None):
            return _M_MPMS.CentreMangementSystem._op_GetfpcControlInfo.invoke(self, (fdcID, ), _ctx)

        def RegisterFDC(self, fdcIdent, _ctx=None):
            return _M_MPMS.CentreMangementSystem._op_RegisterFDC.invoke(self, (fdcIdent, ), _ctx)

        def SyncSystem(self, moduleType, version, _ctx=None):
            return _M_MPMS.CentreMangementSystem._op_SyncSystem.invoke(self, (moduleType, version), _ctx)

        def GetFtpServer(self, _ctx=None):
            return _M_MPMS.CentreMangementSystem._op_GetFtpServer.invoke(self, (), _ctx)

        def checkedCast(proxy, facetOrCtx=None, _ctx=None):
            return _M_MPMS.CentreMangementSystemPrx.ice_checkedCast(proxy, '::MPMS::CentreMangementSystem', facetOrCtx, _ctx)
        checkedCast = staticmethod(checkedCast)

        def uncheckedCast(proxy, facet=''):
            return _M_MPMS.CentreMangementSystemPrx.ice_uncheckedCast(proxy, facet)
        uncheckedCast = staticmethod(uncheckedCast)

    _M_MPMS._t_CentreMangementSystemPrx = IcePy.defineProxy('::MPMS::CentreMangementSystem', CentreMangementSystemPrx)

    _M_MPMS._t_CentreMangementSystem = IcePy.defineClass('::MPMS::CentreMangementSystem', CentreMangementSystem, True, None, (_M_MPMS._t_FrontDispatchController,), ())
    CentreMangementSystem.ice_type = _M_MPMS._t_CentreMangementSystem

    CentreMangementSystem._op_GetPlayPolicies = IcePy.Operation('GetPlayPolicies', Ice.OperationMode.Normal, False, (IcePy._t_string,), (), _M_MPMS._t_PlayPolicyList, ())
    CentreMangementSystem._op_GetfpcControlInfo = IcePy.Operation('GetfpcControlInfo', Ice.OperationMode.Normal, False, (IcePy._t_string,), (), _M_MPMS._t_fpcControlInfo, ())
    CentreMangementSystem._op_RegisterFDC = IcePy.Operation('RegisterFDC', Ice.OperationMode.Normal, False, (_M_Ice._t_Identity,), (), IcePy._t_bool, ())
    CentreMangementSystem._op_SyncSystem = IcePy.Operation('SyncSystem', Ice.OperationMode.Normal, False, (IcePy._t_string, IcePy._t_string), (), _M_MPMS._t_SystemDistribution, ())
    CentreMangementSystem._op_GetFtpServer = IcePy.Operation('GetFtpServer', Ice.OperationMode.Normal, False, (), (), _M_MPMS._t_FtpServer, ())

    _M_MPMS.CentreMangementSystem = CentreMangementSystem
    del CentreMangementSystem

    _M_MPMS.CentreMangementSystemPrx = CentreMangementSystemPrx
    del CentreMangementSystemPrx

# End of module MPMS
