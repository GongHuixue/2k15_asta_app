#ifndef  _CS2INSTALLER_H
#define  _CS2INSTALLER_H 


#include <provreq.h>
#include <InfraGlobals.h>
#include <IHsvSatelliteInstallation.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvPower.h>
#include <IPlfApiDvbsTuning.h>
#include <IPlfApiTuning.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteSettings.h>
#include <ICesOperatorProfile.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvSatGlobalSettings.h>
#include <ICesCipCAMStatusNotify.h>
#include <ICesCipCAMStatus.h>

class CS2InstallerMw;
class CTvMwCore;
class CS2InstallerStub;


class CS2Installer
{

//Contained Components
private:
	CS2InstallerMw *euinstallersat;
	CS2InstallerStub *stub;
	CTvMwCore *tvMwCore;


public:
	ProvidesInterface<IHsvPower>	pow;
	ProvidesInterface<IHsvSatelliteInstallation>	ins;
	ProvidesInterface<IPlfApiTuningNotify>	plfapidvbsN;
	ProvidesInterface<IHsvSatelliteSettings> dvbset;
	ProvidesInterface<ICesOperatorProfileNotify> opinsN;
	ProvidesInterface<ICesCipCAMStatusNotify> cipStatusN;


	RequiresInterface<IPlfApiDvbsTuning>	plfdvbs;
	RequiresInterface<IPlfApiTuning>	plftune;
	RequiresInterface<IPlfApiSigStrengthMeas>	ssm;
	RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
	RequiresInterface<ICesOperatorProfile> opins;
	RequiresInterface<IHsvSatGlobalSettings>	globalsettings;
	RequiresInterface<ICesCipCAMStatus> cipStatus;

public:
	CS2Installer(int token);
	~CS2Installer();

	void setDemuxHandleInterface(long demuxHandle);

};

#endif

