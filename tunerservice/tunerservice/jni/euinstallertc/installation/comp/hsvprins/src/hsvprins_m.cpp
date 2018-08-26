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
 *          %name: hsvprins_m.c %
 *       %version: TVG_Fusion_7 %
 * %date_modified: Wed Mar 04 18:00:26 2009 % 
 *    %derived_by: nareshj %
 */

#include "_hsvprins_m.h"
#include <unistd.h>
#include "hsvprins.h"

TRACESYMBOL(m,"analog/installation/hsvprins_m")
extern "C" {
extern void txvbi__dcu_Enable( void );
extern void txvbi__dcu_Disable( void );
extern void  txsvc__tsacqctrl_Resume();
		extern void txplf__txacqctrl_Resume( );
	extern bool	txplf__txacqctrl_Suspend();
	extern bool	txsvc__tsacqctrl_Suspend();
	extern	bool txplf__txacqctrl_Reset(int);
		extern	bool txsvc__tsacqctrl_Reset(int);

extern void txvbi__vbislN_OnWstData (int wsttype,const int nrLines,int * const pLines,const int sizeFirstBuffer,const int sizeSecondBuffer, int * const firstBuffer,int * const secondBuffer);
}
#define ACI_PRESET_NAME_LENGTH (1)
#define DEFAULT_ANALOG_PRESET_NAME "-----"
#define DEFAULT_ANALOG_PRESET_LENGTH (5)
#ifndef mem_iPresent_CONSTANT
// TODO:#error The presence of "mem" must be statically known

#endif



tmFe_SearchMode_t CHsvPresetInstallation_m_Priv::s__TvSystemsearch = 0;


int CHsvPresetInstallation_m_Priv::s__ColorSystemSearch = 0;
int CHsvPresetInstallation_m_Priv::s__mCurrentSortingIndex = 0;
CHsvPresetInstallation_m_Priv* CHsvPresetInstallation_m_Priv::currentinstance = NULL;

/*static int WaitForTxtResetinAutoInstall = FALSE;*/

/******************************************
 * Local macros
 ******************************************/




#if CHECK_SECAML_SUPPORT

#else

#endif






    

/******************************************
 * Local typedefs
 ******************************************/




/*****************************************
 * Static variables
 *****************************************/

#if mem_iPresent_CONSTANT

HsvPresetSortData * CHsvPresetInstallation_m_Priv::s__PresetData;
                             /* pointer to the preset list which is dynamically allocated */
char *             CHsvPresetInstallation_m_Priv::s__presetNames;
                            /* pointer to the presetnames list */
Nat8 *             CHsvPresetInstallation_m_Priv::s__PresetIndex;
                            /* pointer to the index list for sorting on signalstrength */
#else

#ifndef __cplusplus

HsvPresetSortData CHsvPresetInstallation_m_Priv::s__PresetData[div_MaxAnalogPresets];

char CHsvPresetInstallation_m_Priv::s__presetNames[div_MaxAnalogPresets * div_PresetNameLength];
 
Nat8 CHsvPresetInstallation_m_Priv::s__PresetIndex[div_MaxAnalogPresets];
            /* pointer to the index list for sorting on signalstrength */
#else

HsvPresetSortData CHsvPresetInstallation_m_Priv::s__PresetData[IHsvPresetInstallationDiv_MaxAnalogPresets];

char CHsvPresetInstallation_m_Priv::s__presetNames[IHsvPresetInstallationDiv_MaxAnalogPresets * IHsvPresetInstallationDiv_PresetNameLength];
 
Nat8 CHsvPresetInstallation_m_Priv::s__PresetIndex[IHsvPresetInstallationDiv_MaxAnalogPresets];
            /* pointer to the index list for sorting on signalstrength */
#endif

#endif
/* pointer to the preset names list, which is dynamivally allocated */

HsvPresetSortData CHsvPresetInstallation_m_Priv::s__miPreset;
                              /* preset data for manual,implicit and background installation */
Nat16 CHsvPresetInstallation_m_Priv::s__currentVpsCni;
                          /* VPS CNI detected for current preset */
Nat16 CHsvPresetInstallation_m_Priv::s__currentPkt830Cni;
                       /* Packet 830 CNI detected for current preset */
Nat16 CHsvPresetInstallation_m_Priv::s__currentPkt830Ni;
                        /* Packet 830 NI detected for current preset */
#ifndef __cplusplus

char CHsvPresetInstallation_m_Priv::s__miPresetName[ div_PresetNameLength ];
     /* name for manual installation preset */
char CHsvPresetInstallation_m_Priv::s__tempStr[div_PresetNameLength];

char CHsvPresetInstallation_m_Priv::s__defaultName[div_PresetNameLength];

#else

char CHsvPresetInstallation_m_Priv::s__miPresetName[ IHsvPresetInstallationDiv_PresetNameLength ];
     /* name for manual installation preset */
char CHsvPresetInstallation_m_Priv::s__tempStr[IHsvPresetInstallationDiv_PresetNameLength];

char CHsvPresetInstallation_m_Priv::s__defaultName[IHsvPresetInstallationDiv_PresetNameLength];

#endif

char CHsvPresetInstallation_m_Priv::s__msgString[21];
                          /* to get status message from packet 830 */
int CHsvPresetInstallation_m_Priv::s__installationMode;
                       /* current installation mode */
int CHsvPresetInstallation_m_Priv::s__manualInstallationMode;
                 /* current manual installation mode */
HsvChannel CHsvPresetInstallation_m_Priv::s__currentPreset;
                          /* current preset */
HsvChannel CHsvPresetInstallation_m_Priv::s__lastPresetFound;
                        /* last found preset */
int CHsvPresetInstallation_m_Priv::s__noOfPresetsFound;
                       /* number of presets found */
int CHsvPresetInstallation_m_Priv::s__noOfNewPresetsFound;
                    /* number of new presets found */
Pump CHsvPresetInstallation_m_Priv::s__prgInstallationPump;

int CHsvPresetInstallation_m_Priv::s__nbOfStationAfterSort;
               /* number of presets after sorting is completed */
int CHsvPresetInstallation_m_Priv::s__setChannel;
                             /* channel to be set during manual installation */
int CHsvPresetInstallation_m_Priv::s__setFrequency;
                           /* frequency to be set during manual installation */
int CHsvPresetInstallation_m_Priv::s__setOffset;
                              /* offset to be set during manual installation */
Bool CHsvPresetInstallation_m_Priv::s__fineTune;

int CHsvPresetInstallation_m_Priv::s__presetNumberStored;

int CHsvPresetInstallation_m_Priv::s__noOfPresetFoundInFirstPass;

int CHsvPresetInstallation_m_Priv::s__aciTimeOutCounter;
                      /* counter to maintain ACI timeout */
int CHsvPresetInstallation_m_Priv::s__country;

int CHsvPresetInstallation_m_Priv::s__SPointCSearch;

int CHsvPresetInstallation_m_Priv::s__SPointSSearch;


int CHsvPresetInstallation_m_Priv::s__tvsystemDetectCounter ;

#ifndef __cplusplus

int CHsvPresetInstallation_m_Priv::s__fieldCNI    = (p830_iPresent() ? p830_InvalidRequestId : -1);

int CHsvPresetInstallation_m_Priv::s__fieldNI     = (p830_iPresent() ? p830_InvalidRequestId : -1);

int CHsvPresetInstallation_m_Priv::s__fieldSTATUS = (p830_iPresent() ? p830_InvalidRequestId : -1);

int CHsvPresetInstallation_m_Priv::s__fieldVPS    = (vps_iPresent() ? vps_InvalidRequestId : -1 );

#else

int CHsvPresetInstallation_m_Priv::s__fieldCNI    = IHsvTxtPacket830Data_InvalidRequestId;

int CHsvPresetInstallation_m_Priv::s__fieldNI     = IHsvTxtPacket830Data_InvalidRequestId;

int CHsvPresetInstallation_m_Priv::s__fieldSTATUS = IHsvTxtPacket830Data_InvalidRequestId;

int CHsvPresetInstallation_m_Priv::s__fieldVPS    = IHsvTxtVpsData_InvalidRequestId;

#endif

UInt32 CHsvPresetInstallation_m_Priv::s__lastTunerFrequency;

UInt32 CHsvPresetInstallation_m_Priv::s__ManualInstallFrequency;


/* flags */
Bool CHsvPresetInstallation_m_Priv::s__automaticInstallationFirstPass;

Bool CHsvPresetInstallation_m_Priv::s__manualInstallationPendingStore;

Bool CHsvPresetInstallation_m_Priv::s__prgInstallationInitialised ;

Bool CHsvPresetInstallation_m_Priv::s__prgInstallationTurnOn ;

Bool CHsvPresetInstallation_m_Priv::s__installationStopped ;

Bool CHsvPresetInstallation_m_Priv::s__setFrequencyManual ;

Bool CHsvPresetInstallation_m_Priv::scanningInProgress  = FALSE;

Bool CHsvPresetInstallation_m_Priv::s__setChannelManual ;

Bool CHsvPresetInstallation_m_Priv::s__backGroundCniUpdationOn ;

Bool CHsvPresetInstallation_m_Priv::s__stationFoundFlag ;

Bool CHsvPresetInstallation_m_Priv::s__tvSystemFoundFlag ;

Bool CHsvPresetInstallation_m_Priv::s__txplfResetFlag ;

Bool CHsvPresetInstallation_m_Priv::s__aciSearchOverFlag ;

Bool CHsvPresetInstallation_m_Priv::s__askAciToStorePreset ;

Bool CHsvPresetInstallation_m_Priv::s__currentPresetAciSearch;

Bool CHsvPresetInstallation_m_Priv::s__presetFoundInFirstPass;

Bool CHsvPresetInstallation_m_Priv::s__statusMessageFound ;

Bool CHsvPresetInstallation_m_Priv::s__aciTimeoutStarted ;

Bool CHsvPresetInstallation_m_Priv::s__tvSystemDetectFlag ;

Bool CHsvPresetInstallation_m_Priv::s__positiveModulationSearchStarted ;

Bool CHsvPresetInstallation_m_Priv::s__installMode;

Bool CHsvPresetInstallation_m_Priv::s__manualStationFoundFlag ;

Bool CHsvPresetInstallation_m_Priv::s__implicitInstRequired = FALSE;

Bool CHsvPresetInstallation_m_Priv::s__changePresetAttrib;
 
Bool CHsvPresetInstallation_m_Priv::s__updateOnlyCniInBackground;

Bool CHsvPresetInstallation_m_Priv::s__allMemoryFilled;

Bool CHsvPresetInstallation_m_Priv::s__fineTuneSorC;
     
Bool CHsvPresetInstallation_m_Priv::s__signalStrengthMeasurementInProgress = FALSE;

Bool CHsvPresetInstallation_m_Priv::s__aciPresetStorageOn;



Bool CHsvPresetInstallation_m_Priv::s__HndlSetTunerFreqNtf = FALSE;

tmFe_SearchMode_t CHsvPresetInstallation_m_Priv::s__searchmode = tmFe_SmDefault;

UInt32 CHsvPresetInstallation_m_Priv::s__freqendpos;

int CHsvPresetInstallation_m_Priv::s__WaitForColorSystemPump;

int CHsvPresetInstallation_m_Priv::s__AnalogPassNo = 0;

int CHsvPresetInstallation_m_Priv::s__NoOfPresets = 0;

int CHsvPresetInstallation_m_Priv::s__installationState   =   HsvinsStateNone;

Int32 CHsvPresetInstallation_m_Priv::s__mRfaMinAmplification,CHsvPresetInstallation_m_Priv::s__mRfaMaxAmplification;


/******************************************
 * Forward declarations
 ******************************************/


//Pump filereadpump;

static FILE *in_file =NULL; 

//void Readdata();






















































/*static void prins_StopBackgroundCniUpdation(void);*/




#if CHECK_SECAML_SUPPORT


#endif







int CHsvPresetInstallation_m_Priv::mGetAnalogInstallationSequence (void)
{
   int   retval = eurdiv_PalOnly;
//   TraceDebug(m,"Hsvprins %s %d",__FUNCTION__,__LINE__);

   switch (sysset_GetSystemCountry())
   {
		  case cids_CountryBelgium:
		  case cids_CountryLuxembourg:
		  case cids_CountrySwitzerland:
          if(eurdiv_GetDualAnalogPassStatus())
		  {
		    retval = eurdiv_PalSecam;
		  }
		  else
		  {
		    retval = eurdiv_PalOnly;
		  }
			   break;
		  case cids_CountryFrance:
          if(eurdiv_GetDualAnalogPassStatus())
		  {
		    retval = eurdiv_SecamPal;
		  }
		  else
		  {
		    retval = eurdiv_SecamOnly;
		  }				
				break;
		  default:
				retval = eurdiv_PalOnly;
				break;
   }
   TraceDebug(m,"Hsvprins %s %d retval = %d",__FUNCTION__,__LINE__,retval);

   return retval;
}






/****************************************************/
void CHsvPresetInstallation_m_Priv::pow_Init( )
    /****************************************************
     * Purpose : Initialize program installation.
     ****************************************************/
{       
    prgInstallationInitialised =  TRUE;
    prgInstallationPump    = pmp_PmpCreateEx(pen_PumpEngine, ProgramInstallationStep, FALSE, "chnInsPump");    
    WaitForColorSystemPump = pmp_PmpCreateEx(pen_PumpEngine, WaitForColorSystem, TRUE, "InsColSys");    
} 

/****************************************************/
void CHsvPresetInstallation_m_Priv::pow_TurnOn()
    /****************************************************
     * initialize variables at the power turnon
     *****************************************************/
{
    ASSERT(prgInstallationInitialised);
    if ( prgInstallationInitialised )   
    {           
        txplfResetFlag = TRUE;
        implicitInstRequired  = FALSE;
        prgInstallationTurnOn = TRUE;
        SPointCSearch = 0;
        SPointSSearch = 0;
        lastTunerFrequency = 0;
        tvsystemDetectCounter = 0;
        setChannel = 0;
        miPreset.Name = miPresetName;
        installationMode = prins_InstallationModeNone;
        installationState = HsvinsStateNone;
        noOfPresetsFound = 0;
        noOfNewPresetsFound = 0;
        currentPreset.Channel.AnalogNo    = 1;
        str_strncpy(defaultName,DEFAULT_ANALOG_PRESET_NAME,DEFAULT_ANALOG_PRESET_LENGTH);//div_PresetNameLength);
        str_strncpy(miPreset.Name,DEFAULT_ANALOG_PRESET_NAME,DEFAULT_ANALOG_PRESET_LENGTH);
       
        fieldNI        = (p830_iPresent() ? p830_InvalidRequestId : -1);
        fieldSTATUS    = (p830_iPresent() ? p830_InvalidRequestId : -1);
        fieldCNI       = (p830_iPresent() ? p830_InvalidRequestId : -1);
        fieldVPS       = (vps_iPresent() ? vps_InvalidRequestId : -1);
        HndlSetTunerFreqNtf = FALSE;


#if( mem_iPresent_CONSTANT )

        PresetData  = NULL;
        presetNames = NULL;

#endif

        if( div_SearchForTvSystemInInstallation ) 
        {
            TvSystemsearch = tmFe_SmTvSystemIncluded;

        }
        if( div_SearchForColorSystemInInstallation )
        {        
            ColorSystemSearch = tmFe_SmColorSystemIncluded;        
        }
    }
    else
    {
        instutil_LogError( log_FatalErr, PRINS_INVALID_TURNON ); /*log the error */
    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::pow_TurnOff()
    /****************************************************
     * releases memory if still held
     *****************************************************/
{

    prgInstallationTurnOn = FALSE;                        
    HndlSetTunerFreqNtf = FALSE;

}

void CHsvPresetInstallation_m_Priv::prins_InitialiseTotalChannels ()
{
	noOfPresetsFound	= 0;
}
void CHsvPresetInstallation_m_Priv::prins_Initialise(void)
{
    int NoOfAnalogPresets = -1;
    int i, j, startpreset;
    HsvPgdatAnalogData anadat;


    currentPreset.Channel.AnalogNo      = 1;
    //noOfPresetsFound                    = 0;

    noOfNewPresetsFound                 = 0;
    noOfPresetFoundInFirstPass          = 0;
    changePresetAttrib                  = TRUE;
    presetFoundInFirstPass              = FALSE;
    positiveModulationSearchStarted     = FALSE;
    signalStrengthMeasurementInProgress = FALSE;
    manualInstallationMode              = prins_ManualInstallationModeFrequency;
    aciSearchOverFlag                   = FALSE;
    askAciToStorePreset                 = FALSE;
    statusMessageFound                  = FALSE;
    allMemoryFilled                     = FALSE;
    aciPresetStorageOn                  = FALSE;
    HndlSetTunerFreqNtf                 = FALSE;
    AnalogPassNo                        = 1;
    NoOfPresets                         = 0;
    country                             = sysset_GetSystemCountry();       /* get teletext region */

    if( HSV_INSTALL_INVLAID_ANALOG )
    {   
        NoOfAnalogPresets = pgdb_GetNoRecords( ANALOG_TABLE );

        if( NoOfAnalogPresets < div_MaxAnalogPresets )
        {
            startpreset = 0;
            for( i=0; i<(div_MaxAnalogPresets-NoOfAnalogPresets); i++ )
            {

                for( j= startpreset; j<div_MaxAnalogPresets; j++ )
                {
                    anadat.PresetNumber = j;
                    if( !pgdb_GetByKey(ANALOG_TABLE,(Address)&anadat) ) /* Find if exisits */
                    {
                        startpreset = j;
                        break; /* We found the empty location */
                    }
                }

                pgdb_Initialise (pgdbconst_Analog, (Address) (&anadat));                
                anadat.PresetNumber = startpreset; /* Set the preset number */
                anadat.PreferredStereo = 1;
                pgdb_Add(ANALOG_TABLE,(Address)&anadat );
                TraceDebug(m,"ANALOG_TABLE Addded with preset %d",anadat.PresetNumber);

            }
        }

    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::prins_StartAutomaticInstallation()
    /****************************************************
     * Purpose: Starts automatic installation.
     ****************************************************/
{
    Nat32 errorcode = TM_OK;
    Bool Result;
    TraceDebug(m,"Hsvprins: prins_StartAutomaticInstallation called");

    if( prgInstallationTurnOn )
    {
        FResult ret = err_Ok;
		noOfPresetsFound = 0;	
    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
		
#if( p830_iPresent_CONSTANT )     
    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

        if ( fieldCNI != p830_InvalidRequestId )
        {
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
			TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
        }
        if (fieldNI != p830_InvalidRequestId )
        {
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
	
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
			TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
        }
#endif

#if( 1 )        

        if (fieldVPS != vps_InvalidRequestId)
        {
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
			TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);

        }
#endif
        //ret = feapi_GetRange(WINDOWID,&mRfaMinAmplification,&mRfaMaxAmplification,&errorcode);

        setOffset = 0;
        /* stop the search if tuner is searching*/
        feapi_StopSearch( WINDOWID, &errorcode);/* tun_StopSearch() */
        ASSERT( errorcode == TM_OK );

        installationMode = prins_InstallationModeAutomatic;

        /* initialize flags*/
        installationStopped = FALSE;
        prins_Initialise();

/*  //TODO: listeners
#if( implinsN_iPresent_CONSTANT )
        implinsN_OnEvent( implinsN_OnFrequencyBandSearchStarted );
#endif*/ 
        AllocateMemoryForPresetList();        


        /*CR:BV Audio Mute: Possible to move to start installation - OK */
     /*   if (div_AudioMuteDuringInstall)
        {
            sysctl_SetAudioMute(TRUE);
        }
	*/
        /* To be done at start of installation */
        /* sysctl_SetVideoMute(FALSE);*/

        SetPresetDataIndicator(currentPreset.Channel.AnalogNo,MASK_RECEIVED,FALSE);
        SetPresetDataIndicator(0,MASK_RECEIVED,FALSE);
        installMode = FALSE;

        /* give automatic installation start notifications */
    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
	if(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeVpsPdcAci)
	{
	    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
	}
	
	if(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeAci)
	{
		TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
	}
	
	if(! pgaci_IsAciSupported())
	{
		TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);	 
	}

        /* Find Aci On Current Preset */
        if( ((( euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
                        ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
                    &&( pgaci_IsAciSupported() ) )

          )
        {
		
			txvbi__dcu_Disable( );
                                
			Result = txplf__txacqctrl_Suspend();
			Result = txsvc__tsacqctrl_Suspend();


			Result = txplf__txacqctrl_Reset(0x000100|0x01);//txacqctrl_Prepare|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
			Result = txsvc__tsacqctrl_Reset(0x000100|0x01);//txacqctrl_Prepare|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);

			Result = txplf__txacqctrl_Reset(0x000200|0x01);//(txacqctrl_Execute|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
			Result = txsvc__tsacqctrl_Reset(0x000200|0x01);//(tsacqctrl_Execute|tsacqctrl_ClearStore/*|txsvcms_tsacqctrl_ClearDisplay*/);

        /* Conclude */
			Result = txplf__txacqctrl_Reset(0x000300|0x01);//txacqctrl_Conclude|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
			Result = txsvc__tsacqctrl_Reset(0x000300|0x01);//(tsacqctrl_Conclude|tsacqctrl_ClearStore/*|txsvcms_tsacqctrl_ClearDisplay*/);

            TraceDebug(m,"Hsvprins: Svpaci: %s %d dcu disabled",__FUNCTION__,__LINE__);
			txvbi__dcu_Enable( );
			txsvc__tsacqctrl_Resume();
			txplf__txacqctrl_Resume( );

            TraceDebug(m,"hsvprins:StartAciInstallation");
            pgaci_StartAciInstallation();
            currentPresetAciSearch = TRUE;
            installationState = HsvinsStateCheckAci;
            aciTimeoutStarted = TRUE;
            aciTimeOutCounter = 0;
            pmp_PmpSendAfter( prgInstallationPump
                    ,  insEventAciStoreTimeOut
                    , currentPreset.Channel.AnalogNo
                    , LEAST_COUNT_FOR_ACI_TIMEOUT
                    );
        }
        else
        {
            installationState = HsvinsStateSetFrequency;
            /* Set the tuner frequency to minimum, with finetune enabled */
            if (  SECAM_FIRST && (IS_SECAML_SUPPORTED))
            {
                TraceDebug(m,"hsvprins:feapi_SetTvSystem = tmFe_TvSystemL");
                feapi_SetTvSystem(WINDOWID, tmFe_TvSystemL, &errorcode);
                ASSERT(errorcode == TM_OK);                    

            }
            else
            {
                TraceDebug(m,"hsvprins:feapi_SetTvSystem = tmFe_TvSystemNone");
                feapi_SetTvSystem(WINDOWID, tmFe_TvSystemNone, &errorcode); 
                ASSERT(errorcode == TM_OK);                    

            }

            if( prinsN_iPresent() )
            {
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
            }
            TraceDebug(m,"hsvprins:feapi_SetFreq = %d",freqctl_GetMinFrequency());
       //     feapi_SetFreq(WINDOWID,freqctl_GetMinFrequency(), TRUE, &errorcode);
                feapi_StartSearch( WINDOWID,freqctl_GetMinFrequency(),0,freqctl_GetMaxFrequency(), &errorcode );

				/* ANEESH: HACK: here to perform scanning directly rather than SetFreq,ScanStart as in Fusion */
			installationState = HsvinsStateSearching;
	   ASSERT( errorcode == TM_OK );
            currentPresetAciSearch = FALSE;
        }
        automaticInstallationFirstPass = TRUE;          
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::prins_StopAutomaticInstallation( void )
    /****************************************************
     * Purpose: Stops automatic installation.
     ****************************************************/
{

    TraceDebug(m,"prins_StopAutomaticInstallation");

    if( prgInstallationTurnOn )
    {
#if( 1 )

        if ( fieldCNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
        }
        if (fieldNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
        }              

#endif

#if( 1 )

        if ( fieldVPS != vps_InvalidRequestId )
        {
            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
        }
#endif
        /* stop aci installation */
        if( (((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
                        ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
                    &&(pgaci_IsAciSupported()))
          )
        {
            pgaci_StopAciInstallation();
        }
        installationStopped = TRUE;
        allMemoryFilled = FALSE;
        pmp_PmpSend( prgInstallationPump, insEventStopAutoInstallation, 0 );
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::prins_SkipInstallation( void )
    /****************************************************
     * Purpose: Stops automatic installation.
     ****************************************************/
{
    TraceDebug(m,"prins_SkipInstallation");
    if( prgInstallationTurnOn )
    {
#if( p830_iPresent_CONSTANT )

        if ( fieldCNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
        }
        if (fieldNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
        }              

#endif

#if( 1 )

        if ( fieldVPS != vps_InvalidRequestId )
        {
            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
        }
#endif
        /* stop aci installation */
        if( (((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
                        ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
                    &&(pgaci_IsAciSupported()))
          )
        {
            pgaci_StopAciInstallation();
        }
        allMemoryFilled = FALSE;
        pmp_PmpSend( prgInstallationPump, insEventSkipInstallation, 0 );
    }
}



/*****************************************************************/
void CHsvPresetInstallation_m_Priv::prins_SetManualFrequency( int frequency, int offset, Bool finetune ) 
    /******************************************************************
     * Purpose: Sets Frequency and Offset
     ******************************************************************/
{

    TraceDebug(m,"prins_SetManualFrequency: freq = %d, offset = %d, finetune = %d", frequency, offset, finetune);

    if( prgInstallationTurnOn )
    {
        if(!((frequency <= freqctl_GetMaxFrequency()) || (frequency >= freqctl_GetMinFrequency())))
        {
            ASSERT((frequency <= freqctl_GetMaxFrequency()) && (frequency >= freqctl_GetMinFrequency()));
            frequency = 3248;
        }
        setFrequencyManual = TRUE;
        setFrequency = frequency;
        setOffset = offset;
        fineTune = finetune;
    }
} 

/*****************************************************************/
void CHsvPresetInstallation_m_Priv::prins_GetManualFrequency( int *frequency, int *offset, Bool *finetune)
    /******************************************************************
     * Purpose: Gets Frequency, Offset and Fine Tune
     ******************************************************************/
{
    if(prgInstallationTurnOn)
    {
        *frequency = setFrequency;
        *offset = setOffset;
        *finetune = fineTune;

        TraceDebug(m,"prins_GetManualFrequency returning: freq = %d, offset = %d, finetune = %d", *frequency, *offset, *finetune);
    }
}

/*****************************************************************/
void CHsvPresetInstallation_m_Priv::prins_SetManualChannel( int channel , Bool finetune) 
    /******************************************************************
     * Purpose: Sets Channel
     ******************************************************************/
{

    if( prgInstallationTurnOn )
    {
        if(div_SorCChannelSupported)
        {
            setChannelManual = TRUE;
            setChannel = channel;
            fineTune = finetune;
        }
        else
        {
            ASSERT(!"S or C channel mode not supported");
        }
    }    

}

/*****************************************************************/
void CHsvPresetInstallation_m_Priv::prins_GetManualChannel( int *channel, Bool *finetune)
    /******************************************************************
     * Purpose: Gets Channel and Fine Tune
     ******************************************************************/
{
    if(prgInstallationTurnOn)
    {
        *channel  = setChannel;       
        *finetune = fineTune;
    }
}


/******************************************************************/
void CHsvPresetInstallation_m_Priv::prins_SetManualInstallationMode(int mode)
    /******************************************************************
     * Purpose: Sets ManualInstallation Mode
     ******************************************************************/
{
    if(prgInstallationTurnOn)
    {
        TraceDebug(m,"prins_SetManualInstallationMode : mode = %d", mode);

        if(div_SorCChannelSupported)
        {
            manualInstallationMode = mode;
        }
        else
        {
            if((mode == prins_ManualInstallationModeSChannel) || (mode == prins_ManualInstallationModeSChannel))
            {
                ASSERT(!"S or C channel not supported");
            }
            else
            {
                manualInstallationMode = mode;
            }
        }
    }
}

/******************************************************************/
int CHsvPresetInstallation_m_Priv::prins_GetManualInstallationMode(void)
    /******************************************************************
     * Purpose: Sets ManualInstallation Mode
     ******************************************************************/
{
    TraceDebug(m,"prins_GetManualInstallationMode returning: mode = %d", manualInstallationMode);
    return manualInstallationMode;
}

/******************************************************************/
Bool CHsvPresetInstallation_m_Priv::prins_IsManualInstallationModeSupported(int mode)
    /******************************************************************
     * Purpose: Sets ManualInstallation Mode
     ******************************************************************/
{
    Bool returnVal;
    switch(mode)
    {

        case prins_ManualInstallationModeFrequency:
            returnVal = TRUE;
            break;
        case prins_ManualInstallationModeSChannel:
        case prins_ManualInstallationModeCChannel:
            returnVal = div_SorCChannelSupported;
            break;
        default :
            ASSERT(0);
            returnVal = FALSE;
            break;
    }
    TraceDebug(m,"prins_IsManualInstallationModeSupported returning: mode = %d, retval = %d", mode, returnVal);
    return returnVal;
}

void CHsvPresetInstallation_m_Priv::prins_StartManualInstallation()
{
         pmp_PmpSend( prgInstallationPump, EventStartManualInstallation, 0 );
}

/******************************************************************/
void CHsvPresetInstallation_m_Priv::mStartManualInstallation()
    /******************************************************************
     * Purpose: Starts manual installation.
     ******************************************************************/
{
    Nat32 errorcode = TM_OK;
    tmFe_TvSystem_t tvSystem;
    UInt32 freq;
    FResult ret = err_Ok;

    TraceDebug(m,"prins_MStartManualInstallation called");
    if(prgInstallationTurnOn)
    {
#if( p830_iPresent_CONSTANT )

        if ( fieldCNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
        }
        if (fieldNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
        }
#endif        

#if(1 )       
        if (fieldVPS != vps_InvalidRequestId)
        {
            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
        }
#endif
        //ret = feapi_GetRange(WINDOWID,&mRfaMinAmplification,&mRfaMaxAmplification,&errorcode);

        /* stop the tuner search*/
        if(installationMode != prins_InstallationModeManual)
        {
            feapi_StopSearch( WINDOWID, &errorcode); 
			sleep(3);
            ASSERT( errorcode == TM_OK );
        }
        /* CR:BV Audio Mute: Can be moved to Start Installation - OK */
        if (div_AudioMuteDuringInstall)
        {
            sysctl_SetAudioMute(TRUE);
        }
        /* CR:BV Video Mute: Can be moved to Start Installation - OK */
        /* Manual Installation Dont Touch */
        /* disable screen blanking during frequency tuning */
        sysctl_SetVideoMute(FALSE);

        /* initialise flags */
        fineTuneSorC = FALSE;
        installationStopped = FALSE;
        installationMode = prins_InstallationModeManual;
        currentPreset.Channel.AnalogNo    = 1;
        noOfPresetsFound = 0;
        noOfNewPresetsFound = 0;
        manualInstallationPendingStore = FALSE;
        statusMessageFound = FALSE;
        manualStationFoundFlag = FALSE;
        HndlSetTunerFreqNtf = FALSE;

        changePresetAttrib = TRUE;
        SetDataIndicator( &miPreset,MASK_RECEIVED,FALSE);

        currentPkt830Ni = 0;
        currentPkt830Cni = 0;
        statusMessageFound = FALSE;

        str_strncpy(miPreset.Name, DEFAULT_ANALOG_PRESET_NAME, DEFAULT_ANALOG_PRESET_LENGTH);
        str_strncpy(tempStr, DEFAULT_ANALOG_PRESET_NAME, DEFAULT_ANALOG_PRESET_LENGTH);

        country = sysset_GetSystemCountry();
        TraceDebug(m,"prins_StartManualInstallation %d manualInstallationMode=%d",__LINE__,manualInstallationMode);

        switch( manualInstallationMode )
        {
            case prins_ManualInstallationModeFrequency:
                installMode = FALSE;
				TraceDebug(m,"Hsvprins prins_StartManualInstallation %d setFrequencyManual = %d",__LINE__,setFrequencyManual);

                /* manual set frequency then tune to the specified frequency, otherwise start search from current freq */
                if( setFrequencyManual )
                {
					TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                    installationState = HsvinsStateSetFrequency;
                    if ( div_AttenuatorDetectionInInstall )
                    {
                        //feapi_Set( WINDOWID, mRfaMaxAmplification, &errorcode );

                    }

                    if( prinsN_iPresent() )
                    {
                        prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                    }
					TraceDebug(m,"prins_StartManualInstallation %d %d %d",__LINE__,setFrequency,setOffset);

                    feapi_SetFreq( WINDOWID, setFrequency+setOffset, fineTune, &errorcode );
                    ASSERT( errorcode == TM_OK );

                    if(0)
                    {
						TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                        feapi_GetTvSystem(WINDOWID, &tvSystem, &errorcode);
                        ASSERT( errorcode == TM_OK );

                        if(( tvSystem != tmFe_TvSystemL ) && ( tvSystem != tmFe_TvSystemL1))
                        {
							TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                            feapi_SetTvSystem(WINDOWID, tmFe_TvSystemNone, &errorcode);
                            ASSERT( errorcode == TM_OK );
                        }

                    }
                    fineTuneSorC = TRUE;
                }
                else
                {
                    fineTune = TRUE;
                    installationState = HsvinsStateSearching;
                    feapi_GetTvSystem(WINDOWID, &tvSystem, &errorcode );
                    ASSERT(errorcode == TM_OK);
					TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                    if(( tvSystem == tmFe_TvSystemL ) ||( tvSystem == tmFe_TvSystemL1))
                    {
						TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                        if( mGetFrequencySearchDirection() )
                        {
							TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                            if (div_ManualSearchWithWrapAround)
                            {
								TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                feapi_GetFreq(WINDOWID, &freq, &errorcode);
                                if( prinsN_iPresent() )
                                {
									TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault|tmFe_SmPositiveModulation | TvSystemsearch, freq);                                                                                 
                            }
                            else
                            {
                                if( prinsN_iPresent() )
                                {
									TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
								TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault|tmFe_SmPositiveModulation | TvSystemsearch, freqctl_GetMaxFrequency() );
                            }
                        }
                        else
                        {
							        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                            if (div_ManualSearchWithWrapAround)
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                feapi_GetFreq(WINDOWID,&freq, &errorcode);
                                if( prinsN_iPresent() )
                                {
									        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | tmFe_SmPositiveModulation | TvSystemsearch | tmFe_SmDirectionDown, freq);                                    
                            }
                            else
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                if( prinsN_iPresent() )
                                {
				  TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | tmFe_SmPositiveModulation | TvSystemsearch | tmFe_SmDirectionDown, freqctl_GetMinFrequency());                                    
                            }
                        }
                    }
                    else
                    {
						        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                        if(mGetFrequencySearchDirection())
                        {
							        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                            if (div_ManualSearchWithWrapAround)
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                feapi_GetFreq( WINDOWID, &freq, &errorcode);
                                if( prinsN_iPresent() )
                                {
                                    feapi_GetFreq(WINDOWID,&freq, &errorcode);
                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | TvSystemsearch, freq);                                    

                            }
                            else
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                if( prinsN_iPresent() )
                                {
                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | TvSystemsearch, freqctl_GetMaxFrequency());                                    
                            }
                        }
                        else
                        {
							        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                            if (div_ManualSearchWithWrapAround)
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                feapi_GetFreq(WINDOWID, &freq, &errorcode);
                                if( prinsN_iPresent() )
                                {
                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | TvSystemsearch | tmFe_SmDirectionDown, freq);
                            }
                            else
                            {
								        TraceDebug(m,"prins_StartManualInstallation %d",__LINE__);

                                if( prinsN_iPresent() )
                                {
                                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                                }
                                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | TvSystemsearch | tmFe_SmDirectionDown, freqctl_GetMinFrequency());                                    
                            }
                        }
                    }
                }
                break;

            case prins_ManualInstallationModeSChannel:
                if(div_SorCChannelSupported)
                {
                    SPointSSearch = StartChannelSearch( tmFe_TableEuropeS );
                }
                else
                {
                    ASSERT(!"S or C channel mode not suported");
                }
                break;

            case prins_ManualInstallationModeCChannel:
                if(div_SorCChannelSupported)
                {
                    SPointCSearch = StartChannelSearch( tmFe_TableEuropeC );
                }
                else
                {
                    ASSERT(!"S or C channel mode not suported");
                }
                break;

            default:
                ASSERT( FALSE );
                break;
        }
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::prins_StopManualInstallation()
    /****************************************************
     * function to stop the manual installation
     *****************************************************/
{
    UInt32 currentFreq;
    Nat32 errorcode = TM_OK;

    if( prgInstallationTurnOn )
    {
#if( p830_iPresent_CONSTANT )

        if ( fieldCNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
        }
        if (fieldNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
        }
#endif

#if(1 )        

        if ( fieldVPS != vps_InvalidRequestId )
        {
            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
        }
#endif 
        setFrequencyManual = FALSE;
	    TraceDebug(m,"Hsvprins  %s  %d",__FUNCTION__,__LINE__);		
        setChannelManual = FALSE;
        installationStopped = TRUE;
        feapi_GetFreq( WINDOWID, &currentFreq, &errorcode );
        ASSERT( errorcode == TM_OK );

        if (installationMode == prins_InstallationModeManual)
        {
            switch( manualInstallationMode )
            {

                case prins_ManualInstallationModeFrequency:
                    InstallationCompleted();
                    break;

                case prins_ManualInstallationModeSChannel:
                case prins_ManualInstallationModeCChannel:
                    if(div_SorCChannelSupported)
                    {
                        InstallationCompleted();
                    }
                    else
                    {
                        ASSERT(!"S or C channel not supported");
                    }
                    break;
                default:
                    break;                
            }
        }
    }
}

Bool CHsvPresetInstallation_m_Priv::prins_StartFrequencySearch(void)
{
    Bool retval = FALSE;
    if(rins_GetInstallationMode() == rins_InstallationModeManual)
    {
        prins_StartManualInstallation();            
        retval = TRUE;
    }
    return retval;
}


void CHsvPresetInstallation_m_Priv::prins_StoreManualInstallationValues( HsvChannel channel )
{
    if(1 /*pgdat_IsChannelInstalled (&channel)*/)
    {
        StoreManualInstallationValues(channel);
    }  
    else

    {
        /* Ideally you should have used the previous function boss
           Interface tek se pada nahi kya ? ;-) !! */
        /*Illegal Function Call. Storing this way not supported for new presets*/
        instutil_LogError( log_SoftErr, INS_COMMAND_NOT_ALLOWED ); /*log the error */
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::StoreManualInstallationValues( HsvChannel channel )
    /****************************************************
     * function to store a preset in the NVM during manual 
     * installation
     *****************************************************/
{

    UInt32 freq;
    tmFe_TvSystem_t tvsys;
    Nat32 errorcode = TM_OK;
    Int32     amp=0;
	HsvPgdatAnalogData   tmpanadat;
	HsvPgdatPresetData 	 tmppresetdat;
	
    if(prgInstallationTurnOn)
    {
        errorcode = feapi_GetFreq( WINDOWID, &ManualInstallFrequency, &errorcode );
		TraceNotice (m, "ANALOG: ManualInstallFreq %d ", ManualInstallFrequency);
        ASSERT( errorcode == TM_OK ); 


        presetNumberStored = channel.Channel.AnalogNo;

        currentPreset = channel;
        lastPresetFound = channel;

        if( mRfaMinAmplification < 0) 
        {
            //feapi_Get( WINDOWID, &amp, &errorcode );
            ASSERT ( errorcode == TM_OK );

            if( amp == mRfaMinAmplification )
            {
                SetDataIndicator(&miPreset,MASK_ATTENUATOR,TRUE);
            }

            else if( amp == mRfaMaxAmplification)
            {
                SetDataIndicator(&miPreset,MASK_ATTENUATOR,FALSE);
            }
            else
            {
                /*Do nothing*/
            }
            if(pgdat_IsAttributeSupported(pgdat_BoolAgcInstalled))
            {
                pgdat_StoreChannelDataBool (channel,pgdat_BoolAgcInstalled,TRUE);
            }
        }
        if(( installationMode == prins_InstallationModeNone )
                ||(installationMode == prins_InstallationModeImplicit))
        {
            /* Get the current frequency and tvSystem */
            installationStopped = FALSE;
			    TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

            miPreset.Frequency = ManualInstallFrequency;
            feapi_GetTvSystem( WINDOWID, &tvsys, &errorcode);
            ASSERT( errorcode == TM_OK );
            miPreset.tvSystem = tvsys;
            /*miPreset.tvSystem  = tun_GetTvSystem();*/

            miPreset.colorSystem = (TvColorSystem)col_GetColorSystem();
            installationMode = prins_InstallationModeManual;
            SetDataIndicator(&miPreset,MASK_RECEIVED,FALSE);
            installationState = HsvinsStateNone;
            noOfPresetsFound =1;
            if(!(implicitInstRequired))
            {
                manualStationFoundFlag = TRUE;
                changePresetAttrib = FALSE;
            }
            else
            {
                implicitInstRequired = FALSE;
                manualStationFoundFlag = FALSE;
                changePresetAttrib = TRUE;
            }

            /* Start txt decoding and wait for TXT information */
            manualInstallationPendingStore = TRUE;
            if( pgdat_IsAttributeSupported(pgdat_IntTvSystem) )
            {
                pgdat_StoreChannelDataInt (channel, pgdat_IntTvSystem, ConvertFromPlatformTvSystem((tmFe_TvSystem_t)miPreset.tvSystem));
                TraceInfo(m,"PlfPreset = %d, TvSystem = %d", channel.Channel.AnalogNo, miPreset.tvSystem);
            }
            if( pgdat_IsAttributeSupported(pgdat_IntColoursystem) )
            {
                pgdat_StoreChannelDataInt (channel, pgdat_IntColoursystem, miPreset.colorSystem );
            }
			TraceNotice (m, "Const for Freq %d Supported %d Freq %d ", pgdat_IntFrequency, pgdat_IsAttributeSupported(pgdat_IntFrequency), (miPreset.Frequency));
            if( pgdat_IsAttributeSupported(pgdat_IntFrequency) )
            {
				TraceNotice (m,"Frequency getting saved for Preset %d ", channel.Channel.Digit);
                pgdat_StoreChannelDataInt (channel, pgdat_IntFrequency, ((miPreset.Frequency * 1000)/16) );
					TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

					HsvPgdatPresetData presetdata;
                    presetdata.PresetNumber = (Int16 )channel.Channel.AnalogNo;
                    presetdata.Type         =  HsvAnalog; 
              if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdata))
              {
                /* Work Around for PR https://jira.tpvision.com/browse/AN-53488  */
			        HsvPgdatAnalogData   analogdat;
                    analogdat.PresetNumber    =   presetdata.AnalogTablePreset;	
                if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&analogdat))
                {
                    presetdata.Frequency = ((miPreset.Frequency * 1000)/16);
                    pgdb_Update(PRESET_TABLE, (Address) &presetdata);
                }
              }

                TraceInfo(m,"hsvprins %d %s  PlfPreset = %d, Frequency = %d",  __LINE__,__FUNCTION__,channel.Channel.AnalogNo, miPreset.Frequency);

            }
            if ( div_NameExtractionDuringImplicitManInstall )
            {
						    TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

                if(!RequestVpsP830(&miPreset))
                {
                    /* vps or pkt830 intf not connected, then store the data*/
                    StoreDataEx(&miPreset,currentPreset, TRUE);
                }
            }
            else
            {
						    TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

                StoreDataEx(&miPreset,currentPreset, TRUE);
            }
        }
        else
        {
            if((!GetDataIndicator(&miPreset,MASK_RECEIVED)) && fineTune)
            {
                manualInstallationPendingStore = TRUE;
                feapi_GetFreq( WINDOWID, &freq, &errorcode );
                ASSERT( errorcode == TM_OK );
                miPreset.Frequency = freq;
                feapi_GetTvSystem( WINDOWID, &tvsys, &errorcode);
                ASSERT( errorcode == TM_OK );
                miPreset.tvSystem = tvsys;
			    TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

                /*manualStationFoundFlag*/

                /* fixme for ResetChannel */
                {   /* This stupid piece of code is just doing reset channel */
                    HsvPgdatPresetData presetdat;
                    presetdat.PresetNumber = (Int16 )channel.Channel.AnalogNo;
                    presetdat.Type         =  HsvAnalog; 
                    if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat))
                    {   /* Query for frequency value and store back in Preset List */
                        HsvPgdatAnalogData   anadat;
                        anadat.PresetNumber    =   presetdat.AnalogTablePreset;

                        if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&anadat))
                        {
                            //pgdb_Initialise (ANALOG_TABLE, (Address)&anadat);                            
                            //anadat.PresetNumber = presetdat.AnalogTablePreset;
                            pgdb_Update(ANALOG_TABLE, (Address)&anadat);
                        }
                    }
                }

                if( pgdat_IsAttributeSupported(pgdat_BoolChannelVirgin) )
                {
                    pgdat_StoreChannelDataBool (channel, pgdat_BoolChannelVirgin,FALSE);
                }
                if( pgdat_IsAttributeSupported(pgdat_IntTvSystem) )
                {
                    pgdat_StoreChannelDataInt (channel, pgdat_IntTvSystem,ConvertFromPlatformTvSystem( (tmFe_TvSystem_t)miPreset.tvSystem) );

                }
                if( pgdat_IsAttributeSupported(pgdat_IntFrequency) )
                {
                    pgdat_StoreChannelDataInt (channel, pgdat_IntFrequency, ((miPreset.Frequency*1000)/16)  );

                    TraceInfo(m,"PlfPreset = %d, Frequency = %d", channel.Channel.AnalogNo, miPreset.Frequency);

                }
                if( pgdat_IsAttributeSupported(pgdat_BoolDeTuned) )
                {
                    if (fineTune)
                    {
                        pgdat_StoreChannelDataBool (channel, pgdat_BoolDeTuned, FALSE );
                    }
                    else
                    {
                        pgdat_StoreChannelDataBool ( channel, pgdat_BoolDeTuned, TRUE );
                    }
                }
            }
            else
            {
			    TraceInfo(m,"hsvprins %d %s", __LINE__,__FUNCTION__);

                StoreDataEx(&miPreset,currentPreset, TRUE); /* All Parameters pertaining to a preset are received and
                                                               and the fineTune is not done */
            }
        }

		tmppresetdat.PresetNumber =  (Int16 )channel.Channel.AnalogNo;
		tmppresetdat.Type         =  HsvAnalog; 
		if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat))
		{   
			/* Query for frequency value and store back in Preset List */
			tmpanadat.PresetNumber    =   tmppresetdat.AnalogTablePreset;
	        if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&tmpanadat))
			{
				if( (tmpanadat.ChannelName[0] == 0) || ( (tmpanadat.ChannelName[0] == ' ') && (tmpanadat.ChannelName[1] == ' ') && (tmpanadat.ChannelName[2] == ' ')) )
				{
					memo_memcpy(tmpanadat.ChannelName, instutil_AsciiToUnicode(defaultName, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength);
					pgdb_Update(ANALOG_TABLE, (Address)&tmpanadat);
				}
			}
		}
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::implins_StartImplicitInstallation( HsvChannel channel )
    /****************************************************
     * starts implicit installation
     *****************************************************/
{
    if((prgInstallationTurnOn)
            &&(installationMode != prins_InstallationModeAutomatic)
            &&(installationState != HsvinsStateAcquiringTxt)
      )
    {
        StartBackgroundPresetUpdation(channel,FALSE);        /*update name*/
    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::implins_StopImplicitInstallation( void )
    /****************************************************
     * function to stop implicit installation
     *****************************************************/
{
    if((prgInstallationTurnOn)
            &&(installationMode != prins_InstallationModeAutomatic)
            &&(installationMode != prins_InstallationModeManual)
      )
    {
        installationStopped = TRUE;
        InstallationCompleted();
    }
}


/****************************************************/
Bool CHsvPresetInstallation_m_Priv::prins_StartBackgroundCniUpdation(HsvChannel channel )
    /****************************************************
     * starts back ground CNI updation
     *****************************************************/
{
    Bool ret = FALSE;
    if( prgInstallationTurnOn )
    {
#if( p830_iPresent_CONSTANT )

        if ( fieldCNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldCNI );
            fieldCNI = p830_InvalidRequestId;
        }
        if (fieldNI != p830_InvalidRequestId )
        {
            p830_UnRequestDataFields ( fieldNI );
            fieldNI = p830_InvalidRequestId;
        }
        if (fieldSTATUS != p830_InvalidRequestId)
        {
            p830_UnRequestDataFields ( fieldSTATUS );
            fieldSTATUS = p830_InvalidRequestId;
        }
#endif

#if( 1 )

        if (fieldVPS != vps_InvalidRequestId)
        {
            vps_UnRequestDataFields ( fieldVPS );
            fieldVPS = vps_InvalidRequestId;
        }
#endif

        ret = StartBackgroundPresetUpdation(channel,TRUE);        /*update only CNI*/
    }
    return(ret);
}

/****************************************************/
HsvChannel CHsvPresetInstallation_m_Priv::prins_GetPresetSearchingFor( void )
    /****************************************************
     * Get the current preset
     *****************************************************/
{
    ASSERT(prgInstallationTurnOn);
    return( currentPreset );
}

/****************************************************/
HsvChannel CHsvPresetInstallation_m_Priv::prins_GetLastFoundPreset( void )
    /****************************************************
     * gets the last found preset
     *****************************************************/
{
    Nat32 errorcode = TRUE;
    UInt32 returnValue=0;
    HsvChannel chan;
    int lastPresetFrequency;

    if( prgInstallationTurnOn )
    {
        if ( (div_SorCChannelSupported) && (installationMode == prins_InstallationModeManual) )
        {
            lastPresetFrequency = miPreset.Frequency;
            if( (manualInstallationMode == prins_ManualInstallationModeSChannel) )
            {
                feapi_Freq2Chan( WINDOWID, lastPresetFrequency, tmFe_TableEuropeS, &returnValue, &errorcode ); 
            }
            else if( (manualInstallationMode == prins_ManualInstallationModeCChannel) )
            {
                feapi_Freq2Chan( WINDOWID, lastPresetFrequency, tmFe_TableEuropeC, &returnValue, &errorcode ); 
            }
            else
            {
                returnValue = lastPresetFound.Channel.AnalogNo;
            }
        }
        else
        {
            returnValue = lastPresetFound.Channel.AnalogNo;
        }
    }
    chan.Type = HsvAnalog;
    chan.Channel.AnalogNo = returnValue;

    return( chan );
}

/****************************************************/
int CHsvPresetInstallation_m_Priv::prins_GetLastFoundPresetFrequency( void )
    /****************************************************
     * gets the frequency of the last found the preset
     *****************************************************/
{
    int freq = 0;

    ASSERT(prgInstallationTurnOn);

    switch(installationMode)
    {
        case prins_InstallationModeAutomatic:
            /* preset data should have allocated memory*/

#if(mem_iPresent_CONSTANT)            
            if (PresetData)
            {
                freq = PresetData[lastPresetFound.Channel.AnalogNo].Frequency;
            }
            else
            {
                ASSERT(!"memory not allocated ");
            }
#else           
            freq = PresetData[lastPresetFound.Channel.AnalogNo].Frequency;
#endif            
            break;

        case prins_InstallationModeManual:
        case prins_InstallationModeImplicit:
        case prins_InstallationModeBackground:
            freq = miPreset.Frequency;
            break;
        default:
            ASSERT(!"Invalid state");
            break;
    }
    return(freq);
}

/****************************************************/
char* CHsvPresetInstallation_m_Priv::prins_GetLastFoundPresetName( void )
    /****************************************************
     * gets the name of the last found the preset
     *****************************************************/
{
    ASSERT(prgInstallationTurnOn);
    switch(installationMode)
    {
        case prins_InstallationModeAutomatic:

#if(mem_iPresent_CONSTANT)        
            if ( PresetData )
            {
                str_strncpy( tempStr, PresetData[lastPresetFound.Channel.AnalogNo].Name, div_PresetNameLength);
            }
            else
            {
                ASSERT(!"memory not allocated ");
            }

#else           
            str_strncpy( tempStr, PresetData[lastPresetFound.Channel.AnalogNo].Name, div_PresetNameLength);
#endif
            break;

        case prins_InstallationModeManual:
        case prins_InstallationModeImplicit:
        case prins_InstallationModeBackground:
            str_strncpy( tempStr, miPresetName, div_PresetNameLength);
            break;
        default:
            ASSERT(!"Invalid state");
            break;
    }
    return (tempStr);
}

int CHsvPresetInstallation_m_Priv::prins_GetNumberOfAnalogPresetsAdded(void)
{
    ASSERT(prgInstallationTurnOn);
    if ( prgInstallationTurnOn )
    {    
        if ( noOfNewPresetsFound < div_MaxAnalogPresets )
        {
            return( noOfNewPresetsFound );
        }
        else
        {
            return ( div_MaxAnalogPresets -1 ); 
            /* This else is added to solve the PR blr03mgr#9858 */
        }
    }
    return 0;
}
/****************************************************/
int CHsvPresetInstallation_m_Priv::prins_GetNumberOfAnalogPresetsFound( void )
    /****************************************************
     * gets the number of found presets
     *****************************************************/
{
    ASSERT(prgInstallationTurnOn);
    if ( prgInstallationTurnOn )
    {    
        if ( noOfPresetsFound < div_MaxAnalogPresets )
        {
            return( noOfPresetsFound );
        }
        else
        {
            return ( div_MaxAnalogPresets -1 ); 
            /* This else is added to solve the PR blr03mgr#9858 */
        }
    }
    return 0;
}


/******************************************
 * Notifies
 ******************************************/

/* HndlSetTunerFreqNtf, this case has to be handled only for StationFound and StationNotFound notifications
   for the rest of the notification no need to handle the plf notification, otherwise state machine will get affected */

/* Tuner Notifys */
void CHsvPresetInstallation_m_Priv::feapiN_OnStationFound()
{
	Bool Result;
    ASSERT( prgInstallationTurnOn );
    TraceDebug(m," hsvprins: %s ",__FUNCTION__);
    if ( prgInstallationTurnOn && (rins_GetInstallationState() == rins_StAnalog ))
    {
        TraceDebug(m," hsvprins: %s %d  installationState %d",__FUNCTION__,__LINE__ ,installationState);
		 
        pmp_PmpSend( prgInstallationPump, EventfeapiNOnStationFound, (Nat32)NULL);
	txvbi__dcu_Disable( );
		
	Result = txplf__txacqctrl_Suspend();
        Result = txsvc__tsacqctrl_Suspend();


        Result = txplf__txacqctrl_Reset(0x000100|0x01);//txacqctrl_Prepare|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
        Result = txsvc__tsacqctrl_Reset(0x000100|0x01);//txacqctrl_Prepare|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);

        Result = txplf__txacqctrl_Reset(0x000200|0x01);//(txacqctrl_Execute|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
        Result = txsvc__tsacqctrl_Reset(0x000200|0x01);//(tsacqctrl_Execute|tsacqctrl_ClearStore/*|txsvcms_tsacqctrl_ClearDisplay*/);

        /* Conclude */
        Result = txplf__txacqctrl_Reset(0x000300|0x01);//txacqctrl_Conclude|txacqctrl_ClearStore/*|txadoc_txacqctrl_ClearDisplay*/);
        Result = txsvc__tsacqctrl_Reset(0x000300|0x01);//(tsacqctrl_Conclude|tsacqctrl_ClearStore/*|txsvcms_tsacqctrl_ClearDisplay*/);

	TraceDebug(m,"Hsvprins: Svpaci: %s %d dcu disabled",__FUNCTION__,__LINE__);
	txvbi__dcu_Enable( );
	txsvc__tsacqctrl_Resume();
	txplf__txacqctrl_Resume( );
	TraceDebug(m,"Hsvprins: Svpaci: %s %d dcu_Enable enabled",__FUNCTION__,__LINE__);

    }
}

void CHsvPresetInstallation_m_Priv::mfeapiNOnStationFound(void)
{
    Nat32 errorcode = TM_OK;
    UInt32 freq;
    tmFe_TvSystem_t tvSystem;   
    	TraceDebug(m," hsvprins: %s %d installationState = %d HndlSetTunerFreqNtf= %d",__FUNCTION__,__LINE__,installationState,HndlSetTunerFreqNtf);


        if((installationState == HsvinsStateSearching) || (installationState == HsvinsStateSetFrequency))
        {
                TraceDebug(m," hsvprins: %s %d ",__FUNCTION__,__LINE__);

            feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode );
			        TraceDebug(m," hsvprins: %s %d tvSystem=%d ",__FUNCTION__,__LINE__,tvSystem);

            if( tmFe_TvSystemL == tvSystem  )
            {              
                pmp_PmpSendAfter( WaitForColorSystemPump, 0, 0, 800);
            }
            else
            {
                stationFoundFlag = TRUE;
                feapi_GetFreq( WINDOWID, &freq, &errorcode);
                ASSERT(freq);
				TraceDebug(m," hsvprins: %s %d  frequency=%d",__FUNCTION__,__LINE__,freq);
                if( prinsN_iPresent() )
                {
                  //  prinsN_OnEvent( prinsN_EventTuningStationFound, HSVPRINS_INVALID_VALUE );
                }
                pmp_PmpSend( prgInstallationPump, insEventStationFound, freq );
            }
        }
        else if( /*HndlSetTunerFreqNtf && */( installationState == HsvinsStateCheckAci || installationState == HsvinsStateNone ) )
        {
            HndlSetTunerFreqNtf = FALSE;

            if( prinsN_iPresent() )
            {
              //  prinsN_OnEvent( prinsN_EventTuningStationFound, HSVPRINS_INVALID_VALUE );
            }
        }
}

void CHsvPresetInstallation_m_Priv::feapiN_OnStationNotFound()
{
    ASSERT( prgInstallationTurnOn );
    TraceDebug(m," hsvprins: %s ",__FUNCTION__);
    if ( prgInstallationTurnOn && (rins_GetInstallationState() == rins_StAnalog))
    {
        pmp_PmpSend( prgInstallationPump, EventfeapiNOnStationNotFound, (Nat32)NULL );
    }
}

void CHsvPresetInstallation_m_Priv::mfeapiNOnStationNotFound(void)
{
    if((installationState == HsvinsStateSearching) || (installationState == HsvinsStateSetFrequency))
    {
        if ( prinsN_iPresent() )
        {
            prinsN_OnEvent( prinsN_EventTuningStationNotFound, HSVPRINS_INVALID_VALUE );
        }
        TraceDebug(m," hsvprins: %d::pmpsend of stationnotfound",__LINE__);
        pmp_PmpSend( prgInstallationPump, insEventStationNotFound, 0 );
    }

    else if( HndlSetTunerFreqNtf && ( installationState == HsvinsStateCheckAci || installationState == HsvinsStateNone ) )
    {
        HndlSetTunerFreqNtf = FALSE;
		TraceDebug(m," hsvprins: %s %d",__FUNCTION__,__LINE__);
        if( prinsN_iPresent() )
        {
            prinsN_OnEvent( prinsN_EventTuningStationNotFound, HSVPRINS_INVALID_VALUE );
        }
    }
}

void CHsvPresetInstallation_m_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem )
{
    ASSERT( prgInstallationTurnOn );

    TraceDebug(m," hsvprins: %s tvSystem = %d. Processing this later",__FUNCTION__,tvSystem);
	/* Sending this notification and handling the conditions seperately. This is done because this notificaiton is coming
		before the StationFound is completely processing. This leads to some flags in below check to FAIL. 
		Hence TV System even though detected, is missed in MW. Hence this is treated as case of TVsystemDetection Timeout. 
		To avoid this, handling this message also in PumpHandler and then making sure all the variables in StationFound are set
		before processing TvsystemDetected. */
	pmp_PmpSendAfter( prgInstallationPump, EventDelayedTvSystemDetected, tvSystem, 800);

}

void CHsvPresetInstallation_m_Priv::OnTvSystemDetectedHadler( tmFe_TvSystem_t tvSystem )
{
    ASSERT( prgInstallationTurnOn );

    TraceDebug(m," hsvprins: %s tvSystem = %d",__FUNCTION__,tvSystem);
	
    if( (rins_GetInstallationState() == rins_StAnalog) && TvSystemsearch && stationFoundFlag && (installationState != HsvinsStateCheckAci) && 
            (installationState != HsvinsStateNone) )
    {
        stationFoundFlag = FALSE;
	    TraceDebug(m," hsvprins: %s tvSystem = %d deleyed by 800 ms",__FUNCTION__,tvSystem);
		pmp_PmpSendAfter( prgInstallationPump, insEventTvSystemFound, currentPreset.Channel.AnalogNo, 800);
    }
    UNUSED(tvSystem);
	
}


void CHsvPresetInstallation_m_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength )
{
    TraceDebug(m," hsvprins: %s ",__FUNCTION__);
    if((rins_GetInstallationState() == rins_StAnalog) && prgInstallationTurnOn & (rins_InsVssm == ssm) )
    {
        if ( !HndlSetTunerFreqNtf )
        {       
            pmp_PmpSend( prgInstallationPump, insEventSignalStrengthDetectionInProgess, currentPreset.Channel.AnalogNo );
        }
    }
    UNUSED(strength);
}

void CHsvPresetInstallation_m_Priv::feapiN_OnAfcFreqChanged( Nat32 freq )
{
    UNUSED(freq);
    pmp_PmpSend( prgInstallationPump, insEventAfcFreqChanged, 0 );
}

int CHsvPresetInstallation_m_Priv::mGetTunerFrequency(void)
{
    UInt32 frequency = -1;
    Nat32 errorcode;

    ASSERT(prgInstallationTurnOn);

    feapi_GetFreq(WINDOWID, &frequency, &errorcode);
    ASSERT( errorcode == TM_OK );

    return (int)frequency;
}

int CHsvPresetInstallation_m_Priv::mGetFrequencySearchDirection(void)
{
    /* Naresh: stubbing for the moment, look if we really need this */
    return TRUE;
}

/*Txplf notify */

/****************************************************/
void CHsvPresetInstallation_m_Priv::resetN_OnResetEnd( void )
    /****************************************************
     * teletext reset end notification
     *****************************************************/
{
    if((installationMode != prins_InstallationModeNone)
            &&(installationState != HsvinsStateCheckAci)
      )
    {
        pmp_PmpSend(prgInstallationPump, insEventTxplfResetOver, currentPreset.Channel.AnalogNo);
    }

}
/*Aci notify */
/****************************************************/
void CHsvPresetInstallation_m_Priv::pgaciN_OnAciInstallationCompleted ( Bool success )
    /****************************************************
     * notification that aci instalation is completed
     *****************************************************/
{
    TraceDebug(m," hsvprins: %s %d",__FUNCTION__,__LINE__);

    if(success )
    {
        pmp_PmpSend(prgInstallationPump,insEventAciStored,currentPreset.Channel.AnalogNo);
    }
    else
    {
	    TraceDebug(m," hsvprins: %s %d",__FUNCTION__,__LINE__);

        if( !askAciToStorePreset )
        {
		    TraceDebug(m," hsvprins: %s %d",__FUNCTION__,__LINE__);

            pmp_PmpSend(prgInstallationPump,insEventAciSearched,currentPreset.Channel.AnalogNo);
        }
        else
        {
		    TraceDebug(m," hsvprins: %s %d",__FUNCTION__,__LINE__);

            pmp_PmpSend(prgInstallationPump,insEventAciStoreFail,currentPreset.Channel.AnalogNo);
        }
    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::pgaciN_aciPresetsWriteInDataStarted( void )
    /****************************************************
     *notification before aci starts writing in nvm
     *****************************************************/
{
    aciPresetStorageOn = TRUE;
    if( prinsN_iPresent() )
    {
        prinsN_OnEvent( prinsN_EventAciStoreStarted,HSVPRINS_INVALID_VALUE );
    }
}

void CHsvPresetInstallation_m_Priv::colN_OnColorSystemChanged( )
{
}
void CHsvPresetInstallation_m_Priv::colN_OnCombFilterActiveChanged(  )
{
}

/********************************************
 * Teletext Call Back Functions
 ********************************************/

void CHsvPresetInstallation_m_Priv::OnReceivedVps( void )
{
	//TraceDebug(m," hsvprins: Rahul: %s %d",__FUNCTION__,__LINE__);
    CHsvPresetInstallation_m_Priv::currentinstance->pmp_PmpSend( CHsvPresetInstallation_m_Priv::currentinstance->prgInstallationPump, insEventVpsRecvd, CHsvPresetInstallation_m_Priv::currentinstance->currentPreset.Channel.AnalogNo );
}

void CHsvPresetInstallation_m_Priv::OnReceivedPkt830CNI( void )
{

 //	TraceDebug(m," hsvprins: Rahul: %s %d",__FUNCTION__,__LINE__);
    currentinstance->pmp_PmpSend (currentinstance->prgInstallationPump, insEventPkt830RecvdCNI, currentinstance->currentPreset.Channel.AnalogNo );
}
void CHsvPresetInstallation_m_Priv::OnReceivedPkt830NI( void )
{

 	//TraceDebug(m," hsvprins: Rahul: %s %d",__FUNCTION__,__LINE__);
    currentinstance->pmp_PmpSend( currentinstance->prgInstallationPump, insEventPkt830RecvdNI, currentinstance->currentPreset.Channel.AnalogNo );
}
void CHsvPresetInstallation_m_Priv::OnReceivedPkt830STATUS( void )
{
//	TraceDebug(m," hsvprins: Rahul: %s %d",__FUNCTION__,__LINE__);
    currentinstance->pmp_PmpSend( currentinstance->prgInstallationPump, insEventPkt830RecvdSTATUS, currentinstance->currentPreset.Channel.AnalogNo );
}

/******************************************
 * Auxiliary functions
 ******************************************/
int static temp_pkt_count =0;
/************************************************************/
void CHsvPresetInstallation_m_Priv::ProgramInstallationStep( int event, Nat32 value )
    /************************************************************
     * Purpose: Pump Function for program installation.
     ************************************************************/
{
    Bool SigStrMeasHandle = TRUE;
    Nat32 errorcode = TM_OK;
    HsvPresetSortData * presetPtr;
    Bool retVal;
	 int buff[4*1024]  ;
     int static temp_count_read =0;
     
     int result =0 ;
     int size =0;
     int i =0;

    if(installationMode == prins_InstallationModeAutomatic)
    {
        presetPtr = &PresetData[value];
    }
    else
    {
        presetPtr = &miPreset;
    }

    TraceDebug(m,"hsvprins: ProgramInstallationStep: event = %d, value = %ld",event,value);
    switch( event )
    {
	    case EventStartManualInstallation:
			mStartManualInstallation();
		    break;
        case insEventStationFound:
            StationFound( value );
            break;

        case insEventStationNotFound:
            StationNotFound();
            break;

        case insEventTimeout:
            if(installationState == HsvinsStateAcquiringTxt)
            {
                TimeoutCheck(value);
            }
            else if(installationState == HsvinsStateSignalStrengthMeasurement)
            {
                SignalStrengthMeaured(value);
            }
            break;

        case insEventVpsRecvd:
            EventVpsRecvd(presetPtr,value);
            break;
        case insEventPkt830RecvdCNI:
            EventPkt830CniRecvd(presetPtr,value);
            break;
        case insEventPkt830RecvdNI:
            EventPkt830NiRecvd(presetPtr,value);
            break;
        case insEventPkt830RecvdSTATUS:
            if(p830_iPresent())
            {
                statusMessageFound = p830_GetStatusMessage(msgString);
            }
            break;
        case insEventTxtInfoRecvdCheck:
            TxtInfoRecvdCheck( value );
            break;
        case insEventTvSystemFound:
            if( prinsN_iPresent() )
            {
                prinsN_OnEvent( prinsN_EventTvSystemChanged, HSVPRINS_INVALID_VALUE );
            }
            tvSystemDetectFlag = TRUE;
			/* ANEESH: TODO: Hack for Analog Service Scan */
				txplfResetFlag = TRUE;
            if(txplfResetFlag)
            {
                tvSystemFoundFlag = FALSE;
                txplfResetFlag = FALSE;
                if (div_AttenuatorDetectionInInstall)
                {
                    if( SigStrMeasHandle )
                    {
                        signalStrengthMeasurementInProgress = TRUE;
                        feapi_Start( WINDOWID, feapi_SigSssm, &retVal, &errorcode );
                        TraceInfo(m,"[CS]tmIFeSigStrengthMeas_Start called, retVal:%d",retVal);
                    }
                    else
                    {
                        OnTvSystemDetected( value );
                    }
                }
                else
                {
                    OnTvSystemDetected( value );
                }

            }
            else
            {
                tvSystemFoundFlag = TRUE;
                //if(resetN_ICONNECTED)
                {
                    pmp_PmpSendAfter( prgInstallationPump
                            , insEventTxplfResetOver
                            , currentPreset.Channel.AnalogNo
                            , div_TxtResetTimeoutTime
                            );
                    installationState = HsvinsStateTxtResetWait;
                }

            }
            /*if(!(resetN_ICONNECTED))
            {
                pmp_PmpSendAfter( prgInstallationPump
                        , insEventTxplfResetOver
                        , currentPreset.Channel.AnalogNo
                        , div_TxtResetTimeoutTime
                        );
                installationState = HsvinsStateTxtResetWait;
            }*/
            break;
        case insEventTxplfResetOver:
            if( tvSystemFoundFlag )
            {
                tvSystemFoundFlag = FALSE;
                txplfResetFlag = FALSE;
                if (div_AttenuatorDetectionInInstall)
                {
                    if( SigStrMeasHandle )
                    {
                        signalStrengthMeasurementInProgress = TRUE;
                        feapi_Start( WINDOWID, feapi_SigSssm, &retVal, &errorcode );
                        /* ssm_StartSignalStrengthMeasurement(); */
                    }
                    else
                    {
                        OnTvSystemDetected( value );
                    }
                }
                else
                {
                    OnTvSystemDetected( value );
                }
            }
            else
            {
                if(installationState != HsvinsStateTxtResetWait)
                {
                    txplfResetFlag = TRUE;
                }
            }
            break;
        case insEventAciSearched:
            /* aci not found on current channel */
            aciTimeoutStarted = FALSE;
            aciTimeOutCounter = 0;
	        TraceDebug(m,"hsvprins: %s %d",__FUNCTION__,__LINE__);
		
            if(currentPresetAciSearch )
            {
				if (installationMode == prins_InstallationModeAutomatic)
				{
					if(  SECAM_FIRST &&(IS_SECAML_SUPPORTED) && (automaticInstallationFirstPass ))
					{
						PresetData[currentPreset.Channel.AnalogNo].tvSystem = tmFe_TvSystemL;

						positiveModulationSearchStarted = TRUE;
						feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode ); /* tun_SetTvSystem( tun_TvSystemL );*/
						if( prinsN_iPresent() )
						{
							prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
						}
						StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault |tmFe_SmPositiveModulation |tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );
					}
					else
					{
						if( !positiveModulationSearchStarted )
						{
							if(!(TvSystemsearch))
							{
								feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );

							}
							if (!(ColorSystemSearch))
							{
								col_ForceColorSystem(col_UnknownColorSystem);
							}
							if( prinsN_iPresent() )
							{
								prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
							}
							StartSearching((tmFe_SearchMode_t) tmFe_SmDefault|tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );  
						}
						else
						{
							if(!(TvSystemsearch))
							{
								feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode );

							}
							if (!(ColorSystemSearch))
							{
								col_ForceColorSystem(col_Secam);
							}
							if( prinsN_iPresent() )
							{
								prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
							}
							StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault |tmFe_SmPositiveModulation| tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );
						}
					}
					installationState = HsvinsStateSearching;			
				}
				else 
				{				
					installationState = HsvinsStateSetFrequency;
					TraceDebug(m,"hsvprins: %s %d",__FUNCTION__,__LINE__);
					/* Set the tuner frequency to minimum, with finetune enabled */
					if ( SECAM_FIRST && (IS_SECAML_SUPPORTED))
					{
						feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode ); 

					}
					else
					{
						feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode ); 

					}
					if( prinsN_iPresent() )
					{
						prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
					}
					feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency(), TRUE, &errorcode ); 
				}
                currentPresetAciSearch = FALSE;
            }
            else
            {
                aciSearchOverFlag = TRUE;
                OnTvSystemDetected( value );
            }
            break;
        case insEventAciStored:
            /* aci installation successful */
            aciTimeoutStarted = FALSE;
            aciTimeOutCounter = 0;
            noOfPresetsFound = pgaci_GetNoOfPresets();
			prinsN_OnEvent( prinsN_EventAciStoreStarted,noOfPresetsFound );
		    TraceDebug(m," hsvprins: %s %d prinsN_EventAciStoreStarted sent",__FUNCTION__,__LINE__);
            InstallationCompleted();
            break;
        case insEventAciStoreFail:
            /* aci store fails at the end of the frequency band search */
            aciTimeoutStarted = FALSE;
            aciTimeOutCounter = 0;
            AciStoreFail(value);
            break;

        case insEventAciStoreTimeOut:
		    TraceDebug(m,"Hsvprins: %s %d %d",__FUNCTION__,__LINE__,installationState);
            if(installationState == HsvinsStateCheckAci)
            {
				TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
                AciTimeout(value);
            }
            break;
        case insEventTvSystemDetectTimeOut :
            tvsystemDetectCounter--;
            if( (!tvSystemDetectFlag) && stationFoundFlag  &&(tvsystemDetectCounter == 0))
            {
                stationFoundFlag = FALSE;
                pmp_PmpSend( prgInstallationPump, insEventTvSystemFound, currentPreset.Channel.AnalogNo );
            }
            break;
        case insEventClearPresets :
            ClearPresets(value);
            break;
        case insEventStorePresets :
			TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
            StoreSortedList(value);
            break;
        case insEventSignalStrengthDetectionInProgess:
            if(installationState == HsvinsStateSignalStrengthMeasurement)
            {
                SignalStrengthMeaured(value);
            }
            else if (div_AttenuatorDetectionInInstall)
            {
                SignalStrengthDetectionCompleted(value);
            }
            break;
        case insEventStopAutoInstallation:
            if( FALSE ) /*The diversity div_StorePresetsOnStopInstallation is FALSE in Fusion.Hence setting this to FALSE*/
            {
                installationStopped =  FALSE; /* Overriding the installationStopped so as to store the presets acquired till now */
                SecondPassSearchOver();
            }
            else
            {  
                InstallationCompleted();            
            }
            break;
        case insEventSkipInstallation:
            SecondPassSearchOver();         
            break;          
        case insEventAfcFreqChanged:
            {
                int frequency, presetNo = 0;
                HsvChannel chNo;
                
                if( (rins_GetInstallationState() == rins_StAnalog) && (( installationMode == prins_InstallationModeNone ) || ( installationMode == prins_InstallationModeBackground ) || ( 
installationMode == prins_InstallationModeImplicit ) ))
                {
                    frequency = mGetTunerFrequency();
                    chNo.Type = HsvAnalog;
                    chNo.Channel.AnalogNo = presetNo;
                    if(pgdat_IsAttributeSupported(pgdat_IntFrequency))
                    {
                        pgdat_StoreChannelDataBool ( chNo, pgdat_IntFrequency, frequency);
                    }
                }
            }
            break;
        case EventfeapiNOnStationFound:
			        TraceDebug(m," hsvprins: %s %d ",__FUNCTION__,__LINE__);

            mfeapiNOnStationFound();
            break;
        case EventfeapiNOnStationNotFound:
            mfeapiNOnStationNotFound();
            break;
		case EventDelayedTvSystemDetected:
			OnTvSystemDetectedHadler(value);
			break;
        default:
            ASSERT(FALSE);
            break;
    }
}

void CHsvPresetInstallation_m_Priv::SignalStrengthMeaured(int value)
{
    GetPkt0Name( value );
	TraceNotice (m, " %s %d Store value  ", __FUNCTION__, __LINE__, value);
    SetPresetDataIndicator(value,MASK_RECEIVED,TRUE);
    StoreData();
    ContinueSearch();
}

void CHsvPresetInstallation_m_Priv::StoreData( void )
    /****************************************************
     * function to store current preset from the preset list
     * in the program data
     *****************************************************/
{
	TraceNotice (m, "StoreData: Count %d AnalogNum %d ", noOfPresetsFound, currentPreset.Channel.AnalogNo);
    StoreDataEx(&PresetData[currentPreset.Channel.AnalogNo],currentPreset, FALSE);
}


/****************************************************/
void CHsvPresetInstallation_m_Priv::StoreDataEx( HsvPresetSortData *presetPtr,HsvChannel preset, Bool StoreInPresetList)
    /****************************************************
     * Purpose: This function stores all the data first
     *          into the structure and then it calls
     *          platform function to write the values
     *          obtained by platform to NVM.
     ****************************************************/
{
    Bool SigStrMeasHandle = TRUE;
    Nat32 errorcode = TM_OK;

    tmFe_TvSystem_t tvSystem;
    Bool valid;
    UInt32 sigst;
    UInt32 freq;
    if((installationMode == prins_InstallationModeAutomatic) && (!div_ImmediateStoreInAutoInstall))
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        SetDataIndicator(presetPtr,MASK_RECEIVED,TRUE);
        if(TvSystemsearch)
        {
            feapi_GetTvSystem ( WINDOWID, &tvSystem, &errorcode );
            presetPtr->tvSystem = tvSystem; /* tun_GetTvSystem();*/ 
			TraceNotice (m, " %s TvSystem %d ", __FUNCTION__, tvSystem);
        }
        else
        {
            if(positiveModulationSearchStarted)
            {
                presetPtr->tvSystem = tmFe_TvSystemL;
            }
            else
            {
                presetPtr->tvSystem = tmFe_TvSystemNone;
            }
        }
        if(ColorSystemSearch)
        {
            presetPtr->colorSystem = (TvColorSystem)col_GetColorSystem();
        }
        else
        {
            if(positiveModulationSearchStarted)
            {
                presetPtr->colorSystem = (TvColorSystem)col_Secam;
            }
            else
            {
                presetPtr->colorSystem = (TvColorSystem)col_UnknownColorSystem;
            }
        }
        if (1)
        {
            if(div_SignalStrengthSorting)
            {
                if ( SigStrMeasHandle )
                {
                    feapi_GetMeasValid ( WINDOWID, feapi_SigSssm, &valid, &errorcode );
                    if( valid )
                    {
                       // feapi_GetSigStrength( WINDOWID, feapi_SigSssm, &sigst, &errorcode ); 
                        //presetPtr->SignalStrength = sigst; 
						presetPtr->SignalStrength = sigstr_GetActualSignalStrength(rins_InsVssm,0);
                        TraceInfo(m,"[CS]preset:%d resetPtr->SignalStrength:%d",preset.Channel.AnalogNo,presetPtr->SignalStrength);

                    }
                }
            }
            else
            {
                if ( SigStrMeasHandle )
                {
                   // presetPtr->SignalStrength = sigstr_GetMaxSignalStrength(rins_InsVssm);
                    presetPtr->SignalStrength = sigstr_GetActualSignalStrength(rins_InsVssm,0);

				//	TraceNotice (m, "Hsvprins: Rahul:: SignalStrength %d %s,%d",presetPtr->SignalStrength, __FUNCTION__, __LINE__);
                }
            }
        }
    }
    else
    {
        if((installationMode == prins_InstallationModeAutomatic) && (div_ImmediateStoreInAutoInstall))
        {
            if (div_AttenuatorDetectionInInstall)
            {
                if(div_SignalStrengthSorting)
                {
                    if( SigStrMeasHandle )
                    {
                        feapi_GetMeasValid ( WINDOWID, feapi_SigSssm, &valid, &errorcode );
                        if( valid )
                        {
                            feapi_GetSigStrength( WINDOWID, feapi_SigSssm, &sigst, &errorcode ); 
                            presetPtr->SignalStrength = sigst ; 
                        }
                    }
                }
                else
                {
                    if ( SigStrMeasHandle )
                    {
                        presetPtr->SignalStrength = sigstr_GetMaxSignalStrength(rins_InsVssm);
                    }
                }
            }
        }

        if(installationMode == prins_InstallationModeAutomatic)
        {
            if(TvSystemsearch)
            {
                feapi_GetTvSystem ( WINDOWID, &tvSystem, &errorcode );
                presetPtr->tvSystem = tvSystem; 
            }
            else
            {
                if(positiveModulationSearchStarted)
                {
                    presetPtr->tvSystem = tmFe_TvSystemL;
                }
                else
                {
                    presetPtr->tvSystem = tmFe_TvSystemNone;
                }
            }

            if(ColorSystemSearch)
            {
                presetPtr->colorSystem = (TvColorSystem)col_GetColorSystem();
            }
            else
            {
                if(positiveModulationSearchStarted)
                {
                    presetPtr->colorSystem = (TvColorSystem)col_Secam;
                }
                else
                {
                    presetPtr->colorSystem = (TvColorSystem)col_UnknownColorSystem;
                }
            }
        }
        else
        {
            feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode );
            presetPtr->tvSystem = tvSystem;  
            presetPtr->colorSystem = (TvColorSystem)col_GetColorSystem();
        }

        if(ManualInstallFrequency != 0)
        {
            presetPtr->Frequency = ManualInstallFrequency;
            ManualInstallFrequency = 0;
        }
        else
        {
            feapi_GetFreq( WINDOWID, &freq, &errorcode ); 
            presetPtr->Frequency = freq ; 
        }
        SetDataIndicator(presetPtr,MASK_RECEIVED,TRUE);\

            if( StoreInPresetList )
            {
                /* Store data into NVM */
                if(pgdat_IsAttributeSupported(pgdat_IntFrequency))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntFrequency, ((presetPtr->Frequency*1000)/16)  );
                    TraceInfo(m,"PlfPreset = %d, Frequency = %d", preset.Channel.AnalogNo, presetPtr->Frequency);
                }
                if(pgdat_IsAttributeSupported(pgdat_IntTvSystem))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntTvSystem, ConvertFromPlatformTvSystem(presetPtr->tvSystem) );
                }
                if(pgdat_IsAttributeSupported(pgdat_IntColoursystem))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntColoursystem, presetPtr->colorSystem);
                }
                if(pgdat_IsAttributeSupported(pgdat_BoolChannelVirgin))
                {
                    pgdat_StoreChannelDataBool (preset, pgdat_BoolChannelVirgin,FALSE);
                }
                if(pgdat_IsAttributeSupported(pgdat_IntDecoderType))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntDecoderType, 0 );
                }
                if(pgdat_IsAttributeSupported(pgdat_IntCniNi))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntCniNi, presetPtr->CniNi);
                }
                if(pgdat_IsAttributeSupported(pgdat_IntDataIndicator))
                {
                    pgdat_StoreChannelDataInt (preset, pgdat_IntDataIndicator, presetPtr->DataIndicator );
                }

                if ( (installationMode == prins_InstallationModeManual) ||(installationMode == prins_InstallationModeImplicit) )
                {

                    if(pgdat_IsAttributeSupported(pgdat_BoolTuned))
                    {
                        pgdat_StoreChannelDataBool ( preset, pgdat_BoolTuned, manualStationFoundFlag );
                    }
                    if( mRfaMinAmplification < 0) 
                    {
                        if(pgdat_IsAttributeSupported(pgdat_BoolAttenuator))
                        {
                            pgdat_StoreChannelDataBool (preset,pgdat_BoolAttenuator,GetDataIndicator(presetPtr,MASK_ATTENUATOR));
                        }
                    }
                }
                else
                {
                    if(pgdat_IsAttributeSupported(pgdat_BoolAttenuator))
                    {
                        pgdat_StoreChannelDataBool (preset,pgdat_BoolAttenuator,FALSE);
                    }
                    if(pgdat_IsAttributeSupported(pgdat_BoolTuned))
                    {
                        pgdat_StoreChannelDataBool (preset, pgdat_BoolTuned, TRUE );
                    }
                }

                if ( (installationMode == prins_InstallationModeManual) ||(installationMode == prins_InstallationModeImplicit) )
                {
                    if(pgdat_IsAttributeSupported(pgdat_StringChannelName))
                    {
                        pgdat_StoreChannelDataString(preset, pgdat_StringChannelName, instutil_AsciiToUnicode(presetPtr->Name, PRESENT_NAMELENGTH_ANALOG),PRESENT_NAMELENGTH_ANALOG );
                    }
                }

                /* clear the preset name if mode is not VPSPDC or VPSPDCACI*/
                if( (installationMode == prins_InstallationModeAutomatic)
                        &&((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeNone)
                            ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
                  )
                {
                    if( pgdat_IsAttributeSupported(pgdat_StringChannelName) )
                    {

                        pgdat_StoreChannelDataString(preset, pgdat_StringChannelName, instutil_AsciiToUnicode(defaultName, PRESENT_NAMELENGTH_ANALOG),PRESENT_NAMELENGTH_ANALOG );
                    }
                }
                /* write CNI */

                if(changePresetAttrib)
                {

                    if(pgdat_IsAttributeSupported(pgdat_IntFineTuneFrequency))
                    {
                        pgdat_StoreChannelDataInt ( preset, pgdat_IntFineTuneFrequency, setOffset);
                    }            

                    if( ( installationMode == prins_InstallationModeManual) ||
                            (installationMode == prins_InstallationModeImplicit) )
                    {
                        if ( fineTune )/* the == TRUE was removed */    
                        {
                            fineTune = FALSE;
                            if(pgdat_IsAttributeSupported(pgdat_BoolDeTuned))
                            {
                                pgdat_StoreChannelDataBool (preset, pgdat_BoolDeTuned, FALSE);
                            }
                            /*feapi_GetAfcEnabled( WINDOWID, &valid, &errorcode ); 
                              if( !valid  )
                              {
                              feapi_GetAfcSupp ( WINDOWID, &valid, &errorcode );
                              if ( valid )
                              {
                              feapi_EnableAfc( WINDOWID, TRUE, &errorcode);
                              }
                              }*/
                        }
                        else
                        {
                            if(pgdat_IsAttributeSupported(pgdat_BoolDeTuned))
                            {
                                pgdat_StoreChannelDataBool (preset, pgdat_BoolDeTuned, TRUE);     
                            }
                            /*feapi_GetAfcEnabled( WINDOWID, &valid, &errorcode ); 
                            if ( valid )
                            {
                                feapi_GetAfcSupp ( WINDOWID, &valid, &errorcode );
                                if ( valid )
                                {
                                    feapi_EnableAfc(WINDOWID, FALSE, &errorcode );
                                }
                            }*/
                        }
                    }
                    else 
                    {
                        if(pgdat_IsAttributeSupported(pgdat_BoolDeTuned))
                        {
                            pgdat_StoreChannelDataBool (preset, pgdat_BoolDeTuned, FALSE );
                        }
                    }
                }
            }
            else
            {
                Bool medretval = TRUE;

                medretval = sort_IsPresetInstalled(presetPtr->Frequency);

                if(medretval == FALSE)
                {
                    HsvPgdatAnalogData anadat;
                    anadat.PresetNumber     =   preset.Channel.AnalogNo;
                    anadat.Frequency        =   presetPtr->Frequency;
					/* ANEESH: Correcting the frequency for the database saving part */
					anadat.Frequency		= 	(anadat.Frequency *1000) /16;
                    anadat.ModulationType   =   ConvertFromPlatformTvSystem((tmFe_TvSystem_t)presetPtr->tvSystem);
                    anadat.ColourSystem     =   presetPtr->colorSystem;
                    //anadat.ChannelVirgin    =   FALSE;
                    anadat.DecoderType      =   0;

                    if ( (installationMode == prins_InstallationModeManual) ||(installationMode == prins_InstallationModeImplicit) )
                    {   /* This if will probably never get executed - PJ */
                        anadat.Tuned    =   manualStationFoundFlag;   

                        if( mRfaMinAmplification < 0) 
                        {
                            anadat.Attenuator   =   GetDataIndicator(presetPtr,MASK_ATTENUATOR);
                        }
                    }
                    else
                    {
                        anadat.Attenuator   =   FALSE;
                        anadat.Tuned        =   TRUE;
                    }

                    if ( (installationMode == prins_InstallationModeManual) ||(installationMode == prins_InstallationModeImplicit) )
                    {
                        memo_memcpy (anadat.ChannelName, instutil_AsciiToUnicode(presetPtr->Name, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength);
                    }

                    /* clear the preset name if mode is not VPSPDC or VPSPDCACI*/
                    if( (installationMode == prins_InstallationModeAutomatic)
                            &&((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeNone)
                                ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
                      )
                    {
                        memo_memcpy(anadat.ChannelName, instutil_AsciiToUnicode(defaultName, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength);
                    }

                    if(changePresetAttrib)
                    {
                        anadat.FineTuneFrequency    =   setOffset;

                        if( ( installationMode == prins_InstallationModeManual) ||
                                (installationMode == prins_InstallationModeImplicit) )
                        {
                            if ( fineTune )/* the == TRUE was removed */    
                            {
                                fineTune = FALSE;
                                anadat.DeTuned  =   FALSE;
                                /*feapi_GetAfcEnabled( WINDOWID, &valid, &errorcode ); 
                                if( !valid  )
                                {
                                    feapi_GetAfcSupp ( WINDOWID, &valid, &errorcode );
                                    if ( valid )
                                    {
                                        feapi_EnableAfc( WINDOWID, TRUE, &errorcode );
                                    }
                                }*/
                            }
                            else
                            {
                                anadat.DeTuned  =   TRUE;

                                /*feapi_GetAfcEnabled( WINDOWID, &valid, &errorcode ); 
                                if ( valid )
                                {
                                    feapi_GetAfcSupp ( WINDOWID, &valid, &errorcode );
                                    if ( valid )
                                    {
                                        feapi_EnableAfc( WINDOWID, FALSE, &errorcode );
                                    }
                                }*/
                            }
                        }
                        else 
                        {
                            anadat.DeTuned  =   FALSE;
                        }
                    }

                    /* Store only tuned presets */
                    if(TRUE == anadat.Tuned)
                    {
						if( (anadat.ChannelName[0] == 0) || ( (anadat.ChannelName[0] == ' ') && (anadat.ChannelName[1] == ' ') && (anadat.ChannelName[2] == ' ')) )
						{
							memo_memcpy(anadat.ChannelName, instutil_AsciiToUnicode(defaultName, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength);
						}
                        sort_AddAnalogPreset((Address )&anadat);
                    }
                    else
                    {
                        TraceInfo(m,"Ignored frequency %ld as Tuned bit is not set", anadat.Frequency); 
                    }
                }
            }
    }

    if( installationMode == prins_InstallationModeAutomatic )
    {
        ChannelFound();
    }
    else
    {
        InstallationCompleted();
    }
}


/*****************************************************/
void CHsvPresetInstallation_m_Priv::ContinueSearch( void )
    /*****************************************************
     * Purpose: Continue's search if the current preset is
     *          less than the maximum presets.
     *****************************************************/
{
    Nat32 errorcode = TM_OK;

     tmFe_TvSystem_t tvSystem;
	

	
	feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode );
	
    if( (!presetFoundInFirstPass)&&(!(allMemoryFilled)) && (tvSystem != tmFe_TvSystemNone)) /*The tv system check is added to handle the driver bug on tv system detection failure*/
    {
        currentPreset.Channel.AnalogNo++;
	    prinsN_OnEvent( prinsN_EventChannelFound, rins_GetInstallationMode() );	
	    prinsN_OnEvent( prinsN_EventTuningStationFound, HSVPRINS_INVALID_VALUE); 
    }
	else
	{
		noOfPresetsFound--;
	} 

    if( currentPreset.Channel.AnalogNo < div_MaxAnalogPresets )
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        continueSearchforPreset();
    }
    else
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        if(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeNone)
        {
            allMemoryFilled = TRUE;
            currentPreset.Channel.AnalogNo = 0;
            continueSearchforPreset();
        }
        else
        {
			TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
            SecondPassSearchOver();
        }
    }
}

void CHsvPresetInstallation_m_Priv::continueSearchforPreset( void )
{
    SetPresetDataIndicator(currentPreset.Channel.AnalogNo,MASK_RECEIVED | MASK_VPS | MASK_PKT830CNI | MASK_PKT830NI,FALSE);
    if( !presetFoundInFirstPass )
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        PresetData[currentPreset.Channel.AnalogNo].tvSystem = PresetData[currentPreset.Channel.AnalogNo -1].tvSystem;
    }
    else
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        presetFoundInFirstPass = FALSE;
    }
    /* Now continue with the search */
    if( positiveModulationSearchStarted )
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        if( prinsN_iPresent() )
        {
            prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
        }
        StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault|tmFe_SmPositiveModulation| TvSystemsearch , freqctl_GetMaxFrequency() );             
    }
    else
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        if( prinsN_iPresent() )
        {
            prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
        }
        StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault | TvSystemsearch , freqctl_GetMaxFrequency() );
    }

    installationState = HsvinsStateSearching;    

}

/*****************************************************/
void CHsvPresetInstallation_m_Priv::TimeoutCheck( int preset )
    /*****************************************************
     * Purpose: Switches to next state after a timeout
     *          occurs.
     *****************************************************/
{
    HsvChannel channel;
    channel.Type = HsvAnalog;
    channel.Channel.AnalogNo = preset;
    switch( installationMode )
    {
        case prins_InstallationModeNone:
            break;

        case prins_InstallationModeAutomatic:
            if( !GetPresetDataIndicator(preset,MASK_RECEIVED) )
            {   
                UpdateCniNameInAutomatic( channel );
            }
            break;

        case prins_InstallationModeManual:
            if( !GetDataIndicator(&miPreset,MASK_RECEIVED) )
            {
                SetDataIndicator(&miPreset,MASK_RECEIVED,TRUE);
                UpdateCniNameInManual( currentPreset );     /* blr73mgr#581 */
            }
            break;

        case prins_InstallationModeImplicit:
        case prins_InstallationModeBackground:
            if( !GetDataIndicator(&miPreset,MASK_RECEIVED))
            {
                if( channel.Channel.AnalogNo == currentPreset.Channel.AnalogNo)  /* check if the timeout is for the same preset */
                {
                    UpdatePresetInBackground( channel );
                }
            }
            break; 

        default:
            ASSERT(FALSE);
            break;
    }
}

/*******************************************************/
void CHsvPresetInstallation_m_Priv::StationFound( int frequency )
    /*******************************************************
     * Purpose: This function is called when tuner sends a
     *          notification for station found.
     *          If AutoStoreMode is VPSPDC, acquire VPS and
     *          Packet830 data from teletext. Otherwise
     *          store data and proceed.
     *******************************************************/
{
    TraceDebug(m," hsvprins: %s %d %d",__FUNCTION__,__LINE__,frequency);

    switch( installationMode )
    {
        case prins_InstallationModeNone:
            break;

        case prins_InstallationModeAutomatic:
            if(installationState != HsvinsStateCheckAci)
            {
			    TraceDebug(m," hsvprins: %s %d %d",__FUNCTION__,__LINE__,frequency);
                CheckAIStateOnStationFound( frequency );
            }
            break;

        case prins_InstallationModeManual:
			                TraceDebug(m," hsvprins: %s %d ",__FUNCTION__,__LINE__);
            tvSystemDetectFlag = TRUE; // its a work around. The flag needed to be updated with a notification from tv player which is not implemented yet.

            CheckMIStateOnStationFound( frequency );
            break;

        case prins_InstallationModeBackground:
        case prins_InstallationModeImplicit:
            break;

        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::CheckAIStateOnStationFound( int frequency )
    /****************************************************
     * function to handle Onstationfound notification in
     * automatic installation
     *****************************************************/
{
    Nat32 errorcode = TM_OK;
    TraceDebug(m," hsvprins: %s %d installationState = %d frequency = %d",__FUNCTION__,__LINE__,installationState,frequency);

    switch( installationState )
    {
        case HsvinsStateNone:
            break;

        case HsvinsStateSetFrequency:
            if(  SECAM_FIRST &&(IS_SECAML_SUPPORTED) && (automaticInstallationFirstPass ))
            {
                PresetData[currentPreset.Channel.AnalogNo].tvSystem = tmFe_TvSystemL;

                positiveModulationSearchStarted = TRUE;
                feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode ); /* tun_SetTvSystem( tun_TvSystemL );*/
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                }
                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault |tmFe_SmPositiveModulation |tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );
            }
            else
            {
                if( !positiveModulationSearchStarted )
                {
                    if(!(TvSystemsearch))
                    {
                        feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );

                    }
                    if (!(ColorSystemSearch))
                    {
                        col_ForceColorSystem(col_UnknownColorSystem);
                    }
                    if( prinsN_iPresent() )
                    {
                        prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                    }
                    StartSearching((tmFe_SearchMode_t) tmFe_SmDefault|tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );  
                }
                else
                {
                    if(!(TvSystemsearch))
                    {
                        feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode );

                    }
                    if (!(ColorSystemSearch))
                    {
                        col_ForceColorSystem(col_Secam);
                    }
                    if( prinsN_iPresent() )
                    {
                        prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                    }
                    StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault |tmFe_SmPositiveModulation| tmFe_SmCurrentIncluded| TvSystemsearch, freqctl_GetMaxFrequency() );
                }
            }
            installationState = HsvinsStateSearching;
            break;

        case HsvinsStateSearching:

            PresetData[currentPreset.Channel.AnalogNo].Frequency = frequency;
			PresetData[currentPreset.Channel.AnalogNo].SignalStrength = sigstr_GetActualSignalStrength(rins_InsVssm,0);

				//	TraceNotice (m, "Hsvprins: Rahul %s %d PresetData[currentPreset.Channel.AnalogNo].SignalStrength=%d ", __FUNCTION__,__LINE__,PresetData[currentPreset.Channel.AnalogNo].SignalStrength);

            if(TvSystemsearch)
            {
                tvSystemDetectFlag = FALSE;

                pmp_PmpSendAfter( prgInstallationPump
                        , insEventTvSystemDetectTimeOut
                        , currentPreset.Channel.AnalogNo
                        , TIME_OUT_TVSYSTEM
                        );
                tvsystemDetectCounter++;
                installationState = HsvinsStateTvSystemDetectWait;
            }
            else
            {
                txplfResetFlag = TRUE;
                OnTvSystemDetected(currentPreset.Channel.AnalogNo);
            }

            break;

        case  HsvinsStateAcquiringTxt:
            break;
        case  HsvinsStateCheckAci:
		    TraceDebug(m," hsvprins: %s %d %d",__FUNCTION__,__LINE__,installationState);
            break;
        case HsvinsStateTvSystemDetectWait:
            break;

        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::CheckMIStateOnStationFound( int frequency )
    /****************************************************
     * function to handle Onstationfound notification in
     * manual installation
     *****************************************************/
{
    TraceDebug(m," hsvprins: %s %d installationState=  %d ",__FUNCTION__,__LINE__,installationState);

    switch( installationState )
    {
        case HsvinsStateNone:
            break;

        case HsvinsStateSetFrequency:
            setFrequencyManual = FALSE;
            setChannelManual   = FALSE;
            miPreset.Frequency = frequency;
                TraceDebug(m," hsvprins: %s %d ",__FUNCTION__,__LINE__);

            miPreset.Frequency = frequency;
            if(!tvSystemDetectFlag )
            {
                pmp_PmpSendAfter( prgInstallationPump
                        , insEventTvSystemDetectTimeOut
                        , currentPreset.Channel.AnalogNo
                        , TIME_OUT_TVSYSTEM
                        );
                tvsystemDetectCounter++;
                installationState = HsvinsStateTvSystemDetectWait;
            }
            if( div_SorCChannelSupported &&
                    ((manualInstallationMode == prins_ManualInstallationModeCChannel)
                     ||(manualInstallationMode == prins_ManualInstallationModeSChannel))
              )
            {
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent(prinsN_EventSearchInProgress, frequency );

                }
            }
            manualStationFoundFlag = TRUE;
            if( prinsN_iPresent())
            {
                prinsN_OnEvent(prinsN_EventManualInstallationCniExtractionStarted,HSVPRINS_INVALID_VALUE );
            }
            if( tvSystemDetectFlag )
            {
                OnTvSystemDetected( currentPreset.Channel.AnalogNo );
            }
            break;

        case HsvinsStateSearching:
            miPreset.Frequency = frequency;

            miPreset.Frequency = frequency;
            tvSystemDetectFlag = FALSE;

            pmp_PmpSendAfter( prgInstallationPump
                    , insEventTvSystemDetectTimeOut
                    , currentPreset.Channel.AnalogNo
                    , TIME_OUT_TVSYSTEM
                    );
            tvsystemDetectCounter++;
            installationState = HsvinsStateTvSystemDetectWait;
            if( prinsN_iPresent() )
            {
                prinsN_OnEvent(prinsN_EventSearchInProgress, frequency );

            }

            manualStationFoundFlag = TRUE;
            if( prinsN_iPresent())
            {
                prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionStarted, HSVPRINS_INVALID_VALUE );
            }
            break;

        case  HsvinsStateAcquiringTxt:
            break;
        case  HsvinsStateCheckAci:
            break;
        case HsvinsStateTvSystemDetectWait:
            break;
        case  HsvinsStateTxtResetWait :
            break;
        default:
            ASSERT(FALSE);
            break;
    }
}

/********************************************************/
void CHsvPresetInstallation_m_Priv::StationNotFound( void )
    /********************************************************
     * Purpose: This function is called when no more stations
     *          are found by the tuner.
     *          If a second pass is required, it is done.
     *          Otherwise do sorting if required, or send
     *          a notification for installation completed.
     ********************************************************/
{
    Nat32 errorcode = TM_OK;
	TraceNotice (m, "Hsvprins %s line %d installationMode= %d ", __FUNCTION__, __LINE__,installationMode);
	
    switch( installationMode )
    {
        case prins_InstallationModeNone:
            break;
        case prins_InstallationModeAutomatic:
            if(installationState != HsvinsStateCheckAci)
            {
				TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
				/* ANEESH: TODO: Just see if we can remove this from here */
                feapi_StopSearch( WINDOWID, &errorcode);

                TraceDebug(m,"hsvprins: %s: %d",__FUNCTION__,__LINE__);
                CheckAIStateOnStationNotFound();
            }
            break;

        case prins_InstallationModeManual:
				TraceNotice (m, "Hsvprins %s line %d  ", __FUNCTION__, __LINE__);
                CheckMIStateOnStationNotFound();
				TraceNotice (m, "Hsvprins %s line %d  ", __FUNCTION__, __LINE__);
				
            break;

        case prins_InstallationModeBackground:
        case prins_InstallationModeImplicit:
            break;

        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::CheckAIStateOnStationNotFound( void )
    /****************************************************
     * function to handle OnstationNotfound notification in
     * automatic installation
     *****************************************************/
{
    Nat32 errorcode = TM_OK;
    Bool supp = TRUE;
    TraceDebug(m,"hsvprins: installationState = %d",installationState );
    switch( installationState )
    {
        case HsvinsStateNone:
            break;

        case HsvinsStateSetFrequency:
            if(  SECAM_FIRST &&(IS_SECAML_SUPPORTED) && automaticInstallationFirstPass  )
            {
                PresetData[currentPreset.Channel.AnalogNo].tvSystem = tmFe_TvSystemL;
                positiveModulationSearchStarted = TRUE;
                TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode ); 
                if (!(ColorSystemSearch))
                {
                    col_ForceColorSystem(col_Secam);
                }
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                }
                TraceDebug(m,"hsvprins: StartSearching called");
                StartSearching( (tmFe_SearchMode_t)tmFe_SmDefault|tmFe_SmPositiveModulation | TvSystemsearch, freqctl_GetMaxFrequency() );
            }
            else
            {
                TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                if (  SECAM_FIRST && automaticInstallationFirstPass )
                {
                    TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                    pmp_PmpSend( prgInstallationPump, insEventStationNotFound, 0 );
                }
                else
                {
                    TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                    if( !positiveModulationSearchStarted )
                    {
                        TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                        if(!(TvSystemsearch))
                        {
                            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );

                        }
                        if (!(ColorSystemSearch))
                        {
                            col_ForceColorSystem(col_UnknownColorSystem);
                        }
                        //feapi_GetSearchModeSupp( WINDOWID, tmFe_SmDefault| TvSystemsearch, &supp, &errorcode );
                        if ( supp )
                        {
                            if( prinsN_iPresent() )
                            {
                                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                            }
                            TraceDebug(m,"Hsvprins  : %d  StartSearching called, installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
                            StartSearching((tmFe_SearchMode_t)tmFe_SmDefault| TvSystemsearch, freqctl_GetMaxFrequency() );
                        }
                    }
                    else
                    {
                        if(!(TvSystemsearch))
                        {
                            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode ); /*tun_SetTvSystem( tun_TvSystemL );*/
                        }
                        if (!(ColorSystemSearch))
                        {
                            col_ForceColorSystem(col_Secam);
                        }
                        if( prinsN_iPresent() )
                        {
                            TraceDebug(m," hsvprins: %d::pmpsend of stationnotfound",__LINE__);
                            prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                        }
                        TraceDebug(m," hsvprins: %d::pmpsend of stationnotfound",__LINE__);
                        StartSearching((tmFe_SearchMode_t)tmFe_SmDefault|tmFe_SmPositiveModulation | TvSystemsearch, freqctl_GetMaxFrequency() );
                    }
                }

            }
            installationState = HsvinsStateSearching;
            break;

        case HsvinsStateSearching:
			TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
            AIStationNotFoundFreqSearchState();
            break;

        case  HsvinsStateAcquiringTxt:
            break;
        case  HsvinsStateCheckAci:
            break;
        case HsvinsStateTvSystemDetectWait:
            break;
        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::AIStationNotFoundFreqSearchState(void)
    /****************************************************
     * function to handle Onstationfound notification in
     * automatic installation
     *****************************************************/
{

    TraceDebug(m,"hsvprins: AIStationNotFoundFreqSearchState");
    if( ( !automaticInstallationFirstPass ) || (!SECOND_PASS_REQUIRED) /*!div_SecondPassSearchSupported(country)*/ )

    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        SecondPassSearchOver();
    }
    else
    {        
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        StartSecondPassSearch();
    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::StartSecondPassSearch(void)
    /****************************************************
     * function to start second pass search
     *****************************************************/
{
    Nat32 errorcode = TM_OK;
    AnalogPassNo++;
    noOfPresetFoundInFirstPass = noOfPresetsFound;
    if(((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
                ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci))
            &&(pgaci_GetPagePriority() != pgAciPriorityInvalid)
            &&(pgaci_IsAciSupported())
      )
    {
        askAciToStorePreset = TRUE;
        installationState = HsvinsStateCheckAci;
        pgaci_StoreAciTable();
        aciTimeoutStarted = TRUE;
        aciTimeOutCounter = 0;
        pmp_PmpSendAfter( prgInstallationPump
                ,  insEventAciStoreTimeOut
                , currentPreset.Channel.AnalogNo
                , LEAST_COUNT_FOR_ACI_TIMEOUT
                );
    }
    else
    {
        if( SECAM_FIRST  )
        {
            positiveModulationSearchStarted = FALSE;

            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );
            if( prinsN_iPresent() )
            {
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );               
                prinsN_OnEvent( prinsN_EventPhaseCompleted, HSVPRINS_INVALID_VALUE );
                prinsN_OnEvent( prinsN_EventPhaseStarted, HSVPRINS_INVALID_VALUE );
            }
            feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency(), TRUE, &errorcode );
            installationState = HsvinsStateSetFrequency;
        }
        else if(IS_SECAML_SUPPORTED)
        {
            PresetData[currentPreset.Channel.AnalogNo].tvSystem = tmFe_TvSystemL;

            positiveModulationSearchStarted = TRUE;

            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemL, &errorcode );
            /* Set the tuner frequency to minimum, with finetune enabled */
            if( prinsN_iPresent() )
            {
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );                
                prinsN_OnEvent( prinsN_EventPhaseCompleted, HSVPRINS_INVALID_VALUE );
                prinsN_OnEvent( prinsN_EventPhaseStarted, HSVPRINS_INVALID_VALUE );
            }
            feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency(), TRUE, &errorcode );

            installationState = HsvinsStateSetFrequency;
        }
        else
        {
            if(positiveModulationSearchStarted )
            {
                positiveModulationSearchStarted = FALSE;
            }
            if(( euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc )
                    ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
              )
            {
                DoSorting();               /* Do sorting */
            }
            else
            {
                /* Get name */
                GetPresetName( currentPreset.Channel.AnalogNo );
                ClearRemainingPresets();
            }
        }
    }
    automaticInstallationFirstPass = FALSE;
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::SecondPassSearchOver(void)
    /****************************************************
     * function to
     *****************************************************/
{

    positiveModulationSearchStarted = FALSE;

    switch(euconfig_GetAutoStoreMode())
    {
        case euconfig_AutoStoreModeVpsPdc:
        case euconfig_AutoStoreModeVpsPdcAci:
            {
                if( !automaticInstallationFirstPass )
                {
                    DoSorting();                 /* Do sorting */
                }
                else
                {
                    if(pgaci_GetPagePriority() != pgAciPriorityInvalid)
                    {
                        askAciToStorePreset = TRUE;
                        installationState = HsvinsStateCheckAci;
                        pgaci_StoreAciTable();
                    }
                    else
                    {
                        DoSorting();             /* Do sorting */
                    }
                }
            }
            break;

        case euconfig_AutoStoreModeAci:
            {
                if( !automaticInstallationFirstPass )
                {
                    /* Get name */
                    GetPresetName( currentPreset.Channel.AnalogNo );

                    nbOfStationAfterSort = noOfPresetsFound+1;
					TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
					mCurrentSortingIndex = 0;
                    StoreSortedList(0);
                }
                else
                {
                    if(pgaci_GetPagePriority() != pgAciPriorityInvalid)
                    {
                        askAciToStorePreset = TRUE;
                        installationState = HsvinsStateCheckAci;
                        pgaci_StoreAciTable();
                    }
                    else
                    {
                        /* Get name */
                        GetPresetName( currentPreset.Channel.AnalogNo );
                        nbOfStationAfterSort = noOfPresetsFound+1;
						TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
						mCurrentSortingIndex = 0;
                        StoreSortedList(0);

                    }
                }
            }
            break;
        case euconfig_AutoStoreModeNone:
			TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
            if(div_SortPresetsInAutoStoreModeNone)
            {
				TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
                sortWithSignalStrength(&PresetIndex[0], noOfPresetsFound+1);
                nbOfStationAfterSort = noOfPresetsFound+1;
				TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
				mCurrentSortingIndex = 0;
                StoreSortedList(0);
            }
            else
            {
				TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
                nbOfStationAfterSort = noOfPresetsFound+1;             
				TraceNotice (m, "StoreSortedList from %d  ", __LINE__);				
				mCurrentSortingIndex = 0;
                StoreSortedList(0);
            }
            break;
        default:
            {
                ASSERT(0);
                /* Get name */

            }
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::CheckMIStateOnStationNotFound( void )
    /****************************************************
     * function to handle Onstationnotfound notification in
     * manual installation
     *****************************************************/
{
    UInt32 freq;
    UInt32 chan, nxtchan;
    Nat32 errorcode = TM_OK;
                TraceDebug(m," hsvprins: %s %d installationState=%d",__FUNCTION__,__LINE__,installationState);

    switch( installationState )
    {
        case HsvinsStateNone:
            break;

        case HsvinsStateSetFrequency:
		    TraceDebug(m,"Hsvprins  %s  %d setFrequencyManual = %d",__FUNCTION__,__LINE__,setFrequencyManual);		
	
            if( setFrequencyManual )
            {
                TraceDebug(m," hsvprins: %s %d ",__FUNCTION__,__LINE__);
			
                setFrequencyManual = FALSE;
                implicitInstRequired = TRUE;
            }
            if( setChannelManual )
            {
                setChannelManual = FALSE;
            }
            if( prinsN_iPresent())
            {
                prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionEnded, HSVPRINS_INVALID_VALUE);
            }
            manualStationFoundFlag = FALSE;


            /* CR:BV Audio Mute: Can be moved to notification handling place - OK ? */
           /*   sysctl_SetAudioMute(FALSE);*/

            installationState = HsvinsStateNone;     
            if( prinsN_iPresent())
            {
                prinsN_OnEvent( prinsN_EventManualInstallationChannelNotFound, HSVPRINS_INVALID_VALUE);
            }
            installationMode = prins_InstallationModeNone;
            sysctl_SetVideoMute(TRUE);//to solve PR brg36mgr 15118

            break;

        case HsvinsStateSearching:
		                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );
            if(manualInstallationMode == prins_ManualInstallationModeFrequency)
            {
			                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );

                if( prinsN_iPresent())
                {
                    prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionEnded, HSVPRINS_INVALID_VALUE);
                }
				installationStopped = TRUE;
                InstallationCompleted();
            }
            else if(manualInstallationMode == prins_ManualInstallationModeCChannel)
            {
                if(div_SorCChannelSupported)
                {
                    feapi_GetFreq( WINDOWID, &freq, &errorcode); 
                    ASSERT(errorcode == TM_OK);
                    feapi_Freq2Chan( WINDOWID, freq, tmFe_TableEuropeC, &chan, &errorcode );
                    ASSERT(errorcode == TM_OK);
                    //feapi_GetNextChan( WINDOWID, chan, tmFe_TableEuropeC, &nxtchan, &errorcode );
                    ASSERT(errorcode == TM_OK);



                    if ( (UInt32)SPointCSearch == nxtchan ) /* Last freq reached. And there is no wrap around feature in S/C Channel Mode */
                    {                   
                        if( prinsN_iPresent())
                        {
                            prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionEnded, HSVPRINS_INVALID_VALUE);
                        }                        
                        installationState = HsvinsStateNone;     
                        if( prinsN_iPresent())
                        {
                            prinsN_OnEvent( prinsN_EventManualInstallationChannelNotFound, HSVPRINS_INVALID_VALUE);
                        }
                        installationMode = prins_InstallationModeNone;           

                    }
                    else
                    {
                        if( prinsN_iPresent() )
                        {
                            feapi_GetFreq( WINDOWID, &freq, &errorcode);
                            prinsN_OnEvent(prinsN_EventSearchInProgress, freq );

                        }

                        /* CR:BV Video Mute: Can be moved to ntf TuningStarted - NOK */
                        /* Manual Installation: Dont touch */
                        sysctl_SetVideoMute(FALSE);

                        feapi_GetFreq( WINDOWID, &freq, &errorcode);
                        feapi_Freq2Chan( WINDOWID, freq, tmFe_TableEuropeC, &chan, &errorcode );
                        //feapi_GetNextChan( WINDOWID, chan, tmFe_TableEuropeC, &nxtchan, &errorcode );
                        feapi_GetCarrierFreq( WINDOWID, nxtchan, tmFe_TableEuropeC, &freq, &errorcode ); 
                        if( prinsN_iPresent() )
                        {
                            prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                        }
                        feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode );


                        feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );

                    }
                }
                else
                {
                    ASSERT(!"S or C channel not supported");
                }
            }
            else
            {
                if(div_SorCChannelSupported)
                {
                    feapi_GetFreq( WINDOWID, &freq, &errorcode); 
                    feapi_Freq2Chan( WINDOWID, freq, tmFe_TableEuropeS, &chan, &errorcode );
                    //feapi_GetNextChan( WINDOWID, chan, tmFe_TableEuropeS, &nxtchan, &errorcode );  



                    if (  (UInt32)SPointSSearch == nxtchan ) /* Last freq reached. And there is no wrap around feature in S/C Channel Mode */
                    {
                        if( prinsN_iPresent())
                        {
                            prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionEnded, HSVPRINS_INVALID_VALUE);
                        }
                        installationState = HsvinsStateNone;     
                        if( prinsN_iPresent())
                        {
                            prinsN_OnEvent( prinsN_EventManualInstallationChannelNotFound, HSVPRINS_INVALID_VALUE);
                        }
                        installationMode = prins_InstallationModeNone;      

                    }                
                    else
                    {
                        if( prinsN_iPresent() )
                        {
                            feapi_GetFreq( WINDOWID, &freq, &errorcode );
                            prinsN_OnEvent(prinsN_EventSearchInProgress, freq );

                        }
                        /* CR:BV Video Mute: Can be moved to ntf TuningStarted - NOK */
                        /* Manual Installation: Dont touch */
                        sysctl_SetVideoMute(FALSE);

                        feapi_GetFreq( WINDOWID, &freq, &errorcode );
                        feapi_Freq2Chan( WINDOWID, freq, tmFe_TableEuropeS, &chan, &errorcode );
                        //feapi_GetNextChan( WINDOWID, chan, tmFe_TableEuropeS, &nxtchan, &errorcode );
                        feapi_GetCarrierFreq( WINDOWID, nxtchan, tmFe_TableEuropeS, &freq, &errorcode ); 
                        if( prinsN_iPresent() )
                        {
                            prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                        }
                        feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode );   


                        feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );

                    }
                }
                else
                {
                    ASSERT(!"S or C channel not supported");
                }
            }
            manualStationFoundFlag = FALSE;
            break;

        case  HsvinsStateCheckAci:
            break;
        case HsvinsStateTvSystemDetectWait:
            break;
        case  HsvinsStateAcquiringTxt:
            break;
        case  HsvinsStateTxtResetWait :
            break;
        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::OnTvSystemDetected(int value)
    /****************************************************
     * function to handle Ontvsystemdetected notification
     *****************************************************/
{
    Bool avail;
    /*tmIFeSigStrengthMeas  *SigStrMeasHandle    =   (tmIFeSigStrengthMeas *)intfhdl_GetCurrentSigStrMeasHandle(rins_InsVssm);*/
    Bool SigStrMeasHandle = TRUE;
    Nat32 errorcode = TM_OK;

    switch( installationMode )
    {
        case prins_InstallationModeNone:
            break;
        case prins_InstallationModeAutomatic:
            presetFoundInFirstPass = FALSE;
			/* ANEESH: TODO: Hack for analog automatic installation
				euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeNone */
            if( (euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeNone) )
            {
                /* Find the ACI only in First PASS */
                if( ( automaticInstallationFirstPass )
                        &&(!aciSearchOverFlag )
                        &&(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeVpsPdc)
                        &&(pgaci_IsAciSupported() )
                  )
                {
                    pgaci_StartAciInstallation();
                    installationState = HsvinsStateCheckAci;
                    aciTimeoutStarted = TRUE;
                    aciTimeOutCounter = 0;
                    pmp_PmpSendAfter( prgInstallationPump
                            ,  insEventAciStoreTimeOut
                            ,  value
                            , LEAST_COUNT_FOR_ACI_TIMEOUT
                            );
                }
                /*No ACI Search in Second pass */
                if((!automaticInstallationFirstPass )
                        ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc)
                        ||(!(pgaci_IsAciSupported()))
                  )
                {
                    aciSearchOverFlag = TRUE;
                }
                if(aciSearchOverFlag )
                {
                    aciSearchOverFlag = FALSE;
                    if(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci)
                    {
                        /* Continue in AutoStoreModeAci*/
                        GetPkt0Name( value );
                        SetPresetDataIndicator(value,MASK_RECEIVED,TRUE);
                        StoreData();
                        ContinueSearch();
                    }
                    /* Find the preset if it is found in first pass with teletext */
                    if(  (!automaticInstallationFirstPass )
                            && (noOfPresetFoundInFirstPass != 0)
                            &&(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeAci)
                      )
                    {
                        presetFoundInFirstPass = PresetSearch(noOfPresetFoundInFirstPass,
                                PresetData[currentPreset.Channel.AnalogNo].Frequency,TRUE);
                    }
                    if( (!presetFoundInFirstPass )
                            && (euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeAci)
                      )
                    {
                        /* Start txt decoding and wait for TXT information */
                        RequestVpsP830(&PresetData[currentPreset.Channel.AnalogNo]);
                    }
                    if(presetFoundInFirstPass ) /* the == TRUE was removed */
                    {
                        ContinueSearch();
                    }

                }
            }
            else
            {    /* Continue in AutoStoreModeNone*/
                if(div_SortPresetsInAutoStoreModeNone )
                {
                    PresetIndex[value] = (Nat8)value;
                    StartTimeOut( div_SignalStrengthTimeoutTime );
                    installationState = HsvinsStateSignalStrengthMeasurement;
                    if( SigStrMeasHandle )
                    {
                        feapi_Start( WINDOWID, feapi_SigSssm, &avail, &errorcode);

                    }
                }
                else
                {
					TraceNotice (m, "ANALOG Installation: %s line %d TVSystem Detection happened. Further Scan now ", __FUNCTION__, __LINE__);
					/* ANEESH: HACK: Comment out Pkt0 Name. Not needed currently for normal instalaltion */
                    GetPkt0Name( value );
                    SetPresetDataIndicator(value,MASK_RECEIVED,TRUE);
                    StoreData();
                    ContinueSearch();
                }
            } 
            break;

        case prins_InstallationModeManual:
            /* Start txt decoding and wait for TXT information */

            /* CR:BV Audio Mute - not sure how to substitute - OPEN */
            sysctl_SetAudioMute(FALSE);

            if(!RequestVpsP830(&miPreset))
            {
                if( manualInstallationPendingStore )
                {
                    manualInstallationPendingStore = FALSE;
                    noOfPresetsFound =1;
                    StoreDataEx(&miPreset,currentPreset, TRUE);
                }
                else
                {
                    ChannelFound();
                }
            }

            break;

        case prins_InstallationModeBackground:
        case prins_InstallationModeImplicit:
            break;

        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::EventVpsRecvd(HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received VPS data
     *****************************************************/
{    
#if(1)
    Nat8    dis;
    if( installationMode != prins_InstallationModeNone )
    {
        vps_GetCountryNetworkIdentificationCode( &currentVpsCni  );
        /* get ARD ZDF distinction bit */
        vps_GetDistinctionBits( &dis );
        SetDataIndicator(presetPtr,MASK_ARD,(dis&0x02));
        currentVpsCni = (( currentVpsCni) & (0x0FFF));

        if(currentVpsCni != 0)
        {
            SetDataIndicator(presetPtr,MASK_VPS,TRUE);
        }
        pmp_PmpSend( prgInstallationPump, insEventTxtInfoRecvdCheck, preset );
    }
#else 
    UNUSED( presetPtr );
    UNUSED( preset );
#endif
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::EventPkt830CniRecvd( HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received Packet 830 CNI data
     *****************************************************/
{
#if( 1 )
    Bool    pkt830format2Found;

    if( installationMode != prins_InstallationModeNone )
    {
        pkt830format2Found = p830_GetCountryNetworkIdentificationCode( &currentPkt830Cni  );
        if(pkt830format2Found )/* the == TRUE was removed */
        {

            if(currentPkt830Cni  != 0)
            {
                SetDataIndicator(presetPtr,MASK_PKT830CNI,TRUE);
            }
            pmp_PmpSend( prgInstallationPump, insEventTxtInfoRecvdCheck, preset );
        }
    }
#else
    UNUSED( presetPtr );
    UNUSED( preset );
#endif


}


/****************************************************/
void CHsvPresetInstallation_m_Priv::EventPkt830NiRecvd( HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received Packet 830 NI data
     *****************************************************/
{    
#if( 1 )
    Bool    pkt830format1Found;

    if( installationMode != prins_InstallationModeNone )
    {
        pkt830format1Found = p830_GetNetworkIdentificationCode( &currentPkt830Ni  );

        if(pkt830format1Found )/* the == TRUE was removed */
        {

            if(currentPkt830Ni != 0)
            {
                SetDataIndicator(presetPtr,MASK_PKT830NI,TRUE);
            }
            pmp_PmpSend( prgInstallationPump, insEventTxtInfoRecvdCheck, preset );
        }

    }
#else
    UNUSED( presetPtr );
    UNUSED( preset );
#endif

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::TxtInfoRecvdCheck( int preset )
    /****************************************************
     * function to check CNI/NI info
     *****************************************************/
{
    HsvChannel chan;
    chan.Type = HsvAnalog;
    chan.Channel.AnalogNo = preset;
    switch( installationMode )
    {
        case prins_InstallationModeNone:
            break;

        case prins_InstallationModeAutomatic:
            if( 1 )
            {
                if( !(GetPresetDataIndicator(preset,MASK_RECEIVED)) && IsVpsPkt830InfoReceived(&PresetData[preset]) )
                {
					TraceNotice (m, " 1.Setting MaskRxd TRUE for %d ", preset);
                    SetPresetDataIndicator(preset,MASK_RECEIVED,TRUE);
                    UpdateCniNameInAutomatic(chan);
                }
            }
            break;

        case prins_InstallationModeManual:
            if( 1 )
            {
                if( !(GetDataIndicator(&miPreset,MASK_RECEIVED)) && IsVpsPkt830InfoReceived(&miPreset) )
                {
                    SetDataIndicator(&miPreset,MASK_RECEIVED,TRUE);
                    UpdateCniNameInManual(chan);
                }
            }
            break;

        case prins_InstallationModeBackground:
        case prins_InstallationModeImplicit:
            if(1)
            {
                if( !(GetDataIndicator(&miPreset,MASK_RECEIVED)) && IsVpsPkt830InfoReceived(&miPreset) )
                {
                    SetDataIndicator(&miPreset,MASK_RECEIVED,TRUE);
                    UpdatePresetInBackground(chan);
                }
            }
            break;

        default:
            ASSERT(FALSE);
            break;
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::StoreSortedList( int presetNo )
    /*************************************************************/
    /* Stores the preset information after AutomaticInstallation */
    /* In AutoStoremodeVpsPdc & AutoStoreModeVpsPdcAci           */
    /*************************************************************/
{
    Nat8 index;
    HsvChannel channel;

	/* Overwrite here */
	presetNo = mCurrentSortingIndex;
    index = (Nat8)presetNo;

    channel.Type = HsvAnalog;
    channel.Channel.AnalogNo = index;
    if( eurdiv_AutomaticAnalogPresetAllocation() == FALSE )
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        /* div_AnalogStartPreset -1 if div_AnalogStartPreset is zero and 
           indx is also zero then can it cause problem?? */
        channel.Channel.AnalogNo = index + eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE)) -1;
    }    
	TraceNotice (m, "ANALOG Installation: %s line %d PresetIndex %d  ", __FUNCTION__, __LINE__, index);
    if(index < div_MaxAnalogPresets && !installationStopped )
    {
		TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
        Bool medretval = TRUE;

		TraceNotice (m, "Index %d PresetIndexAfterSorting %d Freq %d ", index, GetPresetIndexAfterSorting(index), PresetData[ GetPresetIndexAfterSorting(index) ].Frequency);
        medretval = sort_IsPresetInstalled(PresetData[ GetPresetIndexAfterSorting(index) ].Frequency) ;

        if(medretval == FALSE)
        {
			TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
            HsvPgdatAnalogData anadat;


            pgdb_Initialise (pgdbconst_Analog, (Address) (&anadat));
            anadat.PresetNumber = channel.Channel.AnalogNo; 


			TraceNotice (m, "index %d idxAfterSort %d nbOfStationAfterSort %d ", index, GetPresetIndexAfterSorting(index), nbOfStationAfterSort);
            if( (GetPresetDataIndicator(GetPresetIndexAfterSorting(index),MASK_RECEIVED) && (index < nbOfStationAfterSort)))
            {
				TraceNotice (m, "ANALOG DATABASE UPDATE HAPPENING ");
                //anadat.ChannelVirgin    =   FALSE;
                anadat.DeTuned          =   FALSE;
                anadat.Frequency        =   PresetData[ GetPresetIndexAfterSorting(index) ].Frequency;
				/* ANEESH: Modifying this for frequency conversion */
				anadat.Frequency 		= 	(anadat.Frequency * 1000)/16;
                anadat.ModulationType   =   ConvertFromPlatformTvSystem(PresetData[ GetPresetIndexAfterSorting(index) ].tvSystem);
                anadat.Tuned            =   TRUE;

                anadat.CniNi            =   PresetData[ GetPresetIndexAfterSorting(index) ].CniNi;
                anadat.DataIndicator    =   PresetData[ GetPresetIndexAfterSorting(index) ].DataIndicator;

                memo_memcpy(anadat.ChannelName, instutil_AsciiToUnicode(PresetData[ GetPresetIndexAfterSorting(index) ].Name, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength);
                anadat.ColourSystem     =   PresetData[GetPresetIndexAfterSorting(index)].colorSystem;

                if (div_AttenuatorDetectionInInstall)
                {
                    anadat.Attenuator   =   GetPresetDataIndicator(GetPresetIndexAfterSorting(index),MASK_ATTENUATOR);
                }
                else
                {
                    anadat.Attenuator   =   FALSE;
                }

                if( (SECAM_FIRST ) &&  (GetPresetDataIndicator(GetPresetIndexAfterSorting(index),MASK_RECEIVED) == FALSE) )
                {
                    anadat.ModulationType   =   ConvertFromPlatformTvSystem(tmFe_TvSystemL);
                }

                if(TRUE == anadat.Tuned)
                {
					TraceNotice (m, "ANALOG Installation: %s line %d  ", __FUNCTION__, __LINE__);
                    sort_AddAnalogPreset((Address )&anadat);
                }
            }

        }
		TraceNotice (m, "ANEESH: AfterStore Value %d ", index);
        index++; /* Next preset */
		mCurrentSortingIndex++;
        pmp_PmpSend(prgInstallationPump,insEventStorePresets,index);
		TraceNotice (m, "ANEESH: Sending Event %d with Value %d NextIndex %d ", insEventStorePresets, index, mCurrentSortingIndex);
    }
    else
    {
        InstallationCompleted();
    }

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::StartTimeOut( int time )
    /****************************************************
     * starts the timeout
     *****************************************************/
{
    pmp_PmpSendAfter( prgInstallationPump
            , insEventTimeout
            , currentPreset.Channel.AnalogNo
            , time
            );
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::InstallationCompleted( void )
    /****************************************************
     * gives installation completed notification
     *****************************************************/
{
    int          im;    
    int          preset;
    Bool         valid;
    HsvChannel   chan;
    Nat32 errorcode = TM_OK;

    im = installationMode;
    installationMode = prins_InstallationModeNone;
    installationState = HsvinsStateNone;
    changePresetAttrib = FALSE;

    /* Send appropriate notifys */
    switch( im )
    {
        case prins_InstallationModeNone:
            break;

        case prins_InstallationModeAutomatic:
            feapi_StopSearch( WINDOWID, &errorcode );


            /*CR:BV Video Mute: Possible to move to notification - OK? */
            /* Expected to be done in hsveuins_m.c */


            /*feapi_GetAfcEnabled( WINDOWID, &valid, &errorcode ); 
            if( !valid )
            {
                feapi_GetAfcSupp ( WINDOWID, &valid, &errorcode );
                if ( valid )
                {
                    feapi_EnableAfc(WINDOWID, TRUE, &errorcode );
                }
            }*/

            /*CR:BV Audio Mute: Possible to move to notification - OK?*/
         /*     sysctl_SetAudioMute(FALSE);*/

            /*Make extentions as favourite */            
            preset = 0;

            ReleaseMemoryForPresetList();
            if( prinsN_iPresent() )
            {
                if( !installationStopped )
                {
                    prinsN_OnEvent( prinsN_EventAutomaticInstallationCompleted,  HSVPRINS_INVALID_VALUE);
                }
                else
                {
                    installationStopped = FALSE;
                    /* make noOfPresetsFound to zero if installation is interrupted and 
                       if the diversity os FALSE */
                    if (!div_ImmediateStoreInAutoInstall)
                    {
                        noOfPresetsFound = 0;
                        noOfNewPresetsFound =   0;
                    }
                }
            }
            break;

        case prins_InstallationModeManual:
            manualInstallationPendingStore = FALSE;
            feapi_StopSearch( WINDOWID, &errorcode );

                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );

            /*CR:BV Video Mute: Possible to move to notification - NOK */
            /* Manual Installation - Dont change */

            sysctl_SetVideoMute(TRUE);

            /*CR:BV Audio Mute: Possible to move to notification - NOK */

         /*     sysctl_SetAudioMute(FALSE);*/

            if( prinsN_iPresent() )
            {
                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );

                if( !installationStopped )
                {
                    chan.Type = HsvAnalog;
                    chan.Channel.AnalogNo = presetNumberStored;
                    prinsN_OnManualInstallationStored( chan );
                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );
                }
                else
                {
                        TraceDebug(m,"hsvprins: %d %s ",__LINE__, __FUNCTION__ );
                    installationStopped = FALSE;
                }
            }
            break;

        case prins_InstallationModeImplicit:
        case prins_InstallationModeBackground:
			/* no listeners
            if( implinsN_iPresent() && ! (updateOnlyCniInBackground) )
            {
                implinsN_OnEvent( implinsN_OnImplicitInstallationCompleted);
            }*/
            break;
        default:
            ASSERT(FALSE);
            break;
    }

#if( 1 )

    if ( fieldCNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldCNI );
        fieldCNI = p830_InvalidRequestId;
    }
    if (fieldNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldNI );
        fieldNI = p830_InvalidRequestId;
    }
    if (fieldSTATUS != p830_InvalidRequestId)
    {
        p830_UnRequestDataFields ( fieldSTATUS );
        fieldSTATUS = p830_InvalidRequestId;
    }

#endif

#if( 1 )    

    if (fieldVPS != vps_InvalidRequestId)
    {
        vps_UnRequestDataFields ( fieldVPS );
        fieldVPS = vps_InvalidRequestId;
    }

#endif
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::ChannelFound( void )
    /****************************************************
     * actions to be taken after channel is found
     *****************************************************/
{
    int retval = TRUE;
    Nat32 errorcode = TM_OK;
    Nat32 freq;

    feapi_GetFreq( WINDOWID, &freq, &errorcode);
    if(!(allMemoryFilled))
    {
        noOfPresetsFound++;
		TraceNotice (m, "ANALOG: NoPresetFound %d ", noOfPresetsFound);
		
        retval = sort_IsPresetInstalled(freq);

        if(!retval)
        {
            noOfNewPresetsFound++;
        }
	prinsN_OnEvent( prinsN_EventTuningStationFound, HSVPRINS_INVALID_VALUE); 
        lastPresetFound = currentPreset;
        installationState = HsvinsStateNone;
      /*  if(installationMode == prins_InstallationModeManual)
        {
            CR:BV Audio Mute: Possible to move to notification - NOK 
            sysctl_SetAudioMute(FALSE);
        }
		*/
        if( prinsN_iPresent() )
        {
            if(installationMode == prins_InstallationModeManual)
            {
                prinsN_OnEvent( prinsN_EventManualInstallationCniExtractionEnded,  HSVPRINS_INVALID_VALUE);
            }
            prinsN_OnEvent( prinsN_EventChannelFound, rins_GetInstallationMode() );
        }
    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::GetPkt0Name( int preset )
    /****************************************************
     * Gives the name of Preset for a given preset in preset 
     * list
     *****************************************************/
{
    GetPkt0NameEx(&PresetData[preset],preset);
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::GetPkt0NameEx( HsvPresetSortData *presetPtr,int preset )
    /****************************************************
     * Gives the name of Preset for a given preset
     *****************************************************/
{
    char            label[div_PresetNameLength];
    unsigned char   i, j = 0;
    Bool            found = FALSE;
    int             presetNameLength = 0, len =0;

    UNUSED(preset);
    /*Check for blank name in Status Message */
    str_strncpy( presetPtr->Name,(char *)&defaultName[0],div_PresetNameLength);
    str_strncpy( label,(char *)&defaultName[0],div_PresetNameLength);
    if(statusMessageFound)
    {

        while( (msgString[j] == ' ') && (j < STATUS_MSG_LEN) )
        {
            j++;
        }
        if( j < STATUS_MSG_LEN )
        {
            len = STATUS_MSG_LEN - j;
            presetNameLength = ( len < div_PresetNameLength ) ? len : div_PresetNameLength;
            for(i=0;i<presetNameLength;i++, j++)
            {
                label[i] = msgString[j];
            }
            found = TRUE;
        }
    }
    /* Copy the name if valid program name is in pkt830*/
    if(( euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc )
            || (euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
            ||((div_SupportNameExtractionInManIns )
                &&((installationMode == prins_InstallationModeManual) 
                    ||(installationMode == prins_InstallationModeImplicit))))
    {
        if((p830_iPresent())&&(statusMessageFound) &&(found) )
        {

            str_strncpy( presetPtr->Name,label, div_PresetNameLength );
            statusMessageFound = FALSE;

        }
        else if( (chlname_iPresent()) &&
                ((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)||
                 (euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc) ||
                 (installationMode == prins_InstallationModeManual)||
                 (installationMode == prins_InstallationModeImplicit))
               )      /* Channel Name from packet0 through Txsvc  */
        {
            if(chlname_GetCurrentChannelLabel (label ))
            {
                str_strncpy( presetPtr->Name,(char*)label, div_PresetNameLength );
            }
        }
        else   /* Copy blanks as channel Name */
        {
            str_strncpy( presetPtr->Name,(char *)&defaultName[0],div_PresetNameLength);
        }
    }
    else
    {
        str_strncpy( presetPtr->Name,(char *)&defaultName[0],div_PresetNameLength);
    }
}

/****************************************************/
Bool CHsvPresetInstallation_m_Priv::PresetSearch(int presetInList,int frequency,Bool BeforeTxt)
    /************************************************************/
    /* This function Searches the preset in Data Base           */
    /* Function Returns the TRUE if preset is found in list and */
    /* have teletext Otherwise returns FALSE                    */
    /************************************************************/
{
    int presetPosition;
    int min;
    int max;
    int mid;
    int ret;
    int tempfreq;
    Nat32 errorcode = TM_OK;
    tmFe_TvSystem_t tvSystem;
    presetPosition = HSVPRINS_INVALID_PRESET;
    ret = FALSE;
    min = 1;
    max = presetInList;
    while(min<=max)
    {
        mid = (min+max)/2;
        tempfreq = PresetData[mid].Frequency;
        if( (tempfreq >= frequency-16) && (tempfreq <= frequency+16) )
        {     /*+-1MHz=+-16 */
            presetPosition = mid;
            break;
        }
        else if(tempfreq > frequency)
        {
            max = mid-1;
        }
        else if(tempfreq < frequency)
        {
            min = mid+1;
        }
        else
        {
            presetPosition = mid;
            break;
        }
    }

    /* Check for teletext information */
    if( (presetPosition != HSVPRINS_INVALID_PRESET) &&
            (GetPresetDataIndicator(presetPosition,MASK_TXTTRNAVLBL )) &&
            (BeforeTxt) )
    {
        ret = TRUE;
    }
    if( (presetPosition != HSVPRINS_INVALID_PRESET) 
            && (GetPresetDataIndicator(presetPosition,MASK_TXTTRNAVLBL) == FALSE)
            && (!(BeforeTxt))
            && (GetPresetDataIndicator(currentPreset.Channel.AnalogNo,MASK_TXTTRNAVLBL ) )/* the == TRUE was removed */
      )
    {
        feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode );
        PresetData[presetPosition].tvSystem = tvSystem;
        PresetData[presetPosition].CniNi = PresetData[currentPreset.Channel.AnalogNo].CniNi;
        str_strncpy((char *) PresetData[presetPosition].Name,
                (char *) PresetData[currentPreset.Channel.AnalogNo].Name, div_PresetNameLength );

        /* copy all bit flags of the new preset to the old preset except the received flag */
        ASSERT(GetPresetDataIndicator(presetPosition,MASK_RECEIVED));
        PresetData[presetPosition].DataIndicator = PresetData[currentPreset.Channel.AnalogNo].DataIndicator;
		TraceNotice (m, " 2.Setting MaskRxd TRUE for %d ", presetPosition);
        SetPresetDataIndicator(presetPosition,MASK_RECEIVED,TRUE);
        ret = TRUE;
    }

    return(ret);

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::AciStoreFail(int value)
    /****************************************************
     * function to handle aci store fail event
     *****************************************************/
{
    TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
    Nat32 errorcode = TM_OK;
    /* Aci search fails after first pass*/
    if( !automaticInstallationFirstPass )
    {
        TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
        askAciToStorePreset = FALSE;
        /* Continue Second pass */
        if( SECAM_FIRST  )
        {
            TraceDebug(m,"  : %d  hsvprins: installationState = %d %s ",__LINE__, installationState, __FUNCTION__ );
            if( prinsN_iPresent() )
            {
                TraceDebug(m," %d %s freqctl_GetMinFrequency() = %d ",__LINE__, __FUNCTION__, freqctl_GetMinFrequency()); 
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
            }
            TraceDebug(m," %d %s freqctl_GetMinFrequency() = %d ",__LINE__, __FUNCTION__, freqctl_GetMinFrequency()); 
            feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency() , TRUE, &errorcode );
            if( prinsN_iPresent() )
            {
                TraceDebug(m," %d %s ",__LINE__, __FUNCTION__); 
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
            }
            StartSearching((tmFe_SearchMode_t)tmFe_SmDefault| TvSystemsearch, freqctl_GetMaxFrequency() );                 
            positiveModulationSearchStarted = FALSE;
            installationState = HsvinsStateSearching;
        }
        else if(IS_SECAML_SUPPORTED)
        {
            TraceDebug(m," %d %s ",__LINE__, __FUNCTION__); 
            PresetData[currentPreset.Channel.AnalogNo].tvSystem = tmFe_TvSystemL;
            positiveModulationSearchStarted = TRUE;
            feapi_SetTvSystem ( WINDOWID, tmFe_TvSystemL, &errorcode );
            /* Set the tuner frequency to minimum, with finetune enabled */
            if( prinsN_iPresent() )
            {
                TraceDebug(m," %d %s freqctl_GetMinFrequency() = %d ",__LINE__, __FUNCTION__, freqctl_GetMinFrequency()); 
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
            }
            TraceDebug(m," %d %s freqctl_GetMinFrequency() = %d ",__LINE__, __FUNCTION__, freqctl_GetMinFrequency()); 
            feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency(), TRUE, &errorcode );
            installationState = HsvinsStateSetFrequency;
        }
        else
        {
            if(positiveModulationSearchStarted )
            {
                positiveModulationSearchStarted = FALSE;
            }
            if(( euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc )
                    ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
              )
            {
                DoSorting();                /* Do sorting */
            }
            else
            {
                /* Get name */
                GetPresetName( value );
                ClearRemainingPresets();
            }
        }
    }
    else
    {
        if(askAciToStorePreset )
        {
            askAciToStorePreset = FALSE;
            if((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc )
                    ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
              )
            {
                DoSorting();                /* Do sorting */
            }
            if(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeAci)
            {
                /* Get name */
                GetPresetName( value );
                ClearRemainingPresets();
            }
        }
        else
        {    /*Aci Search fails at current preset search*/
            if(currentPresetAciSearch )
            {
                installationState = HsvinsStateSetFrequency;
                /* Set the tuner frequency to minimum, with finetune enabled */
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                }
                feapi_SetFreq( WINDOWID, freqctl_GetMinFrequency(), TRUE, &errorcode );
                currentPresetAciSearch = FALSE;
            }
            else /*Aci Search Fails in First Pass frequency Search*/
            {
                aciSearchOverFlag = TRUE;
                OnTvSystemDetected( value );
            }
        }

    }
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::AciTimeout(int value)
    /****************************************************
     * function to handle aci decode timeout event
     *****************************************************/
{
		    TraceDebug(m,"Hsvprins: %s %d value=%d",__FUNCTION__,__LINE__,value);

    if(aciTimeoutStarted )
    {
        /* Increment the time out counter*/
        aciTimeOutCounter ++;
		TraceDebug(m,"Hsvprins: %s %d aciPresetStorageOn = %d",__FUNCTION__,__LINE__,aciPresetStorageOn);
		
        if(aciTimeOutCounter == div_AciOverallTimeoutTime)
        {
            /* When timeout comes for ACI*/
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);
			
            if(!aciPresetStorageOn)
            {
		        TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);			
                aciTimeOutCounter = 0;
                pgaci_StopAciInstallation();
                aciTimeoutStarted = FALSE;
                AciStoreFail(value);
            }

        }
        else
        {
		    TraceDebug(m,"Hsvprins: %s %d",__FUNCTION__,__LINE__);		
            pmp_PmpSendAfter( prgInstallationPump
                    ,  insEventAciStoreTimeOut
                    , value
                    , LEAST_COUNT_FOR_ACI_TIMEOUT
                    );
        }
    }
}

void CHsvPresetInstallation_m_Priv::ClearRemainingPresets(void)
{
    if(div_SortPresetsInAutoStoreModeNone)
    {
        if(noOfPresetsFound != 0)
        {
            sortWithSignalStrength((Nat8 *)&PresetIndex[0], noOfPresetsFound+1);
            nbOfStationAfterSort = noOfPresetsFound+1;
			mCurrentSortingIndex = 0;
			TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
            StoreSortedList(0);
        }
		mCurrentSortingIndex = 0;
		TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
        StoreSortedList(0);
    }
    else
    {
        if(noOfPresetsFound != 0)
        {
            //pgdat_ClearTable(ANALOG_TABLE);  
            pgdat_ClearCurrentTable();
            /*            ClearPresets(noOfPresetsFound); */
        }
        else
        {
            InstallationCompleted();
        }
    }
}
/****************************************************/
void CHsvPresetInstallation_m_Priv::ClearPresets(int presetNo)
    /*****************************************************/
    /*Clears Presets After Automatic Installation in mode*/
    /*AutoSroreModeNone,AutoStoreModeAci                 */
    /*****************************************************/
{
    UNUSED(presetNo);
    ASSERT(!"This function is not used");
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::SetPresetDataIndicator( int prNo, Nat8 mask, Bool bit)
    /****************************************************
     * Purpose: returns Booean data indicator for a given 
     preset in the preset list
     ****************************************************/
{
    HsvPresetSortData *ptr;
    ptr = &PresetData[prNo];
    SetDataIndicator(ptr,mask,bit);
}

/****************************************************/
Bool CHsvPresetInstallation_m_Priv::GetPresetDataIndicator( int prNo, Nat8 mask)
    /****************************************************
     * Purpose: returns Booean data indicator for a given .
     preset in the preset list
     ****************************************************/
{
    HsvPresetSortData *ptr;
    ptr = &PresetData[prNo];
    return (GetDataIndicator(ptr,mask));
}

/****************************************************/
Bool CHsvPresetInstallation_m_Priv::IsVpsPkt830InfoReceived( HsvPresetSortData *ptr)
    /****************************************************
     * checks whether VPS and Packet 830 info arrived
     ****************************************************/
{
    return ( GetDataIndicator(ptr,MASK_VPS) &&
            (GetDataIndicator(ptr,MASK_PKT830CNI) ||  
             GetDataIndicator(ptr,MASK_PKT830NI))  );
}
/****************************************************/
void CHsvPresetInstallation_m_Priv::SetDataIndicator( HsvPresetSortData *ptr, Nat8 mask, Bool bit)
    /****************************************************
     * Purpose: sets Boolean data indicator for a given 
     preset
     ****************************************************/
{

    /*    ASSERT(! (mask & ~(MASK_RECEIVED | MASK_ARD| MASK_VPS | MASK_PKT830CNI | MASK_PKT830NI)) );*/

    if(bit)
    {
        ptr->DataIndicator |= mask;
    }
    else
    {
        ptr->DataIndicator &= (~mask);
    }
}
/****************************************************/
Bool CHsvPresetInstallation_m_Priv::GetDataIndicator( HsvPresetSortData *ptr, Nat8 mask )
    /****************************************************
     * Purpose: returns Boolean data indicator for a given 
     preset
     ****************************************************/
{
    Bool returnVal = FALSE;

    ASSERT( (mask == MASK_RECEIVED) ||
            (mask == MASK_ARD) ||
            (mask == MASK_VPS) ||
            (mask == MASK_PKT830CNI) ||
            (mask == MASK_PKT830NI) ||
            (mask == MASK_ATTENUATOR) ||
            (mask == MASK_TXTTRNAVLBL) );
    if(ptr->DataIndicator & mask )
    {
        returnVal = TRUE;
    }
    return(returnVal);
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::GetPresetName(int prNo)
    /****************************************************
     * Purpose: returns preset name for a given preset in 
     the preset list
     ****************************************************/
{
    GetPresetNameEx(&PresetData[prNo],prNo);
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::GetPresetNameEx(HsvPresetSortData * presetPtr,int preset)
    /****************************************************
     * Purpose: returns preset name for a given preset
     ****************************************************/
{
    Bool        ard;
    Nat16       selectedCni = 0;
    HsvCniName  cni_name;

    UNUSED(preset);
    ard = GetDataIndicator(presetPtr , MASK_ARD);
    //str_strncpy((char *)presetPtr->Name,DEFAULT_ANALOG_PRESET_NAME,DEFAULT_ANALOG_PRESET_LENGTH);
    if(cniname_iPresent())
    {
#if 1
        {
            cni_name = cniname_GetPresetName(currentVpsCni,currentPkt830Cni,currentPkt830Ni,ard);
        }
#else
        {
            cni_name.cniNi = cniname_CniNiInvalid;
            cni_name.name = defaultName;
        }
#endif

        if(cni_name.cniNi != cniname_CniNiInvalid)
        {
            selectedCni = cni_name.cniNi;
            if(selectedCni != currentVpsCni)
            {
                SetDataIndicator(presetPtr,MASK_VPS,FALSE);
            }
            if(selectedCni != currentPkt830Cni)
            {
                SetDataIndicator(presetPtr,MASK_PKT830CNI,FALSE);
            }
            if(selectedCni != currentPkt830Ni)
            {
                SetDataIndicator(presetPtr,MASK_PKT830NI,FALSE);
            }
            if(( euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc )
                    ||(euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci)
                    ||((div_SupportNameExtractionInManIns )/* the == TRUE was removed */
                        &&((installationMode == prins_InstallationModeManual) 
                            ||(installationMode == prins_InstallationModeImplicit)))
              )
            {
                str_strncpy( presetPtr->Name , (char*)cni_name.name, div_PresetNameLength);
            }
            else
            {
                str_strncpy( presetPtr->Name,(char *)&defaultName[0],div_PresetNameLength);
            }
        }
        else
        {
            if( GetDataIndicator(presetPtr,MASK_VPS) )
            {
                selectedCni = currentVpsCni;
                SetDataIndicator(presetPtr,MASK_PKT830NI | MASK_PKT830CNI,FALSE);
            }
            if( GetDataIndicator(presetPtr,MASK_PKT830CNI) )
            {
                selectedCni = currentPkt830Cni;
                SetDataIndicator(presetPtr,MASK_PKT830NI | MASK_VPS,FALSE);
            }
            if( GetDataIndicator(presetPtr,MASK_PKT830NI) )
            {
                selectedCni = currentPkt830Ni;
                SetDataIndicator(presetPtr,MASK_PKT830CNI | MASK_VPS,FALSE);
            }
        }
        presetPtr->CniNi = selectedCni;
    }
    else
    {
        if( GetDataIndicator(presetPtr,MASK_VPS) )
        {
            selectedCni= currentVpsCni;
            SetDataIndicator(presetPtr,MASK_PKT830NI | MASK_PKT830NI,FALSE);
        }
        if( GetDataIndicator(presetPtr,MASK_PKT830CNI) )
        {
            selectedCni = currentPkt830Cni;
            SetDataIndicator(presetPtr,MASK_PKT830NI | MASK_VPS,FALSE);
        }
        if( GetDataIndicator(presetPtr,MASK_PKT830NI) )
        {
            selectedCni = currentPkt830Ni;
            SetDataIndicator(presetPtr,MASK_PKT830CNI | MASK_VPS,FALSE);
        }
        presetPtr->CniNi = selectedCni;
    }
}


/****************************************************/
void CHsvPresetInstallation_m_Priv::AllocateMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases any memory which has been malloced 
     and mallocs again
     ****************************************************/
{
    int     i;
#if mem_iPresent_CONSTANT

    int     sizeOfMalloc;    

    ReleaseMemoryForPresetList();
    sizeOfMalloc = div_MaxAnalogPresets * (sizeof(HsvPresetSortData));
    PresetData = ( HsvPresetSortData * )mem_Malloc( sizeOfMalloc );
    ASSERT(PresetData != NULL);
    memo_memset((void *)PresetData,0,sizeOfMalloc);

    sizeOfMalloc = div_MaxAnalogPresets * div_PresetNameLength;
    presetNames = (char * )mem_Malloc( sizeOfMalloc );
    memo_memset((void *)presetNames,0,sizeOfMalloc);

    if(div_SortPresetsInAutoStoreModeNone)
    {
        sizeOfMalloc = div_MaxAnalogPresets * (sizeof(Nat8));
        PresetIndex = (Nat8 * )mem_Malloc( sizeOfMalloc );
        ASSERT(PresetIndex != NULL);
        memo_memset((void *)PresetIndex,0,sizeOfMalloc);
    }

#endif
    for (i = 0; i<div_MaxAnalogPresets; i++)
    {       
        PresetData[i].Name = presetNames + (i*div_PresetNameLength);
        PresetData[i].DataIndicator = 0;
        PresetData[i].Frequency = 0;
    }
    memo_memset((void *)presetNames,0x20,div_MaxAnalogPresets * div_PresetNameLength);
    if(div_SortPresetsInAutoStoreModeNone)
    {
        memo_memset((void *)PresetIndex,0,div_MaxAnalogPresets * sizeof(Nat8));
    }
}


/****************************************************/
void CHsvPresetInstallation_m_Priv::ReleaseMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/
{
#if mem_iPresent_CONSTANT
    if(PresetData != NULL)
    {
        mem_Free(0, PresetData);
        PresetData = NULL;
    }
    if(presetNames != NULL)
    {
        mem_Free(0, presetNames);
        presetNames = NULL;
    }
    if(div_SortPresetsInAutoStoreModeNone)
    {
        if(PresetIndex != NULL)
        {
            mem_Free(0, PresetIndex);
            PresetIndex = NULL;
        }
    }
#endif
}

/****************************************************/
Bool CHsvPresetInstallation_m_Priv::RequestVpsP830( HsvPresetSortData * presetPtr)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/
{
#if( 1 )
		//TraceNotice (m, "Hsvprins: Rahul %s %d  ", __FUNCTION__,__LINE__);

    if ( fieldCNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldCNI );
        fieldCNI = p830_InvalidRequestId;
    }
    if (fieldNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldNI );
        fieldNI = p830_InvalidRequestId;
    }
    if (fieldSTATUS != p830_InvalidRequestId)
    {
        p830_UnRequestDataFields ( fieldSTATUS );
        fieldSTATUS = p830_InvalidRequestId;
    }

    SetDataIndicator(presetPtr,MASK_PKT830CNI | MASK_PKT830NI,FALSE);
	currentinstance = this;
    fieldCNI    = p830_RequestDataFields(p830_CNICodeField,(VpsCbFn)FNADDR(OnReceivedPkt830CNI), FALSE);
    fieldNI     = p830_RequestDataFields(p830_NICodeField, (VpsCbFn)FNADDR(OnReceivedPkt830NI), FALSE);
    fieldSTATUS = p830_RequestDataFields(p830_StatusMessageField, (VpsCbFn)FNADDR(OnReceivedPkt830STATUS), FALSE);
    currentPkt830Ni = 0;
    currentPkt830Cni = 0;
    statusMessageFound = FALSE;

#endif

#if( 1)//vps_iPresent_CONSTANT )

    if (fieldVPS != vps_InvalidRequestId)
    {
        vps_UnRequestDataFields ( fieldVPS );
        fieldVPS = vps_InvalidRequestId;
    }
    SetDataIndicator(presetPtr,MASK_VPS,FALSE);
    currentVpsCni = 0;
    fieldVPS = vps_RequestDataFields(vps_CNICodeField|vps_DistinctionBitsField, (VpsCbFn) FNADDR (OnReceivedVps), FALSE);

#endif    

    StartTimeOut( 5000);//div_TxtInfoTimeoutTime );
    installationState = HsvinsStateAcquiringTxt;
	return TRUE;
#ifndef __cplusplus
   // return( vps_iPresent_CONSTANT || p830_iPresent_CONSTANT );
#else
	//return( vps_iPresent() || p830_iPresent() );
#endif

}

/****************************************************/
void CHsvPresetInstallation_m_Priv::DoSorting(void)
    /****************************************************
     * Purpose: if any presets are found during band search,
     * this function calls the sorting functions.  
     ****************************************************/
{
    /* Do sorting */
    if( prinsN_iPresent() )
    {
        prinsN_OnEvent( prinsN_EventATSSortingStarted,  HSVPRINS_INVALID_VALUE);
    }
    if(noOfPresetsFound != 0)
    {
        if(prsort_iPresent())
        {
			TraceNotice (m, "Going for SVPATS sort TotalNum %d ", noOfPresetsFound);
            nbOfStationAfterSort = prsort_Sort(PresetData, div_MaxAnalogPresets, noOfPresetsFound );
        }
        else
        {
            nbOfStationAfterSort = noOfPresetsFound;
        }
		TraceNotice (m, "StoreSortedList from %d  ", __LINE__);
		mCurrentSortingIndex = 0;
        StoreSortedList(0);
    }
    else
    {
        InstallationCompleted();
    }
}


/****************************************************/
int CHsvPresetInstallation_m_Priv::StartChannelSearch( tmFe_ChanTable_t cht )
    /****************************************************
     * Purpose: Starts manual installation for S or C channel
     ****************************************************/
{
    Nat32 errorcode = TM_OK;

    UInt32 StartChannel = 0;
    UInt32  freq;
    UInt32  chan = 0, nxtchan;

    if(div_SorCChannelSupported)
    {
        installMode = TRUE;
        if( setChannelManual )
        {
            installationState = HsvinsStateSetFrequency;
            if (div_AttenuatorDetectionInInstall)
            {
                //feapi_Set( WINDOWID, mRfaMaxAmplification, &errorcode );
                /*rfa_SetAmplification(rfa_MaxAmplification);*/
            }

            //feapi_SetTable( WINDOWID, cht, &errorcode );
            /*chan_SetChannelTable( cht );*/
            feapi_GetCarrierFreq( WINDOWID, setChannel, cht, &freq, &errorcode );
            if( prinsN_iPresent() )
            {
                prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
            }
            feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode ); 
            /*tun_SetFrequency(chan_CarrierFrequency( setChannel, cht ),fineTune);*/

            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );
            /*tun_SetTvSystem(tun_TvSystemNone);*/
        }
        else
        {
            fineTune = FALSE;
            installationState = HsvinsStateSearching;
            //feapi_SetTable( WINDOWID, cht, &errorcode ); 
            /* chan_SetChannelTable( cht ); */
            feapi_GetFreq( WINDOWID, &lastTunerFrequency, &errorcode );
            /*lastTunerFrequency = tun_GetFrequency();*/
            feapi_GetFreq( WINDOWID, &freq, &errorcode );
            feapi_Freq2Chan( WINDOWID, freq, cht, &chan, &errorcode ); 

            if( chan != 0 ) 
            {                
                StartChannel = chan;
                //feapi_GetNextChan( WINDOWID, chan, cht, &nxtchan, &errorcode );
                feapi_GetCarrierFreq( WINDOWID, nxtchan, cht, &freq, &errorcode );
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                } 
                feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode );
                /*tun_SetFrequency(chan_CarrierFrequency(  chan_NextChannel(chan_Frequency2Channel(tun_GetFrequency(),cht),cht),cht ) ,fineTune);*/                
            }
            else
            {
                //feapi_GetFirstChan( WINDOWID, cht, &StartChannel, &errorcode ); 
                /* StartChannel = chan_FirstChannel(cht); */
                //feapi_GetFirstChan( WINDOWID, cht, &nxtchan, &errorcode ); 
                feapi_GetCarrierFreq( WINDOWID, nxtchan, cht, &freq, &errorcode );
                if( prinsN_iPresent() )
                {
                    prinsN_OnEvent( prinsN_EventTuningStarted, HSVPRINS_INVALID_VALUE );
                } 
                feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode );
                /*tun_SetFrequency(chan_CarrierFrequency( chan_FirstChannel(cht),cht ) ,fineTune);*/
            }
            feapi_SetTvSystem( WINDOWID, tmFe_TvSystemNone, &errorcode );
            /*tun_SetTvSystem(tun_TvSystemNone);*/
        }
    }
    else
    {
        ASSERT(!"S or C channel not supported");
    }
    return (StartChannel);
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::UpdateCniNameInManual(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in manual installation
     ****************************************************/
{
#if( 1 )

    if ( fieldCNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldCNI );
        fieldCNI = p830_InvalidRequestId;
    }
    if (fieldNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldNI );
        fieldNI = p830_InvalidRequestId;
    }
    if (fieldSTATUS != p830_InvalidRequestId)
    {
        p830_UnRequestDataFields ( fieldSTATUS );
        fieldSTATUS = p830_InvalidRequestId;
    }

#endif

#if( 1 )

    if (fieldVPS != vps_InvalidRequestId)
    {
        vps_UnRequestDataFields ( fieldVPS );
        fieldVPS = vps_InvalidRequestId;
    }

#endif

    GetPkt0NameEx( &miPreset,preset.Channel.AnalogNo);
    /* Call get name from */
    GetPresetNameEx( &miPreset,preset.Channel.AnalogNo);

    if( manualInstallationPendingStore )
    {
        manualInstallationPendingStore = FALSE;
        noOfPresetsFound =1;
        StoreDataEx(&miPreset,preset, TRUE);
    }
    else
    {
        ChannelFound();
    }
}


/****************************************************/
void CHsvPresetInstallation_m_Priv::UpdateCniNameInAutomatic(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in automatic installation
     ****************************************************/
{
    presetFoundInFirstPass = FALSE;
#if(1 )

    if ( fieldCNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldCNI );
        fieldCNI = p830_InvalidRequestId;
    }
    if (fieldNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldNI );
        fieldNI = p830_InvalidRequestId;
    }
    if (fieldSTATUS != p830_InvalidRequestId)
    {
        p830_UnRequestDataFields ( fieldSTATUS );
        fieldSTATUS = p830_InvalidRequestId;
    }

#endif


#if( 1 )

    if (fieldVPS != vps_InvalidRequestId)
    {
        vps_UnRequestDataFields ( fieldVPS );
        fieldVPS = vps_InvalidRequestId;
    }

#endif

    if(1)
    {
        SetPresetDataIndicator(preset.Channel.AnalogNo,MASK_TXTTRNAVLBL ,( txtpre_WstPresent() || txtpre_VpsPresent()) );
        /*        PresetData[preset].txtTransmissionAvailable = ( (txtpre_WstPresent() )||(txtpre_VpsPresent()));*/
    }
    else
    {
        SetPresetDataIndicator(preset.Channel.AnalogNo,MASK_TXTTRNAVLBL ,FALSE);
        /*        PresetData[preset].txtTransmissionAvailable = FALSE;*/
    }
    GetPkt0Name( preset.Channel.AnalogNo );    
    GetPresetName( preset.Channel.AnalogNo ); /* Get name from */

    /* Find the preset if it is found in first pass without teletext */
    if(  ( !automaticInstallationFirstPass )
            && (noOfPresetFoundInFirstPass != 0)
            &&(euconfig_GetAutoStoreMode() != euconfig_AutoStoreModeAci)
      )
    {
        presetFoundInFirstPass = PresetSearch(noOfPresetFoundInFirstPass,
                PresetData[preset.Channel.AnalogNo].Frequency,FALSE);
    }
    if(!(presetFoundInFirstPass))
    {
        StoreData();
    }
    else
    {
        ClearCurrentPreset();
        ChannelFound();
        if(!(allMemoryFilled))
        {
            currentPreset.Channel.AnalogNo++;
        }
    }
    ContinueSearch();
}

Bool CHsvPresetInstallation_m_Priv::StartBackgroundPresetUpdation(HsvChannel channel,Bool updateOnlyCni)
{
    Bool SigStrMeasHandle = TRUE;
    Nat32 errorcode = TM_OK;

    Bool ret = TRUE;
    Bool retVal;
    UInt32  freq; 
    if( prgInstallationTurnOn )
    {
        if(backGroundCniUpdationOn)
        {

#if( p830_iPresent_CONSTANT )

            if ( fieldCNI != p830_InvalidRequestId )
            {
                p830_UnRequestDataFields ( fieldCNI );
                fieldCNI = p830_InvalidRequestId;
            }
            if (fieldNI != p830_InvalidRequestId )
            {
                p830_UnRequestDataFields ( fieldNI );
                fieldNI = p830_InvalidRequestId;
            }
            if (fieldSTATUS != p830_InvalidRequestId)
            {
                p830_UnRequestDataFields ( fieldSTATUS );
                fieldSTATUS = p830_InvalidRequestId;
            }
#endif

#if( 1 )

            if (fieldVPS != vps_InvalidRequestId)
            {
                vps_UnRequestDataFields ( fieldVPS );
                fieldVPS = vps_InvalidRequestId;
            }
#endif
        }
        updateOnlyCniInBackground = updateOnlyCni;
        installationMode = prins_InstallationModeImplicit;
        currentPreset = channel;
        statusMessageFound = FALSE;

        if(!updateOnlyCni)
        {
            changePresetAttrib = TRUE;
        }
        noOfPresetsFound = 0;
        noOfNewPresetsFound =   0;
        installationStopped = FALSE;
        manualStationFoundFlag = TRUE;
        installMode = FALSE;
        feapi_GetFreq( WINDOWID, &freq, &errorcode );
        miPreset.Frequency = freq; /* tun_GetFrequency(); */

        SetDataIndicator(&miPreset,MASK_RECEIVED,FALSE);
        /* Start txt decoding and wait for TXT information */
        if (div_AttenuatorDetectionInInstall)
        {
            if( SigStrMeasHandle  && (!(updateOnlyCniInBackground)) )
            {
                signalStrengthMeasurementInProgress = TRUE;
                feapi_Start( WINDOWID, feapi_SigSssm, &retVal, &errorcode );

            }
            else
            {
                if(RequestVpsP830(&miPreset))
                {
                    backGroundCniUpdationOn = TRUE;
                }
            }
        }
        else
        {
            if(RequestVpsP830(&miPreset))
            {
                backGroundCniUpdationOn = TRUE;
            }
        }
    }
    return(ret);
}

/****************************************************/
void CHsvPresetInstallation_m_Priv::UpdatePresetInBackground(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in implicit installation
     ****************************************************/
{
    Bool tuneBit = FALSE;
    Bool cniUpdated;    

#if( p830_iPresent_CONSTANT )

    if ( fieldCNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldCNI );
        fieldCNI = p830_InvalidRequestId;
    }
    if (fieldNI != p830_InvalidRequestId )
    {
        p830_UnRequestDataFields ( fieldNI );
        fieldNI = p830_InvalidRequestId;
    }
    if (fieldSTATUS != p830_InvalidRequestId)
    {
        p830_UnRequestDataFields ( fieldSTATUS );
        fieldSTATUS = p830_InvalidRequestId;
    }

#endif

#if( 1 )

    if (fieldVPS != vps_InvalidRequestId)
    {
        vps_UnRequestDataFields ( fieldVPS );
        fieldVPS = vps_InvalidRequestId;
    }

#endif

    if(!updateOnlyCniInBackground)
    {
        GetPkt0NameEx(&miPreset, preset.Channel.AnalogNo );
    }
    /* Call get name from */
    GetPresetNameEx(&miPreset, preset.Channel.AnalogNo);
    lastPresetFound = preset;
    noOfPresetsFound++;
    backGroundCniUpdationOn = FALSE ;
    if( !installationStopped )
    {
        if( miPreset.CniNi !=0 )
        {
            SetDataIndicator(&miPreset,MASK_RECEIVED,TRUE);
            cniUpdated = UpdateCNIinPgData( miPreset, preset );
            if(updateOnlyCniInBackground )
            {
                /* 
                   if( prinsN_iPresent() )        // for background CNI updation of EPG give notification all the time
                   {
                   prinsN_OnBackgroundCniUpdated( miPreset.CniNi,preset );
                   }
                   */
            }
            else
            {
                /* 
                   if( prinsN_iPresent() && cniUpdated)    //for implicit installation give notification only if CNI changes
                   {
                   prinsN_OnBackgroundCniUpdated(miPreset.CniNi,preset);
                   }
                   */
            }
        }
        else 
        {
            /* 
               if( prinsN_iPresent() && updateOnlyCniInBackground)
               {               
               prinsN_OnBackgroundCniUpdated(prins_InvalidCni,preset);
               }
               */
        }
    }

    if(pgdat_IsAttributeSupported(pgdat_BoolTuned))
    {
        pgdat_GetChannelDataBool (preset, pgdat_BoolTuned, &tuneBit );
    }

    if(!(tuneBit) && !(updateOnlyCniInBackground) )
    {
        fineTune = TRUE;
        StoreDataEx(&miPreset,preset, TRUE);
    }
    InstallationCompleted();
}

void CHsvPresetInstallation_m_Priv::ClearCurrentPreset(void)
{
    PresetData[currentPreset.Channel.AnalogNo].CniNi =  0;
    SetPresetDataIndicator(currentPreset.Channel.AnalogNo,MASK_RECEIVED | MASK_VPS | MASK_PKT830CNI | MASK_PKT830NI,FALSE);
    PresetData[currentPreset.Channel.AnalogNo].Frequency = 0;
}

int CHsvPresetInstallation_m_Priv::GetPresetIndexAfterSorting(int index)
{
    int retIndex;

	/* ANEESH: Putting this return here. */
	retIndex = index;
		//	TraceNotice (m, "Hsvprins: Rahul %s %d retIndex=%d ", __FUNCTION__,__LINE__,retIndex);

    if(prsort_iPresent() &&
            ((euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdcAci) ||
             (euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeVpsPdc))
      )
    {
        retIndex = prsort_GetPresetIndex(index);
    }
    else if( div_SortPresetsInAutoStoreModeNone &&
            (euconfig_GetAutoStoreMode() == euconfig_AutoStoreModeNone))
    {
        retIndex = PresetIndex[index];
    }
    else
    {
        retIndex = index;
    }
	
    return(retIndex);
}

void CHsvPresetInstallation_m_Priv::SignalStrengthDetectionCompleted(int value)
{
    UInt32 sigst;
    Bool SigStrMeasHandle = TRUE;
    Nat32 errorcode = TM_OK;
    if( div_AttenuatorDetectionInInstall )
    {
        if( signalStrengthMeasurementInProgress )/* the == TRUE was removed */
        {
            signalStrengthMeasurementInProgress = FALSE;
            switch(installationMode)
            {
                case prins_InstallationModeImplicit:
                    if( SigStrMeasHandle )
                    {
                        feapi_GetSigStrength( WINDOWID, feapi_SigSssm, &sigst, &errorcode );
                    }
                    if ( SigStrMeasHandle && ( sigst >= div_WeakSignalStrengthThreshold))
                    {
                        SetDataIndicator(&miPreset,MASK_ATTENUATOR,TRUE);
                    }
                    else
                    {
                        SetDataIndicator(&miPreset,MASK_ATTENUATOR,FALSE);
                    }
                    if(RequestVpsP830(&miPreset))
                    {
                        backGroundCniUpdationOn = TRUE;
                    }
                    break;
                case prins_InstallationModeManual:
                    if ( SigStrMeasHandle )                        
                    {
                        feapi_GetSigStrength( WINDOWID, feapi_SigSssm, &sigst, &errorcode ); 
                        if( sigst >= div_WeakSignalStrengthThreshold )
                        {
                            SetDataIndicator(&miPreset,MASK_ATTENUATOR,TRUE);
                            //feapi_Set( WINDOWID, mRfaMinAmplification, &errorcode );
                        }
                    }
                    else
                    {
                        SetDataIndicator(&miPreset,MASK_ATTENUATOR,FALSE);
                        //feapi_Set( WINDOWID, mRfaMaxAmplification, &errorcode );
                    }
                    OnTvSystemDetected(value);
                    break;
                case prins_InstallationModeAutomatic:
                    if ( SigStrMeasHandle)  
                    {
                        feapi_GetSigStrength( WINDOWID, feapi_SigSssm, &sigst, &errorcode ); 
                        if( sigst >= div_WeakSignalStrengthThreshold )
                        {
                            SetPresetDataIndicator(value,MASK_ATTENUATOR,TRUE);
                        }
                    }
                    else
                    {
                        SetPresetDataIndicator(value,MASK_ATTENUATOR,FALSE);
                    }
                    OnTvSystemDetected( value );
                    break;
                default:
                    ASSERT(FALSE);
                    break;
            }
        }
    }
}

void CHsvPresetInstallation_m_Priv::sortWithSignalStrength(Nat8 *list ,int elements)
    /*****************************************************/
    /*  Parametrs :  List of the elements passed         */
    /*               Number of members passed            */  
    /*Purpose:       Sort  within the Group              */
    /*****************************************************/
{
    Nat8 temp;
    int i;
    int j;
    if(div_SortPresetsInAutoStoreModeNone )
    {
        for (i=elements-1;i>1;i--)
        {
            for(j=1;j<i;j++)
            {
                if(PresetData[ list[j] ].SignalStrength<PresetData[ list[j+1] ].SignalStrength)
                {
                    temp = list[j+1];
                    list[j+1] = list[j];
                    list[j] = temp;
                }
                if(PresetData[ list[j] ].SignalStrength == PresetData[ list[j+1] ].SignalStrength)
                {
                    if(PresetData[ list[j] ].Frequency > PresetData[ list[j+1] ].Frequency)
                    {
                        temp = list[j+1];
                        list[j+1] = list[j];
                        list[j] = temp;
                    }
                }
            }
        }
    }
}

void CHsvPresetInstallation_m_Priv::pacidsN_OnMultiPackageDisplayed ( void )
{
    aciTimeoutStarted = FALSE;
}


void CHsvPresetInstallation_m_Priv::pacidsN_OnMultiPackageFound ( void )
{
	prinsN_OnEvent(prinsN_EventMultiPackageFound, 0);
}    
void CHsvPresetInstallation_m_Priv::pacidsN_OnMultiPackageToBeDisplayed ( void )
{
	prinsN_OnEvent(prinsN_EventMultiPackageToBeDisplayed, 0);
}
void CHsvPresetInstallation_m_Priv::pacidsN_OnMultiPackageRemoved ( void )
{
	prinsN_OnEvent(prinsN_EventMultiPackageRemoved, 0);
}


#if CHECK_SECAML_SUPPORT

Bool CHsvPresetInstallation_m_Priv::IsSECAMLSupported( )
{
    Bool supp = FALSE;
    tmErrorCode_t errorcode = TM_OK;
    feapi_GetTvSystemSupp( WINDOWID, tmFe_TvSystemL, &supp, &errorcode );
    ASSERT( TM_OK == errorcode );
    return supp;
}
#endif



void CHsvPresetInstallation_m_Priv::WaitForColorSystem(int param1, Nat32 param2)
{
    int             colsystem   = 0;
    tmFe_TvSystem_t tvSystem    = 0;
    Nat32 errorcode = TM_OK;
    UInt32          freq;

    UNUSED (param1);
    UNUSED (param2);
    feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode ); 
    ASSERT ( errorcode == TM_OK );
    colsystem = col_GetColorSystem();

    if (( col_Secam == colsystem ) && ( tmFe_TvSystemL == tvSystem ))
    {
        stationFoundFlag = TRUE;
        feapi_GetFreq( WINDOWID, &freq, &errorcode);
        ASSERT(freq);
        if( prinsN_iPresent() )
        {
            prinsN_OnEvent( prinsN_EventTuningStationFound, HSVPRINS_INVALID_VALUE );
        }
        pmp_PmpSend( prgInstallationPump, insEventStationFound, freq );
    }
    else
    {
        /* false channel found during secam search */
        /* restart searching */
        StartSearching( (tmFe_SearchMode_t)searchmode, freqendpos );

    }
}   /* WaitForColorSystem */
/*
   static tmErrorCode_t StartSearching( ptmIFeTuning thif, tmFe_SearchMode_t mode, UInt32 endFreq )
   {
   tmErrorCode_t errorcode;
   searchmode = mode;
   freqendpos = endFreq;
   errorcode = tmIFeTuning_StartSearch( thif, mode, endFreq );           
   return ( errorcode );
   }
   */

tmErrorCode_t CHsvPresetInstallation_m_Priv::StartSearching( tmFe_SearchMode_t mode, UInt32 endFreq )
{
    tmErrorCode_t errorcode = TM_OK;
    UInt32 freq;

    searchmode = mode;
    freqendpos = endFreq;

    feapi_GetFreq( WINDOWID, &freq, &errorcode );

    TraceDebug(m,"hsvprins: StartSearching: freq = %ld, max = %d",freq, freqctl_GetMaxFrequency());
    if( (freq >= (UInt32)freqctl_GetMaxFrequency()) && (installationMode == prins_InstallationModeAutomatic) )
    {
        TraceDebug(m," hsvprins: %d::pmpsend of stationnotfound",__LINE__);
        pmp_PmpSend( prgInstallationPump, insEventStationNotFound, 0 );               
    }
    else /*freq < freqctl_GetMaxFrequency() */ 
    {        
    	if (freq < freqctl_GetMinFrequency())
		{
			freq = freqctl_GetMinFrequency();
		}
        /* In manual installation with the criteria freq >= freqctl_GetMaxFrequency() can come when we trigger
           the manual search at freqctl_GetMaxFrequency(), so we need to start the search, and plf will do the automatic wrap around
           to Minfreq and then start the search */

        TraceDebug(m,"hsvprins: StartSEarch called");
        installationState = HsvinsStateSearching;
		/*TODO: check if passing get freq as start freq is fine*/
        feapi_StartSearch( WINDOWID,freq,mode, endFreq, &errorcode );
    }
    return ( errorcode );
}


int CHsvPresetInstallation_m_Priv::prins_GetInstallationPass()
{
    return AnalogPassNo;
}

int CHsvPresetInstallation_m_Priv::prins_GetNoOfPass(void)
{
    int retval = 0;
    if(SECOND_PASS_REQUIRED /*div_SecondPassSearchSupported(country)*/ )
    {
        retval = 2;
    }
    else
    {
        retval = 1; 
    }
    return retval;
}

int CHsvPresetInstallation_m_Priv::prins_GetInstallationState(void)
{
    return installationState;
}

void CHsvPresetInstallation_m_Priv::prins_SetHandleTunerFreqNotify(Bool val)
{
    HndlSetTunerFreqNtf = val;
}


HsvDvbTvSystem CHsvPresetInstallation_m_Priv::ConvertFromPlatformTvSystem(tmFe_TvSystem_t inval)
{
    HsvDvbTvSystem outval = (HsvDvbTvSystem)0;
	
	/* ANEESH: TODO: These values below are assigned as per TuningAna.Java 
		All the hardcoding should be removed and made proper */
	int countryCode = sysset_GetSystemCountry();



	switch(inval)
	{
		case	tmFe_TvSystemL:
			outval = (HsvDvbTvSystem)0x00000008;
			break;
		case	tmFe_TvSystemBg:
			outval = (HsvDvbTvSystem)0x00000001;
			break;
		case	tmFe_TvSystemI:
				outval = (HsvDvbTvSystem)0x00000002;
			break;
		case	tmFe_TvSystemDk:
				outval = (HsvDvbTvSystem)0x00000004;
			break;
		case 	tmFe_TvSystemM:
				outval = (HsvDvbTvSystem)0x00000010;
			break;
		case 	tmFe_TvSystemBG_A2:
				outval = (HsvDvbTvSystem)0x00000020;
			break;
		case 	tmFe_TvSystemDK_A2:
				outval = (HsvDvbTvSystem)0x00000040;
			break;
		default:
			break;
	}
    return outval;
}


/* Returns TRUE, if the update is sucessfull */

Bool CHsvPresetInstallation_m_Priv::UpdateCNIinPgData( HsvPresetSortData data, HsvChannel channel )
{
    Bool retVal = FALSE;
    int CniNi, dataind;

    if( pgdat_IsAttributeSupported(pgdat_IntCniNi) && pgdat_IsAttributeSupported(pgdat_IntDataIndicator) )
    {
        if( chanlibret_Ok == (pgdat_GetChannelDataInt(channel, pgdat_IntCniNi, &CniNi) ))
        {   
            if(data.CniNi != CniNi )
            {
                pgdat_StoreChannelDataInt(channel, pgdat_IntCniNi, data.CniNi);
                retVal = TRUE;
            }
        }
        else
        {
            ASSERT(FALSE);
        }

        if( chanlibret_Ok == (pgdat_GetChannelDataInt(channel, pgdat_IntDataIndicator, &dataind) ))
        {
            if(data.DataIndicator != dataind )
            {
                pgdat_StoreChannelDataInt(channel, pgdat_IntDataIndicator, data.DataIndicator);
                retVal = TRUE;            
            }
        }
        else
        {
            ASSERT(FALSE);
        }
    }
    return retVal;

}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvPresetInstallation_m_Priv::feapiN_OnSearchInProgress(tmFe_SearchState_t state )
{
}

void CHsvPresetInstallation_m_Priv::feapiN_OnSearchStateChanged(tmFe_SearchState_t state)
{
	return;
}


void CHsvPresetInstallation_m_Priv::feapiN_OnAfcLimitReached(Nat32 freq )
{
}

void CHsvPresetInstallation_m_Priv::feapiN_OnAfcModeChanged() 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvPresetInstallation_m_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}

    
/* TV System functions */    
Bool CHsvPresetInstallation_m_Priv::prins_IsTvSystemSupported( int instvsystem )
{
	return FALSE;
}
void CHsvPresetInstallation_m_Priv::prins_SetTvSystem( int instvsystem )
{
}
int CHsvPresetInstallation_m_Priv::prins_GetTvSystem( void )
{
	return 0;
}
    
	    
    /* Color system functions */
Bool CHsvPresetInstallation_m_Priv::prins_IsColorSystemSupported( int colorsystem )
{
	return FALSE;
}
void CHsvPresetInstallation_m_Priv::prins_SetColorSystem (int colorsystem)
{
}
int CHsvPresetInstallation_m_Priv::prins_GetColorSystem(void)
{
	return 0;
}


void CHsvPresetInstallation_m_Priv::prins_SetTunerFrequency( int freq, Bool fineTune )
{
	Nat32 errorcode = 0;
	TraceDebug(m,"Hsvprins: %s %d Set Frequency = %d", __FUNCTION__,__LINE__,freq);
	feapi_SetFreq( WINDOWID, freq, fineTune, &errorcode );
	ASSERT( errorcode == TM_OK );
}
