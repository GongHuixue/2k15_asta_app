/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *    %name: hsvpgdat_mpgdat.c %
 *    %version: TVG_Fusion_31 %
 *    %date_modified: Thu Apr 09 20:03:01 2009 %
 *    %derived_by: lakshminb %
 */

#include "_hsvpgdat_mpgdat.h"

TRACESYMBOL(m, "zap/pgdat/hsvpgdat_mpgdat")

#include<string.h>

#include<pthread.h>
//#include<sys/msg.h>

#include "sqlite3.h"









/* Type definition message structure */




#if MESSAGE_SEND_RECEIVE_SUPPORT


#endif

int CHsvSatProgramData_mpgdat_Priv::s__gmqd;
       /*Message queue descriptior */

















pthread_mutex_t CHsvSatProgramData_mpgdat_Priv::s__pgdatmutex;

int CHsvSatProgramData_mpgdat_Priv::s__mPgdatExtTaskId = 0;

PgdatLoadSaveMsg CHsvSatProgramData_mpgdat_Priv::s__mPgdatMsg;


void CHsvSatProgramData_mpgdat_Priv::ipgdatpow_Init(void)
{
#if 0
    /* Get the message queue for the key */
    gmqd = msgget(PGDAT_MSG_KEY, IPC_CREAT);
    if (gmqd == -1)
    {
        TraceDebug(m,"The message queue identifier failed, func= %s, line = %d", __FUNCTION__, __LINE__);                     
    }


    /* create Pthread for program data functionality, swapping and reorder of channels */
    /* Set the stack size */

#if MESSAGE_SEND_RECEIVE_SUPPORT

    pthread_t pgdatthread;      /* Thread for Program data for swapping and reorder */

    int retvalth;

    retvalth = pthread_create(&pgdatthread, NULL, (void*)mPgdatThread, NULL); 
    if (retvalth)
    {
        TraceDebug(m,"Error: Return code of thread create in pgdat module, error value = %d",retvalth); 
    }

#endif
    /* Create Mutex for program data functionality, swapping and reorder of channels */
    pthread_mutex_init (&pgdatmutex, NULL);     
	mPgdatExtTaskId = tprtk_TaskCreate( "PgdatRunApp",	PGDAT_EXT_TASK_PRIORITY, PGDAT_EXT_TASK_STACK_SIZE, PgdatExternalEventHandler, 1);
#endif
}

void CHsvSatProgramData_mpgdat_Priv::PgdatExternalEventHandler(int param)
{
	Nat32	PgdatExtEvent;
#if 0
	while (1)
	{
		PgdatExtEvent=tprtk_EventReceive( PGDAT_EXT_LOAD|PGDAT_EXT_SAVE, FALSE, tprtk_TimeoutInfinite );
		if (PgdatExtEvent == PGDAT_EXT_LOAD)
		{
			mLoadChannelTableFromMedium(mPgdatMsg.DirectoryPath, mPgdatMsg.medium) ;
		}
		else if (PgdatExtEvent == PGDAT_EXT_SAVE)
		{
			mSaveChannelTableToMedium (mPgdatMsg.DirectoryPath, mPgdatMsg.medium);
		}
	}
#endif
}

void CHsvSatProgramData_mpgdat_Priv::ipgdatpow_TurnOn(void)
{

}
void CHsvSatProgramData_mpgdat_Priv::ipgdatpow_TurnOff(void)
{

}

void CHsvSatProgramData_mpgdat_Priv::pgdat_ClearCurrentTable(void)
{
    ipgdb_ClearTable(ipgdb_GetCurrentTable());
    chmapop_CommitToFlash(ipgdb_GetCurrentTable());
    chmapop_ChannelTableChanged();
}

void CHsvSatProgramData_mpgdat_Priv::pgdat_ClearAllTables(void)
{
    ipgdb_ClearTable(ipgdb_GetCurrentTable());
    chmapop_CommitToFlash(ipgdbconst_Antenna);
    chmapop_CommitToFlash(ipgdbconst_Cable);
//    chmapop_CommitToFlash(ipgdbconst_Satellite);
    chmapop_ChannelTableChanged();
}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat_IsValidChannel(AppApiChannel channel)
{
    Bool ret = FALSE;


    UNUSED(channel);
    return ret;
}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat_IsChannelInstalled(AppApiChannel *channel )
{
    Bool retval = TRUE;
#if 0
    HsvPgdatPresetData preset;    
    AppApiChannel   tmpChannel = *channel;

    /* Check if any channel is installed with this major no */
    channel->Channel.TwoPart.MajorNo = channel->Channel.Digit;
    channel->Channel.TwoPart.MinorNo = 0;
    channel->Ptc = channel->Channel.Digit;
    channel->Type = AppApiAnalog;

    ASSIGN_PRESET_KEYS(&preset, channel);

    retval = ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset);

    if(retval)
    {
        /* Analog channel is installed. Hence copy the channel no. */
        ASSIGN_CHANNEL_FROM_PRESET(&preset, channel);
    }
    if (!retval)
    {
        *channel =  tmpChannel;
    }        
#endif
    return retval; 

}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat_IsAttributeSupported(int attribute)
{
    return mIsAttributeSupported(attribute);
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_GetChannelDataBool(AppApiChannel channel, int dataid, Bool  *value)
{
    FResult ret = err_Ok;

    ret = mGetScalarAttribute(channel, dataid, (Nat32*)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_StoreChannelDataBool(AppApiChannel channel, int dataid, Bool  value)
{
    FResult ret = err_Ok;

    ret = mSetScalarAttribute(channel, dataid, (Nat32)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_GetChannelDataInt(AppApiChannel channel, int dataid, int   *value)
{
    FResult ret = err_Ok;

    ret = mGetScalarAttribute(channel, dataid, (Nat32*)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_StoreChannelDataInt(AppApiChannel channel, int dataid, int   value)
{
    FResult ret = err_Ok;

    ret = mSetScalarAttribute(channel, dataid, (Nat32)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_GetChannelDataNat32(AppApiChannel channel, int dataid, Nat32 *value)
{
    FResult ret = err_Ok;

    ret = mGetScalarAttribute(channel, dataid, (Nat32*)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_StoreChannelDataNat32(AppApiChannel channel, int dataid, Nat32 value)
{
    FResult ret = err_Ok;

    ret = mSetScalarAttribute(channel, dataid, (Nat32)value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_GetChannelDataString(AppApiChannel channel, int dataid, Nat16  *value, int size)
{
    FResult ret = err_Ok;
    if(size > CHANNEL_NAME_SIZE)
    {
        size = CHANNEL_NAME_SIZE;
    }
    if(pgdat_StringChannelName == dataid)
    {
        dataid = pgdat_StringExtChannelName;
    }

#define NO
#define PTR    *
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)

    if((NULL != value) && mIsAttributeSupported(dataid))
    {
        HsvPgdatPresetData preset;

        ASSIGN_PRESET_KEYS(&preset, &channel);

        if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
        {
            if(AppApiAnalog == channel.Type)
            {
                HsvPgdatAnalogData  anadat;

                ASSIGN_ANALOG_KEYS(&anadat, &preset);

                if(ipgdb_GetByKey(CURRENT_ANALOG_TABLE, (Address)&anadat))
                {
                    switch(dataid)
                    {
#define ANALOG_ATTRIB(a_type, ptr, vale, f_type, field, size)       memcpy((a_type ptr)value, (f_type ptr)anadat.field,(size * sizeof(a_type)))                 
#define COMMON_ATTRIB(a_type, ptr, vale, f_type, field, size)       memcpy((a_type ptr)value, (f_type ptr)anadat.field, (size * sizeof(a_type)))
#define DIGITAL_ATTRIB(a_type, ptr, vale, f_type, field, size)
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)       case HsvPgDat##attrib:                                                                              \
                        applic(a_type, ptr, vale, f_type, field, size);     \
                        break;
#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  VECTOR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else if ((AppApiOnePart == channel.Type) || (AppApiTwoPart == channel.Type))
            {
                HsvPgdatDigServiceData  svcdat;

                ASSIGN_DIGSVC_KEYS(&svcdat, &preset);

                if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
                {


                    switch(dataid)
                    {
#define ANALOG_ATTRIB(a_type, ptr, value, f_type, field, size)                        
#define COMMON_ATTRIB(a_type, ptr, value, f_type, field, size)       memcpy((a_type ptr)value, (f_type ptr)svcdat.field, (size * sizeof(a_type)))
#define DIGITAL_ATTRIB(a_type, ptr, value, f_type, field, size)      memcpy((a_type ptr)value, (f_type ptr)svcdat.field, (size * sizeof(a_type)))
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)       case HsvPgDat##attrib:                                  \
                        applic(a_type, ptr, value, f_type, field, size);    \
                        break;
#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  VECTOR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
        }
        else
        {
            ret = err_ChannelNotInstalled;
        }
    }
    else
    {
        ret = err_BadParameter;
    }

#undef  NO
#undef  PTR
#undef  SCALAR_ITEM

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_StoreChannelDataString(AppApiChannel channel, int dataid, Nat16 *value, int size)
{
    FResult ret = err_Ok;

    if(size > CHANNEL_NAME_SIZE)
    {
        size = CHANNEL_NAME_SIZE;
    }
    if(pgdat_StringChannelName == dataid)
    {
    	TraceNotice(m,"%s %d\n",__FUNCTION__,__LINE__);
    	//dataid = pgdat_StringExtChannelName;
    }

#define NO
#define PTR    *
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)

    if((NULL != value) && mIsAttributeSupported(dataid))
    {
        HsvPgdatPresetData preset;

        ASSIGN_PRESET_KEYS(&preset, &channel);

        if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
        {
            if(AppApiAnalog == channel.Type)
            {
                HsvPgdatAnalogData  anadat;

                ASSIGN_ANALOG_KEYS(&anadat, &preset);

                if(ipgdb_GetByKey(CURRENT_ANALOG_TABLE, (Address)&anadat))
                {
                    switch(dataid)
                    {
#define ANALOG_ATTRIB(f_type, ptr, field, a_type, value, size)       memcpy((f_type ptr)anadat.field, (a_type ptr)value, (size * sizeof(f_type)))                       
#define COMMON_ATTRIB(f_type, ptr, field, a_type, value, size)       memcpy((f_type ptr)anadat.field, (a_type ptr)value, (size * sizeof(f_type))); anadat.field[size] = 0;
#define DIGITAL_ATTRIB(f_type, ptr, field, a_type, value, size)
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)       case HsvPgDat##attrib:                                  \
                        applic(f_type, ptr, field, a_type, value, size);    \
                        break;


#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  VECTOR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }

                    if(pgdat_StringExtChannelName == dataid)
                    {
                        TraceNotice(m,"%s %d ChannelName to NULL", __FUNCTION__, __LINE__);
                        anadat.ChannelName[0] = '\0';
                    }

                    ipgdb_Update(CURRENT_ANALOG_TABLE, (Address)&anadat);
                    if(pgdatN_iPresent())
                    {
                        pgdatN_OnChannelUpdated(channel, dataid);       
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else if ((AppApiOnePart == channel.Type) || (AppApiTwoPart == channel.Type))
            {
                HsvPgdatDigServiceData  svcdat;

                ASSIGN_DIGSVC_KEYS(&svcdat, &preset);

                if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
                {

                    switch(dataid)
                    {
#define ANALOG_ATTRIB(f_type, ptr, field, a_type, value, size)                        
#define COMMON_ATTRIB(f_type, ptr, field, a_type, value, size)       memcpy((f_type ptr)svcdat.field, (a_type ptr)value, (size * sizeof(f_type)))
#define DIGITAL_ATTRIB(f_type, ptr, field, a_type, value, size)      memcpy((f_type ptr)svcdat.field, (a_type ptr)value, (size * sizeof(f_type)))

#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)       case HsvPgDat##attrib:                                  \
                        applic(f_type, ptr, field, a_type, value, size);    \
                        svcdat.field[size] = 0;                         \
                        break;


#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  VECTOR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }

                    ipgdb_Update(CURRENT_D_SVC_TABLE, (Address)&svcdat);

                    if(pgdatN_iPresent())

                    {
                        pgdatN_OnChannelUpdated(channel, dataid);       

                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else
            {
                ret = err_BadParameter;
            }
        }
        else
        {
            ret = err_ChannelNotInstalled;
        }
    }
    else
    {
        ret = err_BadParameter;
    }

#undef  NO
#undef  PTR
#undef  SCALAR_ITEM

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_GetDigitalChannel(AppApiChannel* channel, int OnId, int TsId, int Sid, int Ptc)
{
    Bool Found = FALSE;
    FResult ret = err_Ok;
    HsvPgdatDigServiceData  svcdat;
    int i = 0, NoOfRecs = 0;

    NoOfRecs = ipgdb_GetNoRecords(CURRENT_D_SVC_TABLE);
    for (i = 0; (i < NoOfRecs) && (!Found); i++)
    {
        if(ipgdb_GetByIndex(CURRENT_D_SVC_TABLE, i, (Address)&svcdat))
        {
            if(VALID_ONID(OnId))
            {
                if(svcdat.OriginalNetworkId == OnId)
                {
                    Found = TRUE;
                }
            }
            if(VALID_TSID(TsId))
            {
                Found = FALSE;
                if(svcdat.Tsid == TsId)
                {
                    Found = TRUE;
                }
            }
            if(VALID_SID(Sid))
            {
                Found = FALSE;
				if(svcdat.ServiceId == Sid)
				{
					Found = TRUE;
				}
			}
            if(VALID_PTC(Ptc))
            {
                Found = FALSE;
                if(svcdat.Frequency == Ptc)
                {
                    Found = TRUE;
                }
            }
        }
    }

    if(Found)
    {
        ASSIGN_CHANNEL_FROM_SVC(&svcdat, channel);
    }
    else
    {
        ret = err_ChannelNotInstalled;
    }

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetDigitalChannelForFreesat(int *MultiplePresetList, int OnId, int TsId, int Sid, int Ptc)
{
    Bool Found = FALSE;
    FResult ret = err_Ok;
    HsvPgdatDigServiceData  svcdat;
    int i = 0, NoOfRecs = 0;

    NoOfRecs = ipgdb_GetNoRecords(CURRENT_D_SVC_TABLE);
	TraceNotice(m,"NoOfRecs %d",NoOfRecs);
    for (i = 0; (i < NoOfRecs) && (!Found); i++)
    {
        if(ipgdb_GetByIndex(CURRENT_D_SVC_TABLE, i, (Address)&svcdat))
        {
            if(VALID_ONID(OnId))
            {
                if(svcdat.OriginalNetworkId == OnId)
                {
                    Found = TRUE;
                }
            }
            if(VALID_TSID(TsId))
            {
                Found = FALSE;
                if(svcdat.Tsid == TsId)
                {
                    Found = TRUE;
                }
            }
            if(VALID_SID(Sid))
            {
                Found = FALSE;
				if(svcdat.ServiceId == Sid)
				{
					Found = TRUE;
				}
			}
            if(VALID_PTC(Ptc))
            {
                Found = FALSE;
                if(svcdat.Frequency == Ptc)
                {
                    Found = TRUE;
                }
            }
        }
    }

    if(Found)
    {
        for(int i=0;i<8;i++)
		{
        	MultiplePresetList[i] = svcdat.MultiplePreset[i];
		}
    }
    else
    {
        ret = err_ChannelNotInstalled;
    }

    return ret;
}


AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_LoadChannelTable(char* dir)
{
    FResult ret = err_Ok;

    ipgdb_ClearTable(ipgdb_GetCurrentTable());

    ret = chmapop_LoadChannelTable(ipgdb_GetCurrentTable(), dir);

    chmapop_ChannelTableChanged();
    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_SaveChannelTable(char* dir)
{
    return chmapop_SaveChannelTable(ipgdb_GetCurrentTable(), dir);
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_LoadChannelTableFromMedium(char* dir, int medium) 
{

	FResult ret = err_Ok;   
#if 0
	memset(mPgdatMsg.DirectoryPath, 0x00, sizeof(mPgdatMsg.DirectoryPath));
	strcpy (mPgdatMsg.DirectoryPath, dir);
	mPgdatMsg.medium = medium;

	tprtk_EventSend (mPgdatExtTaskId, PGDAT_EXT_LOAD);
#endif
	return ret;


}



AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_SaveChannelTableToMedium(char* dir, int medium) 
{
	FResult ret = err_Ok;   
#if 0
	memset(mPgdatMsg.DirectoryPath, 0x00, sizeof(mPgdatMsg.DirectoryPath));
	strcpy (mPgdatMsg.DirectoryPath, dir);
	mPgdatMsg.medium = medium;

	tprtk_EventSend (mPgdatExtTaskId, PGDAT_EXT_SAVE);
#endif
	return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_SwapChannels(AppApiChannel channel1, AppApiChannel channel2)
{        
    /*Algorithm */
    /* 1. Check channel isntallation 
       1.1 check whether first channel isntalled
       1.2 Check whether second chennale isntallaed 
       2. If both channels installed
       2.1 Update channel1 with data of channel2
       2.2 Update channel2 with data of channel1
       2.3 if the channel1 is digital then update its fields
       2.4 if the channel2 is didital then update its fields
       3. If channel1 is installed (Channel 2 not installed )
       3.1 Move channel1 data to channel2 (Insert)
       3.2 Delete channel1
       4. If channel2 is installed 
       4.1 Move channel2 data to channel1 (Insert)
       4.2 Delete channel2         
       5. If both are not installed 
       return False
       */

    Bool retval = FALSE;         
    Bool Channel1Ins = FALSE;    
    Bool Channel2Ins = FALSE;   
    //LOCK_MUTEX(pgdatmutex);

    sync_EnableEvents(FALSE);
    /* Check channel isntallation of both channels */
    Channel1Ins = pgdat_IsChannelInstalled(&channel1);
    Channel2Ins = pgdat_IsChannelInstalled(&channel2);

    TraceInfo(m,"%s:%d, Channel1=%d,Channel2=%d ", __FUNCTION__,__LINE__,channel1.Channel.Digit,channel2.Channel.Digit);

    /* Both Channels are installed */
    if ((Channel1Ins) && (Channel2Ins))
    {
        HsvPgdatPresetData Channel1Presetdat,Channel2Presetdat; 
        TraceInfo(m," Swaping Both Channels installed" );
        ASSIGN_PRESET_KEYS(&Channel1Presetdat, &channel1);      
        retval = ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&Channel1Presetdat);
        ASSIGN_PRESET_KEYS(&Channel2Presetdat, &channel2);      
        retval = ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&Channel2Presetdat);

        InstalledSwap(Channel1Presetdat,Channel2Presetdat);

        retval = TRUE;

    }
    /* Channel 1 is installed and channel 2 is not installed */
    if ((Channel1Ins) && (!Channel2Ins))
    {
        /* Insert the preset table at cahnnel2 */
        /* Update the corresponding channel table  */
        /* Delete the preset table at channel1 */

        HsvPgdatPresetData Channel1Presetdat, temppPesetdat;    
        TraceInfo(m," Swapping:first is installed and second is not installed ");
        ASSIGN_PRESET_KEYS(&Channel1Presetdat, &channel1);      
        ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&Channel1Presetdat);

        /* Temporary copy  for deletion */
        temppPesetdat = Channel1Presetdat;
        /* Delete the temp preset table data */
        ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&temppPesetdat);

        Channel1Presetdat.PresetNumber  = channel2.Channel.Digit;   
        Channel1Presetdat.UniqueNodeId  = -1;// Invalid Node id 

        /* Add the new preset number into the Preset Table */
        ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&Channel1Presetdat);

        /* Update Analog or Service table */
        UpdateAnalogOrDigitalTable(Channel1Presetdat);

        retval = TRUE;
    }

    /* Channel 1 is not installed and channel 2 is installed */
    if ((!Channel1Ins) && (Channel2Ins))
    {
        /* Insert the preset table at cahnnel1 */
        /* Update the corresponding channel table  */
        /* Delete the preset table at channel2 */

        HsvPgdatPresetData Channel2Presetdat, temppPesetdat;    
        TraceInfo(m," Swapping:first is not installed and second is installed ");
        ASSIGN_PRESET_KEYS(&Channel2Presetdat, &channel2);      
        ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&Channel2Presetdat);

        /* Temporary copy  for deletion */
        temppPesetdat = Channel2Presetdat;

        /* Delete the temp preset table data */
        ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&temppPesetdat);

        Channel2Presetdat.PresetNumber  = channel1.Channel.Digit;       
        Channel2Presetdat.UniqueNodeId  = -1;// Invalid Node id 

        /* Add the new preset number into the Preset Table */
        ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&Channel2Presetdat);

        /* Update Analog or Service table */
        UpdateAnalogOrDigitalTable(Channel2Presetdat);  

        retval = TRUE;
    }


    /* Both are not installed */
    if ((!Channel1Ins) && (!Channel2Ins))
    {
        TraceInfo(m," Swapping:Bot are not installed ");
        retval = FALSE;
    }

    if (retval)
    {

        TraceInfo(m," Swapping:Sending Notification ");
        chmapop_CommitToFlash(ipgdb_GetCurrentTable());

        if(pgdatN_iPresent())
        {
            pgdatN_OnChannelsSwapped(channel1, channel2);                   
        }
        if(pgdatNxx_iPresent())
        {
            pgdatNxx_OnChannelsSwapped(channel1, channel2); 
        }
    }
    //UNLOCK_MUTEX(pgdatmutex);
    sync_EnableEvents(TRUE);
    return retval;                        



}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat_ReorderChannels(AppApiChannel channel1, AppApiChannel channel2, Bool swap)
{
    /* Algorithm */
    /*  1. Get the digits of both channels
        1.1 Get the digit of channel1
        1.2 Get the digit of channel2
        2. Compare the digit of chanel1 and channel2
        channel1.digit < channel2.digit
        Move down
        otherwise
        Move up 
        3. Call recursively the above until it becomes false  
        4. if Movedown 
        data = data -1 
        else
        data = daa + 1  
        */

    FResult retval = TRUE;   
    sync_EnableEvents(FALSE);

    /* Lock the mutex */
    LOCK_MUTEX(pgdatmutex); 

    if(swap == TRUE)
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        retval = pgdat_SwapChannels(channel1, channel2);
        if(pgdatN_iPresent())
        {
            pgdatN_OnChannelsRearranged(channel1, channel2);
        }
        if(pgdatNxx_iPresent())
        {
            pgdatNxx_OnChannelsRearranged(channel1, channel2);
        }
    }
    else
    {
        TraceDebug(m,"Reorder Function: %s, %d ",__FUNCTION__, __LINE__);
        retval = internalreorder(channel1, channel2, TRUE); 
    }


    /* Unlock the mutex */
    UNLOCK_MUTEX(pgdatmutex);
    sync_EnableEvents(TRUE);
    return retval;

}

void CHsvSatProgramData_mpgdat_Priv::pgdat3_ClearCurrentTable(void)
{
    ipgdb_ClearTable(ipgdb_GetCurrentTable());
    chmapop_CommitToFlash(ipgdb_GetCurrentTable());
    chmapop_ChannelTableChanged();
}

void CHsvSatProgramData_mpgdat_Priv::pgdat3_ClearAllTables(void)
{
    ipgdb_ClearTable(ipgdb_GetCurrentTable());
    chmapop_CommitToFlash(ipgdbconst_Antenna);
    chmapop_CommitToFlash(ipgdbconst_Cable);
    chmapop_ChannelTableChanged();
}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat3_IsValidChannel(AppApiChannel channel)
{
    Bool ret = FALSE;

    UNUSED(channel);
    return ret;
}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat3_IsChannelInstalled(AppApiChannel *channel )
{
    return pgdat_IsChannelInstalled(channel);
}

Bool CHsvSatProgramData_mpgdat_Priv::pgdat3_IsAttributeSupported(int attribute)
{
    return mIsAttributeSupported(attribute);
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetChannelDataBool(AppApiChannel channel, int dataid, Bool  *value)
{
    FResult ret = err_Ok;

    ret = pgdat_GetChannelDataBool(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_StoreChannelDataBool(AppApiChannel channel, int dataid, Bool  value)
{
    FResult ret = err_Ok;

    ret = pgdat_StoreChannelDataBool(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetChannelDataInt(AppApiChannel channel, int dataid, int   *value)
{
    FResult ret = err_Ok;

    ret = pgdat_GetChannelDataInt(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_StoreChannelDataInt(AppApiChannel channel, int dataid, int   value)
{
    FResult ret = err_Ok;

    ret = pgdat_StoreChannelDataInt(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetChannelDataNat32(AppApiChannel channel, int dataid, Nat32 *value)
{
    FResult ret = err_Ok;

    ret = pgdat_GetChannelDataNat32(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_StoreChannelDataNat32(AppApiChannel channel, int dataid, Nat32 value)
{
    FResult ret = err_Ok;

    ret = pgdat_StoreChannelDataNat32(channel, dataid, value);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetChannelDataString(AppApiChannel channel, int dataid, Nat16  *value, int size)
{
    FResult ret = err_Ok;

    ret = pgdat_GetChannelDataString(channel, dataid, value, size);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_StoreChannelDataString(AppApiChannel channel, int dataid, Nat16 *value, int size)
{
    FResult ret = err_Ok;

    ret = pgdat_StoreChannelDataString(channel, dataid, value, size);   

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetDigitalChannel(AppApiChannel* channel, int OnId, int TsId, int Sid, int Ptc)
{
    FResult ret = err_Ok;
    ret = pgdat_GetDigitalChannel(channel, OnId, TsId, Sid, Ptc);

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_LoadChannelTable(char* dir)
{
    FResult ret = err_Ok;

    ipgdb_ClearTable(ipgdb_GetCurrentTable());

    ret = chmapop_LoadChannelTable(ipgdb_GetCurrentTable(), dir);

    chmapop_ChannelTableChanged();
    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_SaveChannelTable(char* dir)
{
    return chmapop_SaveChannelTable(ipgdb_GetCurrentTable(), dir);
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::mLoadChannelTableFromMedium(char* dir, int medium) 
{
    FResult ret = err_Ok;   

    ret = chmapop_LoadChannelExternal(dir);
    if (ret == err_Ok)
    {
        ipgdb_ClearTable(ipgdb_GetCurrentTable());          
        ret = chmapop_ReloadFromFlash(ipgdb_GetCurrentTable());    
        pgdatNxx_OnChannelTableChanged();
		
		pgdatNxxx_OnChannelMapLoadComplete(TRUE);
    }
    else
    {
        ret = err_FileError;
		pgdatNxxx_OnChannelMapLoadComplete(FALSE);
    }

    UNUSED(medium);
    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_LoadChannelTableFromMedium(char* dir, int medium) 
{
	FResult ret = err_Ok;   
#if 0
	memset(mPgdatMsg.DirectoryPath, 0x00, sizeof(mPgdatMsg.DirectoryPath));
	strcpy (mPgdatMsg.DirectoryPath, dir);
	mPgdatMsg.medium = medium;

	tprtk_EventSend (mPgdatExtTaskId, PGDAT_EXT_LOAD);
#endif
	return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::mSaveChannelTableToMedium(char* dir, int medium) 
{
    FResult ret = err_Ok;   
	Bool	status = FALSE;

    ret = chmapop_SaveChannelExternal(dir); 
	
	if(ret == err_Ok)
	{ 
		status = TRUE;
	}
	//PrintfNotice(" %s: pgdatNxxx_OnChannelMapSaveComplete : status %d", __FUNCTION__, status);
	pgdatNxxx_OnChannelMapSaveComplete(status);
	
    UNUSED(medium);
    return ret;

}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_SaveChannelTableToMedium(char* dir, int medium) 
{
	FResult ret = err_Ok;   
#if 0
	memset(mPgdatMsg.DirectoryPath, 0x00, sizeof(mPgdatMsg.DirectoryPath));
	strcpy (mPgdatMsg.DirectoryPath, dir);
	mPgdatMsg.medium = medium;

	tprtk_EventSend (mPgdatExtTaskId, PGDAT_EXT_SAVE);
#endif
	return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetMediumFromTable (char *dir, int *medium) 
{
    FResult ret = err_Ok;

    ret = chmapop_GetMediumFromTable (dir, medium);

    return ret;
}


AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_SwapChannels(AppApiChannel channel1, AppApiChannel channel2)
{        
    /*Algorithm */
    /* 1. Check channel isntallation 
       1.1 check whether first channel isntalled
       1.2 Check whether second chennale isntallaed 
       2. If both channels installed
       2.1 Update channel1 with data of channel2
       2.2 Update channel2 with data of channel1
       2.3 if the channel1 is digital then update its fields
       2.4 if the channel2 is didital then update its fields
       3. If channel1 is installed (Channel 2 not installed )
       3.1 Move channel1 data to channel2 (Insert)
       3.2 Delete channel1
       4. If channel2 is installed 
       4.1 Move channel2 data to channel1 (Insert)
       4.2 Delete channel2         
       5. If both are not installed 
       return False
       */

    //LOCK_MUTEX(pgdatmutex);

    /* Check channel isntallation of both channels */

    /* Both Channels are installed */


    AppApiReturnCode  retval;

    /* Channel 1 is installed and channel 2 is not installed */
    /* Insert the preset table at cahnnel2 */
    /* Update the corresponding channel table  */
    /* Delete the preset table at channel1 */




    /* Temporary copy  for deletion */
    /* Delete the temp preset table data */


    /* Add the new preset number into the Preset Table */

    /* Update Analog or Service table */


    /* Channel 1 is not installed and channel 2 is installed */
    /* Insert the preset table at cahnnel1 */
    /* Update the corresponding channel table  */
    /* Delete the preset table at channel2 */




    /* Temporary copy  for deletion */

    /* Delete the temp preset table data */


    /* Add the new preset number into the Preset Table */

    /* Update Analog or Service table */



    /* Both are not installed */


    retval = pgdat_SwapChannels(channel1, channel2);
    //pgdatNxx_OnChannelTableChanged();
    //UNLOCK_MUTEX(pgdatmutex);
    return retval;                        



}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_ReorderChannels(AppApiChannel channel1, AppApiChannel channel2, Bool swap)
{
    /* Algorithm */
    /*  1. Get the digits of both channels
        1.1 Get the digit of channel1
        1.2 Get the digit of channel2
        2. Compare the digit of chanel1 and channel2
        channel1.digit < channel2.digit
        Move down
        otherwise
        Move up 
        3. Call recursively the above until it becomes false  
        4. if Movedown 
        data = data -1 
        else
        data = daa + 1  
        */

    AppApiReturnCode retval;

    /* Lock the mutex */

    retval = pgdat_ReorderChannels( channel1, channel2, swap);


    /* Unlock the mutex */
    return retval;

}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetNoOfBarkerMultiplexes(int *NoOfMuxes)
{
    AppApiReturnCode ret = err_Ok;
    *NoOfMuxes = 1; /* For Europe DVB-C only 1 Barker multiplex */
    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetBarkerMultiplexByIndex(int index, AppApiMultiplex *muxes)
{
    AppApiReturnCode ret = err_Ok;
    HsvPgdatDigTSData   tsdata;
    int numRecords      = 0;
    int record_index    = 0;
    Nat16 Onid          = 0xFFFF;
    Nat16 Tsid          = 0xFFFF;

    


    if( NULL != muxes )
    {
    	/* Default ONID and TSID values  */
		muxes->OnId = 0xFFFF;
    	muxes->TsId = 0xFFFF;
	
      numRecords = ipgdb_GetNoRecords(CURRENT_D_FREQ_TABLE);
      for(record_index = 0; record_index < numRecords ; record_index ++)
      {
          if(ipgdb_GetByIndex(CURRENT_D_FREQ_TABLE, record_index, (Address)&tsdata)) 
          {      
              if((Onid == tsdata.OriginalNetworkId) && (Tsid == tsdata.Tsid))
              {
                  muxes->OnId                                     = Onid;
                  muxes->TsId                                     = Tsid;    
                  muxes->Ptc                                      = HsvUnknownPtc;
                  muxes->Params.Type                              = AppApiDVBCType;
                  muxes->Params.TuningParams.DVBCParam.Frequency  = tsdata.Frequency;
                  muxes->Params.TuningParams.DVBCParam.SymbolRate = tsdata.SymbolRate;
                  muxes->Params.TuningParams.DVBCParam.Modulation = tsdata.ModulationType;            
                  break;
              }            
          }
      }
    }
    else
    {
        ASSERT(!"GetBarkerMultiplexes :- NULL pointer passed");
        ret = err_BadParameter;
    }

    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_ReArrangeChannels(AppApiChannel channel1, AppApiChannel channel2)
{
    AppApiReturnCode ret = err_Ok;
    pgdat_ReorderChannels(channel1, channel2, FALSE);
    return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetBarkerMultiplexesForChannel(AppApiChannel channel, int* NoOfMuxes, AppApiMultiplex *muxes)
{
    AppApiReturnCode ret = err_Ok;
    UNUSED(channel);
    UNUSED(NoOfMuxes);
    UNUSED(muxes);
    return ret;
}

void CHsvSatProgramData_mpgdat_Priv::GetOperator(AppApiOperator * x)
{

}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetOperator(AppApiOperator *OperatorId)
{
    AppApiReturnCode ret = err_Ok;
	GetOperator(OperatorId);
	return ret;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_StoreChannelDataNat64(AppApiChannel channel, int dataid, Nat64 value)
{
    TraceDebug(m," %d %s data id %d  channel %d ", __LINE__,__FUNCTION__, dataid, channel.Channel.Digit);

    FResult ret = err_Ok;

    ret = mSetScalarAttributeNat64(channel, dataid, value);

    return ret;

}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetChannelDataNat64(AppApiChannel channel, int dataid, Nat64  *value)
{
    FResult ret = err_Ok;

    TraceDebug(m," %d %s data id %d  ", __LINE__,__FUNCTION__, dataid);

    ret = mGetScalarAttributeNat64(channel, dataid, value);

    return ret;
}

FResult CHsvSatProgramData_mpgdat_Priv::mSetScalarAttributeNat64(AppApiChannel channel, int dataid, Nat64  value)
{
    FResult ret = err_Ok;
    Nat64 oldvalue = 0;

    ret = mGetScalarAttributeNat64(channel, dataid, &oldvalue);
    if(err_Ok == ret)
    {

        if(oldvalue != value)
        {

#define NO
#define PTR    *
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)
            if(mIsAttributeSupportedNat64(dataid))
            {

                HsvPgdatPresetData preset;

                ASSIGN_PRESET_KEYS(&preset, &channel);

                if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
                {
                    switch(dataid)
                    {
#define ANALOG_ATTRIB(field, f_type, ptr, value)
#define COMMON_ATTRIB(field, f_type, ptr, value)       preset.field = (f_type ptr) value
#define DIGITAL_ATTRIB(field, f_type, ptr, value)      preset.field = (f_type ptr) value
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                      \
                        applic(field, f_type, ptr, value);      \
                        break;

#ifndef __cplusplus
#include "data/hsvpgdat_Presetattrib.h"
#else
#include "hsvpgdat_Presetattrib.h"
#endif

#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }

                    ipgdb_Update(CURRENT_PRESET_TABLE, (Address)&preset);
                    if(pgdatN_iPresent())
                    {
                        pgdatN_OnChannelUpdated(channel, dataid);
                    }
                    if(pgdatNxx_iPresent())
                    {
                        pgdatNxx_OnChannelUpdated(channel, dataid);     
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else
            {
                ret = err_BadParameter;
            }
        }    
    }
#undef  NO
#undef  PTR
#undef  VECTOR_ITEM
    return ret;
}



FResult CHsvSatProgramData_mpgdat_Priv::mGetScalarAttributeNat64(AppApiChannel channel, int dataid, Nat64  *value)
{
    FResult ret = err_Ok;

#define NO
#define PTR    *
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)
    //TraceNotice(m,"Zaheer: %d %s, DataId: %d", __LINE__, __FUNCTION__, dataid);
    if((NULL != value) && mIsAttributeSupportedNat64(dataid))
    {

        HsvPgdatPresetData preset;

        ASSIGN_PRESET_KEYS(&preset, &channel);

        if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
        {
            switch(dataid)
            {
#define ANALOG_ATTRIB(field, a_type, ptr, value)       (*value) = (a_type ptr) preset.field
#define COMMON_ATTRIB(field, a_type, ptr, value)       (*value) = (a_type ptr) preset.field
#define DIGITAL_ATTRIB(field, a_type, ptr, value)       ret = err_NotSupported;
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                                                 \
                applic(field, a_type, ptr, value);  \
                break;
#ifndef __cplusplus
#include "data/hsvpgdat_Presetattrib.h"
#else
#include "hsvpgdat_Presetattrib.h"
#endif


#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
            }
        }
        else
        {
            //TraceNotice(m,"Zaheer: %d %s: err_ChannelNotInstalled", __LINE__, __FUNCTION__);
            ret = err_ChannelNotInstalled;
        }
    }
    else
    {
        ret = err_BadParameter;
    }

#undef  NO
#undef  PTR
#undef  VECTOR_ITEM

    return ret;
}
FResult CHsvSatProgramData_mpgdat_Priv::mGetScalarAttribute(AppApiChannel channel, int dataid, Nat32  *value)
{
    FResult ret = err_Ok;

#define NO
#define PTR    *
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)
    if((NULL != value) && mIsAttributeSupported(dataid))
    {
        HsvPgdatPresetData preset;

        ASSIGN_PRESET_KEYS(&preset, &channel);

        if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
        {
            if(AppApiAnalog == channel.Type)
            {
                HsvPgdatAnalogData  anadat;

                ASSIGN_ANALOG_KEYS(&anadat, &preset);

                if(ipgdb_GetByKey(CURRENT_ANALOG_TABLE, (Address)&anadat))
                {
                    switch(dataid)
                    {
#define ANALOG_ATTRIB(field, a_type, ptr, value)       (*value) = (a_type ptr) anadat.field
#define COMMON_ATTRIB(field, a_type, ptr, value)       (*value) = (a_type ptr) anadat.field
#define DIGITAL_ATTRIB(field, a_type, ptr, value)       ret = err_NotSupported;
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                                                 \
                        applic(field, a_type, ptr, value);  \
                        break;

#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif


#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else if ((AppApiOnePart == channel.Type) || (AppApiTwoPart == channel.Type))
            {
                HsvPgdatDigServiceData  svcdat;

                ASSIGN_DIGSVC_KEYS(&svcdat, &preset);
                if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
                {
                    switch(dataid)
                    {
#define ANALOG_ATTRIB(field, a_type, ptr, value)       ret= err_NotSupported;                 
#define COMMON_ATTRIB(field, a_type, ptr, value)       (*value) = (a_type) svcdat.field
#define DIGITAL_ATTRIB(field, a_type, ptr, value)      (*value) = (a_type) svcdat.field
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                      \
                        applic(field, a_type, ptr, value);      \
                        break;

#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
        }
        else
        {
            ret = err_ChannelNotInstalled;
        }
    }
    else
    {
        ret = err_BadParameter;
    }

#undef  NO
#undef  PTR
#undef  VECTOR_ITEM

    return ret;
}

FResult CHsvSatProgramData_mpgdat_Priv::mSetScalarAttribute(AppApiChannel channel, int dataid, Nat32 value)
{
    FResult ret = err_Ok;
    Nat32 oldvalue = 0;

    ret = mGetScalarAttribute(channel, dataid, &oldvalue);
    if(err_Ok == ret)
    {
        if(oldvalue != value)
        {

#define NO
#define PTR    *
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)
            if(mIsAttributeSupported(dataid))
            {
                HsvPgdatPresetData preset;

                ASSIGN_PRESET_KEYS(&preset, &channel);

                if (ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&preset))
                {
                    if(AppApiAnalog == channel.Type)
                    {
                        HsvPgdatAnalogData  anadat;

                        ASSIGN_ANALOG_KEYS(&anadat, &preset);

                        if(ipgdb_GetByKey(CURRENT_ANALOG_TABLE, (Address)&anadat))
                        {
                            switch(dataid)
                            {
#define ANALOG_ATTRIB(field, f_type, ptr, value)       anadat.field = (f_type ptr) value
#define COMMON_ATTRIB(field, f_type, ptr, value)       anadat.field = (f_type ptr) value
#define DIGITAL_ATTRIB(field, f_type, ptr, value)
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                                                                          \
                                applic(field, f_type, ptr, value);  \
                                break;

#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                            }
                            ipgdb_Update(CURRENT_ANALOG_TABLE, (Address)&anadat);

                            if(pgdatN_iPresent())
                            {
                                pgdatN_OnChannelUpdated(channel, dataid);       
                            }
                            if(pgdatNxx_iPresent())
                            {
                                pgdatNxx_OnChannelUpdated(channel, dataid);     
                            }
                        }
                        else
                        {
                            ret = err_ChannelNotInstalled;
                        }
                    }
                    else if ((AppApiOnePart == channel.Type) || (AppApiTwoPart == channel.Type))
                    {
                        HsvPgdatDigServiceData  svcdat;

                        ASSIGN_DIGSVC_KEYS(&svcdat, &preset);

                        if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
                        {
                            switch(dataid)
                            {
#define ANALOG_ATTRIB(field, f_type, ptr, value)
#define COMMON_ATTRIB(field, f_type, ptr, value)       svcdat.field = (f_type ptr) value
#define DIGITAL_ATTRIB(field, f_type, ptr, value)      svcdat.field = (f_type ptr) value
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:                      \
                                applic(field, f_type, ptr, value);      \
                                break;

#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif

#undef  SCALAR_ITEM
#undef  ANALOG_ATTRIB
#undef  DIGITAL_ATTRIB
#undef  COMMON_ATTRIB
                            }

                            ipgdb_Update(CURRENT_D_SVC_TABLE, (Address)&svcdat);
                            if(pgdatN_iPresent())
                            {
                                pgdatN_OnChannelUpdated(channel, dataid);
                            }
                            if(pgdatNxx_iPresent())
                            {
                                pgdatNxx_OnChannelUpdated(channel, dataid);     
                            }
                        }
                        else
                        {
                            ret = err_ChannelNotInstalled;
                        }
                    }
                    else
                    {
                        ret = err_BadParameter;
                    }
                }
                else
                {
                    ret = err_ChannelNotInstalled;
                }
            }
            else
            {
                ret = err_BadParameter;
            }
        }
    }

#undef  NO
#undef  PTR
#undef  VECTOR_ITEM

    return ret;
}
Bool CHsvSatProgramData_mpgdat_Priv::mIsAttributeSupportedNat64(int attribute)
{
    Bool ret = FALSE;

    switch(attribute)
    {
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field ,f_type, applic)   case HsvPgDat##attrib:      \
        ret = supp;             \
        break;
		
#ifndef __cplusplus
#include "data/hsvpgdat_Presetattrib.h"
#else
#include "hsvpgdat_Presetattrib.h"
#endif

#undef SCALAR_ITEM
        default : 
            ASSERT(FALSE);
            break;
    }
    return ret;
}
Bool CHsvSatProgramData_mpgdat_Priv::mIsAttributeSupported(int attribute)
{
    Bool ret = FALSE;

    switch(attribute)
    {
#define SCALAR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:      \
        ret = supp;             \
        break;
#define VECTOR_ITEM(attrib, a_type, ptr, supp, field, f_type, applic)   case HsvPgDat##attrib:      \
        ret = supp;             \
        break;
#ifndef __cplusplus
#include "data/hsvpgdat_attrib.h"
#else
#include "hsvpgdat_attrib.h"
#endif


#undef SCALAR_ITEM
#undef VECTOR_ITEM
        default : 
            ASSERT(FALSE);
            break;
    }
    return ret;
}


FResult CHsvSatProgramData_mpgdat_Priv::ShuffleChannels(ReorderChannelInfo rchannelinfo)
{
    AppApiChannel channel1;
    AppApiChannel channel2;
    Bool MoveupOrDown;
    Bool DeleteFirst;
    HsvPgdatPresetData FromPreset;  
    Nat32 i;
    Bool retval = FALSE;
    Bool NeedsToShuffle = FALSE;
    Bool reorderN = FALSE;      


    channel1        = rchannelinfo.RChannel1;
    channel2        = rchannelinfo.RChannel2;
    MoveupOrDown    = rchannelinfo.MoveupOrDown;
    DeleteFirst     = rchannelinfo.DeleteFirst;

    /* Get the preset table for the Channel 1 */
    ASSIGN_PRESET_KEYS(&FromPreset, &channel1);     
    retval = ipgdb_GetByKey(CURRENT_PRESET_TABLE, (Address)&FromPreset);

    /* Temporary copy the channel 1 preset data */


    /* If the preset table is not available send a dummy notification to 
       Apps for removing the  busy icon */
    if (!retval)
    {   
        /* Send dummy notificiation */
        if(pgdatN_iPresent())
        {
            pgdatN_OnChannelsRearranged(channel1, channel2);        
        }
        return FALSE;
    }

    /* Delete the channel1 in the preset table entry */
    //if (DeleteFirst)
    {
        ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&FromPreset);           
    }


    /* Initalize the loop variable */
    i = 1;

    /* Get the right place to insert the channel1 */
    while (EVALUATE(channel1.Channel.Digit, channel2.Channel.Digit, i, MoveupOrDown))
    {
        Int16 nextprevchanno;       
        int index;
        HsvPgdatPresetData PresetItr;

        /* Get the next or previous channel number based on the direction */
        nextprevchanno = NEXT_OR_PREVIOUS(channel1.Channel.Digit,i,MoveupOrDown);

        /* If the nextprevchanno is < 0 that means, we dont have any have channels 
           to reorder */

        if (nextprevchanno < 0)
            break;


        /* Get the Preset index for this new preset number */
        PresetItr.PresetNumber = nextprevchanno;        
        retval = ipgdb_GetIndex(CURRENT_PRESET_TABLE, &index, (Address)&PresetItr);


        /* If the preset is available then Update preset numer 
           else Insert */
        if ((!retval) || (retval != -1))
        {
            HsvPgdatPresetData temppreset;              

            /* Get the preset data for the index */
            retval = ipgdb_GetByIndex(CURRENT_PRESET_TABLE,index,(Address)&PresetItr);          

            /* temporarily store the preset data */
            temppreset = PresetItr;         

            /* Get the next or previous preset number based on the direction */
            INCREMENT_OR_DECREMENT(PresetItr.PresetNumber, 1, MoveupOrDown);

            /* Add the new preset number into the Preset Table */
            PresetItr.UniqueNodeId  = -1;// Invalid Node id 
            ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&PresetItr);

            UpdateAnalogOrDigitalTable(PresetItr);

            /* Delete the temp preset table data */
            ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&temppreset);
        }       

        /* Check whether we need more iterations to shuffle */
        if ( (0 == i % SHUFFLE_CHANNELS_NO_SIZE ) && 
                (channel2.Channel.Digit != NEXT_OR_PREVIOUS(channel1.Channel.Digit,i,MoveupOrDown )) && 
                (channel2.Channel.Digit != NEXT_OR_PREVIOUS(channel1.Channel.Digit,(i+1),MoveupOrDown)))
        {           
            NeedsToShuffle = TRUE;
            break;
        }
        i++;
    }

    /* Insert the first channel at the approriate location*/
    /* If some channels needs to shuffled (reordered) 
       then
       Inserted channel number should be Channel1 preset number +/- number of
       iterations of the preset tbale, +/- depends on the MoveUpOrDown 
       otherwise
       Reorder is completed and Inserted Channel number is
       Channel1 preset number +/- number of iterations of the preset table +/-
       1, depends on the MoveUpOr Down */
    if (NeedsToShuffle)
    {
        FromPreset.PresetNumber = NEXT_OR_PREVIOUS(FromPreset.PresetNumber,i,MoveupOrDown);                 
    }
    else
    {
        reorderN = TRUE;
        if (MoveupOrDown == MOVEDOWN)
        {
            FromPreset.PresetNumber = channel1.Channel.Digit + i - 1;           
        }
        else
        {
            FromPreset.PresetNumber = channel1.Channel.Digit - i + 1;           
        }
    }   
    /* Insert the First channel in the Preset table */  

    FromPreset.UniqueNodeId = -1;// Invalid Node id 
    ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&FromPreset);

    /* Update the corresponding table based on the type (Analog or Digital) of the preset */

    UpdateAnalogOrDigitalTable(FromPreset);

    /* If the some more channels needs to shuffled then call this function again */

    if (NeedsToShuffle)
    {
        AppApiChannel reshuffchannel;

        reshuffchannel.Type = (AppApiChannelType)FromPreset.Type;
        reshuffchannel.Channel.Digit = FromPreset.PresetNumber;
        retval = pgdat_IsChannelInstalled(&reshuffchannel); 
        internalreorder(reshuffchannel, channel2, FALSE);       
    }

    /* If the reorder is completed then send a notification to application
       to stop busy icon */
    if (reorderN)
    {
        chmapop_CommitToFlash(ipgdb_GetCurrentTable());
        TraceDebug(m,"Reorder: %s, %d, Notification to Apps ",__FUNCTION__,__LINE__);   
        if(pgdatN_iPresent())
        {
            pgdatN_OnChannelsRearranged(channel1, channel2);
        }
        if(pgdatNxx_iPresent())
        {
            pgdatNxx_OnChannelsRearranged(channel1, channel2);
            //pgdatN_OnChannelTableChanged();
        }
    }

    return TRUE;
}

#if MESSAGE_SEND_RECEIVE_SUPPORT

void CHsvSatProgramData_mpgdat_Priv::mPgdatThread(void *arg)
{

    TraceDebug(m,"Pgdat Thread function is in execution mode");   
#if 0
    while (1)
    {

        /* Receieve the channel information from the message queue */


        long msgtyp = 1;    

        PgdatReOrderChannelMsg  rechanmsg;  /* Reorder channel Message */
        ssize_t rmsgsize;                   /* Receive channel message */


        rmsgsize = msgrcv(gmqd, (PgdatReOrderChannelMsg*)&rechanmsg, sizeof(rechanmsg.ReChanlInfo), msgtyp, MSG_NOERROR | IPC_NOWAIT);      
        //msgctl(mqd, IPC_STAT, NULL);              
        /* Received message has some valid data then process it */
        if (rmsgsize  !=  -1)
        {
            Bool retval;

            /* Delete the message from the queue*/
            //msgctl(gmqd, IPC_RMID, NULL);     

            rechanmsg.ReChanlInfo.RChannel1.Channel.Digit, rechanmsg.ReChanlInfo.RChannel2.Channel.Digit,
                rechanmsg.ReChanlInfo.MoveupOrDown,rechanmsg.ReChanlInfo.DeleteFirst);

            retval = ShuffleChannels(rechanmsg.ReChanlInfo);                            
        }               

    }
#endif
}
#endif

Bool CHsvSatProgramData_mpgdat_Priv::internalreorder(AppApiChannel channel1, AppApiChannel channel2, Bool DeleteFrist)
{
    Bool retval = FALSE;    
#if 0
    if (channel1.Channel.Digit < channel2.Channel.Digit)
    {

        PgdatReOrderChannelMsg  rechanmsg;  /* Reorder channel Message */
        /* Send the channel information to the message queue */
        ReorderChannelInfo rechaninfo;      

        /* Copy the reorder channels into the structure and Move Down because of 
           first channel present number is less than the second channel preset number */ 
        rechanmsg.ReChanlInfo.RChannel1     = rechaninfo.RChannel1      = channel1;
        rechanmsg.ReChanlInfo.RChannel2     = rechaninfo.RChannel2      = channel2;
        rechanmsg.ReChanlInfo.MoveupOrDown  = rechaninfo.MoveupOrDown   = MOVEDOWN; 
        rechanmsg.ReChanlInfo.DeleteFirst   = rechaninfo.DeleteFirst    = DeleteFrist;  
        rechanmsg.type = 1;

#if MESSAGE_SEND_RECEIVE_SUPPORT        

        int msgretval;                  

        msgretval = msgsnd(gmqd, (PgdatReOrderChannelMsg*)&rechanmsg, sizeof(rechanmsg.ReChanlInfo), IPC_NOWAIT);               
        retval = msgretval;
#else
        retval = ShuffleChannels(rechaninfo);                               
#endif

        /* Return to the calling thread */

    }
    else if (channel1.Channel.Digit > channel2.Channel.Digit)
    {

        PgdatReOrderChannelMsg  rechanmsg;  /* Reorder channel Message */
        ReorderChannelInfo rechaninfo;          

        /* Copy the reorder channels into the structure and Move Up because of 
           first channel present number is greather than the second channel preset number */        

        rechanmsg.ReChanlInfo.RChannel1     = rechaninfo.RChannel1      = channel1;
        rechanmsg.ReChanlInfo.RChannel2     = rechaninfo.RChannel2      = channel2;
        rechanmsg.ReChanlInfo.MoveupOrDown  = rechaninfo.MoveupOrDown   = MOVEUP;   
        rechanmsg.ReChanlInfo.DeleteFirst   = rechaninfo.DeleteFirst    = DeleteFrist;  
        rechanmsg.type = 1;

#if MESSAGE_SEND_RECEIVE_SUPPORT        

        int msgretval;      /* Send the channel information to the message queue */     

        msgretval = msgsnd(gmqd, (PgdatReOrderChannelMsg*)&rechanmsg, sizeof(rechanmsg.ReChanlInfo), IPC_NOWAIT);
        retval = msgretval;

#else
        retval = ShuffleChannels(rechaninfo);                   
#endif  

        /* Return to the calling thread */      
    }
    else
    {        
        retval = FALSE; /*both channels are same, what has to be done? doesnt mean anything */
    }  
#endif
    return retval;
}


void CHsvSatProgramData_mpgdat_Priv::UpdateAnalogOrDigitalTable(HsvPgdatPresetData presetdat)
{
    if(presetdat.Type != AppApiAnalog)
    {
        HsvPgdatDigServiceData  svcdat;                 

        ASSIGN_DIGSVC_KEYS(&svcdat, &presetdat);   

        if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
        {
            svcdat.PresetNumber = presetdat.PresetNumber;       
            ipgdb_Update(CURRENT_D_SVC_TABLE, (Address)&svcdat);        
        }       
    }
    /* This else case is not required there is no cross referencing b/w Analog Table to Preset Table */
    /*
       else
       {
       HsvPgdatAnalogData  anadat;

       ASSIGN_ANALOG_KEYS(&anadat, &presetdat);

       if(ipgdb_GetByKey(CURRENT_ANALOG_TABLE, (Address)&anadat))
       {
       TraceNotice(m,"%s %d freq %d preset %d newpreset %d", __FUNCTION__, __LINE__, anadat.Frequency, anadat.PresetNumber, presetdat.PresetNumber);
       anadat.PresetNumber = presetdat.PresetNumber;
       ipgdb_Update(CURRENT_ANALOG_TABLE, (Address)&anadat);           
       } 

       }
       */
}


void CHsvSatProgramData_mpgdat_Priv::InstalledSwap(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat)
{
    int tempPresetNumber;

    /* Both are Digital Channels */
    if ((Channel1Presetdat.Type != AppApiAnalog ) && (Channel2Presetdat.Type != AppApiAnalog ))
    {
        HsvPgdatDigServiceData  Channel1Svcdat, Channel2Svcdat;
        TraceInfo(m,"Both channels are Digital ");
        /* Get the Serices tables for presets */
        ASSIGN_DIGSVC_KEYS(&Channel1Svcdat, &Channel1Presetdat);  
        ASSIGN_DIGSVC_KEYS(&Channel2Svcdat, &Channel2Presetdat);  

        /* Detele Both Presets from the user table */
        DeletePresetTables(Channel1Presetdat, Channel2Presetdat);       

        /* Swap the presets data */
        tempPresetNumber = Channel1Presetdat.PresetNumber;
        Channel1Presetdat.PresetNumber = Channel2Presetdat.PresetNumber;
        Channel2Presetdat.PresetNumber = tempPresetNumber;

        /* Add Both Preset tables in the User table */
        InsertPresetTables(Channel1Presetdat, Channel2Presetdat);

        /* Update the Service tables */         
        UpdateServiceTable(Channel1Svcdat, Channel1Presetdat.PresetNumber); 
        UpdateServiceTable(Channel2Svcdat, Channel2Presetdat.PresetNumber);                     
    }
    /* Both are Analog */
    if ((Channel1Presetdat.Type == AppApiAnalog) && (Channel2Presetdat.Type == AppApiAnalog))
    {
        HsvPgdatAnalogData  Channel1Anadat,Channel2Anadat;
        TraceInfo(m,"Both channels are Analog ");

        /* Get the Analog tables for presets */
        ASSIGN_ANALOG_KEYS(&Channel1Anadat, &Channel1Presetdat);  
        ASSIGN_ANALOG_KEYS(&Channel2Anadat, &Channel2Presetdat);  

        /* Detele Both Presets from the user table */
        DeletePresetTables(Channel1Presetdat, Channel2Presetdat);       

        /* Swap the presets data */
        tempPresetNumber = Channel1Presetdat.PresetNumber;
        Channel1Presetdat.PresetNumber = Channel2Presetdat.PresetNumber;
        Channel2Presetdat.PresetNumber = tempPresetNumber;

        /* Add Both Preset tables in the User table */
        InsertPresetTables(Channel1Presetdat, Channel2Presetdat);

    }

    if ((Channel1Presetdat.Type != AppApiAnalog) && (Channel2Presetdat.Type == AppApiAnalog))
    {   
        HsvPgdatAnalogData  ChannelAnadat;
        HsvPgdatDigServiceData  ChannelSvcdat;
        TraceInfo(m,"first is Digital and Second is Analog ");

        /* Get the Serices tables for presets */
        ASSIGN_DIGSVC_KEYS(&ChannelSvcdat, &Channel1Presetdat);  
        /* Get the Analog tables for presets */
        ASSIGN_ANALOG_KEYS(&ChannelAnadat, &Channel2Presetdat);  

        /* Detele Both Presets from the user table */
        DeletePresetTables(Channel1Presetdat, Channel2Presetdat);       

        /* Swap the presets data */
        tempPresetNumber = Channel1Presetdat.PresetNumber;
        Channel1Presetdat.PresetNumber = Channel2Presetdat.PresetNumber;
        Channel2Presetdat.PresetNumber = tempPresetNumber;

        /* Add Both Preset tables in the User table */
        InsertPresetTables(Channel1Presetdat, Channel2Presetdat);

        /* Update the Service table and Analog tables */            
        UpdateServiceTable(ChannelSvcdat, Channel1Presetdat.PresetNumber);      
    }
    if ((Channel1Presetdat.Type == AppApiAnalog) && (Channel2Presetdat.Type != AppApiAnalog))
    {           
        HsvPgdatAnalogData  ChannelAnadat;
        HsvPgdatDigServiceData  ChannelSvcdat;
        TraceInfo(m," of first is Analog and Second is Digital ");
        /* Get the Analog tables for presets */
        ASSIGN_ANALOG_KEYS(&ChannelAnadat, &Channel1Presetdat);  
        /* Get the Serices tables for presets */
        ASSIGN_DIGSVC_KEYS(&ChannelSvcdat, &Channel2Presetdat);     

        /* Detele Both Presets from the user table */
        DeletePresetTables(Channel1Presetdat, Channel2Presetdat);       

        /* Swap the presets data */
        tempPresetNumber = Channel1Presetdat.PresetNumber;
        Channel1Presetdat.PresetNumber = Channel2Presetdat.PresetNumber;
        Channel2Presetdat.PresetNumber = tempPresetNumber;

        /* Add Both Preset tables in the User table */
        InsertPresetTables(Channel1Presetdat, Channel2Presetdat);

        /* Update the Service table and Analog tables */            
        UpdateServiceTable(ChannelSvcdat, Channel2Presetdat.PresetNumber);          
    }

}

void CHsvSatProgramData_mpgdat_Priv::DeletePresetTables(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat)
{           
    ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&Channel1Presetdat);
    ipgdb_Delete(CURRENT_PRESET_TABLE, (Address)&Channel2Presetdat);
}

void CHsvSatProgramData_mpgdat_Priv::InsertPresetTables(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat)
{
    Channel1Presetdat.UniqueNodeId  = -1;// Invalid Node id 
    Channel2Presetdat.UniqueNodeId  = -1;// Invalid Node id 
    ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&Channel1Presetdat);
    ipgdb_Add(CURRENT_PRESET_TABLE, (Address)&Channel2Presetdat);
}

void CHsvSatProgramData_mpgdat_Priv::UpdateServiceTable(HsvPgdatDigServiceData  svcdat, int PresetNumber)
{
    if(ipgdb_GetByKey(CURRENT_D_SVC_TABLE, (Address)&svcdat))
    {
        svcdat.PresetNumber = PresetNumber;     
        ipgdb_Update(CURRENT_D_SVC_TABLE, (Address)&svcdat);        
    }   
}                   


AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetSatelliteName (int LnbNumber, Nat16 *SatelliteName)
{
	return 0;
}

AppApiReturnCode CHsvSatProgramData_mpgdat_Priv::pgdat3_GetSatellitePackage (AppApiPackageId *PackageId, AppApiPackageGroup *PackageIGroupId)
{
	return 0;
}

