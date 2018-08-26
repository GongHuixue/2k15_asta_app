#ifndef IHSVSDMCONTROLNOTIFYEX_H
#define IHSVSDMCONTROLNOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmControlNotifyEx
{
public:
	virtual ~IHsvSdmControlNotifyEx(){}
	#define IHsvSdmControlNotifyEx_DataNotAvailable		((int)0x00 )
	#define IHsvSdmControlNotifyEx_OnlyPsiDataAvailable		((int)0x01 )
	#define IHsvSdmControlNotifyEx_SiDataAvailable		((int)0x10 )
	#define IHsvSdmControlNotifyEx_StartedCollection		((int)0x11 )
	#define IHsvSdmControlNotifyEx_StoppedCollection		((int)0x100 )
	#define IHsvSdmControlNotifyEx_DataAvailable		((int)0x101 )
	#define IHsvSdmControlNotifyEx_SDT		((int)0x01 )
	#define IHsvSdmControlNotifyEx_NIT		((int)0x10 )
	#define IHsvSdmControlNotifyEx_EIT		((int)0x11 )
	#define IHsvSdmControlNotifyEx_TOT		((int)0x100 )
	#define IHsvSdmControlNotifyEx_TDT		((int)0x101 )
	#define IHsvSdmControlNotifyEx_PMT		((int)0x110 )
	#define IHsvSdmControlNotifyEx_PAT		((int)0x111 )
	#define IHsvSdmControlNotifyEx_CAT		((int)0x1000 )
	#define IHsvSdmControlNotifyEx_UNT		((int)0x1001 )
	virtual void OnEvent(HsvDemux dmx,int eventid,int value)= 0;
};


#define IHsvSdmControlNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnEvent(HsvDemux dmx,int eventid,int value);\
class Comp ## _ ## intf : public IHsvSdmControlNotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(HsvDemux dmx,int eventid,int value){ return m_parent->intf ## _OnEvent(dmx,eventid,value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
