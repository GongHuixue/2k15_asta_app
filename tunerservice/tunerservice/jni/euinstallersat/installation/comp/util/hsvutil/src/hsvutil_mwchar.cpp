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
 *             %name: hsvutil_mwchar.c %
 *          %version: TVG_1 %
 *    %date_modified: Thu Feb 26 21:40:39 2009 %
 *       %derived_by: aneeshc %
 */

#include "_hsvutil_mwchar.h"

#include<stdio.h>









/* vdixit added */



FResult CHsvUtil_mwchar_Priv::charsetutil_MbToWc( Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, Bool ExtractShortName)
{
    FResult retval  =   0;
    Nat8 *dstStr = NULL;
    int dstLen = 0;

    int countrycode = sysset_GetSystemCountry();
    if ( countrycode != cids_CountryChina)
    {
        if(*mbstr == 0x1F)
        {
            Nat8 *tmpStr = NULL;
            PrintfNotice("compressed string found start decoding\n");
            istringdec_DtgHuffmanDecoderToString(mbstr, (Address *)(&dstStr), mblen, &dstLen);
            
            /* prepend 0x15 as the output is in UTF-8 format */

            tmpStr = (Nat8*) malloc(dstLen+1);
            if(tmpStr != NULL)
            {
                tmpStr[0] = 0x15;
                memcpy((Address)(&tmpStr[1]), (Address)dstStr, dstLen);
                mblen = dstLen+1;

                if(ExtractShortName == TRUE)
                {
                    retval = MbToWc(tmpStr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
                }
                else
                {
                    retval = MbToWc(tmpStr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
                }
                free(tmpStr);
            }
        }
        else
        {
            if(ExtractShortName == TRUE)
            {
                retval = MbToWc(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
            }
            else
            {
                retval = MbToWc(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
            }
        }
     }
    else 
    {       
        if(ExtractShortName == TRUE)
        {
            retval = MbToWcChina(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
        }
        else
        {
            retval = MbToWcChina(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
        }
    }

    return retval;
}

FResult CHsvUtil_mwchar_Priv::charsetutil_MbToWcEx( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, Bool ExtractShortName)
{
    FResult retval  =   0;
    Nat8 *dstStr = NULL;
    int dstLen = 0, countrycode = sysset_GetSystemCountry();
    

    if ( countrycode != cids_CountryChina)
    {

        if(*mbstr == 0x1F)
        {
            Nat8 *tmpStr = NULL;
            PrintfNotice("compressed string found start decoding\n");
            istringdec_DtgHuffmanDecoderToString(mbstr, (Address *)(&dstStr), mblen, &dstLen);
            
            /* prepend 0x15 as the output is in UTF-8 format */
            tmpStr = (Nat8*)malloc(dstLen+1);
            if(tmpStr != NULL)
            {
                tmpStr[0] = 0x15;
                memcpy((Address)(&tmpStr[1]), (Address)dstStr, dstLen);
                mblen = dstLen + 1;

                if(ExtractShortName == TRUE)
                {
                    retval = MbToWcEx(tmpStr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
                }
                else
                {
                    retval = MbToWcEx(tmpStr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
                }
                free(tmpStr);
            }
        }
        else
        {       
            if(ExtractShortName == TRUE)
            {
                retval = MbToWcEx(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
            }
            else
            {
                retval = MbToWcEx(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
            }
        }
    }
    else
    {       
        if(ExtractShortName == TRUE)
        {
            retval = MbToWcExChina(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractShortName);
        }
        else
        {
            retval = MbToWcExChina(mbstr,mblen,wcstr,wclen,charsetutil2_ExtractNone);
        }
    }
    return retval;

}

FResult CHsvUtil_mwchar_Priv::charsetutil2_MbToWcEx( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, int exinfo)
{
    Nat8 *dstStr = NULL;
    int dstLen = 0;
    FResult retval  =   0;

    int countrycode = sysset_GetSystemCountry();
    if ( countrycode != cids_CountryChina )
    {
        if(*mbstr == 0x1F)
        {
            Nat8 *tmpStr = NULL;
            PrintfNotice("compressed string found start decoding mblen = %d\n",mblen);
            istringdec_DtgHuffmanDecoderToString(mbstr, (Address *)(&dstStr), mblen, &dstLen);

            /* prepend 0x15 as the output is in UTF-8 format */

            tmpStr = (Nat8*)malloc(dstLen+1);
            if(tmpStr != NULL)
            {
                tmpStr[0] = 0x15;
                memcpy((Address)(&tmpStr[1]), (Address)dstStr, dstLen);
                mblen = dstLen+1;
            
                retval =  MbToWcEx(tmpStr,mblen,wcstr,wclen,exinfo);
                free(tmpStr);
            }

        }
        else
        {
            retval =  MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo);
        }
    }
    else
    {
        
        retval =  MbToWcExChina(mbstr,mblen,wcstr,wclen,exinfo);
    }
    return retval;
}

FResult CHsvUtil_mwchar_Priv::charsetutil2_MbToWc(Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, int exinfo)
{
    Nat8 *dstStr = NULL;
    int dstLen = 0;
    FResult retval  =   0;

    int countrycode = sysset_GetSystemCountry();
    if ( countrycode != cids_CountryChina )
    {
        if(*mbstr == 0x1F)
        {
            Nat8 *tmpStr = NULL;
            PrintfNotice("compressed string found start decoding mblen = %d\n",mblen);
            istringdec_DtgHuffmanDecoderToString(mbstr, (Address *)(&dstStr), mblen, &dstLen);
            /* prepend 0x15 as the output is in UTF-8 format */

            tmpStr = (Nat8*)malloc(dstLen+1);

            if(tmpStr != NULL)
            {
                tmpStr[0] = 0x15;
                memcpy((Address)(&tmpStr[1]), (Address)dstStr, dstLen);
                mblen = dstLen+1;

                retval =  MbToWc(tmpStr,mblen,wcstr,wclen,exinfo);
                free(tmpStr);
            }
            
        }
        else
        {
            retval =  MbToWc(mbstr,mblen,wcstr,wclen,exinfo);
        }
    }
    else
    {       
        retval =  MbToWcChina(mbstr,mblen,wcstr,wclen,exinfo);
    }

    return retval;
}


     

void CHsvUtil_mwchar_Priv::ApplyShortName(Nat16 *wcstr, int *wclen)
{
    Bool ShortNameSegment      =   TRUE;
    Bool SegmentAtStartOfString =   TRUE;      
    int InLen   =  *wclen;
    int src = 0;
    *wclen      =  0;

    for(src = 0; src < InLen; src++)
    {
        if( (wcstr[src] == EMPHASIS_START) || (wcstr[src] == EMPHASIS_START_U) )
         {
            if(TRUE == SegmentAtStartOfString)
            {
                *wclen = 0;
                SegmentAtStartOfString  =   FALSE;
            }
            ShortNameSegment        =   TRUE;            
            continue;
        }
        if( (wcstr[src] == EMPHASIS_END) || (wcstr[src] == EMPHASIS_END_U) )
         {
            ShortNameSegment    =   FALSE;           
            continue;
        }
        if(! IsControlCode (wcstr[src]) ) 
        { 
            if ((TRUE == ShortNameSegment) || (TRUE == SegmentAtStartOfString)) 
            { 
                wcstr[*wclen]    =   wcstr[src]; 
                (*wclen)++;   /* This will throw a stupid compilation warning! Ullu ka patta compiler */ 
            } 
        } 
    }
}

void CHsvUtil_mwchar_Priv::ApplyEITShortLongEvent(Nat16 *wcstr, int *wclen)
{
    int InLen   =  *wclen;
    int src = 0;
    *wclen      =  0;

    for(src = 0; src < InLen; src++)
    {
        if(IsControlCode(wcstr[src])) 
        {
            if( (wcstr[src] == 0x8A) || (wcstr[src] == 0xE08A) )
            {
               wcstr[*wclen] = 0x0D; 
               (*wclen)++;
            }
        }
        else
        { 
             wcstr[*wclen]    =   wcstr[src]; 
             (*wclen)++;   /* This will throw a stupid compilation warning! Ullu ka patta compiler */ 
        } 
    }
}


Bool CHsvUtil_mwchar_Priv::IsControlCode(Nat16 c) 
{ 
    if( ( (0x0080 <= c) && (c <= 0x009F) ) || 
        ( (0xe080 <= c) && (c <= 0xe09F) ) ) 
    { 
        return TRUE; 
    } 
    else 
    { 
        return FALSE; 
    } 
} 

FResult CHsvUtil_mwchar_Priv::MbToWcEx( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, int exinfo)
{
    FResult retval          =   0;
    int     i               =   0;
    Bool    translate       =   TRUE;
    Bool    skipcontrols    =   TRUE;    
    if( div_ForceCharacterTable )
    {   
        if( *mbstr <= 0x15) 
        {              
            mbstr++; /* Remove the table id from string and decrement the count variables */
            *wclen = *wclen - 1;            
            mblen = mblen - 1;
        }
        
        if(exinfo == charsetutil2_ExtractShortName)
        {   
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, wclen, FALSE );
            ApplyShortName(wcstr, wclen);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, wclen, FALSE );
            ApplyEITShortLongEvent(wcstr, wclen);
        }
        else
        {
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, wclen, TRUE );
        }

    }
    else
    {   
        if(*mbstr >= 0x20)
           {   /* Case 1 in std */
            if(exinfo == charsetutil2_ExtractShortName)
            {   
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, wclen, FALSE );
                ApplyShortName(wcstr, wclen);
            }
            else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
            {
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, wclen, FALSE );
                ApplyEITShortLongEvent(wcstr, wclen);
            }
            else
            {
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, wclen, TRUE );
            }
        }
        else if (*mbstr <= 0x15) 
        {   /* Case 2 in std. Get the tableid from the first byte and pass */
            int tableid = *mbstr;
            int wclenminusone   =   *wclen - 1;
            if ((tableid == 0x10)  )
            {              
                /* mbstr[0] is 0x10 - indicate multibyte table identification */

                tableid = ((mbstr[1] << 8) | (mbstr[2]));

                mbstr += 3;
                mblen -= 3;

                wclenminusone = mblen;
                if(tableid == 0x5)
                {
                    /* 8859 - 5 - This is already handled with single Byte identification as 0x1 */
                    tableid = 0x1;
                }
                else if(tableid == 0xD)
                {
                    /* 8859 - 13 - This is already handled with single Byte identification as 0x9 */
                    tableid = 0x9;
                }
                else if(tableid == 0x4)
                {
                    tableid = 0x8;
                }                
                else if (tableid == 0x1)
                {
                    translate = FALSE;
                    /* 8859 -1 - Simply copy incoming to out going */
                    for(i = 0; (i < mblen) && (i < (*wclen - 1)); i++)
                    {
                        wcstr[i] = (Nat16)(mbstr[i] & 0xFF);
                    } 
                    /*for( i = 0 ; (i < (mblen / 2) ) && ( i < (*wclen - 1)); i++ )
                    {
                        wcstr[i] = (((((Nat16*)(mbstr))[i]) >> 8) & 0xFF) |  (((((Nat16*)(mbstr))[i]) << 8) & 0xFF00);
                    }*/
                    wcstr[i] = 0;
                }
                    if(tableid == 0x2)
                    {
                    /* 8859 - 2- This is for hungary */
                    //printf("Function : %s Line : %d Venkat: HUNGARY-TABLE-ID %d \r\n",__FUNCTION__,__LINE__,tableid);         
                    tableid = 0x6;
                    }   
            }
            else
            {
                mbstr++;
                mblen--;
            }
            if(translate)
            {
                if((exinfo == charsetutil2_ExtractShortName) || (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent))
                {
                    skipcontrols = FALSE;
                }
                retval  = ling_MbToWcEx( tableid, mbstr, mblen, wcstr, &wclenminusone, skipcontrols );
            }
            if(exinfo == charsetutil2_ExtractShortName)
            {                
                ApplyShortName(wcstr, &wclenminusone);
            }
            else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
            {
                ApplyEITShortLongEvent(wcstr, &wclenminusone);
            }            
            *wclen   =   wclenminusone;
        }
        else
        {
            /* Copy out the input structure as it comes into the output string */

            if( ((*mbstr) == 0 ) )
            {
                /* For si05.mpg */
                for( i = 0 ; (i < (mblen / 2) ) && ( i < (*wclen - 1)); i++ )
                {
                    wcstr[i] = (((((Nat16*)(mbstr))[i]) >> 8) & 0xFF) |  (((((Nat16*)(mbstr))[i]) << 8) & 0xFF00);
                }
                wcstr[i] = 0;
            }
            retval  =   -1;
        }
    }
    wcstr[*wclen]    =   0;  /* Null terminated */
     return retval;
}

FResult CHsvUtil_mwchar_Priv::MbToWc( Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, int exinfo)
{
    FResult retval          =   0;
    int     i               =   0;
    Bool    translate       =   TRUE;
    Bool    skipcontrols    =   TRUE;    

    if( div_ForceCharacterTable )
    {   
        if( *mbstr <= 0x15)
        {              
            mbstr++; /* Remove the table id from string and decrement the count variables */
            wclen = wclen - 1;            
            mblen = mblen - 1;
        }
        
        if(exinfo == charsetutil2_ExtractShortName)
        {   
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, &wclen, FALSE );
            ApplyShortName(wcstr, &wclen);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, &wclen, FALSE );
            ApplyEITShortLongEvent(wcstr, &wclen);
        } 
		else if (exinfo == charsetutil2_ExtractBatLrnChannelListName) /* Tricolor Channel List Name from Character Table 0 */
        {
			retval  = ling_MbToWcEx( (0), mbstr, mblen, wcstr, &wclen, TRUE );
		} else if (exinfo == charsetutil2_ExtractBatLrnChannelListTranslation) /* Tricolor Channel List Name Translation from Character Table 1 */
		{
			retval  = ling_MbToWcEx( (1), mbstr, mblen, wcstr, &wclen, TRUE );
		}
        else
        {
            retval  = ling_MbToWcEx( (div_RegionalCharacterTable), mbstr, mblen, wcstr, &wclen, TRUE );
        }

    }
    else
    {   
        if(*mbstr >= 0x20)
        {   /* Case 1 in std */
            if(exinfo == charsetutil2_ExtractShortName)
            {   
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, &wclen, FALSE );
                ApplyShortName(wcstr, &wclen);
            }
            else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
            {
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, &wclen, FALSE );
                ApplyEITShortLongEvent(wcstr, &wclen);
            }
			else if (exinfo == charsetutil2_ExtractBatLrnChannelListName) /* Tricolor Channel List Name from Character Table 0 */
	        {
				retval  = ling_MbToWcEx( (0), mbstr, mblen, wcstr, &wclen, TRUE );
				translate = FALSE;
			} else if (exinfo == charsetutil2_ExtractBatLrnChannelListTranslation) /* Tricolor Channel List Name Translation from Character Table 1 */
			{
				retval  = ling_MbToWcEx( (1), mbstr, mblen, wcstr, &wclen, TRUE );
				translate = FALSE;
			}
            else
            {
                retval  = ling_MbToWcEx( (div_DefaultCharacterTable), mbstr, mblen, wcstr, &wclen, TRUE );
            }
        }
        else if (*mbstr <= 0x15) 
        {   /* Case 2 in std. Get the tableid from the first byte and pass */
            int tableid = *mbstr;
            int wclenminusone   =   wclen - 1;
            if (tableid == 0x10)
            {              
                /* mbstr[0] is 0x10 - indicate multibyte table identification */

                tableid = ((mbstr[1] << 8) | (mbstr[2]));

                mbstr += 3;
                mblen -= 3;

                if(tableid == 0x5)
                {
                    /* 8859 - 5 - This is already handled with single Byte identification as 0x1 */
                    tableid = 0x1;
                }
                else if(tableid == 0xD)
                {
                    /* 8859 - 13 - This is already handled with single Byte identification as 0x9 */
                    tableid = 0x9;
                }
                else if(tableid == 0x4)
                {
                    tableid = 0x8;
                }
                else if (tableid == 0x1)
                {
                    translate = FALSE;
                    /* 8859 -1 - Simply copy incoming to out going */
                    for(i = 0; (i < mblen) && (i < (wclen - 1)); i++)
                    {
                        wcstr[i] = (Nat16)(mbstr[i] & 0xFF);
                    }
                    /*for( i = 0 ; (i < (mblen / 2) ) && ( i < (wclen - 1)); i++ )
                    {
                        wcstr[i] = (((((Nat16*)(mbstr))[i]) >> 8) & 0xFF) |  (((((Nat16*)(mbstr))[i]) << 8) & 0xFF00);
                    } */
                    wcstr[i] = 0;
                }  
                    if(tableid == 0x2)
                    {
                    /* 8859 - 2- This is for hungary */
                    //printf("Function : %s Line : %d Venkat: HUNGARY-TABLE-ID %d \r\n",__FUNCTION__,__LINE__,tableid);         
                    tableid = 0x6;
                    }           
            }
            else
            {
                mbstr++;
                mblen--;
            }
            if(translate)
            {
                if((exinfo == charsetutil2_ExtractShortName) || (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent))
                {
                    skipcontrols = FALSE;
                }
                retval  = ling_MbToWcEx( tableid, mbstr, mblen, wcstr, &wclenminusone, skipcontrols );
            }
            if(exinfo == charsetutil2_ExtractShortName)
            {                
                ApplyShortName(wcstr, &wclenminusone);
            }
            else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
            {
                ApplyEITShortLongEvent(wcstr, &wclenminusone);
            }            
            wclen   =   wclenminusone;
        }
        else
        {
            /* Copy out the input structure as it comes into the output string */

            if( ((*mbstr) == 0 ) )
            {
                /* For si05.mpg */
                for( i = 0 ; (i < (mblen / 2) ) && ( i < (wclen - 1)); i++ )
                {
                    wcstr[i] = (((((Nat16*)(mbstr))[i]) >> 8) & 0xFF) |  (((((Nat16*)(mbstr))[i]) << 8) & 0xFF00);
                }
                wcstr[i] = 0;
            }
        
           

            retval  =   -1;
        }
    }
    wcstr[wclen]    =   0;  /* Null terminated */
    return retval;
}

FResult CHsvUtil_mwchar_Priv::MbToWcExChina( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, int exinfo)
{
    FResult retval          =   0;        
    if(*mbstr >= 0x20)
    {   /* Case 1 in std */
        /* Starts with english chars but may contain chinese characters */
        if(exinfo == charsetutil2_ExtractShortName)
        {                   
            retval  = ling_MbToWcChina( mbstr, mblen, wcstr, wclen);
            ApplyShortName(wcstr, wclen);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcChina( mbstr, mblen, wcstr, wclen);
            ApplyEITShortLongEvent(wcstr, wclen);
        }
        else
        {
            retval  = ling_MbToWcChina( mbstr, mblen, wcstr, wclen);
        }
    }
    else if ( *mbstr <= 0x15) 
    {  
        /* Case 2 in std. Get the tableid from the first byte and pass */
        /* have a table id so pass it to ling and handle there */
        int tableid = *mbstr;
        int wclenminusone   =   *wclen - 1;
        mbstr++;
        if(exinfo == charsetutil2_ExtractShortName)
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, FALSE );
            ApplyShortName(wcstr, &wclenminusone);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, FALSE );
            ApplyEITShortLongEvent(wcstr, &wclenminusone);
        }
        else
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, TRUE );
        }
        *wclen   =   wclenminusone;
    }
    else
    {
        /* Starts with Chinese Characters handle this but may also contain English characters */                        
        retval  = ling_MbToWcChina( mbstr, mblen, wcstr, wclen);
    }    
    wcstr[*wclen]    =   0;  /* Null terminated */     
    return retval;
}

FResult CHsvUtil_mwchar_Priv::MbToWcChina( Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, int exinfo)
{
    FResult retval          =   0;
    if(*mbstr >= 0x20)
    {   /* Case 1 in std */
        /* Starts with english chars but may contain chinese characters */
        if(exinfo == charsetutil2_ExtractShortName)
        {                   
            retval  = ling_MbToWcChina( mbstr, mblen, wcstr, &wclen);
            ApplyShortName(wcstr, &wclen);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcChina( mbstr, mblen, wcstr, &wclen);
            ApplyEITShortLongEvent(wcstr, &wclen);
        }
        else
        {
            retval = ling_MbToWcChina( mbstr, mblen, wcstr, &wclen);
        }
    }
    else if (*mbstr <= 0x15) 
    {   /* Case 2 in std. Get the tableid from the first byte and pass */
        /* have a table id so pass it to ling and handle there */
        int tableid = *mbstr;
        int wclenminusone   =   wclen - 1;
        mbstr++;
        if(exinfo == charsetutil2_ExtractShortName)
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, FALSE );
            ApplyShortName(wcstr, &wclenminusone);
        }
        else if( (exinfo == charsetutil2_ExtractEITShortEvent) || (exinfo == charsetutil2_ExtractEITExtendedEvent) )
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, FALSE );
            ApplyEITShortLongEvent(wcstr, &wclenminusone);
        }
        else
        {
            retval  = ling_MbToWcEx( tableid, mbstr, mblen - 1, wcstr, &wclenminusone, TRUE );
        }
        wclen   =   wclenminusone;
    }
    else
    {           
        /* Starts with Chinese Characters handle this, but may also contain English characters */                       
        retval  = ling_MbToWcChina( mbstr, mblen, wcstr, &wclen);           
    }
    wcstr[wclen]    =   0;  /* Null terminated */
    return retval;
}
/******************************************************************************/

