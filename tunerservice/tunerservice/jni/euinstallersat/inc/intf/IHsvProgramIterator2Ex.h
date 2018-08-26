#ifndef IHSVPROGRAMITERATOR2EX_H
#define IHSVPROGRAMITERATOR2EX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramIterator2Ex
{
public:
	virtual ~IHsvProgramIterator2Ex(){}
	#define IHsvProgramIterator2Ex_All		((int)0 )
	#define IHsvProgramIterator2Ex_Digital		((int)1 )
	#define IHsvProgramIterator2Ex_Analog		((int)2 )
	#define IHsvProgramIterator2Ex_Mux		((int)3 )
	#define IHsvProgramIterator2Ex_ChannelsInMux		((int)4 )
	virtual FResult GetNoOfChannels(int mode,int * noofchannels)= 0;
	virtual FResult GetFirstChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetLastChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetNextChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetPreviousChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetFirstMajorChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetLastMajorChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetNextMajorChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetPreviousMajorChannel(int mode,HsvChannel * channelno)= 0;
	virtual FResult GetFirstMinorChannel(HsvChannel * channelno)= 0;
	virtual FResult GetLastMinorChannel(HsvChannel * channelno)= 0;
	virtual FResult GetNextMinorChannel(HsvChannel * channelno)= 0;
	virtual FResult GetPreviousMinorChannel(HsvChannel * channelno)= 0;
	virtual FResult GetNoOfMinorChannelsOfMajor(HsvChannel channelno,int * noofminor)= 0;
	virtual FResult GetNextSource(HsvSource * source)= 0;
	virtual FResult GetPreviousSource(HsvSource * source)= 0;
	virtual FResult GetFirstSource(HsvSource * firstsource)= 0;
	virtual FResult GetLastSource(HsvSource * lastsource)= 0;
	virtual FResult GetNoOfSources(int * noofsources)= 0;
	virtual FResult GetFirstMultiplex(HsvMultiplex * mux)= 0;
	virtual FResult GetNextMultiplex(HsvMultiplex * mux)= 0;
	virtual FResult GetPreviousMultiplex(HsvMultiplex * mux)= 0;
	virtual FResult GetLastMultiplex(HsvMultiplex * mux)= 0;
};


#define IHsvProgramIterator2ExImpl(Comp,intf)    \
virtual FResult intf ## _GetNoOfChannels(int mode,int * noofchannels);\
virtual FResult intf ## _GetFirstChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetLastChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetNextChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetPreviousChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetFirstMajorChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetLastMajorChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetNextMajorChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetPreviousMajorChannel(int mode,HsvChannel * channelno);\
virtual FResult intf ## _GetFirstMinorChannel(HsvChannel * channelno);\
virtual FResult intf ## _GetLastMinorChannel(HsvChannel * channelno);\
virtual FResult intf ## _GetNextMinorChannel(HsvChannel * channelno);\
virtual FResult intf ## _GetPreviousMinorChannel(HsvChannel * channelno);\
virtual FResult intf ## _GetNoOfMinorChannelsOfMajor(HsvChannel channelno,int * noofminor);\
virtual FResult intf ## _GetNextSource(HsvSource * source);\
virtual FResult intf ## _GetPreviousSource(HsvSource * source);\
virtual FResult intf ## _GetFirstSource(HsvSource * firstsource);\
virtual FResult intf ## _GetLastSource(HsvSource * lastsource);\
virtual FResult intf ## _GetNoOfSources(int * noofsources);\
virtual FResult intf ## _GetFirstMultiplex(HsvMultiplex * mux);\
virtual FResult intf ## _GetNextMultiplex(HsvMultiplex * mux);\
virtual FResult intf ## _GetPreviousMultiplex(HsvMultiplex * mux);\
virtual FResult intf ## _GetLastMultiplex(HsvMultiplex * mux);\
class Comp ## _ ## intf : public IHsvProgramIterator2Ex \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetNoOfChannels(int mode,int * noofchannels){ return m_parent->intf ## _GetNoOfChannels(mode,noofchannels);}\
virtual FResult GetFirstChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetFirstChannel(mode,channelno);}\
virtual FResult GetLastChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetLastChannel(mode,channelno);}\
virtual FResult GetNextChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetNextChannel(mode,channelno);}\
virtual FResult GetPreviousChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetPreviousChannel(mode,channelno);}\
virtual FResult GetFirstMajorChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetFirstMajorChannel(mode,channelno);}\
virtual FResult GetLastMajorChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetLastMajorChannel(mode,channelno);}\
virtual FResult GetNextMajorChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetNextMajorChannel(mode,channelno);}\
virtual FResult GetPreviousMajorChannel(int mode,HsvChannel * channelno){ return m_parent->intf ## _GetPreviousMajorChannel(mode,channelno);}\
virtual FResult GetFirstMinorChannel(HsvChannel * channelno){ return m_parent->intf ## _GetFirstMinorChannel(channelno);}\
virtual FResult GetLastMinorChannel(HsvChannel * channelno){ return m_parent->intf ## _GetLastMinorChannel(channelno);}\
virtual FResult GetNextMinorChannel(HsvChannel * channelno){ return m_parent->intf ## _GetNextMinorChannel(channelno);}\
virtual FResult GetPreviousMinorChannel(HsvChannel * channelno){ return m_parent->intf ## _GetPreviousMinorChannel(channelno);}\
virtual FResult GetNoOfMinorChannelsOfMajor(HsvChannel channelno,int * noofminor){ return m_parent->intf ## _GetNoOfMinorChannelsOfMajor(channelno,noofminor);}\
virtual FResult GetNextSource(HsvSource * source){ return m_parent->intf ## _GetNextSource(source);}\
virtual FResult GetPreviousSource(HsvSource * source){ return m_parent->intf ## _GetPreviousSource(source);}\
virtual FResult GetFirstSource(HsvSource * firstsource){ return m_parent->intf ## _GetFirstSource(firstsource);}\
virtual FResult GetLastSource(HsvSource * lastsource){ return m_parent->intf ## _GetLastSource(lastsource);}\
virtual FResult GetNoOfSources(int * noofsources){ return m_parent->intf ## _GetNoOfSources(noofsources);}\
virtual FResult GetFirstMultiplex(HsvMultiplex * mux){ return m_parent->intf ## _GetFirstMultiplex(mux);}\
virtual FResult GetNextMultiplex(HsvMultiplex * mux){ return m_parent->intf ## _GetNextMultiplex(mux);}\
virtual FResult GetPreviousMultiplex(HsvMultiplex * mux){ return m_parent->intf ## _GetPreviousMultiplex(mux);}\
virtual FResult GetLastMultiplex(HsvMultiplex * mux){ return m_parent->intf ## _GetLastMultiplex(mux);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
