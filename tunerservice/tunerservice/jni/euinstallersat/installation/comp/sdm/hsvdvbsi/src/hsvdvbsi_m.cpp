/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvdvbsi_m.c %
 *       %version: TVG_1 %
 * %date_modified: Wed Dec 19 14:46:12 2007 %
 *    %derived_by: aneeshc %
 */
 


#include "_hsvdvbsi_m.h"


void CHsvDvbSiDataManager_m_Priv::pow_Init(void)
{
#define TABLEITEM(a, b, c)  chsvdvb##a##_pow_Init();  
#include "hsvdvbtables.h"
#undef TABLEITEM
    //chsvdvbpes_pow_Init();
}

void CHsvDvbSiDataManager_m_Priv::pow_TurnOn(void)
{
#define TABLEITEM(a, b, c)  chsvdvb##a##_pow_TurnOn();  
#include "hsvdvbtables.h"
#undef TABLEITEM
    //chsvdvbpes_pow_TurnOn();
}

void CHsvDvbSiDataManager_m_Priv::pow_TurnOff(void)
{
#define TABLEITEM(a, b, c)  chsvdvb##a##_pow_TurnOff();  
#include "hsvdvbtables.h"
#undef TABLEITEM
    //chsvdvbpes_pow_TurnOff();
}

void CHsvDvbSiDataManager_m_Priv::ena_Enable(HsvDemux dmx)
{
#define TABLEITEM(a, b, c)  chsvdvb##a##_ena_Enable( dmx );  
#include "hsvdvbtables.h"
#undef TABLEITEM
}

void CHsvDvbSiDataManager_m_Priv::ena_Disable(HsvDemux dmx)
{    
#define TABLEITEM(a, b, c)  chsvdvb##a##_ena_Disable( dmx );  
#include "hsvdvbtables.h"
#undef TABLEITEM
}

void CHsvDvbSiDataManager_m_Priv::ena_Sync(HsvDemux dmx)
{
#define TABLEITEM(a, b, c)  chsvdvb##a##_ena_Sync( dmx );  
#include "hsvdvbtables.h"
#undef TABLEITEM
}

#if 0


    /** koala type HsvEuropePTCData **/

/* The attributes of a digital channel, represents one channel*/
    /** koala type HsvProgramData **/



Nat16 CHsvDvbSiDataManager_m_Priv::GetOriginalNetworkId(int CurrentCountry)
{
    Nat16 OriginalNetworkId = 0xFFFF;
    switch(CurrentCountry)
    {
        case Denmark:
        case Finland:
        case France:
        case Germany:
        case Italy:
        case Netherlands:
        case Norway:
        case Poland:
        case Portugal:
        case Spain:
        case Sweden:
        case UK:
            OriginalNetworkId = CurrentCountry + 0x2000;  
            break;
        case Australia:
            /* TBD */
            break;
        default:
            {
                int i = 0;      
                int TSesWithKnownONWID = TRUE;
                int CurrentSignalStrenth = 0;

                if(MaxTransportStreams > 0 )
                {
                    OriginalNetworkId       = PTCList[0].ONWID;
                    CurrentSignalStrength   = PTCList[0].SignalStrength;
                }

                for(i = 0; i < MaxTransportStreams; i++)
                {
                    switch(PTCList[i].ONWID - 0x2000)
                    {
                        case Denmark:
                        case Finland:
                        case France:
                        case Germany:
                        case Italy:
                        case Netherlands:
                        case Norway:
                        case Poland:
                        case Portugal:
                        case Spain:
                        case Sweden:
                        case UK:
                        case Australia:
                            {
                                if( (TRUE == TSesWithKnownONWID ) && 
                                    (PTCList[i].SignalStrength > CurrentSignalStrength ) )
                                {   /* Streams with all known ONWID, get the best reception quality */                                     
                                    OriginalNetworkId       = PTCList[i].ONWID;
                                    CurrentSignalStrength   = PTCList[i].SignalStrength;
                                }
                                break;
                            }
                        default:
                            {   
                                if( TRUE == TSesWithKnownONWID)
                                {   /* Oh! we encountered a TS with an unknown ONWID */
                                    TSesWithKnownONWID = FALSE;
                                    OriginalNetworkId       = PTCList[i].ONWID;
                                    CurrentSignalStrength   = PTCList[i].SignalStrength;
                                }
                                else
                                {
                                    if (PTCList[i].SignalStrength > CurrentSignalStrength) 
                                    {   /* Streams with all unknown ONWID, get the best reception quality */                                       
                                        OriginalNetworkId       = PTCList[i].ONWID;
                                        CurrentSignalStrength   = PTCList[i].SignalStrength;
                                    }
                                }
                                break;
                            }
                    }
                }
                break;
            }
    }
    return OriginalNetworkId;
}

Bool CHsvDvbSiDataManager_m_Priv::DigitalPresetEntryforValidLCN(int dbindex)
{
    int retval = FALSE;
    HsvDVBPrimayServiceData psdata;

    srtdb_QueryOnIndex(primaryservicetableid, dbindex,(Address )&psdata);

    if(0 != psdata.LCN)
    {
        Bool MakeCurrentLCNInvalid = TRUE;
        if( psdata.LCN < 1000)
        {
            HsvPresetData presetdata;
            if(srtdb_QueryOnKey(userselectabletableid, psdata.LCN, 0, 0, (Address )&presetdata))
            {   /* Preset Exists */
                HsvDVBPrimaryServiceData oldpsdata;
                if(srtdb_QueryOnKey(primaryservicetableid, presetdata.Onwid, presetdata.ServiceId, 0 ,(Address )&oldpsdata))
                {
                    Bool PresetRequireRefilling = FALSE;
                    if( FALSE == presetdata.PresetReserved )
                    {
                        if (oldpsdata.ServiceType > psdata.ServiceType) 
                        {
                            PresetRequireRefilling = TRUE;
                        }
                        else if( oldpsdata.ServiceType == psdata.ServiceType )
                        {
                            HsvDVBTSData tsdata;
                            HsvDVBTSData oldtsdata;
                            if(! srtdb_QueryOnKey(tstableid, psdata.Onwid, psdata.Tsid, 0, (Address)& tsdata))
                            {
                                ASSERT(! "Not present ? Strange !");
                            }
                            if(! srtdb_QueryOnKey(tstableid, oldpsdata.Onwid, oldpsdata.Tsid, 0, (Address)& oldtsdata))
                            {
                                ASSERT(! "Not present ? Strange !");
                            }
                            if( oldtsdata.SignalStrength  < tsdata.SignalStrength )
                            {
                                PresetRequireRefilling = TRUE;
                            }
                        }
                    }
                    
                    if( TRUE == PresetRequireRefilling)
                    {   

                        oldpsdata.LCN = INVALID_LCN;
                        srtdb_Update(primaryservicetableid, oldpsdata.Onwid , oldpsdata.ServiceId ,0 , oldpsdata);

                        presetdata.Type             = HsvDigital;
                        presetdata.Onwid            = psdata.Onwid;
                        presetdata.ServiceId        = psdata.ServiceId;
                        presetdata.Cookie           = NOCOOKIE;
                        presetdata.PresetReserved   = FALSE;
                        srtdb_Update(userselectabletableid, psdata.LCN, 0, 0, (Address )&presetdata);
                        MakeCurrentLCNInvalid = FALSE;    
                        retval = TRUE;                        
                    }
                }
                else
                {
                    ASSERT(! "Abe, Kisine corrupt kiya kya ?");
                }
                
            }
            else
            {   /* Preset Empty */
                presetdata.Preset           = psdata.LCN;
                presetdata.Type             = HsvDigital;
                presetdata.Onwid            = psdata.Onwid;
                presetdata.ServiceId        = psdata.ServiceId;
                presetdata.Cookie           = NOCOOKIE;
                presetdata.PresetReserved   = FALSE;
                srtdb_Insert(userselectabletableid, psdata.LCN, 0, 0, 0,(Address )&presetdata);
                pmp_PmpSend( UslPump, ONPRESETADDED, presetdata.Preset );
                MakeCurrentLCNInvalid = FALSE;    
                retval = TRUE;
            }

        }
        if(TRUE == MakeLCNInvalid)
        {   
            psdata.LCN = INVALID_LCN;
            srtdb_Update(primaryservicetableid, psdata.Onwid , psdata.ServiceId ,0 , psdata);
        }

    }
    return retval;
}


int CHsvDvbSiDataManager_m_Priv::GetNextFreePresetSegment()
{
    int retval = INVALID_PRESET;
    HsvPresetData presetdata;
    int AnalogBlock = FALSE;
    int MaxGapSize = 0;
    int i = 0;
    int NonLCNBlockStart = srtdb_QueryOnKey(userselectabletableid, LastLCNBasedPreset, 0, 0, (Address &)presetdata);
    int previouspreset = presetdata.preset;

    for(i = NonLCNBlockStart ; i < srtdb_GetNoOfRecords(userselectabletableid); i++)
    {
        srtdb_QueryOnIndex(userselectabletableid, i,(Address )&presetdata);

        if(TRUE != AnalogBlock)
        {   /* Never find gaps inside the Analog Channels */
            CurrentGapSize = presetdata.preset - previouspreset + 1;
            if( MaxGapSize < CurrentGapSize )
            {
                MaxGapSize = CurrentGapSize; 
                retval = previouspreset;
            }
        }
        else
        {
            if(HsvAnalog != presetdata.Type)
            {
                AnalogBlock = FALSE;
            }
        }
        previouspreset = presetdata.preset;
        if( HsvDigital != presetdata.Type)
        {
            AnalogBlock = TRUE;
        }
    }
    
    previouspreset = 0;
    if(0 == MaxGapSize)
    {   /* Did not find any gap in the Non LCN block */
        for(i = 0; i < NonLCNBlockStart ; i++)
        {
            srtdb_QueryOnIndex(userselectabletableid, i,(Address )&presetdata);

            CurrentGapSize = presetdata.preset - previouspreset + 1;
            if( MaxGapSize < CurrentGapSize )
            {
                MaxGapSize = CurrentGapSize; 
                retval = previouspreset;
                previouspreset = presetdata.preset;
            }
        }
    }
    return retval;
}

Bool CHsvDvbSiDataManager_m_Priv::DigitalPresetEntryforInValidLCN(int dbindex)
{
    int retval = TRUE;
    HsvDVBPrimayServiceData psdata;

    srtdb_QueryOnIndex(primaryservicetableid, dbindex,(Address )&psdata);

    if( (CurrentPresetIndex >= 1000) || 
         srtdb_QueryOnKey(userselectabletableid, CurrentPresetIndex, 0, 0) ) 
    {   /* Current Preset is not empty */
        if((CurrentPresetState = GetNextFreePresetSegment()) == INVALID_PRESET)
        {
            ASSERT(! "Sorry Saar, you have run out of presets!");
            pmp_PmpSend( UslPump, ONPRESETTABLEFULL, 0 );
            retval = FALSE;
        }
    }
    
    if(TRUE == retval)
    {
        HsvPresetData presetdata;
        presetdata.Preset           = CurrentPresetIndex;
        presetdata.Type             = HsvDigital;
        presetdata.Onwid            = psdata.Onwid;
        presetdata.ServiceId        = psdata.ServiceId;
        presetdata.Cookie           = NOCOOKIE;
        presetdata.PresetReserved   = FALSE;
        srtdb_Insert(userselectabletableid, CurrentPresetIndex, 0, 0, 0,(Address )&presetdata);
        pmp_PmpSend( UslPump, ONPRESETADDED, presetdata.Preset );
        CurrentPresetIndex++;
    }
    return retval;
}


                                                    

Bool CHsvDvbSiDataManager_m_Priv::AnalogPresetEntry()
{   /* Note: This function does not handle the following case. What if we fail to find a proper 10x + 1 or 100x + 1
             slot for filling the analogees. You need to try probably 100x + 10y + 1 (this is my idea not from TRS - shall
             i patent it?! ;-))or you need to split this into two (mutiple) slots & try to fit in.These are not very 
             important as currently it will be easy to find atleast a 100x + 1 slot for the analoguees and soon the analog 
             channels might get fewer & fewer & they might start fitting in some 10x + 1 itself. 
    */
    Bool retval = FALSE;
    int AnalogChannelBlock = MaxAnalogPreset - MinAnalogPreset;

    HsvPresetData presetdata;
    int AnalogBlock = FALSE;
    int i = 0;
    int NonLCNBlockStart = srtdb_QueryOnKey(userselectabletableid, LastLCNBasedPreset, 0, 0, (Address &)presetdata);
    int previouspreset = presetdata.preset;

    for(i = NonLCNBlockStart + 1; i < srtdb_GetNoOfRecords(userselectabletableid); i++)
    {
        GETVALIDANALOGPRESET(previouspreset); 
        srtdb_QueryOnIndex(userselectabletableid, i,(Address )&presetdata);

        GapSize = presetdata.preset - previouspreset + 1;
        if( GapSize > AnalogChannelBlock )
        {
            break;
        }
        previouspreset = presetdata.preset;
    }    

    for(i = MinAnalogPreset; i < MaxAnalogPreset, i++)
    {
        HsvPresetData presetdata;
        presetdata.Type             =   HsvAnalog;
        presetdata.Preset           =   previouspreset + (i - MinAnalogPreset);
        presetdata.Onwid            =   0xFFFF;
        presetdata.ServiceId        =   i;
        presetdata.Cookie           =   INVALID_COOKIE;
        presetdata.PresetReserved   =   FALSE; /*If we put it true, we can permenantly block all analog presets
                                                 from being filled by any digital preset. Should we ? */
        srtdb_Insert(userselectabletableid, previouspreset + (i - MinAnalogPreset), 0, 0, 0,(Address )&presetdata);
    }
    retval = TRUE;  /* We have not considered any FALSE case. Presently, It will always succeed! See Note */
    return retval;

}

Bool CHsvDvbSiDataManager_m_Priv::AddTS()
{
    int retval = FALSE;
    int SignalStrength = GetSignalStrength();

    if(IsAcceptable(SignalStrength))
    {
        ctrl_StartCollection(InsStatus.CurrentDmux,ctrl_Minimal);
        retval = TRUE;
    }
    return TRUE;
}

Bool CHsvDvbSiDataManager_m_Priv::TSAcquired()
{
    int retval = FALSE;
    int Onwid   = svc_GetOriginalNetworkId();
    int Tsid    = svc_GetTsid();
    HsvDVBTSData   tsdata;

    if(srtdb_QueryByKey( tstableid, Onwid, Tsid, 0, (Address )&tsdata))
    {   /* TS already exists */
        if( tsdata.SIValid == svc_GetSIValid())
        {   /* The existing one and the new one are looking at the same table (SDT or PAT) */
            if( tsdata.TSVersionNumber == svc_GetTSVersionNumber())
            {
                if(CurrentVersionNumber == tsdata.DBVersionNumber)
                {   /* We have encountered the same TS in a different frequency */
                    if( GetSignalStrength() > tsdata.SignalStrength ) 
                    {
                        tsdata.Frequency        =   GetFrequency();
                        tsdata.ModulationType   =   GetModulationType();
                        tsdata.SignalStrength   =   GetSignalStrength();
                        tsdata.DBVersionNumber  =   CurrentVersionNumber;
                    }
                }
                else
                {   /* We have encountered an existing TS during update install */
                    tsdata.Frequency        =   GetFrequency();
                    tsdata.ModulationType   =   GetModulationType();
                    tsdata.SignalStrength   =   GetSignalStrength();
                    tsdata.DBVersionNumber  =   CurrentVersionNumber;
                }
            }
            else
            {   /* TS Information New */
                tsdata.TSVersioNumber   =   svc_GetTSVersionNumber();
                tsdata.Frequency        =   GetFrequency();
                tsdata.ModulationType   =   GetModulationType();
                tsdata.SignalStrength   =   GetSignalStrength();
                tsdata.DBVersionNumber  =   CurrentVersionNumber;
                AddServices();
                retval = TRUE;
            }
        }
        else
        {   /* Either SI data has become "recently" invalid or got "recently" valid */
            /* Requirements on how to do it not frozen */
            retval = TRUE;
        }
    }
    else
    {   /* TS new */
        tsdata.Onwid            =   Onwid;
        tsdata.Tsid             =   Tsid;
        tsdata.Frequency        =   GetFrequency();
        tsdata.ModulationType   =   GetModulationType();
        tsdata.SignalStrength   =   GetSignalStrength();
        tsdata.TSVersioNumber   =   svc_GetTSVersionNumber();
        tsdata.SIValid          =   svc_GetSIValid();
        tsdata.DBVersionNumber  =   CurrentVersionNumber;
        AddServices();
    }
    return retval;
}


#endif



Bool CHsvDvbSiDataManager_m_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    switch(filterid)
    {
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvCurrentProgram:
        case HsvExtendedInfoEventId :
        case HsvExtendedInfoONId :
		case HsvExtendedInfoTsId :
        case HsvExtendedInfoSerId :
        case HsvShortDescEventId :
        case HsvShortDescONId :
		case HsvShortDescTsId :
        case HsvShortDescSerId :    
        case HsvOtherSDTOnwidId: 
        case HsvOtherSDTServiceId:        
            retval = chsvdvbsdt_strmfltr_Set( dest, filterid, value );
            break;                    
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/




Bool CHsvDvbSiDataManager_m_Priv::strmfltr_Clear(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    switch(filterid)
    {
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvCurrentProgram:
        case HsvExtendedInfoONId :
		case HsvExtendedInfoTsId :
        case HsvExtendedInfoSerId :
        case HsvShortDescEventId :
        case HsvShortDescONId :
		case HsvShortDescTsId :
        case HsvShortDescSerId :            
        case HsvOtherSDTOnwidId: 
        case HsvOtherSDTServiceId:            
            break; 
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */


void CHsvDvbSiDataManager_m_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbSiDataManager_m_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrId )
{
	chsvdvbnit_dmxsecfN_OnRequestCancelled(subscrId);
	chsvdvbfnt_dmxsecfN_OnRequestCancelled(subscrId);
	chsvdvbfst_dmxsecfN_OnRequestCancelled(subscrId);
	chsvdvbsdt_dmxsecfN_OnRequestCancelled(subscrId);
	chsvdvbsgt_dmxsecfN_OnRequestCancelled(subscrId);
}

void CHsvDvbSiDataManager_m_Priv::dmxsecfN_OnRequestNotAllowed ()
{
}

Bool CHsvDvbSiDataManager_m_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbSiDataManager_m_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}



/*************************************************************/




