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
 *          %name: hsveuins_madvpgitr.c %
 *       %version: TVG_tv550r4dev1 %
 * %date_modified: Tue Apr 07 11:24:33 2009 %
 *    %derived_by: vijayan % 
 */

/****************************************************************************
  1.pvn: handle installation states correctly with dvbc coming into picture
  2.
 ****************************************************************************/

/****************************************************************************
 * Local include files
 ****************************************************************************/

#include "_hsveuins_madvpgitr.h"

TRACESYMBOL(m, "zap/pgitr/hsveuins_madvpgitr")

/*************************************************************************************************
  MACRO DEFINITION
 *************************************************************************************************/

//#define GET_USER_TABLE_ID(tableId) (((tableId == pgdbconst_Antenna) || (tableId == pgdbconst_Cable)) ? srtdbids_UserTable : -1)

FResult CHsvEuropeInstallation_madvpgitr_Priv::iadvpgitr_GetNoOfChannels( int *noofchannels,Bool IsAnalog)               
{

    FResult retval = apperr_Ok;    
    int numRecords = 0;
    int ChannelCount = 0;
    int index = 0;
    HsvPgdatPresetData tempList;
    HsvChannel  tempchannellist;


    *noofchannels = 0;
    //UsrTableId = GET_USER_TABLE_ID(pgdb_GetCurrentTable());
    //UsrTableId = pgdb_GetCurrentTable();

    numRecords = pgdb_GetNoRecords(PRESET_TABLE);//srtdb_GetNoOfRecords(UsrTableId);

    for(index= 0; index < numRecords ; index ++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, index, (Address)&tempList)) 
        {      
            tempchannellist.Type = (AppApiChannelType)tempList.Type;
            if((IsAnalog) ? IS_ANALOG((&tempchannellist)) : IS_DIGITAL((&tempchannellist)))
            {
                ChannelCount++;
            }            
        }
    }    
    *noofchannels = ChannelCount; 
    return retval;   

}

FResult CHsvEuropeInstallation_madvpgitr_Priv::iadvpgitr_GetFirstChannel(HsvChannel *channelno, Bool IsAnalog)
{
    FResult retval = apperr_ChannelTableEmpty;
    int numRecords = 0;
    int index = 0;
    HsvPgdatPresetData tempList;
    HsvChannel  tempchannellist;

    numRecords = pgdb_GetNoRecords(PRESET_TABLE);//srtdb_GetNoOfRecords(UsrTableId);
    for(index= numRecords; index > 0 ; index --)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, index, (Address)&tempList)) 
        {      
            tempchannellist.Type = (AppApiChannelType)tempList.Type;
            if((IsAnalog) ? IS_ANALOG((&tempchannellist)) : IS_DIGITAL((&tempchannellist)))
            {
				channelno->Type = (IsAnalog) ? HsvAnalog : HsvOnePart;
				channelno->Channel.Digit = tempList.PresetNumber;
				retval = apperr_Ok;
				break;
            }            
        }
    }

    return retval;
}

FResult CHsvEuropeInstallation_madvpgitr_Priv::iadvpgitr_GetLastChannel(HsvChannel *channelno,Bool IsAnalog )
{
    FResult retval = apperr_ChannelTableEmpty;
    int numRecords = 0;
    int index = 0;
    HsvPgdatPresetData tempList;
    HsvChannel  tempchannellist;

    numRecords = pgdb_GetNoRecords(PRESET_TABLE);//srtdb_GetNoOfRecords(UsrTableId);
    for(index= 0; index < numRecords ; index ++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, index, (Address)&tempList)) 
        {      
            tempchannellist.Type = (AppApiChannelType)tempList.Type;
            if((IsAnalog) ? IS_ANALOG((&tempchannellist)) : IS_DIGITAL((&tempchannellist)))
            {
				channelno->Type = (IsAnalog) ? HsvAnalog : HsvOnePart;
				channelno->Channel.Digit = tempList.PresetNumber;
				retval = apperr_Ok;
				break;
            }            
        }
    }

    return retval;
}

FResult CHsvEuropeInstallation_madvpgitr_Priv::iadvpgitr_GetNextChannel(HsvChannel *channelno, Bool IsAnalog )
{
    FResult retval = apperr_ChannelTableEmpty;
    int numRecords = 0;
    int index = 0;
    HsvPgdatPresetData tempList;
    HsvChannel  tempchannellist;

    numRecords = pgdb_GetNoRecords(PRESET_TABLE);//srtdb_GetNoOfRecords(UsrTableId);
	
	tempList.PresetNumber = channelno->Channel.Digit;
	if (pgdb_GetIndex (PRESET_TABLE,&index, (Address)&tempList) == TRUE)
	{
		for(index; index >= 0; index--)
		{
			if(pgdb_GetByIndex(PRESET_TABLE, index, (Address)&tempList)) 
			{      
				tempchannellist.Type = (AppApiChannelType)tempList.Type;
				if((IsAnalog) ? IS_ANALOG((&tempchannellist)) : IS_DIGITAL((&tempchannellist)))
				{
					channelno->Type = (IsAnalog) ? HsvAnalog : HsvOnePart;
					channelno->Channel.Digit = tempList.PresetNumber;
					retval = apperr_Ok;
					break;
				}            
			}
		}
    }

    return retval;
}

FResult CHsvEuropeInstallation_madvpgitr_Priv::iadvpgitr_GetPreviousChannel(HsvChannel *channelno, Bool IsAnalog )
{
    FResult retval = apperr_ChannelTableEmpty;
    int numRecords = 0;
    int index = 0;
    HsvPgdatPresetData tempList;
    HsvChannel  tempchannellist;

    numRecords = pgdb_GetNoRecords(PRESET_TABLE);//srtdb_GetNoOfRecords(UsrTableId);
	
	tempList.PresetNumber = channelno->Channel.Digit;
	if (pgdb_GetIndex (PRESET_TABLE,&index, (Address)&tempList) == TRUE)
	{
		for(index; index < numRecords ; index++)
		{
			if(pgdb_GetByIndex(PRESET_TABLE, index, (Address)&tempList)) 
			{      
				tempchannellist.Type = (AppApiChannelType)tempList.Type;
				if((IsAnalog) ? IS_ANALOG((&tempchannellist)) : IS_DIGITAL((&tempchannellist)))
				{
					channelno->Type = (IsAnalog) ? HsvAnalog : HsvOnePart;
					channelno->Channel.Digit = tempList.PresetNumber;
					retval = apperr_Ok;
					break;
				}            
			}
		}
    }

    return retval;
}

