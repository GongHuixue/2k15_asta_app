/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *          %name: hsvdvbsfreesat_mSettings.c %
 *       %version:  %
 * %date_modified: %
 *    %derived_by:  %
 */

#include "CHsvDvbsFreesat_mSettings.h"

TRACESYMBOL(m, "/installation/comp/hsvdvbsfreesat/HsvDvbsFreeSat_mSettings")

CHsvDvbsFreesat_mSettings::HsvDvbsFreesatSettings CHsvDvbsFreesat_mSettings::s__FreesatDefaultData = {sizeof(HsvDvbsFreesatSettings), PRIMARY_VERSION,SECONDARY_VERSION,DEFAULT_FREESAT_HD_BID,DEFAULT_FREESAT_HD_RID,{'\0'}, 0};
CHsvDvbsFreesat_mSettings::HsvDvbsFreesatSettings CHsvDvbsFreesat_mSettings::s__FreesatCurrentData;
CHsvDvbsFreesat_mSettings::HsvDvbsFreesatSettings CHsvDvbsFreesat_mSettings::s__FreesatPersistentData;


Bool CHsvDvbsFreesat_mSettings::LoadDataFromPersistentFile(void)
{

	FILE *	fp = NULL;
	Nat32  Crc = 0;
	Nat32 Size = 0;
	Bool	bCheckFlag = FALSE;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	fp = fopen(FREESAT_SETTING_FILE_PATH, "rb" );
	if ( fp != NULL )
	{
	  //Size =  fread (&s__FreesatPersistentData,1,sizeof(HsvDvbsFreesatSettings),fp);
	   Size =  fread (&s__FreesatPersistentData,sizeof(HsvDvbsFreesatSettings),1,fp);

	  //if(Size == sizeof(HsvDvbsFreesatSettings))
	   if(Size)
	   {
		    Crc = s__FreesatPersistentData.Crc;
		    s__FreesatPersistentData.Crc = 0;
		    s__FreesatPersistentData.Crc = CalculateCrc32(&s__FreesatPersistentData, sizeof(HsvDvbsFreesatSettings));

		    TraceNotice (m,"LINE %d Size %d CRC read from File %d, CRC Generated %d",__LINE__,Size,Crc,  s__FreesatPersistentData.Crc);
		    TraceNotice(m,"Line %d  Bouquet ID %d Region %d Postcode %s PostCodeLen %d",__LINE__,s__FreesatPersistentData.BouquetId, s__FreesatPersistentData.RegionId,s__FreesatPersistentData.Postcode,s__FreesatPersistentData.PostcodeLen);
		    if ( (Crc == s__FreesatPersistentData.Crc ) &&
		    	( s__FreesatPersistentData.RecordSize == sizeof( HsvDvbsFreesatSettings ))&&
		           ( s__FreesatPersistentData.PrimaryVersion == PRIMARY_VERSION) &&
		            (s__FreesatPersistentData.SecondaryVersion == SECONDARY_VERSION ))
		    {
				bCheckFlag = TRUE;
				memmove(&s__FreesatCurrentData,&s__FreesatPersistentData,sizeof(HsvDvbsFreesatSettings));
		    }
	    }
	    else
	    {
	    		TraceNotice (m,"Number of bites read from file is not equal to actual size, size %d",Size);
	    }
	    fclose(fp);
	}
	else
	{
		TraceNotice (m,"Line %d Freesat settings File open failed",__LINE__);
	}

	return bCheckFlag;
}


Nat32 CHsvDvbsFreesat_mSettings::CalculateCrc32( void* buffer, int size )
{
    /* http://www.cl.cam.ac.uk/Research/SRG/bluebook/21/crc/crc.html */
    Nat32 Result = 0xFFFFFFFF;
    int   i = 0;
    int   j = 0;
    Nat8  Octet = 0;
    Nat8 *Buf   = (Nat8*)buffer;

    for ( i = 0; i < size; i++ )
    {
        Octet = *Buf++;
        for ( j = 0; j < 8; j++ )
        {
            Result = ( Result << 1 );
            if ( ( Octet >> 7 ) ^ ( Result >> 31 ) )
            {
                Result ^= 0x04C11DB7;
            }
            Octet <<= 1;
        }
    }

    return ~Result;             /* The complement of the remainder */

}

void CHsvDvbsFreesat_mSettings::Init(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
}
void CHsvDvbsFreesat_mSettings::TurnOn(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	Bool	bCheckFlag = FALSE;
	bCheckFlag = LoadDataFromPersistentFile ();

	TraceNotice(m,"Data loaded from persistant memory, CRC %d",bCheckFlag);
	 if ( !bCheckFlag )
	{
		memmove ( &s__FreesatPersistentData,&s__FreesatDefaultData,sizeof(HsvDvbsFreesatSettings));
		memmove(&s__FreesatCurrentData,&s__FreesatPersistentData,sizeof(HsvDvbsFreesatSettings));
		TraceNotice(m,"Line %d Default Bouquet ID %d Region %d Postcode %s",__LINE__, s__FreesatCurrentData.BouquetId, s__FreesatCurrentData.RegionId, s__FreesatCurrentData.Postcode);
	}
}

void CHsvDvbsFreesat_mSettings::TurnOff(void)
{
}


Nat32 CHsvDvbsFreesat_mSettings::GetAttribute(int AttributeId)
{
	TraceNotice (m," Entering function Freesat - %s, Attribute %d",__FUNCTION__, AttributeId);

	Nat32 RetVal = 0;

	switch(AttributeId)
	{
		case IHsvSatelliteSettings_AttributeBouquetId:
				{
					RetVal = s__FreesatCurrentData.BouquetId;
					TraceNotice(m,"Bouquet ID returned in %s is %d",__FUNCTION__,s__FreesatCurrentData.BouquetId);
				}
				break;
		case IHsvSatelliteSettings_AttributeRegionId:
				{
					RetVal = s__FreesatCurrentData.RegionId;
					TraceNotice(m,"Region ID returned in %s is %d",__FUNCTION__,s__FreesatCurrentData.RegionId);
				}
				break;
		case IHsvSatelliteSettings_AttributeFreesatHomingServiceData:
			 	{
					HsvFreesatHomingServiceData *tempData; 

					tempData = (HsvFreesatHomingServiceData*)malloc(sizeof(HsvFreesatHomingServiceData));
					
					memset(tempData,0x00,sizeof(tempData));
					memcpy(tempData,&s__FreesatCurrentData.HomingServiceDetails,sizeof(HsvFreesatHomingServiceData));

					RetVal = (Nat32)tempData;
				}	
				break;
		default:
				TraceNotice  (m,"ERROR!!! Invalid AttributeId, should not enter %d",AttributeId);
				break;
	}
	
	return RetVal;
	
}
FResult CHsvDvbsFreesat_mSettings::SetAttribute(int AttributeId,Nat32 Value)
{
	FResult RetVal = IHsvErrorCodeEx_Ok;
	TraceNotice (m," Entering function Freesat - %s, Attribute %d Value %d",__FUNCTION__, AttributeId, Value);


	switch(AttributeId)
	{
		case IHsvSatelliteSettings_AttributeBouquetId:
				s__FreesatCurrentData.BouquetId = Value;
				break;
		case IHsvSatelliteSettings_AttributeRegionId:
				s__FreesatCurrentData.RegionId = Value;
				break;
		case IHsvSatelliteSettings_AttributeFreesatHomingServiceData:
			 	{
					HsvFreesatHomingServiceData *tempData = (HsvFreesatHomingServiceData*)Value;
					memcpy(&s__FreesatCurrentData.HomingServiceDetails,tempData,sizeof(HsvFreesatHomingServiceData));
					
					/*TraceNotice(m," %s linkage count [%d] & info count [%d]",__FUNCTION__,s__FreesatCurrentData.HomingServiceDetails.LinkageServiceCount,\
																		 s__FreesatCurrentData.HomingServiceDetails.InfoLocationServiceCount);
					
					for(int i = 0;i < (s__FreesatCurrentData.HomingServiceDetails.LinkageServiceCount + s__FreesatCurrentData.HomingServiceDetails.InfoLocationServiceCount);i++)
					{
						TraceNotice(m,"stored [%d] [%d] [%d] [%d]",s__FreesatCurrentData.HomingServiceDetails.HomingServices[i].HomingServiceType,
																   s__FreesatCurrentData.HomingServiceDetails.HomingServices[i].ServiceId,\
															       s__FreesatCurrentData.HomingServiceDetails.HomingServices[i].Frequency,\
															       s__FreesatCurrentData.HomingServiceDetails.HomingServices[i].TsId);
					}*/
							
				}	
				break;
		default:
				TraceNotice  (m,"ERROR!!! Invalid AttributeId, should not enter %d",AttributeId);
				RetVal = IHsvErrorCodeEx_BadParameter;
				break;
	}
	
	return RetVal;
}

FResult CHsvDvbsFreesat_mSettings::SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	FResult RetVal = IHsvErrorCodeEx_BadParameter;
	TraceNotice (m," Entering function Freesat - %s, Postcode len  %d Postcode %s",__FUNCTION__, PostcodeLen, Postcode);
	if(Postcode)
	{
		memset(s__FreesatCurrentData.Postcode, 0, (sizeof(Nat8) * MAX_POSTCODE_LENGTH));
		s__FreesatCurrentData.PostcodeLen = ((PostcodeLen < MAX_POSTCODE_LENGTH) ? PostcodeLen : (MAX_POSTCODE_LENGTH - 1));
		memcpy(s__FreesatCurrentData.Postcode, Postcode, s__FreesatCurrentData.PostcodeLen);
		RetVal = IHsvErrorCodeEx_Ok;
	}
	TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,RetVal);
	return RetVal;
}

FResult CHsvDvbsFreesat_mSettings::GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode)
{
	FResult RetVal = IHsvErrorCodeEx_BadParameter;
	TraceNotice (m," Entering function Freesat - %s current postcodelen %d current postcode %s ",__FUNCTION__,s__FreesatCurrentData.PostcodeLen,s__FreesatCurrentData.Postcode);

	if(Postcode)
	{
		memcpy(Postcode, s__FreesatCurrentData.Postcode, (sizeof(Nat8) * MAX_POSTCODE_LENGTH));
		*PostcodeLen = s__FreesatCurrentData.PostcodeLen;
		RetVal = IHsvErrorCodeEx_Ok;
	}
	#if 0
	String tempPostcode = "TEST 7AA";
	if(Postcode)
	{
		memcpy(Postcode,tempPostcode, (sizeof(Nat8) * MAX_POSTCODE_LENGTH));
		RetVal = IHsvErrorCodeEx_Ok;
	}
	#endif
	TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,RetVal);
	return RetVal;
}

void CHsvDvbsFreesat_mSettings::SaveSatelliteSettingsToPersistent(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	s__FreesatPersistentData.BouquetId = s__FreesatCurrentData.BouquetId;
	s__FreesatPersistentData.RegionId = s__FreesatCurrentData.RegionId;
	memcpy(s__FreesatPersistentData.Postcode, s__FreesatCurrentData.Postcode, (sizeof(Nat8) * MAX_POSTCODE_LENGTH));
	s__FreesatPersistentData.PostcodeLen = s__FreesatCurrentData.PostcodeLen;
	memcpy(&s__FreesatPersistentData.HomingServiceDetails,&s__FreesatCurrentData.HomingServiceDetails,sizeof(HsvFreesatHomingServiceData));
}

FResult CHsvDvbsFreesat_mSettings::CommitSatelliteSettingsToPersistent(void)
{
	FResult	RetVal = IHsvErrorCodeEx_Ok;
	FILE*	fp = NULL;
	Nat32 Size = 0;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	fp = fopen(FREESAT_SETTING_FILE_PATH, "w+b" );

	if ( fp != NULL )
	{
		s__FreesatPersistentData.RecordSize = sizeof(HsvDvbsFreesatSettings);
		s__FreesatPersistentData.PrimaryVersion = PRIMARY_VERSION;
		s__FreesatPersistentData.SecondaryVersion = SECONDARY_VERSION;
		s__FreesatPersistentData.Crc = 0;
		s__FreesatPersistentData.Crc = CalculateCrc32(&s__FreesatPersistentData, sizeof(HsvDvbsFreesatSettings));
		Size = fwrite ( &s__FreesatPersistentData,sizeof(HsvDvbsFreesatSettings),1,fp);
		if(!Size)
		{
			TraceNotice (m,"Error!!! Line %d Fwrite failed, size %d",__LINE__,Size);
		}
		fclose (fp);
	}
	else
	{
		TraceNotice (m,"Freesat settings  File open failed");
		RetVal = IHsvErrorCodeEx_FileError;
	}
	return RetVal;
}

FResult CHsvDvbsFreesat_mSettings::GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry)
{
	return IHsvErrorCodeEx_Ok;
}

FResult CHsvDvbsFreesat_mSettings::ResetToDefaultLnbSettings(void)
{
	return IHsvErrorCodeEx_Ok;
}

void CHsvDvbsFreesat_mSettings::ReLoadLnbParametersFromPersistent(void)
{
}
void CHsvDvbsFreesat_mSettings::LoadLnbParametersFromPersistent(void)
{
}
FResult CHsvDvbsFreesat_mSettings::GetLnbSettings(HsvLnbSettings * LnbSettings)
{
	return IHsvErrorCodeEx_Ok;
}
FResult CHsvDvbsFreesat_mSettings::SetLnbSettings(HsvLnbSettings * LnbSettings)
{
	return IHsvErrorCodeEx_Ok;
}
FResult CHsvDvbsFreesat_mSettings::ResetLnbSettings(void)
{
	return IHsvErrorCodeEx_Ok;
}

CHsvDvbsFreesat_mSettings::~CHsvDvbsFreesat_mSettings()
{
}