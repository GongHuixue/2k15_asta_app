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
 *    %name: hsveuins_msigstr.c %
 *    %version: TVG_tv550r4dev1_4 %
 *    %date_modified: Mon Jan 19 10:46:50 2009 %
 *    %derived_by: nareshj %
 */

#include "_hsveuins_msigstr.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_msigstr")





TypeSignalStrengthStatus CHsvEuropeInstallation_msigstr_Priv::s__SigStrStatus;





Nat32 CHsvEuropeInstallation_msigstr_Priv::s__gQSigStrength = SIGSTRENGTHZERO;

Nat32 CHsvEuropeInstallation_msigstr_Priv::s__gASigStrength = SIGSTRENGTHZERO;


Nat32 CHsvEuropeInstallation_msigstr_Priv::s__gVSigStrength = SIGSTRENGTHZERO;


void CHsvEuropeInstallation_msigstr_Priv::UpdateSigStrMeasuredFlag(void)
{   /* If all modes of signal strengths are measured. Put the global flag to true */
    /* Naresh: Workaround solution for now */
    if( (SigStrStatus.VSigStrMeasured)  &&
            (SigStrStatus.ASigStrMeasured)  &&
            (SigStrStatus.QSigStrMeasured)  &&
            (SigStrStatus.SSigStrMeasured)
      )
    {
        SigStrStatus.SigStrMeasured =   TRUE;
    }
    else
    {
        SigStrStatus.SigStrMeasured =   FALSE;
    } 
}

Bool CHsvEuropeInstallation_msigstr_Priv::StartSigStrMeasWithMode(int mode, Nat32 *store, Bool *MeasuredFlag)
{
    Bool retval = FALSE;
    Nat32 errorcode = TM_OK;
    Bool ret = 0;
    Nat32 cookie = 0;
    FResult plfretval = 0;
    DP(("TunerEvent: tmIFeSigStrengthMeas_Start for Tuner\n"));


    plfretval = feapi_Start(WINDOWID, mode, &ret, &errorcode);
    if (plfretval)
    {
        sigstr_GetActualSignalStrength(mode, cookie);
    }
    ASSERT(TM_OK  ==  errorcode );

    *MeasuredFlag = sigstr_IsSignalStrengthMeasurementValid( mode );

    if ( *MeasuredFlag )
    {
        *store = GetSignalstrength( mode );
        UpdateSigStrMeasuredFlag();
    }

    retval  =   TRUE;

    return retval;
}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_Initialise(void)
{
    SigStrStatus.VSigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.ASigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.QSigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SSigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SigStrMeasured     =   FALSE;    
    SigStrStatus.VSigStrMeasured    =   FALSE;    
    SigStrStatus.ASigStrMeasured    =   FALSE;    
    SigStrStatus.QSigStrMeasured    =   FALSE;    
    SigStrStatus.SSigStrMeasured    =   FALSE;    
    SigStrStatus.VMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.VMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.AMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.AMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.QMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.QMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
}

Bool CHsvEuropeInstallation_msigstr_Priv::sigstr_StartSigStrMeasAll(void)
{
    Bool retval = TRUE;
    retval  =   retval  &&  StartSigStrMeasWithMode(rins_InsVssm, &SigStrStatus.VSigStrength, &SigStrStatus.VSigStrMeasured);
    retval  =   retval  &&  StartSigStrMeasWithMode(rins_InsAssm, &SigStrStatus.ASigStrength, &SigStrStatus.ASigStrMeasured);
    retval  =   retval  &&  StartSigStrMeasWithMode(rins_InsQssm, &SigStrStatus.QSigStrength, &SigStrStatus.QSigStrMeasured);
    retval  =   retval  &&  StartSigStrMeasWithMode(rins_InsSssm, &SigStrStatus.SSigStrength, &SigStrStatus.SSigStrMeasured);

    TraceDebug(m,"sigstr_StartSigStrMeas returning %d", retval);
    return retval;
}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_StopSigStrMeasAll(void)
{
    sigstr_StopSigStrMeas( rins_InsVssm );
    sigstr_StopSigStrMeas( rins_InsAssm );
    sigstr_StopSigStrMeas( rins_InsQssm );
    //sigstr_StopSigStrMeas( rins_InsSssm );
}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_UpdateSigStrRange(void)
{
    sigstr_GetSigStrengthRange(rins_InsVssm, &SigStrStatus.VMinSigStr, &SigStrStatus.VMaxSigStr);
    sigstr_GetSigStrengthRange(rins_InsAssm, &SigStrStatus.AMinSigStr, &SigStrStatus.AMaxSigStr);
    sigstr_GetSigStrengthRange(rins_InsQssm, &SigStrStatus.QMinSigStr, &SigStrStatus.QMaxSigStr);
    //sigstr_GetSigStrengthRange(rins_InsSssm, &SigStrStatus.SMinSigStr, &SigStrStatus.SMaxSigStr);
}

//    Weak Signal Installation Functions (Digital)
FResult CHsvEuropeInstallation_msigstr_Priv::sigstr_GetSigStrengthRange(int mode, Nat32* min, Nat32* max)
{
    Nat32 errorcode = TM_OK;

    feapi_GetSigStrengthRange(WINDOWID, mode, min, max, &errorcode);

    ASSERT(TM_OK == errorcode);
    return errorcode;
}

Nat32 CHsvEuropeInstallation_msigstr_Priv::sigstr_GetSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case rins_InsQssm:
            retval      =       SigStrStatus.QSigStrength;  
            break;
        case rins_InsAssm:
            retval      =       SigStrStatus.ASigStrength;  
            break;
            /* case rins_InsSssm:
               retval      =       SigStrStatus.SSigStrength;  
               break;
               */
        case rins_InsVssm:
        default:
            retval      =       SigStrStatus.VSigStrength;  
            break;
    }
    return retval;
}

Nat32 CHsvEuropeInstallation_msigstr_Priv::sigstr_GetMinSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case rins_InsQssm:
            retval      =       SigStrStatus.QMinSigStr;  
            break;
        case rins_InsAssm:
            retval      =       SigStrStatus.AMinSigStr;  
            break;
            /* case rins_InsSssm:
               retval      =       SigStrStatus.SMinSigStr;  
               break;        
               */
        case rins_InsVssm:
        default:
            retval      =       SigStrStatus.VMinSigStr;  
            break;
    }
    return retval;
}

Nat32 CHsvEuropeInstallation_msigstr_Priv::sigstr_GetMaxSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case rins_InsQssm:
            retval      =       SigStrStatus.QMaxSigStr;  
            break;
        case rins_InsAssm:
            retval      =       SigStrStatus.AMaxSigStr;  
            break;
            /* case rins_InsSssm:
               retval      =       SigStrStatus.SMaxSigStr;  
               break;
               */
        case rins_InsVssm:
        default:
            retval      =       SigStrStatus.VMaxSigStr;  
            break;
    }
    return retval;
}

Nat32 CHsvEuropeInstallation_msigstr_Priv::sigstr_GetActualSignalStrength(int mode, Nat32 cookie)
{
    Bool ret = FALSE;
    static Nat32 val = SIGSTRENGTHZERO;
    ret = sigstr_IsSignalStrengthMeasurementValid( mode );
    if( ret )
    {
        val = GetSignalstrength( mode ); /* FIXME : Is the sig str is requeired for th aux tuner ie cookie == aux ??*/
    }
    if(ret)
    {
        switch(mode)
        {
            case rins_InsQssm:
                SigStrStatus.QSigStrength      =   val;  
                SigStrStatus.QSigStrMeasured   =   TRUE;    
                break;
            case rins_InsAssm:
                SigStrStatus.ASigStrength      =   val;  
                SigStrStatus.ASigStrMeasured   =   TRUE;    
                break;
            case rins_InsSssm:
                SigStrStatus.SSigStrength      =   val;  
                SigStrStatus.SSigStrMeasured   =   TRUE;    
                break;
            case rins_InsVssm:
            default:
                SigStrStatus.VSigStrength      =   val;  
                SigStrStatus.VSigStrMeasured   =   TRUE;    
                break;
        }
        UpdateSigStrMeasuredFlag();
    }
    UNUSED(cookie);
    return val;
}

Bool CHsvEuropeInstallation_msigstr_Priv::sigstr_GetSigStrengthMeasured(void)
{
	Bool retval = FALSE;

	TraceNotice(m,"sigstr_GetSigStrengthMeasured returning %d", SigStrStatus.SigStrMeasured);

    retval = sigstr_IsSignalStrengthMeasurementValid(rins_InsQssm);
	TraceNotice(m,"Qssm value %d\n", retval);
	
	retval &= sigstr_IsSignalStrengthMeasurementValid(rins_InsAssm);
	TraceNotice(m,"Assm value %d\n", retval);

	retval &= sigstr_IsSignalStrengthMeasurementValid(rins_InsSssm);
	TraceNotice(m,"Sssm value %d\n", retval);

    return retval;

}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_SetSigStrengthMeasured(Bool val)
{
    TraceDebug(m,"sigstr_SetSigStrengthMeasured called with val = %d", val);
    SigStrStatus.SigStrMeasured = val;
}

/* Taken over from sigmeas interface */

Nat32 CHsvEuropeInstallation_msigstr_Priv::GetSignalstrength(int measmode)
{
    Bool ret = FALSE;
    Nat32 *retval;
    Nat32 errorcode = TM_OK;
    Nat32 val;

    ASSERT(TM_OK  ==  errorcode );

    switch(measmode)
    {
        case rins_InsQssm:
            retval      =       &gQSigStrength;
            break;
        case rins_InsAssm:
            retval      =       &gASigStrength;  
            break;
            /* case rins_InsSssm:
               retval      =       &gSSigStrength;  
               break;
               */
        case rins_InsVssm:
        default:
            retval      =       &gVSigStrength;  
            break;
    }
    feapi_GetMeasValid(WINDOWID, measmode, &ret, &errorcode);
    ASSERT(TM_OK  ==  errorcode );
    if(ret)
    {
        feapi_GetSigStrength(WINDOWID,measmode, retval, &errorcode);
        ASSERT(TM_OK  ==  errorcode );
    }
    val = *retval;
    DP( ("Signalstrength returned for measmode:%d,val:%d,errorcode:%d\n",measmode,val,errorcode) );
    return val;
}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_StartSigStrMeas(int measmode)
{    


    switch(measmode)
    {
        case rins_InsVssm:
            DP(("TunerEvent: tmIFeSigStrengthMeas_Start for VSSM\n"));
            StartSigStrMeasWithMode(rins_InsVssm, &SigStrStatus.VSigStrength, &SigStrStatus.VSigStrMeasured);
            break;
        case rins_InsAssm:
            DP(("TunerEvent: tmIFeSigStrengthMeas_Start for ASSM\n"));
            StartSigStrMeasWithMode(rins_InsAssm, &SigStrStatus.ASigStrength, &SigStrStatus.ASigStrMeasured);
            break;
        case rins_InsQssm:
            DP(("TunerEvent: tmIFeSigStrengthMeas_Start for QSSM\n"));
            StartSigStrMeasWithMode(rins_InsQssm, &SigStrStatus.QSigStrength, &SigStrStatus.QSigStrMeasured);
            break;
        case rins_InsSssm:
            DP(("TunerEvent: tmIFeSigStrengthMeas_Start for SSSM\n"));
            StartSigStrMeasWithMode(rins_InsSssm, &SigStrStatus.SSigStrength, &SigStrStatus.SSigStrMeasured);
            break;
    }


}

void CHsvEuropeInstallation_msigstr_Priv::sigstr_StopSigStrMeas(int measmode)
{
    Nat32 errorcode = TM_OK;
    Bool ret = FALSE;
    feapi_Stop(WINDOWID, measmode, &ret, &errorcode);
    ASSERT(TM_OK  ==  errorcode);
}

Bool CHsvEuropeInstallation_msigstr_Priv::sigstr_IsSignalStrengthMeasurementValid( int measmode )
{
    Bool ret = FALSE;
    Nat32 errorcode = TM_OK;
    feapi_GetMeasValid(WINDOWID, measmode, &ret, &errorcode);
    ASSERT(TM_OK == errorcode );        
    return ret;
}

