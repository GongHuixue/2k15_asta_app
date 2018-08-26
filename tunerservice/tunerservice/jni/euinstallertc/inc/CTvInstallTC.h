#ifndef CTV_INSTALLTC_H
#define CTV_INSTALLTC_H

#include <provreq.h>
#include <InfraGlobals.h>
#include <IHsvInstallation2.h>
#include <IHsvPower.h>
#include <IPlfApiTuningNotify.h>
#include <IPlfApiTuning.h>
#include <IPlfApiChanDec.h>
#include <IPlfApiChanDecDvbT.h>
#include <IPlfApiChanDecDvbC.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvInstallationNotify.h>
#include <IHsvSourceSetupNotify.h>
#include <IHsvSourceSetup.h>
#include <IPlfApiChanDecDvbT2.h>
#include <ICesOperatorProfile.h>
#include <ICesOperatorProfileNotify.h>
#include <CTvMwCore.h>
#include <IHsvTcGlobalSettings.h>
#include <CGfxNativeWindow.h>
#include <IHsvAciDisplay.h>
#include <IHsvSystemSettingsNotify.h>
#include <IHsvSystemSettings.h>


class CTvMwCore;
class CEuInstallerMw;
class CEuInstallerStub;
class IGfxANWabs;
class CTvInstallTC : private IHsvInstallationNotify,private IHsvSystemSettingsNotify
{

public:
	ProvidesInterface<IHsvInstallationNotify>		installN;
    ProvidesInterface<IHsvInstallation2>    		ins;
    ProvidesInterface<IHsvPower>    				pow;
    ProvidesInterface<IPlfApiTuningNotify>  		fetunN;
	ProvidesInterface<IHsvSourceSetupNotify>		srcstpN;
	ProvidesInterface<ICesOperatorProfileNotify>	opinsN;
	ProvidesInterface<IHsvAciDisplay>				acids;
	ProvidesInterface<IHsvSystemSettingsNotify> 	syssetN;
    
    RequiresInterface<IPlfApiTuning>        		fetun;
    RequiresInterface<IPlfApiChanDec>       		chdec;
    RequiresInterface<IPlfApiChanDecDvbT>   		chdecT;
    RequiresInterface<IPlfApiChanDecDvbC>   		chdecC;
    RequiresInterface<IPlfApiSigStrengthMeas>   	ssm;
    RequiresInterface<IHsvInstallationNotify>   	insN;
	RequiresInterface<IHsvSourceSetup>				srcstp;
	RequiresInterface<IPlfApiChanDecDvbT2>			chdecdvbt2;
	RequiresInterface<ICesOperatorProfile>			opins;
	RequiresInterface<IHsvTcGlobalSettings>			globalSettings;
	
	
	

private:
    CTvMwCore *tvMwCore;
    CEuInstallerMw *euinstalltc;
    CEuInstallerStub *stub;
	IGfxANWabs		*GfxNative;
public:
    CTvInstallTC(int token);
    ~CTvInstallTC();
	
	virtual void OnEvent(int eventid, int value);
	virtual void Notify(int property,int value);
	
	void SetSurface(ANativeWindow *pAnw);
	void DestroySurface(void);
	void setDemuxInterface(long demuxHandle);
	void setVbiInterface(long vbiHandle);

};

#endif
