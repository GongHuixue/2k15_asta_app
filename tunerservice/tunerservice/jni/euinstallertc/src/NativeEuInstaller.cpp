/*
 * NativeInstaller.cpp
 *
 *  Created on: 10-May-2013
 *      Author: mahesh.mathada
 */

#include "NativeEuInstaller.h"

#ifdef AOSP_BUILD_TC
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif
#include "NativeEuInstallerJNI.h"
#include <stdio.h>
#include "CTvInstallTC.h"

#define TVSYS_NONE 0x00000000
#define  TVSYS_BG   0x00000001
#define TVSYS_I    0x00000002
#define TVSYS_DK   0x00000004
#define TVSYS_L    0x00000008
#define TVSYS_M    0x00000010
#define TVSYS_BG_A2 0x00000020
#define TVSYS_DK_A2 0x00000040

 NativeInstaller::NativeInstaller(int tokenId,jobject javahan)
{
	__android_log_print(ANDROID_LOG_DEBUG, "NativeInstaller","createInstance");
	insN = this;
	fetun = this;

	chdec = this;
	chdecC = this;
	chdecT = this;
	ssm = this;
	srcstp = this;
	chdecdvbt2 = this;
	globalSettings =  this;
	tcins = new CTvInstallTC(tokenId);

	ins = tcins->ins;
	acids = tcins->acids;
	srcstpN = tcins-> srcstpN;
	tcins->insN = insN;

	fetunN = tcins->fetunN ;
	opinsN = tcins->opinsN;
	tcins->fetun = fetun;
	pow = tcins->pow;

	tcins->chdec = chdec;
	tcins->chdecC = chdecC;
	tcins->chdecT = chdecT;

	tcins->ssm = ssm;
	tcins->srcstp = srcstp;
	tcins->chdecdvbt2 = chdecdvbt2;
	opins = this;
	tcins->opins = opins;
	njni = new NativeJNI();
	tcins->globalSettings = globalSettings;

	pow->TurnOn();

	ScanStarted = 0;
}
int NativeInstaller::init()
{
	pow->Init();
	pow->TurnOn();
	return 0;
}

int NativeInstaller::StartInstallation(int source,int ptc,int mode)
{
	ins->StartInstallation(source,ptc,mode);
	return 0;
}

int NativeInstaller::StopInstallation()
{
	ins->StopInstallation();
	return 0;
}


void NativeInstaller::SetManualFrequency(int frequency, int offset,Bool finetune)
{
	ins->SetManualFrequency(frequency,offset,finetune);
}

void NativeInstaller::GetManualFrequency(int *frequency, int *offset, Bool *finetune)
{
	return ins->GetManualFrequency(frequency,offset,finetune);
}
Bool NativeInstaller::IsManualInstallationModeSupported(int mode)
{
	return ins->IsManualInstallationModeSupported( mode);
}
void NativeInstaller::SetManualInstallationMode(int mode)
{ 
	ins->SetManualInstallationMode( mode);
}
int NativeInstaller::GetManualInstallationMode()
{ 
	return ins->GetManualInstallationMode();
}
void NativeInstaller::StoreManualInstallationValues(HsvChannel channel)
{ 
	 ins->StoreManualInstallationValues(channel);
}
Bool NativeInstaller::AutoStoreManualInstallationValues()
{ 
	return ins->AutoStoreManualInstallationValues();
}
Bool NativeInstaller::StartFrequencySearch()
{ 
	return ins->StartFrequencySearch();
}
int NativeInstaller::GetTunerFrequency()
{ 
	return ins->GetTunerFrequency();
}
void NativeInstaller::SetTunerFrequency(int freq, Bool fineTune)
{
	ins->SetTunerFrequency(freq,fineTune);
}
int NativeInstaller::GetNumberOfAnalogChannelsFound()
{
	return ins->GetNumberOfAnalogChannelsFound();
}
int NativeInstaller::GetNumberOfDigitalChannelsFound(                    )
{
	return ins->GetNumberOfDigitalChannelsFound();
}
int NativeInstaller::GetNumberOfDigitalChannelsRemoved()
{
	return ins->GetNumberOfDigitalChannelsRemoved();
}
int NativeInstaller::GetInstallationStatus()
{
	return ins->GetInstallationStatus();
}
int NativeInstaller::GetInstallationMode()
{
	return ins->GetInstallationMode();
}
Bool NativeInstaller::IsUpdateInstallationSupported()
{
	return ins->IsUpdateInstallationSupported();
}
void NativeInstaller::SetManualChannel(int channel, Bool finetune)
{
	ins->SetManualChannel(channel,finetune);
}

long NativeInstaller::GetSignalstrength(int measmode)
{
	return ins->GetSignalstrength(measmode);
}
int NativeInstaller::StoreWeakSignalInstallationChannel()
{
	return ins->StoreWeakSignalInstallationChannel();
}

void NativeInstaller::GetNetworkIDName(int index, Nat16 *NetworkName)
{
	ins->GetNetworkIDName(index,NetworkName);
}

void NativeInstaller::GetConflictServices( HsvConflictServicesData *ConflictList, int *NumRecords )
{
	ins->GetConflictServices(ConflictList,NumRecords);
}

Bool NativeInstaller::GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue)
{
	return ins->GetAttributeRange(installationmode,attribute,minValue,maxValue);
}

void NativeInstaller::SetUserSymbolRates( int installationmode, int *values, int len )
{
	ins->SetUserSymbolRates( installationmode,values,len );
}
Bool NativeInstaller::GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
	return ins->GetAltTSValues(ONID,TSID);
}

int NativeInstaller::GetInstalledWeakSignalChannel()
{
	HsvChannel hsv;
	hsv = ins->GetInstalledWeakSignalChannel();
	return hsv.Channel.Digit;
}

Bool NativeInstaller::IsFrequencySearchDirectionSupported(Bool searchup)
{
	return ins->IsFrequencySearchDirectionSupported(searchup);
}
void NativeInstaller::SetFrequencySearchDirection(Bool searchup)
{
	ins->SetFrequencySearchDirection(searchup);
}
Bool NativeInstaller::GetFrequencySearchDirection()
{
	return ins->GetFrequencySearchDirection();
}
int NativeInstaller::GetMinFrequency()
{
	return ins->GetMinFrequency();
}
int NativeInstaller::GetMaxFrequency()
{
	return ins->GetMaxFrequency();
}
int NativeInstaller::GetCurrentPass()
{
	return ins->GetCurrentPass();
}
int NativeInstaller::GetNoOfPass()
{
	return ins->GetNoOfPass();
}
int NativeInstaller::GetCurrentPassType()
{
	return ins->GetCurrentPassType();
}
Bool NativeInstaller::IsMediumSupported(int medium)
{
	return ins->IsMediumSupported(medium);
}
int NativeInstaller::GetMedium()
{
	return ins->GetMedium();
}
void NativeInstaller::SetMedium(int medium)
{
	if(tcins->ins != NULL)
	{
		ins->SetMedium(medium);
	}
}
void NativeInstaller::SetInstalledMedium(int medium)
{
	ins->SetInstalledMedium(medium);
}
Bool NativeInstaller::IsTvSystemSupported(int tvsystem)
{
	return ins->IsTvSystemSupported(tvsystem);
}
void NativeInstaller::SetTvSystem(int tvsystem)
{
	ins->SetTvSystem(tvsystem);
}
int NativeInstaller::GetTvSystem()
{
	return ins->GetTvSystem();
}
Bool NativeInstaller::IsColorSystemSupported(int colorsystem)
{
	return ins->IsColorSystemSupported(colorsystem);
}
void NativeInstaller::SetColorSystem(int colorsystem)
{
	ins->SetColorSystem(colorsystem);
}
int NativeInstaller::GetColorSystem()
{
	return ins->GetColorSystem();
}
Bool NativeInstaller::IsValidPTC(int medium, int ptc)
{
	return ins->IsValidPTC(medium,ptc);
}
int NativeInstaller::GetMinPTC(int medium)
{
	return ins->GetMinPTC(medium);
}
int NativeInstaller::GetMaxPTC(int medium)
{
	return ins->GetMaxPTC(medium);
}
int NativeInstaller::GetLastPTCFound()
{
	return ins->GetLastPTCFound();
}
int NativeInstaller::GetNumberOfPTCsFound()
{
	return ins->GetNumberOfPTCsFound();
}
void NativeInstaller::StartSigStrMeas(int measmode)
{
	ins->StartSigStrMeas(measmode);
}
void NativeInstaller::StopSigStrMeas(int measmode)
{
	ins->StopSigStrMeas(measmode);

}
Bool NativeInstaller::IsSignalStrengthMeasurementValid(int measmode)
{
	return ins->IsSignalStrengthMeasurementValid(measmode);
}
Bool NativeInstaller::SetAttributeMode(int installationmode, int attribute,int attributeMode)
{
	return ins->SetAttributeMode(installationmode,attribute,attributeMode);
}
Bool NativeInstaller::SetAttribute(int installationmode, int attribute,int value)
{
	if (attribute == IHsvInstallation2_AttributeDigitalOption) 
	{
		ins->SetAttribute (installationmode, IHsvInstallation2_AttributeAnalogEnabled, value);
	}
	return ins->SetAttribute(installationmode,attribute,value);
}
int NativeInstaller::GetAttributeMode(int installationmode, int attribute)
{
	return ins->GetAttributeMode(installationmode,attribute);
}
int NativeInstaller::GetAttribute(int installationmode, int attribute)
{
	return ins->GetAttribute(installationmode,attribute);
}
Bool NativeInstaller::IsAvailable(int installationmode, int attribute)
{
	return ins->IsAvailable(installationmode,attribute);
}
void NativeInstaller::ResetAttributeToDefault(int installationmode,int attribute)
{
	ins->ResetAttributeToDefault(installationmode,attribute);
}
void NativeInstaller::ResetAttributeToPersistent(int installationmode,int attribute)
{
	ins->ResetAttributeToPersistent(installationmode,attribute);
}
Bool NativeInstaller::IsNetworkUpdateDetected()
{
	return ins->IsNetworkUpdateDetected();
}
void NativeInstaller::Initialise()
{
	ins->Initialise();
}
int NativeInstaller::SkipInstallationScans(int ScanTypes)
{
	return ins->SkipInstallationScans(ScanTypes);
}

void NativeInstaller::GetUserSymbolRates(int installationmode,int *values,int *len)
{
	return ins->GetUserSymbolRates(installationmode,values,len);
}
void NativeInstaller::setUserSymbolRate(int installmode,int *symbRateValue,int symb0_symb1)
{
	ins->SetUserSymbolRates(installmode,symbRateValue,symb0_symb1);
	
}

void NativeInstaller::GetPredefinedSymbolRates(int installationmode,int * values,int * len)
{
	ins->GetPredefinedSymbolRates(installationmode,values,len);
}

int NativeInstaller::GetNetworkIDList()
{
	return ins->GetNetworkIDList();
}

void NativeInstaller::SetFavouriteNetworkID(int mode, int attrib, int index)
{
	ins->SetFavouriteNetworkID(mode,attrib,index);
}
void NativeInstaller::SetFavouriteRegion(int mode, int index, int regionType)
{
	ins->SetFavouriteRegion(mode,index,(HsvEnmRegionType)regionType); //check
}
void NativeInstaller::SetUserSelectConflictService(int LcnIndex, int SvcIndex)
{
	ins->SetUserSelectConflictService(LcnIndex,SvcIndex);
}
void NativeInstaller::ConflictsSelectionDone(Bool UserSelection)
{
	ins->ConflictsSelectionDone(UserSelection);
}
int NativeInstaller::GetInstallationVersion()
{
	return ins->GetInstallationVersion();
}
int NativeInstaller::GetInstallationState()
{
	return ins->GetInstallationState();
}
int NativeInstaller::GetPLPIds(int *PLPIds)
{
	return ins->GetPLPIds(PLPIds);

}
void NativeInstaller::GetManualChannel( int* channel, Bool* finetune)
{
	ins->GetManualChannel( channel, finetune);
}

FResult NativeInstaller::GetSigStrengthRangeMw( int measmode, Nat32* min, Nat32* max)
{
	*min = 0;
	*max = 100;
	return 0; //ins->GetSigStrengthRange( measmode, min,max);

}
int NativeInstaller::GetTargetNitType(Nat16 *NetworkId)
{
	return ins->GetTargetNitType(NetworkId); //check
}
void NativeInstaller::GetRegionList(HsvNetworkRegionsData *RegionsData)
{
	ins->GetRegionList(RegionsData); //check
}
void NativeInstaller::UserSelectionDone(Bool UserSelection)
{
	ins->UserSelectionDone(UserSelection);
}
int NativeInstaller::GetFavouriteRegion(int mode, int RegionType)
{
	return 0;
}

long NativeInstaller::GetSymbolRateMw()
{
	return ins->GetSymbolRate();
}
int NativeInstaller::GetHierarchyMode()
{
	return ins->GetHierarchyMode();
}
Bool NativeInstaller::ZiggoNetworkDataSet(Bool ActionValue)
{
	return ins->ZiggoNetworkDataSet(ActionValue);
}
void NativeInstaller::ClearPersistent()
{
	ins->ClearPersistent();
}

void NativeInstaller::OnSourceSetupApplied(int status)
{
	if(tcins->srcstpN != NULL)
	{
		srcstpN->OnSourceSetupApplied(status);
	}

}

void NativeInstaller::StartPageDisplay(void)
{
	acids->StartPageDisplay();
	return;
}

int NativeInstaller::GetNoOfMtpItems(void)
{
	return acids->GetNoOfMtpItems();
}

void NativeInstaller::SetCursor(Nat8 item)
{
	acids->SetCursor(item);
	return;
}

void NativeInstaller::RemoveCursor(void)
{
	acids->RemoveCursor();
	return;
}

void NativeInstaller::SelectIndex(int index)
{
	acids->SelectIndex(index);
	return;
}

	/*** TVPROVIDER IMPLEMENTATION START ***/
int NativeInstaller::GetNumberOfDatabaseRecords(int TSDataOnly)
{
	return ins->GetNumberOfDatabaseRecords(TSDataOnly);
}

void NativeInstaller::GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)
{
	ins->GetTvProviderBlobDataByIndex(Index,TvProviderBlobData,InstallerPrivateBlobData,TSDataOnly);
	return;
}

void NativeInstaller::AddTvpData(HsvPgdatTvProviderBlobData* TvpData, int Clear)
{
	ins->AddTvpData(TvpData,Clear);
	return;	
}


void NativeInstaller::SyncUniqueIdToMW (HsvPgdatTvProviderBlobData* TvpData)
{
	ins->SyncUniqueIdToMW (TvpData);
	return;	
}

int NativeInstaller::GetLastAnalogPresetNumber()
{
	return ins->GetLastAnalogPresetNumber();
}


	/*** TVPROVIDER IMPLEMENTATION END ***/
FResult NativeInstaller::GetFreq(int winid,Nat32 * Freq,Nat32 * retval)
{

	njni->getFreq(Freq);
//	*Freq = ((*Freq) / 1000) * 16 ;
	*retval = 0;

	return 0;
}
void NativeInstaller::OnEvent(int eventid,int value)
{
	njni->onEvent(eventid,value);
}

FResult NativeInstaller::SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval)
{
	njni->tune(freq,finetune);
	return 0;
}

int NativeInstaller::OnTuned(int arg0,int arg1)
{
	if(arg0 == 1)
	{
		fetunN->OnStationFound();
	}
	else
	{
		fetunN->OnStationNotFound();	
	}
	return 0;
}

int NativeInstaller::OnScanningStandardDetected(int arg0, int arg1)
{
	fetunN->OnStationFound();
	return 0;
}
int NativeInstaller::OnScanAborted()
{
	ScanStarted = 0;
	fetunN->OnStationNotFound();
	return 0;
}

int NativeInstaller::OnScanEnded()
{
	ScanStarted = 0;
	fetunN->OnStationNotFound();
	return 0;
}

void NativeInstaller::OnTvSystemDetected (int tvsys)
{
	Nat32 TvSystem=0;

	
	if(tvsys == TVSYS_BG )
	{
	   TvSystem = tmFe_TvSystemBg ;
	}
	else if(tvsys == TVSYS_I )
	{
		TvSystem = tmFe_TvSystemI ;
	}
	else if(tvsys == TVSYS_DK )
	{
		TvSystem = tmFe_TvSystemDk ;
	}
	else if(tvsys == TVSYS_L )
	{
		TvSystem = tmFe_TvSystemL ;
	}
	else if (tvsys == TVSYS_M)
	{
		TvSystem = tmFe_TvSystemM;
	}
	else if(tvsys == TVSYS_BG_A2)
	{
		TvSystem = tmFe_TvSystemBG_A2;
	}
	else if(tvsys == TVSYS_DK_A2)
	{
		TvSystem = tmFe_TvSystemDK_A2;
	}

	
	fetunN->OnTvSystemDetected(TvSystem);
}

void NativeInstaller::SetInstallRfSetting(int value)
{
	ins->SetInstallRfSetting(value);
}

void NativeInstaller::SetPbsMode(int value)
{
	ins->SetPbsMode(value);
}

void NativeInstaller::PrepareChNameUpdate(int ChUniID, int ServID)
{
	ins->PrepareChNameUpdate(ChUniID, ServID);
}

void NativeInstaller::GetUpdatedChannelName(Nat16* pChName)
{
	ins->GetUpdatedChannelName(pChName);
}

int NativeInstaller::GetUpdatedONID()
{
	return ins->GetUpdatedONID();
}

int NativeInstaller::GetUpdatedTsID()
{
	return ins->GetUpdatedTsID();
}

void NativeInstaller::SetIsDVBT2Scan(int abIsTrue)
{
	ins->SetIsDVBT2Scan(abIsTrue);
}

void NativeInstaller::SetFocusedPlpId(int aiPlpId)
{
	ins->SetFocusedPlpId(aiPlpId);
}

void NativeInstaller::SetExtractScanResult(int abIsTrue)
{
	ins->SetExtractScanResult(abIsTrue);
}

int NativeInstaller::GetUpdatedSymbolRate()
{
	return ins->GetUpdatedSymbolRate();
}

void NativeInstaller::SetLCNSortingControl(int mode)
{
    ins->SetLCNSortingControl(mode);
}
void NativeInstaller::SetInstallCountry(int countryCode)
{
	ins->SetInstallCountry(countryCode);
}
void NativeInstaller::SetSystemCountry(int countryCode)
{
	ins->SetSystemCountry(countryCode);
}
void NativeInstaller::setDigitalOrAnalaog(int analogOrDigital)
{
	if ((analogOrDigital == 2) | (analogOrDigital == 1))
	{
		ins->SetAttribute (IHsvInstallation2_InstallationModeAutomatic, IHsvInstallation2_AttributeAnalogEnabled, true);
	}
	else
	{
		ins->SetAttribute (IHsvInstallation2_InstallationModeAutomatic, IHsvInstallation2_AttributeAnalogEnabled, false);
	}
}
int NativeInstaller::getDigitalOrAnalaog()
{
	return 0;
}
int NativeInstaller::getPogressStatus()
{
	int status = ins->GetInstallationProgress();
	
	return status;
}

int NativeInstaller::GetFirstIntalledAnalogueChannel()
{
	int channelno;	
	ins->GetFirstIntalledAnalogueChannel(&channelno);
	return channelno;
}
int NativeInstaller::GetFirstIntalledDigitalChannel()
{
	int channelno;
	ins->GetFirstIntalledDigitalChannel(&channelno);
	return channelno;
}
int NativeInstaller::GetFirstIntalledRadioChannel()
{

	int channelno;	
	ins->GetFirstIntalledRadioChannel(&channelno);
	return channelno;
}

int NativeInstaller::GetFirstInstalledChannel()
{
	int channelno;	
	ins->GetFirstInstalledChannel(&channelno);
	return channelno;
}

Bool NativeInstaller::ifValidNetworkFreqEntered(int nwtFreq)
{
	int minValue;
	int maxValue;
	Bool retValue = false;

	ins->GetAttributeRange(IHsvInstallation2_InstallationModeAutomatic,IHsvInstallation2_AttributeNetworkFreq,&minValue,&maxValue);

	if((nwtFreq < minValue) || (nwtFreq > maxValue) )
	{
		retValue = true;
	}

	return retValue;
}

Bool NativeInstaller::GetDigitalChannelOnOrOff()
{
	//ins->GetAttribute(IHsvInstallation2_InstallationModeAutomatic,);
	
	return true;
}
void NativeInstaller::getNetworkName(int nid,Nat16* networkName)
{
	ins->GetNetworkNameForNetworkID(nid,networkName);
}
int NativeInstaller::getNIDsFound(int *nids)
{
	int NumberOfEntries;
	int NetworkIDList[200];
	int i = 0;
	ins->GetListOfNetworkIDs(&NumberOfEntries,NetworkIDList);
	for(i = 0; i < NumberOfEntries; i++) {
		__android_log_print(ANDROID_LOG_DEBUG, "NativeInstaller","### getNIDsFound value [%d]",NetworkIDList[i]);
		nids[i] = NetworkIDList[i];
	}
	
	return NumberOfEntries;
}
int NativeInstaller::getDefaultNetworkID()
{
	unsigned short NetworkId;
	ins->GetTargetNitType(&NetworkId);

	return NetworkId;
}
Bool NativeInstaller::ifValidNetworkIDEntered(int nwtId)
{
	Bool	ValidNetwork = true;

	ValidNetwork = ins->IsValidNetworkId(nwtId);

	return ValidNetwork;
}
int NativeInstaller::getFavNetworkList(int *)
{

	return 0;
}
void NativeInstaller::setFavNetwork(int nwt)
{

}
void NativeInstaller::SetConflictSelectinDone(int val)
{
}
void NativeInstaller::skipNetworkFreq()
{
}
void NativeInstaller::skipNetworkID()
{
}
int NativeInstaller::getPrimaryRegionList(int *priRegList)
{

	return 0;
}
void NativeInstaller::setPrimarySelection(int primarySelec)
{
}
char* NativeInstaller::getSecondaryRegionList(int primaryID )
{

	return NULL;
}
void NativeInstaller::setSecondarySelection(int primaryID, int secondaryID)
{
}
char* NativeInstaller::getTertiaryRegionList(int primaryID, int secondaryID)
{
	return NULL;
}
void NativeInstaller::setTertiarySelection(int primaryID, int secondaryID, int tertiaryID)
{
}

FResult NativeInstaller::GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval)
{
	njni->getFreqRange(MinFreq,MaxFreq);
	*MinFreq = ((*MinFreq) / 1000) * 16 ;
	*MaxFreq = ((*MaxFreq) / 1000) * 16 ;
	*retval = 0;


	return 0;
}

 FResult NativeInstaller::GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval)
{

/*	 typedef enum _tmFe_TvSystem_t
	 {
	     tmFe_TvSystemNone = 0x00000001,
	     tmFe_TvSystemBg = 0x00000002,
	     tmFe_TvSystemD = 0x00000004,
	     tmFe_TvSystemDk = 0x00000008,
	     tmFe_TvSystemDk1 = 0x00000010,
	     tmFe_TvSystemDk2 = 0x00000020,
	     tmFe_TvSystemI = 0x00000040,
	     tmFe_TvSystemH = 0x00000080,
	     tmFe_TvSystemK1 = 0x00000100,
	     tmFe_TvSystemL = 0x00000200,
	     tmFe_TvSystemL1 = 0x00000400,
	     tmFe_TvSystemM = 0x00000800,
	     tmFe_TvSystemN = 0x00001000,
	     tmFe_TvSystemC64Qam = 0x00002000,
	     tmFe_TvSystemC256Qam = 0x00004000,
	     tmFe_TvSystemT8Vsb = 0x00008000,
	     tmFe_TvSystemT16Vsb = 0x00010000
	 } tmFe_TvSystem_t;*/


	return 0;
}
 FResult NativeInstaller::GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval)
{
          Nat32 tvsys=0;
	njni->GetTvSystem(&tvsys,retval);
	if(tvsys == TVSYS_BG )
	{
	   * TvSystem = tmFe_TvSystemBg ;
	}
	else if(tvsys == TVSYS_I )
	{
	 * TvSystem = tmFe_TvSystemI ;
	}
	else if(tvsys == TVSYS_DK )
	{
	* TvSystem = tmFe_TvSystemDk ;
	}
	else if(tvsys == TVSYS_L )
	{
	* TvSystem = tmFe_TvSystemL ;
	}
	else if(tvsys == TVSYS_NONE)
	{
	* TvSystem = tmFe_TvSystemNone ;
	}
	else if (tvsys == TVSYS_M)
	{
	*TvSystem = tmFe_TvSystemM;
	}
	else if (tvsys == TVSYS_BG_A2)
	{
	*TvSystem = tmFe_TvSystemBG_A2;
	}
	else if (tvsys == TVSYS_DK_A2)
	{
	*TvSystem = tmFe_TvSystemDK_A2;
	} 
	
	return 0;
}
 FResult NativeInstaller::SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval)
{
	if(TvSystem == tmFe_TvSystemBg )
	{
	   TvSystem = TVSYS_BG ;
	}
	else if(TvSystem == tmFe_TvSystemI )
	{
	   TvSystem = TVSYS_I ;
	}
	else if(TvSystem ==  tmFe_TvSystemDk)
	{
	  TvSystem = TVSYS_DK;
	}
	else if(TvSystem == tmFe_TvSystemL)
	{
	  TvSystem =  TVSYS_L ;
	}
	else if(TvSystem == tmFe_TvSystemBG_A2)
	{
	  TvSystem =  TVSYS_BG_A2;
	}
	else if(TvSystem == tmFe_TvSystemDK_A2)
	{
	  TvSystem =  TVSYS_DK_A2;
	}
	else {
		/* Tjhis is an overloaded function. TRUE: APMEA country. Search NTSC M
											FALSE : EUROPE country. Search PAL */
		TvSystem = ins->GetFrequencySearchDirection() ? TVSYS_M : (TVSYS_BG | TVSYS_I |  TVSYS_DK | TVSYS_BG_A2 | TVSYS_DK_A2);
	}

	njni->SetTvSystem(TvSystem,retval);
	return 0;
}

//FResult NativeInstaller::StartSearch(int winid,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval)

FResult NativeInstaller::StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval)
{
	 if (ScanStarted == 0) {
		 ScanStarted = 1;
		 njni->scanStart(startFreq,endFreq,true);
	 } else {
		 njni->scanNext();
	 }
	 *retval = 0;
	return 0;
}
 FResult NativeInstaller::StopSearch(int winid,Nat32 * retval)
{
	if (ScanStarted == 1)
	{
		njni->scanAbort();
		*retval = IPlfApiTuning_WaitforAbort;
		ScanStarted = 0;
	}
	else
	{
		*retval = IPlfApiTuning_SearchStopped;
	}
	return 0;
}
 


 FResult NativeInstaller::GetSymbolRateRange( int winid, Nat32* MinSymbolRate, Nat32* MaxSymbolRate, Nat32* retval )
 {
	 njni->getSymbolRateRange(MinSymbolRate,MaxSymbolRate);
	 return 0;
 }
 FResult NativeInstaller::SetSymbolRate( int srtmode, Nat32 rate, Nat32* retval )
 {
	 njni->setSymbolRate(srtmode,rate);
	 return 0;
 }
 FResult NativeInstaller::GetSymbolRate( int winid, Nat32* rate, Nat32* retval )
 {
	 njni->getSymbolRate(rate);
	 return 0;
 }
 FResult NativeInstaller::SetSearchRates( int winid, tmFe_SearchSymbolRate_t* SearchRate, Nat32 size, Nat32* retval )
 {
 	int i = 0;
	 return 0; //njni->setSearchRates(SearchRate,size);
 }

 FResult NativeInstaller::SetFreqStep( int winid, Nat32 step, Nat32* retval )
 {
	 njni->setScanStep(step);
	 return 0;
 }
 FResult NativeInstaller::GetFreqStep( int winid, Nat32* step, Nat32* retval )
 {
	 njni->getFreqStep(step);
	 return 0;
 }


 FResult NativeInstaller::SetChanBandwidth( int winid, tmFe_ChanBandwidth_t bandwidth, Nat32* retval )
 {
	 switch(bandwidth) {
	 case tmFe_ChanBandwidthAuto:
		 njni->setBandwidth((int)0);
		 break;
	 case tmFe_ChanBandwidth6MHz:
		 njni->setBandwidth((int)1);
		 break;
	 case tmFe_ChanBandwidth7MHz:
		 njni->setBandwidth((int)2);
		 break;
	 case tmFe_ChanBandwidth8MHz:
		 njni->setBandwidth((int)4);
		 break;
	 case tmFe_ChanBandwidth_6_7_8MHz:
		 njni->setBandwidth((int)7);
		 break;	 
	 }

	 return 0;

 }


 FResult NativeInstaller::GetActualChanBandwidth( int winid, tmFe_ChanBandwidth_t* Bandwidth, Nat32* retval )
 {
	 njni->getActualChanBandwidth((int*)Bandwidth);
	 return 0;
 }



 FResult NativeInstaller::SetStreamPriority( int winid, tmFe_StreamPriority_t streamPriority, Nat32* retval )
 {
	 njni->setStreamPriority((int)streamPriority);
	 return 0;
 }


 FResult NativeInstaller::GetStreamPriority( int winid, tmFe_StreamPriority_t* streamPriority, Nat32* retval )
 {
	 
	njni->getStreamPriority((int*)streamPriority);
	return 0;
 }

  FResult NativeInstaller::GetHierarchyMuxPresence( int winid,Bool * HierarchymodePresent,Nat32 * retval)
  {

	 njni->getHierarchyMode(HierarchymodePresent);
	 return 0;
  }


 FResult NativeInstaller::GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval)
 {
	 njni->getActualConstellation((int*)pConstellation);
	 return 0;
 }


 FResult NativeInstaller::SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval)
 {
	 njni->setConstellation(constellation);
	 return 0;
 }


 FResult NativeInstaller::GetBer(int winid,int decoder,Nat32 * Ber)
 {
	 njni->getBer(Ber);
	 return 0;
 }


 FResult NativeInstaller::GetCarrierPresent( int winid, Bool* Present, Nat32* retval )
 {
	 njni->getCarrierPresent(Present);
	 return 0;
 }

FResult NativeInstaller::GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval)
 {
	 njni->getSigStrengthRange(MinStrength,MaxStrength);
	 return 0;
 }
FResult NativeInstaller::Start(int winid,Bool * Avail,Nat32 * retval)
 {
	// njni->start(Avail);
	 *retval = 0;
	 return 0;
 }
FResult NativeInstaller::Stop(int winid,Bool * Stopped,Nat32 * retval)
 {
	// njni->stop(Stopped);
	 *retval = 0;
	 return 0;
 }
FResult NativeInstaller::GetMeasValid(int winid,Bool * Valid,Nat32 * retval)
 {
// njni->getMeasValid(Valid);
	 *Valid = 1;
	 return 0;
 }
FResult NativeInstaller::GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval)
 {

	 njni->getSigStrength(winid,Strength);
	 return 0;
 }

int NativeInstaller::SourceSetupApply(int Medium)
{
	int retval;

	 retval = njni->SourceSetupApply(Medium);
	 return retval;
}


FResult NativeInstaller::GetActivePlpId(int winid,int * plpid)
{

	 njni->GetActivePlpId(plpid);
	 return 0;
}

FResult NativeInstaller::GetT2CarrierPresent(int winid,Bool * Present)
{

	 njni->GetT2CarrierPresent(Present);
	 return 0;
}

FResult NativeInstaller::SelectPlpId(int winid,int plpid)
{
	 
	 njni->SelectPlpId(plpid);
	 
	 return 0;
}

FResult NativeInstaller::GetDetectedPlpIds(int winid,int * nrOfIds,int * plpids)
{

	 njni->GetDetectedPlpIds(nrOfIds,plpids);
	 
	 return 0;
}

void NativeInstaller::SetStreamPriority(int plpId)
{
	 ins->SetStreamPriority((HsvStreamPriority)plpId);
}
void NativeInstaller::OnOpSearchStatus(Op_ProfileSearchStatus opStatus)
{
	opinsN->OnOpSearchStatus(opStatus);
}
void NativeInstaller::OnOpStatusInfo(Op_ProfileStatusInfo statusInfo)
{
	opinsN->OnOpStatusInfo(statusInfo);
}
void NativeInstaller::OnOpNIT(Op_ProfileNitData nitData)
{
	opinsN->OnOpNIT(nitData);
}
void NativeInstaller::OnOpTune(Op_ProfileTuneData tuneData)
{
	opinsN->OnOpTune(tuneData);
}
void NativeInstaller::RequestStatusInfo(void)
{
	 njni->RequestStatusInfo();
}
void NativeInstaller::RequestNit(void)
{
	 njni->RequestNit();
}
void NativeInstaller::SendOperatorSearchStart(Op_Search_Settings searchstart)
{
	 njni->SendOperatorSearchStart(searchstart);
}
void NativeInstaller::SendOpExit(void)
{
	 njni->SendOpExit();
}
void NativeInstaller::SendOpTuneStatus(Op_Tune_Status tuneStatus)
{
	 njni->SendOpTuneStatus(tuneStatus);
}
void NativeInstaller::SendOpAck(void)
{
	 njni->SendOpAck();
}
void NativeInstaller::SendOpSearchCancel(void)
{
	 njni->SendOpSearchCancel();
}
void NativeInstaller::CacheOperatorData(void)
{
	 njni->CacheOperatorData();
}
void NativeInstaller::GetValuesFromGlobalSettings(int ID, int *Value)
{
	njni->getValueFromTVContentProvider(ID,Value);
}


void NativeInstaller::setDemuxHandle(long demuxHandle)
{
	if(tcins != NULL)
	{
		tcins->setDemuxInterface(demuxHandle);
	}
}
void NativeInstaller::setVbiHandle(long vbiHandle)
{
	if(tcins != NULL)
	{
		tcins->setVbiInterface(vbiHandle);
	}
}

int NativeInstaller::GetNumberOfChannelListIds()
{
	return ins->GetNumberOfChannelListIds();	

}
int NativeInstaller::GetChannelListIdByIndex(int index)
{
	return ins->GetChannelListIdByIndex(index);	
	
}

void NativeInstaller::SetFavouriteChannelListId(int mode, int attrib, int index)
{
	ins->SetFavouriteChannelListId(mode,attrib,index);
}


void NativeInstaller::GetChannelListIDName(int index, Nat16 *ChannelistName)
{
	ins->GetChannelListIDName(index,ChannelistName);
	
}

FResult NativeInstaller::GetTPSId( int winid, HsvDvbTParams* TPSId, Nat32* retval )
{
	njni->getTPSId(TPSId);
	return 0;
}



