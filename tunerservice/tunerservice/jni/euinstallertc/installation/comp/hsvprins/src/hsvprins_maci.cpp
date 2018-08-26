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
 *    %name: hsvprins_maci.c %
 *    %version: TVG_tv550r4dev1_3 %
 *    %date_modified: Tue May 06 09:49:22 2008 %
 *    %derived_by: vijayan %
 */

#include "_hsvprins_maci.h"

TRACESYMBOL(m, "analog/installation/hsvprins_maci")

#include "hsvprins.h"





/****************************************************
 * function to convert aci system to tv system
 ****************************************************/
void CHsvPresetInstallation_maci_Priv::ConvertAcisystemToTvsystem( HsvAciSystem acisys ,tmFe_TvSystem_t *tvsystem, Nat8 *colsystem)
{
    switch( acisys )
    {
        case AciSystemPalSecamBg:           
            *tvsystem = HsvInsTvSystemBg;           
            if( sysset_GetSystemCountry() == cids_CountryFrance )
            {
                *colsystem = col_Secam;
            }
            else
            {
                *colsystem = col_Pal;
            }
            break;
        case AciSystemSecamL:
            *tvsystem = HsvInsTvSystemL;            
            *colsystem = col_Secam;
            break;
        case AciSystemPalM:
            *tvsystem = HsvInsTvSystemM;            
            *colsystem = col_Pal;
            break;
        case AciSystemNtscM:
            *tvsystem = HsvInsTvSystemM;            
            *colsystem = col_Ntsc;
            break;
        case AciSystemPalI:
            *tvsystem = HsvInsTvSystemI;            
            *colsystem = col_Pal;
            break;
        case AciSystemSecamDk:
            *tvsystem = HsvInsTvSystemDk;           
            *colsystem = col_Secam;
            break;
        default:
            ASSERT( !"Invalid aci tvsystem");
            break;
    }
}

HsvAciLanguage CHsvPresetInstallation_maci_Priv::acidat_GetAciLanguage( int language )
{
    HsvAciLanguage opLanguage;

    switch(language)
    {
        case  lngids_LangEnglish : 
            opLanguage = AciLanguageEnglish;
            break;
        case  lngids_LangFrench : 
            opLanguage = AciLanguageFrench;
            break;
        case  lngids_LangSpanish : 
            opLanguage = AciLanguageSpanish;
            break;
        case  lngids_LangArabic : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangBrazilianPortuguese : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangCzech : 
            opLanguage = AciLanguageCzech;
            break;
        case  lngids_LangDanish : 
            opLanguage = AciLanguageDanish;
            break;
        case  lngids_LangDutch : 
            opLanguage = AciLanguageDutch;
            break;
        case  lngids_LangFinnish : 
            opLanguage = AciLanguageFinnish;
            break;
        case  lngids_LangGerman : 
            opLanguage = AciLanguageGerman;
            break;
        case  lngids_LangGreek : 
            opLanguage = AciLanguageGreek;
            break;
        case  lngids_LangHungal : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangHungarian : 
            opLanguage = AciLanguageHungarian;
            break;
        case  lngids_LangItalian : 
            opLanguage = AciLanguageItalian;
            break;
        case  lngids_LangLatinspanish : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangMalay : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangNorwegian : 
            opLanguage = AciLanguageNorwegian;
            break;
        case  lngids_LangPersian : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangPolish : 
            opLanguage = AciLanguagePolish;
            break;
        case  lngids_LangPortuguese : 
            opLanguage = AciLanguagePortuguese;
            break;
        case  lngids_LangRussian : 
            opLanguage = AciLanguageRussian;
            break;
        case  lngids_LangSimplifiedchinese : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangSlovak : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangSwedish : 
            opLanguage = AciLanguageSwedish ;
            break;
        case  lngids_LangTaiwanese : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangTurkish : 
            opLanguage = AciLanguageTurkish;
            break;
        case  lngids_LangSerbian : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangRomanian : 
            opLanguage = AciLanguageRomanian;
            break;
        case  lngids_LangCroatian : 
            opLanguage = AciLanguageInvalid;
            break;
        case  lngids_LangSlovenian : 
            opLanguage = AciLanguageInvalid;
            break;
        default : 
            ASSERT(!"Invalid aci language");
            opLanguage = AciLanguageInvalid;
            break;
    }
    return opLanguage;
}

/******************* With the new pgdat, the following is mechanism to update pgdat***********************/
/*      Declare pgdat structure
        Reset Structure
        Assign a preset and also the values to store
        Get the preset from the database 
        If can  get ( the correct values will be present in the pgdat)
        Update the database
        If cant get ( the new values will not be deleted )
        Insert the database
        */

void CHsvPresetInstallation_maci_Priv::Store(Nat16 tableid , HsvPgdatAnalogData* pstruct)
{
	 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__);

    if( TRUE == pgdb_GetByKey(tableid, (Address)pstruct) )
    {
	 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__);
        pgdb_Update (tableid, (Address)pstruct);
    }
    else
    {
	 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__);
        sort_AddAnalogPreset((Address)pstruct);
    }           
}

void CHsvPresetInstallation_maci_Priv::acidat_StorePreset (HsvAciSingleInfo presetInfo ,Bool clear)
{
    Int32           freq;
    tmFe_TvSystem_t tvSys = 0;
    Nat8            j;
    HsvChannel      prNo;
    char            channelName[div_PresetNameLength+1];
    Nat8            colSys = 0;
    Bool            installed = FALSE;
    prNo.Type = HsvAnalog;
    prNo.Channel.AnalogNo = presetInfo.presetNo;
	 TraceDebug(m," Hsvprins : %s %d  hsvprins: presetInfo.presetNo = %d ",__FUNCTION__,__LINE__, presetInfo.presetNo );

    if(clear == FALSE)
    {
        freq = presetInfo.frequency;
        ConvertAcisystemToTvsystem((HsvAciSystem)presetInfo.aciSystem,&tvSys,&colSys);
        for (j = 0; j<PRESETNAMELENGTH; j++)
        {
            channelName[j] = presetInfo.channelName[j];
        }

	 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__ );

        installed = sort_IsPresetInstalled(freq);

        if(!installed)
        {
            HsvPgdatAnalogData anadat;          
            pgdb_Initialise (pgdbconst_Analog, (Address) (&anadat));
            anadat.PresetNumber =   prNo.Channel.AnalogNo;
            anadat.Frequency    =   (freq * 1000) / 16;
            anadat.ModulationType     =   tvSys;
            anadat.ColourSystem =   colSys;
            anadat.DecoderType  =   0;
            anadat.Tuned        =   TRUE;
            //ToAddNullCharacter(channelName);
			/*TODO: check is this can be removed as ExtChannelName and ChannelVirgin are removed from HsvPgdatAnalogData*/
            memo_memcpy (anadat.ChannelName, instutil_AsciiToUnicode(channelName, PRESENT_NAMELENGTH_ANALOG), div_PresetNameLength * 2);
            //anadat.ChannelVirgin=   FALSE;
            anadat.DeTuned      =   TRUE;
            anadat.Attenuator   =   FALSE;
				 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__ );
	 TraceDebug(m," Hsvprins : %s %d PresetNumber= %d  ",__FUNCTION__,__LINE__,prNo.Channel.AnalogNo );
	 TraceDebug(m," Hsvprins : %s %d  Freq = %d ",__FUNCTION__,__LINE__ ,freq);

            Store( ANALOGUE_TABLE, &anadat);
        }
    }
    else   
    {
		 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__ );

        if(prNo.Channel.AnalogNo != 0)                          /* dont clear preset 0, if not present in transmission */
        {
            HsvPgdatAnalogData anadat;
		 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__ );

            pgdb_Initialise (pgdbconst_Analog, (Address)&anadat);
            /*            if( sysset_GetSystemCountry() == cids_CountryFrance ) */
            if ( (div_AnalogInstallationSequence == div_SecamPal) ||
                    (div_AnalogInstallationSequence == div_SecamOnly) )
            {
                anadat.PresetNumber =   prNo.Channel.AnalogNo;
                anadat.ModulationType     =   (Nat8)tmFe_TvSystemL;
						 TraceDebug(m," Hsvprins : %s %d   ",__FUNCTION__,__LINE__ );

                Store( ANALOGUE_TABLE, &anadat);
            }
        }
    }
}

