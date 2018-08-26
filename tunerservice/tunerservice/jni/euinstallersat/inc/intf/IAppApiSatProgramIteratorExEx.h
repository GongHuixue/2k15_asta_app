#ifndef IAPPAPISATPROGRAMITERATOREXEX_H
#define IAPPAPISATPROGRAMITERATOREXEX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramIteratorExEx
{
public:
	virtual ~IAppApiSatProgramIteratorExEx(){}
	#define IAppApiSatProgramIteratorExEx_All		((int)0 )
	#define IAppApiSatProgramIteratorExEx_Digital		((int)1 )
	#define IAppApiSatProgramIteratorExEx_Analog		((int)2 )
	#define IAppApiSatProgramIteratorExEx_None		((Nat32)0x00000000 )
	#define IAppApiSatProgramIteratorExEx_Favorite		((Nat32)0x00000001 )
	#define IAppApiSatProgramIteratorExEx_Favorite1		((Nat32)0x00000002 )
	#define IAppApiSatProgramIteratorExEx_Favorite2		((Nat32)0x00000004 )
	#define IAppApiSatProgramIteratorExEx_Favorite3		((Nat32)0x00000008 )
	#define IAppApiSatProgramIteratorExEx_Locked		((Nat32)0x00000010 )
	#define IAppApiSatProgramIteratorExEx_UnLocked		((Nat32)0x00000020 )
	#define IAppApiSatProgramIteratorExEx_EpgChannel		((Nat32)0x00000040 )
	#define IAppApiSatProgramIteratorExEx_NonEpgChannel		((Nat32)0x00000080 )
	#define IAppApiSatProgramIteratorExEx_SystemHidden		((Nat32)0x00000100 )
	#define IAppApiSatProgramIteratorExEx_NonSystemHidden		((Nat32)0x00000200 )
	#define IAppApiSatProgramIteratorExEx_UserHidden		((Nat32)0x00000400 )
	#define IAppApiSatProgramIteratorExEx_NonUserHidden		((Nat32)0x00000800 )
	#define IAppApiSatProgramIteratorExEx_AudioOnly		((Nat32)0x00001000 )
	#define IAppApiSatProgramIteratorExEx_NonAudioOnly		((Nat32)0x00002000 )
	#define IAppApiSatProgramIteratorExEx_DvbT		((Nat32)0x00004000 )
	#define IAppApiSatProgramIteratorExEx_DvbC		((Nat32)0x00008000 )
	#define IAppApiSatProgramIteratorExEx_DvbTLite		((Nat32)0x00010000 )
	#define IAppApiSatProgramIteratorExEx_DvbCLite		((Nat32)0x00020000 )
	#define IAppApiSatProgramIteratorExEx_DvbS2		((Nat32)0x00040000 )
	#define IAppApiSatProgramIteratorExEx_DataOnly		((Nat32)0x00080000 )
	#define IAppApiSatProgramIteratorExEx_NonDataOnly		((Nat32)0x00100000 )
	virtual AppApiReturnCode GetNoOfChannels(int mode,Nat32 descriptor,int * noofchannels)= 0;
	virtual AppApiReturnCode GetFirstChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNoOfMajorChannels(int mode,Nat32 descriptor,int * noofchannels)= 0;
	virtual AppApiReturnCode GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors)= 0;
	virtual AppApiReturnCode GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno)= 0;
	virtual AppApiReturnCode GetNoOfMultiplexes(int * noofmuxes)= 0;
	virtual AppApiReturnCode GetFirstMultiplex(AppApiMultiplex * mux)= 0;
	virtual AppApiReturnCode GetNextMultiplex(AppApiMultiplex * mux)= 0;
	virtual AppApiReturnCode GetPreviousMultiplex(AppApiMultiplex * mux)= 0;
	virtual AppApiReturnCode GetLastMultiplex(AppApiMultiplex * mux)= 0;
};


#define IAppApiSatProgramIteratorExExImpl(Comp,intf)    \
virtual AppApiReturnCode intf ## _GetNoOfChannels(int mode,Nat32 descriptor,int * noofchannels);\
virtual AppApiReturnCode intf ## _GetFirstChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNoOfMajorChannels(int mode,Nat32 descriptor,int * noofchannels);\
virtual AppApiReturnCode intf ## _GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors);\
virtual AppApiReturnCode intf ## _GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno);\
virtual AppApiReturnCode intf ## _GetNoOfMultiplexes(int * noofmuxes);\
virtual AppApiReturnCode intf ## _GetFirstMultiplex(AppApiMultiplex * mux);\
virtual AppApiReturnCode intf ## _GetNextMultiplex(AppApiMultiplex * mux);\
virtual AppApiReturnCode intf ## _GetPreviousMultiplex(AppApiMultiplex * mux);\
virtual AppApiReturnCode intf ## _GetLastMultiplex(AppApiMultiplex * mux);\
class Comp ## _ ## intf : public IAppApiSatProgramIteratorExEx \
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
virtual AppApiReturnCode GetNoOfMajorChannels(int mode,Nat32 descriptor,int * noofchannels){ return m_parent->intf ## _GetNoOfMajorChannels(mode,descriptor,noofchannels);}\
virtual AppApiReturnCode GetFirstMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetFirstMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetLastMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetLastMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetNextMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetNextMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetPreviousMajorChannel(int mode,Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetPreviousMajorChannel(mode,descriptor,channelno);}\
virtual AppApiReturnCode GetNoOfMinorChannelsOfMajor(Nat32 descriptor,AppApiChannel channelno,int * noofminors){ return m_parent->intf ## _GetNoOfMinorChannelsOfMajor(descriptor,channelno,noofminors);}\
virtual AppApiReturnCode GetFirstMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetFirstMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetLastMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetLastMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetNextMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetNextMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetPreviousMinorChannel(Nat32 descriptor,AppApiChannel * channelno){ return m_parent->intf ## _GetPreviousMinorChannel(descriptor,channelno);}\
virtual AppApiReturnCode GetNoOfMultiplexes(int * noofmuxes){ return m_parent->intf ## _GetNoOfMultiplexes(noofmuxes);}\
virtual AppApiReturnCode GetFirstMultiplex(AppApiMultiplex * mux){ return m_parent->intf ## _GetFirstMultiplex(mux);}\
virtual AppApiReturnCode GetNextMultiplex(AppApiMultiplex * mux){ return m_parent->intf ## _GetNextMultiplex(mux);}\
virtual AppApiReturnCode GetPreviousMultiplex(AppApiMultiplex * mux){ return m_parent->intf ## _GetPreviousMultiplex(mux);}\
virtual AppApiReturnCode GetLastMultiplex(AppApiMultiplex * mux){ return m_parent->intf ## _GetLastMultiplex(mux);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
