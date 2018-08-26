 /*****************************************************************************************
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
 *
 *  This	source code and any compilation or derivative thereof is the proprietary
 *  information of Koninklijke Philips Electronics N.V. and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed under an Open
 *  Source License of any type without the expressed written permission of Koninklijke
 *  Philips Electronics N.V.
 *
 *  %name: hsvdvbnit_m.cpp %
 *  %version:  TVG_Android_1 %
 *  %date_modified:  %
 *  %derived_by:    Anu Mary %
 *
 *****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "_hsvdvbcamnit_m.h"

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/
TRACESYMBOL(m, "dvb/sitables/hsvdvbcamnit_m")

#ifndef __cplusplus

#else

#endif

/*****************************************************************************************
 * Static variables
 *****************************************************************************************/
Bool CHsvDvbCamNIT_Priv::s__mActive = FALSE;
Nat8 CHsvDvbCamNIT_Priv::s__mBuffer[4*1024];
Nat8 CHsvDvbCamNIT_Priv::s__mCamCharCode = 0;
Bool CHsvDvbCamNIT_Priv::s__mPrevPrivateDataSpecifierPresent = FALSE;
TypeCamNitParser CHsvDvbCamNIT_Priv::s__CamNitParser;
Nat32 mCookie = 0;


/*****************************************************************************************
 * Static Functions /Private Methods
 *****************************************************************************************/

/*****************************************************************************************
 * Keys definition for the sorted table data
 *****************************************************************************************/
HSVCOMPAREKEY(camnitsatellitedsconf, Primary,    HsvNITSatelliteDS, Original_NetworkId)

HSVCOMPAREKEY(camnitsatellitedsconf, Secondary,  HsvNITSatelliteDS, Tsid)

HSVCOMPAREKEY(camnitsatellitedsconf, Teritiary,  HsvNITSatelliteDS, NetworkId)

HSVCOMPAREKEY(camnitsatellitedsconf, Quaternary, HsvNITSatelliteDS, NetworkId)



HSVCOMPAREKEY(optunesatellitedsconf, Primary,    HsvNITSatelliteDS, Frequency)

HSVCOMPAREKEY(optunesatellitedsconf, Secondary,  HsvNITSatelliteDS, Polarization)

HSVCOMPAREKEY(optunesatellitedsconf, Teritiary,  HsvNITSatelliteDS, NetworkId)

HSVCOMPAREKEY(optunesatellitedsconf, Quaternary, HsvNITSatelliteDS, NetworkId)

HSVCOMPAREKEY(camnitcontentlabelconf, Primary,    HsvCamNITContentLabel, ContentByteMin)

HSVCOMPAREKEY(camnitcontentlabelconf, Secondary,  HsvCamNITContentLabel, ContentByteMax)

HSVCOMPAREKEY(camnitcontentlabelconf, Teritiary,  HsvCamNITContentLabel, ISO_639_Language_Code)

HSVCOMPAREKEY(camnitcontentlabelconf, Quaternary, HsvCamNITContentLabel, ContentByteMax)


HSVCOMPAREKEY(camnitserviceconf, Primary,    HsvCamNITService, OriginalNetworkId)

HSVCOMPAREKEY(camnitserviceconf, Secondary,  HsvCamNITService, TsId)

HSVCOMPAREKEY(camnitserviceconf, Teritiary,  HsvCamNITService, ServiceId)

HSVCOMPAREKEY(camnitserviceconf, Quaternary, HsvCamNITService, LogicalChannelNumber)


HSVCOMPAREKEY(camnitlinkageinfoconf, Primary,    HsvCamNITLinkageInfo,  Original_NetworkId)

HSVCOMPAREKEY(camnitlinkageinfoconf, Secondary,  HsvCamNITLinkageInfo,  Tsid)

HSVCOMPAREKEY(camnitlinkageinfoconf, Teritiary,  HsvCamNITLinkageInfo,  LinkageType)

HSVCOMPAREKEY(camnitlinkageinfoconf, Quaternary, HsvCamNITLinkageInfo,  LinkageType)


/*****************************************************************************************
 * Init Functions
 *****************************************************************************************/
void CHsvDvbCamNIT_Priv::mInitCamNitSatelliteDS(void)
{
    srtdb_Init(srtdbids_CamNitSatelliteDS);
}

void CHsvDvbCamNIT_Priv::mInitOpTuneSatelliteDS(void)
{
    srtdb_Init(srtdbids_OpTuneSatelliteDS);
}

void CHsvDvbCamNIT_Priv::mInitCamNitContentLabel(void)
{
    srtdb_Init(srtdbids_CamNitContentLabel);
}

void CHsvDvbCamNIT_Priv::mInitCamNitService(void)
{
    srtdb_Init(srtdbids_CamNitService);
}

void CHsvDvbCamNIT_Priv::mInitCamNitLinkageInfo(void)
{
    srtdb_Init(srtdbids_CamNitLinkageInfo);
}


/*****************************************************************************************
 * Interpret Data Functions
 *****************************************************************************************/
int CHsvDvbCamNIT_Priv::ConvertBcdToDecimal (int bcdvalue)
{
    Nat32 nibble;
    Nat32 decimalval = 0;
    Nat8 count = 0;

    while (count < 8)
    {
        count++;
        nibble = (bcdvalue  & 0xF0000000) >> 28;
        decimalval = (decimalval * 10) + nibble;
        bcdvalue <<= 4;
    }

    return decimalval;
}

int CHsvDvbCamNIT_Priv::MapModulationType (Nat8 modln)
{
    Nat8 retval = -1;

    switch (modln)
    {
        case 0:
            /* Auto */
            break;
        case 1:
            retval = 1;
            break;
        case 2:
            retval = 2;
            break;
        case 3:
            /* Auto */
            break;
    }
    return retval;
}

Nat8 CHsvDvbCamNIT_Priv::MapFECInner (Nat8 fec)
{
    Nat8 retval = 1;

    switch(fec)
    {
        case 1:
             retval = 1;
             break;
        case 2:
            retval = 2;
            break;
        case 3:
            retval = 3;
            break;
        case 4:
            retval = 5;
            break;
        case 5:
            retval = 6;
            break;
        case 6:
            retval = 7;
            break;
        case 7:
            retval = 12;
            break;
        case 8:
            retval = 4;
            break;
        case 9:
            retval = 8;
            break;
        case 10:
            retval = 12;
            break;
    }

    return retval;
}

Nat8 CHsvDvbCamNIT_Priv::MapPolarization (Nat8 pol)
{
    Nat8 retval = 1;

    //retval = (pol == 0) ? 1 : 2;

    switch(pol)
    {
        case 0:
        case 2: 
            retval = 0;     // h/l
            break;
        case 1:
        case 3: 
            retval = 1;     // v/r
            break;
    }
    return retval;
}

int CHsvDvbCamNIT_Priv::MapModulationStd (Nat8 modlnstd)
{
    return ((modlnstd == 0)  ?  1 : 2);    //1. DVBS 2. DVBS2
}


/*  
    From ETSI EN 300 468, table A3 (single byte character table codes):
    0x01 = ISO 8859-5
    0x02 = ISO 8859-6
    0x03 = ISO 8859-7
    0x04 = ISO 8859-8
    0x05 = ISO 8859-9
    0x06 = ISO 8859-10
    0x07 = ISO 8859-11
    0x09 = ISO 8859-13
    0x0a = ISO 8859-14
    0x0b = ISO 8859-15
    0x10 = (3 byte encoding, see table A4)
    0x11 = ISO 10646 (Basic Multilingual Plane)
    0x12 = KSX1001-2004 (Korean)
    0x13 = GB-2312-1980 (Simplified Chinese)
    0x14 = Big5 subset of ISO 10646
    0x15 = UTF8 encoding of ISO 10646 

    From ETSI EN 300 468, table A4 (three byte character table codes):
    0x10 0x00 0x01 = ISO 8859-1
    0x10 0x00 0x02 = ISO 8859-2
    0x10 0x00 0x03 = ISO 8859-3
    0x10 0x00 0x04 = ISO 8859-4
    0x10 0x00 0x05 = ISO 8859-5
    0x10 0x00 0x06 = ISO 8859-6
    0x10 0x00 0x07 = ISO 8859-7
    0x10 0x00 0x08 = ISO 8859-8
    0x10 0x00 0x09 = ISO 8859-9
    0x10 0x00 0x0a = ISO 8859-10
    0x10 0x00 0x0b = ISO 8859-11
    0x10 0x00 0x0d = ISO 8859-13
    0x10 0x00 0x0e = ISO 8859-14
    0x10 0x00 0x0f = ISO 8859-15

    From cesgpi_mwchar.c (tvApp), resulting table codes (that we are converting to) are:
    0x00 = ISO 6937
    0x01 = ISO 8859-5 
    0x02 = ISO 8859-6 
    0x03 = ISO 8859-7 
    0x04 = ISO 8859-8 
    0x05 = ISO 8859-9
    0x06 = ISO 8859-2
    0x07 = ISO 8859-15
    0x08 = ISO 8859-4
    0x09 = ISO 8859-13
    0x11 = ISO/IEC 10646-1 
    0x13 = Chinese charater set GB2312 mixed up with english
    0x15 = UTF8 encoding of ISO 10646 
    */
Nat8 CHsvDvbCamNIT_Priv::mFindTableCode (Nat8* str)
{
    Nat8 charCode = DEFAULT_CHAR_SET;

    switch (*str)
    {
        case 0x00:
        case 0x01: 
        case 0x02: 
        case 0x03: 
        case 0x04: 
        case 0x05:
        case 0x09:
        case 0x11:
        case 0x13:
        case 0x15:
            /* these single byte table IDs map directly */
            charCode = *str;
            break;
        case 0x0b:
            charCode = 0x07;
            break;
        case 0x10:
            {
                int nextCode = ((str[1] << 8) | (str[2]));
                switch (nextCode)
                {
                    case 0x0002: 
                        charCode = 0x06;
                        break;            
                    case 0x0004: 
                        charCode = 0x08;
                        break;            
                    case 0x0005: 
                        charCode = 0x01;
                        break;            
                    case 0x0006: 
                        charCode = 0x02;
                        break;            
                    case 0x0007: 
                        charCode = 0x03;
                        break;            
                    case 0x0008:
                        charCode = 0x04;
                        break;            
                    case 0x0009: 
                        charCode = 0x05;
                        break;            
                    case 0x000d: 
                        charCode = 0x09;
                        break;            
                    case 0x000f: 
                        charCode = 0x07;
                        break;            
                    default:
                        break;            
                }
            }
            break;
        default:
            /* brg36mgr#158094: When the predefined character code is not present, 
                fallback to DEFAULT_CHAR_SET */
            if(!(*str >= 0x20))
            {
                ASSERT(!"Unsupported Character set in the stream");
            }
            break;            
    }


    return charCode;
}


/*****************************************************************************************
 * Populate Data Functions
 *****************************************************************************************/
void CHsvDvbCamNIT_Priv::mPopulateCamNitSatelliteDS (void)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    /* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITSatelliteDS DbaseVersion, TempVersion;

    int i, HsvEvtNull = 0,j = 0, tsloop = 0;

    while (tsloop < CamNitParser.TsLoopDataNum)
    {
        for (i = 0; i < CamNitParser.TsLoopData[tsloop].SDSDDescNum; ++i)
        {
            if (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].DescriptorValid )
            {
                DbaseVersion.VersionNumber  = CamNitParser.VersionNo;
                DbaseVersion.NetworkId         = CamNitParser.NetworkId;
                DbaseVersion.Tsid                  = CamNitParser.TsLoopData[tsloop].TSID;
                DbaseVersion.Original_NetworkId = CamNitParser.TsLoopData[tsloop].ONID;

                for( j = 0; j < CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSDLen ; j++)
                {
                    DbaseVersion.Frequency          = (ConvertBcdToDecimal (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Frequency)) * 10;
                    DbaseVersion.ModulationType  = MapModulationType (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationtype);
                    DbaseVersion.SymbolRate       = (ConvertBcdToDecimal(CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].SymbolRate)) * 100;
                    DbaseVersion.FECInner           = MapFECInner(CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].FEC_Inner);
                    DbaseVersion.Polarization        = MapPolarization (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Polarization);
                    DbaseVersion.RollOff               = CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].RollOff;
                    DbaseVersion.ModulationSystem = MapModulationStd (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationsystem);
                    DbaseVersion.OrbitalPosition = ConvertBcdToDecimal ((CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].OrbitalPostion & 0xFFFF));
                    DbaseVersion.WestEastFlag = CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].WestEastFlag;
                }
                TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                if (srtdb_QueryOnKey(srtdbids_CamNitSatelliteDS, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion)))
                {
                    srtdb_Update (srtdbids_CamNitSatelliteDS, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion));
                }
                else
                {
                    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                    /* New Record */
                    srtdb_Insert(srtdbids_CamNitSatelliteDS, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion));
                }
            }
        }
        ++tsloop;
    }
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
}


void CHsvDvbCamNIT_Priv::mPopulateOpTuneSatelliteDS (void)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    /* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITSatelliteDS DbaseVersion, TempVersion;

    int i, HsvEvtNull = 0,j = 0, tsloop = 0;

    while (tsloop < CamNitParser.TsLoopDataNum)
    {
        for (i = 0; i < CamNitParser.TsLoopData[tsloop].SDSDDescNum; ++i)
        {
            if (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].DescriptorValid )
            {
                DbaseVersion.VersionNumber  = CamNitParser.VersionNo;
                DbaseVersion.NetworkId         = CamNitParser.NetworkId;
                DbaseVersion.Tsid                  = CamNitParser.TsLoopData[tsloop].TSID;
                DbaseVersion.Original_NetworkId = CamNitParser.TsLoopData[tsloop].ONID;

                for( j = 0; j < CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSDLen ; j++)
                {
                    DbaseVersion.Frequency          = (ConvertBcdToDecimal (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Frequency)) * 10;
                    DbaseVersion.ModulationType  = MapModulationType (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationtype);
                    DbaseVersion.SymbolRate       = (ConvertBcdToDecimal(CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].SymbolRate)) * 100;
                    DbaseVersion.FECInner           = MapFECInner(CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].FEC_Inner);
                    DbaseVersion.Polarization        = MapPolarization (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Polarization);
                    DbaseVersion.RollOff               = CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].RollOff;
                    DbaseVersion.ModulationSystem = MapModulationStd (CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationsystem);
                    DbaseVersion.OrbitalPosition = ConvertBcdToDecimal ((CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].OrbitalPostion & 0xFFFF));
                    DbaseVersion.WestEastFlag = CamNitParser.TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].WestEastFlag;
                }
                TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                if (srtdb_QueryOnKey(srtdbids_OpTuneSatelliteDS, DbaseVersion.Frequency, DbaseVersion.Polarization, 0, 0,(Address)(&TempVersion)))
                {
                    srtdb_Update (srtdbids_OpTuneSatelliteDS, DbaseVersion.Frequency, DbaseVersion.Polarization, 0, 0,(Address)(&DbaseVersion));
                }
                else
                {
                    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                    /* New Record */
                    srtdb_Insert(srtdbids_OpTuneSatelliteDS, DbaseVersion.Frequency, DbaseVersion.Polarization, 0, 0, (Address)(&DbaseVersion));
                }
            }
        }
        ++tsloop;
    }
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
}

void CHsvDvbCamNIT_Priv::mPopulateCamNitContentLabel(void)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    HsvCamNITContentLabel DbaseVersion, TempVersion;
    int i = 0, len = 0, stringlen = MAXCONTENTLABLENAMELEN + 1;

    for (i = 0; i < 10; i++)//CamNitParser.CIPlus_Content_Label_Descriptor
    {
        if(CamNitParser.CIPlus_Content_Label_Descriptor[i].DescriptorValid)
        {
            DbaseVersion.ContentByteMin  = CamNitParser.CIPlus_Content_Label_Descriptor[i].Content_Byte_Min;
            DbaseVersion.ContentByteMax = CamNitParser.CIPlus_Content_Label_Descriptor[i].Content_Byte_Min;;
            DbaseVersion.ISO_639_Language_Code  = CamNitParser.CIPlus_Content_Label_Descriptor[i].ISO_639_Language_Code;

            Nat8 *LabelName = (Nat8 *) CamNitParser.CIPlus_Content_Label_Descriptor[i].LabelChar;
            len = CamNitParser.CIPlus_Content_Label_Descriptor[i].LabelCharLen;

            TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
            charsetutil_MbToWcEx( LabelName, len, (Nat16*)&DbaseVersion.LabelChar, &stringlen, charsetutil_ExtractShortName);
            
            if (stringlen > MAXCONTENTLABLENAMELEN)
            {
                stringlen = MAXCONTENTLABLENAMELEN;
            }
            DbaseVersion.LabelChar[stringlen] = 0; 
            TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
            if (srtdb_QueryOnKey( srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0,(Address)(&TempVersion)))
            {
                srtdb_Update(srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0,(Address)(&DbaseVersion));
            }
            else
            {
                TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                /* New Record */
                srtdb_Insert(srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0, (Address)(&DbaseVersion));
            }
        }
    }	
}

void CHsvDvbCamNIT_Priv::mPopulateCamNitService(void)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    HsvCamNITService DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, len = 0, NumOfServiceDescNum = 0;
	Nat8 *ServiceName = NULL;

    while (tsloop < CamNitParser.TsLoopDataNum)
    {
        NumOfServiceDescNum = CamNitParser.TsLoopData[tsloop].CIPlusServiceDescNum;
        TraceNotice(m, "%s() @ %d : NumOfServiceDescNum %d", __FUNCTION__, __LINE__, NumOfServiceDescNum);
        for (i = 0; i < NumOfServiceDescNum; i++)
        {
            if (CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].DescriptorValid ) 
            {
                DbaseVersion.TsId                       = CamNitParser.TsLoopData[tsloop].TSID;
                DbaseVersion.OriginalNetworkId   = CamNitParser.TsLoopData[tsloop].ONID;
                DbaseVersion.ServiceId              = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceId;
                DbaseVersion.ServiceType          = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceType;
                DbaseVersion.VisibleServiceFlag     = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].VisibleServiceFlag;
                DbaseVersion.SelectableServiceFlag  = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].SelectableServiceFlag;
                DbaseVersion.LogicalChannelNumber   = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].LogicalChannelNumber;
                DbaseVersion.ServiceName[0]     = '\0';
                
                //Nat8 *ServiceName = (Nat8 *)CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName;
                len =   CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceNameLen;

                TraceNotice (m, "Service {%d, %d, %d} : LCN %d, ServiceNameLen %d\n", DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, len);
                ServiceName = (Nat8 *) malloc (len+1);
                ServiceName[0] = mCamCharCode;
                TraceNotice (m, "Before concat in CAM NIT module is %d %d \n", ServiceName[0], mCamCharCode);
                //strncat((char *)ServiceName, CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName, len);
                for (int loop = 0; loop < len; loop++){
                    ServiceName[loop+1] = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName[loop];
                    TraceNotice (m, "ServiceName[%d]  %c\n", loop+1, ServiceName[loop+1]);
                }
                TraceNotice (m, "char code used in CAM NIT module is %d\n", ServiceName[0]);
                charsetutil_MbToWc (ServiceName, len+1, DbaseVersion.ServiceName, MAXSERVICENAMELEN, (len >= div_ChannelNameLength) ? TRUE : FALSE);
                len =   MAXSERVICENAMELEN;
                DbaseVersion.ServiceName[len] = '\0';

				ServiceName = NULL;
                free (ServiceName);
                
                if ( srtdb_QueryOnKey( srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&TempVersion) ) )
                {
                    srtdb_Update(srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&DbaseVersion));
                }
                else
                {
                    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                    /* New Record */
                    srtdb_Insert(srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&DbaseVersion));
                }
            }
        }
        tsloop++;
    }
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
}

void CHsvDvbCamNIT_Priv::mPopulateCamNitLinkageInfo(void)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    Bool retval  = TRUE;
    int i= 0, tsloop = 0;
    HSVSPTYPE(CamNITLinkageInfo, dvb, camnit)  linkage;
    HSVSPTYPE(CamNITLinkageInfo, dvb, camnit)  DbaseVersion;

    for( i = 0; i < CamNitParser.LinkageDescNum; i++)
    {
        if(CamNitParser.Linkage_Descriptor[i].DescriptorValid)
        {
            linkage.LinkageType        = (HsvLinkageType)CamNitParser.Linkage_Descriptor[i].LinkageType;
            linkage.Original_NetworkId  = CamNitParser.Linkage_Descriptor[i].ONID;
            linkage.Tsid               = CamNitParser.Linkage_Descriptor[i].TSID;
            linkage.ServiceId          = CamNitParser.Linkage_Descriptor[i].ServiceId;
            linkage.NetworkId          = CamNitParser.NetworkId;
            linkage.VersionNumber      = CamNitParser.VersionNo;
            if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI) )
            {
                TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
                if( srtdb_QueryOnKey( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&DbaseVersion)) )
                {
                    /*Record exists. Update */

                    TraceInfo(m,"%s Onid = %d, TsId = %d", __FUNCTION__, linkage.Original_NetworkId, linkage.Tsid);
                    srtdb_Update( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&linkage));
                }
                else
                {
                    TraceInfo(m,"%s OnId = %d, TsId=%d, Type=%d", __FUNCTION__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
                    srtdb_Insert( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType, linkage.LinkageType,(Address)(&linkage));
                }

            }
        }        

        while ( tsloop < CamNitParser.TsLoopDataNum)
        {

            for( i = 0; i < CamNitParser.TsLoopData[tsloop].LinkageDescNum; i++)
            {
                if(CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid)
                {
                    linkage.LinkageType        = (HsvLinkageType)CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    linkage.Original_NetworkId  = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    linkage.Tsid               = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    linkage.ServiceId          = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    linkage.NetworkId          = CamNitParser.NetworkId;
                    linkage.VersionNumber      = CamNitParser.VersionNo;
                    if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI) )
                    {

                        if( srtdb_QueryOnKey( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),0, (Address)(&DbaseVersion)) )
                        {
                            /*Record exists. Update */
                            srtdb_Update( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0, (Address)(&linkage));
                            TraceInfo(m,"HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, TsId = %d",linkage.Original_NetworkId, linkage.Tsid);
                        }
                        else
                        {
                            TraceInfo(m,"%s: @ %d :: OnId = %d, TsId=%d, Type=%d", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
                            srtdb_Insert( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),(linkage.LinkageType), (Address)(&linkage));
                        }

                    }
                }        

            }
            tsloop++;   
        }
    }
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
}

Bool CHsvDvbCamNIT_Priv::mPopulateNIT(void)
{
    int retval = TRUE;
    
    TraceNotice(m, "%s mActive1 %d", __FUNCTION__, mActive);

    if(mActive)
    {
		if (mCookie == EnmTypeTuneDSDescData)
		{
			mPopulateOpTuneSatelliteDS();
		}
		else
		{
			mPopulateCamNitSatelliteDS();
		}
        mPopulateCamNitService();
        mPopulateCamNitContentLabel();
        mPopulateCamNitLinkageInfo();

        //strapiN_OnCompleted(0, EnmTypeCamNITData);
        TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(HsvDmxMain), mCookie);
        mPrevPrivateDataSpecifierPresent = FALSE;
    }
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    return retval;
}


/*****************************************************************************************
 * Public methods
 *****************************************************************************************/

// Overridden IHsvPower methods
void CHsvDvbCamNIT_Priv::pow_Init(void)
{
    mActive = FALSE;
}

void CHsvDvbCamNIT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbCamNIT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}


// Overridden IHsvSdmEnable methods
void CHsvDvbCamNIT_Priv::ena_Enable(HsvDemux dmx)
{
    mActive = TRUE;

    TraceNotice(m, "mActive %d Reset CAM NIT strapi database", mActive);

    mInitCamNitLinkageInfo();
    mInitCamNitSatelliteDS();
    mInitOpTuneSatelliteDS();
    mInitCamNitContentLabel();
    mInitCamNitService();
}

void CHsvDvbCamNIT_Priv::ena_Disable(HsvDemux dmx)
{
    mActive = FALSE;

    TraceNotice(m, "mActive %d Reset CAM NIT strapi database", mActive);

    mInitCamNitLinkageInfo();
    mInitCamNitSatelliteDS();
    mInitOpTuneSatelliteDS();
    mInitCamNitContentLabel();
    mInitCamNitService();
}

void CHsvDvbCamNIT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED( dmx );
}


// Overriden IHsvStream methods
int CHsvDvbCamNIT_Priv::strapi_GetSize   (HsvDestination dest, int prop)
{
    int retval = 0;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(SatelliteDS, dvb, camnit):
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitSatelliteDS);
            break;
        case HSVSPID(OpTuneSatelliteDS, dvb, camnit):
            retval = srtdb_GetNoOfRecords(srtdbids_OpTuneSatelliteDS);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitLinkageInfo);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitService);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitContentLabel);
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

Bool CHsvDvbCamNIT_Priv::strapi_GetIndex  (HsvDestination dest, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(SatelliteDS, dvb, camnit):
            srtdb_SearchOnKey(srtdbids_CamNitSatelliteDS, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
            srtdb_SearchOnKey(srtdbids_CamNitLinkageInfo, key1, key2, key3, 0,(int *)&index);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
            srtdb_SearchOnKey(srtdbids_CamNitService, key1, key2, key3, 0,(int *)&index);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit): 
            srtdb_SearchOnKey(srtdbids_CamNitContentLabel, key1, key2, key3, 0,(int *)&index);
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    return TRUE;
}

Bool CHsvDvbCamNIT_Priv::strapi_GetByKey  (HsvDestination dest, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    
    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(SatelliteDS, dvb, camnit):
            retval = srtdb_QueryOnKey(srtdbids_CamNitSatelliteDS, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
            retval = srtdb_QueryOnKey(srtdbids_CamNitLinkageInfo, key1, key2, key3, 0, (Address)val);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
            retval = srtdb_QueryOnKey(srtdbids_CamNitService, key1, key2, key3, 0, (Address)val);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit):
            retval = srtdb_QueryOnKey(srtdbids_CamNitContentLabel, key1, key2, key3, 0, (Address)val);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    
    return retval;
}

Bool CHsvDvbCamNIT_Priv::strapi_GetByIndex(HsvDestination dest, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(SatelliteDS, dvb, camnit):
            retval = srtdb_QueryOnIndex(srtdbids_CamNitSatelliteDS, index, (Address)val);
            break;
        case HSVSPID(OpTuneSatelliteDS, dvb, camnit):
            retval = srtdb_QueryOnIndex(srtdbids_OpTuneSatelliteDS, index, (Address)val);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
            retval = srtdb_QueryOnIndex(srtdbids_CamNitLinkageInfo, index, (Address)val);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
            retval = srtdb_QueryOnIndex(srtdbids_CamNitService, index, (Address)val);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit):
            retval = srtdb_QueryOnIndex(srtdbids_CamNitContentLabel, index, (Address)val);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    
    return retval;
}

Bool CHsvDvbCamNIT_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
    Bool retVal = FALSE;

    TraceNotice (m, "%s() @ %d \n", __FUNCTION__, __LINE__);
    
    switch (spid)
    {
        case HSVSPID(CamNITService, dvb, camnit):
            if(noofkeys == 2)
            {
                /*TODO: Servicelist has to be populated from NIT*/
                TraceNotice (m, "%s() @ %d \n", __FUNCTION__, __LINE__);
                retVal = srtdb_SearchOnPrimaryAndSecondaryKey (srtdbids_CamNitService, key1, key2, from, to);
                TraceNotice (m, "%s() @ %d retVal %d, from %p, to %p \n", __FUNCTION__, __LINE__, retVal, from, to);
            }
            else
            {
                ASSERT(FALSE);
            }
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    UNUSED (dest);
    UNUSED (key3);

    return retVal;
}


// Overriden IHsvStreamFilter methods
Bool CHsvDvbCamNIT_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    
    UNUSED (dest);
    UNUSED (value);

    return retval;
}/* End of function strmfltr_Set() */

Bool CHsvDvbCamNIT_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
    return FALSE;
}
Bool CHsvDvbCamNIT_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
    return FALSE;
}
Bool CHsvDvbCamNIT_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
    return FALSE;
}


// Overriden IHsvCamDataParser methods
Bool CHsvDvbCamNIT_Priv::camdataparser_ParseCamData( HsvDestination   dest,  Nat32 cookie, int DataSize, Nat8 *DataPtr)
{
    Nat8 *TempPtr;
    Bool retval = TRUE;
    register int v32=0;
    register Nat8 *ptr = mBuffer;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    int dummy, loopcount = 0, descTag = 0, descTagExtn = 0, descLen = 0, descLoopLen = 0, tsloopIndex = 0;
    int loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0, unused = 0; 
    int nitLoopLen = 0;
    int privateDataSpecifierId = 0;

    ptr = DataPtr;
    
    mPrevPrivateDataSpecifierPresent = FALSE;
    nitLoopLen = DataSize;
    mCookie = cookie;
    TraceNotice(m, "%s() @ %d : cookie %d, DataSize %d", __FUNCTION__, __LINE__, cookie, DataSize);
    
    v32 = GET32(0);

    while (nitLoopLen > 0) {
        if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
        {
            tableLen = HSV_GETSECTION_LENGTH(ptr);
            TraceNotice(m,"%s() : tableLen %d",__FUNCTION__, tableLen);
            nitLoopLen = nitLoopLen - tableLen;

            CamNitParser.NtkNameDescNum = 0;
            CamNitParser.LinkageDescNum = 0;
            CamNitParser.CIPlusContentLabelDescNum = 0;
            CamNitParser.TsLoopDataNum = 0;
            
            CamNitParser.TableId = GETNBITS(v32,0,8);
            TraceNotice(m,"%s() : TableId %d",__FUNCTION__, CamNitParser.TableId);
            dummy = GETNBITS(v32,8,1);
            dummy = GETNBITS(v32,9,1);
            dummy = GETNBITS(v32,10,2);
            CamNitParser.SectionLen = GETNBITS(v32,12,12);
            TraceNotice(m,"%s() : SectionLen %d",__FUNCTION__, CamNitParser.SectionLen);
            v32 = GET32( 3);
            CamNitParser.NetworkId = GETNBITS(v32,0,16);
            TraceNotice(m,"%s() : NetworkId %d",__FUNCTION__, CamNitParser.NetworkId);
            dummy = GETNBITS(v32,16,2);
            CamNitParser.VersionNo = GETNBITS(v32,18,5);
            TraceNotice(m,"%s() : VersionNo %d",__FUNCTION__, CamNitParser.VersionNo);
            dummy = GETNBITS(v32,23,1);
            dummy = GETNBITS(v32,24,8);
            v32 = GET32( 7);
            dummy = GETNBITS(v32,0,8);
            dummy = GETNBITS(v32,8,4);
            CamNitParser.NetworkDescLen = GETNBITS(v32,12,12);
            TraceNotice(m,"%s() : NetworkDescLen %d \n",__FUNCTION__, CamNitParser.NetworkDescLen);
            ptr += 10;
            tableLen = tableLen - 10;
            v32 = GET32( 0);
            while(loopcount < CamNitParser.NetworkDescLen)
            {
                descLoopLen = 0;
                descTag = GETNBITS(v32,0, 8); 
                descLen = GETNBITS(v32,8, 8);
                TraceNotice(m,"%s() @  descTag %d, descLen %d\n",__FUNCTION__, descTag, descLen);
                switch (descTag) {
                case 0x40:
                     CamNitParser.NetworkName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
                     CamNitParser.NetworkName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);
                     CamNitParser.NetworkName_Descriptor.NetworkNameLen = GETNBITS(v32,16,0);
                     CamNitParser.NetworkName_Descriptor.NetworkNameLen = descLen;
                     descLoopLen = HSV_PARSER_MIN(80,CamNitParser.NetworkName_Descriptor.NetworkNameLen); 
                     ptr += 2;
                     memcpy(CamNitParser.NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
                     ptr += CamNitParser.NetworkName_Descriptor.NetworkNameLen;
                     v32 = GET32( 0);
                     CamNitParser.NetworkName_Descriptor.NetworkNameLen = descLoopLen;
                     CamNitParser.NetworkName_Descriptor.DescriptorValid = TRUE;
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x4A:
                    if(CamNitParser.LinkageDescNum<10)
                    {
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorTag = GETNBITS(v32,0,8);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorLen = GETNBITS(v32,8,8);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].TSID = GETNBITS(v32,16,16);
                         v32 = GET32( 4);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].ONID = GETNBITS(v32,0,16);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].ServiceId = GETNBITS(v32,16,16);
                         v32 = GET32( 8);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].LinkageType = GETNBITS(v32,0,8);
                         CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorValid = TRUE;
                         CamNitParser.LinkageDescNum++;
                         //ptr += 9;
                         ptr += (2 + descLen);
                         v32 = GET32( 0);
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0xcb:
                    if(CamNitParser.CIPlusContentLabelDescNum<10)
                    {
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorTag = GETNBITS(v32,0,8);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorLen = GETNBITS(v32,8,8);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].Content_Byte_Min = GETNBITS(v32,16,8);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].Content_Byte_Max = GETNBITS(v32,24,8);
                        v32 = GET32( 4);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].ISO_639_Language_Code = GETNBITS(v32,0,24);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = GETNBITS(v32,24,0);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = (descLen - 5);
                        descLoopLen = HSV_PARSER_MIN(80,CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen); 
                        ptr += 7;
                        memcpy(CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelChar,ptr,descLoopLen);
                        ptr += CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen;
                        v32 = GET32( 0);
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = descLoopLen;
                        CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorValid = TRUE;
                        CamNitParser.CIPlusContentLabelDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                default:
                    tableLen = tableLen - (2 + descLen);
                    loopcount += 2 + descLen;
                    ptr += 2 + descLen;
                    v32 = GET32( 0);
                    break;
                }//endswitch
            }//endwhile
            dummy = GETNBITS(v32,0,4);
            mPopulateNIT();
            CamNitParser.TsLoopLen = GETNBITS(v32,4,12);
            ptr += 2;
            tableLen = tableLen - 2;
            v32 = GET32( 0);
        }
        else
        {
            tableLen = DataSize;
            nitLoopLen = nitLoopLen - tableLen;
            TraceNotice(m, "%s @ %d tableLen %d *ptr %d *(ptr+1) %d", __FUNCTION__, __LINE__, tableLen, *ptr, *(ptr+1));
        }

        TraceNotice(m, "%s @ %d %d GET_PARSE_TABLE_LEN(cookie) %d tsloopIndex %d", __FUNCTION__, __LINE__, cookie, GET_PARSE_TABLE_LEN(cookie), tsloopIndex);
        while( (GET_PARSE_TABLE_LEN(cookie) >  0)  &&  ( tsloopIndex < 1 ))
        {
            CamNitParser.TsLoopData[tsloopIndex].NtkNameDescNum=0;
            CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum=0;
            CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum=0;
            CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum=0;
            loopcount = 0;

            if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
            {
                CamNitParser.TsLoopData[tsloopIndex].TSID = GETNBITS(v32, 0,16);
                CamNitParser.TsLoopData[tsloopIndex].ONID = GETNBITS(v32, 16,16);
                v32 = GET32( 4);
                dummy = GETNBITS(v32,0,4);
                CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
                ptr += 6;
                tableLen = tableLen - 6;
                v32 = GET32( 0);
                TraceNotice(m,"%s @ %d CamNitParser.TsLoopData[%d].TsDescLoopLen %d",__FUNCTION__, __LINE__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen);
            }
            else
            {
                CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen = tableLen;
                TraceNotice(m,"%s @ %d CamNitParser.TsLoopData[%d].TsDescLoopLen %d",__FUNCTION__, __LINE__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen);
            }

            while(loopcount < CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen)
            {
                descLoopLen = 0, loop1length = 0;
                descTag = GETNBITS(v32, 0, 8); 
                descLen = GETNBITS(v32, 8, 8); 
                TraceNotice(m,"%s @ %d descTag %d descLen %d",__FUNCTION__, __LINE__, descTag, descLen);
                switch(descTag) {
                case 0x40:	
                    CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorTag = GETNBITS(v32, 0,8);
                    CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorLen = GETNBITS(v32, 8,8);
                    CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLen;
                    descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen); 
                    ptr += 2;
                    memcpy(CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
                    ptr += CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen;
                    v32 = GET32( 0);
                    CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLoopLen;
                    CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorValid = TRUE;
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x4A:
                    if(CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum<80)
                    {
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
                        v32 = GET32( 4);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
                        v32 = GET32( 8);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);
                        CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
                        CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum++;
                        ptr += 9;
                        v32 = GET32( 0);
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x43:
                    if(CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum<10)
                    {
                        CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD);
                        while( loop1length< HSV_PARSER_MIN(CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen, templen))
                        {
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
                            v32 = GET32( 4);
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].OrbitalPostion = GETNBITS(v32,0, 16); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].WestEastFlag = GETNBITS(v32,16, 1); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Polarization = GETNBITS(v32,17, 2); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].RollOff = GETNBITS(v32,19, 2); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationsystem = GETNBITS(v32,21, 1); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationtype = GETNBITS(v32,22, 2); 
                            v32 = GET32( 7);
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].SymbolRate = GETNBITS(v32,0, 28); 
                            CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].FEC_Inner = GETNBITS(v32,28, 4); 
                            loop1length += 11;
                            loop1index++;
                            ptr += 11;
                            v32 = GET32( 0);
                        }
                        CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].SDSDLen = loop1index;
                        CamNitParser.TsLoopData[tsloopIndex].SDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorValid = TRUE;
                        CamNitParser.TsLoopData[tsloopIndex].SDSDDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
                case 0xCC:
                    if(CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum<300)
                    {
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceId = GETNBITS(v32, 16,16);
                        v32 = GET32( 4);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceType = GETNBITS(v32, 0,8);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].VisibleServiceFlag = GETNBITS(v32, 8,1);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].SelectableServiceFlag = GETNBITS(v32, 9,1);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].LogicalChannelNumber = GETNBITS(v32, 10,14);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
                        descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen); 
                        ptr += 8;
                        memcpy(CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderName,ptr,descLoopLen);
                        ptr += CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen;
                        v32 = GET32( 0);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen = descLoopLen;
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
                        descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen); 
                        ptr += 1;
                        memcpy(CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceName,ptr,descLoopLen);
                        ptr += CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen;
                        v32 = GET32( 0);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen = descLoopLen;
                        if(mPrevPrivateDataSpecifierPresent == TRUE)
                            CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = TRUE;
                        else
                            CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = FALSE;
                        TraceNotice(m,"%s %d %d %d %d",__FUNCTION__, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceId, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].LogicalChannelNumber, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceType, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen);
                        CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x5F:
                    unused = GETNBITS(v32, 0,8);
                    unused = GETNBITS(v32, 8,8);
                    ptr += 2;
                    v32 = GET32( 0);
                    privateDataSpecifierId = GETNBITS(v32, 0,32);
                    TraceNotice(m, "privateDataSpecifierId = %d", privateDataSpecifierId);
                    if(privateDataSpecifierId == 0x40) {
                        mPrevPrivateDataSpecifierPresent = TRUE;
                    }
                    else {
                        mPrevPrivateDataSpecifierPresent = FALSE;
                    }
                    TraceNotice(m, "mPrevPrivateDataSpecifierPresent = %d", mPrevPrivateDataSpecifierPresent);
                    ptr += 4;
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
                default:
                loopcount += 2 + descLen;
                ptr += 2 + descLen;
                tableLen = tableLen - (2 + descLen);
                TraceNotice(m,"%s %d %d %d",__FUNCTION__, loopcount, descLen, tableLen);
                v32 = GET32( 0);
                break;
				}//endswitch
			}//endwhile descloop
			tsloopIndex++;
			loopcount = 0;
			CamNitParser.TsLoopDataNum = tsloopIndex;
			TraceNotice(m, "%s CamNitParser.TsLoopDataNum %d", __FUNCTION__, CamNitParser.TsLoopDataNum);
			retval = retval && mPopulateNIT();
			tsloopIndex = 0;
        }//endwhile tsloopif(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
        if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
        {
            dummy = GETNBITS(v32,0,32);
            ptr += 4;
            TraceNotice(m, "%s dummy %d", __FUNCTION__, dummy);
        }
    }
    return TRUE;
}//end function

void CHsvDvbCamNIT_Priv::camdataparser_SetCharacterCode (char* charCode)
{
    TraceNotice(m,"Character code from CAM is %d %d %d\n", charCode[0], charCode[1], charCode[2]);
    mCamCharCode = mFindTableCode((Nat8 *)charCode);//(Nat8) charCode[0];
    TraceNotice(m,"Character code after conversion is %d", mCamCharCode);
}
