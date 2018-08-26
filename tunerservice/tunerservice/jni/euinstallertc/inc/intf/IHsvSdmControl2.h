#ifndef IHSVSDMCONTROL2_H
#define IHSVSDMCONTROL2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmControl2
{
public:
	virtual ~IHsvSdmControl2(){}
	#define IHsvSdmControl2_Idle		((int)0 )
	#define IHsvSdmControl2_Minimal		((int)1 )
	#define IHsvSdmControl2_Normal		((int)2 )
	#define IHsvSdmControl2_External		((int)3 )
	#define IHsvSdmControl2_CrossCarraige		((int)4 )
	#define IHsvSdmControl2_Invalid		((int)0 )
	#define IHsvSdmControl2_NoDataAvailable		((int)1 )
	#define IHsvSdmControl2_OnlyPsiDataAvailable		((int)2 )
	#define IHsvSdmControl2_SiDataAvailable		((int)3 )
	#define IHsvSdmControl2_NITAvailable		((int)4 )
	#define IHsvSdmControl2_SDTAvailable		((int)5 )
	virtual int GetMode(HsvDemux dmx)= 0;
	virtual int GetStatus(HsvDemux dmx)= 0;
	virtual void StartCollection(HsvDemux dmx,int mode)= 0;
	virtual void StopCollection(HsvDemux dmx)= 0;
};


#define IHsvSdmControl2Impl(Comp,intf)    \
virtual int intf ## _GetMode(HsvDemux dmx);\
virtual int intf ## _GetStatus(HsvDemux dmx);\
virtual void intf ## _StartCollection(HsvDemux dmx,int mode);\
virtual void intf ## _StopCollection(HsvDemux dmx);\
class Comp ## _ ## intf : public IHsvSdmControl2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetMode(HsvDemux dmx){ return m_parent->intf ## _GetMode(dmx);}\
virtual int GetStatus(HsvDemux dmx){ return m_parent->intf ## _GetStatus(dmx);}\
virtual void StartCollection(HsvDemux dmx,int mode){ return m_parent->intf ## _StartCollection(dmx,mode);}\
virtual void StopCollection(HsvDemux dmx){ return m_parent->intf ## _StopCollection(dmx);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
