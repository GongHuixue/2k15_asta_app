#ifndef IAPPAPISATCHANNELLIBRETURNCODES_H
#define IAPPAPISATCHANNELLIBRETURNCODES_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatChannelLibReturnCodes
{
public:
	virtual ~IAppApiSatChannelLibReturnCodes(){}
	#define IAppApiSatChannelLibReturnCodes_Ok		((AppApiReturnCode)0 )
	#define IAppApiSatChannelLibReturnCodes_BadParameter		((AppApiReturnCode)1 )
	#define IAppApiSatChannelLibReturnCodes_ChannelTableEmpty		((AppApiReturnCode)2 )
	#define IAppApiSatChannelLibReturnCodes_ChannelTableExhausted		((AppApiReturnCode)3 )
	#define IAppApiSatChannelLibReturnCodes_MinorNumbersExhausted		((AppApiReturnCode)4 )
	#define IAppApiSatChannelLibReturnCodes_NotSupported		((AppApiReturnCode)5 )
};


#define IAppApiSatChannelLibReturnCodesImpl(Comp,intf)    \
class Comp ## _ ## intf : public IAppApiSatChannelLibReturnCodes \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
