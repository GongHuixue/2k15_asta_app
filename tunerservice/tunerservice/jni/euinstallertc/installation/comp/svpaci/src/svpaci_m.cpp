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
 *          %name: svpaci_m.c %
 *       %version: TVG_Fusion_2 %
 * %date_modified: Wed Oct 11 17:30:17 2006 %
 *    %derived_by: lakshminb %
 */
 
#include "_svpaci_m.h"

TRACESYMBOL(m, "analog/installation/svpaci_m")

/****************************************************
 * Local macro definitions
 ****************************************************/


#ifndef __cplusplus

#else

#endif







/******************************************
 * Static variables
 ******************************************/
Bool CSvcPaci_m_Priv::s__powerInitialised = FALSE;

Bool CSvcPaci_m_Priv::s__initialised = FALSE;

aciState CSvcPaci_m_Priv::s__currentAciState;

aciTimeOut CSvcPaci_m_Priv::s__currentAciTimeOut;

Pump CSvcPaci_m_Priv::s__aciPump,CSvcPaci_m_Priv::s__TimerPump;

PageNr CSvcPaci_m_Priv::s__restoreMtpPage;

Nat32 CSvcPaci_m_Priv::s__restoreMtpFrequency;

Nat32 CSvcPaci_m_Priv::s__startFrequency;

PageNr CSvcPaci_m_Priv::s__currentAciPage;

int CSvcPaci_m_Priv::s__currentDecodedTotalPresets;

Bool CSvcPaci_m_Priv::s__frequencyDetuned = FALSE;

HsvAciBroadcaster CSvcPaci_m_Priv::s__currentAciBroadcaster;

HsvAciNetwork CSvcPaci_m_Priv::s__currentAciNetwork;

HsvAciMode CSvcPaci_m_Priv::s__currentAciMode;

HsvAciLanguage CSvcPaci_m_Priv::s__currentAciLanguage;

HsvAciPriority CSvcPaci_m_Priv::s__currentAciPriority;

HsvAciPriority CSvcPaci_m_Priv::s__currentMaxAciPriority;

PageNr CSvcPaci_m_Priv::s__currentMaxPriorityPage;

Nat32 CSvcPaci_m_Priv::s__currentMaxPriorityFrequency;

HsvAciMultiInfo CSvcPaci_m_Priv::s__currentMtpInfo;

#ifndef __cplusplus

HsvAciSingleInfo CSvcPaci_m_Priv::s__decodedPresets[adiv_MaxPresets];

#else

HsvAciSingleInfo CSvcPaci_m_Priv::s__decodedPresets[ICesPaciDiv_MaxPresets];

#endif

Nat8 CSvcPaci_m_Priv::s__currentMtpIndex;

Nat8 CSvcPaci_m_Priv::s__currentMtpCount;

STimer CSvcPaci_m_Priv::s__pageTimerHandle;

STimer CSvcPaci_m_Priv::s__displayTimerHandle;

int CSvcPaci_m_Priv::s__selectedIndex = 0;

Bool CSvcPaci_m_Priv::s__completedStatus = FALSE;

Bool CSvcPaci_m_Priv::s__writeIndataInProgress = FALSE;

Bool CSvcPaci_m_Priv::s__waitForStationFoundTxtReset = FALSE;

Bool CSvcPaci_m_Priv::s__receivedTxtReset = FALSE;

Bool CSvcPaci_m_Priv::s__receivedOnStationFound = FALSE;

Bool CSvcPaci_m_Priv::s__receivedOnStationNotFound = FALSE;

Nat8 CSvcPaci_m_Priv::s__currentPresetToStore;

int CSvcPaci_m_Priv::s__tryHeader = 0;

Bool	CSvcPaci_m_Priv::s__TimerHandlingNeeded = FALSE;

/******************************************
 * Static Functions
 ******************************************/




































/* ****************************************************
   Events and event handlers
 * ****************************************************/





EVENT_HANDLER CSvcPaci_m_Priv::s__ce_eventHandlerTable[13] = 
{ FNADDR(EventHandlerStationFoundTxtReset)              /* eStationFoundTxtReset   */
    , FNADDR(EventHandlerStationNotFound)                   /* eStationNotFound        */
        , FNADDR(EventHandlerHeaderDecoded)                     /* eHeaderDecoded          */
        , FNADDR(EventHandlerOnPageDecodeSuccessful)            /* ePageDecodeSuccessful   */
        , FNADDR(WriteIndataAndSendCompletedNotification)       /* ePageDecodeFailure      */
        , FNADDR(EventHandlerPageTimerExpired)                  /* eAciPageTimerExpired    */
        , FNADDR(EventHandlerSelectIndex)                       /* eSelectIndex            */
        , FNADDR(EventHandlerDisplayTimerExpired)               /* eDisplayTimerExpired    */
        , FNADDR(EventHandlerTeletextReset)                     /* eTeletextReset          */
        , FNADDR(EventHandlerTunerTimeout)                      /* eTunerTimeout           */
        , FNADDR(EventHandlerStartAciTimeout)                   /* eStartAciTimeout        */
        , FNADDR(EventHandlerServiceLabelTimeout)               /* eServiceLabelTimeout    */
        , FNADDR(EventHandlerStorePresets)                      /* eStorePresets           */
};


/* --------------------------------------------------------------------------- */
/*TODO: Remove this after chnages for timer is done in marmoset*/
#ifdef __cplusplus

void OnDisplayTimerExpired2()
{
}

void OnAciPageTimerExpired2()
{
}
#endif


/****************************************************
 * Purpose : Intialises ACI component
 ****************************************************/

void CSvcPaci_m_Priv::pow_Init()
{
	TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if( txtpre_iPresent() )
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
		aciPump = pmp_PmpCreateEx(pen_PumpEngine,AciHandler, FALSE, "aciPump");
		TimerPump = pmp_PmpCreateEx( pen_PumpEngine, OnPumpTimerExpired, TRUE, "AciTimerPump" );
		#ifndef __cplusplus
		displayTimerHandle = tmr_Create(OnDisplayTimerExpired);
        pageTimerHandle = tmr_Create(OnAciPageTimerExpired);
		#else
		displayTimerHandle = tmr_Create(OnDisplayTimerExpired2);
        pageTimerHandle = tmr_Create(OnAciPageTimerExpired2);
		#endif
		powerInitialised = TRUE;
	}
}

void CSvcPaci_m_Priv::pow_TurnOn()
{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(powerInitialised)
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		currentMaxAciPriority = pgAciPriorityInvalid;
		currentMaxPriorityPage = INVALID_PAGENR;
		currentMaxPriorityFrequency = INVALID_FREQUENCY;

		ResetVariables();
		initialised = TRUE;
	}
	else
	{
		/*ASSERT(!"Aci Power not initialised");*/
		 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
	}
}

void CSvcPaci_m_Priv::pow_TurnOff()
{
    initialised = FALSE;
}

/****************************************************
 * This function checks whether aci is supported
 * i.e. it checks whether teletext interfaces are 
 * conncted
 ****************************************************/
Bool CSvcPaci_m_Priv::pgaci_IsAciSupported( void )
{
    return (powerInitialised);
}

/****************************************************
 * This function checks for the presence of ACI pages 
 * in teletext transmission and starts acquisition and 
 * decoding of the ACI pages.
 ****************************************************/
void CSvcPaci_m_Priv::pgaci_StartAciInstallation( void )
{


	if(initialised)
	{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		if(currentAciState == stIdle)
		{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

			// pmp_PmpSendAfter( TimerPump, 0, aciTimeoutStartAci, adiv_AciTxtHdrReqDelay );
			if( adiv_AciTxtHdrReqDelay > 0)
			{
				pmp_PmpSendAfter( TimerPump, 0, aciTimeoutStartAci, adiv_AciTxtHdrReqDelay );
						 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

			}
			else
			{
				if( adiv_AciTxtHdrReqDelay < 0 )
				{
						 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

					ASSERT(!"adiv_AciTxtHdrReqDelay cannot have negative value");
				}
						 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

				pmp_PmpSend( TimerPump, 0, aciTimeoutStartAci );
			}
		}
		else
		{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

			ASSERT(!"Invalid aci state");
		}
	}
	else
	{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		ASSERT(!"Aci Power not initialised");
	}
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

}

/****************************************************
 * This function causes the ACI decoding to stop in 
 * case the user wants to cancel the ACI decoding action. 
 ****************************************************/
void CSvcPaci_m_Priv::pgaci_StopAciInstallation( void )
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

    if(initialised)
    {
        switch(currentAciState)
        {
            /* If waiting for user input, remove ACI page from screen and send a notification */
            case stWaitForUser:
                tmr_Cancel(displayTimerHandle);
                acidec_RemoveACIPage(currentAciPage);
                acidec_DecodeStop();
                ResetVariables();
                if(acidsN_iPresent())
                {
                    acidsN_OnMultiPackageRemoved();
                }
                break;
                /* If Idle state, no action is taken */
            case stIdle:
                break;
                /* stop page acquisition and tune back to original frequency */
            default:
                /*if(writeIndataInProgress == FALSE)*/
                {
                    currentAciState = stIdle;
                    acidec_DecodeStop();
                    tmr_Cancel(pageTimerHandle);
					TimerHandlingNeeded = FALSE;
                    if( frequencyDetuned )
                    {
                        TuneFrequency(startFrequency);
                        frequencyDetuned = FALSE;
						TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
                    }
                    ResetVariables();
                }
                /*else
                  {
                  ASSERT(!"ACI Write in data in progress");
                  }*/
                break;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}


/****************************************************
 * This function decodes and stores the ACI table 
 * found during frequency band search.
 ****************************************************/
void CSvcPaci_m_Priv::pgaci_StoreAciTable( void )
{
    if(initialised)
    {
        if(currentMaxAciPriority != pgAciPriorityInvalid)
        {
            ResetVariables();
            currentAciState = stMaxPriorityPage;

            /*
               if(tun_iPresent())
               {
               startFrequency = tun_GetFrequency();
               }
               */
            if(prins_iPresent())
            {
                startFrequency = prins_GetTunerFrequency(); 
            }

            currentAciState = stMaxPriorityPage;
            currentAciPage = currentMaxPriorityPage;
			TraceDebug(m,"Hsvprins: Svpaci: %s %d currentMaxPriorityFrequency=%d startFrequency=%d",__FUNCTION__,__LINE__,currentMaxPriorityFrequency,startFrequency);
            TuneFrequency(currentMaxPriorityFrequency);
        }
        else
        {
            ASSERT(!"Incorrect call to storeacitable");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * This function gives the priority of the highest 
 * priority ACI page found during frequency band search.
 ****************************************************/
HsvAciPriority CSvcPaci_m_Priv::pgaci_GetPagePriority ( void )
{
    HsvAciPriority returnVal = pgAciPriorityInvalid;

    if(initialised)
    {
        returnVal = currentMaxAciPriority;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return (returnVal);
}

/****************************************************
 * This function gives the total number of presets 
 * decoded.
 ****************************************************/
int CSvcPaci_m_Priv::pgaci_GetNoOfPresets( void )
{
    int returnVal = 0;

    if(initialised)
    {
        returnVal = currentDecodedTotalPresets;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    TraceDebug(m,"[%s]:returnVal= %d:currentDecodedTotalPresets =[%d]",__FUNCTION__,returnVal,currentDecodedTotalPresets);
    return (returnVal);
}

/****************************************************
 * This function gives the number of mtp items
 ****************************************************/
int CSvcPaci_m_Priv::acids_GetNoOfMtpItems( void  )
{
    int retVal = 0;
    if(initialised)
    {
        retVal = acidec_GetNoOfMultipackageItems();
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return retVal;
}

/****************************************************
 * This function continues the ACI page display
 ****************************************************/
void CSvcPaci_m_Priv::acids_StartPageDisplay( void )
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(currentAciState == stWaitForContinueDisplay)
	{
		TraceDebug(m,"[%s]" , __FUNCTION__);
		currentAciState = stWaitForUser;
		acidec_DisplayACIPage( currentAciPage );
		acidec_SetCursor(0);
		if(acidsN_iPresent())
		{
			acidsN_OnMultiPackageDisplayed();
		}
	}
	else
	{
		ASSERT(!"wrong state");
	}
}


/****************************************************
 * This function selects a menu option.
 ****************************************************/
void CSvcPaci_m_Priv::acids_SelectIndex( int index )
{
    if(initialised)
    {
        selectedIndex = index;
        pmp_PmpSend( aciPump, eSelectIndex, 0 );
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * This function sets the cursor at the given position.
 ****************************************************/
void CSvcPaci_m_Priv::acids_SetCursor( Nat8 item )
{
    if(initialised)
    {
        if(currentAciState == stWaitForUser)
        {
            tmr_Cancel(displayTimerHandle);
            tmr_FireOnce(displayTimerHandle,adiv_MultipageDisplayTimeoutTime);

            acidec_SetCursor(item);
        }
        else
        {
            ASSERT(!" Invalid aci state");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * This function removes the cursor.
 ****************************************************/
void CSvcPaci_m_Priv::acids_RemoveCursor( void )
{
    if(initialised)
    {
        if(currentAciState == stWaitForUser)
        {
            acidec_RemoveCursor();
        }
        else
        {
            ASSERT(!"Invalid aci state");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * Notification function by aci decode to indicate
 * page decode failure
 ****************************************************/
void CSvcPaci_m_Priv::acidecN_OnDecodeFailure()
{
    if(initialised)
    {
        pmp_PmpSend( aciPump, ePageDecodeFailure, 0 );
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * Notification function by aci decode to indicate
 * that header of the requested page is decoded
 ****************************************************/
void CSvcPaci_m_Priv::acidecN_OnHeaderDecoded()
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(initialised)
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
		tmr_Cancel(pageTimerHandle);
		TimerHandlingNeeded = FALSE;
		pmp_PmpSend( aciPump, eHeaderDecoded, 0 );
	}
	else
	{
		ASSERT(!"Aci Power not initialised");
	}
}

/****************************************************
 * Notification function by aci decode to indicate
 * that requested page is decoded successfully
 ****************************************************/
void CSvcPaci_m_Priv::acidecN_OnDecodeSuccessful()
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(initialised)
	{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
		pmp_PmpSend( aciPump, ePageDecodeSuccessful, 0 );
	}
	else
	{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
		ASSERT(!"Aci Power not initialised");
	}
}

/****************************************************
 * Notification function by tvplf to indicate that
 * station was found at the tuned frequency
 ****************************************************/
/*void tunN_OnStationFound( void )*/
void CSvcPaci_m_Priv::OnStationFound( void )
{
	int frequency = 0;
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(initialised)
	{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		/*
		   if(tun_iPresent())
		   {
		   frequency = tun_GetFrequency();
		   }
		   */
		if(prins_iPresent())
		{
			frequency = prins_GetTunerFrequency(); 
		}
		if(waitForStationFoundTxtReset ) /* the == TRUE was removed */
		{
					 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

			/* If teletext reset notification is received send a message that 
			   both Stationfound and teletext reset event have been received  */
			receivedOnStationFound = TRUE;
			if(1)//receivedTxtReset)
			{
				waitForStationFoundTxtReset = FALSE;
				pmp_PmpSend( aciPump, eStationFoundTxtReset, frequency );
			}
		}
	}
}

/****************************************************
 * Notification function by tvplf to indicate that
 * station was not found at the tuned frequency
 ****************************************************/
/*void tunN_OnStationNotFound( void )*/
void CSvcPaci_m_Priv::OnStationNotFound( void )
{
	TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(initialised)
	{
		if(waitForStationFoundTxtReset ) /* the == TRUE was removed */ 
		{
			TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
			receivedOnStationNotFound = TRUE;
			waitForStationFoundTxtReset = FALSE;
			pmp_PmpSend( aciPump, eStationNotFound, 0 );
		}
	}
}

/****************************************************
 * Notification function from program installation 
 * to indicate frequency band search start
 ****************************************************/
/*void pginsN_OnAutomaticInstallationStarted(void)
  {
  if(initialised)
  {
  if(currentAciState == stIdle)
  {
  currentMaxAciPriority = pgAciPriorityInvalid;
  currentMaxPriorityPage = INVALID_PAGENR;
  currentMaxPriorityFrequency = INVALID_FREQUENCY;
  }
  else
  {
  ASSERT(!"Invalid ACI state");
  }

  }
  else
  {*/
/*ASSERT(!"Aci Power not initialised");*/
/*}
  }*/
void CSvcPaci_m_Priv::pginsN_OnEvent(int eventid, int value)
{
	TraceDebug(m,"Hsvprins: Svpaci: %s %d %d %d",__FUNCTION__,__LINE__,eventid,value);

    switch(eventid)
    {
        case pginsN_EventManualInstallationCniExtractionStarted    :
            break;
        case pginsN_EventManualInstallationCniExtractionEnded       :
            break;        
        case pginsN_EventChannelFound                               :
			TraceDebug(m,"Hsvprins: Svpaci: %s %d %d %d",__FUNCTION__,__LINE__,eventid,value);
            break;
        case pginsN_EventInstallationStarted                :
		TraceDebug(m,"Hsvprins: Svpaci: %s %d %d %d",__FUNCTION__,__LINE__,eventid,value);
            {
                if(value == prins_InstallationModeAutomatic)
                {
                    if(initialised)
                    {
                        if(currentAciState == stIdle)
                        {
                            currentMaxAciPriority = pgAciPriorityInvalid;
                            currentMaxPriorityPage = INVALID_PAGENR;
                            currentMaxPriorityFrequency = INVALID_FREQUENCY;
                        }
                        else
                        {
                            ASSERT(!"Invalid ACI state");
                        }

                    }
                    else
                    {
                        /*ASSERT(!"Aci Power not initialised");*/
                    }
                }
            }
            break;
        case pginsN_EventATSSortingStarted                          :
            break;
        case pginsN_EventAciStoreStarted                            :
            break;
        case pginsN_EventTvSystemChanged                            :
            break;

        case pginsN_EventSearchInProgress                          :            
            break;
        case pginsN_EventTuningStarted                          :
            break;
        case pginsN_EventTuningStationFound    :            
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
            OnStationFound();
            break;
        case pginsN_EventTuningStationNotFound :
			TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
            OnStationNotFound();
            break;

            /*case pginsN_EventManualInstallationStarted                    :
              break;
              case pginsN_EventAutomaticInstallationCompleted         :
              break;
              case pginsN_EventAutomaticInstallationStopped               :
              break;
              case pginsN_EventManualInstallationStopped                  :
              break;
              case pginsN_EventManualInstallationChannelNotFound         :
              break;*/

        default:
            break;
    }
}


/****************************************************
 * Notification function to indicate teletext reset end
 ****************************************************/
void CSvcPaci_m_Priv::txrstN_OnResetEnd(void)
{
    if(initialised)
    {
        if(waitForStationFoundTxtReset )  /* the == TRUE was removed */ 
        {
            pmp_PmpSend( aciPump, eTeletextReset, 0 );
        }
    }
}

/****************************************************
 * Handler for pump messages
 ****************************************************/
void CSvcPaci_m_Priv::AciHandler(int event, Nat32 key)
{
    UNUSED(key);
    UNUSED(event);
    if(initialised)
    {
        FPCALL(ce_eventHandlerTable[event])();
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * function to handle OnHeaderDecoded notification
 * In stStart state (i.e when acquiring page 0x1be),
 * if the received page priority is highest it is decoded
 * further, otherwise failure notification is sent
 * If the state is any other, then decoding is continued 
 * further
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerHeaderDecoded(void )
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	if(initialised)
	{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		currentAciBroadcaster = acidec_GetBroadcasterInformation();
		currentAciNetwork = acidec_GetNetworkInformation();

        /* check for priority only if first page in aci acquisition */
        if(currentAciState == stStart)
        {
			/* HACK: Done during ACI Bringup */

            currentAciPriority = CalculatePriority(currentAciBroadcaster, currentAciNetwork);

            /* if highest priority continue decoding further else stop decoding*/
            if(currentAciPriority == pgAciPriority1)
            {
                TraceDebug(m,"CALL: acidec_ContinueDecoding()");
                acidec_ContinueDecoding();
            }
            else
            {
				TraceNotice (m,"%s Line %d ", __FUNCTION__,__LINE__);
                acidec_DecodeStop();
                if(currentAciPriority > currentMaxAciPriority )
                {
                    currentMaxAciPriority = currentAciPriority;
                    currentMaxPriorityPage = currentAciPage;                   
                    if(prins_iPresent())
                    {
                        currentMaxPriorityFrequency = prins_GetTunerFrequency(); 
                    }
                }
                SendCompletedNotification(FALSE);
            }
        }
        else if (currentAciState == stIdle )
        {
            ASSERT(!"Invalid state");
        }
        /* for any other page continue decoding further */
        else
        {
            acidec_ContinueDecoding();
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * function to handle ePageDecodeSuccessful event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerOnPageDecodeSuccessful(void )
{
    Nat8            i;
    HsvAciLanguage     UILanguage;
    Bool            languagePageAcquisition = FALSE;

    currentAciLanguage = acidec_GetAciLanguage(0);
    UILanguage = acidat_GetAciLanguage(sysset_GetSystemLanguage());
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	/* if restoring the multi page, then display page */
	if(currentAciState == stRestoreMtp)
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s: %d",__FUNCTION__,__LINE__);
		tmr_FireOnce(displayTimerHandle,adiv_MultipageDisplayTimeoutTime);
		currentAciState = stWaitForContinueDisplay;
		if(acidsN_iPresent())
		{
			TraceDebug(m,"Hsvprins: Svpaci: %s: %d",__FUNCTION__,__LINE__);
			acidsN_OnMultiPackageToBeDisplayed();
		}
	}
	else
	{
				 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		/* check for language only if getting the start page or the extra language page*/
		if( (currentAciLanguage != UILanguage) && ( (currentAciState == stStart) || 
					(currentAciState == stEvaluateLanguage)) )
		{
					 TraceDebug(m,"Hsvprins: Svpaci: %s: %d currentAciState=%d",__FUNCTION__,__LINE__,currentAciState);

			/* check if the language matches with the extra languages given in the page
			   if match not found continue decoding further else get the matched language page*/
			for(i=1; i<MAX_ACILANGUAGES_INPAGE; i++)   
			{
				if(UILanguage == acidec_GetAciLanguage(i))
				{
							 TraceDebug(m,"Hsvprins: Svpaci:: %s %d UILanguage = %d",__FUNCTION__,__LINE__,UILanguage);

					currentAciPage = acidec_GetExtensionPageForLanguage(UILanguage);
					currentAciState = stEvaluateLanguage;
					CallDecodeStart(currentAciPage);
					languagePageAcquisition = TRUE;
					break;
				}
			}
		}

        /* -- Proceed if language match -- */
        if(!languagePageAcquisition)
        {
            TraceDebug(m,"INvoking Process aci page from Page decode successful...");
            processAciPage();
        }
    }
}

/****************************************************
 * Process the decoded page
 ****************************************************/
void CSvcPaci_m_Priv::processAciPage( void )
{
    PageNr          extnPageNr;

	currentAciMode = acidec_GetMode();
	TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d currentAciMode=%d",__FUNCTION__,__LINE__,currentAciMode);
	/*single page mode*/
	if(currentAciMode == SinglePackageMode )
	{
		TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d currentAciMode=%d",__FUNCTION__,__LINE__,currentAciMode);
		CopyPresets();
		/* decode extension page if present*/
		extnPageNr = acidec_GetExtensionPage();
		if (extnPageNr != INVALID_PAGENR)
		{
			currentAciPage = extnPageNr;
			TraceDebug(m,"CallDecodeStart --> Processing ACI Page [ currentAciPage = %d ][extnPageNr= %d ]",currentAciPage, extnPageNr);
			currentAciState = stExtensionPage;
			CallDecodeStart(currentAciPage);
		}
		else
		{
						    TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d ",__FUNCTION__,__LINE__);

			WriteIndataAndSendCompletedNotification();
		}
	}
	/*multi page mode*/
	else if(currentAciMode == MultiPackageMode )
	{
		if(acidsN_iPresent())
		{
			TraceDebug(m,"++MultiPackageMode++");
			acidsN_OnMultiPackageFound();
		}
		currentMtpCount = acidec_GetNoOfMultipackageItems();
		TraceDebug(m,"Hsvprins: Svpaci:  %s %d currentMtpCount=%d",__FUNCTION__,__LINE__,currentMtpCount);

        /* save the current multi page and frequency*/
        if( frequencyDetuned == FALSE)
        {
            restoreMtpPage = currentAciPage;
            if(prins_iPresent())
            {
                restoreMtpFrequency = prins_GetTunerFrequency(); 
            }

		}
		currentMtpIndex = 0;
		acidec_DecodeStop();
						    TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d ",__FUNCTION__,__LINE__);

		/* tune to the first valid option in multi page*/
		if(!StartCurrentMtpItemDecoding())
		{
				TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d ",__FUNCTION__,__LINE__);

			if( frequencyDetuned )
			{
				 TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				ASSERT(!"Frequency can't be detuned at this time");
			}
			else
			{
				TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				/* all frequencies are invalid so display the page to the user to select from */
				currentAciState = stRestoreMtp;
				currentAciPage = restoreMtpPage;
				CallDecodeStart(currentAciPage);
			}
		}
	}
	else
	{
		ASSERT(!"Invalid aci mode");
	}
}

/****************************************************
 * This function handles the event when OnStationFound 
 * and teletext reset notifications are received
 * In evaluateMtpState it checks for header match 
 * if header match is found it restores back to
 * the original mtp frequency otherwise it checks 
 * other items in the mtp
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerStationFoundTxtReset(void )
{
	receivedTxtReset = FALSE;
	TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d currentAciState %d ",__FUNCTION__,__LINE__,currentAciState);
	switch(currentAciState)
	{
		case stRestoreMtp :
			currentAciPage = restoreMtpPage;
			CallDecodeStart(currentAciPage);
			break;
		case stMaxPriorityPage :
			currentAciPage = currentMaxPriorityPage;
			CallDecodeStart(currentAciPage);
			break;
		case stHeaderMatchSuccessful :
			acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);
			currentAciPage = currentMtpInfo.pageNo;
			CallDecodeStart(currentAciPage);
			break;
		case stCompleted:
			if(pgaciN_iPresent())
			{
				pgaciN_OnAciInstallationCompleted(completedStatus);
			}
			currentAciState = stIdle;
			break;
		case stEvaluateMtp:
			tryHeader = 0;

            // pmp_PmpSendAfter( TimerPump, 0, aciTimeoutServiceLabel, adiv_AciTxtHdrReqDelay );

            if( adiv_AciTxtHdrReqDelay > 0)
            {
                pmp_PmpSendAfter( TimerPump, 0, aciTimeoutServiceLabel, adiv_AciTxtHdrReqDelay );
            }
            else
            {
                if( adiv_AciTxtHdrReqDelay < 0 )
                {
                    ASSERT(!"adiv_AciTxtHdrReqDelay cannot have negative value");
                }
                pmp_PmpSend( TimerPump, 0, aciTimeoutServiceLabel );
            }

            break;
        default :
            ASSERT(!"INVALID ACI STATE");
            break;
    }
}

/****************************************************
 * function which processes OnStationNotFound notification
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerStationNotFound(void )
{
	receivedTxtReset = FALSE;
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d %d",__FUNCTION__,__LINE__,currentAciState);
	
	switch(currentAciState)
	{
		/*if station not found send completed notifications */
		case stRestoreMtp :
			WriteIndataAndSendCompletedNotification();
			break;
			/*if station not found send completed notifications */
		case stMaxPriorityPage :
			SendCompletedNotification(FALSE);
			break;
			/*if station not found send completed notifications */
		case stCompleted:
			if(pgaciN_iPresent())
			{
				pgaciN_OnAciInstallationCompleted(completedStatus);
			}
			currentAciState = stIdle;
			break;
			/* if station not found check for video not present condition for header match*/
		case stEvaluateMtp:
			if(CheckHeaderMatch())
			{
				TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				/* video not present and the service label also indicates video not present condition */
				if( frequencyDetuned )
				{
					currentAciState = stHeaderMatchSuccessful;
					TuneFrequency(restoreMtpFrequency);
					frequencyDetuned = FALSE;
					TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				}
			}
			else
			{
				/* check for next option in multi page menu*/
				currentMtpIndex++;
				TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				if(!StartCurrentMtpItemDecoding())
				{
					/* if no option left, tune back to the saved multi page frequency */
					if( frequencyDetuned )
					{
						currentAciState = stRestoreMtp;
						frequencyDetuned = FALSE;
						TuneFrequency(restoreMtpFrequency);
					}
					else
					{
						WriteIndataAndSendCompletedNotification();
					}
				}
			}
			break;
		default :
			ASSERT(!"INVALID ACI STATE");
			break;
	}
}

/****************************************************
 * event handler to handle ePageTimerExpired event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerPageTimerExpired(void )
{
			 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
	if (TimerHandlingNeeded == TRUE)
	{
		TraceNotice (m, "Timer Fire handled ");
		acidec_DecodeStop();
		WriteIndataAndSendCompletedNotification();
		TimerHandlingNeeded = FALSE;
		
	}
}

/****************************************************
 * event handler to handle eTeletextReset event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerTeletextReset(void )
{
    receivedTxtReset = TRUE;
    /* reset the aci decode component */
    acidec_Reset();
    /* if station found notification received send eStationFoundTxtReset event*/
    if(receivedOnStationFound)
    {
        receivedTxtReset = FALSE;
        receivedOnStationFound = FALSE;
        waitForStationFoundTxtReset = FALSE;
        pmp_PmpSend( aciPump, eStationFoundTxtReset, 0 );
    }
}

/****************************************************
 * event handler to handle eTunerTimeout event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerTunerTimeout(void )
{
    if(waitForStationFoundTxtReset )  /* the == TRUE was removed */
    {
        waitForStationFoundTxtReset = FALSE;
        receivedTxtReset = FALSE;
        switch(currentAciState)
        {
            case stRestoreMtp :
                WriteIndataAndSendCompletedNotification();
                break;
            case stMaxPriorityPage :
                SendCompletedNotification(FALSE);
                break;
            case stCompleted:
                if(pgaciN_iPresent())
                {
                    pgaciN_OnAciInstallationCompleted(completedStatus);
                }
                currentAciState = stIdle;
                break;
                /* tune to the next option if no tuner or teletext reset notification received for current option */
            case stEvaluateMtp:
                currentMtpIndex++;
                if(!StartCurrentMtpItemDecoding())
                {
                    if( frequencyDetuned )
                    {
                        currentAciState = stRestoreMtp;
                        frequencyDetuned = FALSE;
                        TuneFrequency(restoreMtpFrequency);
						TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
                    }
                    else
                    {
                        WriteIndataAndSendCompletedNotification();
                    }
                }
                break;
            default :
                ASSERT(!"INVALID ACI STATE");
                break;
        }
    }
}

/****************************************************
 * event handler to handle eStartAciTimeout event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerStartAciTimeout(void )
{

		 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

	/* check for accelerator characters in teletext headers*/
	if(acidec_IsAciPresent())
	{
		ResetVariables();
		currentAciPage = ACI_INITIAL_PAGENUMBER;
		currentAciState = stStart;
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		/*
		   if(tun_iPresent())
		   {
		   startFrequency = tun_GetFrequency();
		   }
		   */
		if(prins_iPresent())
		{
			startFrequency = prins_GetTunerFrequency(); 
			TraceDebug(m,"Hsvprins: Svpaci: Hsvprins: Svpaci: Svpaci: %s %d %d",__FUNCTION__,__LINE__,startFrequency);
		}

		CallDecodeStart(currentAciPage);
	}
	else
	{
		currentAciState = stIdle;
					 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

		if(pgaciN_iPresent())
		{
					 TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);

			pgaciN_OnAciInstallationCompleted(FALSE);
		}
	}
}

/****************************************************
 * event handler to handle eServiceLabelTimeout event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerServiceLabelTimeout(void )
{
    /*Bool magazine1Available = FALSE;*/
    Bool waitingForMagazine1 = FALSE;

	/* check for magazine 1 only if teletext is in transmission */
	if(IsTxtAvailable()/*txtpre_WstPresent()*/ )
	{
						TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);

		/* maximum tries 10 */
		if(tryHeader < 20) 
		{
				TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);

			if(ServiceLabelMatchPossible(1))
			{
				TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				/* magazine 1 headers are available */
				/*magazine1Available = TRUE;*/
			}
			else
			{
				TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
				/* wait some more time for magazine 1 */
				waitingForMagazine1 = TRUE;
			}
		}
	}
	
	TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
	if(CheckHeaderMatch(/*magazine1Available*/))
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
		/* if header match found, tune back to the original multi page frquency*/
		if( frequencyDetuned )
		{
			currentAciState = stHeaderMatchSuccessful;
			frequencyDetuned = FALSE;
			TuneFrequency(restoreMtpFrequency);
			TraceDebug(m,"Hsvprins: Svpaci: %s %d ",__FUNCTION__,__LINE__);
		}
		else
		{
			ASSERT(!"Invalid selction in aci");
		}
		/* no need to check for magazine1 now */
		waitingForMagazine1 = FALSE;
	}
	else
	{
		if(!waitingForMagazine1)
		{
			currentMtpIndex++;
			if(!StartCurrentMtpItemDecoding())
			{
				if( frequencyDetuned )
				{
					currentAciState = stRestoreMtp;
					frequencyDetuned = FALSE;
					TuneFrequency(restoreMtpFrequency);
				}
				else
				{
					ASSERT(!"Invalid selction in aci");
				}
			}
		}
	}
	if(waitingForMagazine1)
	{
		tryHeader++;

        // pmp_PmpSendAfter( TimerPump, 0, aciTimeoutServiceLabel, adiv_AciTxtHdrReqDelay );

        if( adiv_AciTxtHdrReqDelay > 0)
        {
            pmp_PmpSendAfter( TimerPump, 0, aciTimeoutServiceLabel, adiv_AciTxtHdrReqDelay );
        }
        else
        {
            if( adiv_AciTxtHdrReqDelay < 0 )
            {
                ASSERT(!"adiv_AciTxtHdrReqDelay cannot have negative value");
            }
            pmp_PmpSend( TimerPump, 0, aciTimeoutServiceLabel );
        }

    }
}


Bool CSvcPaci_m_Priv::ServiceLabelMatchPossible(Nat8 mag)
{
    TxtPacket0  temp ;
    Bool success = FALSE;
    int i;
    int sizeOfPacket0 = sizeof(temp.data) / sizeof(temp.data[0]);

    if(pkt0_iPresent())
    {
        pkt0_GetLatestHeader(&temp,mag);
    }        
    for(i=0; i<sizeOfPacket0; i++)
    {
        if(temp.data[i] != ' ')
        {
            success = TRUE;
            break;
        }
    }
    return success;
}

Bool CSvcPaci_m_Priv::IsTxtAvailable(void)
{
    /*TxtPacket0  temp ;*/
    Bool success = FALSE;
    Nat8 i;

    for (i = 0; i < MAXMAG ; i++)
    {
        /*pkt0_GetLatestHeader(&temp,i);*/
        if(ServiceLabelMatchPossible(i))
        {
            success = TRUE;
            break;
        }
    }
    return success;
}

/****************************************************
 * This function selects a menu option.
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerSelectIndex(void )
{
    int index;

    index = selectedIndex;

    /* event valid only when waiting for user input*/
    if(currentAciState == stWaitForUser)
    {
        if ( (index >= 0) && (index < acidec_GetNoOfMultipackageItems() ))
        {
            tmr_Cancel(displayTimerHandle);
            acidec_RemoveACIPage(currentAciPage);

            if(acidsN_iPresent())
            {
                acidsN_OnMultiPackageRemoved();
            }

            /* get the page corresponding to the respective selection */
            acidec_GetMultiPackageInformation((Nat8)index, &currentMtpInfo);
            currentAciPage = currentMtpInfo.pageNo;

            currentAciState = stMtpSelectedPage;
            CallDecodeStart(currentAciPage);
        }
        else
        {
            ASSERT(!"Invalid Index in aci");
        }
    }
    else
    {
        ASSERT(!" Invalid aci state");
    }
}

/****************************************************
 * This function stores presets in NVM one by one
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerStorePresets(void )
{
    HsvAciSingleInfo   singleInfo;
    Bool            clearPreset = FALSE;

    /* event valid only when waiting for user input*/
    /*ASSERT(writeIndataInProgress);*/
    if( currentAciState == stStorePresets)
    {
        if(currentPresetToStore < adiv_MaxPresets)
        {
            singleInfo = decodedPresets[currentPresetToStore];
			TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d singleInfo.presetNo=%d",__FUNCTION__,__LINE__,singleInfo.presetNo);
			if(singleInfo.presetNo == INVALID_PRESETNO)
			{
				singleInfo.presetNo = currentPresetToStore;
				clearPreset = TRUE;
	 		    TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);
			}
			currentPresetToStore++;
	 		TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d currentPresetToStore = %d",__FUNCTION__,__LINE__,currentPresetToStore);			
			acidat_StorePreset(singleInfo,clearPreset);
			pmp_PmpSend( aciPump, eStorePresets, 0 );
		}
		else
		{
			writeIndataInProgress = FALSE;
			SendCompletedNotification(TRUE);
		}
	}
	/*else
	  {
	  ASSERT(!" Invalid aci state");
	  }*/
}

/****************************************************
 * Callback function for ACI proces timer expiry event
 ****************************************************/
void CSvcPaci_m_Priv::OnAciPageTimerExpired( void )
{
    if(initialised)
    {
        pmp_PmpSend( aciPump, eAciPageTimerExpired, 0 );
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * Callback function for ACI proces timer expiry event
 ****************************************************/
void CSvcPaci_m_Priv::EventHandlerDisplayTimerExpired(void )
{
    /* event valid only when waiting for user input*/
    if(currentAciState == stWaitForUser)
    {
        tmr_Cancel(displayTimerHandle);
        acidec_RemoveACIPage(currentAciPage);
        acidec_DecodeStop();
        if(acidsN_iPresent())
        {
            acidsN_OnMultiPackageRemoved();
        }
        /* get the defult page if available*/
        currentAciPage = acidec_GetDefaultPage();
        if(currentAciPage == INVALID_PAGENR)
        {
            /* if default page not available get the page of first option in multi page*/
            acidec_GetMultiPackageInformation(0, &currentMtpInfo);
            currentAciPage = currentMtpInfo.pageNo;
        }

        if(currentAciPage != INVALID_PAGENR)
        {
            currentAciState = stDefaultPage;
            CallDecodeStart(currentAciPage);
        }
        else
        {
            WriteIndataAndSendCompletedNotification();
        }
    }
    else
    {
        ASSERT(!"Invalid Aci State");
    }
}

/****************************************************
 * Callback function for ACI display timer expiry event
 ****************************************************/
void CSvcPaci_m_Priv::OnDisplayTimerExpired( void )
{
    if(initialised)
    {
        pmp_PmpSend( aciPump, eDisplayTimerExpired, 0 );
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * Callback function for tuning timer expiry event
 ****************************************************/
void CSvcPaci_m_Priv::OnPumpTimerExpired(int system, Nat32 timeoutId )
{
    UNUSED(system);
    if(initialised)
    {
        switch (timeoutId)
        {
            case aciTimeoutTuner:
                pmp_PmpSend( aciPump, eTunerTimeout, timeoutId );
                break;
            case aciTimeoutStartAci:
				TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
                pmp_PmpSend( aciPump, eStartAciTimeout, timeoutId );
                break;
            case aciTimeoutServiceLabel:
                pmp_PmpSend( aciPump, eServiceLabelTimeout, timeoutId );
                break;
            default:
                ASSERT(!"Invalid Timeout Id");
                break;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************
 * function for processing the current item of multipage
 * in EvaluateMtp state
 ****************************************************/
Bool CSvcPaci_m_Priv::StartCurrentMtpItemDecoding()
{
	Bool returnVal = FALSE;
	/* check if current mtp index exceeds the total no of options in multi page */
	TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
	currentMtpIndex = currentMtpCount;
	while(currentMtpIndex < currentMtpCount)
	{
		acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);
		/* tune to the frequency of the option if it is valid else check next item*/
		TraceDebug(m,"Hsvprins: Svpaci: %s %d currentMtpInfo.freqLabel=%d",__FUNCTION__,__LINE__,currentMtpInfo.freqLabel);	
		
		if(currentMtpInfo.freqLabel == INVALID_FREQUENCY)
		{
			TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
			currentMtpIndex++;
		}
		else
		{
			TraceDebug(m,"Hsvprins: Svpaci: %s %d currentMtpInfo.freqLabel=%d currentMtpIndex=%d",__FUNCTION__,__LINE__,currentMtpInfo.freqLabel,currentMtpIndex);	
			currentAciState = stEvaluateMtp;
			frequencyDetuned = TRUE;

			acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);
			TuneFrequency((currentMtpInfo.freqLabel * 16)/100);
			returnVal = TRUE;
			break;
		}
	}
			TraceDebug(m,"Hsvprins: Svpaci: %s %d returnVal=%d",__FUNCTION__,__LINE__,returnVal);		
	return (returnVal);
}



/****************************************************
 * Function to store data in a single page by using
 * program data interface
 ****************************************************/
void CSvcPaci_m_Priv::CopyPresets()
{
    Int32           freq;
    int             prNo;
    HsvAciSingleInfo   singleInfo;
    int             prCount;
    Nat8            i;

	prCount = acidec_GetNoOfPresetEntries();
	TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d prCount=%d",__FUNCTION__,__LINE__,prCount);

    for(i=0; i<prCount; i++)
    {
        acidec_GetSinglePackageInformation(i,&singleInfo);

		freq = singleInfo.frequency;
		freq =  (freq  * 16 ) / 100;
		singleInfo.frequency = freq;
		prNo = singleInfo.presetNo;
	    TraceDebug(m,"Hsvprins: Svpaci: Svpaci: %s %d freq=%d prNo=%d",__FUNCTION__,__LINE__,freq,prNo);

        /* check the validity of the preset data*/
        /*if( ((tun_iPresent()) && (freq >= tun_MinFrequency) && (freq <= tun_MaxFrequency)) &&
          ((prNo >= adiv_MinTunPreset) && (prNo <= adiv_MaxTunPreset)) 
          )*/
        if( ((prins_iPresent()) && (freq >= prins_GetMinFrequency()) && (freq <= prins_GetMaxFrequency())) &&
                ((prNo >= adiv_MinTunPreset) && (prNo <= adiv_MaxTunPreset)) 
          )
        {
            if(decodedPresets[prNo].presetNo == INVALID_PRESETNO)
            {
                currentDecodedTotalPresets++;
            }
            decodedPresets[prNo] = singleInfo;
        }
        //else
        {
            /*ASSERT(!"Invalid Presets");*/
        }
    }
}


/****************************************************
 * Function to store data in a single page by using
 * program data interface
 ****************************************************/
void CSvcPaci_m_Priv::StoreInData()
{
    writeIndataInProgress = TRUE;
    if( currentDecodedTotalPresets != 0) 
    {
        /*pgdat_Reset();*/
        pgcni_ClearCNIList();
    }
    currentPresetToStore = 0;
    currentAciState = stStorePresets;
    pmp_PmpSend( aciPump, eStorePresets, 0 );
}

/****************************************************
 * Function to calculate the page priority from its
 * broadcaster and network information
 ****************************************************/
HsvAciPriority CSvcPaci_m_Priv::CalculatePriority(HsvAciBroadcaster broadcaster, HsvAciNetwork network)
{
    HsvAciPriority pr;
    if((broadcaster == AciBroadcasterCable) && (network == AciNetworkCable))
    {
        pr = pgAciPriority1;
    }
    else if((broadcaster == AciBroadcasterTerrestrial) && (network == AciNetworkTerrestrial))
    {
        pr = pgAciPriority2;
    }
    else if((broadcaster == AciBroadcasterTerrestrial) && (network == AciNetworkCable))
    {
        pr = pgAciPriority3;
    }
    else if((broadcaster == AciBroadcasterCable) && (network == AciNetworkTerrestrial))
    {
        pr = pgAciPriority4;
    }
    else
    {
        pr = pgAciPriorityInvalid;
    }
    return (pr);
}


/****************************************************
 * Function to check header match
 ****************************************************/
Bool CSvcPaci_m_Priv::CheckHeaderMatch()
{
    Bool        matchFound ;

    /* check if video present condition */
    if(vip_GetVideoPresent() == vip_VideoPresenceDetected)
    {
        /* check for teletext present condition on the particular frequency*/
        if((txtpre_iPresent()?txtpre_WstPresent():0))
        {
            /* perform service label match if both video and teletext transmission present on the frequency */
            acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);

            if(acidec_MatchServiceLabel( currentMtpInfo.serviceLabel ))
            {
                matchFound = TRUE;
            }
            else
            {
                matchFound = FALSE;
            }
        }
        else
        {
            /*check if the service label indicates no teletext present condition */
            acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);
            if(currentMtpInfo.teletextPresent)
            {
                matchFound = FALSE;
            }
            else
            {
                matchFound = TRUE;
            }
        }
    }
    else
    {
        /*check if the service label indicates no video present condition */
        acidec_GetMultiPackageInformation(currentMtpIndex, &currentMtpInfo);

        if(currentMtpInfo.carrierPresent)
        {
            matchFound = FALSE;
        }
        else
        {
            matchFound = TRUE;
        }
    }
    return matchFound;
}

/****************************************************
 * Function to tune to a given frequency and set the 
 * corresponding variables
 ****************************************************/
void CSvcPaci_m_Priv::TuneFrequency(Nat32 frequency)
{
	receivedTxtReset = FALSE;
	receivedOnStationFound = FALSE;
	receivedOnStationNotFound = FALSE;
	waitForStationFoundTxtReset = TRUE;
	acidec_DecodeStop();
	pmp_PmpSendAfter( TimerPump, 0, aciTimeoutTuner, 120000);//adiv_TunNotifyTimeout );
	TraceDebug(m,"Hsvprins: Svpaci: %s %d frequency = %d timeout = is 12 sec waitForStationFoundTxtReset=%d",__FUNCTION__,__LINE__,frequency,waitForStationFoundTxtReset);	
        pmp_PmpSendAfter( TimerPump, 0, aciTimeoutTuner, 120000);//adiv_TunNotifyTimeout ); /* HACK: ACI Bringup 2000 was used for timeout */
/*
    if( adiv_TunNotifyTimeout > 0) 
    {
        pmp_PmpSendAfter( TimerPump, 0, aciTimeoutTuner, adiv_TunNotifyTimeout ); /* HACK: ACI Bringup 2000 was used for timeout 
    }
    else
    {
        if( adiv_TunNotifyTimeout < 0 )
        {
            ASSERT(!"adiv_TunNotifyTimeout cannot have negative value");
        }
        pmp_PmpSend( TimerPump, 0, aciTimeoutTuner );
    }*/



    /*
       if(tun_iPresent())
       {
       tun_SetFrequency( frequency,TRUE);
       }
       */
 
        prins_SetTunerFrequency((frequency *16)/1000, TRUE );
   	    TraceDebug(m,"Hsvprins: Svpaci: %s %d frequency = %d timeout = is 12 sec",__FUNCTION__,__LINE__,(frequency *16)/1000);	

}

/****************************************************
 * Function to calling decodestart and timer 
 ****************************************************/
void CSvcPaci_m_Priv::CallDecodeStart(PageNr page)
{
	acidec_DecodeStop();
	TraceNotice (m,"%s Line %d ", __FUNCTION__,__LINE__);
	if(currentAciState == stRestoreMtp)
	{
		TraceNotice (m,"%s Line %d ", __FUNCTION__,__LINE__);
		//tmr_FireOnce(pageTimerHandle,adiv_RestorePageAcqTimeoutTime);
		pmp_PmpSendAfter( aciPump, eAciPageTimerExpired, 0, RESTOREPAGEACQTIMEOUTVALUE );
		TimerHandlingNeeded = TRUE;
	}
	else
	{
		//tmr_FireOnce(pageTimerHandle,adiv_AciAcquisitionTimeoutTime);
		pmp_PmpSendAfter( aciPump, eAciPageTimerExpired, 0, ACIACQUISITIONTIMEOUTVALUE );
		TimerHandlingNeeded = TRUE;
	}
	acidec_DecodeStart( page );
}

/****************************************************
 * Function to check if presets were decoded in any
 * check in any previous pages and write them to data
 * It will send successful notification if presets were
 * decoded and failure notification if otherwise
 ****************************************************/
void CSvcPaci_m_Priv::WriteIndataAndSendCompletedNotification( void )
{
    if(currentDecodedTotalPresets)
    {
        if(pgaciN_iPresent())
        {
            pgaciN_aciPresetsWriteInDataStarted();
        }
        StoreInData();
        /*SendCompletedNotification(TRUE);*/
    }
    else
    {
        SendCompletedNotification(FALSE);
    }
}

/****************************************************
 * Function to check if the starting frequency was detuned 
 * before sending the completed notification
 ****************************************************/
void CSvcPaci_m_Priv::SendCompletedNotification(Bool success)
{
	tmr_Cancel(pageTimerHandle);
	TimerHandlingNeeded = FALSE;
	tmr_Cancel(displayTimerHandle);
	completedStatus = success;
	/* if frequency changed then tune back to original frequency */
	if( frequencyDetuned )
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
		TuneFrequency(startFrequency);
		currentAciState = stCompleted;
		frequencyDetuned = FALSE;
	}
	else
	{
		TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
		currentAciState = stIdle;
		if(pgaciN_iPresent())
		{
			TraceDebug(m,"Hsvprins: Svpaci: %s %d",__FUNCTION__,__LINE__);	
			pgaciN_OnAciInstallationCompleted(success);
		}
	}
}

/****************************************************
 * Resets all current AciInstallation variables
 * except the variables related to the priority in 
 * frequency band search
 ****************************************************/
void CSvcPaci_m_Priv::ResetVariables()
{
    int i;

    currentAciTimeOut = aciTimeoutInvalid;
    restoreMtpPage = INVALID_PAGENR;
    restoreMtpFrequency = INVALID_FREQUENCY;
    currentAciState = stIdle;
    startFrequency = INVALID_FREQUENCY;
    currentAciPage = INVALID_PAGENR;
    currentDecodedTotalPresets = 0;
    frequencyDetuned = FALSE;
    currentAciBroadcaster = AciBroadcasterInvalid;
    currentAciNetwork = AciNetworkInvalid;
    currentAciMode = InvalidMode;
    currentAciPriority = pgAciPriorityInvalid;
    currentAciLanguage = AciLanguageInvalid;
    currentMtpIndex = 0;
    currentMtpCount = 0;
    waitForStationFoundTxtReset = 0;
    receivedTxtReset = FALSE;
    receivedOnStationFound = FALSE;
    receivedOnStationNotFound = FALSE;
    selectedIndex = 0;

    completedStatus = FALSE;
    writeIndataInProgress = FALSE;
    for(i=0; i<adiv_MaxPresets; i++)
    {
        decodedPresets[i].presetNo = INVALID_PRESETNO;
    }
}

void CSvcPaci_m_Priv::acidecN_OnReceivedPage()
{
}

void CSvcPaci_m_Priv::txrstN_OnResetBegin()
{
}
