/**********************************************************************
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *	C Source:		hsvdvbsgeneric_mBckgnd.c
 *	Instance:		
 *	Description:	
 *	%created_by:	  aneeshc %
 *	%date_created:	  Fri Apr 19 16:07:21 2013 %
 *
**********************************************************************/

#include "_hsvdvbsgeneric_mBckgnd.h"

TRACESYMBOL(m, "installation/hsvdvbsgeneric/hsvdvbsgeneric_mBckgnd")

/* Macros */

Pump CHsvDvbsGeneric_mBckgnd_Priv::s__mPump;

Bool CHsvDvbsGeneric_mBckgnd_Priv::s__mActive,CHsvDvbsGeneric_mBckgnd_Priv::s__mAcquistionInProgress;


/* static functions */





Bool CHsvDvbsGeneric_mBckgnd_Priv::IsBackgroundInstall (void)
{
	Bool	RetVal = FALSE;
	int		mode,state;

	insstate_GetCurrentInstallationState (&mode, &state);
	RetVal =  (mode == BACKGROUND_MODE) ? TRUE : FALSE;

	return RetVal;
}

void CHsvDvbsGeneric_mBckgnd_Priv::PumpHandler(int event, Nat32 param)
{
    Nat32 OwnedResource = plfres_GetOwnedResources();
    UNUSED(param);

    TraceNotice (m,"%s %d OwnedResource %ld mAcquistionInProgress %d\n",__FUNCTION__,  __LINE__, OwnedResource, mAcquistionInProgress);
    //if( (OwnedResource & plfres_Frontend) && (OwnedResource & plfres_Source) )
    {
        TraceNotice(m,"%s %d mAcquistionInProgress %d\n",__FUNCTION__,  __LINE__, mAcquistionInProgress);
        if( (event == EvDataAvaiable) && (mAcquistionInProgress == FALSE) )
        {
            TraceNotice(m,"@ %d event %s - %s\n", __LINE__, "EvDataAvaiable", "Handled");
            FuncDataAvailable();    
        }
    }
}

inline void CHsvDvbsGeneric_mBckgnd_Priv::FuncDataAvailable(void)
{
    /* Naresh: none of the PTC attributes is going to change to update */
    mAcquistionInProgress = TRUE;
	TraceDebug (m, "BackgroundInstall collection triggered");
	
	idataacq_AcquireData(idataacq_Background);

    //mAcquistionInProgress = FALSE;
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckInstall_EnableBackgroundInstallation (void)
{
    mActive = s2div_IsBackgroundInstallRequired();
    mAcquistionInProgress = FALSE;
	TraceDebug (m, "mActive %d ",mActive);
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckInstall_DisableBackgroundInstallation (void)
{
    mActive = FALSE;
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckgndpow_Init(void)
{
    mPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, TRUE,"hsvdvbsgeneric_mBackground");
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckgndpow_TurnOn(void)
{
    mActive = FALSE;
    mAcquistionInProgress = FALSE;
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckgndpow_TurnOff(void)
{

}

void CHsvDvbsGeneric_mBckgnd_Priv::strapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);

    if(mActive && BACKGROUND_INSTALL)
    {   
		/* Do it only when installation is not happening */
        if( spid == HSVSPID(ActualTSService, dvb, sdt) )
        {
			//TraceDebug (m, "strapiN_OnAdded ");
            pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)NULL, 1500);
        }
    }

}

void CHsvDvbsGeneric_mBckgnd_Priv::strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(eventid);

	//TraceDebug (m, "strapiN_OnChanged ");
    strapiN_OnAdded( dest, spid, key1, key2, key3);

}

void CHsvDvbsGeneric_mBckgnd_Priv::bckctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(dmx);
    UNUSED(value);

    TraceNotice(m,"%s %d eventid %d mActive %d BACKGROUND_INSTALL %d", __FUNCTION__, __LINE__, eventid, mActive, BACKGROUND_INSTALL);
    if(mActive && BACKGROUND_INSTALL)
    {
        if(eventid == bckctrlN_DataAvailable)
        {   
            pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)NULL, 1000);

        }
    }
}

void CHsvDvbsGeneric_mBckgnd_Priv::ibckAcqN_OnDataAquired  (Bool Status)
{
	TraceDebug (m, "DataAcquired ");
	mAcquistionInProgress = FALSE;
}


void CHsvDvbsGeneric_mBckgnd_Priv::strapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsGeneric_mBckgnd_Priv::strapiN_OnCompleted( HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}
