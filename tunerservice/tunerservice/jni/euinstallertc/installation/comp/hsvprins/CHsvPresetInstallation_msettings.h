#ifndef  _CHSVPRESETINSTALLATION_MSETTINGS_H
#define  _CHSVPRESETINSTALLATION_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAnalogSettings.h>
#include <ITvColorDecode2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvWindowDestinationMap.h>
class CHsvPresetInstallation_msettings_Priv;
class CHsvPresetInstallation_msettings
{
public:
ProvidesInterface<IHsvAnalogSettings>	anaset;

//Required interfaces
public:
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ITvColorDecode2>	xcol;
public:
CHsvPresetInstallation_msettings();
virtual ~CHsvPresetInstallation_msettings();
private:
CHsvPresetInstallation_msettings_Priv	*m_priv;
};

#endif

