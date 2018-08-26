#ifndef  _CHSVDVBSOPPROFILE_MSORT_H
#define  _CHSVDVBSOPPROFILE_MSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSorting.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteInstallation.h>
#include <CS2MwBase.h>


class CHsvDvbsOpProfile_mSort: public IHsvPower, public IHsvSorting, public CS2MwBase
{
private:
	
	Pumpdefines(CHsvDvbsOpProfile_mSort);

	#define CLASSSCOPE CHsvDvbsOpProfile_mSort::
	#define FNADDR(f) (& CLASSSCOPE f)
	#define FPCALL(f) (this->* f)

	#define CURRENT_TABLE                       (pgdb->GetCurrentTable())
	#define PTC_TABLE                           (CURRENT_TABLE | IHsvProgramDatabaseConstants_DigitalTS)
	#define SERVICE_TABLE                       (CURRENT_TABLE | IHsvProgramDatabaseConstants_DigitalService)
	#define PRESET_TABLE                        (CURRENT_TABLE | IHsvProgramDatabaseConstants_Preset)
	#define INVALID_PRESET						(0xFFFF)
	#define PRESET_NOT_ALLOCATED(presetno)      (presetno == INVALID_PRESET)
	#define STEP_SIZE							(100)	
	#define ASSIGN_PRESET_FROM_SVC(presetdat, svcdat)   ((presetdat.OriginalNetworkId = svcdat.OriginalNetworkId),\
														 (presetdat.ServiceId = svcdat.ServiceId),\
														 (presetdat.Tsid = svcdat.Tsid),\
														 (presetdat.StreamPriority = svcdat.StreamPriority),\
														 (presetdat.Frequency = svcdat.Frequency))
	#define ASSIGN_DEFAULTCOOKIES(svcdat)           		(((svcdat).CesvcCookie  = 0),\
														 ((svcdat).AppsCookie  = 0),\
														 ((svcdat).TxtCookie	 = 0))
	#define AUTO_MODE									(IHsvSatelliteInstallation_InstallationServiceScan)
	#define CAM_NIT_UPDATE_MODE							(IHsvSatelliteInstallation_InstallationCamNit)
	#define MIN_VALID_LCN    							(0)
	#define MAX_VALID_LCN    							(9999)
	#define VALID_LCN_RANGE(x)  						(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))
	#define MAX_NUM_LCN_ENTRY							8
	#define IS_RADIO_SERVICE(x)                                         	((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService))
	#define REVALIDATE(x)    								((x) &= 0x7FFF)
	#define INVALID_LCN									(0x1000)
	#define INVALIDATE(x)    								 ((x) |= 0x8000)
	#define MAX_RADIO_PRESET							(8000)
	#define MIXED_PRESET_OFFSET						(8000)
	#define RADIO_PRESET_OFFSET 						(5000)
	#define TV_PRESET_OFFSET 							(2000)
	#define MAX_PRESET_NUMBER							(9999)
	#define GETCURRENTINDEX(x)                                            (IS_RADIO_SERVICE(x) ? (mCurrentRadioIndex) : (mCurrentPresetIndex))
	
	
	typedef enum
	{
		SORT_HONOURED_SERVICES = 0,
		SORT_HONOURED_RADIO_SERVICES,
		SORT_NONHONOURED_SERVICES,
		SORT_NONHONOURED_RADIO_SERVICES,
		SORT_COMPLETE
	}SORTING_HANDLER_ENUM;

	static Pump mCamSortPmp;
	static int mCurrentRadioIndex;
	static int mCurrentPresetIndex;

	
	void mPumpHandler (int event, Nat32 param);
	void mSortHonouredServices (Bool checkForRadioServices, int startIndex);
	void mSortNonHonouredServices (Bool checkForRadioServices, int startIndex);
	void mAddEntryToPresetTable (HsvPgdatDigServiceData *svcData, int presetNo, int lcnIndex);
	void mDigitalPresetEntryforValidLCN (int dbIndex, int lcnIndex);
	void mDigitalPresetEntryforInValidLCN(int dbIndex,  int lcnIndex);
	int mGetPresetNoForService(HsvPgdatDigServiceData svcData, int fromPreset, int toPreset);
	int mFirstAvailableGapInPresetList(int fromPreset, int toPreset);
	
public:

	//IHsvPower
	virtual void Init(void);
	virtual void TurnOn(void);
	virtual void TurnOff(void);

	//IHsvSorting
	virtual void Sort(Nat32 param);

	//Constructor
	CHsvDvbsOpProfile_mSort()
	{
		isort = this;
		isortpow = this;
	}

	//Destructor
	virtual ~CHsvDvbsOpProfile_mSort()
	{
	}
	
	//Provides interfaces
	ProvidesInterface<IHsvSorting>	isort;
	ProvidesInterface<IHsvPower>	isortpow;

	//Required interfaces
	public:
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvProgramData3>	pgdat;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
	RequiresInterface<IHsvSatellitePackageInstallation>	rins;
};

#endif

