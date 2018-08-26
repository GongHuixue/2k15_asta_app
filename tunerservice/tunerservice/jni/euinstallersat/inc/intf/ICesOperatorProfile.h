#ifndef ICESOPERATORPROFILE_H
#define ICESOPERATORPROFILE_H
#include <intfparam.h>
#include <provreq.h>
class ICesOperatorProfile
{
public:
	virtual ~ICesOperatorProfile(){}
	virtual void RequestStatusInfo(void)= 0;
	virtual void RequestNit(void)= 0;
	virtual void SendOperatorSearchStart(Op_Search_Settings searchstart)= 0;
	virtual void SendOpExit(void)= 0;
	virtual void SendOpTuneStatus(Op_Tune_Status tuneStatus)= 0;
	virtual void SendOpAck(void)= 0;
	virtual void SendOpSearchCancel(void)= 0;
	virtual void CacheOperatorData(void)= 0;
	virtual Op_ProfileStatusInfo GetStoredOperatorData(void)= 0;
};


#define ICesOperatorProfileImpl(Comp,intf)    \
virtual void intf ## _RequestStatusInfo(void);\
virtual void intf ## _RequestNit(void);\
virtual void intf ## _SendOperatorSearchStart(Op_Search_Settings searchstart);\
virtual void intf ## _SendOpExit(void);\
virtual void intf ## _SendOpTuneStatus(Op_Tune_Status tuneStatus);\
virtual void intf ## _SendOpAck(void);\
virtual void intf ## _SendOpSearchCancel(void);\
virtual void intf ## _CacheOperatorData(void);\
virtual Op_ProfileStatusInfo intf ## _GetStoredOperatorData(void);\
class Comp ## _ ## intf : public ICesOperatorProfile \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void RequestStatusInfo(void){ return m_parent->intf ## _RequestStatusInfo();}\
virtual void RequestNit(void){ return m_parent->intf ## _RequestNit();}\
virtual void SendOperatorSearchStart(Op_Search_Settings searchstart){ return m_parent->intf ## _SendOperatorSearchStart(searchstart);}\
virtual void SendOpExit(void){ return m_parent->intf ## _SendOpExit();}\
virtual void SendOpTuneStatus(Op_Tune_Status tuneStatus){ return m_parent->intf ## _SendOpTuneStatus(tuneStatus);}\
virtual void SendOpAck(void){ return m_parent->intf ## _SendOpAck();}\
virtual void SendOpSearchCancel(void){ return m_parent->intf ## _SendOpSearchCancel();}\
virtual void CacheOperatorData(void){ return m_parent->intf ## _CacheOperatorData();}\
virtual Op_ProfileStatusInfo GetStoredOperatorData(void){ return m_parent->intf ## _GetStoredOperatorData();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
