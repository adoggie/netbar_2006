import time,sys,os,traceback,array
import Ice
#Ice.loadSlice('../idl/mps.ice')
from  MPMS import *



def test_fdc():
    try:
        props = Ice.createProperties()
        c = Ice.initializeWithProperties(sys.argv,props)
        fdc = FrontDispatchControllerPrx.checkedCast(c.stringToProxy("fdc:tcp -h 192.168.14.10 -p 4501"))
        print fdc.GetFPCSettings()
        fpc = fpcParameter()
        fpc.ip='192.168.14.16'
        fpc.mac='00-01-02-03'
        #fdc.ReportMideaPlayEvent('',[EventMediaPlay('m1','qq','192.168.14.2','11-11-11',0,100)])
    except:
        print traceback.print_exc()


def test_cms():
    try:
        props = Ice.createProperties()
        c = Ice.initializeWithProperties(sys.argv,props)
        cms = CentreMangementSystemPrx.checkedCast(c.stringToProxy("cms:tcp -h 192.168.14.10 -p 4502"))
        fpc = fpcParameter()
        fpc.ip='192.168.14.11'
        fpc.mac='00-01-02-03'
        iden = Ice.stringToIdentity('test')
        #cms.RegisterFDC(iden)
        #print cms.GetfpcControlInfo('')
        print cms.GetPlayPolicies('')
        #ftp = cms.GetFtpServer()
        #set = cms.GetPlayPolicies('')
        print cms.GetFPCSettings()
    except:
        print traceback.print_exc()
#====
#
try:
    test_fdc()
except:
    print traceback.print_exc()
#test_cms()
#time.sleep(1000)
