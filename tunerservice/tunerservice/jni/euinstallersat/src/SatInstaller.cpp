/*
 * SatInstaller.cpp
 *
 *  Created on: Jun 12, 2013
 *      Author: mahesh.mathada
 */




#include "SatInstaller.h"

#ifdef AOSP_BUILD_SAT
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif


#include <stdio.h>



SatInstaller::SatInstaller(int tokenId,jobject javahan)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","Constructor %d",tokenId);

	plfdvbs = this;
	plftune = this;
	ssm = this;
	insN = this;
	globalsettings = this;
	opins = this;
	cipStatus = this;

	sins = new CS2Installer(tokenId);

	ins = sins->ins;
	dvbset = sins->dvbset;
	plfapidvbsN = sins->plfapidvbsN;
	sins->insN = insN;
	pow = sins->pow;
	sins->plfdvbs = plfdvbs;
	sins->plftune = plftune;
	sins->ssm = ssm;
	sins->insN = insN;
	sins->globalsettings = globalsettings;
	sins->opins = opins;
	opinsN		= sins->opinsN;
	cipStatusN      = sins->cipStatusN;
	sins->cipStatus = cipStatus;
	
	njni = new SatInstallerJNI();

	pow->TurnOn();

}

//IHsvSatelliteInstallation
int SatInstaller::GetCurrentInstallationState(int * mode,int * state)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetCurrentInstallationState");
	ins->GetCurrentInstallationState(mode,state);
	return 0;
}
FResult SatInstaller::StartInstallation(int source,int Lnb,int mode)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StartInstallation");
	ins->StartInstallation(source,Lnb,mode);
	return 0;
}
FResult SatInstaller::StopInstallation(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StopInstallation");
	ins->StopInstallation();
	return 0;
}
void SatInstaller::ResetInstallation(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","ResetInstallation");
	ins->ResetInstallation();	
}
int SatInstaller::GetNumberOfTvChannelsFound(int Lnb)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfTvChannelsFound");
	return ins->GetNumberOfTvChannelsFound(Lnb);	
}
int SatInstaller::GetNumberofRadioChannelsFound(int Lnb)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberofRadioChannelsFound");
	return ins->GetNumberofRadioChannelsFound(Lnb);	
}
int SatInstaller::GetNumberOfTvChannelsRemoved(int Lnb)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfTvChannelsRemoved");
	return ins->GetNumberOfTvChannelsRemoved(Lnb);	
}
int SatInstaller::GetNumberofRadioChannelsRemoved(int Lnb)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberofRadioChannelsRemoved");
	return ins->GetNumberofRadioChannelsRemoved(Lnb);
}
FResult SatInstaller::GetSatelliteName(int Lnb,Nat16* SatelliteName)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSatelliteName");
	return ins->GetSatelliteName(Lnb,SatelliteName);
}
int SatInstaller::GetNumberOfDigitalChannelsAdded(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfDigitalChannelsAdded");
	return ins->GetNumberOfDigitalChannelsAdded();
}
int SatInstaller::GetNumberOfDigitalChannelsRemoved(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfDigitalChannelsRemoved");
	return ins->GetNumberOfDigitalChannelsRemoved();
}
int SatInstaller::GetNumberOfDigitalChannelsMoved(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfDigitalChannelsMoved");
	return ins->GetNumberOfDigitalChannelsMoved();
}
FResult SatInstaller::IdentifyPackagesAvailable(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","IdentifyPackagesAvailable");
	return ins->IdentifyPackagesAvailable();
}
int SatInstaller::GetTotalNumberOfPackagesFound(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetTotalNumberOfPackagesFound");
	return ins->GetTotalNumberOfPackagesFound();
}	
FResult SatInstaller::GetPackageByIndex(int Index,HsvPackageStructure * Package)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetPackageByIndex");
	ins->GetPackageByIndex(Index,Package);
	return 0;
}
FResult SatInstaller::SetUserPackageIndex(Nat32 PackageIndex)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SetUserPackageIndex");
	ins->SetUserPackageIndex(PackageIndex);
	return 0;
}
FResult SatInstaller::GetUserPackageIndex(Nat32 * PackageIndex,Bool * IsPackage)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetUserPackageIndex");
	ins->GetUserPackageIndex(PackageIndex,IsPackage);
	return 0;
}
FResult SatInstaller::GetInstalledSatellites(int mode,HsvInstalledSatellites * SatelliteEntries)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetInstalledSatellites");
	ins->GetInstalledSatellites(mode,SatelliteEntries);
	return 0;
}	
FResult  SatInstaller::InstallAddedSatellites(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","InstallAddedSatellites");
	ins->InstallAddedSatellites();
	return 0;
}
FResult SatInstaller::ResetAddedSatellites(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","ResetAddedSatellites");
	ins->ResetAddedSatellites();
	return 0;
}
FResult SatInstaller::RemoveSatelliteEntry(int LnbNumber)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","RemoveSatelliteEntry");
	ins->RemoveSatelliteEntry(LnbNumber);
	return 0;
}
int SatInstaller::GetSatelliteSignalStrength(int LnbNumber)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSatelliteSignalStrength");
	return ins->GetSatelliteSignalStrength(LnbNumber);
}
int SatInstaller::GetSatelliteSignalQuality(int LnbNumber)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSatelliteSignalQuality");
	return ins->GetSatelliteSignalQuality(LnbNumber);
}
FResult SatInstaller::LoadManualInstallationDefaultValues(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","LoadManualInstallationDefaultValues");
	ins->LoadManualInstallationDefaultValues();
	return 0;
}
FResult SatInstaller::StoreManualInstallationValues(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StoreManualInstallationValues");
	ins->StoreManualInstallationValues();
	return 0;
}
Nat32 SatInstaller::GetAttribute(int Mode,int AttributeId)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetAttribute");
	return ins->GetAttribute(Mode,AttributeId);
}
FResult SatInstaller::SetAttribute(int Mode,int AttributeId,Nat32 Value)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SetAttribute");
	ins->SetAttribute(Mode,AttributeId,Value);
	return 0;
}
int SatInstaller::GetScanProgressStatus(int Mode)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetScanProgressStatus");
	return ins->GetScanProgressStatus(Mode);
}
FResult SatInstaller::GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSITableIds");
	return ins->GetSITableIds(NetworkID,BouquetID);
}
FResult SatInstaller::GetPackageName(Nat32 PackageId,Nat16 * PackageName)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetPackageName");
	return ins->GetPackageName(PackageId,PackageName);
}
void SatInstaller::GetSIDetails(HsvSDMSIDataValues * SiValues)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSIDetails");
	ins->GetSIDetails(SiValues);
}
void SatInstaller::EnableUnicable(int LnbNumber,Bool Enable)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","EnableUnicable");
	ins->EnableUnicable(LnbNumber,Enable);	
}	
void SatInstaller::StopSignalStrengthMeas(int LnbNumber)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StopSignalStrengthMeas");
	ins->StopSignalStrengthMeas(LnbNumber);
}
int SatInstaller::GetSignalQuality(Nat32 Param)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSignalQuality");
	return ins->GetSignalQuality(Param);
}
void SatInstaller::StartSignalStrengthMeas(int LnbNumber)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StartSignalStrengthMeas");
	 ins->StartSignalStrengthMeas(LnbNumber);
}
int SatInstaller::GetSignalStrength(Nat32 param)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSignalStrength");
	 return ins->GetSignalStrength(param);
}

FResult SatInstaller::StartPredefinedListCopy(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","StartPredefinedListCopy");
	ins->StartPredefinedListCopy();
	return 0;
}

int SatInstaller::GetFirstInstalledChannel()
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetFirstInstalledChannel");
	return	ins->GetFirstInstalledChannel();
}


int SatInstaller::onScanningStandardDetected(int std, int freq)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","onScanningStandardDetected");
	plfapidvbsN->onScanningStandardDetected(std, freq);
	return 0;
}

int SatInstaller::onScanAborted(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","onScanAborted");
	plfapidvbsN->onScanAborted();
	return 0;
}

int SatInstaller::onScanEnded(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","onScanEnded");
	plfapidvbsN->onScanEnded();
	return 0;
}

int SatInstaller::onTuned(int tuningresult, int freq)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","onTuned");
	plfapidvbsN->onTuned(tuningresult,freq);
	return 0;
}

//IHsvSatelliteInstallationNotify
void SatInstaller::OnEvent(int eventid,int value)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnEvent [eventid %d]", eventid);
	njni->onEvent(eventid,value);
}



int SatInstaller::getParams(HsvDvbSParams * par)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","getParams\n");
	njni->getParams(par);
	return 0;
}

int SatInstaller::configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","configureLNB \n");
	njni->configureLNB(lnbcfg, customlnbcfg);
	return 0;
}

int SatInstaller::configureUnicable(HsvDvbSUnicableConfig uccfg)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","configureUnicable \n");
	njni->configureUnicable(uccfg);
	return 0;
}

int SatInstaller::setPolarization(int polarization)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setPolarization\n");
	njni->setPolarization(polarization);
	return 0;
}

int SatInstaller::setSymbolRate(int srdetectmode,int symbolrate)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setSymbolRate \n");
	njni->setSymbolRate(srdetectmode,symbolrate);
	return 0;
}

int SatInstaller::setPLP(Nat8 plpid)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setPLP \n");
	njni->setPLP(plpid);
	return 0;
}

int SatInstaller::setBand(int band)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setBand \n");
	njni->setBand(band);
	return 0;
}

int SatInstaller::setLNBConnectionType(int connectiontype)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setLNBConnectionType \n");
	njni->setLNBConnectionType(connectiontype);
	return 0;
}

int SatInstaller::setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setSatIPParams \n");
	njni->setSatIPParams(modsys,modtype,RollOff,fec,pilots);
	return 0;
}



//IPlfApiTuning
int SatInstaller::tune(int freq,Bool finetune)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","tune \n");
	njni->tune(freq,finetune);
	return 0;
}

int SatInstaller::getFreq(int * freq)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","getFreq \n");
	njni->getFreq(freq);
	return 0;
}

int SatInstaller::scanStart(int startfreq,int endfreq,Bool scanforward)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","scanStart \n");
	njni->scanStart(startfreq,endfreq,scanforward);
	return 0;
}

int SatInstaller::scanAbort(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","scanAbort \n");
	njni->scanAbort();
	return 0;
}

int SatInstaller::scanNext(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","scanNext \n");
	njni->scanNext();
	return 0;
}



// IPlfApiSigStrengthMeas
FResult SatInstaller::GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSigStrengthRange \n");
	njni->getSigStrengthRange(MinStrength,MaxStrength);
	*retval = 0;
	return 0;
}
FResult SatInstaller::Start(int winid,Bool * Avail,Nat32 * retval)
{
	*retval = 0;
	return 0;
}
FResult SatInstaller::Stop(int winid,Bool * Stopped,Nat32 * retval)
{
	 *retval = 0;
	return 0;
}
FResult SatInstaller::GetMeasValid(int winid,Bool * Valid,Nat32 * retval)
{
	*Valid = 1;
	return 0;
}
FResult SatInstaller::GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval)
{
	 //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetSigStrength \n");
	njni->getSigStrength(Strength);
	return 0;
}

// IHsvSatelliteSettings

void SatInstaller::LoadLnbParametersFromPersistent(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","LoadLnbParametersFromPersistent \n");
	dvbset->LoadLnbParametersFromPersistent();
}
FResult SatInstaller::GetLnbSettings(HsvLnbSettings * LnbSettings)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetLnbSettings \n");

	dvbset->GetLnbSettings(LnbSettings);

	return 0;
}
FResult SatInstaller::SetLnbSettings(HsvLnbSettings * LnbSettings)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SetLnbSettings \n");
	dvbset->SetLnbSettings(LnbSettings);

	return 0;
}
FResult SatInstaller::ResetLnbSettings(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","ResetLnbSettings \n");
	dvbset->ResetLnbSettings();
	
	return 0;
}
FResult SatInstaller::GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetDefaultValues \n");
	dvbset->GetDefaultValues(LnbSettingsEntry);
	return 0;
}
FResult SatInstaller::ResetToDefaultLnbSettings(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","ResetToDefaultLnbSettings \n");
	dvbset->ResetToDefaultLnbSettings();
	return 0;
}
Nat32 SatInstaller::GetAttribute(int AttributeId)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetAttribute \n");

	return 0;
}
FResult SatInstaller::SetAttribute(int AttributeId,Nat32 Value)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SetAttribute \n");

	return 0;
}
void SatInstaller::SaveSatelliteSettingsToPersistent(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SaveSatelliteSettingsToPersistent \n");
	dvbset->SaveSatelliteSettingsToPersistent();
}
FResult SatInstaller::CommitSatelliteSettingsToPersistent(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","CommitSatelliteSettingsToPersistent \n");
	dvbset->CommitSatelliteSettingsToPersistent();
	return 0;
}
void SatInstaller::ReLoadLnbParametersFromPersistent(void)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","ReLoadLnbParametersFromPersistent \n");
	dvbset->ReLoadLnbParametersFromPersistent();
}

void SatInstaller::UpdateConfigXmlStrings(char* prescanXml,int prescansize,char* satelliteXml, int satelliteSize)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","UpdateConfigXmlStrings \n");

	ins->UpdateConfigXmlStrings(prescanXml,prescansize,satelliteXml,satelliteSize);
}

void SatInstaller::assetManager_init(AAssetManager* mgr)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","assetManager_init \n");

	ins->SetAttribute(1,IHsvSatelliteInstallation_AttributeAssetManager,(int)mgr);
}

//ICesOperatorProfileNotify
void SatInstaller::OnOpSearchStatus(Op_ProfileSearchStatus opStatus)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnOpSearchStatus \n");
    opinsN->OnOpSearchStatus(opStatus);
}

void SatInstaller::OnOpStatusInfo(Op_ProfileStatusInfo statusInfo)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnOpStatusInfo \n");
    opinsN->OnOpStatusInfo(statusInfo);
}

void SatInstaller::OnOpNIT(Op_ProfileNitData nitData)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnOpNIT \n");
    opinsN->OnOpNIT(nitData);
}

void SatInstaller::OnOpTune(Op_ProfileTuneData tuneData)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnOpTune \n");
    opinsN->OnOpTune(tuneData);
}

//ICesOperatorProfile
void SatInstaller::RequestStatusInfo(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","RequestStatusInfo \n");
     njni->RequestStatusInfo();
}

void SatInstaller::RequestNit(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","RequestNit \n");
     njni->RequestNit();
}

void SatInstaller::SendOperatorSearchStart(Op_Search_Settings searchstart)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SendOperatorSearchStart \n");
     njni->SendOperatorSearchStart(searchstart);
}

void SatInstaller::SendOpExit(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SendOpExit \n");
     njni->SendOpExit();
}

void SatInstaller::SendOpTuneStatus(Op_Tune_Status tuneStatus)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SendOpTuneStatus \n");
     njni->SendOpTuneStatus(tuneStatus);
}

void SatInstaller::SendOpAck(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SendOpAck \n");
     njni->SendOpAck();
}

void SatInstaller::SendOpSearchCancel(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SendOpSearchCancel \n");
     njni->SendOpSearchCancel();
}

void SatInstaller::CacheOperatorData(void)
{
     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","CacheOperatorData \n");
     njni->CacheOperatorData();
}

Op_ProfileStatusInfo SatInstaller::GetStoredOperatorData(void)
{
    Op_ProfileStatusInfo statusInfo;

     //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetStoredOperatorData \n");
     statusInfo = njni->GetStoredOperatorData();

     return statusInfo;
}

void SatInstaller::setPostCode(int pCodeLen ,char *pCode)
{
	
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setPostCode \n");
	ins->SetPostcode((Nat8)pCodeLen,(Nat8 *)pCode);
}

void SatInstaller::GetValuesFromGlobalSettings(int ID, int *Value)
{
	//__android_log_print(ANDROID_LOG_DEBUG,"SatInstaller","GetValuesFromGlobalSettings\n");
	njni->GetValuesFromGlobalSettings (ID, Value);
}

//ICesCipCAMStatusNotify
void SatInstaller::OnEvent (CIPlusStatus_e status)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","OnCAMStatusChanged \n");
    cipStatusN->OnEvent(status);
}

//ICesCipCAMStatus
void SatInstaller::GetCipStatus (Nat8 *status)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetCipStatus \n");
    njni->GetCipStatus (status);
}

void SatInstaller:: StartTricolorRegionParsing ()

{
		//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","startTricolorRegionParsing \n");
		ins->StartTricolorRegionParsing ();
}

void SatInstaller:: SetTricolorRegionIndex(int indx)
{
		//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SetTricolorRegionIndex \n");
		ins->SetTricolorRegionIndex (indx);
}

void SatInstaller:: GetTricolorRegionNames (Nat16 **regionNames, int *len)
{
		//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetTricolorRegionNames \n");
		ins->GetTricolorRegionNames (regionNames, len);
}

	/*** TVPROVIDER IMPLEMENTATION START ***/
int SatInstaller::GetNumberOfDatabaseRecords(int TSDataOnly)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetNumberOfDatabaseRecords");
	return ins->GetNumberOfDatabaseRecords(TSDataOnly);
}

void SatInstaller::GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData,int TSDataOnly)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","GetTvProviderBlobDataByIndex");
	ins->GetTvProviderBlobDataByIndex(Index,TvProviderBlobData,InstallerPrivateBlobData,TSDataOnly);
	return;
}

void SatInstaller::AddTvpData(HsvPgdatTvProviderBlobData* TvpData, int Clear)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","AddTvpData");
	ins->AddTvpData(TvpData,Clear);
	return; 
}

void SatInstaller::SyncUniqueIdToMW (HsvPgdatTvProviderBlobData* TvpData)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","SyncUniqueIdToMW");
	ins->SyncUniqueIdToMW(TvpData);
	return; 
}

	/*** TVPROVIDER IMPLEMENTATION END ***/

void SatInstaller::setDemuxHandle(long demuxHandle)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "SatInstaller","setDemuxHandle");
	if(sins != NULL) {
		sins->setDemuxHandleInterface(demuxHandle);
	}
	
}
