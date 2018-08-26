#ifndef  _CHSVUTIL_H
#define  _CHSVUTIL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvUtil_gpimwchar.h>
#include <CHsvUtil_mhuffdec.h>
#include <CHsvUtil_mwchar.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvHuffmanDecoder.h>
#include <IHsvCountryIds.h>
#include <IHsvUtilDiv.h>
#include <IHsvTcSystemSettings.h>
#include<IMultiLingualStringConversion.h>

class CHsvUtil
{
public:
virtual ~CHsvUtil(){}

//Contained Modules
private:
CHsvUtil_gpimwchar gpimwchar;
CHsvUtil_mhuffdec mhuffdec;
CHsvUtil_mwchar mwchar;
public:
ProvidesInterface<IHsvCharSetUtilityEx>	charsetutil;

ProvidesInterface<IHsvCharSetUtility2>	charsetutil2;

ProvidesInterface<IHsvHuffmanDecoder>	stringdec;

ProvidesInterface<IMultiLingualStringConversion>	ling;
//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvUtilDiv>	div;
RequiresInterface<IHsvTcSystemSettings>	sysset;

public:
CHsvUtil()
{
charsetutil	=	mwchar.charsetutil;
charsetutil2	=	mwchar.charsetutil2;
mwchar.ling	=	gpimwchar.ling;
ling                =     gpimwchar.ling;
mwchar.cids	=	cids;
mwchar.div	=	div;
mwchar.sysset	=	sysset;
mwchar.istringdec	=	mhuffdec.istringdec;
stringdec	=	mhuffdec.istringdec;
}

};

#endif

