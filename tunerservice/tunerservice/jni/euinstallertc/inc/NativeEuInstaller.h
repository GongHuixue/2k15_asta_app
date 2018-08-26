/*
 * NativeInstaller.h
 *
 *  Created on: 10-May-2013
 *      Author: mahesh.mathada
 */

#ifndef NATIVEINSTALLER_H_
#define NATIVEINSTALLER_H_
#include <jni.h>
#include "CTvInstallTC.h"
#include <NativeEuInstallerJNI.h>

class NativeInstaller;

class NativeInstaller: private IHsvInstallationNotify, private IPlfApiTuning, private IPlfApiChanDec,private IPlfApiChanDecDvbC,private IPlfApiChanDecDvbT,private IPlfApiSigStrengthMeas,private IHsvSourceSetup, private IPlfApiChanDecDvbT2, private ICesOperatorProfile, private IHsvTcGlobalSettings
{
private:
        int ScanStarted;

public:
	NativeInstaller(){}
	NativeInstaller(int token,jobject thisOject);
	~NativeInstaller() { }

public:
	ProvidesInterface<IHsvInstallationNotify> insN;
	ProvidesInterface<IPlfApiTuning> fetun;
	ProvidesInterface<IPlfApiChanDec> chdec;
	ProvidesInterface<IPlfApiChanDecDvbC> chdecC;
	ProvidesInterface<IPlfApiChanDecDvbT> chdecT;
	ProvidesInterface<IPlfApiSigStrengthMeas> ssm;
	ProvidesInterface<IHsvSourceSetup>	srcstp;
	ProvidesInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
	ProvidesInterface<IHsvTcGlobalSettings>	globalSettings;
	ProvidesInterface<ICesOperatorProfile>	opins;
		
public:
	RequiresInterface<IHsvInstallation2> ins;
	RequiresInterface<IHsvPower> pow;
	RequiresInterface<IPlfApiTuningNotify> fetunN;
	RequiresInterface<IHsvSourceSetupNotify>	srcstpN;
	RequiresInterface<ICesOperatorProfileNotify>	opinsN;
	RequiresInterface<IHsvAciDisplay>				acids;

public:
	int init();
	int StartInstallation(int source,int ptc,int mode);
	int StopInstallation();
	void SetManualFrequency(int frequency, int offset,Bool finetune);
	void GetManualFrequency(int *frequency, int *offset, Bool *finetune);
	Bool IsManualInstallationModeSupported(int mode);
	void SetManualInstallationMode(int mode);
	int GetManualInstallationMode();
	void StoreManualInstallationValues(HsvChannel channel);
	Bool AutoStoreManualInstallationValues();
	Bool StartFrequencySearch();
	int GetTunerFrequency();
	void SetTunerFrequency(int freq, Bool fineTune);
	int GetNumberOfAnalogChannelsFound();
	int GetNumberOfDigitalChannelsFound();
	int GetNumberOfDigitalChannelsRemoved();
	int GetInstallationStatus();
	int GetInstallationMode();
	Bool IsUpdateInstallationSupported();
	void SetManualChannel(int channel, Bool finetune);
	void GetManualChannel( int* channel, Bool* finetune);
	long GetSignalstrength(int measmode);
	int StoreWeakSignalInstallationChannel();
	int GetInstalledWeakSignalChannel();
	Bool IsFrequencySearchDirectionSupported(Bool searchup);
	void SetFrequencySearchDirection(Bool searchup);
	Bool GetFrequencySearchDirection();
	int GetMinFrequency();
	int GetMaxFrequency();
	int GetCurrentPass();
	int GetNoOfPass();
	int GetCurrentPassType();
	Bool IsMediumSupported(int medium);
	int GetMedium();
	void SetMedium(int medium);
	void SetInstalledMedium(int medium);
	Bool IsTvSystemSupported(int tvsystem);
	void SetTvSystem(int tvsystem);
	int GetTvSystem();
	Bool IsColorSystemSupported(int colorsystem);
	void SetColorSystem(int colorsystem);
	int GetColorSystem();
	Bool IsValidPTC(int medium, int PTC);
	int GetMinPTC(int medium);
	int GetMaxPTC(int medium);
	int GetLastPTCFound();
	int GetNumberOfPTCsFound();
	void StartSigStrMeas(int measmode);
	void StopSigStrMeas(int measmode);
	Bool IsSignalStrengthMeasurementValid(int measmode);
	Bool GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue);
	Bool SetAttributeMode(int installationmode, int attribute,int attributeMode);
	Bool SetAttribute(int installationmode, int attribute,int value);
	int GetAttributeMode(int installationmode, int attribute);
	int GetAttribute(int installationmode, int attribute);
	Bool IsAvailable(int installationmode, int attribute);
	void ResetAttributeToDefault(int installationmode,int attribute);
	void ResetAttributeToPersistent(int installationmode,int attribute);
	int GetTargetNitType(Nat16 *NetworkId);
	Bool IsNetworkUpdateDetected();
	void Initialise();
	int SkipInstallationScans(int ScanTypes);
	Bool GetAltTSValues( Nat16* ONID, Nat16* TSID );
	void SetUserSymbolRates( int installationmode, int *values, int len );
	void GetUserSymbolRates(int installationmode,int * values,int * len);
	void GetPredefinedSymbolRates(int installationmode,int * values,int * len);
	int GetNetworkIDList();
	void GetNetworkIDName(int index, Nat16 *NetworkName);
    void GetChannelListIDName(int index,Nat16 *ChannelistName);
	void SetFavouriteNetworkID(int mode, int attrib, int index);
	int GetNumberOfChannelListIds();
	int GetChannelListIdByIndex(int index);
	void SetFavouriteChannelListId(int mode, int attrib, int index);
	void SetFavouriteRegion(int mode, int index, int regionType);
	void SetUserSelectConflictService(int LcnIndex, int SvcIndex);
	void ConflictsSelectionDone(Bool UserSelection);
	void GetConflictServices( HsvConflictServicesData *ConflictList, int *NumRecords );
	int GetInstallationVersion();
	int GetInstallationState();
	int GetPLPIds(int *PLPIds);
	void GetRegionList(HsvNetworkRegionsData RegionsData);
	void UserSelectionDone(Bool UserSelection);
	int GetFavouriteRegion(int mode, int RegionType);
	int GetConstellation();
	long GetSymbolRateMw();
	int GetHierarchyMode();
	Bool ZiggoNetworkDataSet(Bool ActionValue);
	void ClearPersistent();
	void GetRegionList(HsvNetworkRegionsData *RegionsData);
	void SetStreamPriority(int plpId);

	FResult GetSigStrengthRangeMw( int measmode, Nat32* min, Nat32* max);

	int OnTuned(int arg0,int arg1);
	int OnScanningStandardDetected(int arg0,int arg1);
	int OnScanEnded();
	int OnScanAborted();

	void SetInstallRfSetting(int value);
	void SetLCNSortingControl(int mode);
	void SetInstallCountry(int countryCode);
	void SetSystemCountry(int countryCode);
	void SetRfSetting(int value);
	void SetPbsMode(int value);
	void PrepareChNameUpdate(int ChUniID, int ServID);
	void GetUpdatedChannelName(Nat16* pChName);
	int GetUpdatedONID();
	int GetUpdatedTsID();
	void SetIsDVBT2Scan(int abIsTrue);
	void SetFocusedPlpId(int aiPlpId);
	void SetExtractScanResult(int abIsTrue);
	int GetUpdatedSymbolRate();
	void setDigitalOrAnalaog(int analogOrDigital);
	int getDigitalOrAnalaog();
	int getPogressStatus();
	int GetFirstIntalledAnalogueChannel();
	int GetFirstIntalledDigitalChannel();
	int GetFirstIntalledRadioChannel();

	int GetFirstInstalledChannel();
	//int getDefaultNetWorkFreq();
	Bool ifValidNetworkFreqEntered(int nwtFreq);
	Bool GetDigitalChannelOnOrOff();
	void getNetworkName(int nid,Nat16* networkName);
	int getNIDsFound(int *nids);
	int getDefaultNetworkID();
	Bool ifValidNetworkIDEntered(int nwtId);
	int getFavNetworkList(int *);
	void setFavNetwork(int nwt);
	void SetConflictSelectinDone(int val);
	void skipNetworkFreq();
	void skipNetworkID();
	int getPrimaryRegionList(int *priRegList) ;
	void setPrimarySelection(int primarySelec);
	char* getSecondaryRegionList(int primaryID );
	void setSecondarySelection(int primaryID, int secondaryID);
	char* getTertiaryRegionList(int primaryID, int secondaryID);
	void setTertiarySelection(int primaryID, int secondaryID, int tertiaryID);
	void setUserSymbolRate(int installmode,int *symbRateValue ,int symb0_symb1);

	//Srcsetup Notify
	void OnSourceSetupApplied(int status);
	
	void OnTvSystemDetected (int tvsys);

	void StartPageDisplay(void);
	int GetNoOfMtpItems(void);
	void SetCursor(Nat8 item);
	void RemoveCursor(void);
	void SelectIndex(int index);
	int GetNumberOfDatabaseRecords(int TSDataOnly);
	void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly);
	void AddTvpData(HsvPgdatTvProviderBlobData* TvpData, int Clear);
	void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData* TvpData);
	void setDemuxHandle(long demuxHandle);
	void setVbiHandle(long vbiHandle);
	int GetLastAnalogPresetNumber(void);
	
	void SetSurface(ANativeWindow *pAnw)
	{
		if (tcins) {
			tcins->SetSurface (pAnw);
		}
	}
	
	virtual void OnEvent(int eventid,int value);
	virtual FResult SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval);
	virtual FResult GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval);
	virtual FResult GetFreq(int winid,Nat32 * Freq,Nat32 * retval);
	virtual FResult GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval);
	virtual FResult GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval);
	virtual FResult SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval);
	virtual FResult StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval);
	virtual FResult StopSearch(int winid,Nat32 * retval);

	virtual FResult GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval);
	virtual FResult SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval);
	virtual FResult GetCarrierPresent(int winid,Bool * Present,Nat32 * retval);
	virtual FResult GetBer(int winid,int decoder,Nat32 * Ber);
	
	virtual FResult GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval);
	virtual FResult SetSymbolRate(int winid,Nat32 rate,Nat32 * retval);
	virtual FResult GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval);
	virtual FResult SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval);
	virtual FResult SetFreqStep(int winid,Nat32 step,Nat32 * retval);
	virtual FResult GetFreqStep(int winid,Nat32 * step,Nat32 * retval);


	virtual FResult SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval);
	virtual FResult GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval);
	virtual FResult SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval);
	virtual FResult GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval);
	virtual FResult GetHierarchyMuxPresence(int winid,Bool * HierarchymodePresent,Nat32 * retval);
	virtual FResult GetTPSId( int winid, HsvDvbTParams* TPSId, Nat32* retval );

	virtual FResult GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval);
	virtual FResult Start(int winid,Bool * Avail,Nat32 * retval);
	virtual FResult Stop(int winid,Bool * Stopped,Nat32 * retval);
	virtual FResult GetMeasValid(int winid,Bool * Valid,Nat32 * retval);
	virtual FResult GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval);

	virtual int SourceSetupApply(int Medium);

	virtual FResult GetT2CarrierPresent(int winid,Bool * Present);
	virtual FResult GetActivePlpId(int winid,int * plpid);
	virtual FResult SelectPlpId(int winid,int plpid);
	virtual FResult GetDetectedPlpIds(int winid,int * nrOfIds,int * plpids);

	virtual void GetValuesFromGlobalSettings(int ID, int *Value);
	
	virtual void RequestStatusInfo(void);
	virtual void RequestNit(void);
	virtual void SendOperatorSearchStart(Op_Search_Settings searchstart);
	virtual void SendOpExit(void);
	virtual void SendOpTuneStatus(Op_Tune_Status tuneStatus);
	virtual void SendOpAck(void);
	virtual void SendOpSearchCancel(void);
	virtual void OnOpSearchStatus(Op_ProfileSearchStatus opStatus);
	virtual void OnOpStatusInfo(Op_ProfileStatusInfo statusInfo);
	virtual void OnOpNIT(Op_ProfileNitData nitData);
	virtual void OnOpTune(Op_ProfileTuneData tuneData);
	virtual void CacheOperatorData(void);
	
	
	
public:
	CTvInstallTC *tcins;
	NativeJNI *njni;

};

#endif /* NATIVEINSTALLER_H_ */
