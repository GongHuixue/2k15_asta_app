#include"_hsvmpeg_m.h"

#include<hsvmpeg_errorids.h>

#include<pat_Parser.h>

#include<pmt_Parser.h>


TRACESYMBOL(m, "dvb/mpegtables/hsvmpeg_m")

/******************************************************************************/














#ifdef WIN32

#else

#endif





/***********************************************/

/***********************************************/
/*  Static variables */
/***********************************************/
HsvTSData CHsvMpegDataManager_Priv::s__ProgramData[HsvDmxLast];

Nat16 CHsvMpegDataManager_Priv::s__CurrentProgramNo[HsvDmxLast];

Semaphore CHsvMpegDataManager_Priv::s__SubscriptionSem[HsvDmxLast];

Pump CHsvMpegDataManager_Priv::s__mMpegPump = -1;

Pump CHsvMpegDataManager_Priv::s__mMonitorProgramPmp = -1;

Nat16 CHsvMpegDataManager_Priv::s__teletextPID;



/*****************************************************************************/
#if 0
/** Within clauses added here */
//#define langids_MaxNumberOfLanguages	((int)0x2E)

#endif
/*****************************************************************************/


#ifndef __cplusplus

#else

#endif






Nat8 CHsvMpegDataManager_Priv::s__pat_mBuffer[4*1024];

Bool CHsvMpegDataManager_Priv::pat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = pat_mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    static Typepat_Parser  pat_Parser;
    Bool retval = TRUE;
    int dummy, tsloopIndex = 0, tableLen = 0;

    if (secondarySectionSize > 0)
     {
          memcpy(ptr, PrimarySectionStartAddress, primarySectionSize);
          memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
     }
      else
      {
                  ptr = PrimarySectionStartAddress;
      }
    v32 = GET32(0);
    tableLen = HSV_GETSECTION_LENGTH(ptr);
   pat_Parser.TsLoopDataNum=0;
    pat_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    pat_Parser.section_length = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    pat_Parser.ts_id = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    pat_Parser.version_no = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    ptr += 8;
    tableLen = tableLen - 8;
    v32 = GET32( 0);
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 50 ))
    {
        pat_Parser.programList[tsloopIndex].program_number = GETNBITS(v32, 0,16);
        dummy = GETNBITS(v32,16,3);
        pat_Parser.programList[tsloopIndex].PID = GETNBITS(v32, 19,13);
        tsloopIndex++;
        ptr += 4;
        tableLen -= 4;
        v32 = GET32( 0);
    }//endwhile tsloop
    v32 = GET32( 4);
    dummy = GETNBITS(v32,0,32);
    pat_Parser.TsLoopDataNum = tsloopIndex;
    retval = retval && pop_PopulatePAT(demux, &pat_Parser, code);
    return TRUE;
}//end function


/* !! WARNING !!!:
    This file is auto - generated from Parser Tool.
    ** THIS FILE IS EDITED as for correctness in calling populatePAT call.
    ** Some descriptor parsing is added externally
    ** !! IF MODIFIED PLEASE CHECK FOR CHANGES and MERGE !!
    ** Check for "modified" lines
*/

Nat8 CHsvMpegDataManager_Priv::s__pmt_mBuffer[4*1024];

Bool CHsvMpegDataManager_Priv::pmt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = pmt_mBuffer;
    Nat8          *temp = NULL;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    static Typepmt_Parser  pmt_Parser;
    Bool retval = TRUE;
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0, tableLen = 0, loop1length = 0, templen = 0;
    if (secondarySectionSize > 0)
     {
          memcpy(ptr, PrimarySectionStartAddress, primarySectionSize);
          memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
     }
    else if(PrimarySectionStartAddress)
	{  
        ptr = PrimarySectionStartAddress;
	}
	else
	{
		TraceNotice(m,"ERROR: %s: %d",__FUNCTION__,__LINE__);
	}
    v32 = GET32(0);
    tableLen = HSV_GETSECTION_LENGTH(ptr);
    memset(&pmt_Parser, 0, sizeof(pmt_Parser));
   pmt_Parser.PRDNum=0;
   pmt_Parser.TsLoopDataNum=0;
    pmt_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    pmt_Parser.section_length = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    pmt_Parser.program_number = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    pmt_Parser.version_no = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,3);
    pmt_Parser.PCR_Pid = GETNBITS(v32,11,13);
    dummy = GETNBITS(v32,24,4);
    v32 = GET32( 10);
    pmt_Parser.program_info_length = GETNBITS(v32,4,12);
    ptr += 12;
    tableLen = tableLen - 12;
    v32 = GET32( 0);
    while(loopcount < pmt_Parser.program_info_length)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8);
        descLen = GETNBITS(v32,8, 8);
        switch(descTag) {
        case 0x55:
        if(pmt_Parser.PRDNum<2)
        {
             pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].DescriptorTag = GETNBITS(v32,0,8);
             pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].DescriptorLen = GETNBITS(v32,8,8);
             pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].CountryRatingNum = 0;//GETNBITS(v32,16,0);
                 ptr += 2;
                 v32 = GET32( 0 );
            loop1index = 0, loop1length = 0, templen = sizeof(pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].CountryRating)*80 ;
            while( loop1length< HSV_PARSER_MIN(pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].DescriptorLen, templen ))
            {
//                int minLength = 0;
                pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].CountryRating[loop1index].CountryCode= GETNBITS(v32,0, 24);
                pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].CountryRating[loop1index].Rating= GETNBITS(v32,24, 8);
                loop1length += 4;
                loop1index++;
                ptr += 4;
                v32 = GET32( 0);
                }
                pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].CountryRatingNum = loop1index;
     pmt_Parser.ParentalRating_Descriptor[pmt_Parser.PRDNum].DescriptorValid = TRUE;
     pmt_Parser.PRDNum++;
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
    ptr += 0;
    tableLen = tableLen - 0;
    v32 = GET32( 0);
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 10 ))
    {
   pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count=0;
   pmt_Parser.esData[tsloopIndex].teletext_desc_count=0;
   pmt_Parser.esData[tsloopIndex].subtitle_dec_count=0;
   pmt_Parser.esData[tsloopIndex].stream_id_desc_count=0;
   pmt_Parser.esData[tsloopIndex].iso_lang_desc_count=0;
   pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count=0;
   pmt_Parser.esData[tsloopIndex].avc_desc_count=0;
        pmt_Parser.esData[tsloopIndex].stream_type = GETNBITS(v32, 0,8);
        dummy = GETNBITS(v32,8,3);
        pmt_Parser.esData[tsloopIndex].es_pid = GETNBITS(v32, 11,13);
        dummy = GETNBITS(v32,24,4);
        v32 = GET32( 3);
        pmt_Parser.esData[tsloopIndex].es_info_length = GETNBITS(v32, 4,12);
        ptr += 5;
        tableLen = tableLen - 5;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < pmt_Parser.esData[tsloopIndex].es_info_length)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8);
            descLen = GETNBITS(v32,8, 8);
            switch(descTag) {
            case 0x46:
            if(pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].VBITeletextData)*5 ;
                 while( loop1length< HSV_PARSER_MIN(pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].DescrptorLength, templen))
                 {
//                 int minLength = 0;
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].VBITeletextData[loop1index].lang_code = GETNBITS(v32,0, 24);
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].VBITeletextData[loop1index].type = GETNBITS(v32,24, 5);
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].VBITeletextData[loop1index].magazine_no = GETNBITS(v32,29, 3);
                 v32 = GET32( 4);
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].VBITeletextData[loop1index].page_no = GETNBITS(v32,0, 8);
                loop1length += 5;
                loop1index++;
                ptr += 5;
                 v32 = GET32( 0);
                 }
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].loopCount = loop1index;
                 pmt_Parser.esData[tsloopIndex].VBI_teletext_Descriptor[pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].VBI_TT_desc_count++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);

            v32 = GET32( 0);
            break;

            case 0x56:
            if(pmt_Parser.esData[tsloopIndex].teletext_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].teletextLoop)*5 ;
                 while( loop1length< HSV_PARSER_MIN(pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].DescrptorLength, templen))
                 {
//                 int minLength = 0;
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].teletextLoop[loop1index].lang_code = GETNBITS(v32,0, 24);
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].teletextLoop[loop1index].type = GETNBITS(v32,24, 5);
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].teletextLoop[loop1index].magazine_no = GETNBITS(v32,29, 3);
                 v32 = GET32( 4);
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].teletextLoop[loop1index].page_no = GETNBITS(v32,0, 8);
                loop1length += 5;
                loop1index++;
                ptr += 5;
                 v32 = GET32( 0);
                 }
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].loopCount = loop1index;
                 pmt_Parser.esData[tsloopIndex].Teletext_Descriptor[pmt_Parser.esData[tsloopIndex].teletext_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].teletext_desc_count++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);

            v32 = GET32( 0);
            break;

            case 0x59:
            if(pmt_Parser.esData[tsloopIndex].subtitle_dec_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].DescrptorLength = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].subtitleData)*5 ;
                 while( loop1length< HSV_PARSER_MIN(pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].DescrptorLength, templen))
                 {
//                 int minLength = 0;
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].subtitleData[loop1index].lang_code = GETNBITS(v32,0, 24);
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].subtitleData[loop1index].type = GETNBITS(v32,24, 8);
                 v32 = GET32( 4);
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].subtitleData[loop1index].comp_page_id = GETNBITS(v32,0, 16);
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].subtitleData[loop1index].ancillary_page_id = GETNBITS(v32,16, 16);
                loop1length += 8;
                loop1index++;
                ptr += 8;
                 v32 = GET32( 0);
                 }
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].loopCount = loop1index;
                 pmt_Parser.esData[tsloopIndex].Subtitling_Descriptor[pmt_Parser.esData[tsloopIndex].subtitle_dec_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].subtitle_dec_count++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);

            v32 = GET32( 0);
            break;

            case 0x52:
            if(pmt_Parser.esData[tsloopIndex].stream_id_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].Stream_identifier_Descriptor[pmt_Parser.esData[tsloopIndex].stream_id_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].Stream_identifier_Descriptor[pmt_Parser.esData[tsloopIndex].stream_id_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].Stream_identifier_Descriptor[pmt_Parser.esData[tsloopIndex].stream_id_desc_count].component_tag = GETNBITS(v32, 16,8);
                 pmt_Parser.esData[tsloopIndex].Stream_identifier_Descriptor[pmt_Parser.esData[tsloopIndex].stream_id_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].stream_id_desc_count++;
           ptr += 3;
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

            case 0x0A:
            if(pmt_Parser.esData[tsloopIndex].iso_lang_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].LanguageLoop)*5 ;
                 while( loop1length< HSV_PARSER_MIN(pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].DescrptorLength, templen))
                 {
//                 int minLength = 0;
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].LanguageLoop[loop1index].lang = GETNBITS(v32,0, 24);
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].LanguageLoop[loop1index].audioType = GETNBITS(v32,24, 8);
                loop1length += 4;
                loop1index++;
                ptr += 4;
                 v32 = GET32( 0);
                 }
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].loopCount = loop1index;
                 pmt_Parser.esData[tsloopIndex].ISO_Lang_Descriptor[pmt_Parser.esData[tsloopIndex].iso_lang_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].iso_lang_desc_count++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);

            v32 = GET32( 0);
            break;

            case 0x66:
            if(pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].data_broadcast_id = GETNBITS(v32, 16,16);
                     pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].id_selector_length = descLen - 2;
                     descLoopLen = HSV_PARSER_MIN(100,pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].id_selector_length);
                     ptr += 4;
                     memcpy(pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].selector_byte,ptr,descLoopLen);
                     ptr += pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].id_selector_length;
                     v32 = GET32( 0);
                     pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].id_selector_length = descLoopLen;
                 pmt_Parser.esData[tsloopIndex].Data_broadcast_ID_Descriptor[pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].data_bc_id_desc_count++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);

            v32 = GET32( 0);
            break;

            case 0x28:
            if(pmt_Parser.esData[tsloopIndex].avc_desc_count<2)
            {
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].profile_idc = GETNBITS(v32, 16,8);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set0_flag = GETNBITS(v32, 24,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set1_flag  = GETNBITS(v32, 25,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set2_flag  = GETNBITS(v32, 26,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set3_flag = GETNBITS(v32, 27,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set4_flag = GETNBITS(v32, 28,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].constraint_set5_flag = GETNBITS(v32, 29,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].AVC_compatible_flags = GETNBITS(v32, 30,2);
                 v32 = GET32( 4);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].level_idc = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].AVC_still_present = GETNBITS(v32, 8,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].AVC_24_hour_picture_flag = GETNBITS(v32, 9,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].frame_packing_SEI_not_present_flag = GETNBITS(v32, 10,1);
                 pmt_Parser.esData[tsloopIndex].AVC_Descriptor[pmt_Parser.esData[tsloopIndex].avc_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].avc_desc_count++;
           ptr += 5;
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

            case 0x7C:
            {
                if(pmt_Parser.esData[tsloopIndex].aac_desc_count < 2)
                {
                 pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].profile_and_level = GETNBITS(v32, 16,8);
                 if (descLen > 1) {
                    pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].aac_type_flag = GETNBITS(v32, 24,1);
                    if (1 == pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].aac_type_flag)
                    {
                        pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].aac_type = *(ptr + 4);
                    }
                 }
                 pmt_Parser.esData[tsloopIndex].AAC_Descriptor[pmt_Parser.esData[tsloopIndex].aac_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].aac_desc_count++;
                }
                ptr += 2 + descLen;
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);
                v32 = GET32( 0);
                break;
            }

            case 0x6A:
            {
                if(pmt_Parser.esData[tsloopIndex].ac3_desc_count < 2)
                {
                 temp = ptr;
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].component_type_flag = GETNBITS(v32, 16,1);
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].bsid_flag = GETNBITS(v32, 17,1);
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].mainid_flag = GETNBITS(v32, 18,1);
                 pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].asvc_flag = GETNBITS(v32, 19,1);
                 temp += 3;
                 if (pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].component_type_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].component_type = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].bsid_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].bsid = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].mainid_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].mainid = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].asvc_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].asvc = *temp++;
                 }
                pmt_Parser.esData[tsloopIndex].AC3_Descriptor[pmt_Parser.esData[tsloopIndex].ac3_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].ac3_desc_count++;
                }
                ptr += 2 + descLen;
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);
                v32 = GET32( 0);
                break;
            }

            case 0x7A:
            {
                if(pmt_Parser.esData[tsloopIndex].eac3_desc_count < 2)
                {
                 temp = ptr;
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].component_type_flag = GETNBITS(v32, 16,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].bsid_flag = GETNBITS(v32, 17,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].mainid_flag = GETNBITS(v32, 18,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].asvc_flag = GETNBITS(v32, 19,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].mixinfoexists = GETNBITS(v32, 20,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream1_flag = GETNBITS(v32, 21,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream2_flag = GETNBITS(v32, 22,1);
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream3_flag = GETNBITS(v32, 23,1);
                 temp += 3;
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].component_type_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].component_type = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].bsid_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].bsid = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].mainid_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].mainid = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].asvc_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].asvc = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream1_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream1 = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream2_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream2 = *temp++;
                 }
                 if (pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream3_flag)
                 {
                    pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].substream3 = *temp++;
                 }
                 pmt_Parser.esData[tsloopIndex].EAC3_Descriptor[pmt_Parser.esData[tsloopIndex].eac3_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].eac3_desc_count++;
                }
                ptr += 2 + descLen;
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);
                v32 = GET32( 0);
                break;
            }

            case 0x7f:
            {
                if(pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count < 2)
                {
                 temp = ptr;
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].DescriptorTag = GETNBITS(v32, 0,8);
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].DescrptorLength = GETNBITS(v32, 8,8);
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].tag_extension = GETNBITS(v32, 16,8);
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].mix_type = GETNBITS(v32, 24,1);
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].editorial_classification = GETNBITS(v32, 25,5);
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].lang_code_present = GETNBITS(v32, 31,1);
                 if (pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].lang_code_present)
                 {
                    temp += 4;
                    v32 = (((((temp[0])<<HSV_BYTES3) | ((temp[1])<<HSV_BYTES2) | ((temp[2])<<HSV_BYTE) | (temp[3]))));
                    pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].lang_code = GETNBITS(v32,0, 24);
                 }
                 pmt_Parser.esData[tsloopIndex].Supplementary_audio_Descriptor[pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count].DescriptorValid = TRUE;
                 pmt_Parser.esData[tsloopIndex].suppl_audio_desc_count++;

                }
                ptr += 2 + descLen;
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);
                v32 = GET32( 0);
                break;
            }

            default:
            loopcount += 2 + descLen;
            ptr += 2 + descLen;
            tableLen = tableLen - (2 + descLen);
            v32 = GET32( 0);
            break;
            }//endswitch
        }//endwhile descloop
    tsloopIndex++;
    loopcount = 0;
    //pmt_Parser.TsLoopDataNum = tsloopIndex;
    //retval = retval && pop_PopulatePMT(&PMT_Parser);
    //tsloopIndex = 0;
    }//endwhile tsloop
    pmt_Parser.TsLoopDataNum = tsloopIndex;
    retval = retval && pop_PopulatePMT(demux, &pmt_Parser, code);
    dummy = GETNBITS(v32,0,32);
    return TRUE;
}


// static void DeleteRecord ( HsvDemux dmx, Nat8 property, void * addr );






// static void LogError(int prio, int ErrorId);





// static Bool CompareBpidInfo(HsvPMTBasicPidInfo * comp1,
        // HsvPMTBasicPidInfo * comp2);








/********************************************************/
/* Functions of the IHsvPower interface, provided by this component */
/********************************************************/
void CHsvMpegDataManager_Priv::pow_Init(void)
{
    mMpegPump = pmp_PmpCreateEx(pen_PumpEngine, mMpegPumpHandler,
            FALSE, "hsvmpeg: Mpeg Pump");
    mMonitorProgramPmp = pmp_PmpCreateEx(pen_PumpEngine,
            mMonitorProgramPmpHandler, FALSE,
            "hsvmpeg: Monitor Program Pump");
    ASSERT(mMpegPump > 0);
    ASSERT(mMonitorProgramPmp > 0);
}

/********************************************************/
void CHsvMpegDataManager_Priv::pow_TurnOn(void)
{
    HsvDemux DemuxIterator;
    for (DemuxIterator = HsvDmxMain; DemuxIterator < HsvDmxAux;
            DemuxIterator++) {
        ProgramData[DemuxIterator].programs = 0;
        ProgramData[DemuxIterator].subscriptionID = HSV_INVALID_SCT_REQUEST;
        ProgramData[DemuxIterator].PatVersionNo = HSV_INVALID_VERSION;
        ProgramData[DemuxIterator].tsID = -1;

        ClearPmtSectionData(DemuxIterator);

        SubscriptionSem[DemuxIterator] = rtk_SemCreate();
    }

    ClearPropertyTables(HsvDmxMain);
    ClearPropertyTables(HsvDmxAux);
}

/********************************************************/
void CHsvMpegDataManager_Priv::pow_TurnOff(void)
{
    HsvDemux DemuxIterator;
    for (DemuxIterator = HsvDmxMain; DemuxIterator < HsvDmxAux;
            DemuxIterator++) {
        ProgramData[DemuxIterator].programs = 0;
        ProgramData[DemuxIterator].subscriptionID = HSV_INVALID_SCT_REQUEST;
        ProgramData[DemuxIterator].PatVersionNo = HSV_INVALID_VERSION;
        ProgramData[DemuxIterator].tsID = -1;

        ClearPmtSectionData(DemuxIterator);
        rtk_SemDelete(SubscriptionSem[DemuxIterator]);
    }

    ClearPropertyTables(HsvDmxMain);
    ClearPropertyTables(HsvDmxAux);
}

/********************************************************/
/* Functions of the IHsvSdmEnable interface, provided by this component */
/********************************************************/
void CHsvMpegDataManager_Priv::enable_Enable(HsvDemux dmx)
{
    StartSubscriptions(dmx);
}

/********************************************************/
void CHsvMpegDataManager_Priv::enable_Disable(HsvDemux dmx)
{
    StopSubscriptions(dmx);

    ProgramData[dmx].programs = 0;
    ProgramData[dmx].PatVersionNo = HSV_INVALID_VERSION;

    ClearPmtSectionData(dmx);
    ClearPropertyTables(dmx);
}

/********************************************************/
void CHsvMpegDataManager_Priv::enable_Sync(HsvDemux dmx)
{
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);
    return;
}

/********************************************************/
/* Functions of IHsvMpegSections interface, which is provided by this component */
/********************************************************/
int CHsvMpegDataManager_Priv::mpegsecn_GetNumberofPrograms(HsvDemux dmx)
{
    int numprograms = 0;

    if (ProgramData[dmx].PatVersionNo != (Nat8) HSV_INVALID_VERSION) {
        numprograms = ProgramData[dmx].programs;
    }
    return numprograms;
} /* End of function GetNumberOfPrograms() */

Nat32 CHsvMpegDataManager_Priv::mpegsecn_GetProgramNumber(HsvDemux dmx, int index)
{
    Nat32 RetValue = (Nat32) (-1);

    /* For the CR related to installation of all channels, we will simply return the
     program numbers we saw in the PAT */

    if (index < ProgramData[dmx].programs) {
        RetValue = ProgramData[dmx].programList[index].programNo;
    }

    return RetValue;
}

Bool CHsvMpegDataManager_Priv::mpegsecn_GetComponentInfobyProgramNumber(HsvDemux dmx, int prg,
        HsvComponentInfo * ci)
{
    Bool RetValue = FALSE;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);
    return RetValue;
}

Bool CHsvMpegDataManager_Priv::mpegsecn_GetComponentInfobyIndex(HsvDemux dmx, int index,
        HsvComponentInfo * ci)
{
    /* Fill the HsvComponentInfo pointer with the HsvComponentInfo corresponding to the program
     at the specified index, on the specified demux */
    Bool RetValue = FALSE;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);

    return RetValue;
}

Nat32 CHsvMpegDataManager_Priv::mpegsecn_GetCurrentTsId(HsvDemux dmx)
{

    Nat32 RetValue = (Nat32) (-1);

    if (ProgramData[dmx].PatVersionNo != (Nat8) HSV_INVALID_VERSION) {
        RetValue = ProgramData[dmx].tsID;
    }
    return RetValue;
}

void * CHsvMpegDataManager_Priv::mpegsecn_GetPmtSection(HsvDemux dmx, int prg)
{

    void * RetValue = (void *) NULL;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);
    return RetValue;
} /* End of function GetPmtSection() */

void CHsvMpegDataManager_Priv::mpegsecn_MonitorProgram(HsvDemux dmx, int prg)
{
    /* This function should be 'callable' even if PAT has not been found, so we avoid any
     intialization checks*/
    TraceNotice(m, " %s %d prg %d\n ", __FUNCTION__, __LINE__, prg);
    pmp_PmpSend(mMonitorProgramPmp, ((MONITOR_PROGRAM << 16) | dmx),
            ((prg & 0xffff) << 16));

}/* End of function mpegsecn_MonitorProgram() */

void CHsvMpegDataManager_Priv::mpegsecn_MonitorProgramByIndex(HsvDemux dmx, int prg, int index)
{
    /* This function should be 'callable' even if PAT has not been found, so we avoid any
     intialization checks*/
    /*TraceNotice(m, " %s %d prg %d index %d\n ", __FUNCTION__, __LINE__, prg,
            index);*/
    pmp_PmpSend(mMonitorProgramPmp, ((MONITOR_PROGRAM_BY_INDEX << 16) | dmx),
            (((prg & 0xffff) << 16) | index));

}/* End of function mpegsecn_MonitorProgramByIndex() */

/********************************************************/
/* Functions of IHsvMpegServices interface, which is provided by this component */
/********************************************************/
int CHsvMpegDataManager_Priv::mpegserv_GetLanguageId(char byte1, char byte2, char byte3)
{
    /* Return the language ID of the language corresponding to the three character code */
    /* The 3 character code conforms to the ISO 639-2 B naming convention and the language ID
     that is returned conforms to the integer identifiers defined in IHsvLanguageIds interface */
    int lngid = langids_LangUndefined;

    Nat8 ubyte1 = HSV_TO_LOWER(byte1);
    Nat8 ubyte2 = HSV_TO_LOWER(byte2);
    Nat8 ubyte3 = HSV_TO_LOWER(byte3);

    switch (HSV_MAKE_CHAR_MASK(ubyte1, ubyte2, ubyte3)) {
    case HSV_MAKE_CHAR_MASK('e','n','g'):
        lngid = langids_LangEnglish;
        break;
    case HSV_MAKE_CHAR_MASK('g','e','r'):
    case HSV_MAKE_CHAR_MASK('d','e','u'):
        lngid = langids_LangGerman;
        break;
    case HSV_MAKE_CHAR_MASK('s','w','e'):
        lngid = langids_LangSwedish;
        break;
    case HSV_MAKE_CHAR_MASK('i','t','a'):
        lngid = langids_LangItalian;
        break;
    case HSV_MAKE_CHAR_MASK('f','r','e'):
    case HSV_MAKE_CHAR_MASK('f','r','a'):
        lngid = langids_LangFrench;
        break;
    case HSV_MAKE_CHAR_MASK('s','p','a'):
    case HSV_MAKE_CHAR_MASK('e','s','l'):
    case HSV_MAKE_CHAR_MASK('e','s','p'):
        lngid = langids_LangSpanish;
        break;
    case HSV_MAKE_CHAR_MASK('c','z','e'):
    case HSV_MAKE_CHAR_MASK('c','e','s'):
        lngid = langids_LangCzech;
        break;
    case HSV_MAKE_CHAR_MASK('p','o','l'):
        lngid = langids_LangPolish;
        break;
    case HSV_MAKE_CHAR_MASK('t','u','r'):
        lngid = langids_LangTurkish;
        break;
    case HSV_MAKE_CHAR_MASK('r','u','s'):
        lngid = langids_LangRussian;
        break;
    case HSV_MAKE_CHAR_MASK('g','r','e'):
    case HSV_MAKE_CHAR_MASK('e','l','l'):
        lngid = langids_LangGreek;
        break;
    case HSV_MAKE_CHAR_MASK('b','a','q'):
    case HSV_MAKE_CHAR_MASK('e','u','s'):
        lngid = langids_LangBasque;
        break;
    case HSV_MAKE_CHAR_MASK('c','a','t'):
        lngid = langids_LangCatalan;
        break;
    case HSV_MAKE_CHAR_MASK('s','c','r'):
    case HSV_MAKE_CHAR_MASK('h','r','v'):
        lngid = langids_LangCroatian;
        break;
    case HSV_MAKE_CHAR_MASK('d','a','n'):
        lngid = langids_LangDanish;
        break;
    case HSV_MAKE_CHAR_MASK('d','u','t'):
    case HSV_MAKE_CHAR_MASK('n','l','d'):
        lngid = langids_LangDutch;
        break;
    case HSV_MAKE_CHAR_MASK('f','i','n'):
        lngid = langids_LangFinnish;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','a'):
    case HSV_MAKE_CHAR_MASK('g','a','e'):
        lngid = langids_LangGaelic;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','e'):
    case HSV_MAKE_CHAR_MASK('i','r','i'):
        lngid = langids_LangIrish;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','g'):
        lngid = langids_LangGalligan;
        break;
    case HSV_MAKE_CHAR_MASK('n','o','r'):
        lngid = langids_LangNorwegian;
        break;
    case HSV_MAKE_CHAR_MASK('p','o','r'):
        lngid = langids_LangPortuguese;
        break;
    case HSV_MAKE_CHAR_MASK('s','c','c'):
    case HSV_MAKE_CHAR_MASK('s','r','p'):
        lngid = langids_LangSerbian;
        break;
    case HSV_MAKE_CHAR_MASK('s','l','o'):
    case HSV_MAKE_CHAR_MASK('s','l','k'):
        lngid = langids_LangSlovak;
        break;
    case HSV_MAKE_CHAR_MASK('s','l','v'):
        lngid = langids_LangSlovenian;
        break;
    case HSV_MAKE_CHAR_MASK('w','e','l'):
    case HSV_MAKE_CHAR_MASK('c','y','m'):
        lngid = langids_LangWelsh;
        break;
    case HSV_MAKE_CHAR_MASK('r','u','m'):
    case HSV_MAKE_CHAR_MASK('r','o','n'):
        lngid = langids_LangRomanian;
        break;
    case HSV_MAKE_CHAR_MASK('e','s','t'):
        lngid = langids_LangEstonian;
        break;
    case HSV_MAKE_CHAR_MASK('u','k','r'):
        lngid = langids_LangUkrainian;
        break;
    case HSV_MAKE_CHAR_MASK('a','r','a'):
        lngid = langids_LangArabic;
        break;
    case HSV_MAKE_CHAR_MASK('h','e','b'):
        lngid = langids_LangHebrew;
        break;
    case HSV_MAKE_CHAR_MASK('h','u','n'):
        lngid = langids_LangHungarian;
        break;
    case HSV_MAKE_CHAR_MASK('l','a','v'):
        lngid = langids_LangLatvian;
        break;
    case HSV_MAKE_CHAR_MASK('k','a','z'):
        lngid = langids_LangKazakh;
        break;
    case HSV_MAKE_CHAR_MASK('b','u','l'):
        lngid = langids_LangBulgarian;
        break;
    case HSV_MAKE_CHAR_MASK('c','h','n'):
    case HSV_MAKE_CHAR_MASK('z','h','o'):
        lngid = langids_LangSimplifiedchinese;
        break;
    case HSV_MAKE_CHAR_MASK('l','i','t'):
        lngid = langids_LangLithuanian;
        break;
    case HSV_MAKE_CHAR_MASK('q','a','a'):
    case HSV_MAKE_CHAR_MASK('Q','A','A'):
        lngid = langids_LangOriginalVersion;
        break;
    case HSV_MAKE_CHAR_MASK('m','s','a'):
		lngid = IHsvLanguageIds2_LangBahasaMelayu;
		break;
	case HSV_MAKE_CHAR_MASK('c','m','n'):
		lngid = IHsvLanguageIds2_LangTraditionalChinese;
		break;
    case HSV_MAKE_CHAR_MASK('u','n','d'):
    case HSV_MAKE_CHAR_MASK('U','N','D'):
        if (1) {
            lngid = langids_LangOriginalVersion;
        }
        break;
    case HSV_MAKE_CHAR_MASK('a','d',' '):
    case HSV_MAKE_CHAR_MASK('A','D',' '):
    case HSV_MAKE_CHAR_MASK('a','d','1'):
    case HSV_MAKE_CHAR_MASK('A','D','1'):
    case HSV_MAKE_CHAR_MASK('a','d','2'):
    case HSV_MAKE_CHAR_MASK('A','D','2'):
    case HSV_MAKE_CHAR_MASK('a','d','3'):
    case HSV_MAKE_CHAR_MASK('A','D','3'):
    case HSV_MAKE_CHAR_MASK('a','d','4'):
    case HSV_MAKE_CHAR_MASK('A','D','4'):
    case HSV_MAKE_CHAR_MASK('a','d','5'):
    case HSV_MAKE_CHAR_MASK('A','D','5'):
    case HSV_MAKE_CHAR_MASK('a','d','6'):
    case HSV_MAKE_CHAR_MASK('A','D','6'):
    case HSV_MAKE_CHAR_MASK('a','d','7'):
    case HSV_MAKE_CHAR_MASK('A','D','7'):
    case HSV_MAKE_CHAR_MASK('a','d','8'):
    case HSV_MAKE_CHAR_MASK('A','D','8'):
    case HSV_MAKE_CHAR_MASK('a','d','9'):
    case HSV_MAKE_CHAR_MASK('A','D','9'):
    case HSV_MAKE_CHAR_MASK('Q','A','D'):
    case HSV_MAKE_CHAR_MASK('q','a','d'):
    case HSV_MAKE_CHAR_MASK('N','A','R'):
    case HSV_MAKE_CHAR_MASK('n','a','r'):

        if (1) {
            TraceInfo(m, "euApp: adn is assigned to LangAudioDescription");
            lngid = langids_LangAudioDescription;
        }
        break;
    default:
        break;
    }

    return lngid;
}

Bool CHsvMpegDataManager_Priv::mpegserv_IsProgramPresent(HsvDemux dmx, int prg)
{
    int index;
    Bool retval = FALSE;

    for (index = 0; index < ProgramData[dmx].programs; index++) {
        if (ProgramData[dmx].programList[index].programNo == prg) {
            retval = TRUE;
            break;
        }
    }
    return retval;
}

void * CHsvMpegDataManager_Priv::mpegserv_GetCcDescriptor(HsvDemux dmx, int prg, Bool * IsDescriptorParsed)
{
    HsvDescriptor * RetValue = (HsvDescriptor *) NULL;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);

    return RetValue;
}

void * CHsvMpegDataManager_Priv::mpegserv_GetCaDescriptor(HsvDemux dmx, int prg, Bool * IsDescriptorParsed)
{
    HsvDescriptor * RetValue = (HsvDescriptor *) NULL;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);

    return RetValue;
}

void * CHsvMpegDataManager_Priv::mpegserv_GetAc3Descriptor(HsvDemux dmx, int prg, Bool * IsDescriptorParsed)
{
    HsvDescriptor * RetValue = (HsvDescriptor *) NULL;
    TraceNotice(m, "WARNING: return: %s is void\n", __FUNCTION__);

    return RetValue;
}

void CHsvMpegDataManager_Priv::mpegserv_ReadTsPacketFields (Nat32 dmx, HsvSdmTsSection* section)
{
    return;
}

/*******************************************************************************/

HSVCOMPAREKEY( basicpidinfoconfmain, Primary, HsvPMTBasicPidInfo, ProgramNumber)

 HSVCOMPAREKEY( basicpidinfoconfmain, Secondary, HsvPMTBasicPidInfo, VideoPid)

 HSVCOMPAREKEY( basicpidinfoconfmain, Teritiary, HsvPMTBasicPidInfo, PcrPid)
/* Not used */

 HSVCOMPAREKEY( basicpidinfoconfmain, Quaternary, HsvPMTBasicPidInfo, PcrPid)


 HSVCOMPAREKEY( subtitleconfmain, Primary, HsvPMTSubtitlingInfo, ProgramNumber)

 HSVCOMPAREKEY( subtitleconfmain, Secondary, HsvPMTSubtitlingInfo, LangCode)

 HSVCOMPAREKEY( subtitleconfmain, Teritiary, HsvPMTSubtitlingInfo, Type)
/* Not used */

 HSVCOMPAREKEY( subtitleconfmain, Quaternary, HsvPMTSubtitlingInfo, Type)


 HSVCOMPAREKEY( teletextconfmain, Primary, HsvPMTTeletextInfo, ProgramNumber)

 HSVCOMPAREKEY( teletextconfmain, Secondary, HsvPMTTeletextInfo, LangCode)

 HSVCOMPAREKEY( teletextconfmain, Teritiary, HsvPMTTeletextInfo, Type)
/* Not used */

 HSVCOMPAREKEY( teletextconfmain, Quaternary, HsvPMTTeletextInfo, Type)


 HSVCOMPAREKEY( audioinfoconfmain, Primary, HsvPMTAudioInfo, ProgramNumber)

 HSVCOMPAREKEY( audioinfoconfmain, Secondary, HsvPMTAudioInfo, LangCode)

 HSVCOMPAREKEY( audioinfoconfmain, Teritiary, HsvPMTAudioInfo, AudioType)
/* Not used */

 HSVCOMPAREKEY( audioinfoconfmain, Quaternary, HsvPMTAudioInfo, AudioType)


 HSVCOMPAREKEY( componenttaginfomain, Primary, HsvPMTComponentTagInfo,ProgramNumber)

 HSVCOMPAREKEY( componenttaginfomain, Secondary, HsvPMTComponentTagInfo,ComponentTag)

 HSVCOMPAREKEY( componenttaginfomain, Teritiary, HsvPMTComponentTagInfo, Pid)
/* Not used */

 HSVCOMPAREKEY( componenttaginfomain, Quaternary, HsvPMTComponentTagInfo, Pid)


 HSVCOMPAREKEY( databroadcastinfomain, Primary, HsvPMTDatabroadcastInfo,ProgramNumber)

 HSVCOMPAREKEY( databroadcastinfomain, Secondary, HsvPMTDatabroadcastInfo, OUI)

 HSVCOMPAREKEY( databroadcastinfomain, Teritiary, HsvPMTDatabroadcastInfo, Pid)
/* Not used */

 HSVCOMPAREKEY( databroadcastinfomain, Quaternary, HsvPMTDatabroadcastInfo,Pid)

/* Aux */

 HSVCOMPAREKEY( basicpidinfoconfaux, Primary, HsvPMTBasicPidInfo, ProgramNumber)

 HSVCOMPAREKEY( basicpidinfoconfaux, Secondary, HsvPMTBasicPidInfo, VideoPid)

 HSVCOMPAREKEY( basicpidinfoconfaux, Teritiary, HsvPMTBasicPidInfo, PcrPid)

 HSVCOMPAREKEY( basicpidinfoconfaux, Quaternary, HsvPMTBasicPidInfo, PcrPid)


 HSVCOMPAREKEY( subtitleconfaux, Primary, HsvPMTSubtitlingInfo, ProgramNumber)

 HSVCOMPAREKEY( subtitleconfaux, Secondary, HsvPMTSubtitlingInfo, LangCode)

 HSVCOMPAREKEY( subtitleconfaux, Teritiary, HsvPMTSubtitlingInfo, Type)

 HSVCOMPAREKEY( subtitleconfaux, Quaternary, HsvPMTSubtitlingInfo, Type)


 HSVCOMPAREKEY( teletextconfaux, Primary, HsvPMTTeletextInfo, ProgramNumber)

 HSVCOMPAREKEY( teletextconfaux, Secondary, HsvPMTTeletextInfo, LangCode)

 HSVCOMPAREKEY( teletextconfaux, Teritiary, HsvPMTTeletextInfo, Type)

 HSVCOMPAREKEY( teletextconfaux, Quaternary, HsvPMTTeletextInfo, Type)


 HSVCOMPAREKEY( audioinfoconfaux, Primary, HsvPMTAudioInfo, ProgramNumber)

 HSVCOMPAREKEY( audioinfoconfaux, Secondary, HsvPMTAudioInfo, LangCode)

 HSVCOMPAREKEY( audioinfoconfaux, Teritiary, HsvPMTAudioInfo, AudioType)

 HSVCOMPAREKEY( audioinfoconfaux, Quaternary, HsvPMTAudioInfo, AudioType)


 HSVCOMPAREKEY( componenttaginfoaux, Primary, HsvPMTComponentTagInfo,ProgramNumber)

 HSVCOMPAREKEY( componenttaginfoaux, Secondary, HsvPMTComponentTagInfo,ComponentTag)

 HSVCOMPAREKEY( componenttaginfoaux, Teritiary, HsvPMTComponentTagInfo, Pid)

 HSVCOMPAREKEY( componenttaginfoaux, Quaternary, HsvPMTComponentTagInfo, Pid)



 HSVCOMPAREKEY( databroadcastinfoaux, Primary, HsvPMTDatabroadcastInfo,ProgramNumber)

 HSVCOMPAREKEY( databroadcastinfoaux, Secondary, HsvPMTDatabroadcastInfo, OUI)

 HSVCOMPAREKEY( databroadcastinfoaux, Teritiary, HsvPMTDatabroadcastInfo, Pid)

 HSVCOMPAREKEY( databroadcastinfoaux, Quaternary, HsvPMTDatabroadcastInfo,Pid)


#if 0

Nat8 CHsvMpegDataManager_Priv::basicpidinfoconfmain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}

Nat8 CHsvMpegDataManager_Priv::subtitleconfmain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}

Nat8 CHsvMpegDataManager_Priv::teletextconfmain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}

Nat8 CHsvMpegDataManager_Priv::audioinfoconfmain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}

Nat8 CHsvMpegDataManager_Priv::componenttaginfomain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}

Nat8 CHsvMpegDataManager_Priv::databroadcastinfomain_CompareQuaternaryKey(Nat32 key, Address data)
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}
#endif
/*******************************************************************************/

/**
 **  Function to start section filter for current program PMT ONLY
 */

void CHsvMpegDataManager_Priv::StartProgramfilters(HsvDemux dmx)
{
    Nat32 index;

    /* Shall check and start program filter only for the current program */
	pmp_PmpSend(mMonitorProgramPmp, ((MONITOR_PROGRAM << 16) | dmx),
            ((CurrentProgramNo[dmx] & 0xffff) << 16));

	
}

Bool CHsvMpegDataManager_Priv::populateProgramVideoInfo(HsvDemux dmx, Typepmt_Parser *pmt,
        int esLoop)
{
    HsvPMTBasicPidInfo basicPIDInfo;

    TraceNotice(m, "MYLOG: PID = %d s-type = %d PcrPid %d\n", pmt->esData[esLoop].es_pid,
            pmt->esData[esLoop].stream_type, pmt->PCR_Pid);
    memset(&basicPIDInfo, 0, sizeof(basicPIDInfo));

    basicPIDInfo.ProgramNumber = pmt->program_number;
    basicPIDInfo.VideoPid = pmt->esData[esLoop].es_pid;
    basicPIDInfo.PcrPid = pmt->PCR_Pid;
    basicPIDInfo.PmtVersion = pmt->version_no;
    basicPIDInfo.VideoStreamType = pmt->esData[esLoop].stream_type;
    /* ARR I do not like the look of this ... */
    basicPIDInfo.TeletextPid = teletextPID;

    srtdb_Insert(BASIC_PID_TABLE_ID(dmx), basicPIDInfo.ProgramNumber, -1, -1,
            -1, (Address) &basicPIDInfo);
    if (strapiN_iPresent()) {
        strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx),
                HSVSPID(BasicPidInfo, mpeg, pmt), basicPIDInfo.ProgramNumber,
                (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY));
    }
    return TRUE;
}

Bool CHsvMpegDataManager_Priv::populateStreamIDInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop)
{
    HsvPMTComponentTagInfo comptaginfo;
    Nat32 loop;

    memset(&comptaginfo, 0, sizeof(comptaginfo));

    for (loop = 0;
            loop < DescLoops(pmt->esData[esLoop].Stream_identifier_Descriptor);
            loop++) {
        if (pmt->esData[esLoop].Stream_identifier_Descriptor[loop].DescriptorValid) {
            comptaginfo.ProgramNumber = pmt->program_number;
            comptaginfo.ComponentTag =
                    pmt->esData[esLoop].Stream_identifier_Descriptor[loop].component_tag;
            comptaginfo.Pid = pmt->esData[esLoop].es_pid;
            comptaginfo.PmtVersion = pmt->version_no;
            NotifyComponent(dmx, HSVSPID(ComponentTagInfo, dvb, pmt),
                    (void *) (&comptaginfo));
        }
    }

    return TRUE;
}

Bool CHsvMpegDataManager_Priv::populateTXTInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop)
{
    struct _TsVBI_teletext_Descriptor *pVBITxt = NULL;
    struct _TsTeletext_Descriptor *pTxt = NULL;
    HsvPMTSubtitlingInfo subtInfo;
    HsvPMTTeletextInfo txtInfo;
    int loop, index;

    memset(&subtInfo, 0, sizeof(subtInfo));
    memset(&txtInfo, 0, sizeof(txtInfo));

    txtInfo.ProgramNumber = subtInfo.ProgramNumber = pmt->program_number;
    txtInfo.PmtVersion = subtInfo.PmtVersion = pmt->version_no;
    txtInfo.Pid = subtInfo.Pid = pmt->esData[esLoop].es_pid;

    for (loop = 0;
            loop < DescLoops(pmt->esData[esLoop].VBI_teletext_Descriptor);
            loop++) {
        pVBITxt = &(pmt->esData[esLoop].VBI_teletext_Descriptor[loop]);
        if (pVBITxt->DescriptorValid) {
            teletextPID = pmt->esData[esLoop].es_pid;
            for (index = 0; index < pVBITxt->loopCount; index++) {
                txtInfo.LangCode = GetLanguageId(
                        pVBITxt->VBITeletextData[index].lang_code);
                txtInfo.Language = pVBITxt->VBITeletextData[index].lang_code
                        << 8;
                txtInfo.Type = HSV_SUBTITLE_TYPE;
                txtInfo.Type |= (pVBITxt->VBITeletextData[index].type << 8);
                txtInfo.Type |= (esLoop & 0xFF);

                txtInfo.TeletextMagazieNo =
                        pVBITxt->VBITeletextData[index].magazine_no;
                txtInfo.TeletextPageNo =
                        pVBITxt->VBITeletextData[index].page_no;

                if (HSV_IS_TXT_SUBTITLE(txtInfo.Type)) {
                    subtInfo.LangCode = txtInfo.LangCode;
                    subtInfo.Language = txtInfo.Language;
                    subtInfo.Type = txtInfo.Type;
                    subtInfo.TeletextMagazieNo = txtInfo.TeletextMagazieNo;
                    subtInfo.TeletextPageNo = txtInfo.TeletextPageNo;

                    /* Invalidate the subtitle related fields*/
                    subtInfo.CompositionPageId = (Nat16) (HSV_INVALID_PAGE_ID);
                    subtInfo.AncilliaryPageId = (Nat16) (HSV_INVALID_PAGE_ID);
                    NotifyComponent(dmx, HSVSPID(SubtitlingInfo, dvb, pmt),
                            (void *) (&subtInfo));
                }
                else {
                    NotifyComponent(dmx, HSVSPID(TeletextInfo, dvb, pmt),
                            (void *) (&txtInfo));
                }
            }
        }
    }
    pVBITxt = NULL;

    for (loop = 0;
            loop
                    < (DescLoops(pmt->esData[esLoop].Teletext_Descriptor)
                            && (teletextPID == INVALID_PID)); loop++) {
        pTxt = &(pmt->esData[esLoop].Teletext_Descriptor[loop]);
        if (pTxt->DescriptorValid) {
            teletextPID = pmt->esData[esLoop].es_pid;
            for (index = 0; index < pTxt->loopCount; index++) {
                txtInfo.LangCode = GetLanguageId(
                        pTxt->teletextLoop[index].lang_code);
                txtInfo.Language = pTxt->teletextLoop[index].lang_code << 8;
                txtInfo.Type = HSV_SUBTITLE_TYPE;
                txtInfo.Type |= (pTxt->teletextLoop[index].type << 8);
                txtInfo.Type |= (esLoop & 0xFF);

                txtInfo.TeletextMagazieNo =
                        pTxt->teletextLoop[index].magazine_no;
                txtInfo.TeletextPageNo = pTxt->teletextLoop[index].page_no;

                if (HSV_IS_TXT_SUBTITLE(txtInfo.Type)) {
                    subtInfo.LangCode = txtInfo.LangCode;
                    subtInfo.Language = txtInfo.Language;
                    subtInfo.Type = txtInfo.Type;
                    subtInfo.TeletextMagazieNo = txtInfo.TeletextMagazieNo;
                    subtInfo.TeletextPageNo = txtInfo.TeletextPageNo;

                    /* Invalidate the subtitle related fields*/
                    subtInfo.CompositionPageId = (Nat16) (HSV_INVALID_PAGE_ID);
                    subtInfo.AncilliaryPageId = (Nat16) (HSV_INVALID_PAGE_ID);
                    NotifyComponent(dmx, HSVSPID(SubtitlingInfo, dvb, pmt),
                            (void *) (&subtInfo));
                }
                else {
                    NotifyComponent(dmx, HSVSPID(TeletextInfo, dvb, pmt),
                            (void *) (&txtInfo));
                }
            }
        }
    }
    return TRUE;
}

Bool CHsvMpegDataManager_Priv::populateSUBTInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop)
{
    int loop, index;
    struct _TsSubtitling_Descriptor *pSubtDesc = NULL;
    HsvPMTSubtitlingInfo subtInfo;

    memset(&subtInfo, 0, sizeof(subtInfo));

    for (loop = 0; loop < DescLoops(pmt->esData[esLoop].Subtitling_Descriptor);
            loop++) {
        pSubtDesc = &(pmt->esData[esLoop].Subtitling_Descriptor[loop]);
        if (pSubtDesc->DescriptorValid) {
            for (index = 0; index < pSubtDesc->loopCount; index++) {
                subtInfo.LangCode = GetLanguageId(
                        pSubtDesc->subtitleData[index].lang_code);
                subtInfo.Language = pSubtDesc->subtitleData[index].lang_code
                        << 8;
                subtInfo.Type = HSV_SUBTITLE_TYPE;
                subtInfo.Type |= ((pSubtDesc->subtitleData[index].type << 16)
                        & 0xFF0000);
                subtInfo.Type |= (esLoop & 0xFF);
                subtInfo.Pid = pmt->esData[esLoop].es_pid;
                subtInfo.ProgramNumber = pmt->program_number;
                subtInfo.PmtVersion = pmt->version_no;
                subtInfo.CompositionPageId =
                        pSubtDesc->subtitleData[index].comp_page_id;
                subtInfo.AncilliaryPageId =
                        pSubtDesc->subtitleData[index].ancillary_page_id;
                subtInfo.TeletextMagazieNo = (Nat8) (HSV_INVALID_PAGE_NO);
                subtInfo.TeletextPageNo = (Nat8) (HSV_INVALID_PAGE_NO);
            }
            if (HSV_IS_HDSUBTITLE(subtInfo.Type)) {
                if (eurdiv_IsHDSubtitleSupported() /* && eurdiv_iVersion > 18*/) {
                    NotifyComponent(dmx, HSVSPID(SubtitlingInfo, dvb, pmt),
                            (void *) (&subtInfo));
                }
                else {
                    /* HD Subtitle not supported */
                }
            }
            else {
                NotifyComponent(dmx, HSVSPID(SubtitlingInfo, dvb, pmt),
                        (void *) (&subtInfo));
            }
        }
    }
    return TRUE;
}

Bool CHsvMpegDataManager_Priv::IsPremixedAudioType(Nat32 AudLang, Nat8 AudType)
{
    Bool lRetVal = FALSE;

    /* if audiotype ==0 and language is "adn" in ISO639 then its a premixed audio */

    if (!AudType) {
        if ((langids_LangAudioDescription) == GetLanguageId(AudLang)) {
            lRetVal = TRUE;
        }
    }

    return lRetVal;
}

Bool CHsvMpegDataManager_Priv::popISOAudioLang(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo)
{
    struct _TsISO_Lang_Descriptor *pISODesc;
    Nat32 loop, i;
    Bool pidAdded = FALSE;
    char byte1, byte2, byte3;
    Nat32 Language;

    for (loop = 0; loop < DescLoops(pmt->esData[esLoop].ISO_Lang_Descriptor);
            loop++) {
        if (pmt->esData[esLoop].ISO_Lang_Descriptor[loop].DescriptorValid) {
            pISODesc = &(pmt->esData[esLoop].ISO_Lang_Descriptor[loop]);
            for (i = 0; i < pISODesc->loopCount; i++) {
                Language = pISODesc->LanguageLoop[i].lang;
                byte1 = (char) ((((Nat32) (Language) & 0xFF0000)) >> 16);
                byte2 = (char) ((((Nat32) (Language) & 0xFF00)) >> 8);
                byte3 = (char) ((((Nat32) (Language) & 0xFF)));
                audioInfo->LangCode = GetLanguageId(
                        pISODesc->LanguageLoop[i].lang);
                audioInfo->Language = (pISODesc->LanguageLoop[i].lang << 8);
                audioInfo->NoOfISO639Lang = ((i << 8) | pISODesc->loopCount);
                audioInfo->AudioType &= 0xFFFF00FF;
                audioInfo->AudioType |= ((pISODesc->LanguageLoop[i].audioType)
                        << 8);
                if (IsPremixedAudioType(pISODesc->LanguageLoop[i].lang,
                        pISODesc->LanguageLoop[i].audioType)) {
                    audioInfo->AudioType |= HSV_PREMIXED_VI_TYPE;
                }
                NotifyComponent(dmx, HSVSPID(AudioInfo, mpeg, pmt), audioInfo);
                pidAdded = TRUE;
            }
        }
    }

    if (!pidAdded) {
        NotifyComponent(dmx, HSVSPID(AudioInfo, mpeg, pmt), audioInfo);
    }

    return TRUE;
}

Bool CHsvMpegDataManager_Priv::popAC3PlusAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo)
{
    Bool retVal = FALSE;
    struct _TsEAC3_Descriptor *pAC3Plus = NULL;
    int loop;

    for (loop = 0; loop < DescLoops(pmt->esData[esLoop].EAC3_Descriptor);
            loop++) {
        pAC3Plus = &(pmt->esData[esLoop].EAC3_Descriptor[loop]);
        if (pAC3Plus->DescriptorValid) {
            audioInfo->AudioType |= HSV_AC3PLUS_TYPE;
            if (pAC3Plus->component_type_flag) {
                audioInfo->AudioType |= ((pAC3Plus->component_type << 16)
                        & 0xFF0000);
            }
            else {
                audioInfo->AudioType |= (((0x42) << 16) & 0xFF0000);
            }

            if (pAC3Plus->substream1_flag || pAC3Plus->substream2_flag
                    || pAC3Plus->substream3_flag) {
                if ((((audioInfo->AudioType & 0x0000FF00)
                        == HSV_MPEG_AUDIO_VISUALLY_IMPAIRED)
                        || ((audioInfo->AudioType & 0x0000FF00) == 0))) {
                    audioInfo->AudioType |= HSV_EAC3_AUDIO_VISUALLY_IMPAIRED;
                    if (pAC3Plus->substream1 & 0x10) {
                        if (!HSV_IS_MULTICHANNEL_AC3_SUBSTREAM_TYPE(
                                pAC3Plus->substream1)) {
                            audioInfo->EAC3VIPresent = TRUE;
                        }
                        audioInfo->ADSubstreamValue = SUB_STREAM1;
                    }
                    else if (pAC3Plus->substream2 & 0x10) {
                        if (!HSV_IS_MULTICHANNEL_AC3_SUBSTREAM_TYPE(
                                pAC3Plus->substream2)) {
                            audioInfo->EAC3VIPresent = TRUE;
                        }
                        audioInfo->ADSubstreamValue = SUB_STREAM2;
                    }
                    else if (pAC3Plus->substream3 & 0x10) {
                        if (!HSV_IS_MULTICHANNEL_AC3_SUBSTREAM_TYPE(
                                pAC3Plus->substream3)) {
                            audioInfo->EAC3VIPresent = TRUE;
                        }
                        audioInfo->ADSubstreamValue = SUB_STREAM3;
                    }
                }
            }
            retVal = TRUE;
        }
    }
    return retVal;
}

Bool CHsvMpegDataManager_Priv::popAC3AudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo)
{
    Bool retVal = FALSE;
    int loop;
    struct _TsAC3_Descriptor *pAC3Desc = NULL;

    if (!eurdiv_IsAc3AudioSupported()) {
        return retVal;
    }

    for (loop = 0; loop < DescLoops(pmt->esData[esLoop].AC3_Descriptor);
            loop++) {
        pAC3Desc = &(pmt->esData[esLoop].AC3_Descriptor[loop]);
        if (pAC3Desc->DescriptorValid) {
            audioInfo->AudioType |= (HSV_AC3_TYPE);
            if (pAC3Desc->component_type_flag) {
                audioInfo->AudioType |= ((pAC3Desc->component_type << 16)
                        & 0xFF0000);
            }
            else {
                audioInfo->AudioType = (((0x42) << 16) & 0xFF0000);
            }
            retVal = TRUE;
        }
    }
    return retVal;
}

Bool CHsvMpegDataManager_Priv::popAACAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo)
{
    Bool retVal = FALSE;
    int loop;
    struct _TsAAC_Descriptor *pAACDesc = NULL;

    if (!sdmdiv_IsMpeg4STBoltOnSupported()) {
        return retVal;
    }

    for (loop = 0; loop < DescLoops(pmt->esData[esLoop].AAC_Descriptor);
            loop++) {
        pAACDesc = &(pmt->esData[esLoop].AAC_Descriptor[loop]);
        if (pAACDesc->DescriptorValid) {
            if (pmt->esData[esLoop].stream_type == MPEG4_HEAAC_STREAM_TYPE) {
                audioInfo->AudioType |= (HSV_HEAAC_TYPE);
            }
            else if (pmt->esData[esLoop].stream_type == MPEG4_AAC_STREAM_TYPE) {
                audioInfo->AudioType |= (HSV_AAC_TYPE);
            }
            else {
                audioInfo->AudioType |= (HSV_HEAAC_TYPE);
            }
            audioInfo->AACProfileAndLevel = pAACDesc->profile_and_level;

            if (pAACDesc->aac_type_flag) {
                audioInfo->AudioType |= ((pAACDesc->aac_type << 16) & 0xFF0000);
            }
            else {
                audioInfo->AudioType |= (((0x42) << 16) & 0xFF0000);
            }

            retVal = TRUE;
        }
    }
    return retVal;
}

Bool CHsvMpegDataManager_Priv::popSupplementaryAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo)
{
    Bool retVal = FALSE;
    int loop;
    struct _TsSupplementary_audio_Descriptor *pSupAud = NULL;

    for (loop = 0;
            loop < DescLoops(pmt->esData[esLoop].Supplementary_audio_Descriptor);
            loop++) {
        pSupAud = &(pmt->esData[esLoop].Supplementary_audio_Descriptor[loop]);
        if (pSupAud->DescriptorValid) {
            if (pSupAud->lang_code_present) {
                audioInfo->LangCode = GetLanguageId(pSupAud->lang_code);
                audioInfo->Language = (pSupAud->lang_code << 8);
                audioInfo->NoOfISO639Lang = 1;
            }
            if (pSupAud->mix_type) {
                if (0 == pSupAud->editorial_classification) {
                    /* Currently doing nothing. Taken care in E-AC3 */
                }
                else if (1 == pSupAud->editorial_classification) {
                    audioInfo->AudioType |= HSV_PREMIXED_VI_TYPE;
                }
                else if (2 == pSupAud->editorial_classification) {
                    audioInfo->AudioType |= HSV_MPEG_AUDIO_HEARING_IMPAIRED;
                }
                else if (3 == pSupAud->editorial_classification) {
                    audioInfo->AudioType |= HSV_SPOKEN_SUBTITLES_TYPE;
                }
                else {
                    /* Invalid block .. nothing */
                }
            }
            else { /* Mix type is 0 */
                if ((1 == pSupAud->editorial_classification)
                        || (3 == pSupAud->editorial_classification)) {
                    audioInfo->AudioType |= HSV_MPEG_AUDIO_VISUALLY_IMPAIRED;
                }
            }
            retVal = TRUE;
        }
    }
    return retVal;
}

Bool CHsvMpegDataManager_Priv::populateAudioInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop)
{
    HsvPMTAudioInfo audioInfo = { 0 };
    Bool            populated = FALSE;

    memset(&audioInfo, 0, sizeof(audioInfo));
    TraceNotice(m, "MYLOG: PID = %d s-type = %d\n", pmt->esData[esLoop].es_pid,
            pmt->esData[esLoop].stream_type);
    audioInfo.ProgramNumber = pmt->program_number;
    audioInfo.Pid = pmt->esData[esLoop].es_pid;
    audioInfo.PmtVersion = pmt->version_no;
    audioInfo.AudioType |= ((esLoop) & 0xFF);
    audioInfo.LangCode = langids_LangUndefined;
    audioInfo.Language = 0;
    audioInfo.NoOfISO639Lang = 0;

    popSupplementaryAudioInfo(pmt, esLoop, &audioInfo);

    /*
     * In case of AC3 / EAC3 the stream the stream type is 0x06 which are
     * private PES packets. Special check for them
     */
    if (pmt->esData[esLoop].stream_type == MPEG4_AC3PLUS_STREAM_TYPE) {
        if (FALSE == (populated = popAC3PlusAudioInfo(pmt, esLoop, &audioInfo))) {
            if (FALSE == (populated = popAC3AudioInfo(pmt, esLoop, &audioInfo))) {
                /* No AC3 / EAC3. May contain only Teletext or Subtitle
                 * information. Do not continue parsing
                 */
            }
        }
    }
    else {
        if (FALSE == (populated = popAACAudioInfo(pmt, esLoop, &audioInfo))) {
            /* AAC was also not present. Make MPEG2 type as default */
            audioInfo.AudioType |= HSV_MPEG_AUDIO_TYPE;
            populated = TRUE;
        }
    }

    if (populated) {
        popISOAudioLang(dmx, pmt, esLoop, &audioInfo);
    }

    return TRUE;
}

Bool CHsvMpegDataManager_Priv::pop_PopulatePMT(HsvDemux dmx, Address PMTTable, int code)
{
    Typepmt_Parser *pmt = (Typepmt_Parser *) PMTTable;
    Nat32 index;
    int loop;
    
    //for (index = 0; index < MAX_PMT_MONITORS; index++) {
    for (index = 0; index < ProgramData[dmx].programs; index++) {    
        if (ProgramData[dmx].programList[index].programNo == pmt->program_number) {            
            break;
        }
    }
#if 0
    if (index >= MAX_PMT_MONITORS) {
        return FALSE;
    }
#endif
    if (ProgramData[dmx].programList[index].versionNo == pmt->version_no) {
        return FALSE;
    }

    FreeDataBaseObjects(dmx, pmt->program_number);
    teletextPID = INVALID_PID;

    TraceNotice(m, "MYLOG: PMT Parsing for prg %d\n", pmt->program_number);

    ProgramData[dmx].programList[index].versionNo = pmt->version_no;
    ProgramData[dmx].programList[index].PcrPid = pmt->PCR_Pid;
    ProgramData[dmx].programList[index].collected = TRUE;
	/* Not makding subscriber ID to invalid. Otherwise the freeing of this filter is not properly happening */
    //ProgramData[dmx].programList[index].subscriptionID =
    //        HSV_INVALID_SCT_REQUEST;

    for (loop = 0; loop < pmt->TsLoopDataNum; loop++) {
        populateStreamIDInfo(dmx, pmt, loop);
        populateTXTInfo(dmx, pmt, loop);
        populateSUBTInfo(dmx, pmt, loop);

        switch (pmt->esData[loop].stream_type) {
        case ISO_IEC_11172_VIDEO_STREAM_TYPE:
        case H264_VIDEO_STREAM_TYPE:
        case ISO_IEC_11172_2_VIDEO_STREAM_TYPE:
            populateProgramVideoInfo(dmx, pmt, loop);
            break;

        case ISO_IEC_11172_AUDIO_STREAM_TYPE:
        case ISO_IEC_13818_3_AUDIO_STREAM_TYPE:
        case MPEG4_HEAAC_STREAM_TYPE:
        case MPEG4_AAC_STREAM_TYPE:
        case ATSC_A52_AC3_STREAM_TYPE:
        case MPEG4_AC3PLUS_STREAM_TYPE:
            populateAudioInfo(dmx, pmt, loop);
            break;

        default:
            break;
        }
    }

    if (strapiN_iPresent()) {
        if ((CurrentProgramNo[dmx] == pmt->program_number) && (sec_TableCompleted & code)) {
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx),
                    HSVSPID(CurrentProgram, mpeg, pmt));
        }
        else {
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx),
                    HSVSPID(PmtSection, mpeg, pmt));
        }
    }
    return TRUE;
}

Bool CHsvMpegDataManager_Priv::pop_PopulatePAT(HsvDemux dmx, Address PATTable, int code)
{
    Nat32 prg = 0;
    Nat32 *pNoPrgms = NULL;
    Typepat_Parser *pat = (Typepat_Parser *) PATTable;

    TraceNotice (m, "%s() : IN\n", __FUNCTION__);
    
    /* Check for the version number */
    if (ProgramData[dmx].PatVersionNo != pat->version_no) {
        ProgramData[dmx].PatVersionNo = pat->version_no;
        ProgramData[dmx].tsID = pat->ts_id;
        ProgramData[dmx].programs = 0;
    }

    pNoPrgms = &ProgramData[dmx].programs;

    while ((*pNoPrgms < MAX_POSSIBLE_PROGRAMS)&&
    (prg < pat->TsLoopDataNum)){
    /* Check for NIT PID information */
    if (0 != pat->programList[prg].program_number) {
        ProgramData[dmx].programList[*pNoPrgms].programNo =
        pat->programList[prg].program_number;
        ProgramData[dmx].programList[*pNoPrgms].Pid =
        pat->programList[prg].PID;
        (*pNoPrgms)++;
    }
    prg++;
}

    ProgramData[dmx].programs = *pNoPrgms;
    //ProgramData[dmx].subscriptionID = HSV_INVALID_SCT_REQUEST;

    /* Notification to indicate PAT complete */
    if (strapiN_iPresent()) {
        strapiN_OnCompleted(0, HSVSPID(Program, mpeg, pat));
    }
    StartProgramfilters(dmx);
    return TRUE;
}

void CHsvMpegDataManager_Priv::StartSubscriptions(HsvDemux dmx)
{
    /* Subscribe for the PAT on this demux */

    TraceNotice(m, " HSVMPEG: ZapEvent: StartSubscriptions (PAT) ");

    ProgramData[dmx].subscriptionID = sec_RequestSection(
            HSV_MAP_DMX_TO_DEST(dmx), PAT_PID_VALUE, PAT_TABLE_ID_VALUE,
            (Nat32) (&(ProgramData[dmx].subscriptionID)),
            FNADDR(pat_Parser_Parser));

	TraceNotice (m,"TCInstall: PAT SubscriberID 0x%x ", ProgramData[dmx].subscriptionID);
    /* Ensure that the demux did not fail when we subscribed for the PAT */
    ASSERT(ProgramData[dmx].subscriptionID != HSV_INVALID_SCT_REQUEST);

    if (ProgramData[dmx].subscriptionID == HSV_INVALID_SCT_REQUEST) {
        //LogError(log_SoftErr, MPEG_PAT_SUBSCRIPTION_FAILED);
    }
}

/*************************************************/
void CHsvMpegDataManager_Priv::StopSubscriptions(HsvDemux dmx)
{
    int i = 0;

    /* Cancel all subscriptions for programs */

    for (i = 0; i < MAX_POSSIBLE_PROGRAMS; i++) {
        if (HSV_INVALID_SCT_REQUEST
                != ProgramData[dmx].programList[i].subscriptionID) {
			TraceNotice (m, "TCInstall: Cancelling PMT Filter %d ", ProgramData[dmx].programList[i].subscriptionID);
            /* Retreive the subscription ID and cancel our subscription  */
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),
                    ProgramData[dmx].programList[i].subscriptionID);
            ProgramData[dmx].programList[i].subscriptionID =
                    HSV_INVALID_SCT_REQUEST;
        }
    }

	TraceNotice (m, "TCInstall: PAT Subsciber ID 0x%x Invalid 0x%x ", ProgramData[dmx].subscriptionID, HSV_INVALID_SCT_REQUEST);
    if (HSV_INVALID_SCT_REQUEST != ProgramData[dmx].subscriptionID) {
		TraceNotice (m, "TCInstall: Cancelling PAT Filter %d ", ProgramData[dmx].subscriptionID);
        sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), ProgramData[dmx].subscriptionID);
        ProgramData[dmx].subscriptionID = HSV_INVALID_SCT_REQUEST;
    }
}

/*************************************************/
#if 0

void CHsvMpegDataManager_Priv::LogError(int Priority, int ErrorId)
{
    if (log_iPresent()) {
        if (compids_iPresent()) {
            /* Add the offset of the MPEG data manager to the error ID */
            log_Error(Priority, ErrorId + compids_hsvmpeg);
        }
        else {
            /* Component ID for MPEG is unknown. We hope that the outer component takes care of adding a proper offset to us*/
            log_Error(Priority, ErrorId);
        }
    }
} /* End of function LogError() */
#endif

void CHsvMpegDataManager_Priv::SubscribeForProgram(HsvDemux dmx, int prg, int pid, int index)
{
    HsvSource source;
    HsvChannel curchan;
    int Service_Id;
    int i = 0;
    int CurrentPmtPid = 0;

    TraceNotice(m, "HSVMPEG:  Subscribe for program = %d, pid = %d, index = %d", prg, pid, index);

	if(dmx < HsvDmxLast)
	{
	    if (HSV_INVALID_SCT_REQUEST != ProgramData[dmx].programList[index].subscriptionID) {
	        sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), ProgramData[dmx].programList[index].subscriptionID);
	        ProgramData[dmx].programList[index].subscriptionID = HSV_INVALID_SCT_REQUEST;
	    }

	    ProgramData[dmx].programList[index].versionNo = (Nat8) (HSV_INVALID_VERSION);
        ProgramData[dmx].programList[index].Pid = pid;
        ProgramData[dmx].programList[index].programNo = prg;

        TraceNotice(m, "dmx %d, index %d, versionNo %d, Pid %d,programNo %d", dmx, index, 
                        ProgramData[dmx].programList[index].versionNo,
                        ProgramData[dmx].programList[index].Pid,
                        ProgramData[dmx].programList[index].programNo);
	 
	    if (INVALID_PROGRAM_MAP_PID != pid) {
	        /* Subscribe for a section only if the requested PID was a valid one */
	        ProgramData[dmx].programList[index].subscriptionID = sec_RequestSection2 (
	                HSV_MAP_DMX_TO_DEST(dmx), pid, TS_PROGRAM_MAP_SECTION_TABLE_ID,
	                prg, /* Program number is both cookie and table ID extension field*/
	                prg, FNADDR(pmt_Parser_Parser));

	        if (HSV_INVALID_SCT_REQUEST
	                == ProgramData[dmx].programList[index].subscriptionID) {
	            //dont log an assert. incase of failure no fresult is being returned. clients will have to timeout incase of failure
	            //LogError(log_SoftErr, MPEG_PMT_SUBSCRIPTION_FAILED);
	            TraceNotice (m, "Invalid SCT_REQUEST\n");
	            pmp_PmpSendAfter(mMpegPump, dmx, index, RETRY_REQUEST);               
	        }
	    }
	}
} /* End of function SubscribeForProgram() */

/******************************************************************/
void CHsvMpegDataManager_Priv::ClearPmtSectionData(HsvDemux dmx)
{
    int i;
	if(dmx < HsvDmxLast)
	{
	    for (i = 0; i < MAX_POSSIBLE_PROGRAMS; i++) {
	        ProgramData[dmx].programList[i].versionNo = HSV_INVALID_VERSION;
	        ProgramData[dmx].programList[i].programNo = INVALID_PROGRAM_NUMBER;
	        ProgramData[dmx].programList[i].collected = FALSE;
	        ProgramData[dmx].programList[i].PcrPid = INVALID_PID;
	        ProgramData[dmx].programList[i].Pid = INVALID_PID;
	        ProgramData[dmx].programList[i].subscriptionID =
	                HSV_INVALID_SCT_REQUEST;
	        ProgramData[dmx].programList[i].pmtSecData = NULL;
	    }
	}
}/* End of function ClearPmtSectionData() */

/*********************************************************************************/

#if 0



int CHsvMpegDataManager_Priv::GetDescriptorIDOnpmt( int descriptor_tag, int cookie )
{
    int i = 0;
    UNUSED(cookie);

    switch(descriptor_tag)
    {
#define PMTDESCRIPTOR(a, b)  case (a): \
        i++;
#include "HsvPMTDescriptors.dd"
#undef PMTDESCRIPTOR
        i = (PMT_MAX_DESCRIPTOR - i);
        break;
        default:
        i = -1;
        break;
    }
    return (i);
}
#endif
/*************************IHsvStream Implementation *******************************/
/************************ PATSTRAPI************************************************/


int CHsvMpegDataManager_Priv::patstrapi_GetSize(HsvDestination inst, int prop)
{
    int retval = 0;
    HsvDemux dmx;

    dmx = (int)HSV_MAP_DEST_TO_DMX(inst);

	if(dmx < HsvDmxLast){
	    if (((unsigned char) HSV_INVALID_VERSION) != ProgramData[dmx].PatVersionNo) {
	        switch (prop) {
	        case HSVSPID(Program, mpeg, pat):
	            retval = ProgramData[dmx].programs;
	            break;
	        default:
	            ASSERT(!"Invalid Property called with this function");
	            break;
	        }
	    }
	    else {
	        /* Clients blindly query even when SDM is not started ! */
	        //LogError(log_SoftErr, MPEG_INVALID_QUERY);
	    }
	}

    return retval;
}
/******************************************************************************/

Bool CHsvMpegDataManager_Priv::patstrapi_GetIndex(HsvDestination inst, int prop, int key1, int key2,
        int key3, int *index)
{
    Bool retval = FALSE;
    HsvDemux dmx = HSV_MAP_DEST_TO_DMX(inst);

    UNUSED(key2);
    UNUSED(key3);
	if(dmx < HsvDmxLast){
	    if (((unsigned char) HSV_INVALID_VERSION) != ProgramData[dmx].PatVersionNo) {
	        switch (prop) {
	        case HSVSPID(Program, mpeg, pat): {
	            int i = -1;
	            for (i = 0; i < ProgramData[dmx].programs; i++) {
	                if (key1 == (int) ProgramData[dmx].programList[i].programNo) {
	                    retval = TRUE;
	                    *index = i;
	                    break;
	                }
	            }
	            break;
	        }
	        default:
	            ASSERT(!"Invalid Property called with this function");
	            break;
	        }
	    }
	    else {
	        /* Clients blindly query even when SDM is not started ! */
	        //LogError(log_SoftErr, MPEG_INVALID_QUERY);
	    }
	}

    return retval;
}
/******************************************************************************/

Bool CHsvMpegDataManager_Priv::patstrapi_GetByKey(HsvDestination inst, int prop, int key1, int key2,
        int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux dmx = HSV_MAP_DEST_TO_DMX(inst);

    UNUSED(key2);
    UNUSED(key3);
	if(dmx < HsvDmxLast){
	    if (((unsigned char) HSV_INVALID_VERSION) != ProgramData[dmx].PatVersionNo) {
	        switch (prop) {
	        case HSVSPID(Program, mpeg, pat): {
	            int i = -1;
	            for (i = 0; i < ProgramData[dmx].programs; i++) {
	                if (key1 == (int) ProgramData[dmx].programList[i].programNo) {
	                    HsvPATProgramPIDInfo *pval = (HsvPATProgramPIDInfo *)val;
	                    pval->ProgramNumber =
	                            ProgramData[dmx].programList[i].programNo;
	                    pval->Pid = ProgramData[dmx].programList[i].Pid;
	                    retval = TRUE;
	                    break;
	                }
	            }
	            break;
	        }
	        case HSVSPID(CurrentTsId, mpeg, pat): {
	            int *pval = (int *)val;
	            *pval = ProgramData[dmx].tsID; /* This 16 bit field is present in HSV_TS_PACKETFIELDS macro and represents the transport stream ID of the PAT section */
	            retval = TRUE;
	            break;
	        }
	        default:
	            ASSERT(!"Invalid Property called with this function");
	            break;
	        }
	    }
	    else {
	        /* Clients blindly query even when SDM is not started ! */
	        //LogError(log_SoftErr, MPEG_INVALID_QUERY);
	    }
	}
    return retval;
}
/******************************************************************************/

Bool CHsvMpegDataManager_Priv::patstrapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;
    HsvDemux dmx = HSV_MAP_DEST_TO_DMX(inst);

	if(dmx < HsvDmxLast){
	    if (((unsigned char) HSV_INVALID_VERSION) != ProgramData[dmx].PatVersionNo) {
	        switch (prop) {
	        case HSVSPID(Program, mpeg, pat): {
	            if (index < ProgramData[dmx].programs) {
	                HsvPATProgramPIDInfo *pval = (HsvPATProgramPIDInfo *)val;
	                pval->ProgramNumber =
	                        ProgramData[dmx].programList[index].programNo;
	                pval->Pid = ProgramData[dmx].programList[index].Pid;
	                retval = TRUE;
	            }
	            break;
	        }
	        default:
	            ASSERT(!"Invalid Property called with this function");
	            break;
	        }
	    }
	    else {
	        /* Clients blindly query even when SDM is not started ! */
	        //LogError(log_SoftErr, MPEG_INVALID_QUERY);
	    }
	}

    return retval;
}
/******************************************************************************/

/*************************IHsvStream Implementation *******************************/
/************************ PMTSTRAPI************************************************/

int CHsvMpegDataManager_Priv::pmtstrapi_GetSize(HsvDestination inst, int prop)
{
    int retval = 0;
    HsvDemux dmx;

    dmx = HSV_MAP_DEST_TO_DMX(inst);

    switch (prop) {
    case HSVSPID(BasicPidInfo, mpeg, pmt): {
        /* Return the number of records in the Basic PID info database */
        retval = srtdb_GetNoOfRecords(BASIC_PID_TABLE_ID(dmx));
        /* This corresponds to the number of programs for which we currently have information */
        break;
    }
    case HSVSPID(CurrentBasicPidInfo, mpeg, pmt): {
        int fromindex = 0;
        int toindex = 0;
        if (srtdb_SearchOnPrimaryKey(BASIC_PID_TABLE_ID(dmx),
                CurrentProgramNo[dmx], &fromindex, &toindex)) {
            retval = (toindex - fromindex + 1);
        }
        else {
            retval = 0;
        }
        break;
    }
    case HSVSPID(AudioInfo, mpeg, pmt): {
        /* The GetSize() on this property will return the total number of audio info structures
         over all seen PMTs in this TS. To get information only for those programs
         that clients are interested in, do a GetSize(), followed by GetByIndex() and
         check for the program number of interest */
        retval = srtdb_GetNoOfRecords(AUDIOINFO_TABLE_ID(dmx));
        break;
    }
    case HSVSPID(CurrentAudioInfo, mpeg, pmt): {
        /* The GetSize() on this property will return the total number of audio info structures
         over all seen PMTs in this TS. To get information only for those programs
         that clients are interested in, do a GetSize(), followed by GetByIndex() and
         check for the program number of interest */
        int from = 0;
        int to = 0;
        if (srtdb_SearchOnPrimaryKey(AUDIOINFO_TABLE_ID(dmx),
                CurrentProgramNo[dmx], &from, &to)) {
            retval = (to - from + 1);
        }
        else {
            /* There was no current audio info. */
        }
        break;
    }

    case HSVSPID(SubtitlingInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of Subtitling info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        retval = srtdb_GetNoOfRecords(SUBTITLE_TABLE_ID(dmx));
        break;
    }

    case HSVSPID(CurrentSubtitlingInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of Subtitling info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        int from = 0;
        int to = 0;
        if (srtdb_SearchOnPrimaryKey(SUBTITLE_TABLE_ID(dmx),
                CurrentProgramNo[dmx], &from, &to)) {
            retval = (to - from + 1);
        }
        else {
            /* There was no current subtitling info */
        }
        break;
    }

    case HSVSPID(TeletextInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of teletext info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        retval = srtdb_GetNoOfRecords(TELETEXT_TABLE_ID(dmx));
        break;
    }
    case HSVSPID(CurrentTeletextInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of teletext info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        int from = 0;
        int to = 0;

        if (srtdb_SearchOnPrimaryKey(TELETEXT_TABLE_ID(dmx),
                CurrentProgramNo[dmx], &from, &to)) {
            retval = (to - from + 1);
        }
        break;
    }
    case HSVSPID(PmtSection, mpeg, pmt): {
        retval = 0;

#if 0
        for( i = 0; i < MAX_PMT_MONITORS; i++ )
        {
            if( PmtSectionData[dmx][i].SectionPointer )
            {
                /* We have a non NULL PMT section pointer. Tell this to the outside world*/
                /* Increment the count of the number of PMT's seen */
                retval++;
            }
            else
            {
                /* QAC */
            }
        }
#endif
        break;
    }

    case HSVSPID(ComponentTagInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of component tag info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        retval = srtdb_GetNoOfRecords(COMPONENT_TAG_TABLE_ID(dmx));
        break;
    }
    case HSVSPID(DatabroadcastInfo, dvb, pmt): {
        /* Returning the total number of records will give the client the number of component tag info structures we have for all programs combined*/
        /* If clients are interested in information for specific programs, use GetSize(), followed by GetByIndex and compare against the program number of interest */
        retval = srtdb_GetNoOfRecords(DATABROADCAST_TAG_TABLE_ID(dmx));
        break;
    }
    default:
        ASSERT(!"Invalid Property called with this function");
        break;
    }

    return retval;
} /* End of function pmtstrapi_GetSize() */
/***************************************************************/

Bool CHsvMpegDataManager_Priv::pmtstrapi_GetIndex(HsvDestination inst, int prop, int key1, int key2,
        int key3, int *index)
{

    Bool retval = FALSE;
    inst = (HsvDestination)(HSV_MAP_DEST_TO_DMX(inst));
    switch (prop) {
    case HSVSPID(BasicPidInfo, mpeg, pmt): {

        /* We use only the first key here, which corresponds to the program number  */
        if (index) {
            retval =
                    srtdb_SearchOnKey(BASIC_PID_TABLE_ID(inst), key1,
                            ((Nat32) (HSV_INVALID_KEY)), ((Nat32)(HSV_INVALID_KEY)),(Nat32)(HSV_INVALID_KEY), index );
                        }
                        else
                        {
                            /* NULL pointer passed to query for information*/
                        }
                        break;
                    }
                    case HSVSPID(CurrentBasicPidInfo, mpeg, pmt ):
                    {
                        /* The first key to be used here will be the current program number that we have cached */
                        if( index )
                        {
                            int fromindex = 0;
                            int toindex = 0;
                            int eleindex = 0;

                            if( srtdb_SearchOnPrimaryKey(BASIC_PID_TABLE_ID(inst), CurrentProgramNo[inst], &fromindex, &toindex ) )
                    {
                        /* Program number exists. Retreive the from and to values and return the offset at which the entry is located */
                        if( srtdb_SearchOnKey( BASIC_PID_TABLE_ID(inst), CurrentProgramNo[inst], key1, key2,0, &eleindex ) )
                        {
                            *index = (eleindex - fromindex);
                            retval = TRUE;
                        }
                        else
                        {
                            /* Element does not exist */
                            retval = FALSE;
                        }
                    }
                    else
                    {
                        /* There is no current program !! */

                    }
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        case HSVSPID(AudioInfo, mpeg,pmt):
            {
                /* We use only the first key here, which corresponds to the program number  */
                if( index )
                {
                    retval = srtdb_SearchOnKey( AUDIOINFO_TABLE_ID(inst), key1, key2, key3, 0,index );
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }
        case HSVSPID(CurrentAudioInfo, mpeg,pmt):
            {
                /* The first key to be used here will be the current program number that we have cached */
                if( index )
                {
                    int fromindex   =  0;
                    int toindex     =  0;
                    int eleindex    =  0;

                    if( srtdb_SearchOnPrimaryKey( AUDIOINFO_TABLE_ID(inst), CurrentProgramNo[inst], &fromindex, &toindex ) )
                    {
                        /* Program number exists. Retreive the from and to values and return the offset at which the entry is located */
                        if( srtdb_SearchOnKey( AUDIOINFO_TABLE_ID(inst), CurrentProgramNo[inst], key1, key2,0, &eleindex ) )
                        {
                            *index = (eleindex - fromindex);
                            retval = TRUE;
                        }
                        else
                        {
                            /* Element does not exist */
                            retval = FALSE;
                        }
                    }
                    else
                    {
                        /* There is no current program !! */

                    }
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        case HSVSPID(SubtitlingInfo, dvb,pmt ):
            {
                /* We use only the first key here, which corresponds to the program number  */
                if( index )
                {
                    retval = srtdb_SearchOnKey( SUBTITLE_TABLE_ID(inst), key1, key2, key3,0, index );
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }
        case HSVSPID(CurrentSubtitlingInfo, dvb,pmt ):
            {
                /* The first key to be used here will be the current program number that we have cached */
                if( index )
                {
                    int fromindex   =  0;
                    int toindex     =  0;
                    int eleindex    =  0;

                    if( srtdb_SearchOnPrimaryKey( SUBTITLE_TABLE_ID(inst), CurrentProgramNo[inst], &fromindex, &toindex ) )
                    {
                        /* Program number exists. Retreive the from and to values and return the offset at which the entry is located */
                        if( srtdb_SearchOnKey( SUBTITLE_TABLE_ID(inst), CurrentProgramNo[inst], key1, key2, 0,&eleindex ) )
                        {
                            *index = (eleindex - fromindex);
                            retval = TRUE;
                        }
                        else
                        {
                            /* Element does not exist */
                            retval = FALSE;
                        }
                    }
                    else
                    {
                        /* There is no current program !! */

                    }
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        case HSVSPID(TeletextInfo, dvb, pmt ) :
            {
                /* We use only the first key here, which corresponds to the program number  */
                if( index )
                {
                    retval = srtdb_SearchOnKey( TELETEXT_TABLE_ID(inst), key1, key2, key3,0, index );
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        case HSVSPID(CurrentTeletextInfo, dvb, pmt ) :
            {
                /* The first key to be used here will be the current program number that we have cached */
                if( index )
                {
                    int fromindex   =  0;
                    int toindex     =  0;
                    int eleindex    =  0;

                    if( srtdb_SearchOnPrimaryKey( TELETEXT_TABLE_ID(inst), CurrentProgramNo[inst], &fromindex, &toindex ) )
                    {
                        /* Program number exists. Retreive the from and to values and return the offset at which the entry is located */
                        if( srtdb_SearchOnKey( TELETEXT_TABLE_ID(inst), CurrentProgramNo[inst], key1, key2,0, &eleindex ) )
                        {
                            *index = (eleindex - fromindex);
                            retval = TRUE;
                        }
                        else
                        {
                            /* Element does not exist */
                            retval = FALSE;
                        }
                    }
                    else
                    {
                        /* There is no current program !! */

                    }
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }
        case HSVSPID(PmtSection, mpeg, pmt ) :
            {
                int     i =0;

                for( i = 0 ; i < MAX_POSSIBLE_PROGRAMS; i++ )
                {
                    if( ProgramData[inst].programList[i].programNo == key1 )
                    {
                        if( index != NULL )
                        {
                            *index = i;
                            retval = TRUE;
                            break;
                        }
                        else
                        {
                            /* QAC */
                        }
                    }
                    else
                    {
                        /* QAC */
                    }
                }
                break;
            }
        case HSVSPID(ComponentTagInfo, dvb, pmt):
            {
                /* We use only the first two keys here, which corresponds to the program number and component tag */
                if( index )
                {
                    retval = srtdb_SearchOnKey( COMPONENT_TAG_TABLE_ID(inst), key1, key2, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), index );
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        case HSVSPID(DatabroadcastInfo, dvb, pmt):
            {
                /* We use only the first two keys here, which corresponds to the program number and component tag */
                if( index )
                {
                    retval = srtdb_SearchOnKey( DATABROADCAST_TAG_TABLE_ID(inst), key1, key2, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), index );
                }
                else
                {
                    /* NULL pointer passed to query for information*/
                }
                break;
            }

        default:
            {
                ASSERT(! "Invalid Property called with this function");
                break;
            }
    }
    return retval;
} /* End of function pmtstrapi_GetIndex() */
/***************************************************************/

Bool CHsvMpegDataManager_Priv::pmtstrapi_GetByKey(HsvDestination inst, int prop, int key1, int key2,
        int key3, void *val)
{
    Bool retval = FALSE;

    inst = (HsvDestination)(HSV_MAP_DEST_TO_DMX(inst));

    if (NULL != val) {
        switch (prop) {
        case HSVSPID(TeletextInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(TELETEXT_TABLE_ID(inst), key1, key2, key3,
                    0, (Address) val);
            break;
        }
        case HSVSPID(CurrentTeletextInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(TELETEXT_TABLE_ID(inst),
                    CurrentProgramNo[inst], key1, key2, 0, (Address) val);
            break;
        }
        case HSVSPID(SubtitlingInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(SUBTITLE_TABLE_ID(inst), key1, key2, key3,
                    0, (Address) val);
            break;
        }
        case HSVSPID(CurrentSubtitlingInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(SUBTITLE_TABLE_ID(inst),
                    CurrentProgramNo[inst], key1, key2, 0, (Address) val);
            break;
        }
        case HSVSPID(BasicPidInfo, mpeg, pmt): {
            retval = srtdb_QueryOnKey(BASIC_PID_TABLE_ID(inst), key1,
                    (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY),
                    (Nat32) (HSV_INVALID_KEY), (Address) val);
            break;
        }
        case HSVSPID(CurrentBasicPidInfo, mpeg, pmt): {
            retval = srtdb_QueryOnKey(BASIC_PID_TABLE_ID(inst),
                    CurrentProgramNo[inst], (Nat32) (HSV_INVALID_KEY),
                    (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY),
                    (Address) val);
            break;
        }
        case HSVSPID(AudioInfo, mpeg, pmt): {
            retval = srtdb_QueryOnKey(AUDIOINFO_TABLE_ID(inst), key1, key2,
                    key3, 0, (Address) val);
            break;
        }
        case HSVSPID(CurrentAudioInfo, mpeg, pmt): {
            retval = srtdb_QueryOnKey(AUDIOINFO_TABLE_ID(inst),
                    CurrentProgramNo[inst], key1, key2, 0, (Address) val);
            break;
        }

        case HSVSPID(CurrentProgram, mpeg, pmt): {
            (*(int *) (val)) = CurrentProgramNo[inst];
            retval = TRUE;
            break;
        }

        case HSVSPID(PmtSection, mpeg, pmt): {
            HsvPMTSection * ptrsec = (HsvPMTSection *) (val);
            int i = 0;

            for (i = 0; i < MAX_PMT_MONITORS; i++) {
                if (ProgramData[inst].programList[i].programNo == key1) {
                    ptrsec->PmtSectionPointer =
                            ProgramData[inst].programList[i].pmtSecData;
                    ptrsec->ProgramNumber =
                            ProgramData[inst].programList[i].programNo;
                    retval = TRUE;
                    break;
                }
            }
            break;
        }

        case HSVSPID(ComponentTagInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(COMPONENT_TAG_TABLE_ID(inst), key1, key2,
                    (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY),
                    (Address) val);
            break;
        }

        case HSVSPID(DatabroadcastInfo, dvb, pmt): {
            retval = srtdb_QueryOnKey(DATABROADCAST_TAG_TABLE_ID(inst), key1,
                    key2, (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY),
                    (Address) val);
            break;
        }

        default: {
            /* A property we dont recognize */
            break;
        }
        }
    }
    else {
        ASSERT(!" NULL pointer passed for PMT property query");
    }

    return retval;
} /* End of function pmtstrapi_GetByKey() */
/***************************************************************/

Bool CHsvMpegDataManager_Priv::pmtstrapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    inst = (HsvDestination)(HSV_MAP_DEST_TO_DMX(inst));

    if (NULL != val) {
        switch (prop) {
        case HSVSPID(TeletextInfo, dvb, pmt): {
            retval = srtdb_QueryOnIndex(TELETEXT_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }

        case HSVSPID(CurrentTeletextInfo, dvb, pmt): {
            int fromindex = 0;
            int toindex = 0;

            if (srtdb_SearchOnPrimaryKey(TELETEXT_TABLE_ID(inst),
                    CurrentProgramNo[inst], &fromindex, &toindex)) {
                if ((index >= 0) && (index) < ((toindex - fromindex) + 1)) {
                    retval = srtdb_QueryOnIndex(TELETEXT_TABLE_ID(inst),
                            (fromindex + index), val);
                }
            }
            else {
                /* No current program data*/
            }

            break;
        }

        case HSVSPID(SubtitlingInfo, dvb, pmt): {
            retval = srtdb_QueryOnIndex(SUBTITLE_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }

        case HSVSPID(CurrentSubtitlingInfo, dvb, pmt): {
            int fromindex = 0;
            int toindex = 0;

            if (srtdb_SearchOnPrimaryKey(SUBTITLE_TABLE_ID(inst),
                    CurrentProgramNo[inst], &fromindex, &toindex)) {
                if ((index >= 0) && (index) < ((toindex - fromindex) + 1)) {
                    retval = srtdb_QueryOnIndex(SUBTITLE_TABLE_ID(inst),
                            (fromindex + index), val);
                }
            }
            else {
                /* No current program data*/
            }

            break;
        }

        case HSVSPID(BasicPidInfo, mpeg, pmt): {
            retval = srtdb_QueryOnIndex(BASIC_PID_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }
        case HSVSPID(CurrentBasicPidInfo, mpeg, pmt): {
            int fromindex = 0;
            int toindex = 0;

            if (srtdb_SearchOnPrimaryKey(BASIC_PID_TABLE_ID(inst),
                    CurrentProgramNo[inst], &fromindex, &toindex)) {
                if ((index >= 0) && (index) < ((toindex - fromindex) + 1)) {
                    retval = srtdb_QueryOnIndex(BASIC_PID_TABLE_ID(inst),
                            (fromindex + index), val);
                }
            }
            else {
                /* No current program data*/
            }

            break;
        }
        case HSVSPID(AudioInfo, mpeg, pmt): {
            retval = srtdb_QueryOnIndex(AUDIOINFO_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }

        case HSVSPID(CurrentAudioInfo, mpeg, pmt): {
            int fromindex = 0;
            int toindex = 0;

            if (srtdb_SearchOnPrimaryKey(AUDIOINFO_TABLE_ID(inst),
                    CurrentProgramNo[inst], &fromindex, &toindex)) {
                if ((index >= 0) && (index) < ((toindex - fromindex) + 1)) {
                    retval = srtdb_QueryOnIndex(AUDIOINFO_TABLE_ID(inst),
                            (fromindex + index), val);
                }
            }
            else {
                /* No current program data*/
            }

            break;
        }

        case HSVSPID(CurrentProgram, mpeg, pmt): {
            if (index == 0) {
                (*(int *) (val)) = CurrentProgramNo[inst];
                retval = TRUE;
            }
            else {

            }
            break;
        }

        case HSVSPID(PmtSection, mpeg, pmt): {
            HsvPMTSection * ptrsec = (HsvPMTSection *) (val);
            if ((index >= 0) && (index < MAX_POSSIBLE_PROGRAMS)) {
                if ((Nat8) HSV_INVALID_VERSION
                        != ProgramData[inst].programList[index].versionNo) {
                    ptrsec->PmtSectionPointer =
                            ProgramData[inst].programList[index].pmtSecData;
                    ptrsec->ProgramNumber =
                            ProgramData[inst].programList[index].programNo;
                    retval = TRUE;
                }
                else {
                    /* PMT not acquired yet */
                }
            }
            else {
                /* Bad index */
            }
            break;
        }

        case HSVSPID(ComponentTagInfo, dvb, pmt): {
            retval = srtdb_QueryOnIndex(COMPONENT_TAG_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }

        case HSVSPID(DatabroadcastInfo, dvb, pmt): {
            retval = srtdb_QueryOnIndex(DATABROADCAST_TAG_TABLE_ID(inst), index,
                    (Address) val);
            break;
        }

        default: {
            /* A property we dont recognize */
            break;
        }
        }
    }
    else {
        ASSERT(!" NULL pointer passed for PMT property query");
    }

    return retval;
} /* End of function pmtstrapi_GetByIndex() */
/***************************************************************/

/***********************************************************/
void CHsvMpegDataManager_Priv::ClearPropertyTables(HsvDemux dmx)
{
    switch (dmx) {
    case HsvDmxMain:
        srtdb_Init(srtdbids_BasicPidInfoMain);
        srtdb_Init(srtdbids_AudioInfoMain);
        srtdb_Init(srtdbids_SubtitlingInfoMain);
        srtdb_Init(srtdbids_TeletextInfoMain);
        srtdb_Init(srtdbids_ComponentTagInfoMain);
        srtdb_Init(srtdbids_DatabroadcastInfoMain);
        break;
    case HsvDmxAux:
        srtdb_Init(srtdbids_BasicPidInfoAux);
        srtdb_Init(srtdbids_AudioInfoAux);
        srtdb_Init(srtdbids_SubtitlingInfoAux);
        srtdb_Init(srtdbids_TeletextInfoAux);
        srtdb_Init(srtdbids_ComponentTagInfoAux);
        srtdb_Init(srtdbids_DatabroadcastInfoAux);
        break;
    default:
        /* Do nothing */
        break;
    }
    return;
} /* End of function ClearPropertyTables() */
/***********************************************************/

void CHsvMpegDataManager_Priv::NotifyComponent(HsvDemux dmx, Nat8 property, void * addr)
{
    HsvDestination dest = HSV_MAP_DMX_TO_DEST(dmx);

    switch (property) {
    case HSVSPID(TeletextInfo, dvb, pmt): {
        HsvPMTTeletextInfo txtinfo = (*(HsvPMTTeletextInfo *) (addr));
        HsvPMTTeletextInfo txtdummy;

        if (srtdb_QueryOnKey(TELETEXT_TABLE_ID(dmx), txtinfo.ProgramNumber,
                txtinfo.LangCode, txtinfo.Type, 0, (Address) (&txtdummy))) {
            if (txtinfo.PmtVersion != txtdummy.PmtVersion) {
                /* A similar record exists in the database. Update it */
                if (srtdb_Update(TELETEXT_TABLE_ID(dmx), txtinfo.ProgramNumber,
                        txtinfo.LangCode, txtinfo.Type, 0,
                        (Address) (&txtinfo))) {
                    if (!CompareTxtInfo(&txtdummy, &txtinfo)) {
                        /* Notify only if structures were different */
                        /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                        if (strapiN_iPresent()) {
                            strapiN_OnChanged(dest,
                                    HSVSPID(TeletextInfo, dvb, pmt),
                                    txtinfo.ProgramNumber, txtinfo.LangCode,
                                    txtinfo.Type, HsvEvtNull);
                        }

                        if (CurrentProgramNo[dmx] == txtinfo.ProgramNumber) {
                            if (strapiN_iPresent()) {
                                strapiN_OnChanged(dest,
                                        HSVSPID(CurrentTeletextInfo, dvb, pmt),
                                        txtinfo.ProgramNumber, txtinfo.LangCode,
                                        txtinfo.Type, HsvEvtNull);
                            }
                        }

                    }
                    else {
                        /* Structures were not different. Dont notify */
                    }
                }
                else {
                    /* database update failed for some reason */
                }

            }
            else {
                /* We update records only if there was a change in PMT version */
            }
        }
        else {
            /* There was no such record in the database. Insert it */
            if (srtdb_Insert(TELETEXT_TABLE_ID(dmx), txtinfo.ProgramNumber,
                    txtinfo.LangCode, txtinfo.Type, 0, (Address) (&txtinfo))) {

                if (strapiN_iPresent()) {
                    strapiN_OnAdded(dest,
                            HSVSPID(CurrentTeletextInfo, dvb, pmt),
                            txtinfo.LangCode, txtinfo.Type,
                            (Nat32) (HSV_INVALID_KEY));
                }

                if (CurrentProgramNo[dmx] == txtinfo.ProgramNumber) {
                    if (strapiN_iPresent()) {
                        strapiN_OnAdded(dest,
                                HSVSPID(CurrentTeletextInfo, dvb, pmt),
                                txtinfo.LangCode, txtinfo.Type,
                                (Nat32) (HSV_INVALID_KEY));
                    }
                }

            }
            else {
                /* database insert failed. do not notify */
            }
        }

        break;
    }
    case HSVSPID(SubtitlingInfo, dvb, pmt): {
        HsvPMTSubtitlingInfo stlinfo = (*(HsvPMTSubtitlingInfo *) (addr));
        HsvPMTSubtitlingInfo sbtldummy;
        if (srtdb_QueryOnKey(SUBTITLE_TABLE_ID(dmx), stlinfo.ProgramNumber,
                stlinfo.LangCode, stlinfo.Type, 0, (Address) (&sbtldummy))) {
            if (sbtldummy.PmtVersion != stlinfo.PmtVersion) {
                /* A similar record exists in the database. Update it */
                if (srtdb_Update(SUBTITLE_TABLE_ID(dmx), stlinfo.ProgramNumber,
                        stlinfo.LangCode, stlinfo.Type, 0,
                        (void *) (&stlinfo))) {

                    if (!CompareSbtlInfo(&sbtldummy, &stlinfo)) {
                        /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                        if (strapiN_iPresent()) {
                            strapiN_OnChanged(dest,
                                    HSVSPID(SubtitlingInfo, dvb, pmt),
                                    stlinfo.ProgramNumber, stlinfo.LangCode,
                                    stlinfo.Type, HsvEvtNull);
                        }

                        if (CurrentProgramNo[dmx] == stlinfo.ProgramNumber) {
                            if (strapiN_iPresent()) {
                                strapiN_OnChanged(dest,
                                        HSVSPID(CurrentSubtitlingInfo, dvb,
                                                pmt), stlinfo.LangCode,
                                        stlinfo.Type, (Nat32) (HSV_INVALID_KEY),
                                        HsvEvtNull);
                            }
                        }
                    }
                    else {
                        /* Structures not different. Dont notify */
                    }
                }
                else {
                    /* database update failed for some reason */
                }
            }
            else {
                /* We update only on version changes */
            }
        }
        else {
            /* There was no such record in the database. Insert it */
            if (srtdb_Insert(SUBTITLE_TABLE_ID(dmx), stlinfo.ProgramNumber,
                    stlinfo.LangCode, stlinfo.Type, 0, (void *) (&stlinfo))) {
                if (strapiN_iPresent()) {
                    strapiN_OnAdded(dest, HSVSPID(SubtitlingInfo, dvb, pmt),
                            stlinfo.ProgramNumber, stlinfo.LangCode,
                            stlinfo.Type);
                }

                if (CurrentProgramNo[dmx] == stlinfo.ProgramNumber) {
                    if (strapiN_iPresent()) {
                        strapiN_OnAdded(dest,
                                HSVSPID(CurrentSubtitlingInfo, dvb, pmt),
                                stlinfo.LangCode, stlinfo.Type,
                                (Nat32) (HSV_INVALID_KEY));
                    }
                }
            }
            else {
                /* database updated failed for some reason */
            }
        }

        break;
    }
    case HSVSPID(AudioInfo, mpeg, pmt): {
        HsvPMTAudioInfo audioinfo = (*(HsvPMTAudioInfo *) (addr));
        HsvPMTAudioInfo audiodummy;
        /*TraceNotice(m,
                "MYLOG:  Audio PID = %d, program number = %d, pmt version = %d",
                audioinfo.Pid, audioinfo.ProgramNumber, audioinfo.PmtVersion);*/
        if (srtdb_QueryOnKey(AUDIOINFO_TABLE_ID(dmx), audioinfo.ProgramNumber,
                audioinfo.LangCode, audioinfo.AudioType, 0,
                (Address) (&audiodummy))) {
            /*TraceDebug(m, " HSVMPEG:  Dummy version = %d, actual version = %d",
                    audiodummy.PmtVersion, audioinfo.PmtVersion);*/
            if (audioinfo.PmtVersion != audiodummy.PmtVersion) {
                /* A similar record exists in the database. Update it */
                if (srtdb_Update(AUDIOINFO_TABLE_ID(dmx),
                        audioinfo.ProgramNumber, audioinfo.LangCode,
                        audioinfo.AudioType, 0, (void *) (&audioinfo))) {
                    if (!CompareAudioInfo(&audiodummy, &audioinfo)) {
                        /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                        if (strapiN_iPresent()) {
                            strapiN_OnChanged(dest,
                                    HSVSPID(AudioInfo, mpeg, pmt),
                                    audioinfo.ProgramNumber, audioinfo.LangCode,
                                    audioinfo.AudioType, HsvEvtNull);
                        }

                        if (CurrentProgramNo[dmx] == audioinfo.ProgramNumber) {
                            if (strapiN_iPresent()) {
                                strapiN_OnChanged(dest,
                                        HSVSPID(CurrentAudioInfo, mpeg, pmt),
                                        audioinfo.LangCode, audioinfo.AudioType,
                                        (Nat32) (HSV_INVALID_KEY), HsvEvtNull);
                            }
                        }
                    }
                    else {
                        /* Structures not different. Dont notify*/
                    }
                }
                else {
                    /* database update failed for some reason */
                }

            }
            else {
                /* We update information only if there was a change in PMT version */
            }
        }
        else {
            /* There was no such record in the database. Insert it */
            if (srtdb_Insert(AUDIOINFO_TABLE_ID(dmx), audioinfo.ProgramNumber,
                    audioinfo.LangCode, audioinfo.AudioType,
                    audioinfo.AudioType, (void *) (&audioinfo))) {

                if (strapiN_iPresent()) {
                    strapiN_OnAdded(dest, HSVSPID(AudioInfo, mpeg, pmt),
                            audioinfo.ProgramNumber, audioinfo.LangCode,
                            audioinfo.AudioType);
                }

                if (CurrentProgramNo[dmx] == audioinfo.ProgramNumber) {
                    if (strapiN_iPresent()) {
                        strapiN_OnAdded(dest,
                                HSVSPID(CurrentAudioInfo, mpeg, pmt),
                                audioinfo.LangCode, audioinfo.AudioType,
                                (Nat32) (HSV_INVALID_KEY));
                    }
                }
            }
            else {
                /* database updated failed for some reason */
            }
        }

        break;
    }
    case HSVSPID(ComponentTagInfo, dvb, pmt): {
        HsvPMTComponentTagInfo compinfo = (*(HsvPMTComponentTagInfo *) (addr));
        HsvPMTComponentTagInfo compdummy;

        if (srtdb_QueryOnKey(COMPONENT_TAG_TABLE_ID(dmx),
                compinfo.ProgramNumber, compinfo.ComponentTag,
                ((Nat32) (HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (Address)(&compdummy) ))
                {

                    if( compdummy.PmtVersion != compinfo.PmtVersion )
                    {
                        /* A similar record exists in the database. Update it */
                        if( srtdb_Update( COMPONENT_TAG_TABLE_ID(dmx),compinfo.ProgramNumber,compinfo.ComponentTag, ((Nat32)(HSV_INVALID_KEY)), ((Nat32)(HSV_INVALID_KEY)),(void *)(&compinfo) ) )
                        {
                            if( !CompareCompTagInfo( &compdummy, &compinfo) )
                            {
                                /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                                if( strapiN_iPresent() )
                                {
                                    strapiN_OnChanged( dest, HSVSPID(ComponentTagInfo, dvb,pmt ),compinfo.ProgramNumber,compinfo.ComponentTag, HSV_INVALID_KEY, HsvEvtNull );
                                }
                            }
                            else
                            {
                                /* Structures not different. Dont notify */
                            }
                        }
                        else
                        {
                            /* database update failed for some reason */
                        }

                    }
                }
                else
                {
                    /* There was no such record in the database. Insert it */
                    if( srtdb_Insert( COMPONENT_TAG_TABLE_ID(dmx), compinfo.ProgramNumber,compinfo.ComponentTag, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (void *)(&compinfo)) )
                    {
                        if( strapiN_iPresent() )
                        {
                            strapiN_OnAdded( dest, HSVSPID(ComponentTagInfo, dvb,pmt ), compinfo.ProgramNumber,compinfo.ComponentTag, HSV_INVALID_KEY );
                        }
                    }
                    else
                    {
                        /* database updated failed for some reason */
                    }
                }

        break;
    }
    case HSVSPID(DatabroadcastInfo, dvb, pmt): {
        HsvPMTDatabroadcastInfo dbinfo = (*(HsvPMTDatabroadcastInfo *) (addr));
        HsvPMTDatabroadcastInfo dbdummy;

        if (srtdb_QueryOnKey(DATABROADCAST_TAG_TABLE_ID(dmx),
                dbinfo.ProgramNumber, dbinfo.OUI,
                ((Nat32) (HSV_INVALID_KEY)), ((Nat32)(HSV_INVALID_KEY)),(Address)(&dbdummy) ))
                {

                    if( dbdummy.PmtVersion != dbinfo.PmtVersion )
                    {
                        /* A similar record exists in the database. Update it */
                        if( srtdb_Update( DATABROADCAST_TAG_TABLE_ID(dmx),dbinfo.ProgramNumber,dbinfo.OUI, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (void *)(&dbinfo) ) )
                        {
                            /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                            if( strapiN_iPresent() )
                            {
                                strapiN_OnChanged( dest, HSVSPID(DatabroadcastInfo, dvb,pmt ),dbinfo.ProgramNumber,dbinfo.OUI, HSV_INVALID_KEY, HsvEvtNull );
                            }
                        }
                        else
                        {
                            /* database update failed for some reason */
                        }

                    }
                }
                else
                {
                    /* There was no such record in the database. Insert it */
                    if( srtdb_Insert( DATABROADCAST_TAG_TABLE_ID(dmx), dbinfo.ProgramNumber,dbinfo.OUI, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (void *)(&dbinfo)) )
                    {
                        if( strapiN_iPresent() )
                        {
                            strapiN_OnAdded( dest, HSVSPID(DatabroadcastInfo, dvb,pmt ), dbinfo.ProgramNumber,dbinfo.OUI, HSV_INVALID_KEY );
                        }
                    }
                    else
                    {
                        /* database updated failed for some reason */
                    }
                }

        break;
    }

    default: {
        break;
    }

    } /* End of switch( property ) */

    return;
} /* End of function NotifyComponent() */
#if 0
/***********************************************************/

void CHsvMpegDataManager_Priv::DeleteRecord(HsvDemux dmx, Nat8 property, void * addr)
{
    // HsvDestination dest = HSV_MAP_DMX_TO_DEST(dmx);

    switch (property) {
    case HSVSPID(TeletextInfo, dvb, pmt): {
        HsvPMTTeletextInfo txtinfo = (*(HsvPMTTeletextInfo *) (addr));
        HsvPMTTeletextInfo txtdummy;

        if (srtdb_QueryOnKey(TELETEXT_TABLE_ID(dmx), txtinfo.ProgramNumber,
                txtinfo.LangCode, txtinfo.Type, 0, (Address) (&txtdummy))) {
            /* A similar record exists in the database. Delete it */
            if (srtdb_Delete(TELETEXT_TABLE_ID(dmx), txtinfo.ProgramNumber,
                    txtinfo.LangCode, txtinfo.Type, 0)) {
                if (strapiN_iPresent()) {
                    strapiN_OnRemoved(dest, HSVSPID(TeletextInfo, dvb, pmt),
                            txtinfo.ProgramNumber, txtinfo.LangCode,
                            txtinfo.Type);
                }
                else {
                    /* Nobody is interested in our notification */
                }
            }
            else {
                /* database update failed for some reason */
            }
        }
        else {
            /* Record did not exist. Do not bother */
        }
        break;
    }
    case HSVSPID(SubtitlingInfo, dvb, pmt): {
        HsvPMTSubtitlingInfo stlinfo = (*(HsvPMTSubtitlingInfo *) (addr));
        HsvPMTSubtitlingInfo sbtldummy;
        if (srtdb_QueryOnKey(SUBTITLE_TABLE_ID(dmx), stlinfo.ProgramNumber,
                stlinfo.LangCode, stlinfo.Type, 0, (Address) (&sbtldummy))) {
            /* A similar record exists in the database. Delete it */
            if (srtdb_Delete(SUBTITLE_TABLE_ID(dmx), stlinfo.ProgramNumber,
                    stlinfo.LangCode, stlinfo.Type, 0)) {
                if (strapiN_iPresent()) {
                    strapiN_OnRemoved(dest,
                            HSVSPID(CurrentSubtitlingInfo, dvb, pmt),
                            stlinfo.LangCode, stlinfo.Type,
                            (Nat32) (HSV_INVALID_KEY));
                }
                else {
                    /* Nobody is interested in our notification */
                }
            }
            else {
                /* database update failed for some reason */
            }
        }
        else {
            /* Record did not exist. Dont bother */
        }

        break;
    }
    case HSVSPID(AudioInfo, mpeg, pmt): {
        HsvPMTAudioInfo audioinfo = (*(HsvPMTAudioInfo *) (addr));
        HsvPMTAudioInfo audiodummy;

        if (srtdb_QueryOnKey(AUDIOINFO_TABLE_ID(dmx), audioinfo.ProgramNumber,
                audioinfo.LangCode, audioinfo.AudioType, 0,
                (Address) (&audiodummy))) {
            /* A similar record exists in the database. Update it */
            if (srtdb_Delete(AUDIOINFO_TABLE_ID(dmx), audioinfo.ProgramNumber,
                    audioinfo.LangCode, audioinfo.AudioType, 0)) {

                /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                if (strapiN_iPresent()) {
                    strapiN_OnRemoved(dest, HSVSPID(AudioInfo, mpeg, pmt),
                            audioinfo.ProgramNumber, audioinfo.LangCode,
                            audioinfo.AudioType);
                }
                if (CurrentProgramNo[dmx] == audioinfo.ProgramNumber) {
                    if (strapiN_iPresent()) {
                        strapiN_OnRemoved(dest,
                                HSVSPID(CurrentAudioInfo, mpeg, pmt),
                                audioinfo.ProgramNumber, audioinfo.LangCode,
                                audioinfo.AudioType);
                    }
                }

            }
            else {
                /* database update failed for some reason */
            }
        }
        else {
            /* Record did not exist. Do not bother */
        }

        break;
    }
    case HSVSPID(ComponentTagInfo, dvb, pmt): {
        HsvPMTComponentTagInfo comptaginfo = (*(HsvPMTComponentTagInfo*) (addr));
        HsvPMTComponentTagInfo comptagdummy;

        if (srtdb_QueryOnKey(COMPONENT_TAG_TABLE_ID(dmx),
                comptaginfo.ProgramNumber, comptaginfo.ComponentTag,
                ((Nat32) (HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (Address)(&comptagdummy) ))
                {
                    /* A similar record exists in the database. Update it */
                    if( srtdb_Delete( COMPONENT_TAG_TABLE_ID(dmx),comptaginfo.ProgramNumber,comptaginfo.ComponentTag, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)) ) )
                    {

                        /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                        if( strapiN_iPresent() )
                        {
                            strapiN_OnRemoved( dest, HSVSPID(ComponentTagInfo, dvb, pmt),comptaginfo.ProgramNumber,comptaginfo.ComponentTag, HSV_INVALID_KEY);
                        }

                    }
                    else
                    {
                        /* database update failed for some reason */
                    }
                }
                else
                {
                    /* Record did not exist. Do not bother */
                }

        break;

    }

    case HSVSPID(DatabroadcastInfo, dvb, pmt): {
        HsvPMTDatabroadcastInfo dbinfo = (*(HsvPMTDatabroadcastInfo*) (addr));
        HsvPMTDatabroadcastInfo dbdummy;

        if (srtdb_QueryOnKey(DATABROADCAST_TAG_TABLE_ID(dmx),
                dbinfo.ProgramNumber, dbinfo.OUI,
                ((Nat32) (HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)), (Address)(&dbdummy) ))
                {
                    /* A similar record exists in the database. Update it */
                    if( srtdb_Delete( DATABROADCAST_TAG_TABLE_ID(dmx),dbinfo.ProgramNumber,dbinfo.OUI, ((Nat32)(HSV_INVALID_KEY)),((Nat32)(HSV_INVALID_KEY)) ) )
                    {

                        /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                        if( strapiN_iPresent() )
                        {
                            strapiN_OnRemoved( dest, HSVSPID(DatabroadcastInfo, dvb, pmt),dbinfo.ProgramNumber,dbinfo.OUI, HSV_INVALID_KEY);
                        }

                    }
                    else
                    {
                        /* database update failed for some reason */
                    }
                }
                else
                {
                    /* Record did not exist. Do not bother */
                }

        break;

    }

    default: {
        break;
    }

    } /* End of switch( property ) */

    return;

} /* End of function DeleteRecord() */
#endif
/***********************************************************/


void CHsvMpegDataManager_Priv::FreeDataBaseObjects(HsvDemux dmx, int prg)
{
    int i = 0;
    HsvPMTBasicPidInfo basicpidinfo;
    HsvPMTSubtitlingInfo stlinfo;
    HsvPMTTeletextInfo txtinfo;
    HsvPMTAudioInfo audioinfo;
    HsvPMTComponentTagInfo compinfo;
    HsvPMTDatabroadcastInfo dbinfo;

    for (i = (srtdb_GetNoOfRecords(BASIC_PID_TABLE_ID(dmx)) - 1); i >= 0; i--) {

        if (srtdb_QueryOnIndex((BASIC_PID_TABLE_ID(dmx)), i,
                (void *) (&basicpidinfo))) {
            if (basicpidinfo.ProgramNumber == prg) {
                srtdb_Delete((BASIC_PID_TABLE_ID(dmx)),
                        basicpidinfo.ProgramNumber, (Nat32) (HSV_INVALID_KEY),
                        (Nat32) (HSV_INVALID_KEY), (Nat32) (HSV_INVALID_KEY));
            }
        }
    }

    for (i = (srtdb_GetNoOfRecords(SUBTITLE_TABLE_ID(dmx)) - 1); i >= 0; i--) {

        if (srtdb_QueryOnIndex((SUBTITLE_TABLE_ID(dmx)), i,
                (void *) (&stlinfo))) {
            if (stlinfo.ProgramNumber == prg) {
                srtdb_Delete((SUBTITLE_TABLE_ID(dmx)), stlinfo.ProgramNumber,
                        stlinfo.LangCode, stlinfo.Type, 0);
            }
        }
    }

    for (i = (srtdb_GetNoOfRecords(TELETEXT_TABLE_ID(dmx)) - 1); i >= 0; i--) {

        if (srtdb_QueryOnIndex((TELETEXT_TABLE_ID(dmx)), i,
                (void *) (&txtinfo))) {
            if (txtinfo.ProgramNumber == prg) {
                srtdb_Delete((TELETEXT_TABLE_ID(dmx)), txtinfo.ProgramNumber,
                        txtinfo.LangCode, txtinfo.Type, 0);
            }
        }
    }

    for (i = (srtdb_GetNoOfRecords(AUDIOINFO_TABLE_ID(dmx)) - 1); i >= 0; i--) {

        if (srtdb_QueryOnIndex((AUDIOINFO_TABLE_ID(dmx)), i,
                (void *) (&audioinfo))) {
            if (audioinfo.ProgramNumber == prg) {
                srtdb_Delete((AUDIOINFO_TABLE_ID(dmx)), audioinfo.ProgramNumber,
                        audioinfo.LangCode, audioinfo.AudioType, 0);
            }
        }
    }

    for (i = (srtdb_GetNoOfRecords(COMPONENT_TAG_TABLE_ID(dmx)) - 1); i >= 0;
            i--) {

        if (srtdb_QueryOnIndex((COMPONENT_TAG_TABLE_ID(dmx)), i,
                (void *) (&compinfo))) {
            if (audioinfo.ProgramNumber == prg) {
                srtdb_Delete((COMPONENT_TAG_TABLE_ID(dmx)),
                        compinfo.ProgramNumber, compinfo.ComponentTag,
                        (Nat32) HSV_INVALID_KEY, (Nat32) HSV_INVALID_KEY);
            }
        }
    }

    for (i = (srtdb_GetNoOfRecords(DATABROADCAST_TAG_TABLE_ID(dmx)) - 1);
            i >= 0; i--) {

        if (srtdb_QueryOnIndex((DATABROADCAST_TAG_TABLE_ID(dmx)), i,
                (void *) (&dbinfo))) {
            if (dbinfo.ProgramNumber == prg) {
                srtdb_Delete((DATABROADCAST_TAG_TABLE_ID(dmx)),
                        dbinfo.ProgramNumber, dbinfo.OUI,
                        (Nat32) HSV_INVALID_KEY, (Nat32) HSV_INVALID_KEY);
            }
        }
    }

} /* End of function FreeDataBaseObjects() */
/*************************************************************************/

Nat8 CHsvMpegDataManager_Priv::GetLanguageId(Nat32 Language)
{
    /* Assume that the lower 3 bytes of the Nat32 contain the 3 byte code */
    char byte1 = (char) ((((Nat32) (Language) & 0xFF0000)) >> 16);
    char byte2 = (char) ((((Nat32) (Language) & 0xFF00)) >> 8);
    char byte3 = (char) ((((Nat32) (Language) & 0xFF)));

    return (Nat8) (mpegserv_GetLanguageId(byte1, byte2, byte3));
} /* End of function GetLanguageId() */
/*************************************************************************/
#if 0

Bool CHsvMpegDataManager_Priv::CompareBpidInfo(HsvPMTBasicPidInfo * comp1,
        HsvPMTBasicPidInfo * comp2)
{
    Bool retval = FALSE;
    if (comp1->ProgramNumber == comp2->ProgramNumber) {
        if (comp1->VideoPid == comp2->VideoPid) {
            if (comp1->PcrPid == comp2->PcrPid) {
                if (comp1->TeletextPid == comp2->TeletextPid) {
                    if (comp1->VideoStreamType == comp2->VideoStreamType) {
                        retval = TRUE;
                    }
                }
            }
        }
    }

    return retval;

}
#endif

Bool CHsvMpegDataManager_Priv::CompareTxtInfo(HsvPMTTeletextInfo * comp1,
        HsvPMTTeletextInfo * comp2)
{
    Bool retval = FALSE;
    if (comp1->ProgramNumber == comp2->ProgramNumber) {
        if (comp1->LangCode == comp2->LangCode) {
            if (comp1->Language == comp2->Language) {
                if (comp1->Type == comp2->Type) {
                    if (comp1->Pid == comp2->Pid) {
                        if (comp1->TeletextMagazieNo
                                == comp2->TeletextMagazieNo) {
                            if (comp1->TeletextPageNo
                                    == comp2->TeletextPageNo) {
                                retval = TRUE;
                            }
                        }
                    }
                }
            }
        }
    }

    return retval;

}

Bool CHsvMpegDataManager_Priv::CompareSbtlInfo(HsvPMTSubtitlingInfo * comp1,
        HsvPMTSubtitlingInfo * comp2)
{
    Bool retval = FALSE;
    if (comp1->ProgramNumber == comp2->ProgramNumber) {
        if (comp1->LangCode == comp2->LangCode) {
            if (comp1->Language == comp2->Language) {
                if (comp1->Type == comp2->Type) {
                    if (comp1->Pid == comp2->Pid) {
                        if (comp1->TeletextMagazieNo
                                == comp2->TeletextMagazieNo) {
                            if (comp1->TeletextPageNo
                                    == comp2->TeletextPageNo) {
                                if (comp1->CompositionPageId
                                        == comp2->CompositionPageId) {
                                    if (comp1->AncilliaryPageId
                                            == comp2->AncilliaryPageId) {
                                        retval = TRUE;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return retval;
}

Bool CHsvMpegDataManager_Priv::CompareCompTagInfo(HsvPMTComponentTagInfo * comp1,
        HsvPMTComponentTagInfo * comp2)
{
    Bool retval = FALSE;
    if (comp1->ProgramNumber == comp2->ProgramNumber) {
        if (comp1->ComponentTag == comp2->ComponentTag) {
            if (comp1->Pid == comp2->Pid) {
                retval = TRUE;
            }
        }
    }

    return retval;

}

/*
 static Bool CompareDatabroadcastInfo( HsvPMTDatabroadcastInfo * comp1, HsvPMTDatabroadcastInfo * comp2 )
 {
 Bool retval = FALSE;
 if( comp1->ProgramNumber == comp2->ProgramNumber )
 {
 if( comp1->OUI == comp2->OUI )
 {
 if( comp1->Pid == comp2->Pid )
 {
 retval = TRUE;
 }
 }
 }

 return retval;

 }
 */

Bool CHsvMpegDataManager_Priv::CompareAudioInfo(HsvPMTAudioInfo * comp1, HsvPMTAudioInfo * comp2)
{
    Bool retval = FALSE;
    if (comp1->ProgramNumber == comp2->ProgramNumber) {
        if (comp1->LangCode == comp2->LangCode) {
            if (comp1->Language == comp2->Language) {
                if (comp1->AudioType == comp2->AudioType) {
                    if (comp1->Pid == comp2->Pid) {
                        retval = TRUE;
                    }
                }
            }
        }
    }

    return retval;
}

void CHsvMpegDataManager_Priv::mMpegPumpHandler(int dmx, Nat32 index)
{

	if(dmx < HsvDmxLast){
	    // check with mounesh what to do with dmx param - should it be hsvmain?
	    ProgramData[dmx].programList[index].subscriptionID = sec_RequestSection2(
	            HSV_MAP_DMX_TO_DEST(dmx), ProgramData[dmx].programList[index].Pid,
	            TS_PROGRAM_MAP_SECTION_TABLE_ID,
	            ProgramData[dmx].programList[index].programNo, /* Program number is both cookie and table ID extension field*/
	            ProgramData[dmx].programList[index].programNo,
	            FNADDR(pmt_Parser_Parser));
	}

}

void CHsvMpegDataManager_Priv::mMonitorProgramPmpHandler(int param1, Nat32 param2)
{

    int i;
    int pid = INVALID_PROGRAM_MAP_PID;

    Nat16 dmx = (param1 & 0xffff);
    Nat16 eventid = ((param1 >> 16) & 0xffff);
    //Nat16 index = (param2 & 0xffff);
    Nat16 prg = ((param2 >> 16) & 0xffff);

    TraceNotice (m, "%s() : prg %d\n", __FUNCTION__, prg);

	if(dmx < HsvDmxLast){
	    switch (eventid) {
	    case MONITOR_PROGRAM:

	        /* If a PAT had been seen before, we can determine the PMT PID from the PAT */
	        for (i = 0; i < ProgramData[dmx].programs; i++) {
	            if (prg == ProgramData[dmx].programList[i].programNo) {
	                pid = ProgramData[dmx].programList[i].Pid;
	                break;
	            }
	        }
	        CurrentProgramNo[dmx] = prg;
	        /* Clear everything so that we can issue fresh notifications when a monitor call is made */
	        rtk_SemAcquire(SubscriptionSem[dmx]);
	        SubscribeForProgram(dmx, prg, pid, i);
	        rtk_SemRelease(SubscriptionSem[dmx]);
	        break;

	    case MONITOR_PROGRAM_BY_INDEX:

	        for (i = 0; i < ProgramData[dmx].programs; i++) {
	            if (prg == ProgramData[dmx].programList[i].programNo) {
	                pid = ProgramData[dmx].programList[i].Pid;
	                break;
	            }
	        }
	        rtk_SemAcquire(SubscriptionSem[dmx]);
	        SubscribeForProgram(dmx, prg, pid, i);
	        rtk_SemRelease(SubscriptionSem[dmx]);
	        break;

	    default:
	        break;

	    }
	}
}
/******************************************************************************/

Bool CHsvMpegDataManager_Priv::pmtstrapi_GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)
{
	return FALSE;
}

Bool CHsvMpegDataManager_Priv::patstrapi_GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)
{
	return FALSE;
}

void CHsvMpegDataManager_Priv::mpegsecn_MonitorProgram2(HsvDemux dmx,int prg)
{
}

void CHsvMpegDataManager_Priv::init_Init(void)
{
}
