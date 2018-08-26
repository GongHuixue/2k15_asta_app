/**********************************************************************
 *
 *   C Source:       hsvdvbcins_msettings.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    ponraman %
 *   %date_created:  Fri Jan 18 18:27:01 2013 %
 *
 **********************************************************************/
#include "_hsvdvbcins_msettings.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_msettings")

#include "hsvdvbcins.h"
#include <sys/stat.h>




int CHsvDvbCInstallation_msettings_Priv::s__mConstellation[14] =
{
/*HsvUnknownConstellation*/ tmFe_UnknownConstellation,
/*HsvAutoConstellation*/    tmFe_AutoConstellation,
/*HsvBpsk*/                 tmFe_Bpsk,
/*HsvQpsk*/                 tmFe_Qpsk,
/*Hsv8psk*/                 tmFe_8psk,
/*HsvQam4*/                 tmFe_Qam4,
/*HsvQam16*/                tmFe_Qam16,
/*HsvQam32*/                tmFe_Qam32,
/*HsvQam64*/                tmFe_Qam64,
/*HsvQam128*/               tmFe_Qam128,
/*HsvQam256*/               tmFe_Qam256,
/*HsvQam1024*/              tmFe_Qam1024,
/*HsvVsb8*/                 tmFe_Vsb8,
/*HsvVsb16*/                tmFe_Vsb16
};


int CHsvDvbCInstallation_msettings_Priv::s__ModulationVals[MAX_MODULATION_VALS]  = { 
                            HsvQam128, 
                            HsvQam64,
                            HsvQam256,
                            HsvQam32, 
                            HsvQam16 
                        };



int CHsvDvbCInstallation_msettings_Priv::s__ModulationVals_Sweden    [MAX_MOD_TYP] = { HsvQam64, HsvQam128,HsvQam256 };
 
int CHsvDvbCInstallation_msettings_Priv::s__ModulationVals_Norway    [MAX_MOD_TYP] = { HsvQam128,HsvQam256,HsvQam64 };

int CHsvDvbCInstallation_msettings_Priv::s__ModulationVals_Denmark   [MAX_MOD_TYP] = { HsvQam128,HsvQam256,HsvQam64 };


int CHsvDvbCInstallation_msettings_Priv::s__SearchRates_Sweden [MAX_SETS][MAX_SYMRATES_PER_SET] =    {   { 6875000, 6950000, 7000000, 6900000, INVALID_SYMBOLRATE },
                                                                { 5957000, 6000000, 6125000, 6900000, INVALID_SYMBOLRATE },
                                                                { 6950000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };


int CHsvDvbCInstallation_msettings_Priv::s__SearchRates_Norway [MAX_SETS][MAX_SYMRATES_PER_SET] =    {   { 5957000, 6000000, 6125000, 6900000, 6875000 },
                                                                { 6950000, 6900000, 6875000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE },
                                                                { 6900000, 6875000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };


int CHsvDvbCInstallation_msettings_Priv::s__SearchRates_Denmark [MAX_SETS][MAX_SYMRATES_PER_SET] =   {   { 5957000, 6000000, 6125000, 6875000, 6900000 },
                                                                { 6950000, 6875000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE },
                                                                { 6875000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };

/*************************************************************************
 * Local Structures and enums
 **************************************************************************/

/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/









//static void mGetPathName(char* dirName, char* FileName, char* PathName);



/****************************************************************************
 * Static variables
 ****************************************************************************/
HsvDVBSettings CHsvDvbCInstallation_msettings_Priv::s__mCurrentData;

HsvDVBSettings CHsvDvbCInstallation_msettings_Priv::s__mDefaultData;

HsvDVBSettings CHsvDvbCInstallation_msettings_Priv::s__mPersistentData;

HsvDVBSettings CHsvDvbCInstallation_msettings_Priv::s__mConsistencyCheckData;

/* Used for storage during Digital test reception */
HsvDVBSettings CHsvDvbCInstallation_msettings_Priv::s__mManualData;

char CHsvDvbCInstallation_msettings_Priv::s__mDirName[MAX_CHARACTERS];

char CHsvDvbCInstallation_msettings_Priv::s__mFileName[MAX_CHARACTERS];

/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvDvbCInstallation_msettings_Priv::mLoadDefaults(HsvDVBSettings* tmpdata)
{
    int i, dummyint;
    int Param;
    Nat8 option;


    if(eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkOperator, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&Param)))
    {
        tmpdata->NetworkOperator = Param;
		dummyint = Param;
        TraceDebug(m,"Function:%s::Line=%d::NetworkOperator=%d",__FUNCTION__,__LINE__,tmpdata->NetworkOperator);
    }	
    if(eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&Param)))
    {
        tmpdata->ScanMode = Param;
        TraceDebug(m,"Default Scan Mode = %d",tmpdata->ScanMode);
    }
    if(eurdiv_GetDefaultAttributeValues(rins_AttributeSymbolRate, SYS_COUNTRY, &(tmpdata->SymbolRateMode), (int*) (&(tmpdata->SymbolRateLen)), (int*) (tmpdata->SymbolRate)))
    {
  /*      TraceDebug(m,"Default SymbolRate Mode = %d",tmpdata->SymbolRateMode);
        TraceDebug(m,"Default SymbolRate Len  = %d",tmpdata->SymbolRateLen);
        for(dummyint = 0; dummyint < tmpdata->SymbolRateLen; dummyint++)
        {
            TraceDebug(m,"Default SymbolRate[%d] = %lu",dummyint,tmpdata->SymbolRate[dummyint]);
        }
		*/
    }
    /* Only 1 value not an array */
    if(eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkId, SYS_COUNTRY, &(tmpdata->NetworkIDMode), &dummyint, (int*) (&(tmpdata->NetworkID))))
    {
        /*TraceDebug(m,"Default NtkID Mode = %d",tmpdata->NetworkIDMode);*/
        TraceDebug(m,"Default NtkID = %d",tmpdata->NetworkID);
    }
    if(eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkFreq, SYS_COUNTRY, &(tmpdata->NetworkFrequencyMode), (int*) (&(tmpdata->NetworkFrequencyLen)), (int*) (tmpdata->NetworkFrequency)))
    {
        /*TraceDebug(m,"Default NtkFreq Mode = %d",tmpdata->NetworkFrequencyMode);
        TraceDebug(m,"Default NtkFreq Len  = %d",tmpdata->NetworkFrequencyLen);
        for(dummyint = 0; dummyint < tmpdata->NetworkFrequencyLen; dummyint++)
        {
            TraceDebug(m,"Default NtkFreq[%d] = %lu",dummyint,tmpdata->NetworkFrequency[dummyint]);
        }*/
		
    }
    if(eurdiv_GetDefaultAttributeValues(rins_AttributeModulation, SYS_COUNTRY, &(tmpdata->ModulationMode), (int*) (&(tmpdata->ModulationLen)), (int*) (tmpdata->Modulation)))
    {
		/*
        TraceDebug(m,"Default Modulation Mode = %d",tmpdata->ModulationMode);
        TraceDebug(m,"Default Modulation Len  = %d",tmpdata->ModulationLen);

        for(dummyint = 0; dummyint < tmpdata->ModulationLen; dummyint++)
        {
            TraceDebug(m,"Default Modulation[%d] = %ld",dummyint,tmpdata->Modulation[dummyint]);
        }
		*/
    }
    if( eurdiv_GetDefaultAttributeValues(rins_AttributeDigitalOption, SYS_COUNTRY, &option, &dummyint, (int*) (&Param)) )
    {
        tmpdata->DigitalOption = Param;
        //TraceDebug(m,"Default Digital Option = %d",tmpdata->DigitalOption);
    }
	
	if( eurdiv_GetDefaultAttributeValues(rins_AttributeDualAnalogPass, SYS_COUNTRY, &option, &dummyint, (int*) (&Param)) )
    {
        tmpdata->DualAnalogPass = Param;
        //TraceDebug(m,"Default DualAnalogPass Option = %d",tmpdata->DualAnalogPass);
    }
	
	    if( eurdiv_GetDefaultAttributeValues(rins_AttributeDTTScanOnAnalog, SYS_COUNTRY, &option, &dummyint, (int*) (&Param)) )
    {
        tmpdata->DTTScanonAnalog = Param;
        //TraceDebug(m,"Default DTTScanonAnalog = %d",tmpdata->DTTScanonAnalog);
    }
	
	if( eurdiv_GetDefaultAttributeValues(rins_AttributeLCNOption, SYS_COUNTRY, &option, &dummyint, (int*) (&Param)) )
    {
        tmpdata->LCNOption = Param;
        //TraceDebug(m,"Default LCNOption = %d",tmpdata->LCNOption);
    }

    tmpdata->UserSymbolRateLen = MAX_USERSYMRATES;
    for(i = 0; i < tmpdata->UserSymbolRateLen; i++)
    {
        tmpdata->UserSymbolRate[i] = 0;
    }
    tmpdata->FreqStepSize = DEFAULT_STEP_SIZE;
    tmpdata->InstalledCity = cityids_CityBeijing;
    tmpdata->InstalledONID  = INVALID_ONID;

    if(eurdiv_GetDefaultAttributeValues(rins_AttributeScrOrFTA, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&Param)))
    {
        tmpdata->ScrambledState = Param;
        //TraceDebug(m,"Function:%s::Line=%d::scrambled State=%d",__FUNCTION__,__LINE__,tmpdata->ScrambledState);
    }
	
	if(eurdiv_GetDefaultAttributeValues(rins_AttributeLCNSorting, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&Param)))
    {
        tmpdata->LCNSorting = Param;
        //TraceDebug(m,"%s LCNSorting %d\n",__FUNCTION__, tmpdata->LCNSorting);
    }
}

void CHsvDvbCInstallation_msettings_Priv::mAttributeCopy(HsvDVBSettings* dest, HsvDVBSettings* src, int attribute)
{
    int i = 0;

    switch(attribute)
    {
        case rins_AttributeScanMode:
            dest->ScanMode = src->ScanMode;
            break;
        case rins_AttributeNetworkId:
            dest->NetworkIDMode = src->NetworkIDMode;
            dest->NetworkID = src->NetworkID;
            break;
        case rins_AttributeSymbolRate:
            dest->SymbolRateMode = src->SymbolRateMode;     
            dest->SymbolRateLen = src->SymbolRateLen;
            dest->UserSymbolRateLen = src->UserSymbolRateLen;
            for(i = 0; i < dest->UserSymbolRateLen; i++)
            {
                dest->UserSymbolRate[i] = src->UserSymbolRate[i];
            }
            for(i = 0; i < dest->SymbolRateLen; i++)
            {
                dest->SymbolRate[i] = src->SymbolRate[i];
            }
            break;
        case rins_AttributeNetworkFreq:
            dest->NetworkFrequencyMode = src->NetworkFrequencyMode;
            dest->NetworkFrequencyLen = src->NetworkFrequencyLen;
            for(i = 0; i < dest->NetworkFrequencyLen; i++)
            {
                dest->NetworkFrequency[i] = src->NetworkFrequency[i];
            }
            break;
        case rins_AttributeModulation:
            dest->ModulationMode = src->ModulationMode;
            dest->ModulationLen = src->ModulationLen;
            for(i = 0; i < dest->ModulationLen; i++)
            {
                dest->Modulation[i] = src->Modulation[i];
            }
            break;
        case rins_AttributeDigitalOption:
            dest->DigitalOption = src->DigitalOption;
            break;
        case rins_AttributeFreqStepSize:
            dest->FreqStepSize  = src->FreqStepSize;
            break;
        case rins_AttributeCity:
            dest->InstalledCity  = src->InstalledCity;
            break;



        case rins_AttributeScrOrFTA:
            dest->ScrambledState = src->ScrambledState;
            break;

        case rins_AttributeNetworkOperator:
            dest->NetworkOperator = src->NetworkOperator;
            break;
		case rins_AttributeLCNSorting:
            dest->LCNSorting = src->LCNSorting;
            break;
		case rins_AttributeDualAnalogPass:
       		dest->DualAnalogPass = src->DualAnalogPass;
			break;
		case rins_AttributeDTTScanOnAnalog:	
       		dest->DTTScanonAnalog = src->DTTScanonAnalog;
            break;	
		case rins_AttributeLCNOption:	
       		dest->LCNOption = src->LCNOption;
            break;			
        default:
            ASSERT(FALSE);
            break;
    }
}

Bool CHsvDvbCInstallation_msettings_Priv::mModeCopy(HsvDVBSettings* tmp, int attribute, int mode)
{
    Bool retval = TRUE;
    int i=0;
    switch(attribute)
    {
        case rins_AttributeScanMode:
            retval = FALSE;
            ASSERT(!"No automatic or manual value for ScanMode");
            break;
        case rins_AttributeSymbolRate:
            {
                tmp->SymbolRateMode = mode;         
                if( (tmp->SymbolRateMode == rins_AutomaticValue) || (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite) )
                {
                    tmp->SymbolRateLen = mDefaultData.SymbolRateLen;
                    for( i = 0 ; i < tmp->SymbolRateLen ; i++ )
                    {
                        tmp->SymbolRate[i] = mDefaultData.SymbolRate[i];
                    }
                }           
            }
            break;
        case rins_AttributeNetworkId:
            {
                tmp->NetworkIDMode = mode;
                if( tmp->NetworkIDMode == rins_AutomaticValue )
                {
                    tmp->NetworkID = mDefaultData.NetworkID;
                }
            }
            break;
        case rins_AttributeNetworkFreq:
            {    
                tmp->NetworkFrequencyMode = mode;
                if( tmp->NetworkFrequencyMode == rins_AutomaticValue )
                {
                    tmp->NetworkFrequencyLen = mDefaultData.NetworkFrequencyLen;
                    for( i = 0 ; i < tmp->NetworkFrequencyLen ; i++ )
                    {
                        tmp->NetworkFrequency[i] = mDefaultData.NetworkFrequency[i];
                    }
                }
				if(SYS_COUNTRY == cids_CountryRomania)
				{
					eurdiv_GetDefaultAttributeValues(rins_AttributeModulation, SYS_COUNTRY, &(mCurrentData.ModulationMode), (int*) (&(mCurrentData.ModulationLen)), (int*) (mCurrentData.Modulation));
				}
            }
            break;
        case rins_AttributeModulation:
            tmp->ModulationMode = mode;
            break;
        case rins_AttributeDigitalOption:
            retval = FALSE;
            ASSERT(!"No automatic or manual value for DigitalOption");
            break;

        case rins_AttributeFreqStepSize:
            retval = FALSE;
            ASSERT(!"No automatic or manual value for step size");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

Bool CHsvDvbCInstallation_msettings_Priv::mAttributeValueCopy(HsvDVBSettings* tmp, int attribute, int value)
{
    Bool retval = TRUE;

    switch(attribute)
    {
        case rins_AttributeScanMode:
            tmp->ScanMode = value;
            break;
        case rins_AttributeNetworkId:
            if(tmp->NetworkIDMode == rins_ManualValue)
            {
                tmp->NetworkID = value;
                //TraceDebug(m,"NetworkID set = %d",value);
            }
            else
            {
                retval = FALSE;
                TraceDebug(m,"Cannot set NetworkID");
            }
            break;
        case rins_AttributeSymbolRate:
            if(tmp->SymbolRateMode == rins_ManualValue)
            {
                retval = FALSE;
                //TraceDebug(m,"tmp->SymbolRateLen: %d symbol rate[0] :  %ld\n", tmp->SymbolRateLen, tmp->SymbolRate[0]);
            }
            else
            {
                retval = FALSE;
            }
            break;
        case rins_AttributeNetworkFreq:
            if(tmp->NetworkFrequencyMode == rins_ManualValue)
            {
                tmp->NetworkFrequencyLen = 1;
                tmp->NetworkFrequency[0] = value;
                //TraceDebug(m,"SetFrequency = %d : ",value);
            }
            else
            {
                retval = FALSE;
            }
            break;
        case rins_AttributeModulation:
            if(tmp->ModulationMode == rins_ManualValue)
            {
                tmp->ModulationLen = 1;
                tmp->Modulation[0] = value;
            }
            else
            {
                /* Assumption as modulation would not be manual */
                if(eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)
                {
                    /* User has cancelled the Network Frequency/Network ID wizard */
                    tmp->ModulationLen = 3; 
                }
                else
                {       
                    retval = FALSE;
                }
            }
            break;
        case rins_AttributeDigitalOption:
            tmp->DigitalOption = value;
            break;
        case rins_AttributeFreqStepSize:
            tmp->FreqStepSize = value;
            break;
        case rins_AttributeCity:
            tmp->InstalledCity  = value;
            break;


        case rins_AttributeScrOrFTA:
            tmp->ScrambledState = value;
            break;

        case rins_AttributeNetworkOperator:
            tmp->NetworkOperator  = value;
            break;
		case rins_AttributeLCNSorting:
            tmp->LCNSorting  = value;
            break;
	    case rins_AttributeDualAnalogPass:
            tmp->DualAnalogPass  = value;
            break;
		case rins_AttributeDTTScanOnAnalog:
            tmp->DTTScanonAnalog  = value;
            break;	
		case rins_AttributeLCNOption:
            tmp->LCNOption  = value;
            break;			
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

int CHsvDvbCInstallation_msettings_Priv::mGetAttrMode(HsvDVBSettings* tmp, int attribute)
{
    int retval = 0;
    switch(attribute)
    {
        case rins_AttributeScanMode:
            ASSERT(!"ScanMode doesnt have Auto/Manual");
            break;
        case rins_AttributeNetworkId:
            retval = tmp->NetworkIDMode;
            break;
        case rins_AttributeSymbolRate:
            retval = tmp->SymbolRateMode;
            break;
        case rins_AttributeNetworkFreq:
            retval = tmp->NetworkFrequencyMode;
            break;
        case rins_AttributeModulation:
            retval = tmp->ModulationMode;
            break;
        case rins_AttributeDigitalOption:
            ASSERT(!"Digital Option doesnt have Auto/Manual");
            break;
        case rins_AttributeFreqStepSize:
            ASSERT(!"Frequency step size doesnt have Auto/Manual");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

int CHsvDvbCInstallation_msettings_Priv::mGetAttrValue(HsvDVBSettings* tmp, int attribute)
{
    int retval = 0;
	
    switch(attribute)
    {
        case rins_AttributeScanMode:
            retval = tmp->ScanMode;
            break;
        case rins_AttributeNetworkId:
            retval = tmp->NetworkID;
            //TraceDebug(m,"retval of NetworkID = %d",retval);
            break;
        case rins_AttributeSymbolRate:
            retval = FALSE;
            break;
        case rins_AttributeNetworkFreq:
            retval = tmp->NetworkFrequency[0];
            break;
        case rins_AttributeModulation:
            retval = tmp->Modulation[0];
            break;
        case rins_AttributeDigitalOption:
            retval = tmp->DigitalOption;
            break;
        case rins_AttributeFreqStepSize:
            retval = tmp->FreqStepSize;
            break;
        case rins_AttributeScrOrFTA:
            retval = tmp->ScrambledState;
            break;
        case rins_AttributeCity:
            retval = tmp->InstalledCity;
            break;
        case rins_AttributeNetworkOperator:
            retval = tmp->NetworkOperator;
            break;
		case rins_AttributeLCNSorting:
            retval = tmp->LCNSorting;
            break;
		case rins_AttributeDualAnalogPass:
       		retval = tmp->DualAnalogPass;
	        //TraceDebug(m,"retval of DualAnalogPass = %d",retval);		
			break;
		case rins_AttributeDTTScanOnAnalog:	
       		retval = tmp->DTTScanonAnalog;
	        //TraceDebug(m,"retval of DTTScanonAnalog = %d",retval);					
            break;		
		case rins_AttributeLCNOption:	
       		retval = tmp->LCNOption;
	        //TraceDebug(m,"retval of LCNOption = %d",retval);					
            break;			
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

void CHsvDvbCInstallation_msettings_Priv::mInitialiseStruct(HsvDVBSettings* tmp)
{
    tmp->ScanMode = rins_QuickScan;
    tmp->SymbolRateMode = rins_AutomaticValue;
    tmp->SymbolRateLen = 0;
    tmp->NetworkIDMode = rins_AutomaticValue;
    tmp->NetworkID = INVALID_NETWORKID;
    tmp->NetworkFrequencyMode = rins_AutomaticValue;
    tmp->NetworkFrequencyLen = 0;
    tmp->ModulationMode = rins_AutomaticValue;
    tmp->ModulationLen = 0;
    tmp->DigitalOption = TRUE;
    tmp->FreqStepSize           = rins_DVBCStepSize8;
    tmp->InstalledONID  = INVALID_ONID;
    tmp->ScrambledState = FALSE;
	tmp->DTTScanonAnalog = FALSE;
	tmp->DualAnalogPass = FALSE;
	tmp->LCNOption = TRUE;
}


int CHsvDvbCInstallation_msettings_Priv::mGetNextAttrib(HsvDVBSettings* tmp, int attribute, Nat32 value)
{
    int i = 0, retval = 0;
    static int k =0;

    switch(attribute)
    {
        case rins_AttributeScanMode:
        case rins_AttributeNetworkId:
        case rins_AttributeDigitalOption:
        case rins_AttributeFreqStepSize:
            ASSERT(!"No length for vector values");
            break;
        case rins_AttributeSymbolRate:
            retval = INVALID_SYMBOLRATE;

            if(value == INVALID_SYMBOLRATE)
            {
                retval = tmp->SymbolRate[0];
                k++;
            }
            else
            {
                for(i = 0; i < tmp->SymbolRateLen; i++)
                {
                    if(value == tmp->SymbolRate[i])
                    {
                        break;
                    }
                }
                if(i < (tmp->SymbolRateLen -  1))
                {
                    retval = tmp->SymbolRate[i + 1];
                    k++;
                }
            }

            if( ( (retval == INVALID_SYMBOLRATE) || k > tmp->SymbolRateLen) 
                    && (tmp->SymbolRateMode == rins_ManualValue) )
            {
                if(k == tmp->SymbolRateLen)
                {
                    retval = tmp->UserSymbolRate[0];
                    k++;
                }
                else
                {
                    for(i = 0; i < tmp->UserSymbolRateLen; i++)
                    {
                        if(value == tmp->UserSymbolRate[i])
                        {
                            break;
                        }
                    }
                    if(i < (tmp->UserSymbolRateLen -  1))
                    {
                        retval = tmp->UserSymbolRate[i + 1];
                        k++;
                    }
                }
            }

            if(tmp->SymbolRateMode == rins_ManualValue)
            {
                if(k >= (tmp->SymbolRateLen + tmp->UserSymbolRateLen) )
                {
                    k = 0;
                }
            }
            else
            {
                if(k >= tmp->SymbolRateLen)
                {
                    k = 0;
                }
            }       
            break;
        case rins_AttributeNetworkFreq:
            retval = INVALID_FREQUENCY;

            if(value == INVALID_FREQUENCY)
            {
                retval = tmp->NetworkFrequency[0];
            }
            else
            {
                for(i = 0; i < tmp->NetworkFrequencyLen; i++)
                {
                    if(value == tmp->NetworkFrequency[i])
                    {
                        break;
                    }
                }
                if(i < (tmp->NetworkFrequencyLen - 1))
                {
                    retval = tmp->NetworkFrequency[i + 1];
                }
            }
            break;
        case rins_AttributeModulation:
            retval = HsvUnknownConstellation;

            if(value == HsvUnknownConstellation)
            {
                retval = tmp->Modulation[0];
            }
            else
            {
                for(i = 0; i < tmp->ModulationLen; i++)
                {
                    if(value == tmp->Modulation[i])
                    {
                        break;
                    }
                }
                if(i < (tmp->ModulationLen -1))
                {
                    retval = tmp->Modulation[i + 1];
                }
            }
            break;
        default:
            ASSERT(FALSE);
        break;
    }
    return retval;
}    

void CHsvDvbCInstallation_msettings_Priv::mGetPredefinedSymbolRatesNordic(int country, int *SearchRates, int *SearchRateLen )
{
    int i, j, k, newentry = FALSE;
    int aslen = 0;

    for (i = 0; i  < MAX_SETS; i++)
    {
        for (j = 0; j < MAX_SYMRATES_PER_SET; j++)
        {
            if (aslen < MAX_PREDEFINE_SYMRATE)
            {
                newentry = TRUE;
                switch (country)
                {
                    case cids_CountrySweden:
                        SearchRates[aslen]  = SearchRates_Sweden[i][j];
                        break;  
                    case cids_CountryNorway:    
                        SearchRates[aslen]  = SearchRates_Norway[i][j];                 
                        break;  
                    case cids_CountryDenmark:
                        SearchRates[aslen]  = SearchRates_Denmark[i][j];
                        break;
                }
                newentry = (SearchRates[aslen] == INVALID_SYMBOLRATE) ? FALSE : TRUE;
                if ((aslen > 0) && (newentry == TRUE))
                {
                    for (k = 0; k < aslen; k++)
                    {
                        if (SearchRates[aslen] == SearchRates[k])
                        {
                            newentry = FALSE;
                        }
                    }
                }
                if (newentry == TRUE)
                {
                    aslen++;
                }
            }
        }
    }
    if(aslen > MAX_SEARCH_RATES)
    {
        *SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        *SearchRateLen = aslen;
    }
    UNUSED (mConstellation);
    UNUSED (ModulationVals);
    UNUSED (ModulationVals_Sweden);
    UNUSED (ModulationVals_Norway);
    UNUSED (ModulationVals_Denmark);

}
Bool CHsvDvbCInstallation_msettings_Priv::mIsPersistentFileAvailable()
{
    FILE* fp;
    int readRecords;
	Bool retval = FALSE;
//	struct stat Stat;

	mGetFilePath();
	
    //TraceDebug(m,"Fopen of %s", mFileName);

    fp = fopen(mFileName, "rb");
    
	if(fp)
    {
        readRecords = fread((Address)(&mConsistencyCheckData), sizeof(mConsistencyCheckData), 1, fp);
        if(readRecords)
        {
			retval = TRUE;
			//TraceDebug(m,"Persistent Settings is Present");
		}
		fclose(fp);
	}

	return retval;
}
    
/********************************
  provides IHsvPower isetpow
 ********************************/
void CHsvDvbCInstallation_msettings_Priv::isetpow_Init()
{
    /* Invalidate all the values */
    mInitialiseStruct(&mDefaultData);
    mInitialiseStruct(&mCurrentData);
    mInitialiseStruct(&mPersistentData);
    mInitialiseStruct(&mManualData);
    mManualData.ScanMode = rins_FullScan;
}
void CHsvDvbCInstallation_msettings_Priv::isetpow_TurnOn()
{
    FILE* fp;
    int readRecords;
	char FileName[MAX_CHARACTERS];
	struct stat statbuf;
	
    mLoadDefaults(&mDefaultData);
    mLoadDefaults(&mCurrentData);
    mLoadDefaults(&mPersistentData);
    mLoadDefaults(&mManualData);
    mManualData.ScanMode = rins_FullScan;

    mGetFilePath();
    
    if(apsysset_GetVirginBit () == TRUE)
    {
        //TraceNotice(m,"%s %d idvbset_ClearPersistent\n", __FUNCTION__, __LINE__);
        idvbset_ClearPersistent();
    }
    else
	{
	    fp = fopen(mFileName, "rb");
	    if(fp)
	    {
	        readRecords = fread((Address)(&mPersistentData), sizeof(mPersistentData), 1, fp);
	        if(readRecords)
	        {
	            TraceDebug(m,"Persistent Settings is loaded from Flash file");
	            TraceDebug(m,"Write Persistent Settings to Current");
	            idvbset_ResetAllToPersistent();

	            /*NB: below hack is reqd when CR4 to EXT, as enum values of modulation is changed b/w */
	            //TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
	            mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeModulation);
	            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeModulation);
	        }
	        else
	        {
	            TraceDebug(m,"Nothing present in the file.Load Defaults instead");
	        }
	        fclose(fp);
	    }
	    else
	    {
	        TraceDebug(m,"No Flash file present.Load Defaults instead");
	    }
	
   		/* Also load Default data to manual data */
    	idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeScanMode);
   		idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeNetworkId);
    	idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeSymbolRate);
    	idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeNetworkFreq);
    	idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeModulation);
    	idvbset_ResetAttributeToDefault(MANUAL_MODE, rins_AttributeScrOrFTA);
	}

	/*If file does not exists, create the file and change the ownership for HsvDVBCSettings*/
	if (stat(mFileName, &statbuf) == -1)
	{
		fp = fopen(mFileName, "w+" );
		fclose(fp);
		//TraceNotice(m,"%s: %d :File is created",__FUNCTION__,__LINE__);
	}

	/*ownership need to be changed if file is created by older SW also*/
	if(chown(mFileName,-1,AID_USER_SETTING) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chown: %d",__FUNCTION__,__LINE__);
	}
	if(chmod(mFileName, (S_IRWXU | S_IRWXG )) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chmod : %d",__FUNCTION__,__LINE__);
	}

	
	/*If file does not exists, craete the file and change the ownership for HsvServiceListDescFile*/
	str_strcpy (FileName, "/user_setting/rw/tvserver/databases/channellib/HsvServiceListDescFile");
	if (stat(FileName, &statbuf) == -1)
	{
		fp = fopen(FileName, "w+" );
		fclose(fp);
		//TraceNotice(m,"%s: %d :File is created",__FUNCTION__,__LINE__);
	}

	/*ownership need to be changed if file is created by older SW also*/
	if(chown(FileName,-1,AID_USER_SETTING) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chown: %d",__FUNCTION__,__LINE__);
	}
	if(chmod(FileName, (S_IRWXU | S_IRWXG )) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chmod : %d",__FUNCTION__,__LINE__);
	}
	
	/*If file does not exists, craete the file and change the ownership for HsvCableDelSysDescFile*/
	str_strcpy (FileName, "/user_setting/rw/tvserver/databases/channellib/HsvCableDelSysDescFile");

	if (stat(FileName, &statbuf) == -1)
	{
		fp = fopen(FileName, "w+" );
		fclose(fp);
		//TraceNotice(m,"%s: %d :File is created",__FUNCTION__,__LINE__);
	}

	/*ownership need to be changed if file is created by older SW also*/
	if(chown(FileName,-1,AID_USER_SETTING) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chown: %d",__FUNCTION__,__LINE__);
	}
	if(chmod(FileName, (S_IRWXU | S_IRWXG )) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chmod : %d",__FUNCTION__,__LINE__);
	}

	
}
void CHsvDvbCInstallation_msettings_Priv::isetpow_TurnOff()
{
}

/********************************
  IHsvDVBSettings idvbset
 ********************************/
/* Set and Get works on temporary data */
Bool CHsvDvbCInstallation_msettings_Priv::idvbset_GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue)
{
    Bool retval = FALSE;
    Nat32 plfretval = 0;
    FResult plferr = plferrids_Ok;

    UNUSED(installationmode);
    if(attribute == rins_AttributeSymbolRate)
    {
        plferr = feapi_GetSymbolRateRange( WINDOWID, (Nat32*) (minValue), (Nat32*) (maxValue), &plfretval );
        ASSERT(plferr == plferrids_Ok);
        ASSERT(plfretval == TM_OK);
        retval = TRUE;
    }
    else if(attribute == rins_AttributeNetworkId)
    {
        *minValue = 0;
        /* NetworkId >= 0xFF01 is treated as invalid as per FRS */
        *maxValue = (eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable) == eurdiv_Install)? 0xFFFF : 0xFF00;       
        retval = TRUE;
    }
    else if(attribute == rins_AttributeNetworkFreq)
    {
        *minValue = START_FREQUENCY;
        *maxValue = END_FREQUENCY;
        retval = TRUE;
    }
    else
    {
        ASSERT(!"Invalid Attribute");
    }
    return retval;    
}

Bool CHsvDvbCInstallation_msettings_Priv::idvbset_SetAttributeMode(int installationmode, int attribute, int attributeMode)
{
    Bool retval = FALSE;

	//TraceNotice(m,"[%s] [%d] Mode attribute[%d] attributeMode[%d] \n",__FUNCTION__,__LINE__,attribute,attributeMode);
    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mModeCopy(&mCurrentData, attribute, attributeMode);
    }
    else if(installationmode == MANUAL_MODE)
    {
        retval = mModeCopy(&mManualData, attribute, attributeMode);
    }
    return retval;
}

Bool CHsvDvbCInstallation_msettings_Priv::idvbset_SetAttribute(int installationmode, int attribute, int value)
{
    Bool retval = TRUE;
    int dummyint,dummyint2, TmpNetworkOperator;
    int mode;
    int Param;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
		TmpNetworkOperator = mCurrentData.NetworkOperator;
		
        retval = mAttributeValueCopy(&mCurrentData, attribute, value);
        if(rins_AttributeScanMode == attribute) {   
            eurdiv_GetDefaultAttributeValues(rins_AttributeSymbolRate, SYS_COUNTRY, &(mCurrentData.SymbolRateMode), (int*) (&(mCurrentData.SymbolRateLen)), (int*) (mCurrentData.SymbolRate));
        }
        else if(rins_AttributeNetworkOperator == attribute)
        {
        	dummyint = value;
            eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&mode));
            eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkFreq, SYS_COUNTRY, (Nat8*)(&mCurrentData.NetworkFrequencyMode), (int*) (&mCurrentData.NetworkFrequencyLen), (int*) (mCurrentData.NetworkFrequency));
			eurdiv_GetDefaultAttributeValues(rins_AttributeModulation, SYS_COUNTRY, (Nat8*)(&mCurrentData.ModulationMode), (int*) (&mCurrentData.ModulationLen), (int*) (mCurrentData.Modulation));
				
			if(TmpNetworkOperator != mCurrentData.NetworkOperator)
			{
				eurdiv_GetDefaultAttributeValues(rins_AttributeSymbolRate, SYS_COUNTRY, (Nat8*) (&dummyint), (int*) (&mCurrentData.SymbolRateLen), (int*) (mCurrentData.SymbolRate));  /* brg36mgr#151973 */
				mCurrentData.ScanMode = mode;
				mCurrentData.NetworkID = 0;
				mCurrentData.NetworkIDMode = -1;
				if ((SYS_COUNTRY == cids_CountryBelgium) && (mCurrentData.NetworkOperator == rins_None))
				{
					mCurrentData.ScrambledState = 0;
				}
				else if((SYS_COUNTRY == cids_CountryBelgium) && (mCurrentData.NetworkOperator == rins_Telenet))
				{
					eurdiv_GetDefaultAttributeValues(rins_AttributeScrOrFTA, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, &Param);
					mCurrentData.ScrambledState = Param;
				}
				if ((SYS_COUNTRY == cids_CountryBelgium) && (mCurrentData.NetworkOperator == rins_Telenet)){
					eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkId, SYS_COUNTRY, &(mCurrentData.NetworkIDMode), &dummyint, (int*) (&(dummyint2 /*mCurrentData.NetworkID*/)));
					mCurrentData.NetworkID = (dummyint2 & 0xFFFF);
				}
				if ((SYS_COUNTRY == cids_CountryDenmark)&& (mCurrentData.NetworkOperator == rins_YouSee)) {
					eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkId, SYS_COUNTRY, &(mCurrentData.NetworkIDMode), &dummyint, (int*) (&(dummyint2 /*mCurrentData.NetworkID*/)));
					mCurrentData.NetworkID = (dummyint2 & 0xFFFF); 
				}
			}
			else
			{
				mCurrentData.ScanMode = mode;

				if(SYS_COUNTRY == sysset_GetInstallCountry())
				{
					mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeScanMode);
					mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeNetworkFreq);
					mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeModulation);
					
				}
				else 
				{
						if ((SYS_COUNTRY == cids_CountryBelgium) && (mCurrentData.NetworkOperator == rins_Telenet)) {
							eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkId, SYS_COUNTRY, &(mCurrentData.NetworkIDMode), &dummyint, (int*) (&(dummyint2 /*mCurrentData.NetworkID*/)));
							mCurrentData.NetworkID = (dummyint2 & 0xFFFF); 
						}
						
						if ((SYS_COUNTRY == cids_CountryDenmark)&& (mCurrentData.NetworkOperator == rins_YouSee)) {
							eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkId, SYS_COUNTRY, &(mCurrentData.NetworkIDMode), &dummyint, (int*) (&(dummyint2 /*mCurrentData.NetworkID*/)));
							mCurrentData.NetworkID = (dummyint2 & 0xFFFF); 
						}
				}

				dummyint = mCurrentData.NetworkOperator;
				if ((SYS_COUNTRY == cids_CountrySwitzerland) && (mCurrentData.NetworkOperator == rins_UPC))
				{
					/* During Virgin installation, medium is Terrestrial. Hence reloading of ScanMode will not be correct.
						For Switzerland/UPC reloading the correct value */
					eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&mode));
					mCurrentData.ScanMode = mode;
				}
				if ((SYS_COUNTRY == cids_CountryBelgium) && (mCurrentData.NetworkOperator == rins_Telenet))
				{
					eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&mode));
					mCurrentData.ScanMode = mode;
					if (apsysset_GetVirginBit() == TRUE)
					{
						/* For virgin installation we need not reload the values from persistent. Reload network value from default */
						eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkFreq, SYS_COUNTRY, (Nat8*)(&mCurrentData.NetworkFrequencyMode), (int*) (&mCurrentData.NetworkFrequencyLen), (int*) (mCurrentData.NetworkFrequency));
					}
				}
				if ((SYS_COUNTRY == cids_CountryRomania) && (mCurrentData.NetworkOperator == rins_UPC))
				{
					eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&mode));
					mCurrentData.ScanMode = mode;
					if (apsysset_GetVirginBit() == TRUE)
					{
						/* For virgin installation we need not reload the values from persistent. Reload network value from default */
						eurdiv_GetDefaultAttributeValues(rins_AttributeNetworkFreq, SYS_COUNTRY, (Nat8*)(&mCurrentData.NetworkFrequencyMode), (int*) (&mCurrentData.NetworkFrequencyLen), (int*) (mCurrentData.NetworkFrequency));
					}
				}
				
				if ((SYS_COUNTRY == cids_CountrySlovenia) && (mCurrentData.NetworkOperator == rins_Telemach))
				{
					
					eurdiv_GetDefaultAttributeValues(rins_AttributeScanMode, SYS_COUNTRY, (Nat8*) (&dummyint), &dummyint, (int*) (&mode));
					mCurrentData.ScanMode = mode;
				}
				
				
				//TraceNotice(m, "%s PreviousNetworkOperator %d CurrentNetworkOperator %d mCurrentData.ScanMode %d", __FUNCTION__, TmpNetworkOperator, mCurrentData.NetworkOperator, mCurrentData.ScanMode);
			}						
        }		
    }
    else if(installationmode == MANUAL_MODE)
    {
        retval = mAttributeValueCopy(&mManualData, attribute, value);
    }
    if(retval == FALSE)
    {
        ASSERT(!"Cant set values in Automode");
    }
    return retval;
}

int CHsvDvbCInstallation_msettings_Priv::idvbset_GetAttributeMode(int installationmode, int attribute)
{
    int retval = 0;


    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mGetAttrMode(&mCurrentData, attribute);
    }
    else if(installationmode == MANUAL_MODE)
    {
        retval = mGetAttrMode(&mManualData, attribute);
    }
    return retval;
}

int CHsvDvbCInstallation_msettings_Priv::idvbset_GetAttribute(int installationmode, int attribute)
{
    int retval = 0;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mGetAttrValue(&mCurrentData, attribute);
    }
    else if(installationmode == MANUAL_MODE)
    {
        retval = mGetAttrValue(&mManualData, attribute);
    }
    return retval;
}

Bool CHsvDvbCInstallation_msettings_Priv::idvbset_IsAvailable(int installationmode, int attribute) //added to solve PR brg36mgr#77588
{
    Bool retval = TRUE;
    FResult feapiretval = plferrids_Ok;
    Nat32 Decoder = feapi_ChanDecDvbC;

    /*feapiretval = feapi_GetChanDec(WINDOWID, &Decoder);
    ASSERT(feapiretval == plferrids_Ok);
	*/
	/* ANEESH: TODO: Chk this will cause any regression */

    if((attribute == rins_AttributeSymbolRate) && (feapi_ChanDecDvbT == Decoder) && (installationmode == MANUAL_MODE))
    {
        retval = FALSE;
    }
	if(attribute == rins_AttributeUpdateInstall)
	{
		/* if medium is cable and if previous scan is a failed quick scan its not available, else its always available */
				
		retval = TRUE;

		/* first check if medium is cable */

		if(rins_GetMedium() == rins_Cable)
		{
			if(mIsPersistentFileAvailable())
			{
				if((mConsistencyCheckData.ScanMode == rins_QuickScan ) && (VALID_NTKID(mConsistencyCheckData.NetworkID) == FALSE))
				{
					retval = FALSE;
				}
			}
			else
			{
				retval = FALSE;
			}
		}
	}
	else if(attribute == rins_AttributePersistentFile)
	{
		retval = mIsPersistentFileAvailable();
	}

	//TraceDebug(m,"Update Install possible = %d", retval);
    
	return retval;
}
/* Copies Default to Temporary */
void CHsvDvbCInstallation_msettings_Priv::idvbset_ResetAttributeToDefault(int installationmode, int attribute)
{
    int i = 0;

    //TraceDebug(m,"%s",__FUNCTION__);

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        mAttributeCopy(&mCurrentData, &mDefaultData, attribute);
    }
    else if(installationmode == MANUAL_MODE)
    {
        switch(attribute)
        {
            case rins_AttributeScanMode:
                mManualData.ScanMode = rins_FullScan;
                break;
            case rins_AttributeNetworkId:
                mManualData.NetworkID = mDefaultData.NetworkID;
                break;
            case rins_AttributeSymbolRate:
                mManualData.SymbolRateLen = mDefaultData.SymbolRateLen;
                for(i = 0; i < mManualData.SymbolRateLen; i++)
                {
                    mManualData.SymbolRate[i] = mDefaultData.SymbolRate[i];
                }
                mManualData.UserSymbolRateLen = mDefaultData.UserSymbolRateLen;
                for(i = 0; i < mManualData.UserSymbolRateLen; i++)
                {
                    mManualData.UserSymbolRate[i] = mDefaultData.UserSymbolRate[i];
                }
                break;
            case rins_AttributeNetworkFreq:
                mManualData.NetworkFrequencyLen = mDefaultData.NetworkFrequencyLen;
                for(i = 0; i < mManualData.NetworkFrequencyLen; i++)
                {
                    mManualData.NetworkFrequency[i] = mDefaultData.NetworkFrequency[i];
                }
                break;
            case rins_AttributeModulation:
                //TraceDebug(m,"mDefaultData.ModulationLen = %d",mDefaultData.ModulationLen);
                mManualData.ModulationLen = mDefaultData.ModulationLen;
                for(i = 0; i < mManualData.ModulationLen; i++)
                {
                    mManualData.Modulation[i] = mDefaultData.Modulation[i];
                }
                break;
            case rins_AttributeDigitalOption:
                mManualData.DigitalOption = mDefaultData.DigitalOption;
                break;
			case rins_AttributeScrOrFTA: 
				mManualData.ScrambledState = mDefaultData.ScrambledState;
				break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
}
/* Copies Persistent to Temporary */
void CHsvDvbCInstallation_msettings_Priv::idvbset_ResetAttributeToPersistent(int installationmode, int attribute)
{
    UNUSED(installationmode);
    //TraceDebug(m,"%s",__FUNCTION__);

    if(AUTO_MODE || UPDATE_MODE)
    {
        mAttributeCopy(&mCurrentData, &mPersistentData, attribute);
    }
    else if(MANUAL_MODE)
    {
        ASSERT(!"No persistent settings for Manaul mode");
    }
}
/* Copies all Default attributes to Temporary */
void CHsvDvbCInstallation_msettings_Priv::idvbset_ResetAllToDefault()
{
    //TraceDebug(m,"%s",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeScanMode);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeSymbolRate);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeNetworkId);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeNetworkFreq);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeModulation);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeDigitalOption);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeFreqStepSize);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeScrOrFTA);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeNetworkOperator);
	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeLCNSorting);
	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeDualAnalogPass);
	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeDTTScanOnAnalog);
	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeLCNOption);
	insN_OnEvent(insN_NetworkOperator,mCurrentData.NetworkOperator);
}
/* Copies all Persistent attributes to Temporary */
void CHsvDvbCInstallation_msettings_Priv::idvbset_ResetAllToPersistent()
{
    //TraceDebug(m,"%s",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeScanMode);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeSymbolRate);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeNetworkId);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeNetworkFreq);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeModulation);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeDigitalOption);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeFreqStepSize);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeCity);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeScrOrFTA);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeNetworkOperator);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeLCNSorting);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeDualAnalogPass);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeDTTScanOnAnalog);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeLCNOption);
	insN_OnEvent(insN_NetworkOperator,mCurrentData.NetworkOperator);
}

/* To get vector values. Used during auto install */
int CHsvDvbCInstallation_msettings_Priv::idvbset_GetAttributeLength(int installationmode, int attribute)
{
    int retval = 0;
    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        switch(attribute)
        {
            case rins_AttributeScanMode:
            case rins_AttributeNetworkId:
                ASSERT(!"No length for scalar values");
                break;
            case rins_AttributeSymbolRate:
                retval = mCurrentData.SymbolRateLen;            
                if( mCurrentData.SymbolRateMode == rins_ManualValue )
                {               
                    retval +=  mCurrentData.UserSymbolRateLen;
                }
                break;
            case rins_AttributeNetworkFreq:
                retval = mCurrentData.NetworkFrequencyLen;
                break;
            case rins_AttributeModulation:
                retval = mCurrentData.ModulationLen;
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
    else if(installationmode == MANUAL_MODE)
    {
        switch(attribute)
        {
            case rins_AttributeScanMode:
            case rins_AttributeNetworkId:
                ASSERT(!"No length for scalar values");
                break;
            case rins_AttributeSymbolRate:
                retval = mManualData.SymbolRateLen;         
                if( mManualData.SymbolRateMode == rins_ManualValue )
                {               
                    retval +=  mManualData.UserSymbolRateLen;
                }                       
                break;
            case rins_AttributeNetworkFreq:
                retval = mManualData.NetworkFrequencyLen;
                break;
            case rins_AttributeModulation:
                retval = mManualData.ModulationLen;
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
    return retval;
}

int CHsvDvbCInstallation_msettings_Priv::idvbset_GetNextAttributeValue(int installationmode, int attribute, int value)
{
    int retval = 0;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mGetNextAttrib(&mCurrentData, attribute, (Nat32)value);        
    }
    else if(installationmode == MANUAL_MODE)
    {
        retval = mGetNextAttrib(&mManualData, attribute, (Nat32)value);     
    }
    return retval;
}

/* To set values to preferred or not. If value not present, it is added to the top of list.
   Preferred notion is used by taking that value to top of the list. The list is copied to 
   persistent data which finally gets written to flash through CommitPreferred */

void CHsvDvbCInstallation_msettings_Priv::idvbset_SetPreferred(int attribute, int value, Bool preferred)
{
    /* preferred is set to TRUE. setting it to FALSE is handled by loading default
       data i.s.o preferred data. In this way preferred flag gets cleared. NO need
       to explicitly set preferred as FALSE */
    int i = 0, temp;
    Bool found = FALSE;
    UNUSED(preferred);

    //TraceDebug(m,"%s",__FUNCTION__);

    switch(attribute)
    {
        case rins_AttributeScanMode:
            ASSERT(!"ScanMode cant be preferred");
            break;
        case rins_AttributeNetworkId:
            mCurrentData.NetworkID = value;
            //      mPersistentData.NetworkID = value;
            break;
        case rins_AttributeSymbolRate:
            //TraceDebug(m,"SymRateLen = %d",mCurrentData.SymbolRateLen);
            found = FALSE;
            if(mCurrentData.SymbolRateMode != rins_ManualValue)
            {
                for( i = 0;i < mCurrentData.SymbolRateLen; i++)
                {
                    if((Nat32)value == mCurrentData.SymbolRate[i])
                    {
                        //TraceDebug(m,"Found value = %d",value);
                        found = TRUE;
                        break;
                    }
                }
                if(found)
                {
                    //TraceDebug(m,"Swapping 2 values %ld and %ld",(Nat32) mCurrentData.SymbolRate[0],(Nat32) mCurrentData.SymbolRate[i]);
                    temp = mCurrentData.SymbolRate[0];
                    mCurrentData.SymbolRate[0] = value;
                    mCurrentData.SymbolRate[i] = temp;
                }
                else
                {
                    /* new value to be inserted in the list */
                    //TraceDebug(m,"New Value to be inserted in the list = %d",value);
                    if((mCurrentData.SymbolRateLen + 1) == MAX_SYMBOL_RATES)
                    {
                        ASSERT(!"Sorry cant set the preferred value");
                    }
                    else
                    {
                        //TraceDebug(m,"Swapping 2 values %ld and %ld",(Nat32) mCurrentData.SymbolRate[0],(Nat32) mCurrentData.SymbolRate[mCurrentData.SymbolRateLen - 1]);
                        temp = mCurrentData.SymbolRate[0];
                        mCurrentData.SymbolRate[0] = value;
                        mCurrentData.SymbolRate[mCurrentData.SymbolRateLen++] = temp;
                    }
                }

                //TraceDebug(m,"Copying for Symbol Rate done");
/*
                for(i = 0 ; i < mCurrentData.SymbolRateLen; i++)
                {
                    //TraceDebug(m,"SymbolRate[%d] = %ld",i,(Nat32) mCurrentData.SymbolRate[i]);
                }
*/
                //TraceDebug(m,"Copying for Frequency Rate");
            }
            break;
        case rins_AttributeNetworkFreq:
           // TraceDebug(m,"NetworkFreqLen = %d",mCurrentData.NetworkFrequencyLen);
            found = FALSE;
            if(mCurrentData.NetworkFrequencyMode == rins_ManualValue)
            {
                //mCurrentData.NetworkFrequency[0] = value;
                TraceDebug(m,"User Entered frequency retained: %d", mCurrentData.NetworkFrequency[0]);
            }
            else
            {
                for( i = 0;i < mCurrentData.NetworkFrequencyLen; i++)
                {
                    if((Nat32)value == mCurrentData.NetworkFrequency[i])
                    {
              //          TraceDebug(m,"Found value = %d",value);
                        found = TRUE;
                        break;
                    }
					else if(CHECKDRIFT(mCurrentData.NetworkFrequency[i],(Nat32)value) < 16)
					{
						/*check if the drift is lesser than 1MHZ.*/
				//		TraceDebug(m,"Found value %d is within drift and near to %d",value,mCurrentData.NetworkFrequency[i]);
						found = TRUE;
						value = mCurrentData.NetworkFrequency[i];
						break;
					}                                                                              
                }
                if(found)
                {
                    //TraceDebug(m,"Swapping 2 values %ld and %ld",(Nat32) mCurrentData.NetworkFrequency[0],(Nat32) mCurrentData.NetworkFrequency[i]);
                    temp = mCurrentData.NetworkFrequency[0];
                    mCurrentData.NetworkFrequency[0] = value;
                    mCurrentData.NetworkFrequency[i] = temp;
                }
                else
                {
                    /* new value to be inserted in the list */
                    //TraceDebug(m,"New Value to be inserted in the list = %d",value);
                    if((mCurrentData.NetworkFrequencyLen + 1) == MAX_SYMBOL_RATES)
                    {
                        ASSERT(!"Sorry cant set the preferred value");
                    }
                    else
                    {
                    	
                        //TraceDebug(m,"Swapping 2 values %ld and %ld",(Nat32) mCurrentData.NetworkFrequency[0],(Nat32) mCurrentData.NetworkFrequency[mCurrentData.NetworkFrequencyLen-1]);
                        temp = mCurrentData.NetworkFrequency[0];
                        mCurrentData.NetworkFrequency[0] = value;
                        mCurrentData.NetworkFrequency[mCurrentData.NetworkFrequencyLen++] = temp;
                    }
                }

                //TraceDebug(m,"AFter modification of Freq");
/*
                for(i = 0 ; i < mCurrentData.NetworkFrequencyLen; i++)
                {
                    //TraceDebug(m,"Frequency[%d] = %ld",i,(Nat32) mCurrentData.NetworkFrequency[i]);
                }

                TraceDebug(m,"Copying for Frequency Rate");
				*/
            }
            //      mAttributeCopy(&mPersistentData, &mCurrentData, attribute);
            break;
        case rins_AttributeModulation:
            /* Modulation values will not be taken as preferred values. So call should never come here */
            break;
        default:
            ASSERT(FALSE);
            break;
    }
}

/* Writes persistent values to flash */

void CHsvDvbCInstallation_msettings_Priv::idvbset_CommitPreferred()
{
    /* Write to Flash */
    FILE* fp;
    int writenrec = 0;

    TraceDebug(m,"Fopen for write = %s", mFileName);

    fp = fopen(mFileName, "wb");
    if(fp)
    {
        writenrec = fwrite((Address)(&mPersistentData), sizeof(mPersistentData), 1, fp);
        if(writenrec)
        {
            TraceDebug(m,"Persistent Settings is loaded to Flash file");
        }
        else
        {
            TraceDebug(m,"Writing to flash failed ");
        }
		if(fflush(fp))
		{
			//PrintfNotice("fflush failed");
		}
		if(fsync(fileno(fp)))
		{
			//PrintfNotice("fsync failed");
		}
        fclose(fp);
    }
    else
    {
        TraceDebug(m,"Flash file not present");
    }
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_CopyTemporaryToPersistent()
{
    //TraceDebug(m,"%s",__FUNCTION__);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeScanMode);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeSymbolRate);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeNetworkId);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeNetworkFreq);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeModulation);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeDigitalOption);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeFreqStepSize);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeCity);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeScrOrFTA);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeNetworkOperator);
	mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeLCNSorting);
	mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeDualAnalogPass);
	mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeDTTScanOnAnalog);	
	mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeLCNOption);	
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_ClearPersistent()
{
	mGetFilePath();
    //PrintfErr("%s %d mFileName %s\n",__FUNCTION__, __LINE__, mFileName);
    unlink(mFileName);
    mLoadDefaults(&mPersistentData);
}
/****************************************************
  provides IHsvSystemSettingsNotify syssetN
 ****************************************************/

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnCountryChanged( int country )
{
    if( (country == sysset_GetInstallCountry()) && (apsysset_GetVirginBit () == FALSE) )
    {
        //TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        mLoadDefaults(&mDefaultData);
        idvbset_ResetAttributeToDefault(AUTO_MODE, rins_AttributeScanMode);
        idvbset_ResetAllToPersistent();
    }
    else
    {

		if(apsysset_GetVirginBit () == TRUE)
		{
			
			mLoadDefaults(&mCurrentData);
			
		}
        
        idvbset_ResetAttributeToDefault(AUTO_MODE, rins_AttributeScanMode);
        mLoadDefaults(&mDefaultData);
        mLoadDefaults(&mManualData);
		if(apsysset_GetVirginBit () == TRUE)
		{
			mLoadDefaults(&mPersistentData);
			
		}
        idvbset_ResetAllToDefault();
    }
}
void CHsvDvbCInstallation_msettings_Priv::syssetN_OnMediumChanged( int medium )
{
    UNUSED(medium);
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_SetUserSymbolRates( int installationmode, int *values, int len )
{
    int i = 0;

    if( values != NULL )
    {
        if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
        {
            mCurrentData.UserSymbolRateLen = len;
            for(; i < mCurrentData.UserSymbolRateLen; i++)
            {
                mCurrentData.UserSymbolRate[i] = values[i];
            }
        }
        else if(installationmode == MANUAL_MODE)
        {
            mManualData.UserSymbolRateLen = len;            
            for(; i < mManualData.UserSymbolRateLen; i++)
            {
                mManualData.UserSymbolRate[i] = values[i];              
            }           
        }
    }
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_GetUserSymbolRates( int installationmode, int *values, int *len )
{
    int i = 0;
    if( values != NULL )
    {
        if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
        {
            *len = mCurrentData.UserSymbolRateLen;
            for(; i < mCurrentData.UserSymbolRateLen; i++)
            {
                values[i] = mCurrentData.UserSymbolRate[i];
            }
        }
        else if(installationmode == MANUAL_MODE)
        {
            *len = mManualData.UserSymbolRateLen;
            for(; i < mManualData.UserSymbolRateLen; i++)
            {
                values[i] = mManualData.UserSymbolRate[i];
            }
        }
    }
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_GetPredefinedSymbolRates( int installationmode, int *values, int *len )
{
    //UNUSED(installationmode);
    int     country = SYS_COUNTRY;
    int i = 0;
    if( values != NULL )
    {
        if( (rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode) == rins_FullScan) &&
			((country == cids_CountryNorway) || (country == cids_CountrySweden) || (country == cids_CountryDenmark)) )
        {
            mGetPredefinedSymbolRatesNordic(country, values, len);
        }
        else
        {
            *len = mCurrentData.SymbolRateLen;
            for( i=0; i < mCurrentData.SymbolRateLen; i++ )
            {
                values[i] = mCurrentData.SymbolRate[i];
            }
        }
    }
}

void CHsvDvbCInstallation_msettings_Priv::idvbset_ClearUserSymbolRates(void)
{
    int i;
    mCurrentData.UserSymbolRateLen = MAX_USERSYMRATES;
    for(i = 0; i < mCurrentData.UserSymbolRateLen; i++)
    {
        mCurrentData.UserSymbolRate[i] = 0;
    }   
}


void CHsvDvbCInstallation_msettings_Priv::syssetN_OnCityChanged( int city )
{
    if( city == sysset_GetInstallCity() )
    {
        idvbset_ResetAllToPersistent();
    }
    else
    {
        mLoadDefaults(&mDefaultData);
        mLoadDefaults(&mManualData);
        idvbset_ResetAllToDefault();
    }
}

void CHsvDvbCInstallation_msettings_Priv::mGetFilePath(void)
{
/*
	ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast);
    str_strcat(mDirName, "/channellib/");
	
	if(!str_strlen(mDirName))
    {
        ASSERT(!"Boot parition mount has failed");
    }
    
	if(str_strlen(mDirName))
	{
		str_strcpy(mFileName, mDirName);
		str_strcat(mFileName, FILE_NAME);
	}
	else
	{
		ASSERT(!"Boot parition mount has failed");
		str_strcpy(mFileName, DEFAULT_FILE_PATH);
	}

    TraceDebug(m,"Fopen of %s", mFileName);
*/
	str_strcpy (mFileName, "/user_setting/rw/tvserver/databases/channellib/HsvDvbCSettings");

}




Nat8 CHsvDvbCInstallation_msettings_Priv::idvbset_GetONIDNetworkOperator ( int ONID ) 
{
	return 0;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnLanguageChanged (  int lang  ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnInstalledCountryChanged (  int country ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnHearingImpairedTypeChanged (  int lang  ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredAudioFormatChanged ( int format ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredPrimaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredSecondaryAudioLanguageChanged ( int value ) 
{
	return;
}
void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredPrimarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredSecondarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredPrimaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCInstallation_msettings_Priv::syssetN_OnPreferredSecondaryTxtLanguageChanged ( int value ) 
{
	return;
}

