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
	#define IHsvProgramSelection2_TvSystem		((int)3 )
	#define IHsvProgramSelection2_AudioPid		((int)4 )
	#define IHsvProgramSelection2_VideoPid		((int)5 )
	#define IHsvProgramSelection2_PcrPid		((int)6 )
	#define IHsvProgramSelection2_ProgramNumber		((int)7 )
	#define IHsvProgramSelection2_SymbolRate		((int)8 )
	#define IHsvProgramSelection2_DecoderType		((int)9 )
	#define IHsvProgramSelection2_InvalidAttribute		((int)-1 )
	virtual FResult SelectProgram(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection,int Priority)= 0;
	virtual void GetCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual void GetActualCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual FResult IsSelectionAllowed(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest)= 0;
	virtual Bool IsSelectionInProgress(void)= 0;
	virtual void GetLastRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual void GetLastActualRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo)= 0;
	virtual Bool IsAssociationAllowed(HsvSource Source,HsvSource AssociationSource)= 0;
	virtual void SetAssociation(HsvSource Source,HsvSource AssociationSource)= 0;
	virtual HsvSource GetAssociation(HsvSource Source)= 0;
	virtual void EnableAllExtensionBreakIn(Bool enable)= 0;
	virtual Bool IsAllExtensionBreakInEnabled(void)= 0;
	virtual void EnableExtensionBreakIn(HsvSource ext,Bool enable)= 0;
	virtual Bool IsExtensionBreakInEnabled(HsvSource ext)= 0;
	virtual void EnableBreakInHistory(Bool enable)= 0;
	virtual Bool IsBreakInHistoryEnabled(void)= 0;
	virtual void ClearBreakInStack(void)= 0;
	virtual Bool IsBreakInStackEmpty(void)= 0;
	virtual Bool GetBreakInSourceByIndex(int index,HsvSource * BreakInSource)= 0;
	virtual int GetNumberOfBreakInSources(void)= 0;
	virtual Bool GetRuningStatusForService(void)= 0;
	virtual FResult IsDualWindowCombinationAllowed(HsvSource MainSource,HsvChannel MainChannel,HsvSource AuxSource,HsvChannel AuxChannel)= 0;
	virtual FResult SetAttribute(int attribute,int value)= 0;
	virtual void GetAttribute(int attribute,int * value)= 0;
	virtual Bool IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection)= 0;
	virtual int GetActualTypeOfSelection(HsvDestination Dest)= 0;
	virtual Bool IsProgramSelectionRequired(HsvChannel Channel)= 0;
	virtual Bool SetVirginBitOn(void)= 0;
};


#define IHsvProgramSelection2Impl(Comp,intf)    \
virtual FResult intf ## _SelectProgram(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection,int Priority);\
virtual void intf ## _GetCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual void intf ## _GetActualCurrentProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual FResult intf ## _IsSelectionAllowed(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest);\
virtual Bool intf ## _IsSelectionInProgress(void);\
virtual void intf ## _GetLastRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual void intf ## _GetLastActualRequestedProgram(HsvDestination Dest,HsvSource * Source,HsvChannel * ChannelNo);\
virtual Bool intf ## _IsAssociationAllowed(HsvSource Source,HsvSource AssociationSource);\
virtual void intf ## _SetAssociation(HsvSource Source,HsvSource AssociationSource);\
virtual HsvSource intf ## _GetAssociation(HsvSource Source);\
virtual void intf ## _EnableAllExtensionBreakIn(Bool enable);\
virtual Bool intf ## _IsAllExtensionBreakInEnabled(void);\
virtual void intf ## _EnableExtensionBreakIn(HsvSource ext,Bool enable);\
virtual Bool intf ## _IsExtensionBreakInEnabled(HsvSource ext);\
virtual void intf ## _EnableBreakInHistory(Bool enable);\
virtual Bool intf ## _IsBreakInHistoryEnabled(void);\
virtual void intf ## _ClearBreakInStack(void);\
virtual Bool intf ## _IsBreakInStackEmpty(void);\
virtual Bool intf ## _GetBreakInSourceByIndex(int index,HsvSource * BreakInSource);\
virtual int intf ## _GetNumberOfBreakInSources(void);\
virtual Bool intf ## _GetRuningStatusForService(void);\
virtual FResult intf ## _IsDualWindowCombinationAllowed(HsvSource MainSource,HsvChannel MainChannel,HsvSource AuxSource,HsvChannel AuxChannel);\
virtual FResult intf ## _SetAttribute(int attribute,int value);\
virtual void intf ## _GetAttribute(int attribute,int * value);\
virtual Bool intf ## _IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection);\
virtual int intf ## _GetActualTypeOfSelection(HsvDestination Dest);\
virtual Bool intf ## _IsProgramSelectionRequired(HsvChannel Channel);\
virtual Bool intf ## _SetVirginBitOn(void);\
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
virtual Bool IsAssociationAllowed(HsvSource Source,HsvSource AssociationSource){ return m_parent->intf ## _IsAssociationAllowed(Source,AssociationSource);}\
virtual void SetAssociation(HsvSource Source,HsvSource AssociationSource){ return m_parent->intf ## _SetAssociation(Source,AssociationSource);}\
virtual HsvSource GetAssociation(HsvSource Source){ return m_parent->intf ## _GetAssociation(Source);}\
virtual void EnableAllExtensionBreakIn(Bool enable){ return m_parent->intf ## _EnableAllExtensionBreakIn(enable);}\
virtual Bool IsAllExtensionBreakInEnabled(void){ return m_parent->intf ## _IsAllExtensionBreakInEnabled();}\
virtual void EnableExtensionBreakIn(HsvSource ext,Bool enable){ return m_parent->intf ## _EnableExtensionBreakIn(ext,enable);}\
virtual Bool IsExtensionBreakInEnabled(HsvSource ext){ return m_parent->intf ## _IsExtensionBreakInEnabled(ext);}\
virtual void EnableBreakInHistory(Bool enable){ return m_parent->intf ## _EnableBreakInHistory(enable);}\
virtual Bool IsBreakInHistoryEnabled(void){ return m_parent->intf ## _IsBreakInHistoryEnabled();}\
virtual void ClearBreakInStack(void){ return m_parent->intf ## _ClearBreakInStack();}\
virtual Bool IsBreakInStackEmpty(void){ return m_parent->intf ## _IsBreakInStackEmpty();}\
virtual Bool GetBreakInSourceByIndex(int index,HsvSource * BreakInSource){ return m_parent->intf ## _GetBreakInSourceByIndex(index,BreakInSource);}\
virtual int GetNumberOfBreakInSources(void){ return m_parent->intf ## _GetNumberOfBreakInSources();}\
virtual Bool GetRuningStatusForService(void){ return m_parent->intf ## _GetRuningStatusForService();}\
virtual FResult IsDualWindowCombinationAllowed(HsvSource MainSource,HsvChannel MainChannel,HsvSource AuxSource,HsvChannel AuxChannel){ return m_parent->intf ## _IsDualWindowCombinationAllowed(MainSource,MainChannel,AuxSource,AuxChannel);}\
virtual FResult SetAttribute(int attribute,int value){ return m_parent->intf ## _SetAttribute(attribute,value);}\
virtual void GetAttribute(int attribute,int * value){ return m_parent->intf ## _GetAttribute(attribute,value);}\
virtual Bool IsTuningRequired(HsvSource Source,HsvChannel ChannelNo,HsvDestination Dest,int TypeOfSelection){ return m_parent->intf ## _IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection);}\
virtual int GetActualTypeOfSelection(HsvDestination Dest){ return m_parent->intf ## _GetActualTypeOfSelection(Dest);}\
virtual Bool IsProgramSelectionRequired(HsvChannel Channel){ return m_parent->intf ## _IsProgramSelectionRequired(Channel);}\
virtual Bool SetVirginBitOn(void){ return m_parent->intf ## _SetVirginBitOn();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
