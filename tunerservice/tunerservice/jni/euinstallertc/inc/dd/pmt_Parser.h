#ifndef _PMT_PARSER_H_
#define _PMT_PARSER_H_

struct _TsVBITeletextData{
	Nat32     lang_code;
	Nat8     type;
	Nat8     magazine_no;
	Nat8     page_no;
};

struct _TsVBI_teletext_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescrptorLength;
	Nat8     loopCount;
	struct _TsVBITeletextData VBITeletextData[5];
	Nat8     DescriptorValid;
};

struct _TsteletextLoop{
	Nat32     lang_code;
	Nat8     type;
	Nat8     magazine_no;
	Nat8     page_no;
};

struct _TsTeletext_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescrptorLength;
	Nat8     loopCount;
	struct _TsteletextLoop teletextLoop[5];
	Nat8     DescriptorValid;
};

struct _TssubtitleData{
	Nat32     lang_code;
	Nat8     type;
	Nat16     comp_page_id;
	Nat16     ancillary_page_id;
};

struct _TsSubtitling_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescrptorLength;
	Nat8     loopCount;
	struct _TssubtitleData subtitleData[5];	
	Nat8     DescriptorValid;
};	

struct _TsStream_identifier_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescrptorLength;
	Nat8     component_tag;
	Nat8     DescriptorValid;
};	

struct _CountryRating{
	Nat32     CountryCode;
	Nat8     Rating;
};

struct _ParentalRating_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescriptorLen;
	Nat8     CountryRatingNum;
	struct _CountryRating CountryRating[80];
	Nat8     DescriptorValid;
};

    struct _TsLanguageLoop{
        Nat32     lang;
        Nat8     audioType;
    };

    struct _TsISO_Lang_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     loopCount;
		struct _TsLanguageLoop LanguageLoop[5];
        Nat8     DescriptorValid;
    };

    struct _TsData_broadcast_ID_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat16     data_broadcast_id;
        Nat8     id_selector_length;
        Nat8     selector_byte[100];
        Nat8     DescriptorValid;
    };	

    struct _TsAVC_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     profile_idc;
        Nat8     constraint_set0_flag;
        Nat8     constraint_set1_flag ;
        Nat8     constraint_set2_flag ;
        Nat8     constraint_set3_flag;
        Nat8     constraint_set4_flag;
        Nat8     constraint_set5_flag;
        Nat8     AVC_compatible_flags;
        Nat8     level_idc;
        Nat8     AVC_still_present;
        Nat8     AVC_24_hour_picture_flag;
        Nat8     frame_packing_SEI_not_present_flag;
        Nat8     DescriptorValid;
    };
	
    struct _TsSupplementary_audio_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     tag_extension;
        Nat8     mix_type;
        Nat8     editorial_classification;
        Nat8     lang_code_present;
        Nat32    lang_code;
        Nat8     DescriptorValid;
    };	

    struct _TsAC3_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     component_type_flag;
        Nat8     bsid_flag;
        Nat8     mainid_flag;
        Nat8     asvc_flag;
        Nat8     component_type;
        Nat8     bsid;
        Nat8     mainid;
        Nat8     asvc;
        Nat8     DescriptorValid;
    };
	
    struct _TsEAC3_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     component_type_flag;
        Nat8     bsid_flag;
        Nat8     mainid_flag;
        Nat8     asvc_flag;
        Nat8     mixinfoexists;
        Nat8     substream1_flag;
        Nat8     substream2_flag;
        Nat8     substream3_flag;
        Nat8     component_type;
        Nat8     bsid;
        Nat8     mainid;
        Nat8     asvc;
        Nat8     substream1;
        Nat8     substream2;
        Nat8     substream3;
        Nat8     DescriptorValid;
    };	
	
    struct _TsAAC_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescrptorLength;
        Nat8     profile_and_level;
        Nat8     aac_type_flag;
        Nat8     aac_type;
        Nat8     DescriptorValid;
    };	
	
    struct _esData{
		Nat8     stream_type;
		Nat16     es_pid;
		Nat16     es_info_length;
		struct _TsVBI_teletext_Descriptor VBI_teletext_Descriptor[2];
		Nat8     VBI_TT_desc_count;
		struct _TsTeletext_Descriptor Teletext_Descriptor[2];
		Nat8     teletext_desc_count;
		struct _TsSubtitling_Descriptor Subtitling_Descriptor[2];
		Nat8     subtitle_dec_count;
		struct _TsStream_identifier_Descriptor Stream_identifier_Descriptor[2];
		Nat8     stream_id_desc_count;
		struct _TsISO_Lang_Descriptor ISO_Lang_Descriptor[2];
		Nat8     iso_lang_desc_count;
		struct _TsData_broadcast_ID_Descriptor Data_broadcast_ID_Descriptor[2];
		Nat8     data_bc_id_desc_count;
		struct _TsAVC_Descriptor AVC_Descriptor[2];
		Nat8     avc_desc_count;
		struct _TsSupplementary_audio_Descriptor Supplementary_audio_Descriptor[2];
		Nat8     suppl_audio_desc_count;
		struct _TsAC3_Descriptor AC3_Descriptor[2];
		Nat8     ac3_desc_count;
		struct _TsEAC3_Descriptor EAC3_Descriptor[2];
		Nat8     eac3_desc_count;
		struct _TsAAC_Descriptor AAC_Descriptor[2];
		Nat8     aac_desc_count;
    };	
	
typedef struct _pmt_Parser{
    Nat8     TableId;
    Nat16     section_length;
    Nat16     program_number;
    Nat8     version_no;
    Nat16     PCR_Pid;
    Nat16     program_info_length;
	struct _ParentalRating_Descriptor ParentalRating_Descriptor[2];
    Nat8     PRDNum;
    Nat16     TsLoopLen;
    Nat8     TsLoopDataNum;
	struct _esData esData[10];	
}Typepmt_Parser;

#endif