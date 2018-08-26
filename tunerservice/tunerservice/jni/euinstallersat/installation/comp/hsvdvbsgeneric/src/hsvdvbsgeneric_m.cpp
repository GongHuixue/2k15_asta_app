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
 *	C Source:		hsvdvbsgeneric_m.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 mrohit %
 *	%date_created:	 Fri Feb 22 23:10:35 2013 %
 *
**********************************************************************/

#include "_hsvdvbsgeneric_m.h"

/****************************************************************************
 * Macros and types
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsgeneric_m")






/****************************************************************************
 * Static variables
 ****************************************************************************/
TypeInstallationStatus CHsvDvbsGeneric_m_Priv::s__InsStatus;



/****************************************************************************
 * External functions
 ****************************************************************************/

int CHsvDvbsGeneric_m_Priv::ins_GetCurrentInstallationState (int *mode, int *state)
{
	int	RetVal = err_BadParameter;

	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetCurrentInstallationState (mode, state);
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetCurrentInstallationState (mode, state);
			break;
	}
	return RetVal;
}

FResult CHsvDvbsGeneric_m_Priv::ins_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult		RetVal = err_BadParameter;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:	
			RetVal = isvcscan_StartInstallation (Source, Lnb, Mode);
			SET_MODE (Mode);
			break;
		case	MANUAL_MODE:
			RetVal = isrt_StartInstallation (Source, Lnb, Mode);
			SET_MODE (Mode);
			break;
	}

	return RetVal;
}

FResult CHsvDvbsGeneric_m_Priv::ins_StopInstallation(void)
{
	int	RetVal = err_BadParameter;

	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_StopInstallation();
			break;
		case	MANUAL_MODE:
			RetVal = isrt_StopInstallation();
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberOfTvChannelsFound      (int Mode, int Lnb)
{
	int	RetVal = 0;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberOfTvChannelsFound (Mode, Lnb);
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetNumberOfTvChannelsFound (Mode, Lnb);
			break;
	}
	return RetVal;

}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberofRadioChannelsFound   (int Mode, int Lnb)
{
	int	RetVal = 0;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberofRadioChannelsFound (Mode, Lnb);
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetNumberofRadioChannelsFound (Mode, Lnb);
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberOfTvChannelsRemoved    (int Mode, int Lnb)
{
	int	RetVal = 0;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberOfTvChannelsRemoved (Mode,Lnb);
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberofRadioChannelsRemoved (int Mode, int Lnb)
{
	int	RetVal = 0;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberofRadioChannelsRemoved (Mode,Lnb);
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberOfDigitalChannelsAdded(void)
{
	int	RetVal = 0;

	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberOfDigitalChannelsAdded();
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetNumberOfDigitalChannelsAdded();
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberOfDigitalChannelsRemoved(void)
{
	int	RetVal = 0;

	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberOfDigitalChannelsRemoved();
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetNumberOfDigitalChannelsRemoved();
			break;
	}

	return RetVal;
}

int CHsvDvbsGeneric_m_Priv::ins_GetNumberOfDigitalChannelsMoved (void)
{
	int	RetVal = 0;

	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetNumberOfDigitalChannelsMoved ();
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetNumberOfDigitalChannelsMoved ();
			break;
	}

	return RetVal;
}

FResult CHsvDvbsGeneric_m_Priv::ins_StoreManualInstallationValues (void)
{
	return isrt_StoreManualInstallationValues();
}

FResult CHsvDvbsGeneric_m_Priv::ins_LoadManualInstallationDefaultValues (void)
{
	return isrt_LoadManualInstallationDefaultValues ();
}
Bool CHsvDvbsGeneric_m_Priv::ins_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return isrt_SetManualInstallationAttributes (AttributeId, Value);
}

int CHsvDvbsGeneric_m_Priv::ins_GetAttribute(int Mode, int AttributeId)
{
	int	RetVal = err_BadParameter;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetAttribute(Mode,AttributeId);
			break;
		case	MANUAL_MODE:
			RetVal = isrt_GetAttribute(Mode,AttributeId);
			break;
	}

	return RetVal;
}

FResult CHsvDvbsGeneric_m_Priv::ins_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	TraceNotice(m,"Error!!! SetPostcode- call should not land here");
	return 0;
}

FResult CHsvDvbsGeneric_m_Priv::ins_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_m_Priv::ins_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_m_Priv::ins_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
int CHsvDvbsGeneric_m_Priv::ins_GetScanProgressStatus (int Mode)
{
	int	RetVal = 0;

	switch (Mode)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			RetVal = isvcscan_GetScanProgressStatus (Mode);
			break;
	}

	return RetVal;
}

FResult CHsvDvbsGeneric_m_Priv::ins_WriteBarkerMuxData(void)
{
	return isvcscan_WriteBarkerMuxData();
}
void CHsvDvbsGeneric_m_Priv::ctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			isvcscanctrlN_OnEvent(Dmx,EventId,Value);
			break;
		case	MANUAL_MODE:
			isrtctrlN_OnEvent(Dmx,EventId,Value);
			break;
	}
}

void CHsvDvbsGeneric_m_Priv::plfApidvbsN_OnLockChanged(Bool LockState)
{
	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			isvcscanplfApidvbsN_OnLockChanged(LockState);
			break;
		case	MANUAL_MODE:
			isrtplfApidvbsN_OnLockChanged(LockState);
			break;
	}
}

void CHsvDvbsGeneric_m_Priv::plfApidvbsN_OnBlindScanEnd(void)
{
	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			isvcscanplfApidvbsN_OnBlindScanEnd();
			break;
	}
}

void CHsvDvbsGeneric_m_Priv::iacqN_OnDataAquired  (Bool Status)
{
	switch (CURRENT_MODE)
	{
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	AUTOUPDATE_MODE:
		case	ADDSAT_MODE:
			iscanAcqN_OnDataAquired(Status);
			break;
		case	MANUAL_MODE:
			isrtAcqN_OnDataAquired(Status);
			break;
		case	BACKGROUND_MODE:
			ibckAcqN_OnDataAquired(Status);
			break;
	}
}

void CHsvDvbsGeneric_m_Priv::bckInstall_EnableBackgroundInstallation (void)
{
	SET_MODE (BACKGROUND_MODE);
	ibckInstall_EnableBackgroundInstallation();
}

void CHsvDvbsGeneric_m_Priv::bckInstall_DisableBackgroundInstallation (void)
{
    ibckInstall_DisableBackgroundInstallation ();
}

void CHsvDvbsGeneric_m_Priv::pow_Init ()
{
	isvcscanpow_Init ();
	isrtpow_Init ();
	iacqpow_Init ();
	isortpow_Init ();
	ibckgndpow_Init ();
}

void CHsvDvbsGeneric_m_Priv::pow_TurnOn ()
{
	isvcscanpow_TurnOn ();
	isrtpow_TurnOn ();
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
	ibckgndpow_TurnOn ();
}

void CHsvDvbsGeneric_m_Priv::pow_TurnOff ()
{
	isvcscanpow_TurnOff ();
	isrtpow_TurnOff ();
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
	ibckgndpow_TurnOff ();
}

void CHsvDvbsGeneric_m_Priv::ins_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsGeneric_m_Priv::strapiN_OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{
   // TraceNotice(m,"%s() : %d", __FUNCTION__, __LINE__);
    switch (CURRENT_MODE)
	{		
		case MANUAL_MODE:
			isrtstrapiN->OnAdded (dest, spid, key1, key2, key3);
			break;
        case BACKGROUND_MODE:
            ibckgndstrapiN->OnAdded (dest, spid, key1, key2, key3);
            break;
        default:
            break;
	}    
}

void CHsvDvbsGeneric_m_Priv::strapiN_OnChanged (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
  //  TraceNotice(m,"%s() : %d", __FUNCTION__, __LINE__);
    switch (CURRENT_MODE)
	{		
		case MANUAL_MODE:
			isrtstrapiN->OnChanged (dest, spid, key1, key2, key3, eventid);
			break;
        case BACKGROUND_MODE:
            ibckgndstrapiN->OnChanged (dest, spid, key1, key2, key3, eventid);
            break;
        default:
            break;
	}
}

void CHsvDvbsGeneric_m_Priv::strapiN_OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{    
   // TraceNotice(m,"%s() : %d", __FUNCTION__, __LINE__);
    switch (CURRENT_MODE)
	{		
		case MANUAL_MODE:
			isrtstrapiN->OnRemoved (dest, spid, key1, key2, key3);
			break;
        case BACKGROUND_MODE:
            ibckgndstrapiN->OnRemoved (dest, spid, key1, key2, key3);
            break;
        default:
            break;
	}
}

void CHsvDvbsGeneric_m_Priv::strapiN_OnCompleted (HsvDestination dest, int spid)
{  
//    TraceNotice(m,"%s() : %d", __FUNCTION__, __LINE__);
    switch (CURRENT_MODE)
	{		
		case MANUAL_MODE:
			isrtstrapiN->OnCompleted (dest, spid);
			break;
        case BACKGROUND_MODE:
            ibckgndstrapiN->OnCompleted (dest, spid);
            break;
        default:
            break;
	}
}

