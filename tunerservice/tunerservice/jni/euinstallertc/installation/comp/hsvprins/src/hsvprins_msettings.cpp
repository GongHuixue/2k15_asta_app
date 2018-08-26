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
 *    %name: hsvprins_msettings.c %
 *    %version: TVG_tv550r4dev1 %
 *    %date_modified: Wed May 21 11:40:37 2008 %
 *    %derived_by: vijayan %
 */

#include "_hsvprins_msettings.h"

TRACESYMBOL(m, "analog/installation/hsvprins_msettings")

#include "hsvprins.h"






tmFe_TvSystem_t CHsvPresetInstallation_msettings_Priv::convertToPlfTvSystem(int instvsystem)
{
    tmFe_TvSystem_t tvsys = tmFe_TvSystemNone;    
    switch( instvsystem )
    {
        case HsvInsTvSystemBg :
            tvsys = tmFe_TvSystemBg;                       
            break;
        case HsvInsTvSystemDk :                
            tvsys = tmFe_TvSystemDk;                
            break;
        case HsvInsTvSystemI :
            tvsys = tmFe_TvSystemI;
            break;
        case HsvInsTvSystemL :
            tvsys = tmFe_TvSystemL;                
            break;
        case HsvInsTvSystemM :
            tvsys = tmFe_TvSystemM;                
            break;
        case HsvInsTvSystemAuto :                
            tvsys = tmFe_TvSystemNone;                
            break;
            /*case HsvInsTvSystemNone :
              break;*/
        default :
            ASSERT(FALSE);
            break;
    }
    return( tvsys );
}


void CHsvPresetInstallation_msettings_Priv::convertToPlfColorSystem(int insCol,int *plfCol,int *plfColFreq)
{
    *plfCol = col_UnknownColorSystem;
    *plfColFreq = col_FreqInvalid;
    switch(insCol)
    {
        case HsvInsColourSystemPal:
            *plfCol = col_Pal;
            *plfColFreq = col_FreqUnknown;
            break;
        case HsvInsColourSystemSecam:
            *plfCol = col_Secam;
            *plfColFreq = col_FreqUnknown;
            break;
        case HsvInsColourSystemNtsc358:
            *plfCol = col_Ntsc;
            *plfColFreq = col_Freq3pt579545;
            break;
        case HsvInsColourSystemAuto:
            *plfCol = col_UnknownColorSystem;
            *plfColFreq = col_FreqUnknown;
            break;
        case HsvInsColourSystemNtsc443:
            *plfCol = col_Ntsc;
            *plfColFreq = col_Freq4pt433619;
            break;
        case HsvInsColourSystemNtscUnknown:
            *plfCol = col_Ntsc; 
            *plfColFreq = col_FreqUnknown;
            break;
        case HsvInsColourSystemInvalid:
            *plfCol = col_InvalidColorSystem;
            *plfColFreq = col_FreqInvalid;
            break;
        default:
            ASSERT(FALSE);
            break;
    }
}

int CHsvPresetInstallation_msettings_Priv::convertToPrgColorSystem(int colSys,int colFreq)
{
    int color = col_InvalidColorSystem;

    if(colSys == col_Pal)
    {
        color = HsvInsColourSystemPal;
    }
    else if(colSys == col_Secam)
    {
        color = HsvInsColourSystemSecam;
    }
    else if(colSys == col_Ntsc)
    {
        //if(colFreq == col_Freq4pt433619)
        if(colFreq == col_FreqUnknown)
        {
            //color = HsvInsColourSystemNtsc443;
            color = HsvInsColourSystemNtscUnknown;
        }
        else
        {
            color = HsvInsColourSystemNtsc358;
        }
    }
    else if(colSys == col_UnknownColorSystem)
    {
        color = HsvInsColourSystemAuto;
    }
    else if(colSys == col_InvalidColorSystem)
    {
        color = HsvInsColourSystemInvalid;
    }
    else
    {
        color = col_InvalidColorSystem;
    }

    return color;
}

Bool CHsvPresetInstallation_msettings_Priv::anaset_IsTvSystemSupported(int instvsystem )
{
    tmFe_TvSystem_t tvsys;
    Nat32 errorcode = TM_OK;
    Bool retVal= FALSE ;
    tvsys = convertToPlfTvSystem( instvsystem );
    feapi_GetTvSystemSupp( WINDOWID, tvsys, & retVal, &errorcode );

    return retVal;
}

/******************************************************************/
void CHsvPresetInstallation_msettings_Priv::anaset_SetTvSystem( int instvSystem )
    /******************************************************************
     * Purpose: Sets TvSystem
     ******************************************************************/
{
    tmFe_TvSystem_t tvsys;
    Nat32 errorcode = TM_OK;
    Bool Supported = FALSE; 

    tvsys = convertToPlfTvSystem(instvSystem);

    feapi_GetTvSystemSupp( WINDOWID,tvsys, &Supported, &errorcode );
    ASSERT( errorcode == TM_OK );
    if( Supported )
    {
        feapi_SetTvSystem( WINDOWID, tvsys, &errorcode );
        ASSERT( errorcode == TM_OK );
    }
}

/******************************************************************/
int CHsvPresetInstallation_msettings_Priv::anaset_GetTvSystem()
    /******************************************************************
     * Purpose: Gets TvSystem
     ******************************************************************/
{
    int returnValue = HsvInsTvSystemAuto;
    tmFe_TvSystem_t tvSystem;
    Nat32 errorcode = TM_OK;

    errorcode = feapi_GetTvSystem( WINDOWID, &tvSystem, &errorcode );

    switch(tvSystem)
    {

        case tmFe_TvSystemBg:
        case tmFe_TvSystemH:
            returnValue = HsvInsTvSystemBg;
            break;
        case tmFe_TvSystemDk:
        case tmFe_TvSystemD:
        case tmFe_TvSystemK1:
            returnValue = HsvInsTvSystemDk;
            break;
        case tmFe_TvSystemI:
            returnValue = HsvInsTvSystemI;
            break;
        case tmFe_TvSystemL1:
        case tmFe_TvSystemL:
            returnValue = HsvInsTvSystemL;
            break;
        case tmFe_TvSystemM:
        case tmFe_TvSystemN:
            returnValue = HsvInsTvSystemM;
            break;

        default:
            returnValue = HsvInsTvSystemAuto;
            break;
    }
    return(returnValue);
}



void CHsvPresetInstallation_msettings_Priv::anaset_SetColorSystem (int colorsystem)
{
    int plfCol;
    int plfColFreq;
    convertToPlfColorSystem(colorsystem,&plfCol,&plfColFreq);
    if(plfColFreq == col_UnknownColorSystem)
    {
        col_ForceColorSystem(plfCol);
        if( xcol_iPresent() )
        {
            xcol_ForceColorSystem( plfCol );
        }
    }
    else
    {
        col_ForceColorSystemEx(plfCol,plfColFreq);
        if( xcol_iPresent() )
        {
            xcol_ForceColorSystemEx( plfCol, plfColFreq );
        }
    }
}

int CHsvPresetInstallation_msettings_Priv::anaset_GetColorSystem( void )
{
    return convertToPrgColorSystem(col_GetColorSystem(),col_GetCarrierFrequency());
}

Bool CHsvPresetInstallation_msettings_Priv::anaset_IsColorSystemSupported( int colorsystem )
{
    int plfCol;
    int plfColFreq;
    Bool retVal;

    convertToPlfColorSystem( colorsystem,&plfCol,&plfColFreq );
    if( plfColFreq == col_FreqUnknown )
    {
        retVal = col_ColorSystemSupported(plfCol);
    }
    else
    {
        retVal = col_ColorSystemSupportedEx(plfCol,plfColFreq);
    }
    return retVal;
}


