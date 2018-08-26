#ifndef IPRODAPINVMPROTECTEDACCESSEXEX_H
#define IPRODAPINVMPROTECTEDACCESSEXEX_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiNvmProtectedAccessExEx
{
public:
	virtual ~IProdApiNvmProtectedAccessExEx(){}
	#define IProdApiNvmProtectedAccessExEx_optTrue		((int)1 )
	#define IProdApiNvmProtectedAccessExEx_optFalse		((int)0 )
	#define IProdApiNvmProtectedAccessExEx_optInvalid		((int)-1 )
	virtual Bool GetBool(NvmId nvmid,int subid)= 0;
	virtual void SetBool(NvmId nvmid,Bool val,int subid)= 0;
	virtual Bool GetBoolIx(NvmId nvmid,int ix,int subid)= 0;
	virtual void SetBoolIx(NvmId nvmid,int ix,Bool val,int subid)= 0;
	virtual Bool GetBoolIxIx(NvmId nvmid,int ix1,int ix2,int subid)= 0;
	virtual void SetBoolIxIx(NvmId nvmid,int ix1,int ix2,Bool val,int subid)= 0;
	virtual char GetChar(NvmId nvmid,int subid)= 0;
	virtual void SetChar(NvmId nvmid,char val,int subid)= 0;
	virtual char GetCharIx(NvmId nvmid,int ix,int subid)= 0;
	virtual void SetCharIx(NvmId nvmid,int ix,char val,int subid)= 0;
	virtual char GetCharIxIx(NvmId nvmid,int ix1,int ix2,int subid)= 0;
	virtual void SetCharIxIx(NvmId nvmid,int ix1,int ix2,char val,int subid)= 0;
	virtual int GetInt(NvmId nvmid,int subid)= 0;
	virtual void SetInt(NvmId nvmid,int val,int subid)= 0;
	virtual int GetIntIx(NvmId nvmid,int ix,int subid)= 0;
	virtual void SetIntIx(NvmId nvmid,int ix,int val,int subid)= 0;
	virtual int GetIntIxIx(NvmId nvmid,int ix1,int ix2,int subid)= 0;
	virtual void SetIntIxIx(NvmId nvmid,int ix1,int ix2,int val,int subid)= 0;
	virtual Int32 GetInt32(NvmId nvmid,int subid)= 0;
	virtual void SetInt32(NvmId nvmid,Int32 val,int subid)= 0;
	virtual Int32 GetInt32Ix(NvmId nvmid,int ix,int subid)= 0;
	virtual void SetInt32Ix(NvmId nvmid,int ix,Int32 val,int subid)= 0;
	virtual Int32 GetInt32IxIx(NvmId nvmid,int ix1,int ix2,int subid)= 0;
	virtual void SetInt32IxIx(NvmId nvmid,int ix1,int ix2,Int32 val,int subid)= 0;
	virtual FResult LastError(void)= 0;
	virtual void GetNat16(NvmId nvmid,int subid,Nat16 * value)= 0;
	virtual void SetNat16(NvmId nvmid,int subid,Nat16 * value)= 0;
	virtual void InvalidateCache(void)= 0;
};


#define IProdApiNvmProtectedAccessExExImpl(Comp,intf)    \
virtual Bool intf ## _GetBool(NvmId nvmid,int subid);\
virtual void intf ## _SetBool(NvmId nvmid,Bool val,int subid);\
virtual Bool intf ## _GetBoolIx(NvmId nvmid,int ix,int subid);\
virtual void intf ## _SetBoolIx(NvmId nvmid,int ix,Bool val,int subid);\
virtual Bool intf ## _GetBoolIxIx(NvmId nvmid,int ix1,int ix2,int subid);\
virtual void intf ## _SetBoolIxIx(NvmId nvmid,int ix1,int ix2,Bool val,int subid);\
virtual char intf ## _GetChar(NvmId nvmid,int subid);\
virtual void intf ## _SetChar(NvmId nvmid,char val,int subid);\
virtual char intf ## _GetCharIx(NvmId nvmid,int ix,int subid);\
virtual void intf ## _SetCharIx(NvmId nvmid,int ix,char val,int subid);\
virtual char intf ## _GetCharIxIx(NvmId nvmid,int ix1,int ix2,int subid);\
virtual void intf ## _SetCharIxIx(NvmId nvmid,int ix1,int ix2,char val,int subid);\
virtual int intf ## _GetInt(NvmId nvmid,int subid);\
virtual void intf ## _SetInt(NvmId nvmid,int val,int subid);\
virtual int intf ## _GetIntIx(NvmId nvmid,int ix,int subid);\
virtual void intf ## _SetIntIx(NvmId nvmid,int ix,int val,int subid);\
virtual int intf ## _GetIntIxIx(NvmId nvmid,int ix1,int ix2,int subid);\
virtual void intf ## _SetIntIxIx(NvmId nvmid,int ix1,int ix2,int val,int subid);\
virtual Int32 intf ## _GetInt32(NvmId nvmid,int subid);\
virtual void intf ## _SetInt32(NvmId nvmid,Int32 val,int subid);\
virtual Int32 intf ## _GetInt32Ix(NvmId nvmid,int ix,int subid);\
virtual void intf ## _SetInt32Ix(NvmId nvmid,int ix,Int32 val,int subid);\
virtual Int32 intf ## _GetInt32IxIx(NvmId nvmid,int ix1,int ix2,int subid);\
virtual void intf ## _SetInt32IxIx(NvmId nvmid,int ix1,int ix2,Int32 val,int subid);\
virtual FResult intf ## _LastError(void);\
virtual void intf ## _GetNat16(NvmId nvmid,int subid,Nat16 * value);\
virtual void intf ## _SetNat16(NvmId nvmid,int subid,Nat16 * value);\
virtual void intf ## _InvalidateCache(void);\
class Comp ## _ ## intf : public IProdApiNvmProtectedAccessExEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool GetBool(NvmId nvmid,int subid){ return m_parent->intf ## _GetBool(nvmid,subid);}\
virtual void SetBool(NvmId nvmid,Bool val,int subid){ return m_parent->intf ## _SetBool(nvmid,val,subid);}\
virtual Bool GetBoolIx(NvmId nvmid,int ix,int subid){ return m_parent->intf ## _GetBoolIx(nvmid,ix,subid);}\
virtual void SetBoolIx(NvmId nvmid,int ix,Bool val,int subid){ return m_parent->intf ## _SetBoolIx(nvmid,ix,val,subid);}\
virtual Bool GetBoolIxIx(NvmId nvmid,int ix1,int ix2,int subid){ return m_parent->intf ## _GetBoolIxIx(nvmid,ix1,ix2,subid);}\
virtual void SetBoolIxIx(NvmId nvmid,int ix1,int ix2,Bool val,int subid){ return m_parent->intf ## _SetBoolIxIx(nvmid,ix1,ix2,val,subid);}\
virtual char GetChar(NvmId nvmid,int subid){ return m_parent->intf ## _GetChar(nvmid,subid);}\
virtual void SetChar(NvmId nvmid,char val,int subid){ return m_parent->intf ## _SetChar(nvmid,val,subid);}\
virtual char GetCharIx(NvmId nvmid,int ix,int subid){ return m_parent->intf ## _GetCharIx(nvmid,ix,subid);}\
virtual void SetCharIx(NvmId nvmid,int ix,char val,int subid){ return m_parent->intf ## _SetCharIx(nvmid,ix,val,subid);}\
virtual char GetCharIxIx(NvmId nvmid,int ix1,int ix2,int subid){ return m_parent->intf ## _GetCharIxIx(nvmid,ix1,ix2,subid);}\
virtual void SetCharIxIx(NvmId nvmid,int ix1,int ix2,char val,int subid){ return m_parent->intf ## _SetCharIxIx(nvmid,ix1,ix2,val,subid);}\
virtual int GetInt(NvmId nvmid,int subid){ return m_parent->intf ## _GetInt(nvmid,subid);}\
virtual void SetInt(NvmId nvmid,int val,int subid){ return m_parent->intf ## _SetInt(nvmid,val,subid);}\
virtual int GetIntIx(NvmId nvmid,int ix,int subid){ return m_parent->intf ## _GetIntIx(nvmid,ix,subid);}\
virtual void SetIntIx(NvmId nvmid,int ix,int val,int subid){ return m_parent->intf ## _SetIntIx(nvmid,ix,val,subid);}\
virtual int GetIntIxIx(NvmId nvmid,int ix1,int ix2,int subid){ return m_parent->intf ## _GetIntIxIx(nvmid,ix1,ix2,subid);}\
virtual void SetIntIxIx(NvmId nvmid,int ix1,int ix2,int val,int subid){ return m_parent->intf ## _SetIntIxIx(nvmid,ix1,ix2,val,subid);}\
virtual Int32 GetInt32(NvmId nvmid,int subid){ return m_parent->intf ## _GetInt32(nvmid,subid);}\
virtual void SetInt32(NvmId nvmid,Int32 val,int subid){ return m_parent->intf ## _SetInt32(nvmid,val,subid);}\
virtual Int32 GetInt32Ix(NvmId nvmid,int ix,int subid){ return m_parent->intf ## _GetInt32Ix(nvmid,ix,subid);}\
virtual void SetInt32Ix(NvmId nvmid,int ix,Int32 val,int subid){ return m_parent->intf ## _SetInt32Ix(nvmid,ix,val,subid);}\
virtual Int32 GetInt32IxIx(NvmId nvmid,int ix1,int ix2,int subid){ return m_parent->intf ## _GetInt32IxIx(nvmid,ix1,ix2,subid);}\
virtual void SetInt32IxIx(NvmId nvmid,int ix1,int ix2,Int32 val,int subid){ return m_parent->intf ## _SetInt32IxIx(nvmid,ix1,ix2,val,subid);}\
virtual FResult LastError(void){ return m_parent->intf ## _LastError();}\
virtual void GetNat16(NvmId nvmid,int subid,Nat16 * value){ return m_parent->intf ## _GetNat16(nvmid,subid,value);}\
virtual void SetNat16(NvmId nvmid,int subid,Nat16 * value){ return m_parent->intf ## _SetNat16(nvmid,subid,value);}\
virtual void InvalidateCache(void){ return m_parent->intf ## _InvalidateCache();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
