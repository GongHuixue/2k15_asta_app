#ifndef  _CHSVDVBTINSTALLATION_MCOUNTRY_H
#define  _CHSVDVBTINSTALLATION_MCOUNTRY_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAltFrequencyIterator.h>
#include <IHsvInstallationNotify.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvInstallationCountrySpecifics.h>
#include <IHsvLanguageIds.h>
#include <IHsvAltFrequencyScannerNotify.h>
#include <IHsvDVBSettings.h>
#include <IHsvCountryIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvInstallation2.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
class CHsvDvbTInstallation_mcountry_Priv;
class CHsvDvbTInstallation_mcountry
{
public:
ProvidesInterface<IHsvAltFrequencyIterator>	afitr;

ProvidesInterface<IHsvInstallationNotify>	cntryinsN;

ProvidesInterface<IHsvSortedTableConfigurationEx>	freqlistconf;

ProvidesInterface<IHsvSdmControlNotifyEx>	icctrlN;

ProvidesInterface<IHsvPower>	icntrypow;

ProvidesInterface<IHsvStreamNotify>	icntrystrapiN;

ProvidesInterface<IHsvInstallationCountrySpecifics>	inscountry;

ProvidesInterface<IHsvLanguageIds>	langids;

//Required interfaces
public:
RequiresInterface<IHsvAltFrequencyScannerNotify>	afscanN;
RequiresInterface<IHsvDVBSettings>	cdvbset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvDvbTInstallation_mcountry();
virtual ~CHsvDvbTInstallation_mcountry();
private:
CHsvDvbTInstallation_mcountry_Priv	*m_priv;
};

#endif

