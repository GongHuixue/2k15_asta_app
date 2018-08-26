#ifndef IHSVTSVCHANNELNAME_H
#define IHSVTSVCHANNELNAME_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTsvChannelName
{
public:
	virtual ~IHsvTsvChannelName(){}
	virtual Bool GetCurrentChannelLabel(String label)= 0;
	virtual int ChannelLabelLength(void)= 0;
};


#define IHsvTsvChannelNameImpl(Comp,intf)    \
virtual Bool intf ## _GetCurrentChannelLabel(String label);\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvTsvChannelName \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_ChannelLabelLength; \
    Comp ## _ ## intf( Comp *parent):m_ChannelLabelLength(parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool GetCurrentChannelLabel(String label){ return m_parent->intf ## _GetCurrentChannelLabel(label);}\
virtual int ChannelLabelLength(void){ return m_ChannelLabelLength.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
