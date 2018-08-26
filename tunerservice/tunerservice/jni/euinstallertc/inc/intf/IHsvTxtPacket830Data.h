#ifndef IHSVTXTPACKET830DATA_H
#define IHSVTXTPACKET830DATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPacket830Data
{
public:
	virtual ~IHsvTxtPacket830Data(){}
	virtual int RequestDataFields(Nat16 field_bit_vector,Packet830CbFn cb_fn,Bool cb_on_every_update)= 0;
	virtual void UnRequestDataFields(int request_id)= 0;
	virtual Bool IsDataFieldsAvailable(Nat16 field_bit_vector)= 0;
	virtual Bool GetStatusMessage(String msg_string)= 0;
	virtual Bool GetInitialPage(PageNr * ptr_pn,Subcode * ptr_sc)= 0;
	virtual Bool GetUTCDate(Mjd * ptr_mjd)= 0;
	virtual Bool GetUTCTime(Time * ptr_time)= 0;
	virtual Bool GetTimeOffset(Int8 * ptr_time_offset)= 0;
	virtual Bool GetNetworkIdentificationCode(Nat16 * ptr_ni)= 0;
	virtual Bool GetPilCode(PilCode * ptr_pil_code)= 0;
	virtual Bool GetCountryNetworkIdentificationCode(Nat16 * ptr_cni)= 0;
	virtual Bool GetLabelInfo(LabelInfo * ptr_li)= 0;
	virtual Bool GetProgramControlInfo(ProgramControlInfo * ptr_pci)= 0;
	virtual Bool GetProgramType(Nat8 * ptr_ptype)= 0;
	#define IHsvTxtPacket830Data_StatusMessageField		((int)0x0001 )
	#define IHsvTxtPacket830Data_InitialPageField		((int)0x0002 )
	#define IHsvTxtPacket830Data_UTCDateField		((int)0x0004 )
	#define IHsvTxtPacket830Data_UTCTimeField		((int)0x0008 )
	#define IHsvTxtPacket830Data_TimeOffsetField		((int)0x0010 )
	#define IHsvTxtPacket830Data_NICodeField		((int)0x0020 )
	#define IHsvTxtPacket830Data_PilCodeField		((int)0x0040 )
	#define IHsvTxtPacket830Data_CNICodeField		((int)0x0080 )
	#define IHsvTxtPacket830Data_LabelInfoField		((int)0x0100 )
	#define IHsvTxtPacket830Data_ProgramControlInfoField		((int)0x0200 )
	#define IHsvTxtPacket830Data_ProgramTypeField		((int)0x0400 )
	#define IHsvTxtPacket830Data_InvalidRequestId		((int)-1 )
	#define IHsvTxtPacket830Data_MinutesPerTimeOffsetUnit		((int)30 )
};


#define IHsvTxtPacket830DataImpl(Comp,intf)    \
virtual int intf ## _RequestDataFields(Nat16 field_bit_vector,Packet830CbFn cb_fn,Bool cb_on_every_update);\
virtual void intf ## _UnRequestDataFields(int request_id);\
virtual Bool intf ## _IsDataFieldsAvailable(Nat16 field_bit_vector);\
virtual Bool intf ## _GetStatusMessage(String msg_string);\
virtual Bool intf ## _GetInitialPage(PageNr * ptr_pn,Subcode * ptr_sc);\
virtual Bool intf ## _GetUTCDate(Mjd * ptr_mjd);\
virtual Bool intf ## _GetUTCTime(Time * ptr_time);\
virtual Bool intf ## _GetTimeOffset(Int8 * ptr_time_offset);\
virtual Bool intf ## _GetNetworkIdentificationCode(Nat16 * ptr_ni);\
virtual Bool intf ## _GetPilCode(PilCode * ptr_pil_code);\
virtual Bool intf ## _GetCountryNetworkIdentificationCode(Nat16 * ptr_cni);\
virtual Bool intf ## _GetLabelInfo(LabelInfo * ptr_li);\
virtual Bool intf ## _GetProgramControlInfo(ProgramControlInfo * ptr_pci);\
virtual Bool intf ## _GetProgramType(Nat8 * ptr_ptype);\
class Comp ## _ ## intf : public IHsvTxtPacket830Data \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int RequestDataFields(Nat16 field_bit_vector,Packet830CbFn cb_fn,Bool cb_on_every_update){ return m_parent->intf ## _RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update);}\
virtual void UnRequestDataFields(int request_id){ return m_parent->intf ## _UnRequestDataFields(request_id);}\
virtual Bool IsDataFieldsAvailable(Nat16 field_bit_vector){ return m_parent->intf ## _IsDataFieldsAvailable(field_bit_vector);}\
virtual Bool GetStatusMessage(String msg_string){ return m_parent->intf ## _GetStatusMessage(msg_string);}\
virtual Bool GetInitialPage(PageNr * ptr_pn,Subcode * ptr_sc){ return m_parent->intf ## _GetInitialPage(ptr_pn,ptr_sc);}\
virtual Bool GetUTCDate(Mjd * ptr_mjd){ return m_parent->intf ## _GetUTCDate(ptr_mjd);}\
virtual Bool GetUTCTime(Time * ptr_time){ return m_parent->intf ## _GetUTCTime(ptr_time);}\
virtual Bool GetTimeOffset(Int8 * ptr_time_offset){ return m_parent->intf ## _GetTimeOffset(ptr_time_offset);}\
virtual Bool GetNetworkIdentificationCode(Nat16 * ptr_ni){ return m_parent->intf ## _GetNetworkIdentificationCode(ptr_ni);}\
virtual Bool GetPilCode(PilCode * ptr_pil_code){ return m_parent->intf ## _GetPilCode(ptr_pil_code);}\
virtual Bool GetCountryNetworkIdentificationCode(Nat16 * ptr_cni){ return m_parent->intf ## _GetCountryNetworkIdentificationCode(ptr_cni);}\
virtual Bool GetLabelInfo(LabelInfo * ptr_li){ return m_parent->intf ## _GetLabelInfo(ptr_li);}\
virtual Bool GetProgramControlInfo(ProgramControlInfo * ptr_pci){ return m_parent->intf ## _GetProgramControlInfo(ptr_pci);}\
virtual Bool GetProgramType(Nat8 * ptr_ptype){ return m_parent->intf ## _GetProgramType(ptr_ptype);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
