#ifndef  _CSVCPACI_MDIV_PRIV_H
#define  _CSVCPACI_MDIV_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ICesPaciDiv.h>
#include <CTCMwBase.h>
class CSvcPaci_mdiv_Priv;
#define CLASSSCOPE CSvcPaci_mdiv_Priv::
#include "locals_mdiv.h"

class CSvcPaci_mdiv_Priv : public CTCMwBase
{
public:
virtual ~CSvcPaci_mdiv_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mdiv.h"
#undef MEMBERVARS
//Provided interfaces
private:
ICesPaciDivImpl(CSvcPaci_mdiv_Priv,adiv);
public:
ProvidesInterface<ICesPaciDiv>	adiv;

//Required interfaces
public:
RequiresInterface<ICesPaciDiv>	div;

public:
CSvcPaci_mdiv_Priv():i__adiv(this)
{
adiv	=	&i__adiv;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define div_iPresent() (div.Present())
#define div_MaxPresets	ICesPaciDiv_MaxPresets
#define div_MaxTunPreset	div->MaxTunPreset()
#define div_MinTunPreset	div->MinTunPreset()
#define div_AciAcquisitionTimeoutTime	div->AciAcquisitionTimeoutTime()
#define div_RestorePageAcqTimeoutTime	div->RestorePageAcqTimeoutTime()
#define div_MultipageDisplayTimeoutTime	div->MultipageDisplayTimeoutTime()
#define div_AciTxtHdrReqDelay	div->AciTxtHdrReqDelay()
#define div_TunNotifyTimeout	div->TunNotifyTimeout()
/*
#define adiv_MaxPresets	ICesPaciDiv_MaxPresets
#define adiv_MaxTunPreset	i__adiv.m_MaxTunPreset
#define adiv_MinTunPreset	i__adiv.m_MinTunPreset
#define adiv_AciAcquisitionTimeoutTime	i__adiv.m_AciAcquisitionTimeoutTime
#define adiv_RestorePageAcqTimeoutTime	i__adiv.m_RestorePageAcqTimeoutTime
#define adiv_MultipageDisplayTimeoutTime	i__adiv.m_MultipageDisplayTimeoutTime
#define adiv_AciTxtHdrReqDelay	i__adiv.m_AciTxtHdrReqDelay
#define adiv_TunNotifyTimeout	i__adiv.m_TunNotifyTimeout
*/
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mdiv.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

