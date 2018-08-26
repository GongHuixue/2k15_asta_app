#ifndef IAPPAPICHANNELLIBRETURNCODES_H
#define IAPPAPICHANNELLIBRETURNCODES_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiChannelLibReturnCodes
{
public:
	virtual ~IAppApiChannelLibReturnCodes(){}
	#define IAppApiChannelLibReturnCodes_Ok		((AppApiReturnCode)0 )
	#define IAppApiChannelLibReturnCodes_BadParameter		((AppApiReturnCode)1 )
	#define IAppApiChannelLibReturnCodes_ChannelTableEmpty		((AppApiReturnCode)2 )
	#define IAppApiChannelLibReturnCodes_ChannelTableExhausted		((AppApiReturnCode)3 )
	#define IAppApiChannelLibReturnCodes_MinorNumbersExhausted		((AppApiReturnCode)4 )
	#define IAppApiChannelLibReturnCodes_NotSupported		((AppApiReturnCode)5 )
};


#define IAppApiChannelLibReturnCodesImpl(Comp,intf)    \
class Comp ## _ ## intf : public IAppApiChannelLibReturnCodes \
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
