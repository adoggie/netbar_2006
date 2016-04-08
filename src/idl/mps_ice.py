# **********************************************************************
#
# Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

# Ice version 2.1.2
# Generated from file `mps.ice'

import Ice, IcePy, __builtin__

# Start of module MPMS
_M_MPMS = Ice.openModule('MPMS')
__name__ = 'MPMS'

_M_MPMS.fpcSetting = Ice.createTempClass()
class fpcSetting(object):
    def __init__(self, ieDefaultAddr='', wallpaper='', alNotification='', alAdvertisement=''):
        self.ieDefaultAddr = ieDefaultAddr
        self.wallpaper = wallpaper
        self.alNotification = alNotification
        self.alAdvertisement = alAdvertisement

    def __hash__(self):
        _h = 0
        _h = 5 * _h + __builtin__.hash(self.ieDefaultAddr)
        _h = 5 * _h + __builtin__.hash(self.wallpaper)
        _h = 5 * _h + __builtin__.hash(self.alNotification)
        _h = 5 * _h + __builtin__.hash(self.alAdvertisement)
        return _h % 0x7fffffff

    def __eq__(self, other):
        if not self.ieDefaultAddr == other.ieDefaultAddr:
            return False
        if not self.wallpaper == other.wallpaper:
            return False
        if not self.alNotification == other.alNotification:
            return False
        if not self.alAdvertisement == other.alAdvertisement:
            return False
        return True

    def __str__(self):
        return IcePy.stringify(self, _M_MPMS._t_fpcSetting)

    __repr__ = __str__

_M_MPMS._t_fpcSetting = IcePy.defineStruct('::MPMS::fpcSetting', fpcSetting, (
    ("ieDefaultAddr", IcePy._t_string),
    ("wallpaper", IcePy._t_string),
    ("alNotification", IcePy._t_string),
    ("alAdvertisement", IcePy._t_string)
))

_M_MPMS.fpcSetting = fpcSetting
del fpcSetting

_M_MPMS.MediaControlInfo = Ice.createTempClass()
class MediaControlInfo(object):
    def __init__(self, url='', player='', width=0, height=0):
        self.url = url
        self.player = player
        self.width = width
        self.height = height

    def __hash__(self):
        _h = 0
        _h = 5 * _h + __builtin__.hash(self.url)
        _h = 5 * _h + __builtin__.hash(self.player)
        _h = 5 * _h + __builtin__.hash(self.width)
        _h = 5 * _h + __builtin__.hash(self.height)
        return _h % 0x7fffffff

    def __eq__(self, other):
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
    ("url", IcePy._t_string),
    ("player", IcePy._t_string),
    ("width", IcePy._t_int),
    ("height", IcePy._t_int)
))

_M_MPMS.MediaControlInfo = MediaControlInfo
del MediaControlInfo

_M_MPMS._t_MediaControlInfoList = IcePy.defineSequence('::MPMS::MediaControlInfoList', _M_MPMS._t_MediaControlInfo)

_M_MPMS.PlayPolicy = Ice.createTempClass()
class PlayPolicy(object):
    def __init__(self, fpcs=_M_MPMS.fpcSetting(), qq=_M_MPMS.MediaControlInfo(), msn=_M_MPMS.MediaControlInfo()):
        self.fpcs = fpcs
        self.qq = qq
        self.msn = msn

    def __hash__(self):
        _h = 0
        _h = 5 * _h + __builtin__.hash(self.fpcs)
        _h = 5 * _h + __builtin__.hash(self.qq)
        _h = 5 * _h + __builtin__.hash(self.msn)
        return _h % 0x7fffffff

    def __eq__(self, other):
        if not self.fpcs == other.fpcs:
            return False
        if not self.qq == other.qq:
            return False
        if not self.msn == other.msn:
            return False
        return True

    def __str__(self):
        return IcePy.stringify(self, _M_MPMS._t_PlayPolicy)

    __repr__ = __str__

_M_MPMS._t_PlayPolicy = IcePy.defineStruct('::MPMS::PlayPolicy', PlayPolicy, (
    ("fpcs", _M_MPMS._t_fpcSetting),
    ("qq", _M_MPMS._t_MediaControlInfo),
    ("msn", _M_MPMS._t_MediaControlInfo)
))

_M_MPMS.PlayPolicy = PlayPolicy
del PlayPolicy

_M_MPMS._t_PlayPolicyList = IcePy.defineSequence('::MPMS::PlayPolicyList', _M_MPMS._t_PlayPolicy)

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

    def __str__(self):
        return IcePy.stringify(self, _M_MPMS._t_FrontPlayController)

    __repr__ = __str__

_M_MPMS.FrontPlayControllerPrx = Ice.createTempClass()
class FrontPlayControllerPrx(Ice.ObjectPrx):

    def ChangeSetting(self, setting, _ctx=None):
        return _M_MPMS.FrontPlayController._op_ChangeSetting.invoke(self, (setting, ), _ctx)

    def GetType(self, _ctx=None):
        return _M_MPMS.FrontPlayController._op_GetType.invoke(self, (), _ctx)

    def checkedCast(proxy, facet='', _ctx=None):
        return _M_MPMS.FrontPlayControllerPrx.ice_checkedCast(proxy, '::MPMS::FrontPlayController', facet, _ctx)
    checkedCast = staticmethod(checkedCast)

    def uncheckedCast(proxy, facet=''):
        return _M_MPMS.FrontPlayControllerPrx.ice_uncheckedCast(proxy, facet)
    uncheckedCast = staticmethod(uncheckedCast)

_M_MPMS._t_FrontPlayControllerPrx = IcePy.defineProxy('::MPMS::FrontPlayController', FrontPlayControllerPrx)

_M_MPMS._t_FrontPlayController = IcePy.defineClass('::MPMS::FrontPlayController', FrontPlayController, True, None, (), ())
FrontPlayController.ice_type = _M_MPMS._t_FrontPlayController

FrontPlayController._op_ChangeSetting = IcePy.Operation('ChangeSetting', Ice.OperationMode.Normal, False, (_M_MPMS._t_fpcSetting,), (), None, ())
FrontPlayController._op_GetType = IcePy.Operation('GetType', Ice.OperationMode.Normal, False, (), (), IcePy._t_string, ())

_M_MPMS.FrontPlayController = FrontPlayController
del FrontPlayController

_M_MPMS.FrontPlayControllerPrx = FrontPlayControllerPrx
del FrontPlayControllerPrx

_M_MPMS._t_ByteList = IcePy.defineSequence('::MPMS::ByteList', IcePy._t_byte)

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
    # def RegisterFPC(self, fpc, anystr, digest, current=None):
    # def GetMediaControlInfo(self, event, current=None):

    def __str__(self):
        return IcePy.stringify(self, _M_MPMS._t_FrontDispatchController)

    __repr__ = __str__

_M_MPMS.FrontDispatchControllerPrx = Ice.createTempClass()
class FrontDispatchControllerPrx(Ice.ObjectPrx):

    def RegisterFPC(self, fpc, anystr, digest, _ctx=None):
        return _M_MPMS.FrontDispatchController._op_RegisterFPC.invoke(self, (fpc, anystr, digest), _ctx)

    def GetMediaControlInfo(self, event, _ctx=None):
        return _M_MPMS.FrontDispatchController._op_GetMediaControlInfo.invoke(self, (event, ), _ctx)

    def checkedCast(proxy, facet='', _ctx=None):
        return _M_MPMS.FrontDispatchControllerPrx.ice_checkedCast(proxy, '::MPMS::FrontDispatchController', facet, _ctx)
    checkedCast = staticmethod(checkedCast)

    def uncheckedCast(proxy, facet=''):
        return _M_MPMS.FrontDispatchControllerPrx.ice_uncheckedCast(proxy, facet)
    uncheckedCast = staticmethod(uncheckedCast)

_M_MPMS._t_FrontDispatchControllerPrx = IcePy.defineProxy('::MPMS::FrontDispatchController', FrontDispatchControllerPrx)

_M_MPMS._t_FrontDispatchController = IcePy.defineClass('::MPMS::FrontDispatchController', FrontDispatchController, True, None, (), ())
FrontDispatchController.ice_type = _M_MPMS._t_FrontDispatchController

FrontDispatchController._op_RegisterFPC = IcePy.Operation('RegisterFPC', Ice.OperationMode.Normal, False, (_M_MPMS._t_FrontPlayControllerPrx, IcePy._t_string, _M_MPMS._t_ByteList), (), None, ())
FrontDispatchController._op_GetMediaControlInfo = IcePy.Operation('GetMediaControlInfo', Ice.OperationMode.Normal, False, (_M_MPMS._t_fpcCatchedEvent,), (), _M_MPMS._t_MediaControlInfoList, ())

_M_MPMS.FrontDispatchController = FrontDispatchController
del FrontDispatchController

_M_MPMS.FrontDispatchControllerPrx = FrontDispatchControllerPrx
del FrontDispatchControllerPrx

_M_MPMS.CentreMangementSystem = Ice.createTempClass()
class CentreMangementSystem(Ice.Object):
    def __init__(self):
        if __builtin__.type(self) == _M_MPMS.CentreMangementSystem:
            raise RuntimeError('MPMS.CentreMangementSystem is an abstract class')

    def ice_ids(self, current=None):
        return ('::Ice::Object', '::MPMS::CentreMangementSystem')

    def ice_id(self, current=None):
        return '::MPMS::CentreMangementSystem'

    #
    # Operation signatures.
    #
    # def GetMediaControlInfo(self, event, current=None):
    # def GetPlayPolicies(self, fdcID, current=None):

    def __str__(self):
        return IcePy.stringify(self, _M_MPMS._t_CentreMangementSystem)

    __repr__ = __str__

_M_MPMS.CentreMangementSystemPrx = Ice.createTempClass()
class CentreMangementSystemPrx(Ice.ObjectPrx):

    def GetMediaControlInfo(self, event, _ctx=None):
        return _M_MPMS.CentreMangementSystem._op_GetMediaControlInfo.invoke(self, (event, ), _ctx)

    def GetPlayPolicies(self, fdcID, _ctx=None):
        return _M_MPMS.CentreMangementSystem._op_GetPlayPolicies.invoke(self, (fdcID, ), _ctx)

    def checkedCast(proxy, facet='', _ctx=None):
        return _M_MPMS.CentreMangementSystemPrx.ice_checkedCast(proxy, '::MPMS::CentreMangementSystem', facet, _ctx)
    checkedCast = staticmethod(checkedCast)

    def uncheckedCast(proxy, facet=''):
        return _M_MPMS.CentreMangementSystemPrx.ice_uncheckedCast(proxy, facet)
    uncheckedCast = staticmethod(uncheckedCast)

_M_MPMS._t_CentreMangementSystemPrx = IcePy.defineProxy('::MPMS::CentreMangementSystem', CentreMangementSystemPrx)

_M_MPMS._t_CentreMangementSystem = IcePy.defineClass('::MPMS::CentreMangementSystem', CentreMangementSystem, True, None, (), ())
CentreMangementSystem.ice_type = _M_MPMS._t_CentreMangementSystem

CentreMangementSystem._op_GetMediaControlInfo = IcePy.Operation('GetMediaControlInfo', Ice.OperationMode.Normal, False, (_M_MPMS._t_fpcCatchedEvent,), (), _M_MPMS._t_MediaControlInfoList, ())
CentreMangementSystem._op_GetPlayPolicies = IcePy.Operation('GetPlayPolicies', Ice.OperationMode.Normal, False, (IcePy._t_string,), (), _M_MPMS._t_PlayPolicyList, ())

_M_MPMS.CentreMangementSystem = CentreMangementSystem
del CentreMangementSystem

_M_MPMS.CentreMangementSystemPrx = CentreMangementSystemPrx
del CentreMangementSystemPrx

# End of module MPMS
