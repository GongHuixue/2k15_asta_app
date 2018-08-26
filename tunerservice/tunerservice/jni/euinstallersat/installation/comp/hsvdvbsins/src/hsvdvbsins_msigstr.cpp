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
 *    %name: hsvdvbsins_msigstr.c %
 *    %version: BLR005#TVG_2 %
 *    %date_modified: Mon Jan 19 10:46:50 2009 %
 *    %derived_by: aneeshc %
 */

#include "_hsvdvbsins_msigstr.h"





TypeSignalStrengthStatus CHsvDvbsInstallation_msigstr_Priv::s__SigStrStatus;











Nat32 CHsvDvbsInstallation_msigstr_Priv::s__gQSigStrength = SIGSTRENGTHZERO;

Nat32 CHsvDvbsInstallation_msigstr_Priv::s__gSSigStrength = SIGSTRENGTHZERO;


void CHsvDvbsInstallation_msigstr_Priv::UpdateSigStrMeasuredFlag(void)
{   /* If all modes of signal strengths are measured. Put the global flag to true */
	/* Naresh: Workaround solution for now */
    if((SigStrStatus.QSigStrMeasured)  && (SigStrStatus.SSigStrMeasured) )
    {
        SigStrStatus.SigStrMeasured =   TRUE;
    }
	else
    {
        SigStrStatus.SigStrMeasured =   FALSE;
    } 
}

Bool CHsvDvbsInstallation_msigstr_Priv::StartSigStrMeasWithMode(int mode, Nat32 *store, Bool *MeasuredFlag)
{
    Bool	retval = FALSE;
	Bool	ret = 0;
	Nat32	errorcode = TM_OK;
    Nat32	cookie = 0;
	FResult plfretval = 0;

    DP(("TunerEvent: tmIFeSigStrengthMeas_Start for Tuner\n"));
   
	plfretval = plfwrapper_Start(WINDOWID, mode, &ret, &errorcode);
    if (plfretval)
    {
        isigstr_GetActualSignalStrength(mode, cookie);
    }
    ASSERT(TM_OK  ==  errorcode );

    *MeasuredFlag = isigstr_IsSignalStrengthMeasurementValid( mode );

    if ( *MeasuredFlag )
    {
        *store = GetSignalstrength( mode );
        UpdateSigStrMeasuredFlag();
    }

    retval  =   TRUE;
    
    return retval;
}

/* Taken over from sigmeas interface */

Nat32 CHsvDvbsInstallation_msigstr_Priv::GetSignalstrength(int measmode)
{
    Bool	ret = FALSE;
    Nat32	*retval = NULL;
    Nat32	errorcode = TM_OK;
    Nat32	val;
    
    ASSERT(TM_OK  ==  errorcode );

    switch(measmode)
    {
    case isigstr_InsQsm:
        retval      =       &gQSigStrength;
        break;
    case isigstr_InsSsm:
        retval      =       &gSSigStrength;  
        break;
    default:
        break;
    }
	if (retval)
	{
		plfwrapper_GetMeasValid(WINDOWID, measmode, &ret, &errorcode);
		ASSERT(TM_OK  ==  errorcode );
		if(ret)
		{
			plfwrapper_GetSigStrength(WINDOWID,measmode, retval, &errorcode);
			ASSERT(TM_OK  ==  errorcode );
		}
		val = *retval;
	}
	else
	{
		val = 0;
	}

    DP( ("Signalstrength returned for measmode:%d,val:%d,errorcode:%d\n",measmode,val,errorcode) );
    return val;
}

/* Platform Wrapper code */
FResult CHsvDvbsInstallation_msigstr_Priv::plfwrapper_Start( int winid, int ssm, Bool* Avail, Nat32* retval )
{
    FResult		plferr = 0;
    switch(ssm)
    {
    case isigstr_InsQsm:
        plferr = qssm_Start(winid, Avail, retval);
        break;
    case isigstr_InsSsm://same as Vssm ?
        plferr = vssm_Start(winid, Avail, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}

FResult CHsvDvbsInstallation_msigstr_Priv::plfwrapper_GetSigStrengthRange( int winid, int ssm, Nat32* MinStrength, Nat32* MaxStrength, Nat32* retval )
{
    FResult		plferr = 0;
    switch(ssm)
    {
    case isigstr_InsQsm:
        plferr = qssm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    case isigstr_InsSsm://same as Vssm ?
        plferr = vssm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}

FResult CHsvDvbsInstallation_msigstr_Priv::plfwrapper_GetMeasValid( int winid, int ssm, Bool* Valid, Nat32* retval )
{
    FResult		plferr = 0;
    switch(ssm)
    {
    case isigstr_InsQsm:
        plferr = qssm_GetMeasValid(winid, Valid, retval);
        break;
    case isigstr_InsSsm://same as Vssm ?
        plferr = vssm_GetMeasValid(winid, Valid, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}

FResult CHsvDvbsInstallation_msigstr_Priv::plfwrapper_GetSigStrength( int winid, int ssm, Nat32* Strength, Nat32* retval )
{
    FResult		plferr = 0;
    switch(ssm)
    {
    case isigstr_InsQsm:
        plferr = qssm_GetSigStrength(winid, Strength, retval);
        break;
    case isigstr_InsSsm://same as Vssm ?
        plferr = vssm_GetSigStrength(winid, Strength, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}

FResult CHsvDvbsInstallation_msigstr_Priv::plfwrapper_Stop( int winid, int ssm, Bool* Stopped, Nat32* retval )
{
    FResult		plferr = 0;
    switch(ssm)
    {
    case isigstr_InsQsm:
        plferr = qssm_Stop(winid, Stopped, retval);
        break;
    case isigstr_InsSsm://same as Vssm ?
        plferr = vssm_Stop(winid, Stopped, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}


/***  EXPORTED INTERFACES ***/
void CHsvDvbsInstallation_msigstr_Priv::isigstr_Initialise(void)
{
    SigStrStatus.QSigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SSigStrength       =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SigStrMeasured     =   FALSE;    
    SigStrStatus.QSigStrMeasured    =   FALSE;    
    SigStrStatus.SSigStrMeasured    =   FALSE;    
    SigStrStatus.QMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.QMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SMinSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
    SigStrStatus.SMaxSigStr         =   SIGSTRENGTHZERO;    /*default signalstrength*/
}

FResult CHsvDvbsInstallation_msigstr_Priv::isigstr_GetSigStrengthRange(int mode, Nat32* min, Nat32* max)
{
    Nat32 errorcode = TM_OK;
    
    plfwrapper_GetSigStrengthRange(WINDOWID, mode, min, max, &errorcode);

    ASSERT(TM_OK == errorcode);
    return errorcode;
}

Nat32 CHsvDvbsInstallation_msigstr_Priv::isigstr_GetSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case isigstr_InsQsm:
            retval      =       SigStrStatus.QSigStrength;  
            break;

         case isigstr_InsSsm:
            retval      =       SigStrStatus.SSigStrength;  
            break;		
    }
    return retval;
}

Nat32 CHsvDvbsInstallation_msigstr_Priv::isigstr_GetMinSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case isigstr_InsQsm:
            retval      =       SigStrStatus.QMinSigStr;  
            break;
         case isigstr_InsSsm:
            retval      =       SigStrStatus.SMinSigStr;  
            break;
    }
    return retval;
}

Nat32 CHsvDvbsInstallation_msigstr_Priv::isigstr_GetMaxSignalStrength(int mode)                     
{
    Nat32 retval = 0;
    switch(mode)
    {
        case isigstr_InsQsm:
            retval      =       SigStrStatus.QMaxSigStr;  
            break;
         case isigstr_InsSsm:
            retval      =       SigStrStatus.SMaxSigStr;  
            break;
    }
    return retval;
}

Nat32 CHsvDvbsInstallation_msigstr_Priv::isigstr_GetActualSignalStrength(int mode, Nat32 cookie)
{
    Bool ret = FALSE;
    static Nat32 val = SIGSTRENGTHZERO;
    ret = isigstr_IsSignalStrengthMeasurementValid( mode );
    if( ret )
    {
        val = GetSignalstrength( mode ); /* FIXME : Is the sig str is requeired for th aux tuner ie cookie == aux ??*/
    }
    if(ret)
    {
        switch(mode)
        {
            case isigstr_InsQsm:
                SigStrStatus.QSigStrength      =   val;  
                SigStrStatus.QSigStrMeasured   =   TRUE;    
                break;

            case isigstr_InsSsm:
                SigStrStatus.SSigStrength      =   val;  
                SigStrStatus.SSigStrMeasured   =   TRUE;    
                break;
            default:   
                break;
        }
        UpdateSigStrMeasuredFlag();
    }
    UNUSED(cookie);
    return val;
}

Bool CHsvDvbsInstallation_msigstr_Priv::isigstr_StartSigStrMeasAll(void)
{
    Bool retval = TRUE;

    retval  =   retval  &&  StartSigStrMeasWithMode(isigstr_InsQsm, &SigStrStatus.QSigStrength, &SigStrStatus.QSigStrMeasured);
    retval  =   retval  &&  StartSigStrMeasWithMode(isigstr_InsSsm, &SigStrStatus.SSigStrength, &SigStrStatus.SSigStrMeasured);

	printf("sigstr_StartSigStrMeas returning %d\n", retval);
    return retval;
}

void CHsvDvbsInstallation_msigstr_Priv::isigstr_StopSigStrMeasAll(void)
{
    isigstr_StopSigStrMeas( isigstr_InsQsm );
    isigstr_StopSigStrMeas( isigstr_InsSsm );
}

void CHsvDvbsInstallation_msigstr_Priv::isigstr_UpdateSigStrRange(void)
{
    isigstr_GetSigStrengthRange(isigstr_InsQsm, &SigStrStatus.QMinSigStr, &SigStrStatus.QMaxSigStr);
    isigstr_GetSigStrengthRange(isigstr_InsSsm, &SigStrStatus.SMinSigStr, &SigStrStatus.SMaxSigStr);
}

Bool CHsvDvbsInstallation_msigstr_Priv::isigstr_GetSigStrengthMeasured(void)
{
	printf("isigstr_GetSigStrengthMeasured returning %d\n", SigStrStatus.SigStrMeasured);
	return SigStrStatus.SigStrMeasured;	
}

void CHsvDvbsInstallation_msigstr_Priv::isigstr_SetSigStrengthMeasured(Bool val)
{
	printf("sigstr_SetSigStrengthMeasured called with val = %d\n", val);
	SigStrStatus.SigStrMeasured = val;
}

void CHsvDvbsInstallation_msigstr_Priv::isigstr_StartSigStrMeas(int measmode)
{     
    switch(measmode)
	{
	case isigstr_InsQsm:
		DP(("TunerEvent: tmIFeSigStrengthMeas_Start for QSSM\n"));
		StartSigStrMeasWithMode(isigstr_InsQsm, &SigStrStatus.QSigStrength, &SigStrStatus.QSigStrMeasured);
		break;
	case isigstr_InsSsm:
		DP(("TunerEvent: tmIFeSigStrengthMeas_Start for SSSM\n"));
		StartSigStrMeasWithMode(isigstr_InsSsm, &SigStrStatus.SSigStrength, &SigStrStatus.SSigStrMeasured);
		break;
	}
}

void CHsvDvbsInstallation_msigstr_Priv::isigstr_StopSigStrMeas(int measmode)
{
    Nat32	errorcode = TM_OK;
    Bool	ret = FALSE;
    plfwrapper_Stop(WINDOWID, measmode, &ret, &errorcode);
    ASSERT(TM_OK  ==  errorcode);
}

Bool CHsvDvbsInstallation_msigstr_Priv::isigstr_IsSignalStrengthMeasurementValid( int measmode )
{
    Bool	ret = FALSE;
    Nat32	errorcode = TM_OK;
    plfwrapper_GetMeasValid(WINDOWID, measmode, &ret, &errorcode);
    ASSERT(TM_OK == errorcode );        
    return ret;
}
