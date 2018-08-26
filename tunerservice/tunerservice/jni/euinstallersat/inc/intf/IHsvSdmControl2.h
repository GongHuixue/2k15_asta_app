#ifndef IHSVSDMCONTROL2_H
#define IHSVSDMCONTROL2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmControl2
{
public:
	virtual ~IHsvSdmControl2(){}
	#define IHsvSdmControl2_Idle				((int)0 )
	#define IHsvSdmControl2_Minimal				((int)1 )
	#define IHsvSdmControl2_Normal				((int)2 )
	#define IHsvSdmControl2_External			((int)3 )
	#define IHsvSdmControl2_CrossCarraige		((int)4 )
	#define IHsvSdmControl2_NormalPlusPmt		((int)5 )
	#define IHsvSdmControl2_M7Minimal			((int)6 )
	#define IHsvSdmControl2_HomingMuxData		((int)7 )
	#define IHsvSdmControl2_PkgBuildMode		((int)8 )
	#define IHsvSdmControl2_FransatNormal		((int)9 )
	#define IHsvSdmControl2_MinimalPlusBat		((int)10 )
	#define IHsvSdmControl2_FreesatMinimalNitAct ((int)11 )
	#define IHsvSdmControl2_FreesatPostcode		((int)12 )
	#define IHsvSdmControl2_FreesatNormal		((int)13 )
	#define IHsvSdmControl2_FreesatMinimalNitOth ((int)14 )
	#define IHsvSdmControl2_FreesatPSIMode		((int)15)
	#define IHsvSdmControl2_FreesatMinimalSdtOth ((int)16)
	#define IHsvSdmControl2_AstraSGT			((int)17 )
	#define IHsvSdmControl2_TricolorNormal		((int)18)	
	#define IHsvSdmControl2_TricolorRegionScanMode	((int)19)
	#define IHsvSdmControl2_FransatCamIns		((int)20 )
	#define IHsvSdmControl2_Invalid		((int)0 )
	#define IHsvSdmControl2_NoDataAvailable		((int)1 )
	#define IHsvSdmControl2_OnlyPsiDataAvailable ((int)2 )
	#define IHsvSdmControl2_SiDataAvailable		((int)3 )
	#define IHsvSdmControl2_NITAvailable		((int)4 )
	#define IHsvSdmControl2_SDTAvailable		((int)5 )
	#define IHsvSdmControl2_FNTAvailable		((int)6 )
	#define IHsvSdmControl2_FSTAvailable		((int)7 )
	#define IHsvSdmControl2_BATAvailable		((int)8 )
	#define IHsvSdmControl2_TOTAvailable		((int)9 )
	
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
