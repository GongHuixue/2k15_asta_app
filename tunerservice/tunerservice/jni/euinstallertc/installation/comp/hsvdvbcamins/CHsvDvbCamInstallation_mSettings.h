#ifndef  _CHSVDVBCAMINSTALLATION_MSETTINGS_H
#define  _CHSVDVBCAMINSTALLATION_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSettings.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IString.h> 
#include <IHsvInstallation2.h>
class CHsvDvbCamInstallation_mSettings_Priv;
class CHsvDvbCamInstallation_mSettings
{
public:
ProvidesInterface<IHsvDVBSettings>	idvbset;
ProvidesInterface<IHsvPower>	isetpow;
ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;
public:
RequiresInterface<IString>	str; 
RequiresInterface<IHsvInstallation2>	rins;
public:
CHsvDvbCamInstallation_mSettings();
virtual ~CHsvDvbCamInstallation_mSettings();
private:
CHsvDvbCamInstallation_mSettings_Priv	*m_priv;
};

#endif

