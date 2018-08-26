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
 *          %name: hsvpgdat_include.h %
 *       %version: cltv1_TV550R4_5 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nituk % 
 */


FLASH_ITEM(0, ipgdbconst_Preset                ,srtdbids_UserTable     ,"AntennaPresetTable"    ,"CablePresetTable", "AntennaPresetTableBak"    ,"CablePresetTableBak",   div_PrimaryFileVersion, div_SecondaryFileVersion, HsvPgdatPresetData       ,DefaultPresetValues, UserTableconf_MaxElements      ,UserTableconf_ElementSize		)
FLASH_ITEM(1, ipgdbconst_Analog                ,srtdbids_AnalogTable   ,"AntennaAnalogTable"    ,"CableAnalogTable", "AntennaAnalogTableBak"    ,"CableAnalogTableBak",	  div_PrimaryFileVersion, div_SecondaryFileVersion, HsvPgdatAnalogData       ,DefaultAnalogValues, AnalogTableconf_MaxElements    ,AnalogTableconf_ElementSize	)
FLASH_ITEM(2, ipgdbconst_DigitalService        ,srtdbids_DigSrvcTable  ,"AntennaDigSrvTable"    ,"CableDigSrvTable", "AntennaDigSrvTableBak"    ,"CableDigSrvTableBak",   div_PrimaryFileVersion, div_SecondaryFileVersion, HsvPgdatDigServiceData   ,DefaultDigSvcValues, DigSrvcTableconf_MaxElements   ,DigSrvcTableconf_ElementSize	)
FLASH_ITEM(3, ipgdbconst_FrequencyMapTable     ,srtdbids_FreqMapTable  ,"AntennaFrqMapTable"    ,"CableFrqMapTable", "AntennaFrqMapTableBak"    ,"CableFrqMapTableBak",   div_PrimaryFileVersion, div_SecondaryFileVersion, HsvPgdatDigFreqMapData   ,DefaultFrqMapValues, FreqMapTableconf_MaxElements   ,FreqMapTableconf_ElementSize	)
FLASH_ITEM(4, ipgdbconst_DigitalTS             ,srtdbids_DigTSTable    ,"AntennaDigTSTable"     ,"CableDigTSTable",  "AntennaDigTSTableBak"     ,"CableDigTSTableBak",    div_PrimaryFileVersion, div_SecondaryFileVersion, HsvPgdatDigTSData		   ,DefaultDigTSValues,  DigTSTableconf_MaxElements		,DigTSTableconf_ElementSize		)
#ifndef RAM_ITEM
#define  RAM_ITEM(idx, pgdbtid, srttid, type, def_val, me, es)
#endif

RAM_ITEM(5, ipgdbconst_CurrentDigitalService	,srtdbids_CurrentDigSrvcTable  ,HsvPgdatDigServiceData	,DefaultDigSvcValues	,CurrDigSrvcTableconf_MaxElements   ,CurrDigSrvcTableconf_ElementSize	)
RAM_ITEM(6, ipgdbconst_CurrentDigitalTS		,srtdbids_CurrentDigTSTable		   ,HsvPgdatDigTSData		,DefaultDigTSValues		,CurrDigTSTableconf_MaxElements     ,CurrDigTSTableconf_ElementSize		)
