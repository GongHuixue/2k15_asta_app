#ifndef IHSVMINIPRESCAN_H
#define IHSVMINIPRESCAN_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMiniPrescan
{
public:
	virtual ~IHsvMiniPrescan(){}
	virtual FResult StartMiniPrescan(int LnbNumber,int Param)= 0;
	virtual void StopMiniPrescan(void)= 0;
	virtual FResult GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID)= 0;
};


#define IHsvMiniPrescanImpl(Comp,intf)    \
virtual FResult intf ## _StartMiniPrescan(int LnbNumber,int Param);\
virtual void intf ## _StopMiniPrescan(void);\
virtual FResult intf ## _GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID);\
class Comp ## _ ## intf : public IHsvMiniPrescan \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult StartMiniPrescan(int LnbNumber,int Param){ return m_parent->intf ## _StartMiniPrescan(LnbNumber,Param);}\
virtual void StopMiniPrescan(void){ return m_parent->intf ## _StopMiniPrescan();}\
virtual FResult GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID){ return m_parent->intf ## _GetSITableIds(NetworkID,BouquetID);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
