#ifndef ITVPLATFORMRESOURCE_H
#define ITVPLATFORMRESOURCE_H
#include <intfparam.h>
#include <provreq.h>
class ITvPlatformResource
{
public:
	virtual ~ITvPlatformResource(){}
	virtual Bool IsResourceOwned(Nat32 resid)= 0;
	virtual Nat32 GetOwnedResources(void)= 0;
	#define ITvPlatformResource_AudioFeaturing		((Nat32)0x00000001 )
	#define ITvPlatformResource_Connectivity		((Nat32)0x00000002 )
	#define ITvPlatformResource_Frontend		((Nat32)0x00000004 )
	#define ITvPlatformResource_General		((Nat32)0x00000008 )
	#define ITvPlatformResource_Infrastructure		((Nat32)0x00000010 )
	#define ITvPlatformResource_Source		((Nat32)0x00000020 )
	#define ITvPlatformResource_VideoFeaturing		((Nat32)0x00000040 )
	#define ITvPlatformResource_Xray		((Nat32)0x00000080 )
	#define ITvPlatformResource_Scale		((Nat32)0x00000100 )
	#define ITvPlatformResource_Gfx		((Nat32)0x00000200 )
	#define ITvPlatformResource_Mute		((Nat32)0x00000400 )
	virtual int GetResourceState(void)= 0;
	virtual void RequestResourceState(int State)= 0;
	virtual void RestorePreviousState(void)= 0;
	#define ITvPlatformResource_FullState		((int)1 )
	#define ITvPlatformResource_SubState		((int)2 )
	#define ITvPlatformResource_IdleState		((int)3 )
	#define ITvPlatformResource_FullStateWithVideoScale		((int)4 )
	#define ITvPlatformResource_Invalid		((int)-1 )
	#define ITvPlatformResource_FullWithScaleState		((int)5 )
	#define ITvPlatformResource_IdleWithMuteState		((int)6 )
	#define ITvPlatformResource_FullStateWithOutMute		((int)7 )
	#define ITvPlatformResource_FrontEndState		((int)8 )
	#define ITvPlatformResource_ScaleState		((int)9 )
};


#define ITvPlatformResourceImpl(Comp,intf)    \
virtual Bool intf ## _IsResourceOwned(Nat32 resid);\
virtual Nat32 intf ## _GetOwnedResources(void);\
virtual int intf ## _GetResourceState(void);\
virtual void intf ## _RequestResourceState(int State);\
virtual void intf ## _RestorePreviousState(void);\
class Comp ## _ ## intf : public ITvPlatformResource \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool IsResourceOwned(Nat32 resid){ return m_parent->intf ## _IsResourceOwned(resid);}\
virtual Nat32 GetOwnedResources(void){ return m_parent->intf ## _GetOwnedResources();}\
virtual int GetResourceState(void){ return m_parent->intf ## _GetResourceState();}\
virtual void RequestResourceState(int State){ return m_parent->intf ## _RequestResourceState(State);}\
virtual void RestorePreviousState(void){ return m_parent->intf ## _RestorePreviousState();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
