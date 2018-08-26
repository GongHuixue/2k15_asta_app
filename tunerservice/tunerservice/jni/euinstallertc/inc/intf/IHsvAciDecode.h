#ifndef IHSVACIDECODE_H
#define IHSVACIDECODE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciDecode
{
public:
	virtual ~IHsvAciDecode(){}
	virtual void DecodeStart(PageNr pn)= 0;
	virtual void DecodeStop(void)= 0;
	virtual void Reset(void)= 0;
	virtual int GetDecodeStatus(void)= 0;
	virtual void ContinueDecoding(void)= 0;
	virtual HsvAciMode GetMode(void)= 0;
	virtual HsvAciNetwork GetNetworkInformation(void)= 0;
	virtual HsvAciBroadcaster GetBroadcasterInformation(void)= 0;
	virtual Nat8 GetNoOfPresetEntries(void)= 0;
	virtual Nat8 GetNoOfMultipackageItems(void)= 0;
	virtual HsvAciLanguage GetAciLanguage(Nat8 lanIndex)= 0;
	virtual PageNr GetExtensionPageForLanguage(HsvAciLanguage lan)= 0;
	virtual PageNr GetExtensionPage(void)= 0;
	virtual Bool GetSinglePackageInformation(Nat8 packageIndex,HsvAciSingleInfo * singleInfo)= 0;
	virtual Bool GetMultiPackageInformation(Nat8 packageIndex,HsvAciMultiInfo * multiInfo)= 0;
	virtual PageNr GetDefaultPage(void)= 0;
	virtual Bool MatchServiceLabel(Nat8 * srcLabel)= 0;
	virtual void DisplayACIPage(PageNr pn)= 0;
	virtual Bool IsAciPresent(void)= 0;
	virtual void SetCursor(Nat8 item)= 0;
	virtual void RemoveCursor(void)= 0;
	virtual void RemoveACIPage(PageNr pn)= 0;
	#define IHsvAciDecode_ConstAciPage		((int)0x1BE )
	#define IHsvAciDecode_StateIdle		((int)1 )
	#define IHsvAciDecode_StateDecoding		((int)2 )
	#define IHsvAciDecode_StateSuccess		((int)3 )
	#define IHsvAciDecode_StateFail		((int)4 )
};


#define IHsvAciDecodeImpl(Comp,intf)    \
virtual void intf ## _DecodeStart(PageNr pn);\
virtual void intf ## _DecodeStop(void);\
virtual void intf ## _Reset(void);\
virtual int intf ## _GetDecodeStatus(void);\
virtual void intf ## _ContinueDecoding(void);\
virtual HsvAciMode intf ## _GetMode(void);\
virtual HsvAciNetwork intf ## _GetNetworkInformation(void);\
virtual HsvAciBroadcaster intf ## _GetBroadcasterInformation(void);\
virtual Nat8 intf ## _GetNoOfPresetEntries(void);\
virtual Nat8 intf ## _GetNoOfMultipackageItems(void);\
virtual HsvAciLanguage intf ## _GetAciLanguage(Nat8 lanIndex);\
virtual PageNr intf ## _GetExtensionPageForLanguage(HsvAciLanguage lan);\
virtual PageNr intf ## _GetExtensionPage(void);\
virtual Bool intf ## _GetSinglePackageInformation(Nat8 packageIndex,HsvAciSingleInfo * singleInfo);\
virtual Bool intf ## _GetMultiPackageInformation(Nat8 packageIndex,HsvAciMultiInfo * multiInfo);\
virtual PageNr intf ## _GetDefaultPage(void);\
virtual Bool intf ## _MatchServiceLabel(Nat8 * srcLabel);\
virtual void intf ## _DisplayACIPage(PageNr pn);\
virtual Bool intf ## _IsAciPresent(void);\
virtual void intf ## _SetCursor(Nat8 item);\
virtual void intf ## _RemoveCursor(void);\
virtual void intf ## _RemoveACIPage(PageNr pn);\
class Comp ## _ ## intf : public IHsvAciDecode \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void DecodeStart(PageNr pn){ return m_parent->intf ## _DecodeStart(pn);}\
virtual void DecodeStop(void){ return m_parent->intf ## _DecodeStop();}\
virtual void Reset(void){ return m_parent->intf ## _Reset();}\
virtual int GetDecodeStatus(void){ return m_parent->intf ## _GetDecodeStatus();}\
virtual void ContinueDecoding(void){ return m_parent->intf ## _ContinueDecoding();}\
virtual HsvAciMode GetMode(void){ return m_parent->intf ## _GetMode();}\
virtual HsvAciNetwork GetNetworkInformation(void){ return m_parent->intf ## _GetNetworkInformation();}\
virtual HsvAciBroadcaster GetBroadcasterInformation(void){ return m_parent->intf ## _GetBroadcasterInformation();}\
virtual Nat8 GetNoOfPresetEntries(void){ return m_parent->intf ## _GetNoOfPresetEntries();}\
virtual Nat8 GetNoOfMultipackageItems(void){ return m_parent->intf ## _GetNoOfMultipackageItems();}\
virtual HsvAciLanguage GetAciLanguage(Nat8 lanIndex){ return m_parent->intf ## _GetAciLanguage(lanIndex);}\
virtual PageNr GetExtensionPageForLanguage(HsvAciLanguage lan){ return m_parent->intf ## _GetExtensionPageForLanguage(lan);}\
virtual PageNr GetExtensionPage(void){ return m_parent->intf ## _GetExtensionPage();}\
virtual Bool GetSinglePackageInformation(Nat8 packageIndex,HsvAciSingleInfo * singleInfo){ return m_parent->intf ## _GetSinglePackageInformation(packageIndex,singleInfo);}\
virtual Bool GetMultiPackageInformation(Nat8 packageIndex,HsvAciMultiInfo * multiInfo){ return m_parent->intf ## _GetMultiPackageInformation(packageIndex,multiInfo);}\
virtual PageNr GetDefaultPage(void){ return m_parent->intf ## _GetDefaultPage();}\
virtual Bool MatchServiceLabel(Nat8 * srcLabel){ return m_parent->intf ## _MatchServiceLabel(srcLabel);}\
virtual void DisplayACIPage(PageNr pn){ return m_parent->intf ## _DisplayACIPage(pn);}\
virtual Bool IsAciPresent(void){ return m_parent->intf ## _IsAciPresent();}\
virtual void SetCursor(Nat8 item){ return m_parent->intf ## _SetCursor(item);}\
virtual void RemoveCursor(void){ return m_parent->intf ## _RemoveCursor();}\
virtual void RemoveACIPage(PageNr pn){ return m_parent->intf ## _RemoveACIPage(pn);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
