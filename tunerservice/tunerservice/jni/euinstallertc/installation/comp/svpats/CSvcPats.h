#ifndef  _CSVCPATS_H
#define  _CSVCPATS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCniPresetName.h>
#include <IHsvPresetSort.h>
#include <ICesCountryIds.h>
#include <ICesPatsDiv.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IString.h>
#include <IHsvTcSystemSettings.h>
class CSvcPats_Priv;
class CSvcPats
{
public:
ProvidesInterface<IHsvCniPresetName>	cniname;

ProvidesInterface<IHsvPresetSort>	prsort;

//Required interfaces
public:
RequiresInterface<ICesCountryIds>	countid;
RequiresInterface<ICesPatsDiv>	div;
RequiresInterface<IHsvLanguageIds2>	langid;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IString>	str;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CSvcPats();
virtual ~CSvcPats();
private:
CSvcPats_Priv	*m_priv;
};

#endif

