#ifndef IHSVTXTPAGECONVERT_H
#define IHSVTXTPAGECONVERT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPageConvert
{
public:
	virtual ~IHsvTxtPageConvert(){}
	virtual void ConfInit(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfWindowId(TxtPageConfigStruct * pcs,TWindowId window_id)= 0;
	virtual TWindowId GetConfWindowId(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfPageHandle(TxtPageConfigStruct * pcs,TxtPageHandle hnd)= 0;
	virtual TxtPageHandle GetConfPageHandle(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfPresentation(TxtPageConfigStruct * pcs,int presentation)= 0;
	virtual int GetConfPresentation(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfSupRow24(TxtPageConfigStruct * pcs,Bool sup_row_24)= 0;
	virtual Bool GetConfSupRow24(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfSupHeader(TxtPageConfigStruct * pcs,Bool sup_header)= 0;
	virtual Bool GetConfSupHeader(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfSupPicture(TxtPageConfigStruct * pcs,Bool sup_picture)= 0;
	virtual Bool GetConfSupPicture(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfSupSidePanels(TxtPageConfigStruct * pcs,Bool sup_side_pan)= 0;
	virtual Bool GetConfSupSidePanels(TxtPageConfigStruct * pcs)= 0;
	virtual void SetConfSupRowAttribs(TxtPageConfigStruct * pcs,Bool sup_row_attribs)= 0;
	virtual Bool GetConfSupRowAttribs(TxtPageConfigStruct * pcs)= 0;
	virtual void ConfigureTextPageConversion(TxtPageConfigStruct * pcs)= 0;
	virtual void StartTextPageConversion(Bool x)= 0;
	virtual void TerminateTextPageConversion(void)= 0;
	virtual void SetRevealState(Bool rev_state)= 0;
	virtual Bool GetRevealState(void)= 0;
	virtual Bool GetPageWidthOffset(TxtPageHandle hnd,int * width,int * offset)= 0;
	virtual Bool GetPagePon(void)= 0;
	virtual void SetRollingHeader(int mode,int magazine)= 0;
	virtual void SetRollingTime(int mode)= 0;
	virtual void SetHeaderInitialPosition(Nat8 topleftrow,Nat8 topleftcol)= 0;
	virtual void HoldConversion(Bool convhold_state)= 0;
	virtual void ResetUpdateCounter(void)= 0;
	virtual void IncrementUpdateCounter(void)= 0;
	#define IHsvTxtPageConvert_LEVEL_10		((int)0 )
	#define IHsvTxtPageConvert_LEVEL_15		((int)1 )
	#define IHsvTxtPageConvert_LEVEL_25		((int)2 )
	#define IHsvTxtPageConvert_TRH_HOLD		((int)0 )
	#define IHsvTxtPageConvert_TRH_ROL		((int)1 )
	#define IHsvTxtPageConvert_TRT_HOLD		((int)0 )
	#define IHsvTxtPageConvert_TRT_ROL		((int)1 )
};


#define IHsvTxtPageConvertImpl(Comp,intf)    \
virtual void intf ## _ConfInit(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfWindowId(TxtPageConfigStruct * pcs,TWindowId window_id);\
virtual TWindowId intf ## _GetConfWindowId(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfPageHandle(TxtPageConfigStruct * pcs,TxtPageHandle hnd);\
virtual TxtPageHandle intf ## _GetConfPageHandle(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfPresentation(TxtPageConfigStruct * pcs,int presentation);\
virtual int intf ## _GetConfPresentation(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfSupRow24(TxtPageConfigStruct * pcs,Bool sup_row_24);\
virtual Bool intf ## _GetConfSupRow24(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfSupHeader(TxtPageConfigStruct * pcs,Bool sup_header);\
virtual Bool intf ## _GetConfSupHeader(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfSupPicture(TxtPageConfigStruct * pcs,Bool sup_picture);\
virtual Bool intf ## _GetConfSupPicture(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfSupSidePanels(TxtPageConfigStruct * pcs,Bool sup_side_pan);\
virtual Bool intf ## _GetConfSupSidePanels(TxtPageConfigStruct * pcs);\
virtual void intf ## _SetConfSupRowAttribs(TxtPageConfigStruct * pcs,Bool sup_row_attribs);\
virtual Bool intf ## _GetConfSupRowAttribs(TxtPageConfigStruct * pcs);\
virtual void intf ## _ConfigureTextPageConversion(TxtPageConfigStruct * pcs);\
virtual void intf ## _StartTextPageConversion(Bool x);\
virtual void intf ## _TerminateTextPageConversion(void);\
virtual void intf ## _SetRevealState(Bool rev_state);\
virtual Bool intf ## _GetRevealState(void);\
virtual Bool intf ## _GetPageWidthOffset(TxtPageHandle hnd,int * width,int * offset);\
virtual Bool intf ## _GetPagePon(void);\
virtual void intf ## _SetRollingHeader(int mode,int magazine);\
virtual void intf ## _SetRollingTime(int mode);\
virtual void intf ## _SetHeaderInitialPosition(Nat8 topleftrow,Nat8 topleftcol);\
virtual void intf ## _HoldConversion(Bool convhold_state);\
virtual void intf ## _ResetUpdateCounter(void);\
virtual void intf ## _IncrementUpdateCounter(void);\
class Comp ## _ ## intf : public IHsvTxtPageConvert \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void ConfInit(TxtPageConfigStruct * pcs){ return m_parent->intf ## _ConfInit(pcs);}\
virtual void SetConfWindowId(TxtPageConfigStruct * pcs,TWindowId window_id){ return m_parent->intf ## _SetConfWindowId(pcs,window_id);}\
virtual TWindowId GetConfWindowId(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfWindowId(pcs);}\
virtual void SetConfPageHandle(TxtPageConfigStruct * pcs,TxtPageHandle hnd){ return m_parent->intf ## _SetConfPageHandle(pcs,hnd);}\
virtual TxtPageHandle GetConfPageHandle(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfPageHandle(pcs);}\
virtual void SetConfPresentation(TxtPageConfigStruct * pcs,int presentation){ return m_parent->intf ## _SetConfPresentation(pcs,presentation);}\
virtual int GetConfPresentation(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfPresentation(pcs);}\
virtual void SetConfSupRow24(TxtPageConfigStruct * pcs,Bool sup_row_24){ return m_parent->intf ## _SetConfSupRow24(pcs,sup_row_24);}\
virtual Bool GetConfSupRow24(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfSupRow24(pcs);}\
virtual void SetConfSupHeader(TxtPageConfigStruct * pcs,Bool sup_header){ return m_parent->intf ## _SetConfSupHeader(pcs,sup_header);}\
virtual Bool GetConfSupHeader(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfSupHeader(pcs);}\
virtual void SetConfSupPicture(TxtPageConfigStruct * pcs,Bool sup_picture){ return m_parent->intf ## _SetConfSupPicture(pcs,sup_picture);}\
virtual Bool GetConfSupPicture(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfSupPicture(pcs);}\
virtual void SetConfSupSidePanels(TxtPageConfigStruct * pcs,Bool sup_side_pan){ return m_parent->intf ## _SetConfSupSidePanels(pcs,sup_side_pan);}\
virtual Bool GetConfSupSidePanels(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfSupSidePanels(pcs);}\
virtual void SetConfSupRowAttribs(TxtPageConfigStruct * pcs,Bool sup_row_attribs){ return m_parent->intf ## _SetConfSupRowAttribs(pcs,sup_row_attribs);}\
virtual Bool GetConfSupRowAttribs(TxtPageConfigStruct * pcs){ return m_parent->intf ## _GetConfSupRowAttribs(pcs);}\
virtual void ConfigureTextPageConversion(TxtPageConfigStruct * pcs){ return m_parent->intf ## _ConfigureTextPageConversion(pcs);}\
virtual void StartTextPageConversion(Bool x){ return m_parent->intf ## _StartTextPageConversion(x);}\
virtual void TerminateTextPageConversion(void){ return m_parent->intf ## _TerminateTextPageConversion();}\
virtual void SetRevealState(Bool rev_state){ return m_parent->intf ## _SetRevealState(rev_state);}\
virtual Bool GetRevealState(void){ return m_parent->intf ## _GetRevealState();}\
virtual Bool GetPageWidthOffset(TxtPageHandle hnd,int * width,int * offset){ return m_parent->intf ## _GetPageWidthOffset(hnd,width,offset);}\
virtual Bool GetPagePon(void){ return m_parent->intf ## _GetPagePon();}\
virtual void SetRollingHeader(int mode,int magazine){ return m_parent->intf ## _SetRollingHeader(mode,magazine);}\
virtual void SetRollingTime(int mode){ return m_parent->intf ## _SetRollingTime(mode);}\
virtual void SetHeaderInitialPosition(Nat8 topleftrow,Nat8 topleftcol){ return m_parent->intf ## _SetHeaderInitialPosition(topleftrow,topleftcol);}\
virtual void HoldConversion(Bool convhold_state){ return m_parent->intf ## _HoldConversion(convhold_state);}\
virtual void ResetUpdateCounter(void){ return m_parent->intf ## _ResetUpdateCounter();}\
virtual void IncrementUpdateCounter(void){ return m_parent->intf ## _IncrementUpdateCounter();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
