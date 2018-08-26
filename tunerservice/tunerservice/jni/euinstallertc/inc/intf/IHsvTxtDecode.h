#ifndef IHSVTXTDECODE_H
#define IHSVTXTDECODE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtDecode
{
public:
	virtual ~IHsvTxtDecode(){}
	virtual void DecodeOddParity(Nat8 * src,Nat8 * dst,Nat8 * old,int size)= 0;
};


#define IHsvTxtDecodeImpl(Comp,intf)    \
virtual void intf ## _DecodeOddParity(Nat8 * src,Nat8 * dst,Nat8 * old,int size);\
class Comp ## _ ## intf : public IHsvTxtDecode \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void DecodeOddParity(Nat8 * src,Nat8 * dst,Nat8 * old,int size){ return m_parent->intf ## _DecodeOddParity(src,dst,old,size);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
