#ifndef IHSVCHANNELLIBRETURNCODES_H
#define IHSVCHANNELLIBRETURNCODES_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChannelLibReturnCodes
{
public:
	virtual ~IHsvChannelLibReturnCodes(){}
	#define IHsvChannelLibReturnCodes_Ok		((AppApiReturnCode)0 )
	#define IHsvChannelLibReturnCodes_BadParameter		((AppApiReturnCode)1 )
	#define IHsvChannelLibReturnCodes_ChannelTableEmpty		((AppApiReturnCode)2 )
	#define IHsvChannelLibReturnCodes_ChannelTableExhausted		((AppApiReturnCode)3 )
	#define IHsvChannelLibReturnCodes_MinorNumbersExhausted		((AppApiReturnCode)4 )
	#define IHsvChannelLibReturnCodes_NotSupported		((AppApiReturnCode)5 )
	#define IHsvChannelLibReturnCodes_FileError		((AppApiReturnCode)6 )
	#define IHsvChannelLibReturnCodes_ChannelTableVersionError		((AppApiReturnCode)7 )
	#define IHsvChannelLibReturnCodes_ChannelTableCrcError		((AppApiReturnCode)8 )
	#define IHsvChannelLibReturnCodes_ChannelNotInstalled		((AppApiReturnCode)9 )
	#define IHsvChannelLibReturnCodes_NVMError		((AppApiReturnCode)10 )
};


#define IHsvChannelLibReturnCodesImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvChannelLibReturnCodes \
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
