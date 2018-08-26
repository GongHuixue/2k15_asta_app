#ifndef IHSVCAMSCANHELPER_H
#define IHSVCAMSCANHELPER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCamScanHelper
{
public:
	virtual ~IHsvCamScanHelper(){}
	virtual Bool CamNitParser_Parser(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr)= 0;
	virtual int GetCamInstallationMode(void)= 0;
	virtual void SetCharacterCode(char* characterCode)= 0;
};


#define IHsvCamScanHelperImpl(Comp,intf)    \
virtual Bool intf ## _CamNitParser_Parser(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr);\
virtual int intf ## _GetCamInstallationMode(void);\
virtual void intf ## _SetCharacterCode(char* characterCode);\
class Comp ## _ ## intf : public IHsvCamScanHelper \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool CamNitParser_Parser(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr){ return m_parent->intf ## _CamNitParser_Parser(dest,cookie,DataSize,DataPtr);}\
virtual int GetCamInstallationMode(void){ return m_parent->intf ## _GetCamInstallationMode();}\
virtual void SetCharacterCode(char* characterCode){ return m_parent->intf ## _SetCharacterCode(characterCode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
