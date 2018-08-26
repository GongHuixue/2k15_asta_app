#ifndef IHSVADVANCEPROGRAMITERATOR_H
#define IHSVADVANCEPROGRAMITERATOR_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAdvanceProgramIterator
{
public:
	virtual ~IHsvAdvanceProgramIterator(){}
	virtual FResult GetNoOfChannels(int * size,Bool IsAnalog)= 0;
	virtual FResult GetFirstChannel(HsvChannel * channelno,Bool IsAnalog)= 0;
	virtual FResult GetLastChannel(HsvChannel * channelno,Bool IsAnalog)= 0;
	virtual FResult GetNextChannel(HsvChannel * channelno,Bool IsAnalog)= 0;
	virtual FResult GetPreviousChannel(HsvChannel * channelno,Bool IsAnalog)= 0;
};


#define IHsvAdvanceProgramIteratorImpl(Comp,intf)    \
virtual FResult intf ## _GetNoOfChannels(int * size,Bool IsAnalog);\
virtual FResult intf ## _GetFirstChannel(HsvChannel * channelno,Bool IsAnalog);\
virtual FResult intf ## _GetLastChannel(HsvChannel * channelno,Bool IsAnalog);\
virtual FResult intf ## _GetNextChannel(HsvChannel * channelno,Bool IsAnalog);\
virtual FResult intf ## _GetPreviousChannel(HsvChannel * channelno,Bool IsAnalog);\
class Comp ## _ ## intf : public IHsvAdvanceProgramIterator \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetNoOfChannels(int * size,Bool IsAnalog){ return m_parent->intf ## _GetNoOfChannels(size,IsAnalog);}\
virtual FResult GetFirstChannel(HsvChannel * channelno,Bool IsAnalog){ return m_parent->intf ## _GetFirstChannel(channelno,IsAnalog);}\
virtual FResult GetLastChannel(HsvChannel * channelno,Bool IsAnalog){ return m_parent->intf ## _GetLastChannel(channelno,IsAnalog);}\
virtual FResult GetNextChannel(HsvChannel * channelno,Bool IsAnalog){ return m_parent->intf ## _GetNextChannel(channelno,IsAnalog);}\
virtual FResult GetPreviousChannel(HsvChannel * channelno,Bool IsAnalog){ return m_parent->intf ## _GetPreviousChannel(channelno,IsAnalog);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
