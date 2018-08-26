#ifndef  _CHSVPRESETINSTALLATION_MACI_H
#define  _CHSVPRESETINSTALLATION_MACI_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciData.h>
#include <IHsvCountryIds.h>
#include <ITvColorDecode2.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLanguageIds2.h>
#include <IMemoryOperations.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvInstallation2.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvTcSystemSettings.h>
class CHsvPresetInstallation_maci_Priv;
class CHsvPresetInstallation_maci
{
public:
ProvidesInterface<IHsvAciData>	acidat;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvPresetInstallation_maci();
virtual ~CHsvPresetInstallation_maci();
private:
CHsvPresetInstallation_maci_Priv	*m_priv;
};

#endif

