#ifndef IAPPAPISATPROGRAMITERATOR_H
#define IAPPAPISATPROGRAMITERATOR_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramIterator
{
public:
	virtual ~IAppApiSatProgramIterator(){}
	#define IAppApiSatProgramIterator_All		((int)0 )
	#define IAppApiSatProgramIterator_Digital		((int)1 )
	#define IAppApiSatProgramIterator_Analog		((int)2 )
	#define IAppApiSatProgramIterator_None		((Nat32)0x00000000 )
	#define IAppApiSatProgramIterator_Favorite		((Nat32)0x00000001 )
	#define IAppApiSatProgramIterator_Favorite1		((Nat32)0x00000002 )
	#define IAppApiSatProgramIterator_Favorite2		((Nat32)0x00000004 )
	#define IAppApiSatProgramIterator_Favorite3		((Nat32)0x00000008 )
	#define IAppApiSatProgramIterator_Locked		((Nat32)0x00000010 )
	#define IAppApiSatProgramIterator_UnLocked		((Nat32)0x00000020 )
	#define IAppApiSatProgramIterator_EpgChannel		((Nat32)0x00000040 )
	#define IAppApiSatProgramIterator_NonEpgChannel		((Nat32)0x00000080 )
	#define IAppApiSatProgramIterator_SystemHidden		((Nat32)0x00000100 )
	#define IAppApiSatProgramIterator_NonSystemHidden		((Nat32)0x00000200 )
	#define IAppApiSatProgramIterator_UserHidden		((Nat32)0x00000400 )
	#define IAppApiSatProgramIterator_NonUserHidden		((Nat32)0x00000800 )
	#define IAppApiSatProgramIterator_AudioOnly		((Nat32)0x00001000 )
	#define IAppApiSatProgramIterator_NonAudioOnly		((Nat32)0x00002000 )
	#define IAppApiSatProgramIterator_DvbT		((Nat32)0x00004000 )
	#define IAppApiSatProgramIterator_DvbC		((Nat32)0x00008000 )
	#define IAppApiSatProgramIterator_DvbTLite		((Nat32)0x00010000 )
	#define IAppApiSatProgramIterator_DvbCLite		((Nat32)0x00020000 )
	#define IAppApiSatProgramIterator_DvbS2		((Nat32)0x00040000 )
	virtual AppApiReturnCode GetNoOfChannels(int mode,Nat32 descriptor,int * noofchannels)= 0;
	virtual AppApiReturnCode GetFirstChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors)= 0;
	virtual AppApiReturnCode GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
};


#define IAppApiSatProgramIteratorImpl(Comp,intf)    \
virtual AppApiReturnCode intf ## _GetNoOfChannels(int mode,Nat32 descriptor,int * noofchannels);\
virtual AppApiReturnCode intf ## _GetFirstChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors);\
virtual AppApiReturnCode intf ## _GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
class Comp ## _ ## intf : public IAppApiSatProgramIterator \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual AppApiReturnCode GetNoOfChannels(int mode,Nat32 descriptor,int * noofchannels){ return m_parent->intf ## _GetNoOfChannels(mode,descriptor,noofchannels);}\
virtual AppApiReturnCode GetFirstChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetFirstChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetLastChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetLastChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetNextChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetNextChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetPreviousChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetPreviousChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetFirstMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetLastMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetNextMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetPreviousMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors){ return m_parent->intf ## _GetNoOfMinorChannelsOfMajor(descriptor,channelno,noofminors);}\
virtual AppApiReturnCode GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetFirstMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetLastMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetNextMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetPreviousMinorChannel(descriptor,channelno);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
