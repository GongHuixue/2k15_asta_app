#ifndef IHSVTXTVPSDATA_H
#define IHSVTXTVPSDATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtVpsData
{
public:
	virtual ~IHsvTxtVpsData(){}
	virtual int RequestDataFields(Nat8 field_bit_vector,VpsCbFn cb_fn,Bool cb_on_every_update)= 0;
	virtual void UnRequestDataFields(int request_id)= 0;
	virtual Bool IsDataFieldsAvailable(Nat8 field_bit_vector)= 0;
	virtual Bool GetPilCode(PilCode * ptr_pil_code)= 0;
	virtual Bool GetCountryNetworkIdentificationCode(Nat16 * ptr_cni)= 0;
	virtual Bool GetProgramType(Nat8 * ptr_ptype)= 0;
	virtual Bool GetProgramControlStatus(Nat8 * ptr_ps)= 0;
	virtual Bool GetDistinctionBits(Nat8 * ptr_dist_bits)= 0;
	#define IHsvTxtVpsData_PilCodeField		((int)0x0001 )
	#define IHsvTxtVpsData_CNICodeField		((int)0x0002 )
	#define IHsvTxtVpsData_ProgramTypeField		((int)0x0004 )
	#define IHsvTxtVpsData_ProgramControlStatusField		((int)0x0008 )
	#define IHsvTxtVpsData_DistinctionBitsField		((int)0x0010 )
	#define IHsvTxtVpsData_InvalidRequestId		((int)-1 )
};


#define IHsvTxtVpsDataImpl(Comp,intf)    \
virtual int intf ## _RequestDataFields(Nat8 field_bit_vector,VpsCbFn cb_fn,Bool cb_on_every_update);\
virtual void intf ## _UnRequestDataFields(int request_id);\
virtual Bool intf ## _IsDataFieldsAvailable(Nat8 field_bit_vector);\
virtual Bool intf ## _GetPilCode(PilCode * ptr_pil_code);\
virtual Bool intf ## _GetCountryNetworkIdentificationCode(Nat16 * ptr_cni);\
virtual Bool intf ## _GetProgramType(Nat8 * ptr_ptype);\
virtual Bool intf ## _GetProgramControlStatus(Nat8 * ptr_ps);\
virtual Bool intf ## _GetDistinctionBits(Nat8 * ptr_dist_bits);\
class Comp ## _ ## intf : public IHsvTxtVpsData \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int RequestDataFields(Nat8 field_bit_vector,VpsCbFn cb_fn,Bool cb_on_every_update){ return m_parent->intf ## _RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update);}\
virtual void UnRequestDataFields(int request_id){ return m_parent->intf ## _UnRequestDataFields(request_id);}\
virtual Bool IsDataFieldsAvailable(Nat8 field_bit_vector){ return m_parent->intf ## _IsDataFieldsAvailable(field_bit_vector);}\
virtual Bool GetPilCode(PilCode * ptr_pil_code){ return m_parent->intf ## _GetPilCode(ptr_pil_code);}\
virtual Bool GetCountryNetworkIdentificationCode(Nat16 * ptr_cni){ return m_parent->intf ## _GetCountryNetworkIdentificationCode(ptr_cni);}\
virtual Bool GetProgramType(Nat8 * ptr_ptype){ return m_parent->intf ## _GetProgramType(ptr_ptype);}\
virtual Bool GetProgramControlStatus(Nat8 * ptr_ps){ return m_parent->intf ## _GetProgramControlStatus(ptr_ps);}\
virtual Bool GetDistinctionBits(Nat8 * ptr_dist_bits){ return m_parent->intf ## _GetDistinctionBits(ptr_dist_bits);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
