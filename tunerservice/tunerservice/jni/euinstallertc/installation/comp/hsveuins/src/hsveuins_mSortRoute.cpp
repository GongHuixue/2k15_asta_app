#include "_hsveuins_mSortRoute.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mSortRoute")



#define IS_BLIZOO_FULLSCAN ((rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode) == rins_FullScan)\
							&& (CURRENT_COUNTRY == cids_CountryBulgaria) \
                            && (rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_Blizoo))
                           


int CHsvEuropeInstallation_mSortRoute_Priv::isortroute_GetCurrentActiveSortInterface()
{   
    int CurrentActiveSortInterface = isortroute_stubsort;
    
    switch(CURRENT_ACTIVE_MEDIUM)
    {
        case CABLE:
            if(IS_DVBC_LIGHT)
                CurrentActiveSortInterface = isortroute_dvbclitesort;
            else
			if(IS_BLIZOO_FULLSCAN)
			{
                CurrentActiveSortInterface = isortroute_blizoosort;
				TraceNotice(m,"Rahul:::_%s %d",__FUNCTION__,__LINE__);
			}
            else
            {	
				TraceNotice(m,"Rahul:::_%s %d",__FUNCTION__,__LINE__);			
                CurrentActiveSortInterface = isortroute_dvbcsort;
			}
            break;
        case ANTENNA:
			CurrentActiveSortInterface = isortroute_dvbtsort;
			
            switch(CURRENT_COUNTRY)
            {
                case cids_CountryItaly:
			case cids_CountryPoland:
                    if(IS_DVBT_LIGHT)
                        CurrentActiveSortInterface = isortroute_dvbtlitesort;
                    else
                        CurrentActiveSortInterface = isortroute_italysort;
                    break;
                case cids_CountryNorway:
                    if(IS_DVBT_LIGHT)
                        CurrentActiveSortInterface = isortroute_dvbtlitesort;
                    else
                        CurrentActiveSortInterface = isortroute_norsort;
                    break;
                case cids_CountryFinland:
                    CurrentActiveSortInterface = isortroute_finsort;
                    break;
				case cids_CountryAustralia://APMEA
				case cids_CountryTaiwan:
				case cids_CountryNewZealand:
				case cids_CountryMalaysia:
				case cids_CountrySingapore:
				case cids_CountryThailand:
                case cids_CountryIndonesia:
				case cids_CountryVietnam:
					CurrentActiveSortInterface=isortroute_apmeasort;
					break;
				case cids_CountryHungary:
					 CurrentActiveSortInterface=isortroute_hungarysort;
					 break;					
                default:
                    if(CURRENT_COUNTRY == cids_CountryUK)
                        CurrentActiveSortInterface = isortroute_dvbt2sort;
                    else
                    {
                        if(IS_DVBT_LIGHT)
                            CurrentActiveSortInterface = isortroute_dvbtlitesort;
                        else
                            CurrentActiveSortInterface = isortroute_dvbtsort;
                    }
                    break;
            }
			
            break;
        default:
            break;
    }
    //TraceNotice(m,"%s %d CurrentActiveSortInterface %d", __FUNCTION__, __LINE__, CurrentActiveSortInterface);
    return CurrentActiveSortInterface;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_Initialise(void)
{
    TraceNotice(m,"Hey, look sorting calls are getting grounded, atleast some sort module should be active to handle sort calls");
    ASSERT(!"none of the sort module is active, hence sorting calls are getting grounded");
}


HsvChannel CHsvEuropeInstallation_mSortRoute_Priv::istubsort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = -1;
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    return channel;
}


void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AddAnalogPreset(Address adata) 
{
	return;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AnalogPresetEntry(void) 
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN) 
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country ) 
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsOfOtherCountries   (void) 
{
	return FALSE;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AddDigitalPreset (HsvPgdatDigServiceData *svcdat) 
{
	return;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AutoStoreManualInstallationValues (void) 
{
	return FALSE;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_RemoveDigitalPresets(void) 
{
	return;
}

int CHsvEuropeInstallation_mSortRoute_Priv::istubsort_GetNumberOfAnalogChannelsFound() 
{
	return 0;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_UpdateDigitalPreset(HsvPgdatDigServiceData *svcdat) 
{
	return;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_DeleteAllDigitalChannels()     
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_UpdatingLCNDuringUpdateInstallation() 
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_DeleteInvalidPTCTable() 
{
	return FALSE;
}

int CHsvEuropeInstallation_mSortRoute_Priv::istubsort_GetOriginalNetworkId(int CurrentCountry) 
{
	return 0;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_IsPresetInstalled(Int32 frequency) 
{
	return FALSE;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsForCountry(int ONID) 
{
	return;
}

void CHsvEuropeInstallation_mSortRoute_Priv::istubsort_SortAll() 
{
	return;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles) 
{
	return FALSE;
}

Bool CHsvEuropeInstallation_mSortRoute_Priv::istubsort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid) 
{
	return FALSE;
}

void CHsvEuropeInstallation_mSortRoute_Priv::isortroute_Enable(void)
{
	return;
}

