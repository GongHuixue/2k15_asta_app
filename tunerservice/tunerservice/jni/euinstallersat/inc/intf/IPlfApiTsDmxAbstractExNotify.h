#ifndef IPLFAPITSDMXABSTRACTEXNOTIFY_H
#define IPLFAPITSDMXABSTRACTEXNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTsDmxAbstractExNotify
{
public:
	virtual ~IPlfApiTsDmxAbstractExNotify(){}
	virtual void OnBufferOverflow(int winid)= 0;
	virtual void OnRequestAllowed(int winid)= 0;
	virtual void OnRequestNotAllowed(int winid)= 0;
	virtual void OnRequestCancelled(int winid,Nat32 subscrId)= 0;
	virtual void OnRequestListCancelled(int winid,Nat32 subscrId)= 0;
	#define IPlfApiTsDmxAbstractExNotify_CrcStatusOk		((int)1 )
	#define IPlfApiTsDmxAbstractExNotify_CrcStatusNotOk		((int)2 )
	#define IPlfApiTsDmxAbstractExNotify_CrcStatusNotChecked		((int)3 )
	#define IPlfApiTsDmxAbstractExNotify_CrcStatusNoCrc		((int)4 )
	virtual void OnSectionArrived(int winid,Nat32 subscrId,int Cookie,int CrcStatus,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie)= 0;
	virtual void OnSectionListArrived(int winid,Nat32 subscrId,int Cookie,Nat32 ListCookie,Nat32 nSections,tmTsDmx_Section_t * sections)= 0;
	virtual void OnPesCancelled(int winid,Nat32 subscrId)= 0;
	virtual void OnPesArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie)= 0;
	virtual void OnPesListCancelled(int winid,Nat32 subscrId)= 0;
	virtual void OnPesListArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 ListCookie,Nat32 nPackets,tmTsDmx_Pes_t * packets)= 0;
	virtual void OnPcrPidStopped(int winid,Nat16 pid)= 0;
	virtual void OnAudioPidStopped(int winid,Nat16 pid)= 0;
	virtual void OnVideoPidStopped(int winid,Nat16 pid)= 0;
	virtual void OnAudioDescriptivePidStopped(int winid,Nat16 pid)= 0;
	virtual void OnScramblingStatusChanged(int winid,int MediaType,int status)= 0;
};


#define IPlfApiTsDmxAbstractExNotifyImpl(Comp,intf)    \
virtual void intf ## _OnBufferOverflow(int winid);\
virtual void intf ## _OnRequestAllowed(int winid);\
virtual void intf ## _OnRequestNotAllowed(int winid);\
virtual void intf ## _OnRequestCancelled(int winid,Nat32 subscrId);\
virtual void intf ## _OnRequestListCancelled(int winid,Nat32 subscrId);\
virtual void intf ## _OnSectionArrived(int winid,Nat32 subscrId,int Cookie,int CrcStatus,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie);\
virtual void intf ## _OnSectionListArrived(int winid,Nat32 subscrId,int Cookie,Nat32 ListCookie,Nat32 nSections,tmTsDmx_Section_t * sections);\
virtual void intf ## _OnPesCancelled(int winid,Nat32 subscrId);\
virtual void intf ## _OnPesArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie);\
virtual void intf ## _OnPesListCancelled(int winid,Nat32 subscrId);\
virtual void intf ## _OnPesListArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 ListCookie,Nat32 nPackets,tmTsDmx_Pes_t * packets);\
virtual void intf ## _OnPcrPidStopped(int winid,Nat16 pid);\
virtual void intf ## _OnAudioPidStopped(int winid,Nat16 pid);\
virtual void intf ## _OnVideoPidStopped(int winid,Nat16 pid);\
virtual void intf ## _OnAudioDescriptivePidStopped(int winid,Nat16 pid);\
virtual void intf ## _OnScramblingStatusChanged(int winid,int MediaType,int status);\
class Comp ## _ ## intf : public IPlfApiTsDmxAbstractExNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnBufferOverflow(int winid){ return m_parent->intf ## _OnBufferOverflow(winid);}\
virtual void OnRequestAllowed(int winid){ return m_parent->intf ## _OnRequestAllowed(winid);}\
virtual void OnRequestNotAllowed(int winid){ return m_parent->intf ## _OnRequestNotAllowed(winid);}\
virtual void OnRequestCancelled(int winid,Nat32 subscrId){ return m_parent->intf ## _OnRequestCancelled(winid,subscrId);}\
virtual void OnRequestListCancelled(int winid,Nat32 subscrId){ return m_parent->intf ## _OnRequestListCancelled(winid,subscrId);}\
virtual void OnSectionArrived(int winid,Nat32 subscrId,int Cookie,int CrcStatus,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie){ return m_parent->intf ## _OnSectionArrived(winid,subscrId,Cookie,CrcStatus,PSize,PAddr,SSize,SAddr,DataCookie);}\
virtual void OnSectionListArrived(int winid,Nat32 subscrId,int Cookie,Nat32 ListCookie,Nat32 nSections,tmTsDmx_Section_t * sections){ return m_parent->intf ## _OnSectionListArrived(winid,subscrId,Cookie,ListCookie,nSections,sections);}\
virtual void OnPesCancelled(int winid,Nat32 subscrId){ return m_parent->intf ## _OnPesCancelled(winid,subscrId);}\
virtual void OnPesArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 PSize,Address PAddr,Nat32 SSize,Address SAddr,Nat32 DataCookie){ return m_parent->intf ## _OnPesArrived(winid,subscrId,Cookie,PSize,PAddr,SSize,SAddr,DataCookie);}\
virtual void OnPesListCancelled(int winid,Nat32 subscrId){ return m_parent->intf ## _OnPesListCancelled(winid,subscrId);}\
virtual void OnPesListArrived(int winid,Nat32 subscrId,Nat32 Cookie,Nat32 ListCookie,Nat32 nPackets,tmTsDmx_Pes_t * packets){ return m_parent->intf ## _OnPesListArrived(winid,subscrId,Cookie,ListCookie,nPackets,packets);}\
virtual void OnPcrPidStopped(int winid,Nat16 pid){ return m_parent->intf ## _OnPcrPidStopped(winid,pid);}\
virtual void OnAudioPidStopped(int winid,Nat16 pid){ return m_parent->intf ## _OnAudioPidStopped(winid,pid);}\
virtual void OnVideoPidStopped(int winid,Nat16 pid){ return m_parent->intf ## _OnVideoPidStopped(winid,pid);}\
virtual void OnAudioDescriptivePidStopped(int winid,Nat16 pid){ return m_parent->intf ## _OnAudioDescriptivePidStopped(winid,pid);}\
virtual void OnScramblingStatusChanged(int winid,int MediaType,int status){ return m_parent->intf ## _OnScramblingStatusChanged(winid,MediaType,status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
