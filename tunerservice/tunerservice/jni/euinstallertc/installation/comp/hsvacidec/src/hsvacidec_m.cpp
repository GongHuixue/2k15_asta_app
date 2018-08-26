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
 *          %name: hsvacidec_m.c %
 *       %version: TVG_Fusion_1 %
 * %date_modified: Wed Nov 07 10:32:00 2007 %
 *    %derived_by: lakshminb %
 */

/* Header files */

#include "_hsvacidec_m.h"

TRACESYMBOL(m, "analog/installation/hsvacidec_m")

/****************************************************
 * Local macro definitions
 ****************************************************/

 extern "C" {
 
	Bool tspah2__mode2_SetMode( int mode );
	void tspah2__pctl_SetRequestPage( PageNr pNo, Subcode subCd );
 }
 
 

Nat8 CHsvAciDecode_Priv::s__presetCount = 0;
HsvAciMode CHsvAciDecode_Priv::s__mode;
/* Local Types */


/* declaration of static variables */
Pump CHsvAciDecode_Priv::s__pumpDecodePage;

Pump CHsvAciDecode_Priv::s__pumpRequestPage;


/* variables related to power initialisation */
Bool CHsvAciDecode_Priv::s__Initialised = FALSE;

Bool CHsvAciDecode_Priv::s__PowerInitialised = FALSE;

Bool CHsvAciDecode_Priv::s__InterfacesConnected = FALSE;


/* variables related to the current page being decoded */
TxtPageHandle CHsvAciDecode_Priv::s__pageHandle = NOHND;

Nat8 * CHsvAciDecode_Priv::s__dPacket;



int CHsvAciDecode_Priv::s__mtpCurrentCount;

Nat8 CHsvAciDecode_Priv::s__mtpCurrentRow;

Bool CHsvAciDecode_Priv::s__aciDecodeOn = FALSE;




HsvAciNetwork CHsvAciDecode_Priv::s__network;

HsvAciLanguage CHsvAciDecode_Priv::s__language;

HsvAciBroadcaster CHsvAciDecode_Priv::s__broadcaster;

PageNr CHsvAciDecode_Priv::s__extensionPageNumber;



Nat8 CHsvAciDecode_Priv::s__multiPackageItems;

PageNr CHsvAciDecode_Priv::s__MtpDefaultPage;

PageNr CHsvAciDecode_Priv::s__currentRequestedPage;

Subcode CHsvAciDecode_Priv::s__currentReceivedPageSubcode;

int CHsvAciDecode_Priv::s__currentState;
Nat8 CHsvAciDecode_Priv::s__pktptr[400];

HsvAciSingleInfo CHsvAciDecode_Priv::s__presetSingle[MAX_FIXED_SINGLEPRESET_PER_PAGE];

HsvAciMultiInfo CHsvAciDecode_Priv::s__mtpArray[MAX_PRESETROWS_PER_PAGE];

Nat8 CHsvAciDecode_Priv::s__mtpRow[MAX_PRESETROWS_PER_PAGE];

languagePageInfo CHsvAciDecode_Priv::s__aciLanguageArray[MAX_LANGUAGEPAGES_INSYSTEMROW];


/* variables related to display  page being decoded */
TWindowId CHsvAciDecode_Priv::s__mainWindowId = 0;

Bool CHsvAciDecode_Priv::s__txtMainWindow;

Bool CHsvAciDecode_Priv::s__ConfigureOn = FALSE;

Bool CHsvAciDecode_Priv::s__headerDecoded = FALSE;


Nat8 CHsvAciDecode_Priv::s__FourtySpaces[40] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };


/* declaration of static functions */
CHsvAciDecode_Priv *AciPageHandle;



void CHsvAciDecode_Priv::Setacipagehandle( CHsvAciDecode_Priv* acipagehandle)
{
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d",__FUNCTION__,__LINE__);	AciPageHandle = acipagehandle;	
}


















/* functions in Koala interfaces */


/*TODO: this is notification from req intf*/


void PageReceivedHandler2(int tag, PageNr page,Subcode subcode,Bool arvd_drop,Nat16 ctrlbits)
{
	__android_log_print(ANDROID_LOG_DEBUG, m, "Hsvprins: Svpaci: Hsvacidec:%s  %d", __FUNCTION__,__LINE__);
	AciPageHandle->PageReceivedHandler( tag,  page, subcode, arvd_drop, ctrlbits);
}


/*****************************************************************
 * Power functions
 *****************************************************************/

void CHsvAciDecode_Priv::pow_Init( void )
{
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d",__FUNCTION__,__LINE__);
    if( cnv_iPresent() &&
            pkt0_iPresent() &&
            dsdrv_iPresent() &&
            req_iPresent() &&
            acc_iPresent() &&
            dsenb_iPresent())
    {
	    TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);        	
		InterfacesConnected = TRUE;
    }
    pumpDecodePage     = pmp_PmpCreateEx(pen_PumpEngine,DecodePageHandler, TRUE, "PageDecodePump");
	pumpRequestPage    = pmp_PmpCreateEx(pen_PumpEngine,RequestPageHandler, TRUE, "RequestDecodePump");
    PowerInitialised = TRUE;
}

void CHsvAciDecode_Priv::pow_TurnOn(void)
{
    if(PowerInitialised)
    {
        SuggestPage(INITIAL_START_PAGE);
        pageHandle = NOHND;
        resetMultiPageInfo();
        ResetVariables();
        currentState = acidec_StateIdle;
        Initialised = TRUE;
    }

}

void CHsvAciDecode_Priv::pow_TurnOff(void)
{ 
    if(Initialised)
    {
        if(InterfacesConnected)
        {
            if (NOHND != pageHandle)
            {
                acc_ClosePage(pageHandle);
                pageHandle = NOHND;
            }
            if(div_PrefetchAciPage)
            {
                req_UnSuggestPage(INITIAL_START_PAGE);
            }
        }
        else
        {
            ASSERT(!"Aci optional intf not connected");
        }
    }
    Initialised = FALSE;
    InterfacesConnected = FALSE;
}
extern Bool acipage_present_temp;
/****************************************************************************
  Interface function implementations
 ****************************************************************************/
/****************************************************************************
 * Function name     : acidec_IsAciPresent
 * Description       : Checks for the presence of accelerator characters 
 in the teletext headers
 ****************************************************************************/
Bool CHsvAciDecode_Priv::acidec_IsAciPresent(void)
{
    Nat8        i;
    Nat8        j;
    Nat8        k=0;
    TxtPacket0  header;
    Bool        AciPresent = FALSE;
    int         Cable;
    int         Satellite;
    int         Terrestrial;
	    TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);        
    if(Initialised)
    {
	acipage_present_temp = 0;
	    TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d",__FUNCTION__,__LINE__);
        if(InterfacesConnected)
        {
		    TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d",__FUNCTION__,__LINE__);
            for (i = 0; i < MAXMAG ; i++)
            {
                if(i == 0)
                {
                    k = 1;
                }
                else if(i == (MAXMAG-1) )
                {
                    k = 0;
                }
                else
                {
                    k++;
                }

                Cable=0;
                Satellite=0;
                Terrestrial=0;

                pkt0_GetLatestHeader(&header,k);
				 TraceDebug(m,"Hsvprins: Svpaci:  Hsvacidec: cable header %s %d acipage_present_temp %d ",__FUNCTION__,__LINE__ ,acipage_present_temp);
                for (j=0 ; j <= 31 ;j++)
                {
                    switch(header.data[j])
                    {
                        case 0x09 : 
                            TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: cable header %s %d",__FUNCTION__,__LINE__);
                            Cable++;
                            if(Cable >= 2)
                            {
                                broadcaster = AciBroadcasterCable;        
                                AciPresent = TRUE; 
                            }
                            break;
                        case 0x0C : 
                            TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: sat header %s %d",__FUNCTION__,__LINE__);
                            Satellite++;
                            if(Satellite >= 2)
                            {
                                broadcaster = AciBroadcasterSatellite;    
                                AciPresent = TRUE ; 
                            }
                            break;
                        case 0x19 :
                            TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: ter header %s %d",__FUNCTION__,__LINE__);
                            Terrestrial++;
                            if(Terrestrial >= 2)
                            {
                                broadcaster = AciBroadcasterTerrestrial;  
                                AciPresent = TRUE; 
                            }
                            break;
                        default:
                            break;
                    }
                    if(AciPresent)
                    {
					    TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:  %s %d",__FUNCTION__,__LINE__);
                        break;
                    }
                }
                if(AciPresent)
                {
					TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:  %s %d",__FUNCTION__,__LINE__);				
                    break;
                }
            }
        }
        else
        {
            ASSERT(!"Aci optional interface not connected");
			 TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d",__FUNCTION__,__LINE__);
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
	
	                               
								TraceNotice (m,"ACI Present status %d ", AciPresent);
    return(AciPresent);
}

/****************************************************************************
 * Function name     : acidec_DecodeStart
 * Description       : Starts retrieving and decoding of aci page
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_DecodeStart(PageNr pn)
{
    if(Initialised)
    {
        if(InterfacesConnected)
        {
            if(!aciDecodeOn)
            {
                headerDecoded = FALSE;
                currentState = acidec_StateDecoding;
                currentRequestedPage = pn;
                if (NOHND != pageHandle)
                {
                    acc_ClosePage(pageHandle);
                    pageHandle = NOHND;
                }
                aciDecodeOn = TRUE;
				TraceNotice (m,"%s Line %d ", __FUNCTION__,__LINE__);
                req_SetType(currentRequestedPage,ptData,0,NULL);
		 		pmp_PmpSendAfter( pumpRequestPage, 0, 0, 2000);				
            }        
            else
            {
                ASSERT(!"Aci decode already On");
            }
        }
        else
        {
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_DecodeStop
 * Description       : Stops retrieving and decoding of aci page and clears all
 buffers
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_DecodeStop(void)
{
    if(Initialised)
    {
        if(InterfacesConnected)
        {
            if(aciDecodeOn)
            {
			TraceNotice (m,"%s Line %d currentRequestedPage %d  ", __FUNCTION__,__LINE__,currentRequestedPage);
                req_UnRequestPage(currentRequestedPage,SC_ANY,PageReceivedHandler2);

            }
            aciDecodeOn = FALSE;
            currentState = acidec_StateIdle;
            ResetVariables();
        }
        else
        {
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_GetDecodeStatus
 * Description       : Stops retrieving and decoding of aci page and clears all
 buffers
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_Reset(void)
{
    if(Initialised)
    {
        pageHandle = NOHND;
        /*    resetMultiPageInfo();*/
        ResetVariables();
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_GetDecodeStatus
 * Description       : Stops retrieving and decoding of aci page and clears all
 buffers
 ****************************************************************************/
int CHsvAciDecode_Priv::acidec_GetDecodeStatus(void)
{
    int returnVal;
    if(Initialised)
    {
        returnVal = currentState;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnVal = AciStateOff;
    }
    return(returnVal);
}

/****************************************************************************
 * Function name     : acidec_ContinueDecoding
 * Description       : 
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_ContinueDecoding(void)
{
    if(Initialised)
    {
        ASSERT(aciDecodeOn);
        if(headerDecoded)
        {
            headerDecoded = FALSE;
            if(mode == SinglePackageMode)
            {
				TraceNotice (m,"%s Line %d mode %d  ", __FUNCTION__,__LINE__,mode);
                AciSingleDecode();
            }
            else if(mode == MultiPackageMode)
            {
                AciMultiDecode();
            }
            else
            {
                ASSERT(!"Invalid Aci Mode");
            }
        }
        else
        {
            ASSERT(!"header not decoded");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }

}

/****************************************************************************
 * Function name     : acidec_GetMode
 * Description       : Gets page transmission mode of a page
 ****************************************************************************/
HsvAciMode CHsvAciDecode_Priv::acidec_GetMode(void)
{
    HsvAciMode returnVal;
    if(Initialised)
    {
				TraceNotice (m,"Hsvprins: Svpaci: %s  %d mode = %d  ", __FUNCTION__,__LINE__,mode);	

        returnVal = mode;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnVal = InvalidMode;
    }
			TraceNotice (m,"Hsvprins: Svpaci: %s  %d mode = %d  ", __FUNCTION__,__LINE__,mode);	
    return(returnVal);
}

/****************************************************************************
 * Function name     : acidec_GetNetworkInformation
 * Description       : Gets network information of a page
 ****************************************************************************/
HsvAciNetwork CHsvAciDecode_Priv::acidec_GetNetworkInformation(void)
{
    HsvAciNetwork returnVal;
    if(Initialised)
    {
        returnVal = network;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnVal = AciNetworkInvalid;
    }
    return returnVal;
}

/****************************************************************************
 * Function name     : acidec_GetBroadcasterInformation
 * Description       : Gets broadcaster information of a page
 ****************************************************************************/
HsvAciBroadcaster CHsvAciDecode_Priv::acidec_GetBroadcasterInformation(void)
{
    HsvAciBroadcaster returnVal;
    if(Initialised)
    {
        returnVal = broadcaster;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnVal = AciBroadcasterInvalid;
    }
    return returnVal;
}

/****************************************************************************
 * Function name     : acidec_GetAciLanguage
 * Description       : Gets Aci language of a page
 ****************************************************************************/
HsvAciLanguage CHsvAciDecode_Priv::acidec_GetAciLanguage(Nat8 lanIndex)
{
    HsvAciLanguage returnLang;

    if(Initialised)
    {
        if(lanIndex < MAX_LANGUAGEPAGES_INSYSTEMROW)
        {
            returnLang = aciLanguageArray[lanIndex].language;
        }
        else
        {
            ASSERT(!"Invalid language index");
            returnLang = aciLanguageArray[0].language;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnLang = AciLanguageInvalid;
    }
    return(returnLang);
}

/****************************************************************************
 * Function name     : acidec_GetExtensionPageForLanguage
 * Description       : Gets corresponding page for a given aci language
 ****************************************************************************/
PageNr CHsvAciDecode_Priv::acidec_GetExtensionPageForLanguage (HsvAciLanguage lan)
{
    int         i;
    PageNr      returnPage = INVALID_PAGENR;

    if(Initialised)
    {
        if(lan < AciLanguageInvalid)
        {
            for(i = 0 ;i < MAX_LANGUAGEPAGES_INSYSTEMROW ; i++)
            {
                if (aciLanguageArray[i].language == lan)
                {
                    returnPage = aciLanguageArray[i].pageNo;
                    break;
                }
            }
        }
        else
        {
            ASSERT(!"Invalid language");
            returnPage = INVALID_PAGENR;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return (returnPage);
}

/****************************************************************************
 * Function name     : acidec_GetNoOfPresetEntries
 * Description       : Gets number of decoded presets in single type aci page
 ****************************************************************************/
Nat8 CHsvAciDecode_Priv::acidec_GetNoOfPresetEntries(void)
{
    Nat8 returnVal;
    if(Initialised)
    {
        returnVal = presetCount;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        returnVal = 0;
    }
    return returnVal;
}

/****************************************************************************
 * Function name     : acidec_GetSinglePackageInformation
 * Description       : Gets a decoded preset from single type page
 ****************************************************************************/
Bool CHsvAciDecode_Priv::acidec_GetSinglePackageInformation(Nat8 packageIndex, HsvAciSingleInfo *singleinfo)
{
    Bool returnVal = FALSE;
    if(Initialised)
    {
        if(packageIndex < MAX_FIXED_SINGLEPRESET_PER_PAGE)
        {
            if (packageIndex >= presetCount)
            {
                returnVal = FALSE;
            }
            else
            {
                *singleinfo = presetSingle[packageIndex];
                returnVal = TRUE;
            }
        }
        else
        {
            ASSERT(!"Invalid package index");
            returnVal = FALSE;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return(returnVal);
}

/****************************************************************************
 * Function name     : acidec_GetExtensionPage
 * Description       : Gets extension page for a given single page
 ****************************************************************************/
PageNr CHsvAciDecode_Priv::acidec_GetExtensionPage(void)
{
    PageNr returnVal = INVALID_PAGENR;
    if(Initialised)
    {
        returnVal = extensionPageNumber;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return(returnVal);
}

/****************************************************************************
 * Function name     : acidec_GetDefaultPage
 * Description       : Gets default page number in a multi page
 ****************************************************************************/
PageNr CHsvAciDecode_Priv::acidec_GetDefaultPage( void)
{
    PageNr returnVal = INVALID_PAGENR;
    if(Initialised)
    {
        returnVal =  MtpDefaultPage;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return returnVal;
}

/****************************************************************************
 * Function name     : acidec_MatchServiceLabel
 * Description       : checks for service label on the tuned channel
 ****************************************************************************/
Bool CHsvAciDecode_Priv::acidec_MatchServiceLabel( Nat8* label)
{
    int         index;
    Bool        returnVal=FALSE;
    TxtPacket0  temp ;

    if(Initialised)
    {
        if(InterfacesConnected)
        {
            pkt0_GetLatestHeader(&temp,1);

            if( (label[0] == 0x3d) && (label[1] == 0x3d) && (label[2] == 0x3d))    /* === */
            {
                returnVal = FALSE;
            }

            else if( (label[0] == 0x3f) && (label[1] == 0x3f) && ( label[2] == 0x3f))   /* ??? */
            {
                returnVal = TRUE;
            }

            else if( (label[0] == 0x25) && (label[1] == 0x25) && (label[2] == 0x25))    /* %%% */
            {
                returnVal = FALSE;
            }

            else
            {
                index = 0;
                while(  index < 21 )
                {
                    if( (label[0] == '?') || (label[0] == temp.data[index]) )
                    {
                        if( (label[1] == '?') || (label[1] == temp.data[index + 1]) )
                        {
                            if( (label[2] == '?') || (label[2] == temp.data[index + 2]) )
                            {
                                returnVal = TRUE;
                                break;
                            }
                        }
                    }
                    index++;
                }
            }
        }
        else
        {
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return( returnVal );
}

/****************************************************************************
 * Function name     : acidec_GetMultiPackageInformation
 * Description       : gets decoded preset from a multipage
 ****************************************************************************/
Bool CHsvAciDecode_Priv::acidec_GetMultiPackageInformation( Nat8 packageIndex, HsvAciMultiInfo* multiInfo)
{
    Bool returnVal= FALSE;
    if(Initialised)
    {
        if(packageIndex < MAX_PRESETROWS_PER_PAGE)
        {
            if (packageIndex >= multiPackageItems)
            {
                returnVal = FALSE;
            }
            else
            {
                *multiInfo = mtpArray[packageIndex];
                returnVal = TRUE;
            }
        }
        else
        {
            ASSERT(!"Invalid package index");
            returnVal = FALSE;
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return (returnVal);
}

/****************************************************************************
 * Function name     : acidec_DisplayACIPage
 * Description       : displays a multi page
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_DisplayACIPage( PageNr pn)
{
    int                 i; 
    PageNr              pageNumber;
    Bool                success;
    Nat8*               old;
    TxtPageConfigStruct pcs;
	
	
	tspah2__mode2_SetMode( 0 );
	tspah2__pctl_SetRequestPage(pn, 0x3f7f );

	
	
     #if 0
    if(Initialised)
    {
        if(InterfacesConnected)
        {
            if(pageHandle == NOHND)
            {
                pageHandle = acc_OpenPageForRead(currentRequestedPage,currentReceivedPageSubcode);
            }

            old = (Nat8 *)FourtySpaces;

            if(pageHandle != NOHND)
            {
                if(pn == currentRequestedPage)
                {
                    dPacket = (Nat8 *)acc_GetPacket(pageHandle,0);
                    if(dPacket != NULL)
                    {
                        for(i=8;i<=37;i++)
                        {
                            pageNumber =  (PageNr)HexAsciiToNat( dPacket+i, 3, &success );
                            if((success) && (pageNumber == pn))
                            {
                                dPacket[i]    = 0x20;
                                dPacket[i+1]  = 0x20;
                                dPacket[i+2]  = 0x20;
                            }
                        }
                    }

                    if(dec_iPresent())
                    {
                        for (i = 1; i < 24; i++)
                        {
                            dPacket = (Nat8 *)acc_GetPacket(pageHandle, (PacketNumber)i);
                            if(dPacket != NULL)
                            {
                                dec_DecodeOddParity(dPacket, dPacket, old, 40);
                            }
                        }
                    }

                    /* enable txplf display components CR 703 */
                    dsenb_Enable();
                    /* to remove the page no at top */
                    if ( mainWindowId != NULL )
                    {
                        DeleteMainWindow( mainWindowId );
                        mainWindowId = NULL;
                    }

                    mainWindowId = CreateMainWindow(div_AciDispStartRow,div_AciDispStartCol,div_AciDispEndRow,div_AciDispEndCol);

                    cnv_ConfInit(&pcs);
                    cnv_SetConfPageHandle(&pcs,pageHandle); 

                    cnv_SetConfSupRow24(&pcs, FALSE);
                    cnv_SetConfSupHeader(&pcs, FALSE);
                    cnv_SetConfSupPicture(&pcs, FALSE);
                    cnv_SetConfSupSidePanels(&pcs, FALSE);
                    cnv_SetConfSupRowAttribs(&pcs, FALSE);

                    cnv_SetRollingHeader((int)cnv_TRH_HOLD, MAG_ANY);
                    cnv_SetRollingTime( cnv_TRT_ROL );

                    cnv_SetConfPresentation(&pcs,cnv_LEVEL_10);
                    cnv_SetConfWindowId(&pcs,mainWindowId);
                    cnv_ConfigureTextPageConversion(&pcs);
                    cnv_StartTextPageConversion(TRUE);
                    ConfigureOn = TRUE;
                }
                else
                {
                    ASSERT(!"Invalid page to be displayed");
                }
            }
            else
            {
                ASSERT(!"ACI page handle invalid");
            }
        }
        else
        {
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
        UNUSED(pcs);
    }
	#endif
}


/****************************************************************************
 * Function name     : acidec_SetCursor
 * Description       : sets cursor at given location
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_SetCursor( Nat8 item)
{
    if(Initialised)
    {
        if(acinv_iPresent())
        {
            if(item < multiPackageItems)
            {
                ASSERT((mtpRow[item] >= acinv_MinRow) && (mtpRow[item] <= acinv_MaxRow));
                acinv_SetCursor(mtpRow[item]);
            }
            else
            {
                ASSERT(!"cursor position not correct");
            }
        }
        else
        {
            ASSERT(!"Aci display not supported");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_RemoveCursor
 * Description       : removes cursor from given location
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_RemoveCursor( void )
{
    if(Initialised)
    {
        if(acinv_iPresent())
        {
            acinv_SetCursor(acinv_NoRow);
        }
        else
        {
            ASSERT(!"Aci display not supported");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_RemoveACIPage
 * Description       : removes ACI page from display
 ****************************************************************************/
void CHsvAciDecode_Priv::acidec_RemoveACIPage( PageNr pn)
{
    UNUSED(pn);
    if(Initialised)
    {
        if(InterfacesConnected)
        {        
            acidec_RemoveCursor();
            cnv_TerminateTextPageConversion();
			tspah2__mode2_SetMode( 6 );
        }
        else
        {            
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}

/****************************************************************************
 * Function name     : acidec_GetNoOfMultiPackageItems
 * Description       : gets no of multi package items in multi page
 ****************************************************************************/
Nat8 CHsvAciDecode_Priv::acidec_GetNoOfMultipackageItems( void)
{
    Nat8 returnVal = 0;
    ASSERT(Initialised);
    if(Initialised)
    {
        returnVal = multiPackageItems;
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
    return(returnVal);
}

/* Static functions */

/****************************************************************************
 * Function name     : PageReceivedHandler
 * Description       : handler function to handle when ACI page is received
 ****************************************************************************/
void CHsvAciDecode_Priv::PageReceivedHandler(int tag, PageNr page,Subcode subcode,Bool arvd_drop,Nat16 ctrlbits)
{
    UNUSED(ctrlbits);     
    UNUSED(tag);
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);
    if(Initialised)
	{
    
					TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);
        if(InterfacesConnected)
        {
						TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);
            if(arvd_drop)
            {
							TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);
                currentReceivedPageSubcode = subcode;
                pageHandle = acc_OpenPageForRead(page,subcode);
                req_UnRequestPage(page,SC_ANY,PageReceivedHandler2);

				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d pageHandle %d",__FUNCTION__,__LINE__,pageHandle);
                pmp_PmpSend( pumpDecodePage, page, subcode ); 
            }
        }
        else
        {         
	        TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);		
            ASSERT(!"Aci optional interface not connected");
        }
    }
    else
    {
        ASSERT(!"Aci Power not initialised");
    }
}


void CHsvAciDecode_Priv::RequestPageHandler(int system, Nat32 key)
{
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d currentRequestedPage = %d",__FUNCTION__,__LINE__,currentRequestedPage);		

	req_RequestPage(currentRequestedPage,(Subcode)SC_ANY,PageReceivedHandler2,0);
	
}
/****************************************************************************
 * Function name     : DecodePageHandler
 * Description       : handler function to handle decoding of ACI page
 ****************************************************************************/
void CHsvAciDecode_Priv::DecodePageHandler(int system, Nat32 key)
{
    PageNr      page;
    Bool        success = FALSE;
    Nat8*       old;

    page = (PageNr)system;

    ASSERT(Initialised);
    ASSERT(currentRequestedPage == page);
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);
    if(InterfacesConnected)
    {
        acidec_IsAciPresent();
        old = (Nat8 *)FourtySpaces;

        if(acidecN_iPresent())
        {
            acidecN_OnReceivedPage();
        }

        if (NOHND != pageHandle)
        {
            dPacket = (Nat8 *)acc_GetPacket(pageHandle,PACKET_1);
            if(dPacket != NULL)
            {
                if(dec_iPresent())
                {
                    dec_DecodeOddParity(dPacket, pktptr, old,40);
                }
                else
                {
                    CopyPktString(dPacket, pktptr,40);
                }

                if (  ( pktptr[0] == CONCEAL_CHAR)
                        && ( pktptr[1] == 0x2F )        /* / */
                        && (  ( pktptr[3] == 0x49 )   /* Version I */
                            || ( pktptr[3] == 0x64 )   /* Version d */
                            || ( pktptr[3] == 0x73 )   /* Version s */
                            || ( pktptr[3] == 0x38 )   /* Version 8 */
                            || ( pktptr[3] == 0x2F )   /* Version / */
                           )
                        && (  ( pktptr[4] == 0x73 )   /* Coding Type s */
                            || ( pktptr[4] == 0x38 )   /* Coding Type 8 */
                            || ( pktptr[4] == 0x2F )   /* Coding Type / */
                            || ( pktptr[4] == 0x50 )   /* Coding Type P */
                           )
                   )
                {   
                    FindNetworkInfo();
					for(int i = 1;i <=10;i++)
						TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d   pktptr[%d] = %d",__FUNCTION__,__LINE__,i,pktptr[i]);
         
                    if (network != AciNetworkInvalid)
                    {   
						TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d  network is %d ",__FUNCTION__,__LINE__,network);
                        GetModeInfo();
                        if (mode != InvalidMode)
                        {
							TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d  mode is %d ",__FUNCTION__,__LINE__,mode);
                            GetLanguageInfo();
                            if (language != AciLanguageInvalid)
                            {
								TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d  language is %d ",__FUNCTION__,__LINE__,language);
                                success = TRUE;
								TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d  aciDecodeOn is %d ",__FUNCTION__,__LINE__,aciDecodeOn);								
                                if (aciDecodeOn)
                                {
									TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d  acidecN_iPresent is %d ",__FUNCTION__,__LINE__,acidecN_iPresent());																	
                                    if(acidecN_iPresent())
                                    {
                                        headerDecoded = TRUE;
								TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d   ",__FUNCTION__,__LINE__);								

                                        acidecN_OnHeaderDecoded();
                                    }
                                }
                            }
                        }
                    } 
                }
            }
        }    
        
		TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec:%s  %d",__FUNCTION__,__LINE__);		
		if ( !success )
        {
            network = AciNetworkInvalid;
            mode    = InvalidMode;
            ResetVariables();
            currentState = acidec_StateFail;
            aciDecodeOn = FALSE;

            if(acidecN_iPresent())
            {
                acidecN_OnDecodeFailure();
            }
        }
    }
    else
    {     
		TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec FAIL: %s %d",__FUNCTION__,__LINE__);	
        ASSERT(!"Aci optional interface not connected");
    }
    UNUSED(key);

}


/****************************************************************************
 * Function name     : AciSingleDecode
 * Description       : handler function to handle decoding of single ACI page
 ****************************************************************************/
void CHsvAciDecode_Priv::AciSingleDecode(void)
{
    Bool        success= FALSE;
    Nat8        acirow = 2;
    Nat8*       old;
	int ix =0;

    old = (Nat8 *)FourtySpaces;
	presetCount =0;

    if(InterfacesConnected)
    {

        do
        {       
            dPacket = (Nat8 *)acc_GetPacket(pageHandle,acirow);
            if(dPacket != NULL)
            {
                if(dec_iPresent())
                {
                    dec_DecodeOddParity(dPacket, pktptr, old,40);
                }
                else
                {
                    CopyPktString(dPacket, pktptr,40);
                }
                AciDecodePreset(pktptr+0);
                AciDecodePreset(pktptr+19);
            }
            acirow++;
        }while ( (pktptr[0] != CONCEAL_CHAR) && (acirow<24) );

        if(pktptr[0] == CONCEAL_CHAR)
        {
			TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);
            extensionPageNumber = (PageNr)HexAsciiToNat( pktptr+ 5 , 3 , &success );
			TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d extensionPageNumber = %d success = %d",__FUNCTION__,__LINE__,extensionPageNumber,success);
            if(extensionPageNumber == 0xfff)
            {
                extensionPageNumber = INVALID_PAGENR;
            }
        }
        else
        {
			TraceDebug(m,"Hsvprins: Svpaci: %sHsvacidec %s %d ",__FUNCTION__,__LINE__);
            success = FALSE;
        }


        if(success)
        {
					TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

            if(extensionPageNumber != INVALID_PAGENR)
            {
						TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

                if(!CheckIfReservedPage(extensionPageNumber))
                {
					TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);
                    extensionPageNumber = INVALID_PAGENR;
                }
            }
        }
        if(!success)
        {
            extensionPageNumber = INVALID_PAGENR;
            ResetVariables();
            currentState = acidec_StateFail;
            aciDecodeOn = FALSE;
			TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

            if(acidecN_iPresent())
            {
                acidecN_OnDecodeFailure();
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);
            }
        }
        else
        {
					TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

            if(extensionPageNumber != INVALID_PAGENR)
            {
                SuggestPage(extensionPageNumber);
							TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

            }
            currentState = acidec_StateSuccess;
            aciDecodeOn = FALSE;
            if (NOHND != pageHandle)
            {
                acc_ClosePage(pageHandle);
                pageHandle = NOHND;
							TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

            }

            if(acidecN_iPresent())
            {
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d mode =%d  presetCount %d",__FUNCTION__,__LINE__,mode,presetCount);
				
				
                acidecN_OnDecodeSuccessful();
            }
        }
    }
}

/****************************************************************************
 * Function name     : AciMultiDecode
 * Description       : handler function to handle decoding of multi ACI page
 ****************************************************************************/
void CHsvAciDecode_Priv::AciMultiDecode(void)
{
    Nat8        i;
    Nat8        count = 0;
    Bool        success = FALSE;
    PageNr      pageNumber;
    Nat8*       old;

    resetMultiPageInfo();

    old = (Nat8 *)FourtySpaces;
    mtpCurrentRow = 2;
    mtpCurrentCount = 0;

    if(InterfacesConnected)
    {

        for(i = 2; i < (MAX_PRESETROWS_PER_PAGE+3); i++)
        {
            mtpCurrentRow = i;
            dPacket = (Nat8 *)acc_GetPacket(pageHandle,mtpCurrentRow);
            if(dPacket != NULL)
            {
                if(dec_iPresent())
                {
                    dec_DecodeOddParity(dPacket, pktptr, old,40);
                }
                else
                {
                    CopyPktString(dPacket, pktptr,40);
                }
                if( pktptr[0] != CONCEAL_CHAR )
                {
                    if(DecodeMtpPage(pktptr,dPacket))
                    {
                        count++;
                    }
                    else
                    {
                        mtpArray[count].teletextPresent = FALSE;
                        mtpArray[count].carrierPresent = FALSE;
                        mtpArray[count].freqLabel = INVALID_FREQUENCY;
                        mtpArray[count].pageNo = INVALID_PAGENR;
                        mtpArray[count].serviceLabel[0] = '\0';
                    }
                }
                else
                {
                    if( (pktptr[5] == 0x46) &&
                            (pktptr[6] == 0x46) &&
                            (pktptr[7] == 0x46) )
                    {
                        MtpDefaultPage = INVALID_PAGENR;
                        multiPackageItems = count;
                        if(multiPackageItems )
                        {
                            success = TRUE;
                        }
                    }
                    else
                    {
                        pageNumber = (PageNr)HexAsciiToNat( pktptr+ 5 , 3 , &success );

                        if(success)
                        {
                            if(CheckIfReservedPage(pageNumber))
                            {
                                MtpDefaultPage = pageNumber;
                                SuggestPage(pageNumber);
                            }
                            else
                            {

                                MtpDefaultPage = INVALID_PAGENR;
                            }
                            multiPackageItems = count;
                        }
                    }
                    break;
                }
            }
        }
        if(success)
        {
            currentState = acidec_StateSuccess;
            aciDecodeOn = FALSE;

            if (NOHND != pageHandle)
            {
                acc_ClosePage(pageHandle);
                pageHandle = NOHND;
            }

            if(acidecN_iPresent())
            {
                acidecN_OnDecodeSuccessful();
            }
        }
        else
        {
            ResetVariables();
            currentState = acidec_StateFail;
            aciDecodeOn = FALSE;

            if(acidecN_iPresent())
            {
                acidecN_OnDecodeFailure();
            }
        }
    }
    else
    {            
        ASSERT(!"Aci optional interface not connected");
    }

}


/****************************************************************************
 * Function name     : ResetVariables
 * Description       : clears static variables related to page decoding
 ****************************************************************************/
void CHsvAciDecode_Priv::ResetVariables()
{
    int         i;
	TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec: %s %d ",__FUNCTION__,__LINE__);
    if(InterfacesConnected)
    { 
        currentRequestedPage = INVALID_PAGENR;
        for(i = 0; i <MAX_LANGUAGEPAGES_INSYSTEMROW ; i++)
        {
            aciLanguageArray[i].language =  AciLanguageInvalid;
            aciLanguageArray[i].pageNo   =  INVALID_PAGENR ;
        }
        for(i=0 ; i <MAX_FIXED_SINGLEPRESET_PER_PAGE ; i++)
        {
            presetSingle[i].presetNo  = (Nat8)INVALID_PRESET;
            presetSingle[i].frequency = INVALID_FREQUENCY;
            presetSingle[i].channelName[0]= '\0';
            presetSingle[i].aciSystem = (Nat8)AciSystemInvalid;
            presetSingle[i].pageNo    = INVALID_PAGENR;
        }

        if (NOHND != pageHandle)
        {
            acc_ClosePage(pageHandle);
            pageHandle = NOHND;
        }

        network = AciNetworkInvalid;
        broadcaster = AciBroadcasterInvalid;
        mode = InvalidMode;
        presetCount = 0;


        aciDecodeOn = FALSE;
        language = AciLanguageInvalid;

        extensionPageNumber = INVALID_PAGENR;
        presetCount = 0;
        headerDecoded = FALSE;
        currentReceivedPageSubcode = 0;
    }
    else
    {            
        ASSERT(!"Aci optional interface not connected");
    }
}

/****************************************************************************
 * Function name     : resetMultiPageInfo
 * Description       : clears static variables related to page decoding
 ****************************************************************************/
void CHsvAciDecode_Priv::resetMultiPageInfo( void )
{
    int i;

    for(i=0 ; i <MAX_PRESETROWS_PER_PAGE ; i++)
    {

        mtpArray[i].pageNo          = INVALID_PAGENR;
        mtpArray[i].freqLabel       = INVALID_FREQUENCY;
        mtpArray[i].serviceLabel[0] = '\0';
        mtpArray[i].carrierPresent  = FALSE;
        mtpArray[i].teletextPresent  = FALSE;

        mtpRow[i] = 0;
    }
    multiPackageItems = 0;
    MtpDefaultPage = INVALID_PAGENR;
}

/****************************************************************************
 * Function name     : CreateMainWindow
 * Description       : creates main window to display ACI page
 ****************************************************************************/
TWindowId CHsvAciDecode_Priv::CreateMainWindow( Nat8 topLeftRow, Nat8 topLeftColumn, Nat8 bottomRightRow, Nat8 bottomRightColumn )
{
    TWindowId   winId;
    Nat8        row;
    Bool        mode_40_or_56 = TRUE;
    /* Assert Validation */
    ASSERT( (topLeftColumn) <= TXTCOLUMNMAX );
    ASSERT( (bottomRightColumn) <= TXTCOLUMNMAX );

    if(Initialised)
    {
        if(InterfacesConnected)
        {
            /* The display mode ( either display 40, 56 or 82 characters ) is set
               if there is a change in the display mode */

            winId =mainWindowId;
            if ( winId != NULL )
            {
                /* Window exists. Close the window */
                DeleteMainWindow( winId );
                mainWindowId = NULL;
            }
            /* Window not present create new window */
            mainWindowId = (TWindowId)dsdrv_OpenWindow (1,topLeftRow,topLeftColumn,bottomRightRow,bottomRightColumn);
	    TraceDebug(m,"Hsvprins:  open_window: %s %d dsdrv_BodyPad = %d",__FUNCTION__,__LINE__,dsdrv_BodyPad);

            ASSERT ( mainWindowId != NULL );
            txtMainWindow = TRUE;

            /* The window is cleared with the TextPageColor */
            dsdrv_ClearWindow( mainWindowId, TX_COLOUR_BLACK /*TxtPageColor*/ );  

            /* The Row height is set to 10 scan lines for UTV and 9 for FTV and double height is set to FALSE */

            dsdrv_SetRowsDoubleHeight( (int)topLeftRow, (Nat8)( bottomRightRow ), FALSE );

            /* Sets display of each row for the T0 plane */
            for ( row = 0; row <= bottomRightRow ; row++ )
            {

                dsdrv_SetRowDisplayEnable( row, TRUE, mode_40_or_56 );
                dsdrv_SetRowBoxEnable( row, TRUE, mode_40_or_56 );        
            }

            for ( row = 0; row <= 27; row++ )
            {
                dsdrv_SetRowForeAndBackgroundClutSelection( row, TRUE, TRUE, mode_40_or_56 );
                dsdrv_SetScreenRowColour( row, TX_COLOUR_BLACK, mode_40_or_56 );
            }

            dsdrv_SetScreenTopBottomColour( TX_COLOUR_BLACK, FALSE, mode_40_or_56 );
            dsdrv_SetScreenTopBottomColour( TX_COLOUR_BLACK, TRUE, mode_40_or_56 );

        } 
        else
        {            
            ASSERT(!"Aci optional interface not connected");
        }        
    }
    else
    {
        UNUSED(topLeftRow);             /* to remove 'unused' warning in compiler */
        UNUSED(topLeftColumn);          /* to remove 'unused' warning in compiler */
        UNUSED(bottomRightRow);         /* to remove 'unused' warning in compiler */
        UNUSED(bottomRightColumn);      /* to remove 'unused' warning in compiler */
    }
    return( mainWindowId );  
}


/****************************************************************************
 * Function name     : DeletMainWindow
 * Description       : deletes main window
 ****************************************************************************/
void CHsvAciDecode_Priv::DeleteMainWindow( TWindowId winId )
{
    if(dsdrv_iPresent())
    {
        if ( txtMainWindow && ( winId != NULL ) )
        {
            dsdrv_ClearWindow( winId, TX_COLOUR_TRANSPARENT); 
            dsdrv_CloseWindow( winId );
            txtMainWindow = FALSE;
            /*winId = NULL;*/
        }
    }
    else
    {
        ASSERT(!"Aci optional interface not connected");
    }
}

/****************************************************************************
 * Function name     : decodeMtpPage
 * Description       : decodes a multi page
 ****************************************************************************/
Bool CHsvAciDecode_Priv::DecodeMtpPage( Nat8* txtInfo, Nat8* dPacketx )
{
    Bool        success = FALSE;

    PageNr      pageNumber;
    Nat32       freq;
    Nat8        refString[5] = "\x3d\x3d\x3d\x00";//blocking QAC warnnings
    Nat8        refTeletextString[5] = "\x25\x25\x25\x00";//blocking QAC warnnings
	TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);

    success = FALSE;

    mtpArray[mtpCurrentCount].pageNo = INVALID_PAGENR ;
    mtpArray[mtpCurrentCount].freqLabel = INVALID_FREQUENCY;

    /* Get extensionpageNumber */
    pageNumber =  (PageNr)HexAsciiToNat( txtInfo+27, 3, &success );

    if ( success )
    {
		TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);

        success = CheckIfReservedPage(pageNumber);

        mtpArray[mtpCurrentCount].pageNo = pageNumber;

        if(success)
        {
			TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);

            /* Get unique Frequency */
            if( (txtInfo[30] == 0x46) &&
                    (txtInfo[31] == 0x46) &&
                    (txtInfo[32] == 0x46) &&
                    (txtInfo[33] == 0x46) &&
                    (txtInfo[34] == 0x46) )
            {
                mtpArray[mtpCurrentCount].freqLabel = INVALID_FREQUENCY;
			    TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);
            }
            else
            {
				TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);

                freq = DecAsciiToNat( txtInfo+30, 5, &success );
                if(success)
                {
					TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d freq=%d",__FUNCTION__,__LINE__,freq);
                    mtpArray[mtpCurrentCount].freqLabel = freq;
                }
            }

            if( success )
            { 
                /* Get unique Txt Label */
                txtInfo[31] = '\0';

                /* remove item nos from original page memory */
                dPacketx[8] = 0x20;
                dPacketx[9] = 0x20;
	            TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);

                str_strncpy( (char *)mtpArray[mtpCurrentCount].serviceLabel , (char *)txtInfo+35 ,3);
                if ( ! str_strncmp( (char *)txtInfo+35, (char *)refString ,3) ) /* === */
                {
                    mtpArray[mtpCurrentCount].carrierPresent = FALSE;
                }
                else
                {
                    mtpArray[mtpCurrentCount].carrierPresent = TRUE;
                }

                if ( ! str_strncmp( (char *)txtInfo+35, (char *)refTeletextString ,3) ) /* %%% */
                {
                    mtpArray[mtpCurrentCount].teletextPresent = FALSE;
                }
                else
                {
                    mtpArray[mtpCurrentCount].teletextPresent = TRUE;
                }

                mtpRow[mtpCurrentCount] = mtpCurrentRow;
                mtpCurrentCount++;
            }
            else
            {
				TraceDebug(m,"Hsvprins:  Hsvacidec: %s %d ",__FUNCTION__,__LINE__);
                mtpArray[mtpCurrentCount].freqLabel = INVALID_FREQUENCY;
                success = FALSE;
            }
        }
    }
    return success;
}

/****************************************************************************
 * Function name     : AciDecodePreset
 * Description       : decodes a preset at a row in a single type page
 ****************************************************************************/
void CHsvAciDecode_Priv::AciDecodePreset(Nat8* txtinfo )
{
    Nat32       freq = 0;
    Nat16       pr;
    PageNr      pn;
    Bool        success=TRUE;

    /* Get presetnumber */
    pr = (Nat16)DecAsciiToNat( txtinfo, 3, &success );
	TraceDebug(m,"Hsvprins: Svpaci:  pr %x success %d",pr,success);
    if(!success)
    {
        presetSingle[presetCount].presetNo = (Nat8)INVALID_PRESET;
    }
    else
    {
        /* If the preset no is EEE then the preset in empty */
        if((pr == 0xEEE) || (pr == 0xFFF)) 
        {
            presetSingle[presetCount].presetNo = (Nat8)INVALID_PRESET;
            success = FALSE;
        }
        else
        {
            presetSingle[presetCount].presetNo = (Nat8)pr;
        }
    }
	TraceDebug(m,"Hsvprins: Svpaci: pr %x success %d",pr,success);
    if( success )
    {
        /* Get Frequency */
        if (IsDigit(txtinfo[3]))
        {
            freq =  DecAsciiToNat( txtinfo + 3, 5 , &success );
        }
        else
        {
            freq = HexAsciiToNat( txtinfo + 3, 1, &success ) * 10000 ;
            if(success)
            {
                freq = freq + DecAsciiToNat( txtinfo + 4, 4 , &success );
            }
        }
        if(!success)
        {
            presetSingle[presetCount].frequency = INVALID_FREQUENCY;
        }
        else
        {
            presetSingle[presetCount].frequency = freq;
        }
    }
	TraceDebug(m,"Hsvprins: Svpaci: freq %d success %d presetCount %d",freq,success,presetCount);
    if( success )
    {
        /* Get Name */
        str_strncpy( (char *)presetSingle[presetCount].channelName, (char *)txtinfo + 8, 5 );
        presetSingle[presetCount].channelName[5] = '\0';
		TraceDebug(m,"Hsvprins: channelName %s",(char *)presetSingle[presetCount].channelName);
    }

    if( success )
    {
        /* Get pageNo */

        /* Get system */
        if( txtinfo[17] != 0x49 ) /* I */
        {
            success = FALSE;
			TraceDebug(m,"Hsvprins: Svpaci: line %d success %d",__LINE__,success);
        }
        else
        {
            pn = (PageNr)HexAsciiToNat( txtinfo + 14, 3 , &success );
			TraceDebug(m,"Hsvprins: Svpaci: line %d success %d",__LINE__,success);

            if( (!CheckIfReservedPage(pn)) || (pn == 0xfff) || (!success))
            {
                presetSingle[presetCount].pageNo = INVALID_PAGENR;
                success = TRUE;
            }
            else
            {
                presetSingle[presetCount].pageNo = pn;
            }
		TraceDebug(m,"Hsvprins: Svpaci: line %d success %d",__LINE__,success);
            switch ( txtinfo[18] )
            {
                case 0x49 /* I */ :                     
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemPalSecamBg;
                    break;

                case 0x64 /* d */ :
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemSecamL;
                    break;

                case 0x73 /* s */ :
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemPalM;
                    break;

                case 0x38 /* 8 */ :
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemNtscM;
                    break;

                case 0x2f /* / */ :
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemPalI;
                    break;

                case 0x50 /* P */ :
                    presetSingle[presetCount].aciSystem = (Nat8)AciSystemSecamDk;
                    break;

                default :
				TraceDebug(m,"Hsvprins: Svpaci: line %d success %d",__LINE__,success);
                    success = FALSE;
                    break;
            }
        }
    }

	TraceDebug(m,"Hsvprins: Svpaci: presetCount %x success %d",presetCount,success);
    if(success)
    {
        presetCount ++;
    }
    else
    {
        presetSingle[presetCount].presetNo  = (Nat8)INVALID_PRESET;
        presetSingle[presetCount].frequency = INVALID_FREQUENCY;
        presetSingle[presetCount].channelName[0]= '\0';
        presetSingle[presetCount].aciSystem = (Nat8)AciSystemInvalid;
        presetSingle[presetCount].pageNo    = INVALID_PAGENR;
    }
}

/****************************************************************************
 * Function name     : FindNetworkInfo
 * Description       : decode network info
 ****************************************************************************/
void CHsvAciDecode_Priv::FindNetworkInfo(void)
{
    switch(pktptr[2])
    {
        case 0x49 : 
            network = AciNetworkCable; 
            break;
        case 0x64 : 
            network = AciNetworkCable; 
            break;
        case 0x73 : 
            network = AciNetworkSatellite; 
            break;
        case 0x38 : 
            network = AciNetworkSatellite; 
            break; 
        case 0x2F : 
            network = AciNetworkTerrestrial; 
            break;
        case 0x50 : 
            network = AciNetworkTerrestrial;
            break;
        default   : 
            network = AciNetworkInvalid ; 
            break;
    }
}

/****************************************************************************
 * Function name     : GetModeInfo
 * Description       : decode mode info
 ****************************************************************************/
void CHsvAciDecode_Priv::GetModeInfo(void)
{
    if ((pktptr[5] == 0x73) || (pktptr[5] == 0x38) || (pktptr[5] == 0x2F))
    {
        mode = SinglePackageMode;
    }
    else
    {
        if((pktptr[5] == 0x49) || (pktptr[5] == 0x64) || (pktptr[5] == 0x50))
        {
            mode = MultiPackageMode;
        }
        else
        {
            mode = InvalidMode;
        }
    }
}

/****************************************************************************
 * Function name     : GetLanguageInfo
 * Description       : decode language info
 ****************************************************************************/
void CHsvAciDecode_Priv::GetLanguageInfo(void)
{
    Bool        success = 0;
    Nat32       languagecode;
    int         arrayindex;
    int         index;
    PageNr      pagenumber;

    languagecode  = HexAsciiToNat( pktptr+6,2,&success );
    if (success)
    {
        language = ConvertLanguageCode ( (Nat8) languagecode); 
    }
    aciLanguageArray[0].language = language;
    aciLanguageArray[0].pageNo = currentRequestedPage;

    arrayindex = 1;
    for( index = 1 ; index < MAX_LANGUAGEPAGES_INSYSTEMROW ; index++ )
    {
        /* Get extention languages and pages */
        languagecode = HexAsciiToNat (pktptr + 8 + ( (index-1) * 5) ,2, &success );
        if ( ( success ) && ( languagecode != 0xFF ) )
        {
            aciLanguageArray[arrayindex].language = (HsvAciLanguage)ConvertLanguageCode( (Nat8)languagecode );
            pagenumber = (PageNr)HexAsciiToNat( pktptr+ 10 + ( (index -1) *5) , 3 , &success );

            if(success)
            {
                success = CheckIfReservedPage(pagenumber);
            }
            if(!success)
            {
                /*pagenumber = INVALID_PAGENR;*/
                aciLanguageArray[arrayindex].language = AciLanguageInvalid;
            }
            else
            {
                aciLanguageArray[arrayindex].pageNo =  pagenumber;
                arrayindex++;
            }
        } 
    }
}

/****************************************************************************
 * Function name     : ConvertLanguageCode
 * Description       : gets aci language 
 ****************************************************************************/
HsvAciLanguage CHsvAciDecode_Priv::ConvertLanguageCode( Nat8 code )
{
    HsvAciLanguage lang;
    switch(code)
    {
        case 0x32 : 
            lang = AciLanguageCzech; 
            break;
        case 0x29 : 
            lang = AciLanguageDanish; 
            break;
        case 0x48 : 
            lang = AciLanguageDutch; 
            break;
        case 0x2C : 
            lang = AciLanguageEnglish; 
            break;
        case 0x26 : 
            lang = AciLanguageFinnish; 
            break;
        case 0x2F : 
            lang = AciLanguageFrench; 
            break;
        case 0x11 : 
            lang = AciLanguageGerman; 
            break;
        case 0x21 : 
            lang = AciLanguageGreek; 
            break;
        case 0x1B : 
            lang = AciLanguageHungarian; 
            break;
        case 0x15 : 
            lang = AciLanguageItalian; 
            break;
        case 0x43 : 
            lang = AciLanguageTurkish; 
            break;
        case 0x3F : 
            lang = AciLanguageNorwegian; 
            break;
        case 0x33 : 
            lang = AciLanguagePolish; 
            break;
        case 0x58 : 
            lang = AciLanguagePortuguese; 
            break;
        case 0x2E : 
            lang = AciLanguageRomanian; 
            break;
        case 0x47 : 
            lang = AciLanguageRussian; 
            break;
        case 0x3E : 
            lang = AciLanguageSpanish; 
            break;
        case 0x4E : 
            lang = AciLanguageSwedish; 
            break;
        default   : 
            lang = AciLanguageInvalid;
            break;
    }
    return (lang);
}


/****************************************************************************
 * Function name     : SuggestPage
 * Description       : suggest a page for acquisition.
 ****************************************************************************/
void CHsvAciDecode_Priv::SuggestPage(PageNr pn)
{
    if( div_PrefetchAciPage )
    {        
        if( req_iPresent() )
        {        
            req_SuggestPage(pn);
        }
    }
    else
    {
        UNUSED(pn);             /* to remove 'unused' warning in compiler */
    }
}

/****************************************************************************
 * Function name     : DecAsciiToNat
 * Description       : convert ascii decimal to Nat32
 ****************************************************************************/
Nat32 CHsvAciDecode_Priv::DecAsciiToNat( Nat8* text, Nat8 number_of_digits, Bool *success )
{
    Nat8        temptext[10];
    Nat8        index;
    Nat32       result;

    ASSERT(number_of_digits < 10);
    str_strncpy( (char *)temptext, (char *)text, number_of_digits );
    temptext[number_of_digits]='\0';

    index = 0;
    result = 0;
    do
    {
        result = result * 10;
        *success = ( IsDigit( temptext[index] ) != 0 );
        if( *success )
        {
            result = result + ( temptext[index] - 0x30 );
        }
        index++;
    } while( ( index < number_of_digits ) && (*success) );

    if ( !(*success) )
    {
        result = 0;
    }

    return (result);
}

/****************************************************************************
 * Function name     : HexAsciiToNat
 * Description       : convert ascii hex to Nat32
 ****************************************************************************/
Nat32 CHsvAciDecode_Priv::HexAsciiToNat( Nat8* text,Nat8 numberofdigits,Bool *success )
{
    Nat8        temptext[9];
    Nat8        index;
    Nat32       result = 0;

    str_strncpy( (char *)temptext, (char *)text, numberofdigits );
    temptext[numberofdigits]='\0';

    index = 0;
    do
    {
        result = result << 4;
        *success = ( IsXDigit( temptext[index] ) != 0 );
        if ( *success )
        {
            if ( (0x30 <= temptext[index]) && (temptext[index] <= 0x39) )
            {
                result = result + ( temptext[index] - 0x30 );
            }
            else
            {
                result = result + ( temptext[index] - 0x41 + 0xA );
            }
        }
        index++;
    } while(  ( index < numberofdigits ) && ( *success ) );

    if ( !(*success) )
    {
        result = 0;
    }

    return (result);
}

/****************************************************************************
 * Function name     : IsXDigit
 * Description       : to check whether a character is hex digit
 ****************************************************************************/
Bool CHsvAciDecode_Priv::IsXDigit(Nat8 x)
{
    Bool returnVal;
    if ( ((x >=0x30) && (x <= 0x39)) || ((x >= 0x41) && (x <= 0x46)))
    {
        returnVal = TRUE;
    }
    else
    {
        returnVal = FALSE;
    }
    return(returnVal);
}

/****************************************************************************
 * Function name     : IsDigit
 * Description       : to check whether a character is numeric
 ****************************************************************************/
Bool CHsvAciDecode_Priv::IsDigit(Nat8 x)
{
    Bool returnVal;
    if((x >=0x30) && (x <= 0x39)) 
    {
        returnVal = TRUE;
    }
    else
    {
        returnVal = FALSE;
    }
    return returnVal;
}

/****************************************************************************
 * Function name     : CheckIfReservedPage
 * Description       : to check whether a page number is a reserved page 
 ****************************************************************************/
Bool CHsvAciDecode_Priv::CheckIfReservedPage(PageNr pn)
{
    Bool        success = TRUE;
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);
    if ( !((pn >= 0) && (pn <= 0x7FF) ) )
    {
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

        success = FALSE;
    }
    if((pn == 0x1F0) ||  (pn == 0x1F8) ||  (pn == 0x1F9) || (pn == 0x1BE))
    {
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

        success = FALSE;
    }
    if( ((pn&0x0ff) == 0x0FE) || ((pn&0x0ff) == 0xFF) || ((pn&0x0ff) == 0x0FD) )
    {
				TraceDebug(m,"Hsvprins: Svpaci: Hsvacidec %s %d ",__FUNCTION__,__LINE__);

        success = FALSE;
    }
    return success;    
}

void CHsvAciDecode_Priv::CopyPktString( Nat8 *src, Nat8 *dest, int count)
{
    int i;
    for(i=0; i<count; i++)
    {
        dest[i] = src[i];
    }
}

/****************************************************************************
 * Notification functions
 ****************************************************************************/
void CHsvAciDecode_Priv::cnvN_OnTxtPageConverted(void)
{
    if(Initialised)
    {
        if(ConfigureOn)
        {
            acidec_SetCursor(0);
        }
    }
}

void CHsvAciDecode_Priv::cnvN_OnTxtPageConversionTerminated(void)
{
    if(Initialised)
    {
        if( ConfigureOn )
        {
            if ( mainWindowId != NULL )
            {
                DeleteMainWindow( mainWindowId );
                mainWindowId = NULL;
            }
            if( dsenb_iPresent() )
            {            
                dsenb_Disable();
            }
            ConfigureOn = FALSE;
        }
    }
}

void CHsvAciDecode_Priv::cnvN_OnTxtTopBottomScreenColour( Bool topbottom, int tbscreencol )
{
    Bool        mode_40_or_56 = TRUE;

    if(Initialised)
    {
        if( ConfigureOn )
        {
            if( dsdrv_iPresent() )
            {
                dsdrv_SetScreenTopBottomColour( tbscreencol , topbottom, mode_40_or_56 );
            }
        }
    }
    else
    {
        UNUSED(tbscreencol);        /* to remove 'unused' warning in compiler */
        UNUSED(topbottom);          /* to remove 'unused' warning in compiler */
    }
}

void CHsvAciDecode_Priv::cnvN_OnTxtPictureOn(void)
{
}

void CHsvAciDecode_Priv::cnvN_OnTxtRow( int row, int row_colour )
{
    Bool        mode_40_or_56 = TRUE;

    if(Initialised)
    {
        if( ConfigureOn )
        {
            if ( dsdrv_iPresent() ) 
            {            
                dsdrv_SetRowDisplayEnable( (Nat8)(row)     , TRUE,       mode_40_or_56 );
                dsdrv_SetScreenRowColour ( (Nat8)( row + 1), row_colour,  mode_40_or_56 );
                dsdrv_SetRowDisplayEnable( (Nat8)( row + 1), FALSE,      mode_40_or_56 ); 
            }
        }
    }
    else
    {
        UNUSED(row_colour);             /* to remove 'unused' warning in compiler */
        UNUSED(row);                    /* to remove 'unused' warning in compiler */
    }
}

void CHsvAciDecode_Priv::cnvN_OnTxtRevealCancel(void)
{

}

void CHsvAciDecode_Priv::cnvN_OnTxtRollingHeaderTerminated(void)
{

}

