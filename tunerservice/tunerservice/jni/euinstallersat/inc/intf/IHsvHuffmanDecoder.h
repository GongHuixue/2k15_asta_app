#ifndef IHSVHUFFMANDECODER_H
#define IHSVHUFFMANDECODER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvHuffmanDecoder
{
public:
	virtual ~IHsvHuffmanDecoder(){}
	virtual void DtgHuffmanDecoderToString(Nat8 * src,Address * dstBuf,int size,int * dstSize)= 0;
};


#define IHsvHuffmanDecoderImpl(Comp,intf)    \
virtual void intf ## _DtgHuffmanDecoderToString(Nat8 * src,Address * dstBuf,int size,int * dstSize);\
class Comp ## _ ## intf : public IHsvHuffmanDecoder \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void DtgHuffmanDecoderToString(Nat8 * src,Address * dstBuf,int size,int * dstSize){ return m_parent->intf ## _DtgHuffmanDecoderToString(src,dstBuf,size,dstSize);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
