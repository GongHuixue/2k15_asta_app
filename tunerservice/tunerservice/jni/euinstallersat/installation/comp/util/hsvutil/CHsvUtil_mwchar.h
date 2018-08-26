#ifndef  _CHSVUTIL_MWCHAR_H
#define  _CHSVUTIL_MWCHAR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvUtilDiv.h>
#include <IHsvHuffmanDecoder.h>
#include <IAppApiMultiLingualStringConversion.h>
#include <IHsvSatSystemSettings.h>
class CHsvUtil_mwchar_Priv;
class CHsvUtil_mwchar
{
public:
ProvidesInterface<IHsvCharSetUtilityEx>	charsetutil;

ProvidesInterface<IHsvCharSetUtility2>	charsetutil2;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvUtilDiv>	div;
RequiresInterface<IHsvHuffmanDecoder>	istringdec;
RequiresInterface<IAppApiMultiLingualStringConversion>	ling;
RequiresInterface<IHsvSatSystemSettings>	sysset;
public:
CHsvUtil_mwchar();
virtual ~CHsvUtil_mwchar();
private:
CHsvUtil_mwchar_Priv	*m_priv;
};

#endif

