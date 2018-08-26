#ifndef IHSVPROGRAMSELECTION2_H
#define IHSVPROGRAMSELECTION2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramSelection2
{
public:
	virtual ~IHsvProgramSelection2(){}
	#define IHsvProgramSelection2_DefaultSelection		((int)1 )
	#define IHsvProgramSelection2_SilentSelection		((int)2 )
	#define IHsvProgramSelection2_ControlledSelection		((int)4 )
	#define IHsvProgramSelection2_ReplacementSelection		((int)8 )
	#define IHsvProgramSelection2_BreakIn		((int)16 )
	#define IHsvProgramSelection2_DecoderBreakIn		((int)32 )
	#define IHsvProgramSelection2_MultifeedSelection		((int)64 )
	#define IHsvProgramSelection2_NDTSelection		((int)128 )
	#define IHsvProgramSelection2_PriorityHigh		((int)1 )
	#define IHsvProgramSelection2_PriorityMed		((int)2 )
	#define IHsvProgramSelection2_PriorityLow		((int)3 )
	#define IHsvProgramSelection2_Frequency		((int)1 )
	#define IHsvProgramSelection2_ModulationType		((int)2 )
	#define IHsvProgramSelection2_Polarization		((int)3 )
	#define IHsvProgramSelection2_SymbolRate		((int)4 )
	#define IHsvProgramSelection2_LnbNumber		((int)5 )
	#define IHsvProgramSelection2_AudioPid		((int)6 )
	#define IHsvProgramSelection2_VideoPid		((int)7 )
	#define IHsvProgramSelection2_PcrPid		((int)8 )
	#define IHsvProgramSelection2_ProgramNumber		((int)9 )
	#define IHsvProgramSelection2_ModulationStd		((int)10 )
	#define IHsvProgramSelection2_CodeRate		((int)11 )
	#define IHsvProgramSelection2_InvalidAttribute		((int)-1 )
	virtual FResult SelectProgram(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection,int Priority)= 0;
	virtual void GetCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual void GetActualCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual FResult IsSelectionAllowed(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest)= 0;
	virtual Bool IsSelectionInProgress(void)= 0;
	virtual void GetLastRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual void GetLastActualRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual FResult SetAttribute(int attribute,int value)= 0;
	virtual void GetAttribute(int attribute,int * value)= 0;
	virtual Bool IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection)= 0;
	virtual int GetActualTypeOfSelection(HsvDestination Dest)= 0;
	virtual Bool IsProgramSelectionRequired(HsvChannel channelno)= 0;
};


#define IHsvProgramSelection2Impl(Comp,intf)    \
virtual FResult intf ## _SelectProgram(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection,int Priority);\
virtual void intf ## _GetCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual void intf ## _GetActualCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual FResult intf ## _IsSelectionAllowed(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest);\
virtual Bool intf ## _IsSelectionInProgress(void);\
virtual void intf ## _GetLastRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual void intf ## _GetLastActualRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual FResult intf ## _SetAttribute(int attribute,int value);\
virtual void intf ## _GetAttribute(int attribute,int * value);\
virtual Bool intf ## _IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection);\
virtual int intf ## _GetActualTypeOfSelection(HsvDestination Dest);\
virtual Bool intf ## _IsProgramSelectionRequired(HsvChannel channelno);\
class Comp ## _ ## intf : public IHsvProgramSelection2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult SelectProgram(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection,int Priority){ return m_parent->intf ## _SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority);}\
virtual void GetCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo){ return m_parent->intf ## _GetCurrentProgram(Dest,Source,ChannelNo);}\
virtual void GetActualCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo){ return m_parent->intf ## _GetActualCurrentProgram(Dest,Source,ChannelNo);}\
virtual FResult IsSelectionAllowed(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest){ return m_parent->intf ## _IsSelectionAllowed(Source,ChannelNo,Dest);}\
virtual Bool IsSelectionInProgress(void){ return m_parent->intf ## _IsSelectionInProgress();}\
virtual void GetLastRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo){ return m_parent->intf ## _GetLastRequestedProgram(Dest,Source,ChannelNo);}\
virtual void GetLastActualRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo){ return m_parent->intf ## _GetLastActualRequestedProgram(Dest,Source,ChannelNo);}\
virtual FResult SetAttribute(int attribute,int value){ return m_parent->intf ## _SetAttribute(attribute,value);}\
virtual void GetAttribute(int attribute,int * value){ return m_parent->intf ## _GetAttribute(attribute,value);}\
virtual Bool IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection){ return m_parent->intf ## _IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection);}\
virtual int GetActualTypeOfSelection(HsvDestination Dest){ return m_parent->intf ## _GetActualTypeOfSelection(Dest);}\
virtual Bool IsProgramSelectionRequired(HsvChannel channelno){ return m_parent->intf ## _IsProgramSelectionRequired(channelno);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
