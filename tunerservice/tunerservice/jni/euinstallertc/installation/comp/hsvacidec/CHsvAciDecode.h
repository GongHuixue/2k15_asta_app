#ifndef  _CHSVACIDECODE_H
#define  _CHSVACIDECODE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciDecode.h>
#include <IHsvTxtPageConvertNotify.h>
#include <IHsvPower.h>
#include <IHsvTxtPageAccess.h>
#include <IHsvAciDecodeNotify.h>
#include <IHsvAciNavigation.h>
#include <IHsvTxtPageConvert.h>
#include <ITvColorDecode2.h>
#include <IHsvTxtDecode.h>
#include <IHsvAciDecodeDiv.h>
#include <IHsvTxtDisplayDriver.h>
#include <IEnable.h>
#include <IHsvEuropeConfiguration.h>
#include <IPumpEngine.h>
#include <IHsvTxtPacket0.h>
#include <IPumpExSub.h>
#include <IHsvTxtPageRequest.h>
#include <IString.h>
class CHsvAciDecode_Priv;
class CHsvAciDecode
{
public:
ProvidesInterface<IHsvAciDecode>	acidec;

ProvidesInterface<IHsvTxtPageConvertNotify>	cnvN;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvTxtPageAccess>	acc;
RequiresInterface<IHsvAciDecodeNotify>	acidecN;
RequiresInterface<IHsvAciNavigation>	acinv;
RequiresInterface<IHsvTxtPageConvert>	cnv;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvTxtDecode>	dec;
RequiresInterface<IHsvAciDecodeDiv>	div;
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<IEnable>	dsenb;
RequiresInterface<IHsvEuropeConfiguration>	euconfig;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvTxtPacket0>	pkt0;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvTxtPageRequest>	req;
RequiresInterface<IString>	str;
public:
CHsvAciDecode();
virtual ~CHsvAciDecode();
private:
CHsvAciDecode_Priv	*m_priv;
};

#endif

