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
 *          %name: hsvdvbtins_mcountry.c %
 *       %version: TVG_Fusion_5 %
 * %date_modified: Fri Feb 20 20:30:33 2009 %
 *    %derived_by: nituk % 
 */

#include "_hsvdvbtins_mcountry.h"
//TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mcountry")








Nat16 CHsvDvbTInstallation_mcountry_Priv::s__RankingList_Germany[GERMAN_RANKINGLIST_SIZE] =
{
    0x000E,  // Das Erste
    0x0001,  // Das Erste
    0x0020,  // Das Erste
    0x0040,  // Das Erste
    0x0060,  // Das Erste
    0x0080,  // Das Erste
    0x00B0,  // Das Erste
    0x00D0,  // Das Erste
    0x00E0,  // Das Erste
    0x0100,  // Das Erste
    0x00A0,  // Das Erste (RB)
    0x0202,  // ZDF
    0x4018,  // Sat.1   
    0x4604,  // Sat. 1 Hamburg/Schleswig-H
    0x4681,  // SAT. 1 Hessen / Rheinland-Pfalz
    0x4603,  // Sat. 1 Niedersachsen
    0x4C81,  // SAT. 1 NRW
    0x4881,  // SAT. 1 Bayern
    0x4015,  // RTL
    0x4016,  // RTL II
    0x401B,  // Super RTL
    0x4601,  // RTL Hamburg/Schleswig-H
    0x4680,  // RTL Hessen / Rheinland-Pfalz
    0x4600,  // RTL Niedersachsen
    0x4880,  // RTL Bayern
    0x4C80,  // RTL NRW
    0x4013,  // ProSieben
    0x0002,  // Arte
    0x4022,  // VOX
    0x400A,  // Kabel 1
    0x0205,  // Doku/Kika
    0x4010,  // n-tv
    0x400E,  // N24
    0x4025,  // EURONEWS
    0x4008,  // DSF
    0x4024,  // EUROSPORT
    0x0004,  // Eins Extra
    0x0005,  // Eins Festival
    0x0006,  // Eins Muxx
    0x400C,  // MTV
    0x400D,  // MTV2 Pop
    0x4020,  // VIVA
    0x4021,  // VIVA PLUS
    0x4012,  // ONYX-TV
    0x0082,  // NDR FS HH
    0x0084,  // NDR FS MV
    0x0081,  // NDR FS NDS
    0x0083,  // NDR FS SH
    0x00A1,  // NDR FS (RB)
    0x0103,  // WDR Dortmund
    0x0104,  // WDR Düsselldorf
    0x0105,  // WDR Essen
    0x0106,  // WDR Köln
    0x0107,  // WDR Münster
    0x0108,  // WDR Siegen
    0x0109,  // WDR Wuppertal
    0x0102,  // WDR Bielefeld
    0x0101,  // WDR Aachen
    0x000F,  // WDR
    0x0064,  // MDR Fernsehen
    0x0061,  // MDR Sachsen
    0x0062,  // MDR S-Anhalt
    0x0063,  // MDR Thüringen
    0x00E1,  // Sudwest BW
    0x00E2,  // Sudwest RP
    0x0203,  // Info/3Sat
    0x00B2,  // RBB Berlin
    0x00B1,  // RBB Brandenbourg
    0x000C,  // RBB Berlin
    0x000B,  // RBB Brandenbourg
    0x0003,  // Phoenix
    0x000D,  // Phoenix
    0x0021,  // BFS Nord
    0x0022,  // BFS Süd
    0x0023,  // BR Alpha
    0x0041,  // Hessen Fernsehen
    0x0042,  // Hessen Fernsehen
    0x0043,  // Hessen Fernsehen
    0x4B00,  // Rhein-Main-TV
    0x4D80,  // Saar TV
    0x00D1,  // SR Fernsehen Südwest 
    0x4026,  // Terra Nova  
    0x4E00,  // Chemnitz Fernsehen
    0x4E01,  // Dresden Fernsehen   
    0x4E02,  // Leipzig Fernsehen
    0x4011,  // NEUN LIVE
    0x4781,  // Offener Kanal Berlin
    0x4782,  // Spreekanal
    0x4783,  // TV.BERLIN
    0x4023,  // XXP
    0x40C0,  // FAB
    0x4882,  // Franken Fernsehen
    0x4A80,  // Hamburg 1
    0x401E,  // TRT International
    0x401D,  // Tele 5
    0x401C,  // TD 1    
    0x401A,  // Sonnenklar.TV
    0x4C82,  // tv.nrw  
    0x401F,  // TW1 
    0x4E03,  // VRF Vogtland Regional FS
    0x4007,  // Deutsche Welle TV
    0x4E04,  // Euro Regional tv
    0x4800,  // RNF LIFE
    0x4004,  // Bloomberg TV
    0x4003,  // BBC World
    0x4002,  // BTV4U
    0x4005,  // CNBC Europe
    0x4006,  // CNN International
    0x4D81,  // GIGA TV
    0x4019,  // Sky News
    0x400F,  // NBC Europe
    0x400B,  // Kanal D
    0x4883,  // MFF Münchenfenster Fernsehprg.
    0x0010,  // ARD-MHP-Data
    0x4014,  // QVC
    0x4009,  // Home Shopping Europe    
    0x4017,  // RTL Shop
    0x0000   // must be last entry to delineate end of table
};


Nat16 CHsvDvbTInstallation_mcountry_Priv::s__RankingList_Austria[AUSTRIAN_RANKINGLIST_SIZE] =
{
    /* New List */
    0x2775, //ORF1
    0x2776, //ORF2W
    0x2778, //ORF2B
    0x2779, //ORF2O
    0x277B, //ORF2S
    0x277C, //ORF2T
    0x2780, //ORF2ST
    0x2784, //ORF2K
    0x2788, //ATV+/ATV
    0x278A, //ORF2N
    0x278C, //ORF2N
    0x278D, //ORF2N
    0x278F, //ORF2O
    0x2790, //ORF2V
    0x2794, //ORF2B
    0x2798, //ORF2T
    0x278B, //PULS 4
    0x2789, //PULS 4
    0x2B5E, //3SAT
    0x2C26, //3SAT
    0x2B5F, //ORF Sport Plus
    0x2C27, //ORF Sport Plus
    0x0000  // must be last entry to delineate end of table

};



HsvNITFreqList CHsvDvbTInstallation_mcountry_Priv::s__NITFreqListDesc[MAX_MUXES_PER_NTK],CHsvDvbTInstallation_mcountry_Priv::s__NITFreqListDescTmp[MAX_MUXES_PER_NTK];

int CHsvDvbTInstallation_mcountry_Priv::s__mFreqListCounter = 0;




Bool CHsvDvbTInstallation_mcountry_Priv::s__StrapiNDuringInstallation = FALSE;




FreqListPlusMux CHsvDvbTInstallation_mcountry_Priv::s__FLPlusMux[MAX_MUXES_PER_NTK];

Bool CHsvDvbTInstallation_mcountry_Priv::s__mAltFreqNetworkUpdateDetected;



/*HSVCOMPAREKEY(freqlistconf, Primary, HsvNITFreqList, Original_NetworkId)
  HSVCOMPAREKEY(freqlistconf, Secondary, HsvNITFreqList, Tsid)

  HSVCOMPAREKEY(freqlistconf, Teritiary,   HsvNITFreqList, Frequency)
  HSVCOMPAREKEY(freqlistconf, QuaternaryKey,   HsvNITFreqList,Frequency)
  */

void CHsvDvbTInstallation_mcountry_Priv::icntrypow_Init(void)
{
}

/****************************************************************************
 *Function   :
 *Description:
 *Parameters :
 *****************************************************************************/

void CHsvDvbTInstallation_mcountry_Priv::icntrypow_TurnOn(void)
{
    LoadFLPlusMux();
}

void CHsvDvbTInstallation_mcountry_Priv::LoadFLPlusMux(void)
{
    FILE* fp;
    int readrec = 0;
    char dirName[MAX_CHARACTERS];
    char PathName[MAX_CHARACTERS];
    int i=0;
    int j=0;
    int m,n = 0;

	/*ffsdir_GetDirPath( dirName, ffsdir_Boot, ffsdir_Broadcast );*/
	str_strcpy (dirName, "/user_setting/rw/tvserver/databases/channellib/");

	if(str_strlen(dirName))
	{
		str_strcpy(PathName, dirName);
		str_strcat(PathName, "/HsvNITFreqListFile");
		//PrintfNotice("%s %d dirName %s\n", __FUNCTION__, __LINE__, PathName);
		fp = fopen(PathName, "rb");

		if(fp)
		{
			//PrintfNotice("%s %d dirName %s\n", __FUNCTION__, __LINE__, PathName);
			readrec = fread((Address)(FLPlusMux), (sizeof(FLPlusMux)/MAX_MUXES_PER_NTK), MAX_MUXES_PER_NTK, fp);
                    for(m=0;m<MAX_MUXES_PER_NTK;m++)
                    {
                        for(n=0;n<MAX_NO_ALT_FREQ_PER_MUX;n++)
                        {
                            NITFreqListDesc[m].Frequency[n] = FLPlusMux[m].Frequency[n];
                        }
                        NITFreqListDesc[m].NoOfFreqs = FLPlusMux[m].NoOfFreqs;
                        NITFreqListDesc[m].Original_NetworkId = FLPlusMux[m].Original_NetworkId;
                        NITFreqListDesc[m].Tsid = FLPlusMux[m].Tsid;
                        NITFreqListDesc[m].VersionNumber = FLPlusMux[m].VersionNumber;
                    }
                    if(readrec == MAX_MUXES_PER_NTK)
                    {
                        for(i=0;i<MAX_MUXES_PER_NTK;i++)
                        {
                            //TraceDebug(m,"MUX%d",i);
                            if(NITFreqListDesc[i].Original_NetworkId != 0)
                            {
                                //TraceDebug(m,"    Onid %d Tsid %d",NITFreqListDesc[i].Original_NetworkId,NITFreqListDesc[i].Tsid);
                                for(j=0;j<NITFreqListDesc[i].NoOfFreqs;j++)
                                {
                                    //TraceDebug(m,"Freq[%d] %ld",j,NITFreqListDesc[i].Frequency[j]);
                                }
                            }
                        }
                    }
                    else
                    {
                        //TraceDebug(m,"Mohanan : read Cable Del Sys to Flash Fail with readrec : %d",readrec);
                    }
                    fclose(fp);
                }
                else
                {
                    //TraceDebug(m,"Mohanan : Unable to open %s",PathName);
                    //TraceDebug(m,"Mohanan : Unable to open NITFreqList file");
                }
            }
            else
            {
                //TraceDebug(m,"Mohanan : Boot parition mount has failed");
	}
}


/****************************************************************************
 *Function   :
 *Description:
 *Parameters :
 *****************************************************************************/

void CHsvDvbTInstallation_mcountry_Priv::icntrypow_TurnOff(void)
{
}


Nat16 * CHsvDvbTInstallation_mcountry_Priv::inscountry_GetRankingList(int Country)
{

    if (cids_CountryGermany == Country)
    {
        return (Nat16 *)RankingList_Germany;    
    }
    else
    {
        if (cids_CountryAustria == Country)
        {
            return (Nat16 *)RankingList_Austria;   
        }
        else
        {
            ASSERT(!"Country in neither Germany or Austria\n");
        }
    }
    return NULL;  
}

void CHsvDvbTInstallation_mcountry_Priv::CopyDBase()

{
    HsvNITFreqList NewDBase;
    HSVSPTYPE(FreqList, dvb, nit) FreqListDesc;
    int i,j;
    int NoOfMuxs;
    NoOfMuxs = strapi_GetSize(HsvMain, HSVSPID(FreqList, dvb, nit));

    for (i = 0;i < NoOfMuxs;i++)
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(FreqList, dvb, nit), i, (void*)(&FreqListDesc)))
        {
            //Multiply frequency by 16 to store the value directly in platform value
            NewDBase.Original_NetworkId = FreqListDesc.Original_NetworkId;
            NewDBase.Tsid = FreqListDesc.Tsid;
            NewDBase.NoOfFreqs = FreqListDesc.NoOfFreqs;
            NewDBase.VersionNumber = FreqListDesc.VersionNumber;
            for(j = 0;j < NewDBase.NoOfFreqs;j++)
            {
                NewDBase.Frequency[j] = FreqListDesc.Frequency[j];
            }


        }
        else
        {
            DEBUG_PRINT("%s %d strapi_GetByIndex failed\n", __FUNCTION__, __LINE__);
        }
    }


}

int CHsvDvbTInstallation_mcountry_Priv::afitr_GetNoOfAltFrequencies(Nat16 OnId, Nat16 TsId)
{
    int noofAltFreq = 0;
    int i=0;

    //TraceDebug(m,"Mohanan : afitr_GetNoOfAltFrequencies Onid %d Tsid %d",OnId,TsId);

    for(i=0;i<MAX_MUXES_PER_NTK;i++)
    {
        if((NITFreqListDesc[i].Original_NetworkId == OnId) && (NITFreqListDesc[i].Tsid == TsId))
        {
            noofAltFreq = NITFreqListDesc[i].NoOfFreqs;
            break;
        }
    }
    //TraceDebug(m,"Mohanan : afitr_GetNoOfAltFrequencies %d i %d",noofAltFreq,i);

    if(CABLE_MEDIUM && eurdiv_GetAltFreqScanSupported(sysset_GetInstallCountry()))
    {
        noofAltFreq = 1;
    }

    return noofAltFreq;
}

Nat32 CHsvDvbTInstallation_mcountry_Priv::afitr_GetFirstAltFrequency(Nat16 OnId, Nat16 TsId)
{
    int freq = afitr_InvalidFrequency;
    int i=0;

    //TraceDebug(m,"Mohanan : afitr_GetFirstAltFrequency Onid %d Tsid %d",OnId,TsId);

    if(CABLE_MEDIUM)
    {
        if(cdvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode) == rins_QuickScan)
        {
            //TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
            freq = cdvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);
        }
        else
        {
            //TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        }       
    }
    else
    {
        for(i=0;i<MAX_MUXES_PER_NTK;i++)
        {
            if((NITFreqListDesc[i].Original_NetworkId == OnId) && (NITFreqListDesc[i].Tsid == TsId))
            {
                freq = NITFreqListDesc[i].Frequency[0];
                break;
            }
        }
    }
    //TraceDebug(m,"Mohanan : afitr_GetFirstAltFrequency freq %d ",freq);

    return freq;
}

Nat32 CHsvDvbTInstallation_mcountry_Priv::afitr_GetNextAltFrequency(Nat16 OnId, Nat16 TsId, Nat32 Freq)
{
    int freq = afitr_InvalidFrequency;
    int i=0;
    int j=0;

    //TraceDebug(m,"Mohanan : afitr_GetNextAltFrequency Onid %d Tsid %d Freq %ld",OnId,TsId,Freq);

    if(CABLE_MEDIUM)
    {
        freq = afitr_InvalidFrequency;
    }
    else
    {
        for(i=0;i<MAX_MUXES_PER_NTK;i++)
        {
            if((NITFreqListDesc[i].Original_NetworkId == OnId) && (NITFreqListDesc[i].Tsid == TsId))
            {
                for(j=0;j<NITFreqListDesc[i].NoOfFreqs;j++)
                {
                    if(Freq == NITFreqListDesc[i].Frequency[j])
                    {
                        if(((j+1) != NITFreqListDesc[i].NoOfFreqs) && (j+1)<MAX_NO_ALT_FREQ_PER_MUX)
                        {
                            freq = NITFreqListDesc[i].Frequency[j+1];
                        }
                        break;
                    }
                }
                break;
            }
        }

    }

    //TraceDebug(m,"Mohanan : afitr_GetNextAltFrequency freq %d ",freq);

    return freq;
}

Nat32 CHsvDvbTInstallation_mcountry_Priv::afitr_GetPreviousAltFrequency(Nat16 OnId, Nat16 TsId, Nat32 Freq)
{
    int freq = afitr_InvalidFrequency;
    int i=0;
    int j=0;

    for(i=0;i<MAX_MUXES_PER_NTK;i++)
    {
        if((NITFreqListDesc[i].Original_NetworkId == OnId) && (NITFreqListDesc[i].Tsid == TsId))
        {
            for(j=0;j<NITFreqListDesc[i].NoOfFreqs;j++)
            {
                if(Freq == NITFreqListDesc[i].Frequency[j])
                {
                    if((j-1)>=0)
                    {
                        freq = NITFreqListDesc[i].Frequency[j-1];
                    }
                    break;
                }
            }
            break;
        }
    }

    //TraceDebug(m,"Mohanan : afitr_GetPreviousAltFrequency freq %d ",freq);

    return freq;
}

Nat32 CHsvDvbTInstallation_mcountry_Priv::afitr_GetLastAltFrequency(Nat16 OnId, Nat16 TsId)
{
    int freq = afitr_InvalidFrequency;
    int i=0;

    for(i=0;i<MAX_MUXES_PER_NTK;i++)
    {
        if((NITFreqListDesc[i].Original_NetworkId == OnId) && (NITFreqListDesc[i].Tsid == TsId))
        {

            freq = NITFreqListDesc[i].Frequency[NITFreqListDesc[i].NoOfFreqs -1 ];
            break;
        }
    }

    return freq;
}

void CHsvDvbTInstallation_mcountry_Priv::icctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(value);
    switch(eventid)
    {
        case icctrlN_DataAvailable:
            break;

        case icctrlN_DataNotAvailable:                   
            break;

        case icctrlN_StartedCollection:
            break;

        case icctrlN_StoppedCollection:
            break; 

        default:
            break;
    }
    UNUSED(dmx);
}


void CHsvDvbTInstallation_mcountry_Priv::cntryinsN_OnEvent ( int eventid, int value )
{
    int NoOfMuxs = strapi_GetSize(HsvMain, HSVSPID(FreqList, dvb, nit));
    if(eurdiv_FreqListDescriptorSupported(rins_GetMedium()))
    {
        switch(eventid)
        {
            case cntryinsN_EventInstallationCompleted:
                {
                    int i=0,j=0;

                    //TraceDebug(m,"Mohanan : cntryinsN_OnEvent EventInstallationCompleted value %d",value);
                    {
                        /* For some reason strapi_getsize returns 0, so have this for loop */
                        NoOfMuxs = 0;
                        for(i=0;i<MAX_MUXES_PER_NTK;i++)
                        {
                            if(NITFreqListDescTmp[i].Original_NetworkId)
                            {
                                NoOfMuxs++;
                            }
                        }
                    }
                    for(i=0;i<MAX_MUXES_PER_NTK;i++)
                    {
                        for(j=0;j<MAX_NO_ALT_FREQ_PER_MUX;j++)
                        {
                            NITFreqListDesc[i].Frequency[j] = NITFreqListDescTmp[i].Frequency[j];
                        }
                        NITFreqListDesc[i].NoOfFreqs = NITFreqListDescTmp[i].NoOfFreqs;
                        NITFreqListDesc[i].Original_NetworkId = NITFreqListDescTmp[i].Original_NetworkId;
                        NITFreqListDesc[i].Tsid = NITFreqListDescTmp[i].Tsid;
                        NITFreqListDesc[i].VersionNumber = NITFreqListDescTmp[i].VersionNumber;
                    }

                    for(i=0;i<MAX_MUXES_PER_NTK;i++)
                    {
                        for(j=0;j<MAX_NO_ALT_FREQ_PER_MUX;j++)
                        {
                            FLPlusMux[i].Frequency[j] = NITFreqListDesc[i].Frequency[j];
                        }
                        FLPlusMux[i].NoOfFreqs = NITFreqListDesc[i].NoOfFreqs;
                        FLPlusMux[i].Original_NetworkId = NITFreqListDesc[i].Original_NetworkId;
                        FLPlusMux[i].Tsid = NITFreqListDesc[i].Tsid;
                        FLPlusMux[i].VersionNumber = NITFreqListDesc[i].VersionNumber;
                        FLPlusMux[i].NoOfMuxs = NoOfMuxs;
                    }
                    WriteIntoFlash();
                    mFreqListCounter = 0;
                    mAltFreqNetworkUpdateDetected = FALSE;
                    StrapiNDuringInstallation = FALSE;
                }
                break;
            case cntryinsN_EventInstallationStarted:
                mFreqListCounter = 0;
                StrapiNDuringInstallation = TRUE;
                break;
            case cntryinsN_EventInstallationStopped:
                mAltFreqNetworkUpdateDetected = FALSE;
                StrapiNDuringInstallation = FALSE;
                mFreqListCounter = 0;
                break;
            default:
                break;
        }
    }

}

void CHsvDvbTInstallation_mcountry_Priv::icntrystrapiN_OnCompleted( HsvDestination dest, int spid)
{
    UNUSED(dest);
    if(spid == HSVSPID(FreqList, dvb, nit))
    {
        int NoOfMuxs = strapi_GetSize(HsvMain, HSVSPID(FreqList, dvb, nit));
        int i=0;
        int j=0;
        HsvNITFreqList tmplist;
        Bool NewOnidTsidPair = TRUE;

        //TraceDebug(m,"Mohanan : icntrystrapiN_OnCompleted for freq_list NoOfMuxs %d mFreqListCounter %d",NoOfMuxs,mFreqListCounter);

        if(NoOfMuxs)
        {
            int tmp_cnt = 0;
            Nat32 tmp_freq = 0;
            Bool add_freq = TRUE;
            int k = 0;
            int l = 0;
            int m = 0;
            if(mFreqListCounter == 0)
            {
                for(i=0;i<MAX_MUXES_PER_NTK;i++)
                {
                    NITFreqListDescTmp[i].Original_NetworkId = 0;
                    NITFreqListDescTmp[i].Tsid = 0;
                    NITFreqListDescTmp[i].NoOfFreqs = 0;
                    for(j=0;j<MAX_NO_ALT_FREQ_PER_MUX;j++)
                    {
                        NITFreqListDescTmp[i].Frequency[j] = 0;
                    }
                    NITFreqListDescTmp[i].VersionNumber = 0;
                }
            }
            for(i=0;i<NoOfMuxs;i++)
            {
                if(strapi_GetByIndex(HsvMain, HSVSPID(FreqList, dvb, nit), i, (void*)&tmplist))
                {
                    for(k=0;k<mFreqListCounter;k++)
                    {
                        if((tmplist.Original_NetworkId == NITFreqListDescTmp[k].Original_NetworkId) && (tmplist.Tsid == NITFreqListDescTmp[k].Tsid))
                        {
                            if(tmplist.VersionNumber == NITFreqListDescTmp[k].VersionNumber)
                            {

                                tmp_cnt = NITFreqListDescTmp[k].NoOfFreqs;
                                tmp_freq = 0;
                                add_freq = TRUE;
                                for(m=0;m<tmplist.NoOfFreqs;m++)
                                {
                                    tmp_freq = tmplist.Frequency[m];
                                    for(l=0;l<tmp_cnt;l++)
                                    {
                                        if(NITFreqListDescTmp[k].Frequency[l] == tmp_freq)
                                        {
                                            add_freq = FALSE;
                                        }
                                    }
                                    if(add_freq)
                                    {
                                        ////TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);    
                                        NITFreqListDescTmp[k].Frequency[tmp_cnt++] = tmp_freq;
                                    }
                                    if(tmp_cnt >= MAX_NO_ALT_FREQ_PER_MUX)
                                    {
                                        //  //TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
                                        break;
                                    }
                                }
                                NewOnidTsidPair = FALSE;
                            }
                        }
                    }
                }
                if(NewOnidTsidPair && (mFreqListCounter < MAX_MUXES_PER_NTK))
                {
                    //TraceDebug(m,"MUX%d",mFreqListCounter);
                    if(strapi_GetByIndex(HsvMain, HSVSPID(FreqList, dvb, nit), i, (void*)(&NITFreqListDescTmp[mFreqListCounter])))
                    {
                        //TraceDebug(m,"Onid %d Tsid %d",NITFreqListDescTmp[mFreqListCounter].Original_NetworkId,NITFreqListDescTmp[mFreqListCounter].Tsid);
                        for(j=0;j<NITFreqListDescTmp[mFreqListCounter].NoOfFreqs;j++)
                        {
                            //TraceDebug(m,"    Freq[%d] %ld",j,NITFreqListDescTmp[mFreqListCounter].Frequency[j]);
                        }
                    }
                    mFreqListCounter++;
                }
            }
        }

        if(!StrapiNDuringInstallation)
        {
            if(!CompareAndUpdateAltFrequency())
            {
                WriteIntoFlash();
            }

            mFreqListCounter = 0;//correct ? reset for every notification if InstallNotInProgress
            for(i=0;i<MAX_MUXES_PER_NTK;i++)
            {

                if(NoOfMuxs > FLPlusMux[i].NoOfMuxs)
                {
                    // To set a flag to perform an update installation when the no of muxs have increased
                    // This function was borrowed from the previous assumption that when there is a freq list change an update installation should be triggered
                    if((sysset_GetSystemCountry() == cids_CountryNorway)||(sysset_GetSystemCountry() == cids_CountryNewZealand))//APMEA
                    {
                        mAltFreqNetworkUpdateDetected = TRUE;
                        insN_OnEvent(insN_EventNetworkUpdateDetected, TRUE);
                    }
                    break;
                }
            }
        }
    }
}

void CHsvDvbTInstallation_mcountry_Priv::icntrystrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbTInstallation_mcountry_Priv::icntrystrapiN_OnChanged( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);
}

void CHsvDvbTInstallation_mcountry_Priv::icntrystrapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);

}

void CHsvDvbTInstallation_mcountry_Priv::WriteIntoFlash(void)
{
    FILE* fp;
    int writtenrec = 0;
    char dirName[MAX_CHARACTERS];
    char PathName[MAX_CHARACTERS];

	str_strcpy (dirName, "/user_setting/rw/tvserver/databases/channellib/");
	if(str_strlen(dirName))
	{
		str_strcpy(PathName, dirName);
		str_strcat(PathName, "/HsvNITFreqListFile");
		//PrintfNotice("%s %d dirName %s\n", __FUNCTION__, __LINE__, PathName);
		fp = fopen(PathName, "wb");

                //TraceDebug(m,"Mohanan : File to write %s",PathName);

                if(fp)
                {
                    writtenrec = fwrite((Address)(FLPlusMux), (sizeof(FLPlusMux)/MAX_MUXES_PER_NTK), MAX_MUXES_PER_NTK, fp);
                    if(writtenrec == MAX_MUXES_PER_NTK)
                    {
                        //TraceDebug(m,"Mohanan : FLPlusMux written successfully %d %d ",writtenrec,sizeof(FLPlusMux));
                    }
                    else
                    {
                        //TraceDebug(m,"Mohanan : FLPlusMux written failed %d %d ",writtenrec,sizeof(FLPlusMux));
                    }
                    fclose(fp);
                }
                else
                {
                    DEBUG_PRINT("%s %d Unable to open %s\n", __FUNCTION__, __LINE__, PathName);
                    //TraceDebug(m,"Unable to open FLPlusMux file");
		}
	}
	else
	{
		ASSERT(!"Boot parition mount has failed");
	}
}

Bool CHsvDvbTInstallation_mcountry_Priv::CompareAndUpdateAltFrequency(void) /* returns true if same, hence no flash update */
{
    Bool retval = TRUE;
    int i = 0;
    int j = 0;
    int k = 0;

    //TraceDebug(m,"hsvdvbtins : CompareAndUpdateAltFrequency mFreqListCounter %d",mFreqListCounter);

    for(i=0;i<mFreqListCounter;i++)
    {
        for(k=0;k<MAX_MUXES_PER_NTK;k++)
        {

            if( (NITFreqListDescTmp[i].Original_NetworkId == NITFreqListDesc[k].Original_NetworkId)
                    &&(NITFreqListDescTmp[i].Tsid == NITFreqListDesc[k].Tsid)
              )
            {
                break;
            }
        }

        if(k != MAX_MUXES_PER_NTK)
        {
            //TraceDebug(m,"hsvdvbtins : new ver no %d old no %d",NITFreqListDescTmp[i].VersionNumber, NITFreqListDesc[k].VersionNumber);

            if(NITFreqListDescTmp[i].VersionNumber != NITFreqListDesc[k].VersionNumber)
            {
                for(j=0;j<MAX_NO_ALT_FREQ_PER_MUX;j++)
                {
                    NITFreqListDesc[k].Frequency[j] = NITFreqListDescTmp[i].Frequency[j];
                    FLPlusMux[k].Frequency[j] = NITFreqListDescTmp[i].Frequency[j];
                }
                NITFreqListDesc[k].NoOfFreqs = NITFreqListDescTmp[i].NoOfFreqs;
                FLPlusMux[k].NoOfFreqs = NITFreqListDescTmp[i].NoOfFreqs;

                NITFreqListDesc[k].VersionNumber = NITFreqListDescTmp[i].VersionNumber;
                FLPlusMux[k].VersionNumber = NITFreqListDescTmp[i].VersionNumber;
                retval = FALSE;
            }
        }
    }

    return retval;
}

#if 0

void CHsvDvbTInstallation_mcountry_Priv::afscanN_OnAltFrequencyScanCompleted(int Status)
{
    if(Status == afscanN_StatusSignalFound)
    {
        DEBUG_PRINT("%s %d\n", __FUNCTION__, __LINE__);
        if(sysset_GetSystemCountry() == cids_CountryNorway)
        {
            mAltFreqNetworkUpdateDetected = TRUE;
            insN_OnEvent(insN_EventNetworkUpdateDetected, TRUE);
        }
    }
}
#endif


Bool CHsvDvbTInstallation_mcountry_Priv::afitr_IsNetworkUpdateDetected()
{
    Bool retval = FALSE;

    if(sysset_GetSystemCountry() == cids_CountryNorway)
    {
        retval = mAltFreqNetworkUpdateDetected;
    }
    DEBUG_PRINT("%s %d retval %d\n", __FUNCTION__, __LINE__, mAltFreqNetworkUpdateDetected);
    return retval;
}




Nat8 CHsvDvbTInstallation_mcountry_Priv::freqlistconf_ComparePrimaryKey   (Nat32 Key, Address data) 
{
	return 0;
}

Nat8 CHsvDvbTInstallation_mcountry_Priv::freqlistconf_CompareSecondaryKey (Nat32 Key, Address data) 
{
	return 0;
}

Nat8 CHsvDvbTInstallation_mcountry_Priv::freqlistconf_CompareTeritiaryKey (Nat32 Key, Address data) 
{
	return 0;
}

Nat8 CHsvDvbTInstallation_mcountry_Priv::freqlistconf_CompareQuaternaryKey(Nat32 Key, Address data) 
{
	return 0;
}