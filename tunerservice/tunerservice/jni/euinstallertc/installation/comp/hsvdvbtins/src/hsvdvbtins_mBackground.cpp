#include "_hsvdvbtins_mBackground.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mBackground")

/* Macros */

Pump CHsvDvbTInstallation_mBackground_Priv::s__mPump;

Bool CHsvDvbTInstallation_mBackground_Priv::s__mActive,CHsvDvbTInstallation_mBackground_Priv::s__mAcquistionInProgress;

int CHsvDvbTInstallation_mBackground_Priv::s__mCurrentSessionCookie;
Bool CHsvDvbTInstallation_mBackground_Priv::s__mPresetChanged,CHsvDvbTInstallation_mBackground_Priv::s__mLowestPreset;
Nat16 CHsvDvbTInstallation_mBackground_Priv:: s__OnIdCached= 0xFFFF;
Nat16 CHsvDvbTInstallation_mBackground_Priv:: s__SrvIdCached= 0xFFFF;
Nat16 CHsvDvbTInstallation_mBackground_Priv:: s__TsIdCached= 0xFFFF;
Nat32 CHsvDvbTInstallation_mBackground_Priv:: s__FrequencyCached = 0;
Nat32 CHsvDvbTInstallation_mBackground_Priv:: s__StreamPriorityCached =0;
Nat16 CHsvDvbTInstallation_mBackground_Priv:: s_PresetNumberCached= 0xFFFF;
/* static functions */


Bool CHsvDvbTInstallation_mBackground_Priv::mIsSdtVersionUpdate(void)
{
	Bool	VersionUpdated = FALSE;
	HsvPgdatDigTSData tsdata;
	HsvChannel Channel;
	HsvSource  Src;
	HsvPgdatPresetData	PresetData;
	int		retval = 0;
	int 	CurrentSDTVersion=0;
	
	pgsel_GetActualCurrentProgram(HsvMain,&Src, &Channel);
	PresetData.PresetNumber = Channel.Channel.Digit;
	if (pgdb_GetByKey(PRESET_TABLE, &PresetData) == TRUE)
	{
		tsdata.Frequency = PresetData.Frequency;
		tsdata.StreamPriority = PresetData.StreamPriority;
		if(pgdb_GetByKey( PTC_TABLE, (Address )&tsdata) == TRUE)
		{
			CurrentSDTVersion = tsdata.SDTVersion;
			if ((strapi_GetByKey(HsvMain, HSVSPID(ActualTsVersionNo, dvb, sdt), 0, 0, 0, &retval) == TRUE)
				 && (retval != 0xFF) // to handle scenario - use case selection happened and strapi got flushed out
				)
			{
			  TraceDebug (m, "Background: CurrentSDTVerion %d Version in Database %d ", CurrentSDTVersion,retval);
			  VersionUpdated = (CurrentSDTVersion != retval) ? TRUE: FALSE;
            }			
		}
		else
		{
			TraceNotice(m,"Background: No matching TS Table entry for Freq %d StreamPrio %d ", tsdata.Frequency, tsdata.StreamPriority);
		}
	}
	else
	{
		TraceNotice (m, "Background: No Preset found for %d ", PresetData.PresetNumber);
	}
	
	TraceNotice (m, "Background: mIsSdtVersionUpdate %d ", VersionUpdated);
	
	return VersionUpdated;
}

Bool CHsvDvbTInstallation_mBackground_Priv::mIsMenuLanguageChanged(HsvPgdatDigTSData *tsdata, int *preset)
{
	Bool	LangChanged = FALSE;
	HsvChannel Channel;
	HsvSource  Src;
	HsvPgdatPresetData	PresetData;
	int		retval = 0;
	
	pgsel_GetActualCurrentProgram(HsvMain,&Src, &Channel);
	PresetData.PresetNumber = Channel.Channel.Digit;
	*preset = Channel.Channel.Digit;
	if (pgdb_GetByKey(PRESET_TABLE, &PresetData) == TRUE)
	{
		tsdata->Frequency = PresetData.Frequency;
		tsdata->StreamPriority = PresetData.StreamPriority;
		if(pgdb_GetByKey( PTC_TABLE, (Address )tsdata) == TRUE)
		{
			TraceDebug (m, "Background: CurrentMenuLang %d language in Database %d ", sysset_GetSystemLanguage(),tsdata->LanguageCode);
			if(sysset_GetSystemLanguage() != tsdata->LanguageCode)
			{
			  TraceDebug (m, "Background: MenuLanguage Changed CurrentMenuLang %d language in Database %d ", sysset_GetSystemLanguage(),tsdata->LanguageCode);
			  LangChanged = TRUE;
			}
		}
		else
		{
			TraceNotice(m,"Background: No matching TS Table entry for Freq %d StreamPrio %d ", tsdata->Frequency, tsdata->StreamPriority);
		}
	}
	else
	{
		TraceNotice (m, "Background: No Preset found for %d ", PresetData.PresetNumber);
	}
	
	TraceNotice (m, "Background: LangChanged %d ", LangChanged);
	
	return LangChanged;
}

Bool CHsvDvbTInstallation_mBackground_Priv::mIsNitVersionUpdate(void)
{
    HsvPgdatDigTSData tsdata;
	HsvSource  Src;
    HsvChannel Channel;
	Nat8 CurrentNITVersion = 0;
	Nat32 CurrentFreq = 0;	
	HsvChannel channel;
	Bool NitVersionUpdated=FALSE;	
    Nat8 retval = -1;
	HsvPgdatPresetData	PresetData;
	pgsel_GetActualCurrentProgram(HsvMain,&Src, &Channel);
	PresetData.PresetNumber = Channel.Channel.Digit;
	memset((Address)&tsdata, 0, sizeof(HsvPgdatDigTSData));
	tsdata.NITVersion=-1;
	if(eurdiv_IsApmeaNetworkUpdateCountry()==TRUE || sysset_GetSystemCountry()==cids_CountryHungary)
	{
		if (pgdb_GetByKey(PRESET_TABLE, &PresetData) == TRUE)
		{ 
			CurrentFreq = PresetData.Frequency;
			OnId = PresetData.OriginalNetworkId;
			SrvId = PresetData.ServiceId;
			TsId = PresetData.Tsid;
			TraceNotice (m,"Frequency %d ", CurrentFreq);
		}
		if(strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (Address)(&CurrentNITVersion))==TRUE)
		{
			tsdata.Frequency = CurrentFreq;		
			tsdata.StreamPriority =PresetData.StreamPriority;
			if(pgdb_GetByKey( PTC_TABLE, (Address )&tsdata) == TRUE)
			{
				if((CurrentNITVersion != tsdata.NITVersion)&&(CurrentNITVersion!=INVALID_NIT_VERSION))
				{
					TraceDebug(m,"NIT version changes");
					NitVersionUpdated=TRUE;				
					TraceDebug(m,"%s %d CurrentFreq %lu CurrentNITVersion %d tsdata.NITVersion %d", __FUNCTION__, __LINE__, CurrentFreq, CurrentNITVersion,tsdata.NITVersion);
					tsdata.NITVersion=CurrentNITVersion;
					pgdb_Update(PTC_TABLE,&tsdata);
				}
			}
			else
			{
			TraceNotice (m, "TSData query failed for Frequency %d", CurrentFreq);
			}
		}	
	}	
  return NitVersionUpdated;
}

Bool CHsvDvbTInstallation_mBackground_Priv::mCachedServiceDetail()
{
	HsvSource  Src;
	HsvPgdatPresetData	PresetData;
	HsvChannel Channel;
	Bool cachedcomplete=FALSE;
	pgsel_GetActualCurrentProgram(HsvMain,&Src, &Channel);
	PresetData.PresetNumber = Channel.Channel.Digit;
	
	/*We are checking NIT actual version only*/
	if (pgdb_GetByKey(PRESET_TABLE, &PresetData) == TRUE)
	{ 
		OnIdCached= PresetData.OriginalNetworkId;
		SrvIdCached= PresetData.ServiceId;
		TsIdCached= PresetData.Tsid;
		PresetNumberCached=PresetData.PresetNumber;
		FrequencyCached = PresetData.Frequency;
		StreamPriorityCached = PresetData.StreamPriority;
		TraceNotice (m,"Current Channel Frequency %d PresetNbr %d ", PresetData.Frequency, PresetData.PresetNumber);
		cachedcomplete=TRUE;
	}

	return cachedcomplete;
}
void CHsvDvbTInstallation_mBackground_Priv::mTunedLowestPreset()
{
	HsvPgdatDigServiceData  svcdat_temp;
	int from = -1, to = -1,srvindex = -1;
	HsvPgdatPresetData	PresetData,temp_PresetData;
	int presetNumber = 0;	
	Bool	mLowestPreset = FALSE, mPresetChanged = FALSE;

	
	TraceDebug(m,"ONID:SID:TSID:Preset=[%d],[%d],[%d],[%d] ",OnIdCached,SrvIdCached,TsIdCached,PresetNumberCached);
	svcdat_temp.OriginalNetworkId = OnIdCached;
	svcdat_temp.ServiceId = SrvIdCached;
	if(pgdb_GetRange(SERVICE_TABLE,2,(Address)&svcdat_temp,&from,&to)) 
	{
		ASSERT(from<=to);
		for (srvindex = from; srvindex <= to ; srvindex++)
		{
			if(pgdb_GetByIndex(SERVICE_TABLE, srvindex, (Address)&svcdat_temp)) 
			{
				if((svcdat_temp.Tsid == TsIdCached) && (svcdat_temp.Frequency == FrequencyCached) && (svcdat_temp.StreamPriority == StreamPriorityCached))
				{
					TraceDebug(m,"%s %d PresetNumber in Service table=[%d] ", __FUNCTION__, __LINE__,svcdat_temp.PresetNumber);								
					temp_PresetData.PresetNumber = svcdat_temp.PresetNumber;
					if (pgdb_GetByKey(PRESET_TABLE, &temp_PresetData) == TRUE)
					{
						TraceDebug(m,"%s%d PresetNumber in Preset table=[%d] ", __FUNCTION__, __LINE__,temp_PresetData.PresetNumber);
						if(temp_PresetData.PresetNumber != PresetNumberCached) 
						{
							presetNumber = temp_PresetData.PresetNumber;
							mPresetChanged = TRUE;
						} 
					}
					else 
					{
					TraceNotice (m, "Strange!! Preset got changed in Service Table. But doesn't exist in PresetTable. ");
					}
					break;	
				}
			}
		}
		if(srvindex > to) 
		{
			mLowestPreset = TRUE;
		}
	} 
	else 
	{
		mLowestPreset = TRUE;
	}
	TraceDebug(m,"%s %d mLowestPreset=[%d] ", __FUNCTION__, __LINE__,mLowestPreset);

	if(mLowestPreset) 
	{
		int NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
		while(NoOfRecords > 0)
		{
			if(pgdb_GetByIndex(PRESET_TABLE, (NoOfRecords-1), (Address)&PresetData))
			{
				if((mCheckVisibleService(&PresetData)))
				{
					TraceNotice (m, "Lowest Visible Preset found at %d ", PresetData.PresetNumber);
					break;
				}
			}
			else
			{
				TraceErr(m, "pgdb_GetByIndex failed");
			}
			NoOfRecords--;
		}
		TraceDebug(m,"NoOfRecords=[%d]",NoOfRecords);
		if(NoOfRecords > 0)
		{
			presetNumber = PresetData.PresetNumber;
		}
		else
		{
			TraceNotice(m, "No Visible Service found");
		}
		mLowestPreset = FALSE;
		mPresetChanged = TRUE;
	}
	TraceNotice(m ,"%s %d mPresetChanged[%d] presetNumber[%d] ",__FUNCTION__,__LINE__,mPresetChanged,presetNumber);
	if(mPresetChanged == TRUE) 
	{
		installN_OnEvent(installN_EventNewPresetNumber,presetNumber);
		mPresetChanged = FALSE;
	}

}

Bool CHsvDvbTInstallation_mBackground_Priv::mCheckVisibleService(HsvPgdatPresetData* preset)
{
	HsvPgdatDigServiceData data;
	Bool retval = FALSE;
	ASSIGN_DIGSVC_KEYS(&data, preset);
	if(pgdb_GetByKey((pgdb_GetCurrentTable() | pgdbconst_DigitalService), (Address)&data))
	{               
		retval = (eurdiv_IsDbookCountry() == TRUE) ?  (!data.SystemHidden) : data.VisibleService;
	}
	else
	{
		TraceErr(m, "pgdb_GetByKey failed");
	}
    return retval;
}

void CHsvDvbTInstallation_mBackground_Priv::PumpHandler(int event, Nat32 param)
{
    Nat32 OwnedResource = plfres_GetOwnedResources();
	Bool 	CachingDone = FALSE;
	Bool NitVersionUpdated=FALSE;
	Bool	TuneToLowestPresetNeeded = FALSE;
	HsvPgdatDigTSData tsdata;
	Bool UpdateDone = false;
	int preset = -1;
    UNUSED(param);
	TraceDebug(m,"+event=[%d]",event);
    TraceDebug(m,"%s %d OwnedResource %ld mAcquistionInProgress %d CurSectionCookie %d RequestCameForCookie %d ",__FUNCTION__,  __LINE__, OwnedResource, mAcquistionInProgress, mCurrentSessionCookie, param);
	if( (event == EvDataAvaiable) && (mAcquistionInProgress == FALSE) && (TRUE == mActive) && BACKGROUND_INSTALL && (mCurrentSessionCookie == param))
	{
		NitVersionUpdated=mIsNitVersionUpdate();
		if(mCachedServiceDetail()==TRUE)
		{
			CachingDone = TRUE;
		}
		if (mIsSdtVersionUpdate() == TRUE)
		{
			TraceDebug(m,"@ %d event %s - %s", __LINE__, "EvDataAvaiable", "Handled");
			FuncDataAvailable();
			TuneToLowestPresetNeeded = TRUE;
		}
		else if((eurdiv_MultiLingSupported()) && mIsMenuLanguageChanged(&tsdata, &preset))
		{
			mAcquistionInProgress=TRUE;
			if (UpdateServiceNames(&tsdata) == TRUE)
			{
				TraceDebug(m,"ServiceNames Updated");
				installN_OnEvent(installN_EventInstallationStarted, CURRENT_MODE);
				installN_OnEvent(installN_EventInstallationCompleted, CURRENT_MODE);
			}
			else
			{
				//Send Event to sync TStable with current menu language
				TraceDebug(m,"Sending EventLanguageUpdate to sync TS Table with current Menu language ");
				installN_OnEvent(installN_EventLanguageUpdate, preset);
			}			
			
			mAcquistionInProgress=FALSE;
		}

		if(NitVersionUpdated==TRUE)
		{
			mAcquistionInProgress=TRUE;
			if(eurdiv_IsApmeaNetworkUpdateCountry()==TRUE)
			{
				installN_OnEvent(installN_EventNetworkUpdateDetected, CURRENT_MODE);
				TraceDebug(m,"Network update detected");
			}
			if(eurdiv_UpdateLCNOnFly()==TRUE)
			{
				TuneToLowestPresetNeeded = TRUE;
				installN_OnEvent(installN_EventInstallationStarted, CURRENT_MODE);
				mUpdateLCN();
				installN_OnEvent(installN_EventInstallationCompleted, CURRENT_MODE);
			}
			mAcquistionInProgress = FALSE;
		}

		if(UpdateChannelName(&preset))
		{
			installN_OnEvent(installN_EventChannelNameUpdated, preset);
			mAcquistionInProgress = FALSE;
		}

		if ((CachingDone) && (TuneToLowestPresetNeeded == TRUE))
		{
			mTunedLowestPreset();
		}
	}
	else
	{
		TraceDebug(m,"Background installation. Ignored as SDT Actual Version remains same ");
	}
}
void CHsvDvbTInstallation_mBackground_Priv::mUpdateLCN()
{
	int NoSrvRecord=pgdb_GetNoRecords(SERVICE_TABLE);
	int index=-1;	
	HsvPgdatDigServiceData svcdat;		
	HsvPgdatPresetData presetdat;
	HSVSPTYPE(ActualNetworkLCN, dvb, nit) lcnv1;
	/*Update LCNs and Delete Preset entries for the services with LCN updates*/
	for(index=0;index<NoSrvRecord;index++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE,index,(Address)&svcdat)==TRUE)
		{
			if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkLCN, dvb, nit), svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,(Address)&lcnv1) == TRUE)
		    {	        	
		    	TraceDebug(m,"svcdat.LCN=[%d]",svcdat.LCN);
				TraceDebug(m,"Update LCN For ONID:SID:TSID=[%d],[%d],[%d] with LCN=[%d]",lcnv1.Original_NetworkId,lcnv1.Tsid,lcnv1.ServiceId,lcnv1.LogicalChannelNum); 
				if( (VALID_LCN_RANGE(svcdat.LCN) || VALID_LCN_RANGE(lcnv1.LogicalChannelNum)) &&		
					((lcnv1.LogicalChannelNum!= svcdat.LCN) ||(svcdat.VisibleService!=lcnv1.VisibleService)))				
					{					
						TraceNotice(m,"%s %d deleted preset becoz => psvcdat->LCN %d svcdat.LCN %d svcdat.PresetNumber %d", __FUNCTION__, __LINE__, svcdat.LCN, svcdat.LCN, svcdat.PresetNumber);	
						presetdat.PresetNumber =   svcdat.PresetNumber;		
						presetdat.Type         =   HsvOnePart;						
						pgdb_Delete(PRESET_TABLE,(Address)&presetdat);				
						svcdat.PresetNumber = INVALID_PRESET;
						svcdat.LCN=lcnv1.LogicalChannelNum;
						svcdat.VisibleService=lcnv1.VisibleService;
						pgdb_Update(SERVICE_TABLE,&svcdat);					
						TraceDebug(m,"LCN Updated");
					}
				}
		}
	}

	/*Sort services with LCN updates*/	
	for(index=0;index<NoSrvRecord;index++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE,index,(Address)&svcdat)==TRUE)
		{
			if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkLCN, dvb, nit), svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,(Address)&lcnv1) == TRUE)
		    {	        	
				if(svcdat.PresetNumber == INVALID_PRESET){
					TraceDebug(m,"LCN UPDATED For ONID:SID:TSID=[%d],[%d],[%d] with LCN=[%d]",lcnv1.Original_NetworkId,lcnv1.Tsid,lcnv1.ServiceId,lcnv1.LogicalChannelNum); 
					sort_AddDigitalPreset(&svcdat);
				}
			}
		}
	}
}

void CHsvDvbTInstallation_mBackground_Priv::mCopyString(Nat16 *dest, Nat16 *src, int maxchars)
{
    int i = 0;
    for (i = 0 ; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }   
    *dest = 0;
}


Bool CHsvDvbTInstallation_mBackground_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}



Bool CHsvDvbTInstallation_mBackground_Priv::GetSvcNameWithCurrentLanguage(HsvPgdatDigServiceData *psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	int from = 0, to = 0;
	Bool  retval = false;
	HsvSDTMultiLingSvcName MultiLingName;
	if(strapi_GetRangeByKey(HsvMain,HSVSPID(MultiLingSvcName, dvb, sdt),3,psvcdat->OriginalNetworkId,psvcdat->Tsid,psvcdat->ServiceId,&from,&to))
	{
		TraceDebug(m,"No. of MultiLing Descriptors present : %d", ((to - from) + 1));
		for(int i = from; i <= to; i++)
		{
			TraceNotice(m,"sysset_GetSystemLanguage() %d, MultiLingName.LangCode: %d",sysset_GetSystemLanguage(),MultiLingName.LangCode);
			if(strapi_GetByIndex(HsvMain,HSVSPID(MultiLingSvcName, dvb, sdt),i,(Address)&MultiLingName))
			{
				TraceNotice(m,"sysset_GetSystemLanguage() %d, MultiLingName.LangCode: %d",sysset_GetSystemLanguage(),MultiLingName.LangCode);
				if(sysset_GetSystemLanguage() == MultiLingName.LangCode)
				{
					//Copy Service Name
					mCopyString(service->ServiceName, MultiLingName.ServiceName, (eurdiv_ChannelNameLength - 1));
					retval = true;
					break;
				}
			}
		}		
		
	}

	return retval;

}


Bool CHsvDvbTInstallation_mBackground_Priv::UpdateServiceNames(	HsvPgdatDigTSData *tsdata)
{
    int TotalServices = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));
	int index=-1;	
	HsvPgdatDigServiceData svcdat;		
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
    HsvChannel Channelinfo;
	int Onid = 0, Tsid = 0, retval = 0;
	Bool UpdateDone = false;

	
    retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &Onid) ;

	/*Update ServiceNames with NewLanguage*/
	if(retval)
	{
		for(index=0;index<TotalServices;index++)
		{
			if(strapi_GetByIndex(HsvMain,HSVSPID(ActualTSService, dvb, sdt),index,(Address)&service)==TRUE)
			{
			
		        svcdat.OriginalNetworkId     =   Onid;
		        svcdat.ServiceId             =   service.ServiceId;
		        svcdat.Frequency             =   tsdata->Frequency; 
		        svcdat.StreamPriority        =   tsdata->StreamPriority; 
				if( pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
			    {	        	
					/*Meaning user has not updated the name. So its ok we can update now. */
		            if(svcdat.UserModifiedName == FALSE)
		            {
						if(eurdiv_MultiLingSupported() && GetSvcNameWithCurrentLanguage(&svcdat,&service))
						{
							TraceDebug(m,"Service Name with LangCode: %d is available",sysset_GetSystemLanguage());
						}
						else
						{
							TraceDebug(m," MultiLingual Descriptor is not present");
						}
						if(service.ServiceName[0] == 0)
						{
							mCopyString( svcdat.ChannelName, instutil_AsciiToUnicode("-----", 10), 10);
						}

						TraceDebug(m,"Update NAME = %d", svcdat.UserModifiedName);

		            
						if (mCompareUnicodeString(svcdat.ChannelName, service.ServiceName) == FALSE)
						{
							
							Channelinfo.Ptc = svcdat.PresetNumber; 
							Channelinfo.Channel.OnePart = svcdat.PresetNumber;                  
							Channelinfo.Type = GETSERVICETYPE(svcdat.ServiceType);
							pgdat_StoreChannelDataString (Channelinfo, pgdat_StringExtChannelName,	service.ServiceName, eurdiv_ChannelNameLength);
							UpdateDone = true;
							TraceDebug(m,"Channel Name Update for preset %d done Background Mode",svcdat.PresetNumber);
						}
	            
		            }
				
				}
			}
		}
		tsdata->LanguageCode = sysset_GetSystemLanguage();
		pgdb_Update(PTC_TABLE,tsdata);
		
	}
	
	return UpdateDone;
}

Bool CHsvDvbTInstallation_mBackground_Priv::UpdateChannelName(int *pPreset)
{
	int TotalServices;
	int index=-1;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPgdatDigServiceData svcdat;
	int Onid = 0, Tsid = 0, retval = 0;

	Bool UpdateDone = false;

	int fiServID = sysset_GetServiceIDForChNameUpdate();

	//TraceDebug(m,"UpdateChannelName() is called. SrvID: %d", fiServID);

	if(fiServID > 0) {
		TotalServices = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));

		TraceDebug(m,"UpdateChannelName() is called. SrvID: %d   Size: %d", fiServID, TotalServices);

		retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &Onid);

		if(retval)
		{
			TraceDebug(m,"UpdateChannelName(): Got data.");

			retval = strapi_GetByKey(HsvMain, HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &Tsid) ;

			for(index=0;index<TotalServices;index++)
			{
				if(strapi_GetByIndex(HsvMain,HSVSPID(ActualTSService, dvb, sdt),index,(Address)&service)==TRUE)
				{
					if(service.ServiceId == fiServID) {

						TraceDebug(m,"UpdateChannelName(): Matched service found. ONID:%d  TSID:%d",Onid,Tsid);
						sysset_SetUpdatedChannelName(service.ServiceName);
						sysset_SetUpdatedONID(Onid);
						sysset_SetUpdatedTsID(Tsid);

						*pPreset = sysset_GetChUniqueIDForChNameUpdate();
						sysset_SetServiceIDForChNameUpdate(0);
						UpdateDone = true;
						break;
					}
				}
			}

		}
		else
		{
			TraceDebug(m,"UpdateChannelName(): No data.");
		}
	}

	return UpdateDone;
}


inline void CHsvDvbTInstallation_mBackground_Priv::FuncDataAvailable(void)
{
    /* Naresh: none of the PTC attributes is going to change to update */
    mAcquistionInProgress = TRUE;
    installN_OnEvent(installN_EventInstallationStarted, CURRENT_MODE);
    idataacq_AcquireData();
	installN_OnEvent(installN_EventInstallationCompleted, CURRENT_MODE);
    mAcquistionInProgress = FALSE;
}

void CHsvDvbTInstallation_mBackground_Priv::ena_Enable(void)
{
	mCurrentSessionCookie++;
    mActive = eurdiv_IsBackgroundInstallRequired(rins_Terrestrial);
    mAcquistionInProgress = FALSE;
	TraceNotice (m, "DVBT Background Enabled  mActive %d ", mActive);
}

void CHsvDvbTInstallation_mBackground_Priv::ena_Disable(void)
{
	mCurrentSessionCookie++;
	TraceNotice (m, "DVBT Background Disabled ");
    mActive = FALSE;
}

void CHsvDvbTInstallation_mBackground_Priv::ibpow_Init(void)
{
    mPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, TRUE,"hsvdvbtins_mBackground");
}

void CHsvDvbTInstallation_mBackground_Priv::ibpow_TurnOn(void)
{
    mActive = FALSE;
    mAcquistionInProgress = FALSE;
	mCurrentSessionCookie = 0;
	mPresetChanged=FALSE;
	mLowestPreset=FALSE;
}

void CHsvDvbTInstallation_mBackground_Priv::ibpow_TurnOff(void)
{

}

void CHsvDvbTInstallation_mBackground_Priv::ibstrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);

    if(mActive && BACKGROUND_INSTALL)
    {   /* Do it only when installation is not happening */
        if(( spid == HSVSPID(ActualTSService, dvb, sdt) && (TRUE == mActive)))
        {
            pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)mCurrentSessionCookie, 10000);
        }
		if(( spid == HSVSPID(ActualNITVer, dvb, nit) && (TRUE == mActive)))
		{
			pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)mCurrentSessionCookie, 10000);		
			TraceNotice(m,"3.spid=[%d]",spid);
		}
    }
}

void CHsvDvbTInstallation_mBackground_Priv::ibstrapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(eventid);
    ibstrapiN_OnAdded( dest, spid, key1, key2, key3);
}

void CHsvDvbTInstallation_mBackground_Priv::ibctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(dmx);
    UNUSED(value);

    TraceNotice(m,"%s %d eventid %d mActive %d BACKGROUND_INSTALL %d", __FUNCTION__, __LINE__, eventid, mActive, BACKGROUND_INSTALL);
    if(mActive && BACKGROUND_INSTALL)
    {
        if(eventid == ibctrlN_DataAvailable)
        {   
            pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)mCurrentSessionCookie, 1000);

        }
    }
}


void CHsvDvbTInstallation_mBackground_Priv::ibstrapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbTInstallation_mBackground_Priv::ibstrapiN_OnCompleted( HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}

/****************************************************
  provides IHsvSystemSettingsNotifyEx syssetN
 ****************************************************/

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnCountryChanged( int country )
{
}


void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnMediumChanged( int medium )
{
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnLanguageChanged (  int lang  ) 
{
	// Language changed so update service names
	TraceNotice(m,"Language Changed to : %d", lang);
	pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)mCurrentSessionCookie, 2000);
}
void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnInstalledCountryChanged (  int country ) 
{
	return;
}
void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnHearingImpairedTypeChanged (  int lang  ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredAudioFormatChanged ( int format ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredPrimaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredSecondaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredPrimarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredSecondarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredPrimaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnPreferredSecondaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_mBackground_Priv::isyssetN_OnCityChanged (  int city  ) 
{
	return;
}

