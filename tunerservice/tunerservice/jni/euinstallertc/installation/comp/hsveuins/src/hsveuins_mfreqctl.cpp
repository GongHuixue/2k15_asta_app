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
 *          %name: hsveuins_mfreqctl.c %
 *       %version: TVG_fusion_7 %
 * %date_modified: Fri Apr 04 11:58:00 2008 %
 *    %derived_by: nituk % 
 */

#include "_hsveuins_mfreqctl.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mfreqctl")


int CHsvEuropeInstallation_mfreqctl_Priv::s__InstallationInitialised = FALSE;

int CHsvEuropeInstallation_mfreqctl_Priv::s__InstallationTurnOn = FALSE;


int CHsvEuropeInstallation_mfreqctl_Priv::s__PlatformTables [PLATFORM_TABLE_ENTRIES] = {
    tmFe_TableEuropeS,
    tmFe_TableEuropeC,        
    tmFe_UnknownTable,
    tmFe_TableApAntenna,
    tmFe_TableApCable,
    tmFe_TableUsCable,
    tmFe_TableUsAntenna,
    tmFe_TableUsAfn,
    tmFe_TableEuropeDkS,
    tmFe_TableEuropeDkC,
    tmFe_TableEuropeIS,
    tmFe_TableEuropeIC,
    tmFe_TableEuropeLS,
    tmFe_TableEuropeLC

};


void CHsvEuropeInstallation_mfreqctl_Priv::imfreqctlpow_Init(void)
{
    InstallationInitialised = TRUE;
}

void CHsvEuropeInstallation_mfreqctl_Priv::imfreqctlpow_TurnOn(void)
{
    if(TRUE == InstallationInitialised)
    {
        InstallationTurnOn  =   TRUE;
    }
}

void CHsvEuropeInstallation_mfreqctl_Priv::imfreqctlpow_TurnOff(void)
{
    InstallationTurnOn  =   FALSE;
}

int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetMinFrequency( void )                      
{    
    Nat32 errorcode;
    Nat32 MinFrequency = INVALID_FREQUENCY;
    Nat32 MaxFrequency = INVALID_FREQUENCY;

    feapi_GetFreqRange(WINDOWID, &MinFrequency,&MaxFrequency, &errorcode);
    ASSERT( errorcode == TM_OK );        

    return MinFrequency;
}

int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetMaxFrequency( void )                      
{
    Nat32 errorcode;
    Nat32 MinFrequency = INVALID_FREQUENCY;
    Nat32 MaxFrequency = INVALID_FREQUENCY;

    feapi_GetFreqRange(WINDOWID, &MinFrequency,&MaxFrequency, &errorcode);
    ASSERT( errorcode == TM_OK );        

    return MaxFrequency;
}


int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetFrequency2Channel(int chantbl, int frequency )
{
    UInt32 returnChannel = rins_InvalidChannel;
    Nat32 errorcode = 0;

    if(InstallationTurnOn)
    {
        ASSERT((frequency <= freqctl_GetMaxFrequency()) && (frequency >= freqctl_GetMinFrequency()));
        if(chantbl < rins_MaxChannel)
        {

            ASSERT( errorcode == TM_OK );
            if ( errorcode == TM_ERR_FE_NO_CHAN )
            {
                returnChannel = rins_InvalidChannel;
            }
        }
    }
    return(returnChannel); 
}

int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetChannel2CarrierFrequency(int chantbl, int channel)
{
    UInt32 returnFreq = rins_InvalidFrequency;
    Nat32 errorcode = 0;

    if(InstallationTurnOn)
    {
        if(chantbl < rins_MaxChannel)
        {
            //feapi_GetCarrierFreq(WINDOWID, channel, (tmFe_ChanTable_t)PlatformTables[chantbl], &returnFreq, &errorcode );
            //ASSERT( errorcode == TM_OK );
            if ( errorcode == TM_ERR_FE_NO_FREQ)
            {
                returnFreq = rins_InvalidFrequency;
            }
        }
    }
    return ( (int)returnFreq );
}

int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetChannel2CentreFrequency(int chantbl, int channel)
{
    UInt32 returnFreq = rins_InvalidFrequency;
    Nat32 errorcode;

    if(InstallationTurnOn)
    {
		/* ANEESH: TODO: Check how to implement this */
		/*
        if(chantbl < rins_MaxChannel)
        {
            UInt32 upperFreq = rins_InvalidFrequency;
            UInt32 lowerFreq = rins_InvalidFrequency;

            feapi_GetUpperFreq(WINDOWID, channel, (tmFe_ChanTable_t)PlatformTables[chantbl], &upperFreq, &errorcode);
            ASSERT( errorcode == TM_OK );
            if ( errorcode == TM_ERR_FE_NO_FREQ)
            {
                returnFreq = rins_InvalidFrequency;
            }

            if ((Int32)upperFreq != rins_InvalidFrequency)
            {
                feapi_GetLowerFreq(WINDOWID, channel, (tmFe_ChanTable_t)PlatformTables[chantbl], &lowerFreq, &errorcode);
                ASSERT( errorcode == TM_OK );
                if ( errorcode == TM_ERR_FE_NO_FREQ)
                {
                    returnFreq = rins_InvalidFrequency;
                }
            }

            if ( ((Int32)upperFreq != rins_InvalidFrequency) && ((Int32)lowerFreq != rins_InvalidFrequency) )
            {
                returnFreq = (upperFreq + lowerFreq)/2;
            }
        }
		*/
    }
    return ( (int)returnFreq );
}

int CHsvEuropeInstallation_mfreqctl_Priv::freqctl_GetTunerFrequency( void )                        
{
    UInt32 frequency = -1;
    Nat32 errorcode;

    ASSERT(InstallationTurnOn);

    feapi_GetFreq(WINDOWID, &frequency, &errorcode);
	frequency = (frequency/16) * 1000;
    ASSERT( errorcode == TM_OK );

    return (int)frequency;
}

void CHsvEuropeInstallation_mfreqctl_Priv::freqctl_SetTunerFrequency( int freq, Bool fineTune )         
{   
    Nat32   errorcode;
    if ( InstallationTurnOn )
    {
        //hsvprins_prins_SetHandleTunerFreqNotify(TRUE);
        if( insN_iPresent() )
        {
            insN_OnEvent( insN_EventTuningStarted, INVALID_VALUE );
        }
        feapi_SetFreq(WINDOWID,freq, fineTune, &errorcode);
    }
    else
    {
        ASSERT(!"Component not Turned 0n" );
    }    
}
