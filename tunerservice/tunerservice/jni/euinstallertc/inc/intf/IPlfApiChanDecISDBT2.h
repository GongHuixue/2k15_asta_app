#ifndef IPLFAPICHANDECISDBT2_H
#define IPLFAPICHANDECISDBT2_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecISDBT2
{
public:
	virtual ~IPlfApiChanDecISDBT2(){}
	#define IPlfApiChanDecISDBT2_LayerA		((int)1 )
	#define IPlfApiChanDecISDBT2_LayerB		((int)2 )
	#define IPlfApiChanDecISDBT2_LayerC		((int)4 )
	virtual FResult GetSupportedLayers(int winid,int * layers)= 0;
	virtual FResult SetLayer(int winid,int layer)= 0;
	virtual FResult GetLayer(int winid,int * layer)= 0;
};


#define IPlfApiChanDecISDBT2Impl(Comp,intf)    \
virtual FResult intf ## _GetSupportedLayers(int winid,int * layers);\
virtual FResult intf ## _SetLayer(int winid,int layer);\
virtual FResult intf ## _GetLayer(int winid,int * layer);\
class Comp ## _ ## intf : public IPlfApiChanDecISDBT2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetSupportedLayers(int winid,int * layers){ return m_parent->intf ## _GetSupportedLayers(winid,layers);}\
virtual FResult SetLayer(int winid,int layer){ return m_parent->intf ## _SetLayer(winid,layer);}\
virtual FResult GetLayer(int winid,int * layer){ return m_parent->intf ## _GetLayer(winid,layer);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
