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
 *          %name: hsveuins_msysctl.c %
 *       %version: TVG_tv550r4dev1_5 %
 * %date_modified: Wed Nov 21 17:18:35 2007 %
 *    %derived_by: vijayan % 
 */

#include "_hsveuins_msysctl.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_msysctl")



Bool CHsvEuropeInstallation_msysctl_Priv::s__soundMuteOnOff = FALSE;

Bool CHsvEuropeInstallation_msysctl_Priv::MuteStatus = FALSE;



Nat16 CHsvEuropeInstallation_msysctl_Priv::s__unicodestring[div_PresetNameLength];
//[div_PresetNameLength];
/* fixme: This should not be the way ideally */


/***********************************************************************
 *Function   : void instutil_LogError(int Priority, int ErrorId )
 *Description: 
 *Parameters : 
 ************************************************************************/
void CHsvEuropeInstallation_msysctl_Priv::sysctl_BlockDestinations( HsvDestination dest, Bool OnOff )
{   
	/*If Mute status is already set before installation then mute and unmute need not to be done for installation*/
	if(OnOff == TRUE)
	{
		MuteStatus = actl_Get2(actl_ProgramMute,0);
		TraceNotice(m,"%s: %d: MuteStatus : %d", __FUNCTION__,__LINE__,MuteStatus);
	}

	if(MuteStatus == FALSE)
	{
		TraceNotice(m,"%s: %d: Setting MuteStatus : %d", __FUNCTION__,__LINE__,OnOff);
		actl_Set2(actl_ProgramMute,actl_SpeakerOutput,OnOff);
	}
}

int CHsvEuropeInstallation_msysctl_Priv::GetMuteColor(void)
{
    int mute_color = 1;
    switch(div_PgctrlMuteColor)
    {
        case VIDEO_MUTE_BLACK :
            mute_color = vctl_VideoMutePogramBlack;
            break;

        case VIDEO_MUTE_BLUE:
            mute_color = vctl_VideoMuteBlue;
            break;

        case VIDEO_MUTE_GREY:
            mute_color = vctl_VideoMutePogramGrey;
            break;

        default:
            mute_color = vctl_VideoMuteBlue;
            break;
    }
    return(mute_color);   
}

/* This is used by the analog module */
void CHsvEuropeInstallation_msysctl_Priv::sysctl_SetVideoMute(Bool OnOff)
{
    UNUSED(OnOff);
}

void CHsvEuropeInstallation_msysctl_Priv::sysctl_SetAudioMute(Bool OnOff)
{
    if(OnOff != soundMuteOnOff)
    {
        int OnOffSet    =   (TRUE==OnOff)?actl_BoolTrue:actl_BoolFalse;
        actl_Set2(actl_ProgramMute,actl_AllOutput,OnOffSet);
        soundMuteOnOff  =   OnOff;
    }
}

/***********************************************************************
 *Function   : void LogError(int Priority, int ErrorId )
 *Description: 
 *Parameters : 
 ************************************************************************/
void CHsvEuropeInstallation_msysctl_Priv::instutil_LogError( int Priority, int ErrorId )
{
    if(log_SoftErr == Priority)
    {
        PError (ErrorId);
    }
    if( log_iPresent() )
    {
#if 0
		/* ANEESH: REmoving this */
        if( compids_iPresent() )
        {
            /* Add the offset of the installation view component to the error ID */
            log_Error( Priority, ErrorId + compids_hsveuins );
        }
        else
#endif
        {
            /* Component ID for installation is unknown. */
            log_Error( Priority, ErrorId );
        }
    }
}
Nat16* CHsvEuropeInstallation_msysctl_Priv::instutil_AsciiToUnicode( char * str, int length)
{
    int i=0;

    for(i = 0; i < div_PresetNameLength; i++)
    {
        unicodestring[i] = 0;
    }

    for(i = 0; i < length; i++)
    {
        unicodestring[i] = str[i];
    }

    return(unicodestring);
}

void CHsvEuropeInstallation_msysctl_Priv::PError(int ErrorID)
{
    switch(ErrorID)
    {
        case INS_INVALID_TURNON:   
            TraceDebug(m,"LogSoftErr: Function call when Installation is not turned on");
            break;
        case INS_FRONTEND_NOT_INITIALISED:          
            TraceDebug(m,"LogSoftErr: FrontEnd not initialised");
            break;
        case INS_USECASE_SELECTION_FAILED:          
            TraceDebug(m,"LogSoftErr: Usecase Selection failed");
            break;
        case INS_FAILED_TO_GET_CHANTBL_INTERFACE:   
            TraceDebug(m,"LogSoftErr: Failed to get ChanTable interface");
            break;
        case INS_FAILED_TO_GET_DIGDEMOD_INTERFACE:  
            TraceDebug(m,"LogSoftErr: Failed to get DigDemod interface");
            break;
        case INS_FAILED_TO_GET_SIGSTR_INTERFACE:    
            TraceDebug(m,"LogSoftErr: Failed to get SigStr interface");
            break;
        case INS_FAILED_TO_SUBSCRIBE_TO_TUNINGNTF:  
            TraceDebug(m,"LogSoftErr: Failed to get TuningNtf interface");
            break;
        case INS_FAILED_TO_SUBSCRIBE_TO_SIGSTRNTF:  
            TraceDebug(m,"LogSoftErr: Failed to get SigStrNtf interface");
            break;
        case INS_FAILED_TO_SUBSCRIBE_TO_DIGDEMODNTF:
            TraceDebug(m,"LogSoftErr: Failed to get DigDemodNtf interface");
            break;
        case INS_COMMAND_NOT_ALLOWED:               
            TraceDebug(m,"LogSoftErr: Command Not Allowed. Violation of call sequence by client");
            break;
        case INS_INVALID_SWITCH_CASE:               
            TraceDebug(m,"LogSoftErr: Invalid Switch Case");
            break;
        case INS_UNEXPECTED_DELETION:               
            TraceDebug(m,"LogSoftErr: Unexpected deletion of database entry");
            break;
        case INS_UNEXPECTED_CORRUPTION:             
            TraceDebug(m,"LogSoftErr: Unexpected database corruption");
            break;
        case INS_PRESET_TABLE_FULL:                 
            TraceDebug(m,"LogSoftErr: Preset Table Full");
            break;
        case INS_NO_TRANSPORT_STREAM:               
            TraceDebug(m,"LogSoftErr: No Transport Stream found after digital installation");
            break;
        case INS_FAILED_TO_GET_RFAMP_INTERFACE:     
            TraceDebug(m,"LogSoftErr: Failed to get RfAmp Interface");
            break;
        case INS_FAILED_TO_SUBSCRIBE_TO_CHANDECNTF:     
            TraceDebug(m,"LogSoftErr: Failed to get channel decoder Interface");
            break;
        default:
            break;
    }
}

