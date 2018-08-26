#ifndef  _CHSVDVBSFREESAT_MBCKGND_H
#define  _CHSVDVBSFREESAT_MBCKGND_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvPower.h>
#include <ITvPlatformResourceNotify.h>
#include <IHsvStreamNotify.h>
#include <IProdApiSystemStateObserverNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvStream.h>
#include <IHsvSdmControl2.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSorting.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <CS2MwBase.h>

/*****************************************************************************************
 * Class definition
 *****************************************************************************************/
class CHsvDvbsFreesat_mBckgnd: public IHsvPower,public IHsvSatelliteBackgroundInstallation, public IHsvStreamNotify, public CS2MwBase
							   		  //,public IHsvSatelliteInstallationNotify, public IHsvSdmControlNotifyEx, public IHsvDigitalAcquisitionNotify,
{
private:

	static Bool mActive, mUpdateDone;
	
	Pumpdefines (CHsvDvbsFreesat_mBckgnd);

	#define BACKGROUND_MODE                             (IHsvSatelliteInstallation_InstallationBackground)
	#define BACKGROUND_INSTALL                          (CHsvDvbsFreesat_mBckgnd::mIsBackgroundInstall())
	#define CURRENT_TABLE                               (pgdb->GetCurrentTable())
	#define SERVICE_TABLE                               (CURRENT_TABLE | IHsvProgramDatabaseConstants_DigitalService)
	#define	PRESET_TABLE                                (CURRENT_TABLE | IHsvProgramDatabaseConstants_Preset)
	#define VALID_VERSION(version)                      ((version >=0) && (version<=31))
	#define MIN_VALID_LCN    						    (0)
	#define	MAX_VALID_LCN    						    (2000)
	#define	VALID_LCN_RANGE(x)  					    (((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))
	#define MAX_NUM_LCN_ENTRY							(8)
	#define	INVALID_PRESET								(0x1FFF)
	#define SET_BCKGND_STATE(state)						(CHsvDvbsFreesat_mBckgnd::mBckgndStatus.State = state)
	#define CURRENT_BCKGND_STATE						(CHsvDvbsFreesat_mBckgnd::mBckgndStatus.State)

	/*
	#define CLASSSCOPE CHsvDvbsFreesat_mBckgnd::
	#define FNADDR(f) (& CLASSSCOPE f)
	#define FPCALL(f) (this->* f)
	
	typedef void (CLASSSCOPE *FunctionNat32)(Nat32);	

	typedef enum
	{
	    EvStart,
		EvStartCollection,
	    EvDataAvailable,
	    EvDataNotAvailable,
	    EvInstallComplete,
	    EvSorting,
	    EvSortComplete,
	    EvStop,
	    EvMax
	} BackgroundEvents;

	typedef	enum
	{
		StIdle = 0,
		StStarted,
		StSIAcquireWait,
		StServiceInstallWait,
		StServiceInstallComplete,
		StSorting,
		StMax
	}BackgroundState;

	typedef struct BckgndInstance
	{
		BackgroundState State;
	} BckgndInstance;


	//static Pump mBckgndPump;
	//static BckgndInstance mBckgndStatus;
	//static FunctionNat32 mEventActionMatrix[EvMax][StMax];

	/*
	void PumpHandler (int event, Nat32 param);
	void FuncStartBackgroundInstallation (Nat32 param);
	void FuncStartCollection (Nat32 param);
	void FuncDataAvailable (Nat32 param);
	void FuncDataNotAvailable (Nat32 param);
	void FuncInstallComplete (Nat32 param);
	void FuncSorting (Nat32 param);
	void FuncSortComplete (Nat32 param);
	void FuncStopBackgroundInstallation (Nat32 param);
	Bool mIsBATVersionChanged (void);
	*/
	Bool UpdateServiceTable (HSVSPTYPE(ActualTSService, dvb, sdt) service);
	Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
	void mCopyString(Nat16* dest, Nat16* src, int maxchars);
	Bool mIsBackgroundInstall (void);
	
public:

	//IHsvPower
	virtual void Init(void);
	virtual void TurnOn(void);
	virtual void TurnOff(void);

	//IHsvSatelliteBackgroundInstallation
	virtual void EnableBackgroundInstallation (void);
	virtual void DisableBackgroundInstallation (void);

	//IHsvStreamNotify
	virtual void OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3);
	virtual void OnChanged (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid);
	virtual void OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3);
	virtual void OnCompleted (HsvDestination dest, int spid);

	/*IHsvSatelliteInstallationNotify
	void OnEvent (int eventId, int value);
	//IHsvSdmControlNotifyEx
	virtual void OnEvent (HsvDemux dmx, int eventid, int value);

	//IHsvDigitalAcquisitionNotify
	virtual void OnDataAquired  (Bool Status);
	*/

	//Constructor
	CHsvDvbsFreesat_mBckgnd()
	{
		ibckgndpow = this;
		ibckInstall = this;
		strapiN = this;
		//iinsN = this;
		//bckctrlN = this;
		//ibckAcqN = this;
	}

	//Destructor
	virtual ~CHsvDvbsFreesat_mBckgnd()
	{

	}

	//Provides interfaces
	ProvidesInterface<IHsvPower> ibckgndpow;
	ProvidesInterface<IHsvSatelliteBackgroundInstallation> ibckInstall;
	ProvidesInterface<IHsvStreamNotify>	strapiN;
	//ProvidesInterface<IHsvSatelliteInstallationNotify>	iinsN;
	//ProvidesInterface<IHsvSdmControlNotifyEx> bckctrlN;
	//ProvidesInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;

	//Required interfaces
	RequiresInterface<IHsvErrorCodeEx>	err;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvDigitalAcquisition>	idataacq;
	RequiresInterface<IHsvSatelliteInstallation>	insstate;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IHsvProgramData3>	pgdat;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<ITvPlatformResource>	plfres;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvSatelliteDiversity>	s2div;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvSdmControl2>	ctrl;
	RequiresInterface<IHsvSatelliteSettings> isettings;
	RequiresInterface<IHsvSorting>	isort;

};

#endif
