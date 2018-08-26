#ifndef IHSVDESTINATIONCONFIGURATION_H
#define IHSVDESTINATIONCONFIGURATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDestinationConfiguration
{
public:
	virtual ~IHsvDestinationConfiguration(){}
	virtual int iVersion(void)= 0;
	virtual int NoOfDestinations(void)= 0;
	virtual Nat16 destPropVideo(void)= 0;
	virtual Nat16 destPropAudio(void)= 0;
	virtual Nat16 destPropLockable(void)= 0;
	virtual Bool IsMemberDestination(HsvDestination memberDest,HsvDestination grpDest)= 0;
	virtual Nat32 GetMemberDestinations(HsvDestination grpDest)= 0;
	virtual Bool IsDestinationSupported(HsvDestination Dest)= 0;
	virtual Bool IsAudioOnlyDestination(HsvDestination Dest)= 0;
	virtual Bool IsGroupDestination(HsvDestination Dest)= 0;
	virtual Bool CheckProperty(HsvDestination dest,Nat16 prop)= 0;
};


#define IHsvDestinationConfigurationImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Nat16>;\
friend class InterfaceParam<Comp,Nat16>;\
friend class InterfaceParam<Comp,Nat16>;\
virtual Bool intf ## _IsMemberDestination(HsvDestination memberDest,HsvDestination grpDest);\
virtual Nat32 intf ## _GetMemberDestinations(HsvDestination grpDest);\
virtual Bool intf ## _IsDestinationSupported(HsvDestination Dest);\
virtual Bool intf ## _IsAudioOnlyDestination(HsvDestination Dest);\
virtual Bool intf ## _IsGroupDestination(HsvDestination Dest);\
virtual Bool intf ## _CheckProperty(HsvDestination dest,Nat16 prop);\
class Comp ## _ ## intf : public IHsvDestinationConfiguration \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    InterfaceParam<Comp,int> m_NoOfDestinations; \
    InterfaceParam<Comp,Nat16> m_destPropVideo; \
    InterfaceParam<Comp,Nat16> m_destPropAudio; \
    InterfaceParam<Comp,Nat16> m_destPropLockable; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent),m_NoOfDestinations(parent),m_destPropVideo(parent),m_destPropAudio(parent),m_destPropLockable(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
virtual int NoOfDestinations(void){ return m_NoOfDestinations.Call();}\
virtual Nat16 destPropVideo(void){ return m_destPropVideo.Call();}\
virtual Nat16 destPropAudio(void){ return m_destPropAudio.Call();}\
virtual Nat16 destPropLockable(void){ return m_destPropLockable.Call();}\
virtual Bool IsMemberDestination(HsvDestination memberDest,HsvDestination grpDest){ return m_parent->intf ## _IsMemberDestination(memberDest,grpDest);}\
virtual Nat32 GetMemberDestinations(HsvDestination grpDest){ return m_parent->intf ## _GetMemberDestinations(grpDest);}\
virtual Bool IsDestinationSupported(HsvDestination Dest){ return m_parent->intf ## _IsDestinationSupported(Dest);}\
virtual Bool IsAudioOnlyDestination(HsvDestination Dest){ return m_parent->intf ## _IsAudioOnlyDestination(Dest);}\
virtual Bool IsGroupDestination(HsvDestination Dest){ return m_parent->intf ## _IsGroupDestination(Dest);}\
virtual Bool CheckProperty(HsvDestination dest,Nat16 prop){ return m_parent->intf ## _CheckProperty(dest,prop);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
