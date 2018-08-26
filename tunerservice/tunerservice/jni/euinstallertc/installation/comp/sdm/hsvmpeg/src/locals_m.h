#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include"_hsvmpeg_m.h"

#include<hsvmpeg_errorids.h>

#include<pat_Parser.h>

#include<pmt_Parser.h>

#include <string.h>

/******************************************************************************/

#define pen_PumpEngine 0

#define strapiN_iPresent()  1

#define PAT_TABLE_ID_VALUE                  (0x00)

#define PAT_PID_VALUE                       (0x00)

#define TS_PROGRAM_MAP_SECTION_TABLE_ID     (0x02)

/* Error status values */

#define PROGRAM_MAP_PID_CHANGE              (-2  )

#define PROGRAM_NUMBER_FOR_NETWORK_PID      ( 0  )

#define INVALID_PID                         (0x1FFF)

#define HSV_INVALID_KEY                     (-1)

#define RETRY_REQUEST                       1000

#define MAX_PROGRAM_INFO_LENGTH             (1021)

#define MAX_PMT_SECTION_SIZE                (1024)                          /* The maximum possible size of a PMT section */

#define MAX_ES_INFO_LENGTH                  (1021)

#define MAX_PMT_SECTION_LENGTH              (1021)                          /* The maximum value that the section_length field is allowed to have */

#define MAX_PROGRAM_ELEMENTS                ( 10  )

#define MAX_PMT_MONITORS                    ( 5 )//sdmdiv_MaxPmtMonitors  )      /* Make this diversity dependent. 1 for selection. 1 for MPL. 5 for MHEG*/

#define CURRENT_PROGRAM_INDEX               ( 6  )                          /* Take the last PMT section for the current filter */

#define MAX_DESCRIPTORS_IN_PROGRAM_ELEMENT  ( 5  )

#define PROGRAM_ACQUIRED                    ( 0  )

#define PROGRAM_NOT_ACQUIRED                ( 1  )

#define INVALID_PROGRAM_NUMBER              ( 0  )

#define INVALID_PROGRAM_MAP_PID             ( -1 )

#define INVALID_ELEMENTARY_PID              ( -1 )

#define PROGRAM_ELEMENT_HEADER_LENGTH       ( 5  )

#define HSV_CLEAN_EFFECTS_TYPE              (0x01)                          /* See table 2-53 of IS 13818_1 2nd edition */

#define HSV_LOWEST_BYTE(a)                  ((a) &0xFF)

#define HSV_SECOND_LOWEST_BYTE(a)           (((a) >> 8) & 0xFF)

#define HSV_MAKE_CHAR_MASK(a,b,c)           ( ((((Nat32)(a))<<16) ) | (((Nat32)(b))<<8) | (((Nat32)(c))) )

#define MAX_POSSIBLE_PMT_VIDEO_PIDS         (5)         /* Maximum number of Video PIDs which can be seen in PMT*/

#define PMT_TABLE_ARRAY_INDEX_VALUE         ( pmt_Table  )


/* Program and Program Element descriptor tag values */
/* Refer Table 2-40 in IS13818-1 standards document */

#define VIDEO_STREAM_DESCRIPTOR_TAG         (0x02)

#define AUDIO_STREAM_DESCRIPTOR_TAG         (0x03)

#define MPEG4_VIDEO_STREAM_DESCRIPTOR_TAG   (0x1B)//mohanan
/* These descriptor tag values have been obtained from the ATSC A65/B standards document */

#define CONTENT_ADVISORY_DESCRIPTOR_TAG     (0x87)

#define AC3_AUDIO_STREAM_DESCRIPTOR_TAG     (0x81)

#define CAPTION_SERVICE_DESCRIPTOR_TAG      (0x86)

/* Defined in the IS0/IEC 13818-1 standards document */

#define ISO639_LANGUAGE_DESCRIPTOR_TAG      (0x0A)

/* Stream types. Most of these are available in Table 2-36
 of IS138181-1 standards document. The ATSC_A52_AC3_STREAM_TYPE
 value is from the A65/B standards document */

#define ISO_IEC_11172_VIDEO_STREAM_TYPE         (Hsv_ISOIEC_11172_STREAM_TYPE_VIDEO)

#define ISO_IEC_13818_2_VIDEO_STREAM_TYPE       (Hsv_ISOIEC_13818_2_STREAM_TYPE_VIDEO)

#define ISO_IEC_11172_2_VIDEO_STREAM_TYPE       (Hsv_ISOIEC_11172_2_STREAM_TYPE_VIDEO)
//#define ISO_IEC_13818_2_ITUT_VIDEO_STREAM_TYPE  (Hsv_ISOIEC_13818_2_STREAM_TYPE_ITUT_VIDEO)

#define ISO_IEC_13818_6_STREAM_TYPE_B           (Hsv_ISOIEC_13818_6_STREAM_TYPE_B)

#define ISO_IEC_11172_AUDIO_STREAM_TYPE     (Hsv_ISOIEC_11172_STREAM_TYPE_AUDIO)

#define ISO_IEC_13818_3_AUDIO_STREAM_TYPE   (Hsv_ISOIEC_13818_3_STREAM_TYPE_AUDIO)

#define ATSC_A52_AC3_STREAM_TYPE            (Hsv_ATSC_A52_STREAM_TYPE_AC3)

#define MPEG4_HEAAC_STREAM_TYPE             (Hsv_MPEG4_STREAM_TYPE_HEAAC)

#define MPEG4_AAC_STREAM_TYPE               (Hsv_MPEG4_STREAM_TYPE_AAC)

#define MPEG4_AC3PLUS_STREAM_TYPE           (6)

#define MAX_POSSIBLE_PROGRAMS               (50)

#define ISO_IEC_13818_1_PRIVATE_STREAM_TYPE (Hsv_ISOIEC_13818_1_STREAM_TYPE_PRIVATE)

#define H264_VIDEO_STREAM_TYPE                  (Hsv_H264_STREAM_TYPE_VIDEO)

#define TELETEXT_TABLE_ID(dmx)          (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_TeletextInfoMain)         : (srtdbids_TeletextInfoAux))

#define VBI_TELETEXT_TABLE_ID(dmx)      (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_TeletextInfoMain)         : (srtdbids_TeletextInfoAux))

#define SUBTITLE_TABLE_ID(dmx)          (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_SubtitlingInfoMain)       : (srtdbids_SubtitlingInfoAux))

#define BASIC_PID_TABLE_ID(dmx)         (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_BasicPidInfoMain)         : (srtdbids_BasicPidInfoAux))

#define AUDIOINFO_TABLE_ID(dmx)         (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_AudioInfoMain)            : (srtdbids_AudioInfoAux))

#define COMPONENT_TAG_TABLE_ID(dmx)     (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_ComponentTagInfoMain)     : (srtdbids_ComponentTagInfoAux))

#define DATABROADCAST_TAG_TABLE_ID(dmx) (((dmx) == ((Nat32)(HsvDmxMain))) ?  (srtdbids_DatabroadcastInfoMain)    : (srtdbids_DatabroadcastInfoAux))

#define DescLoops(name)                 (sizeof(name)/sizeof(name[0]))

#define NOADSTREAM                      (0)

#define SUB_STREAM1                     (1)

#define SUB_STREAM2                     (2)

#define SUB_STREAM3                     (3)


/* Cookies to identify descriptor postion */

#define LOOP0 0

#define LOOP1 1


/* Add Win 32 correction for mode match mask settings to help dvptst demux */

#ifdef WIN32

#define TABLE_ID_EXTN_FIELD            (3)

#else

#define TABLE_ID_EXTN_FIELD            (1)

#endif

#define TABLEID_MASK                   (0xFF)

/***********************************************/

typedef struct {
    Nat8 versionNo;
    Nat16 programNo;
    Nat16 Pid;
    Nat16 PcrPid;
    Nat32 subscriptionID;
    Bool collected;
    Nat8 *pmtSecData;
} HsvPmtData;
typedef struct {
    Nat8 PatVersionNo;
    Nat16 tsID;
    Nat32 programs;
    Nat32 subscriptionID;
    HsvPmtData programList[MAX_POSSIBLE_PROGRAMS];
} HsvTSData;
enum {
    MONITOR_PROGRAM, MONITOR_PROGRAM_BY_INDEX
};
#if 0
/** Within clauses added here */
//#define langids_MaxNumberOfLanguages	((int)0x2E)

#define langids_MaxNumberOfLanguages_CONSTANT	0x2E
/*** provides interfaces ***/

/* interface audioinfoconfaux : IHsvSortedTableConfigurationEx */

#define audioinfoconfaux_ICONNECTED	1

#define audioinfoconfaux_BiggerKey	((Nat8)0x2)

#define audioinfoconfaux_BiggerKey_CONSTANT	0x2
// #define audioinfoconfaux_ComparePrimaryKey	hsvmpeg__audioinfoconfmain_ComparePrimaryKey
// #define audioinfoconfaux_CompareQuaternaryKey	hsvmpeg__audioinfoconfmain_CompareQuaternaryKey
// #define audioinfoconfaux_CompareSecondaryKey	hsvmpeg__audioinfoconfmain_CompareSecondaryKey
// #define audioinfoconfaux_CompareTeritiaryKey	hsvmpeg__audioinfoconfmain_CompareTeritiaryKey

#define audioinfoconfaux_ElementSize	sizeof(HsvPMTAudioInfo)

#define audioinfoconfaux_Equal	((Nat8)0x1)

#define audioinfoconfaux_Equal_CONSTANT	0x1

#define audioinfoconfaux_MaxElements	((int)0x46)

#define audioinfoconfaux_MaxElements_CONSTANT	0x46

#define audioinfoconfaux_Primary	((Nat8)0x1)

#define audioinfoconfaux_Primary_CONSTANT	0x1

#define audioinfoconfaux_Quaternary	((Nat8)0x8)

#define audioinfoconfaux_Quaternary_CONSTANT	0x8

#define audioinfoconfaux_Secondary	((Nat8)0x2)

#define audioinfoconfaux_Secondary_CONSTANT	0x2

#define audioinfoconfaux_SmallerKey	((Nat8)0x0)

#define audioinfoconfaux_SmallerKey_CONSTANT	0x0

#define audioinfoconfaux_SortCriteria	((Nat8)0x7)

#define audioinfoconfaux_SortCriteria_CONSTANT	0x7

#define audioinfoconfaux_Teritiary	((Nat8)0x4)

#define audioinfoconfaux_Teritiary_CONSTANT	0x4

#define audioinfoconfaux_ThreadSafe	((Bool)0x1)

#define audioinfoconfaux_ThreadSafe_CONSTANT	0x1

/* interface audioinfoconfmain : IHsvSortedTableConfigurationEx */

#define audioinfoconfmain_ICONNECTED	1

#define audioinfoconfmain_BiggerKey	((Nat8)0x2)

#define audioinfoconfmain_BiggerKey_CONSTANT	0x2
// #define audioinfoconfmain_ComparePrimaryKey	hsvmpeg__audioinfoconfmain_ComparePrimaryKey
// #define audioinfoconfmain_CompareQuaternaryKey	hsvmpeg__audioinfoconfmain_CompareQuaternaryKey
// #define audioinfoconfmain_CompareSecondaryKey	hsvmpeg__audioinfoconfmain_CompareSecondaryKey
// #define audioinfoconfmain_CompareTeritiaryKey	hsvmpeg__audioinfoconfmain_CompareTeritiaryKey

#define audioinfoconfmain_ElementSize	sizeof(HsvPMTAudioInfo)

#define audioinfoconfmain_Equal	((Nat8)0x1)

#define audioinfoconfmain_Equal_CONSTANT	0x1

#define audioinfoconfmain_MaxElements	((int)0x46)

#define audioinfoconfmain_MaxElements_CONSTANT	0x46

#define audioinfoconfmain_Primary	((Nat8)0x1)

#define audioinfoconfmain_Primary_CONSTANT	0x1

#define audioinfoconfmain_Quaternary	((Nat8)0x8)

#define audioinfoconfmain_Quaternary_CONSTANT	0x8

#define audioinfoconfmain_Secondary	((Nat8)0x2)

#define audioinfoconfmain_Secondary_CONSTANT	0x2

#define audioinfoconfmain_SmallerKey	((Nat8)0x0)

#define audioinfoconfmain_SmallerKey_CONSTANT	0x0

#define audioinfoconfmain_SortCriteria	((Nat8)0x7)

#define audioinfoconfmain_SortCriteria_CONSTANT	0x7

#define audioinfoconfmain_Teritiary	((Nat8)0x4)

#define audioinfoconfmain_Teritiary_CONSTANT	0x4

#define audioinfoconfmain_ThreadSafe	((Bool)0x1)

#define audioinfoconfmain_ThreadSafe_CONSTANT	0x1

/* interface basicpidinfoconfaux : IHsvSortedTableConfigurationEx */

#define basicpidinfoconfaux_ICONNECTED	1

#define basicpidinfoconfaux_BiggerKey	((Nat8)0x2)

#define basicpidinfoconfaux_BiggerKey_CONSTANT	0x2
// #define basicpidinfoconfaux_ComparePrimaryKey	hsvmpeg__basicpidinfoconfmain_ComparePrimaryKey
// #define basicpidinfoconfaux_CompareQuaternaryKey	hsvmpeg__basicpidinfoconfmain_CompareQuaternaryKey
// #define basicpidinfoconfaux_CompareSecondaryKey	hsvmpeg__basicpidinfoconfmain_CompareSecondaryKey
// #define basicpidinfoconfaux_CompareTeritiaryKey	hsvmpeg__basicpidinfoconfmain_CompareTeritiaryKey

#define basicpidinfoconfaux_ElementSize	sizeof(HsvPMTBasicPidInfo)

#define basicpidinfoconfaux_Equal	((Nat8)0x1)

#define basicpidinfoconfaux_Equal_CONSTANT	0x1

#define basicpidinfoconfaux_MaxElements	((int)0x7)

#define basicpidinfoconfaux_MaxElements_CONSTANT	0x7

#define basicpidinfoconfaux_Primary	((Nat8)0x1)

#define basicpidinfoconfaux_Primary_CONSTANT	0x1

#define basicpidinfoconfaux_Quaternary	((Nat8)0x8)

#define basicpidinfoconfaux_Quaternary_CONSTANT	0x8

#define basicpidinfoconfaux_Secondary	((Nat8)0x2)

#define basicpidinfoconfaux_Secondary_CONSTANT	0x2

#define basicpidinfoconfaux_SmallerKey	((Nat8)0x0)

#define basicpidinfoconfaux_SmallerKey_CONSTANT	0x0

#define basicpidinfoconfaux_SortCriteria	((Nat8)0x1)

#define basicpidinfoconfaux_SortCriteria_CONSTANT	0x1

#define basicpidinfoconfaux_Teritiary	((Nat8)0x4)

#define basicpidinfoconfaux_Teritiary_CONSTANT	0x4

#define basicpidinfoconfaux_ThreadSafe	((Bool)0x1)

#define basicpidinfoconfaux_ThreadSafe_CONSTANT	0x1

/* interface basicpidinfoconfmain : IHsvSortedTableConfigurationEx */

#define basicpidinfoconfmain_ICONNECTED	1

#define basicpidinfoconfmain_BiggerKey	((Nat8)0x2)

#define basicpidinfoconfmain_BiggerKey_CONSTANT	0x2
// #define basicpidinfoconfmain_ComparePrimaryKey	hsvmpeg__basicpidinfoconfmain_ComparePrimaryKey
// #define basicpidinfoconfmain_CompareQuaternaryKey	hsvmpeg__basicpidinfoconfmain_CompareQuaternaryKey
// #define basicpidinfoconfmain_CompareSecondaryKey	hsvmpeg__basicpidinfoconfmain_CompareSecondaryKey
// #define basicpidinfoconfmain_CompareTeritiaryKey	hsvmpeg__basicpidinfoconfmain_CompareTeritiaryKey

#define basicpidinfoconfmain_ElementSize	sizeof(HsvPMTBasicPidInfo)

#define basicpidinfoconfmain_Equal	((Nat8)0x1)

#define basicpidinfoconfmain_Equal_CONSTANT	0x1

#define basicpidinfoconfmain_MaxElements	((int)0x7)

#define basicpidinfoconfmain_MaxElements_CONSTANT	0x7

#define basicpidinfoconfmain_Primary	((Nat8)0x1)

#define basicpidinfoconfmain_Primary_CONSTANT	0x1

#define basicpidinfoconfmain_Quaternary	((Nat8)0x8)

#define basicpidinfoconfmain_Quaternary_CONSTANT	0x8

#define basicpidinfoconfmain_Secondary	((Nat8)0x2)

#define basicpidinfoconfmain_Secondary_CONSTANT	0x2

#define basicpidinfoconfmain_SmallerKey	((Nat8)0x0)

#define basicpidinfoconfmain_SmallerKey_CONSTANT	0x0

#define basicpidinfoconfmain_SortCriteria	((Nat8)0x1)

#define basicpidinfoconfmain_SortCriteria_CONSTANT	0x1

#define basicpidinfoconfmain_Teritiary	((Nat8)0x4)

#define basicpidinfoconfmain_Teritiary_CONSTANT	0x4

#define basicpidinfoconfmain_ThreadSafe	((Bool)0x1)

#define basicpidinfoconfmain_ThreadSafe_CONSTANT	0x1

/* interface componenttaginfoaux : IHsvSortedTableConfigurationEx */

#define componenttaginfoaux_ICONNECTED	1

#define componenttaginfoaux_BiggerKey	((Nat8)0x2)

#define componenttaginfoaux_BiggerKey_CONSTANT	0x2
// #define componenttaginfoaux_ComparePrimaryKey	hsvmpeg__componenttaginfomain_ComparePrimaryKey
// #define componenttaginfoaux_CompareQuaternaryKey	hsvmpeg__componenttaginfomain_CompareQuaternaryKey
// #define componenttaginfoaux_CompareSecondaryKey	hsvmpeg__componenttaginfomain_CompareSecondaryKey
// #define componenttaginfoaux_CompareTeritiaryKey	hsvmpeg__componenttaginfomain_CompareTeritiaryKey

#define componenttaginfoaux_ElementSize	sizeof(HsvPMTComponentTagInfo)

#define componenttaginfoaux_Equal	((Nat8)0x1)

#define componenttaginfoaux_Equal_CONSTANT	0x1

#define componenttaginfoaux_MaxElements	((int)0x46)

#define componenttaginfoaux_MaxElements_CONSTANT	0x46

#define componenttaginfoaux_Primary	((Nat8)0x1)

#define componenttaginfoaux_Primary_CONSTANT	0x1

#define componenttaginfoaux_Quaternary	((Nat8)0x8)

#define componenttaginfoaux_Quaternary_CONSTANT	0x8

#define componenttaginfoaux_Secondary	((Nat8)0x2)

#define componenttaginfoaux_Secondary_CONSTANT	0x2

#define componenttaginfoaux_SmallerKey	((Nat8)0x0)

#define componenttaginfoaux_SmallerKey_CONSTANT	0x0

#define componenttaginfoaux_SortCriteria	((Nat8)0x3)

#define componenttaginfoaux_SortCriteria_CONSTANT	0x3

#define componenttaginfoaux_Teritiary	((Nat8)0x4)

#define componenttaginfoaux_Teritiary_CONSTANT	0x4

#define componenttaginfoaux_ThreadSafe	((Bool)0x1)

#define componenttaginfoaux_ThreadSafe_CONSTANT	0x1

/* interface componenttaginfomain : IHsvSortedTableConfigurationEx */

#define componenttaginfomain_ICONNECTED	1

#define componenttaginfomain_BiggerKey	((Nat8)0x2)

#define componenttaginfomain_BiggerKey_CONSTANT	0x2
// #define componenttaginfomain_ComparePrimaryKey	hsvmpeg__componenttaginfomain_ComparePrimaryKey
// #define componenttaginfomain_CompareQuaternaryKey	hsvmpeg__componenttaginfomain_CompareQuaternaryKey
// #define componenttaginfomain_CompareSecondaryKey	hsvmpeg__componenttaginfomain_CompareSecondaryKey
// #define componenttaginfomain_CompareTeritiaryKey	hsvmpeg__componenttaginfomain_CompareTeritiaryKey

#define componenttaginfomain_ElementSize	sizeof(HsvPMTComponentTagInfo)

#define componenttaginfomain_Equal	((Nat8)0x1)

#define componenttaginfomain_Equal_CONSTANT	0x1

#define componenttaginfomain_MaxElements	((int)0x46)

#define componenttaginfomain_MaxElements_CONSTANT	0x46

#define componenttaginfomain_Primary	((Nat8)0x1)

#define componenttaginfomain_Primary_CONSTANT	0x1

#define componenttaginfomain_Quaternary	((Nat8)0x8)

#define componenttaginfomain_Quaternary_CONSTANT	0x8

#define componenttaginfomain_Secondary	((Nat8)0x2)

#define componenttaginfomain_Secondary_CONSTANT	0x2

#define componenttaginfomain_SmallerKey	((Nat8)0x0)

#define componenttaginfomain_SmallerKey_CONSTANT	0x0

#define componenttaginfomain_SortCriteria	((Nat8)0x3)

#define componenttaginfomain_SortCriteria_CONSTANT	0x3

#define componenttaginfomain_Teritiary	((Nat8)0x4)

#define componenttaginfomain_Teritiary_CONSTANT	0x4

#define componenttaginfomain_ThreadSafe	((Bool)0x1)

#define componenttaginfomain_ThreadSafe_CONSTANT	0x1

/* interface databroadcastinfoaux : IHsvSortedTableConfigurationEx */

#define databroadcastinfoaux_ICONNECTED	1

#define databroadcastinfoaux_BiggerKey	((Nat8)0x2)

#define databroadcastinfoaux_BiggerKey_CONSTANT	0x2
// #define databroadcastinfoaux_ComparePrimaryKey	hsvmpeg__databroadcastinfomain_ComparePrimaryKey
// #define databroadcastinfoaux_CompareQuaternaryKey	hsvmpeg__databroadcastinfomain_CompareQuaternaryKey
// #define databroadcastinfoaux_CompareSecondaryKey	hsvmpeg__databroadcastinfomain_CompareSecondaryKey
// #define databroadcastinfoaux_CompareTeritiaryKey	hsvmpeg__databroadcastinfomain_CompareTeritiaryKey

#define databroadcastinfoaux_ElementSize	sizeof(HsvPMTDatabroadcastInfo)

#define databroadcastinfoaux_Equal	((Nat8)0x1)

#define databroadcastinfoaux_Equal_CONSTANT	0x1

#define databroadcastinfoaux_MaxElements	((int)0x46)

#define databroadcastinfoaux_MaxElements_CONSTANT	0x46

#define databroadcastinfoaux_Primary	((Nat8)0x1)

#define databroadcastinfoaux_Primary_CONSTANT	0x1

#define databroadcastinfoaux_Quaternary	((Nat8)0x8)

#define databroadcastinfoaux_Quaternary_CONSTANT	0x8

#define databroadcastinfoaux_Secondary	((Nat8)0x2)

#define databroadcastinfoaux_Secondary_CONSTANT	0x2

#define databroadcastinfoaux_SmallerKey	((Nat8)0x0)

#define databroadcastinfoaux_SmallerKey_CONSTANT	0x0

#define databroadcastinfoaux_SortCriteria	((Nat8)0x3)

#define databroadcastinfoaux_SortCriteria_CONSTANT	0x3

#define databroadcastinfoaux_Teritiary	((Nat8)0x4)

#define databroadcastinfoaux_Teritiary_CONSTANT	0x4

#define databroadcastinfoaux_ThreadSafe	((Bool)0x1)

#define databroadcastinfoaux_ThreadSafe_CONSTANT	0x1

/* interface databroadcastinfomain : IHsvSortedTableConfigurationEx */

#define databroadcastinfomain_ICONNECTED	1

#define databroadcastinfomain_BiggerKey	((Nat8)0x2)

#define databroadcastinfomain_BiggerKey_CONSTANT	0x2
// #define databroadcastinfomain_ComparePrimaryKey	hsvmpeg__databroadcastinfomain_ComparePrimaryKey
// #define databroadcastinfomain_CompareQuaternaryKey	hsvmpeg__databroadcastinfomain_CompareQuaternaryKey
// #define databroadcastinfomain_CompareSecondaryKey	hsvmpeg__databroadcastinfomain_CompareSecondaryKey
// #define databroadcastinfomain_CompareTeritiaryKey	hsvmpeg__databroadcastinfomain_CompareTeritiaryKey

#define databroadcastinfomain_ElementSize	sizeof(HsvPMTDatabroadcastInfo)

#define databroadcastinfomain_Equal	((Nat8)0x1)

#define databroadcastinfomain_Equal_CONSTANT	0x1

#define databroadcastinfomain_MaxElements	((int)0x46)

#define databroadcastinfomain_MaxElements_CONSTANT	0x46

#define databroadcastinfomain_Primary	((Nat8)0x1)

#define databroadcastinfomain_Primary_CONSTANT	0x1

#define databroadcastinfomain_Quaternary	((Nat8)0x8)

#define databroadcastinfomain_Quaternary_CONSTANT	0x8

#define databroadcastinfomain_Secondary	((Nat8)0x2)

#define databroadcastinfomain_Secondary_CONSTANT	0x2

#define databroadcastinfomain_SmallerKey	((Nat8)0x0)

#define databroadcastinfomain_SmallerKey_CONSTANT	0x0

#define databroadcastinfomain_SortCriteria	((Nat8)0x3)

#define databroadcastinfomain_SortCriteria_CONSTANT	0x3

#define databroadcastinfomain_Teritiary	((Nat8)0x4)

#define databroadcastinfomain_Teritiary_CONSTANT	0x4

#define databroadcastinfomain_ThreadSafe	((Bool)0x1)

#define databroadcastinfomain_ThreadSafe_CONSTANT	0x1

/* interface subtitleconfaux : IHsvSortedTableConfigurationEx */

#define subtitleconfaux_ICONNECTED	1

#define subtitleconfaux_BiggerKey	((Nat8)0x2)

#define subtitleconfaux_BiggerKey_CONSTANT	0x2
// #define subtitleconfaux_ComparePrimaryKey	hsvmpeg__subtitleconfmain_ComparePrimaryKey
// #define subtitleconfaux_CompareQuaternaryKey	hsvmpeg__subtitleconfmain_CompareQuaternaryKey
// #define subtitleconfaux_CompareSecondaryKey	hsvmpeg__subtitleconfmain_CompareSecondaryKey
// #define subtitleconfaux_CompareTeritiaryKey	hsvmpeg__subtitleconfmain_CompareTeritiaryKey

#define subtitleconfaux_ElementSize	sizeof(HsvPMTSubtitlingInfo)

#define subtitleconfaux_Equal	((Nat8)0x1)

#define subtitleconfaux_Equal_CONSTANT	0x1

#define subtitleconfaux_MaxElements	((int)0x46)

#define subtitleconfaux_MaxElements_CONSTANT	0x46

#define subtitleconfaux_Primary	((Nat8)0x1)

#define subtitleconfaux_Primary_CONSTANT	0x1

#define subtitleconfaux_Quaternary	((Nat8)0x8)

#define subtitleconfaux_Quaternary_CONSTANT	0x8

#define subtitleconfaux_Secondary	((Nat8)0x2)

#define subtitleconfaux_Secondary_CONSTANT	0x2

#define subtitleconfaux_SmallerKey	((Nat8)0x0)

#define subtitleconfaux_SmallerKey_CONSTANT	0x0

#define subtitleconfaux_SortCriteria	((Nat8)0x7)

#define subtitleconfaux_SortCriteria_CONSTANT	0x7

#define subtitleconfaux_Teritiary	((Nat8)0x4)

#define subtitleconfaux_Teritiary_CONSTANT	0x4

#define subtitleconfaux_ThreadSafe	((Bool)0x1)

#define subtitleconfaux_ThreadSafe_CONSTANT	0x1

/* interface subtitleconfmain : IHsvSortedTableConfigurationEx */

#define subtitleconfmain_ICONNECTED	1

#define subtitleconfmain_BiggerKey	((Nat8)0x2)

#define subtitleconfmain_BiggerKey_CONSTANT	0x2
// #define subtitleconfmain_ComparePrimaryKey	hsvmpeg__subtitleconfmain_ComparePrimaryKey
// #define subtitleconfmain_CompareQuaternaryKey	hsvmpeg__subtitleconfmain_CompareQuaternaryKey
// #define subtitleconfmain_CompareSecondaryKey	hsvmpeg__subtitleconfmain_CompareSecondaryKey
// #define subtitleconfmain_CompareTeritiaryKey	hsvmpeg__subtitleconfmain_CompareTeritiaryKey

#define subtitleconfmain_ElementSize	sizeof(HsvPMTSubtitlingInfo)

#define subtitleconfmain_Equal	((Nat8)0x1)

#define subtitleconfmain_Equal_CONSTANT	0x1

#define subtitleconfmain_MaxElements	((int)0x46)

#define subtitleconfmain_MaxElements_CONSTANT	0x46

#define subtitleconfmain_Primary	((Nat8)0x1)

#define subtitleconfmain_Primary_CONSTANT	0x1

#define subtitleconfmain_Quaternary	((Nat8)0x8)

#define subtitleconfmain_Quaternary_CONSTANT	0x8

#define subtitleconfmain_Secondary	((Nat8)0x2)

#define subtitleconfmain_Secondary_CONSTANT	0x2

#define subtitleconfmain_SmallerKey	((Nat8)0x0)

#define subtitleconfmain_SmallerKey_CONSTANT	0x0

#define subtitleconfmain_SortCriteria	((Nat8)0x7)

#define subtitleconfmain_SortCriteria_CONSTANT	0x7

#define subtitleconfmain_Teritiary	((Nat8)0x4)

#define subtitleconfmain_Teritiary_CONSTANT	0x4

#define subtitleconfmain_ThreadSafe	((Bool)0x1)

#define subtitleconfmain_ThreadSafe_CONSTANT	0x1

/* interface teletextconfaux : IHsvSortedTableConfigurationEx */

#define teletextconfaux_ICONNECTED	1

#define teletextconfaux_BiggerKey	((Nat8)0x2)

#define teletextconfaux_BiggerKey_CONSTANT	0x2
// #define teletextconfaux_ComparePrimaryKey	hsvmpeg__teletextconfmain_ComparePrimaryKey
// #define teletextconfaux_CompareQuaternaryKey	hsvmpeg__teletextconfmain_CompareQuaternaryKey
// #define teletextconfaux_CompareSecondaryKey	hsvmpeg__teletextconfmain_CompareSecondaryKey
// #define teletextconfaux_CompareTeritiaryKey	hsvmpeg__teletextconfmain_CompareTeritiaryKey

#define teletextconfaux_ElementSize	sizeof(HsvPMTTeletextInfo)

#define teletextconfaux_Equal	((Nat8)0x1)

#define teletextconfaux_Equal_CONSTANT	0x1

#define teletextconfaux_MaxElements	((int)0x46)

#define teletextconfaux_MaxElements_CONSTANT	0x46

#define teletextconfaux_Primary	((Nat8)0x1)

#define teletextconfaux_Primary_CONSTANT	0x1

#define teletextconfaux_Quaternary	((Nat8)0x8)

#define teletextconfaux_Quaternary_CONSTANT	0x8

#define teletextconfaux_Secondary	((Nat8)0x2)

#define teletextconfaux_Secondary_CONSTANT	0x2

#define teletextconfaux_SmallerKey	((Nat8)0x0)

#define teletextconfaux_SmallerKey_CONSTANT	0x0

#define teletextconfaux_SortCriteria	((Nat8)0x7)

#define teletextconfaux_SortCriteria_CONSTANT	0x7

#define teletextconfaux_Teritiary	((Nat8)0x4)

#define teletextconfaux_Teritiary_CONSTANT	0x4

#define teletextconfaux_ThreadSafe	((Bool)0x1)

#define teletextconfaux_ThreadSafe_CONSTANT	0x1

/* interface teletextconfmain : IHsvSortedTableConfigurationEx */

#define teletextconfmain_ICONNECTED	1

#define teletextconfmain_BiggerKey	((Nat8)0x2)

#define teletextconfmain_BiggerKey_CONSTANT	0x2
// #define teletextconfmain_ComparePrimaryKey	hsvmpeg__teletextconfmain_ComparePrimaryKey
// #define teletextconfmain_CompareQuaternaryKey	hsvmpeg__teletextconfmain_CompareQuaternaryKey
// #define teletextconfmain_CompareSecondaryKey	hsvmpeg__teletextconfmain_CompareSecondaryKey
// #define teletextconfmain_CompareTeritiaryKey	hsvmpeg__teletextconfmain_CompareTeritiaryKey

#define teletextconfmain_ElementSize	sizeof(HsvPMTTeletextInfo)

#define teletextconfmain_Equal	((Nat8)0x1)

#define teletextconfmain_Equal_CONSTANT	0x1

#define teletextconfmain_MaxElements	((int)0x46)

#define teletextconfmain_MaxElements_CONSTANT	0x46

#define teletextconfmain_Primary	((Nat8)0x1)

#define teletextconfmain_Primary_CONSTANT	0x1

#define teletextconfmain_Quaternary	((Nat8)0x8)

#define teletextconfmain_Quaternary_CONSTANT	0x8

#define teletextconfmain_Secondary	((Nat8)0x2)

#define teletextconfmain_Secondary_CONSTANT	0x2

#define teletextconfmain_SmallerKey	((Nat8)0x0)

#define teletextconfmain_SmallerKey_CONSTANT	0x0

#define teletextconfmain_SortCriteria	((Nat8)0x7)

#define teletextconfmain_SortCriteria_CONSTANT	0x7

#define teletextconfmain_Teritiary	((Nat8)0x4)

#define teletextconfmain_Teritiary_CONSTANT	0x4

#define teletextconfmain_ThreadSafe	((Bool)0x1)

#define teletextconfmain_ThreadSafe_CONSTANT	0x1

#endif
/*****************************************************************************/

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)


/********************************************************/
/* Forward declarations  */
/********************************************************/

#define NOCLASS

#if 0

#endif
/*******************************************************************************/

/**
 **  Function to start section filter for current program PMT ONLY
 */

#if 0

#endif

#if 0

#endif
/*************************IHsvStream Implementation *******************************/
/************************ PATSTRAPI************************************************/

#if 0
/***********************************************************/

#endif
/***********************************************************/

#if 0

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#include"_hsvmpeg_m.h"

#include<hsvmpeg_errorids.h>

#include<pat_Parser.h>

#include<pmt_Parser.h>

#ifdef WIN32

#else

#endif

HsvTSData ProgramData[HsvDmxLast];
static HsvTSData s__ProgramData[HsvDmxLast];
Nat16 CurrentProgramNo[HsvDmxLast];
static Nat16 s__CurrentProgramNo[HsvDmxLast];
Semaphore SubscriptionSem[HsvDmxLast];
static Semaphore s__SubscriptionSem[HsvDmxLast];
Pump mMpegPump;
static Pump s__mMpegPump;
Pump mMonitorProgramPmp;
static Pump s__mMonitorProgramPmp;
Nat16 teletextPID;
static Nat16 s__teletextPID;
#if 0
/** Within clauses added here */
//#define langids_MaxNumberOfLanguages	((int)0x2E)

#endif
/*****************************************************************************/

#ifndef __cplusplus

#else

#endif

Nat8 pat_mBuffer[4*1024];
static Nat8 s__pat_mBuffer[4*1024];
Bool pat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
Nat8 pmt_mBuffer[4*1024];
static Nat8 s__pmt_mBuffer[4*1024];
Bool pmt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
#if 0

#endif
/*******************************************************************************/

/**
 **  Function to start section filter for current program PMT ONLY
 */

void StartProgramfilters(HsvDemux dmx);
Bool populateProgramVideoInfo(HsvDemux dmx, Typepmt_Parser *pmt,
        int esLoop);
Bool populateStreamIDInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop);
Bool populateTXTInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop);
Bool populateSUBTInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop);
Bool IsPremixedAudioType(Nat32 AudLang, Nat8 AudType);
Bool popISOAudioLang(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo);
Bool popAC3PlusAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo);
Bool popAC3AudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo);
Bool popAACAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo);
Bool popSupplementaryAudioInfo(Typepmt_Parser *pmt, int esLoop,
        HsvPMTAudioInfo *audioInfo);
Bool populateAudioInfo(HsvDemux dmx, Typepmt_Parser *pmt, int esLoop);
Bool pop_PopulatePMT(HsvDemux dmx, Address PMTTable, int code);
Bool pop_PopulatePAT(HsvDemux dmx, Address PATTable, int code);
void StartSubscriptions(HsvDemux dmx);
void StopSubscriptions(HsvDemux dmx);
#if 0

void LogError(int Priority, int ErrorId);
#endif

void SubscribeForProgram(HsvDemux dmx, int prg, int pid, int index);
void ClearPmtSectionData(HsvDemux dmx);
#if 0

#endif
/*************************IHsvStream Implementation *******************************/
/************************ PATSTRAPI************************************************/

void ClearPropertyTables(HsvDemux dmx);
void NotifyComponent(HsvDemux dmx, Nat8 property, void * addr);
#if 0
/***********************************************************/

void DeleteRecord(HsvDemux dmx, Nat8 property, void * addr);
#endif
/***********************************************************/

void FreeDataBaseObjects(HsvDemux dmx, int prg);
Nat8 GetLanguageId(Nat32 Language);
#if 0

Bool CompareBpidInfo(HsvPMTBasicPidInfo * comp1,
        HsvPMTBasicPidInfo * comp2);
#endif

Bool CompareTxtInfo(HsvPMTTeletextInfo * comp1,
        HsvPMTTeletextInfo * comp2);
Bool CompareSbtlInfo(HsvPMTSubtitlingInfo * comp1,
        HsvPMTSubtitlingInfo * comp2);
Bool CompareCompTagInfo(HsvPMTComponentTagInfo * comp1,
        HsvPMTComponentTagInfo * comp2);
Bool CompareAudioInfo(HsvPMTAudioInfo * comp1, HsvPMTAudioInfo * comp2);
void mMpegPumpHandler(int dmx, Nat32 index);
void mMonitorProgramPmpHandler(int param1, Nat32 param2);
void module__init(void){
#include"_hsvmpeg_m.h"

#include<hsvmpeg_errorids.h>

#include<pat_Parser.h>

#include<pmt_Parser.h>

#ifdef WIN32

#else

#endif

	memcpy((void*)ProgramData,(void*)s__ProgramData,sizeof(ProgramData));
	memcpy((void*)CurrentProgramNo,(void*)s__CurrentProgramNo,sizeof(CurrentProgramNo));
	memcpy((void*)SubscriptionSem,(void*)s__SubscriptionSem,sizeof(SubscriptionSem));
	mMpegPump	=	s__mMpegPump;
	mMonitorProgramPmp	=	s__mMonitorProgramPmp;
	teletextPID	=	s__teletextPID;
#if 0
/** Within clauses added here */
//#define langids_MaxNumberOfLanguages	((int)0x2E)

#endif
/*****************************************************************************/

#ifndef __cplusplus

#else

#endif

	memcpy((void*)pat_mBuffer,(void*)s__pat_mBuffer,sizeof(pat_mBuffer));
	memcpy((void*)pmt_mBuffer,(void*)s__pmt_mBuffer,sizeof(pmt_mBuffer));
#if 0

#endif
/*******************************************************************************/

/**
 **  Function to start section filter for current program PMT ONLY
 */

#if 0

#endif

#if 0

#endif
/*************************IHsvStream Implementation *******************************/
/************************ PATSTRAPI************************************************/

#if 0
/***********************************************************/

#endif
/***********************************************************/

#if 0

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef pen_PumpEngine
#undef pen_PumpEngine
#endif //pen_PumpEngine
#ifdef strapiN_iPresent()
#undef strapiN_iPresent()
#endif //strapiN_iPresent()
#ifdef PAT_TABLE_ID_VALUE
#undef PAT_TABLE_ID_VALUE
#endif //PAT_TABLE_ID_VALUE
#ifdef PAT_PID_VALUE
#undef PAT_PID_VALUE
#endif //PAT_PID_VALUE
#ifdef TS_PROGRAM_MAP_SECTION_TABLE_ID
#undef TS_PROGRAM_MAP_SECTION_TABLE_ID
#endif //TS_PROGRAM_MAP_SECTION_TABLE_ID
#ifdef PROGRAM_MAP_PID_CHANGE
#undef PROGRAM_MAP_PID_CHANGE
#endif //PROGRAM_MAP_PID_CHANGE
#ifdef PROGRAM_NUMBER_FOR_NETWORK_PID
#undef PROGRAM_NUMBER_FOR_NETWORK_PID
#endif //PROGRAM_NUMBER_FOR_NETWORK_PID
#ifdef INVALID_PID
#undef INVALID_PID
#endif //INVALID_PID
#ifdef HSV_INVALID_KEY
#undef HSV_INVALID_KEY
#endif //HSV_INVALID_KEY
#ifdef RETRY_REQUEST
#undef RETRY_REQUEST
#endif //RETRY_REQUEST
#ifdef MAX_PROGRAM_INFO_LENGTH
#undef MAX_PROGRAM_INFO_LENGTH
#endif //MAX_PROGRAM_INFO_LENGTH
#ifdef MAX_PMT_SECTION_SIZE
#undef MAX_PMT_SECTION_SIZE
#endif //MAX_PMT_SECTION_SIZE
#ifdef MAX_ES_INFO_LENGTH
#undef MAX_ES_INFO_LENGTH
#endif //MAX_ES_INFO_LENGTH
#ifdef MAX_PMT_SECTION_LENGTH
#undef MAX_PMT_SECTION_LENGTH
#endif //MAX_PMT_SECTION_LENGTH
#ifdef MAX_PROGRAM_ELEMENTS
#undef MAX_PROGRAM_ELEMENTS
#endif //MAX_PROGRAM_ELEMENTS
#ifdef MAX_PMT_MONITORS
#undef MAX_PMT_MONITORS
#endif //MAX_PMT_MONITORS
#ifdef CURRENT_PROGRAM_INDEX
#undef CURRENT_PROGRAM_INDEX
#endif //CURRENT_PROGRAM_INDEX
#ifdef MAX_DESCRIPTORS_IN_PROGRAM_ELEMENT
#undef MAX_DESCRIPTORS_IN_PROGRAM_ELEMENT
#endif //MAX_DESCRIPTORS_IN_PROGRAM_ELEMENT
#ifdef PROGRAM_ACQUIRED
#undef PROGRAM_ACQUIRED
#endif //PROGRAM_ACQUIRED
#ifdef PROGRAM_NOT_ACQUIRED
#undef PROGRAM_NOT_ACQUIRED
#endif //PROGRAM_NOT_ACQUIRED
#ifdef INVALID_PROGRAM_NUMBER
#undef INVALID_PROGRAM_NUMBER
#endif //INVALID_PROGRAM_NUMBER
#ifdef INVALID_PROGRAM_MAP_PID
#undef INVALID_PROGRAM_MAP_PID
#endif //INVALID_PROGRAM_MAP_PID
#ifdef INVALID_ELEMENTARY_PID
#undef INVALID_ELEMENTARY_PID
#endif //INVALID_ELEMENTARY_PID
#ifdef PROGRAM_ELEMENT_HEADER_LENGTH
#undef PROGRAM_ELEMENT_HEADER_LENGTH
#endif //PROGRAM_ELEMENT_HEADER_LENGTH
#ifdef HSV_CLEAN_EFFECTS_TYPE
#undef HSV_CLEAN_EFFECTS_TYPE
#endif //HSV_CLEAN_EFFECTS_TYPE
#ifdef HSV_LOWEST_BYTE(a)
#undef HSV_LOWEST_BYTE(a)
#endif //HSV_LOWEST_BYTE(a)
#ifdef HSV_SECOND_LOWEST_BYTE(a)
#undef HSV_SECOND_LOWEST_BYTE(a)
#endif //HSV_SECOND_LOWEST_BYTE(a)
#ifdef HSV_MAKE_CHAR_MASK(a,b,c)
#undef HSV_MAKE_CHAR_MASK(a,b,c)
#endif //HSV_MAKE_CHAR_MASK(a,b,c)
#ifdef MAX_POSSIBLE_PMT_VIDEO_PIDS
#undef MAX_POSSIBLE_PMT_VIDEO_PIDS
#endif //MAX_POSSIBLE_PMT_VIDEO_PIDS
#ifdef PMT_TABLE_ARRAY_INDEX_VALUE
#undef PMT_TABLE_ARRAY_INDEX_VALUE
#endif //PMT_TABLE_ARRAY_INDEX_VALUE
#ifdef VIDEO_STREAM_DESCRIPTOR_TAG
#undef VIDEO_STREAM_DESCRIPTOR_TAG
#endif //VIDEO_STREAM_DESCRIPTOR_TAG
#ifdef AUDIO_STREAM_DESCRIPTOR_TAG
#undef AUDIO_STREAM_DESCRIPTOR_TAG
#endif //AUDIO_STREAM_DESCRIPTOR_TAG
#ifdef MPEG4_VIDEO_STREAM_DESCRIPTOR_TAG
#undef MPEG4_VIDEO_STREAM_DESCRIPTOR_TAG
#endif //MPEG4_VIDEO_STREAM_DESCRIPTOR_TAG
#ifdef CONTENT_ADVISORY_DESCRIPTOR_TAG
#undef CONTENT_ADVISORY_DESCRIPTOR_TAG
#endif //CONTENT_ADVISORY_DESCRIPTOR_TAG
#ifdef AC3_AUDIO_STREAM_DESCRIPTOR_TAG
#undef AC3_AUDIO_STREAM_DESCRIPTOR_TAG
#endif //AC3_AUDIO_STREAM_DESCRIPTOR_TAG
#ifdef CAPTION_SERVICE_DESCRIPTOR_TAG
#undef CAPTION_SERVICE_DESCRIPTOR_TAG
#endif //CAPTION_SERVICE_DESCRIPTOR_TAG
#ifdef ISO639_LANGUAGE_DESCRIPTOR_TAG
#undef ISO639_LANGUAGE_DESCRIPTOR_TAG
#endif //ISO639_LANGUAGE_DESCRIPTOR_TAG
#ifdef ISO_IEC_11172_VIDEO_STREAM_TYPE
#undef ISO_IEC_11172_VIDEO_STREAM_TYPE
#endif //ISO_IEC_11172_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#undef ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#endif //ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#undef ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#endif //ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_13818_6_STREAM_TYPE_B
#undef ISO_IEC_13818_6_STREAM_TYPE_B
#endif //ISO_IEC_13818_6_STREAM_TYPE_B
#ifdef ISO_IEC_11172_AUDIO_STREAM_TYPE
#undef ISO_IEC_11172_AUDIO_STREAM_TYPE
#endif //ISO_IEC_11172_AUDIO_STREAM_TYPE
#ifdef ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#undef ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#endif //ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#ifdef ATSC_A52_AC3_STREAM_TYPE
#undef ATSC_A52_AC3_STREAM_TYPE
#endif //ATSC_A52_AC3_STREAM_TYPE
#ifdef MPEG4_HEAAC_STREAM_TYPE
#undef MPEG4_HEAAC_STREAM_TYPE
#endif //MPEG4_HEAAC_STREAM_TYPE
#ifdef MPEG4_AAC_STREAM_TYPE
#undef MPEG4_AAC_STREAM_TYPE
#endif //MPEG4_AAC_STREAM_TYPE
#ifdef MPEG4_AC3PLUS_STREAM_TYPE
#undef MPEG4_AC3PLUS_STREAM_TYPE
#endif //MPEG4_AC3PLUS_STREAM_TYPE
#ifdef MAX_POSSIBLE_PROGRAMS
#undef MAX_POSSIBLE_PROGRAMS
#endif //MAX_POSSIBLE_PROGRAMS
#ifdef ISO_IEC_13818_1_PRIVATE_STREAM_TYPE
#undef ISO_IEC_13818_1_PRIVATE_STREAM_TYPE
#endif //ISO_IEC_13818_1_PRIVATE_STREAM_TYPE
#ifdef H264_VIDEO_STREAM_TYPE
#undef H264_VIDEO_STREAM_TYPE
#endif //H264_VIDEO_STREAM_TYPE
#ifdef TELETEXT_TABLE_ID(dmx)
#undef TELETEXT_TABLE_ID(dmx)
#endif //TELETEXT_TABLE_ID(dmx)
#ifdef VBI_TELETEXT_TABLE_ID(dmx)
#undef VBI_TELETEXT_TABLE_ID(dmx)
#endif //VBI_TELETEXT_TABLE_ID(dmx)
#ifdef SUBTITLE_TABLE_ID(dmx)
#undef SUBTITLE_TABLE_ID(dmx)
#endif //SUBTITLE_TABLE_ID(dmx)
#ifdef BASIC_PID_TABLE_ID(dmx)
#undef BASIC_PID_TABLE_ID(dmx)
#endif //BASIC_PID_TABLE_ID(dmx)
#ifdef AUDIOINFO_TABLE_ID(dmx)
#undef AUDIOINFO_TABLE_ID(dmx)
#endif //AUDIOINFO_TABLE_ID(dmx)
#ifdef COMPONENT_TAG_TABLE_ID(dmx)
#undef COMPONENT_TAG_TABLE_ID(dmx)
#endif //COMPONENT_TAG_TABLE_ID(dmx)
#ifdef DATABROADCAST_TAG_TABLE_ID(dmx)
#undef DATABROADCAST_TAG_TABLE_ID(dmx)
#endif //DATABROADCAST_TAG_TABLE_ID(dmx)
#ifdef DescLoops(name)
#undef DescLoops(name)
#endif //DescLoops(name)
#ifdef NOADSTREAM
#undef NOADSTREAM
#endif //NOADSTREAM
#ifdef SUB_STREAM1
#undef SUB_STREAM1
#endif //SUB_STREAM1
#ifdef SUB_STREAM2
#undef SUB_STREAM2
#endif //SUB_STREAM2
#ifdef SUB_STREAM3
#undef SUB_STREAM3
#endif //SUB_STREAM3
#ifdef LOOP0
#undef LOOP0
#endif //LOOP0
#ifdef LOOP1
#undef LOOP1
#endif //LOOP1
#ifdef TABLE_ID_EXTN_FIELD
#undef TABLE_ID_EXTN_FIELD
#endif //TABLE_ID_EXTN_FIELD
#ifdef TABLE_ID_EXTN_FIELD
#undef TABLE_ID_EXTN_FIELD
#endif //TABLE_ID_EXTN_FIELD
#ifdef TABLEID_MASK
#undef TABLEID_MASK
#endif //TABLEID_MASK
#ifdef langids_MaxNumberOfLanguages_CONSTANT
#undef langids_MaxNumberOfLanguages_CONSTANT
#endif //langids_MaxNumberOfLanguages_CONSTANT
#ifdef audioinfoconfaux_ICONNECTED
#undef audioinfoconfaux_ICONNECTED
#endif //audioinfoconfaux_ICONNECTED
#ifdef audioinfoconfaux_BiggerKey
#undef audioinfoconfaux_BiggerKey
#endif //audioinfoconfaux_BiggerKey
#ifdef audioinfoconfaux_BiggerKey_CONSTANT
#undef audioinfoconfaux_BiggerKey_CONSTANT
#endif //audioinfoconfaux_BiggerKey_CONSTANT
#ifdef audioinfoconfaux_ElementSize
#undef audioinfoconfaux_ElementSize
#endif //audioinfoconfaux_ElementSize
#ifdef audioinfoconfaux_Equal
#undef audioinfoconfaux_Equal
#endif //audioinfoconfaux_Equal
#ifdef audioinfoconfaux_Equal_CONSTANT
#undef audioinfoconfaux_Equal_CONSTANT
#endif //audioinfoconfaux_Equal_CONSTANT
#ifdef audioinfoconfaux_MaxElements
#undef audioinfoconfaux_MaxElements
#endif //audioinfoconfaux_MaxElements
#ifdef audioinfoconfaux_MaxElements_CONSTANT
#undef audioinfoconfaux_MaxElements_CONSTANT
#endif //audioinfoconfaux_MaxElements_CONSTANT
#ifdef audioinfoconfaux_Primary
#undef audioinfoconfaux_Primary
#endif //audioinfoconfaux_Primary
#ifdef audioinfoconfaux_Primary_CONSTANT
#undef audioinfoconfaux_Primary_CONSTANT
#endif //audioinfoconfaux_Primary_CONSTANT
#ifdef audioinfoconfaux_Quaternary
#undef audioinfoconfaux_Quaternary
#endif //audioinfoconfaux_Quaternary
#ifdef audioinfoconfaux_Quaternary_CONSTANT
#undef audioinfoconfaux_Quaternary_CONSTANT
#endif //audioinfoconfaux_Quaternary_CONSTANT
#ifdef audioinfoconfaux_Secondary
#undef audioinfoconfaux_Secondary
#endif //audioinfoconfaux_Secondary
#ifdef audioinfoconfaux_Secondary_CONSTANT
#undef audioinfoconfaux_Secondary_CONSTANT
#endif //audioinfoconfaux_Secondary_CONSTANT
#ifdef audioinfoconfaux_SmallerKey
#undef audioinfoconfaux_SmallerKey
#endif //audioinfoconfaux_SmallerKey
#ifdef audioinfoconfaux_SmallerKey_CONSTANT
#undef audioinfoconfaux_SmallerKey_CONSTANT
#endif //audioinfoconfaux_SmallerKey_CONSTANT
#ifdef audioinfoconfaux_SortCriteria
#undef audioinfoconfaux_SortCriteria
#endif //audioinfoconfaux_SortCriteria
#ifdef audioinfoconfaux_SortCriteria_CONSTANT
#undef audioinfoconfaux_SortCriteria_CONSTANT
#endif //audioinfoconfaux_SortCriteria_CONSTANT
#ifdef audioinfoconfaux_Teritiary
#undef audioinfoconfaux_Teritiary
#endif //audioinfoconfaux_Teritiary
#ifdef audioinfoconfaux_Teritiary_CONSTANT
#undef audioinfoconfaux_Teritiary_CONSTANT
#endif //audioinfoconfaux_Teritiary_CONSTANT
#ifdef audioinfoconfaux_ThreadSafe
#undef audioinfoconfaux_ThreadSafe
#endif //audioinfoconfaux_ThreadSafe
#ifdef audioinfoconfaux_ThreadSafe_CONSTANT
#undef audioinfoconfaux_ThreadSafe_CONSTANT
#endif //audioinfoconfaux_ThreadSafe_CONSTANT
#ifdef audioinfoconfmain_ICONNECTED
#undef audioinfoconfmain_ICONNECTED
#endif //audioinfoconfmain_ICONNECTED
#ifdef audioinfoconfmain_BiggerKey
#undef audioinfoconfmain_BiggerKey
#endif //audioinfoconfmain_BiggerKey
#ifdef audioinfoconfmain_BiggerKey_CONSTANT
#undef audioinfoconfmain_BiggerKey_CONSTANT
#endif //audioinfoconfmain_BiggerKey_CONSTANT
#ifdef audioinfoconfmain_ElementSize
#undef audioinfoconfmain_ElementSize
#endif //audioinfoconfmain_ElementSize
#ifdef audioinfoconfmain_Equal
#undef audioinfoconfmain_Equal
#endif //audioinfoconfmain_Equal
#ifdef audioinfoconfmain_Equal_CONSTANT
#undef audioinfoconfmain_Equal_CONSTANT
#endif //audioinfoconfmain_Equal_CONSTANT
#ifdef audioinfoconfmain_MaxElements
#undef audioinfoconfmain_MaxElements
#endif //audioinfoconfmain_MaxElements
#ifdef audioinfoconfmain_MaxElements_CONSTANT
#undef audioinfoconfmain_MaxElements_CONSTANT
#endif //audioinfoconfmain_MaxElements_CONSTANT
#ifdef audioinfoconfmain_Primary
#undef audioinfoconfmain_Primary
#endif //audioinfoconfmain_Primary
#ifdef audioinfoconfmain_Primary_CONSTANT
#undef audioinfoconfmain_Primary_CONSTANT
#endif //audioinfoconfmain_Primary_CONSTANT
#ifdef audioinfoconfmain_Quaternary
#undef audioinfoconfmain_Quaternary
#endif //audioinfoconfmain_Quaternary
#ifdef audioinfoconfmain_Quaternary_CONSTANT
#undef audioinfoconfmain_Quaternary_CONSTANT
#endif //audioinfoconfmain_Quaternary_CONSTANT
#ifdef audioinfoconfmain_Secondary
#undef audioinfoconfmain_Secondary
#endif //audioinfoconfmain_Secondary
#ifdef audioinfoconfmain_Secondary_CONSTANT
#undef audioinfoconfmain_Secondary_CONSTANT
#endif //audioinfoconfmain_Secondary_CONSTANT
#ifdef audioinfoconfmain_SmallerKey
#undef audioinfoconfmain_SmallerKey
#endif //audioinfoconfmain_SmallerKey
#ifdef audioinfoconfmain_SmallerKey_CONSTANT
#undef audioinfoconfmain_SmallerKey_CONSTANT
#endif //audioinfoconfmain_SmallerKey_CONSTANT
#ifdef audioinfoconfmain_SortCriteria
#undef audioinfoconfmain_SortCriteria
#endif //audioinfoconfmain_SortCriteria
#ifdef audioinfoconfmain_SortCriteria_CONSTANT
#undef audioinfoconfmain_SortCriteria_CONSTANT
#endif //audioinfoconfmain_SortCriteria_CONSTANT
#ifdef audioinfoconfmain_Teritiary
#undef audioinfoconfmain_Teritiary
#endif //audioinfoconfmain_Teritiary
#ifdef audioinfoconfmain_Teritiary_CONSTANT
#undef audioinfoconfmain_Teritiary_CONSTANT
#endif //audioinfoconfmain_Teritiary_CONSTANT
#ifdef audioinfoconfmain_ThreadSafe
#undef audioinfoconfmain_ThreadSafe
#endif //audioinfoconfmain_ThreadSafe
#ifdef audioinfoconfmain_ThreadSafe_CONSTANT
#undef audioinfoconfmain_ThreadSafe_CONSTANT
#endif //audioinfoconfmain_ThreadSafe_CONSTANT
#ifdef basicpidinfoconfaux_ICONNECTED
#undef basicpidinfoconfaux_ICONNECTED
#endif //basicpidinfoconfaux_ICONNECTED
#ifdef basicpidinfoconfaux_BiggerKey
#undef basicpidinfoconfaux_BiggerKey
#endif //basicpidinfoconfaux_BiggerKey
#ifdef basicpidinfoconfaux_BiggerKey_CONSTANT
#undef basicpidinfoconfaux_BiggerKey_CONSTANT
#endif //basicpidinfoconfaux_BiggerKey_CONSTANT
#ifdef basicpidinfoconfaux_ElementSize
#undef basicpidinfoconfaux_ElementSize
#endif //basicpidinfoconfaux_ElementSize
#ifdef basicpidinfoconfaux_Equal
#undef basicpidinfoconfaux_Equal
#endif //basicpidinfoconfaux_Equal
#ifdef basicpidinfoconfaux_Equal_CONSTANT
#undef basicpidinfoconfaux_Equal_CONSTANT
#endif //basicpidinfoconfaux_Equal_CONSTANT
#ifdef basicpidinfoconfaux_MaxElements
#undef basicpidinfoconfaux_MaxElements
#endif //basicpidinfoconfaux_MaxElements
#ifdef basicpidinfoconfaux_MaxElements_CONSTANT
#undef basicpidinfoconfaux_MaxElements_CONSTANT
#endif //basicpidinfoconfaux_MaxElements_CONSTANT
#ifdef basicpidinfoconfaux_Primary
#undef basicpidinfoconfaux_Primary
#endif //basicpidinfoconfaux_Primary
#ifdef basicpidinfoconfaux_Primary_CONSTANT
#undef basicpidinfoconfaux_Primary_CONSTANT
#endif //basicpidinfoconfaux_Primary_CONSTANT
#ifdef basicpidinfoconfaux_Quaternary
#undef basicpidinfoconfaux_Quaternary
#endif //basicpidinfoconfaux_Quaternary
#ifdef basicpidinfoconfaux_Quaternary_CONSTANT
#undef basicpidinfoconfaux_Quaternary_CONSTANT
#endif //basicpidinfoconfaux_Quaternary_CONSTANT
#ifdef basicpidinfoconfaux_Secondary
#undef basicpidinfoconfaux_Secondary
#endif //basicpidinfoconfaux_Secondary
#ifdef basicpidinfoconfaux_Secondary_CONSTANT
#undef basicpidinfoconfaux_Secondary_CONSTANT
#endif //basicpidinfoconfaux_Secondary_CONSTANT
#ifdef basicpidinfoconfaux_SmallerKey
#undef basicpidinfoconfaux_SmallerKey
#endif //basicpidinfoconfaux_SmallerKey
#ifdef basicpidinfoconfaux_SmallerKey_CONSTANT
#undef basicpidinfoconfaux_SmallerKey_CONSTANT
#endif //basicpidinfoconfaux_SmallerKey_CONSTANT
#ifdef basicpidinfoconfaux_SortCriteria
#undef basicpidinfoconfaux_SortCriteria
#endif //basicpidinfoconfaux_SortCriteria
#ifdef basicpidinfoconfaux_SortCriteria_CONSTANT
#undef basicpidinfoconfaux_SortCriteria_CONSTANT
#endif //basicpidinfoconfaux_SortCriteria_CONSTANT
#ifdef basicpidinfoconfaux_Teritiary
#undef basicpidinfoconfaux_Teritiary
#endif //basicpidinfoconfaux_Teritiary
#ifdef basicpidinfoconfaux_Teritiary_CONSTANT
#undef basicpidinfoconfaux_Teritiary_CONSTANT
#endif //basicpidinfoconfaux_Teritiary_CONSTANT
#ifdef basicpidinfoconfaux_ThreadSafe
#undef basicpidinfoconfaux_ThreadSafe
#endif //basicpidinfoconfaux_ThreadSafe
#ifdef basicpidinfoconfaux_ThreadSafe_CONSTANT
#undef basicpidinfoconfaux_ThreadSafe_CONSTANT
#endif //basicpidinfoconfaux_ThreadSafe_CONSTANT
#ifdef basicpidinfoconfmain_ICONNECTED
#undef basicpidinfoconfmain_ICONNECTED
#endif //basicpidinfoconfmain_ICONNECTED
#ifdef basicpidinfoconfmain_BiggerKey
#undef basicpidinfoconfmain_BiggerKey
#endif //basicpidinfoconfmain_BiggerKey
#ifdef basicpidinfoconfmain_BiggerKey_CONSTANT
#undef basicpidinfoconfmain_BiggerKey_CONSTANT
#endif //basicpidinfoconfmain_BiggerKey_CONSTANT
#ifdef basicpidinfoconfmain_ElementSize
#undef basicpidinfoconfmain_ElementSize
#endif //basicpidinfoconfmain_ElementSize
#ifdef basicpidinfoconfmain_Equal
#undef basicpidinfoconfmain_Equal
#endif //basicpidinfoconfmain_Equal
#ifdef basicpidinfoconfmain_Equal_CONSTANT
#undef basicpidinfoconfmain_Equal_CONSTANT
#endif //basicpidinfoconfmain_Equal_CONSTANT
#ifdef basicpidinfoconfmain_MaxElements
#undef basicpidinfoconfmain_MaxElements
#endif //basicpidinfoconfmain_MaxElements
#ifdef basicpidinfoconfmain_MaxElements_CONSTANT
#undef basicpidinfoconfmain_MaxElements_CONSTANT
#endif //basicpidinfoconfmain_MaxElements_CONSTANT
#ifdef basicpidinfoconfmain_Primary
#undef basicpidinfoconfmain_Primary
#endif //basicpidinfoconfmain_Primary
#ifdef basicpidinfoconfmain_Primary_CONSTANT
#undef basicpidinfoconfmain_Primary_CONSTANT
#endif //basicpidinfoconfmain_Primary_CONSTANT
#ifdef basicpidinfoconfmain_Quaternary
#undef basicpidinfoconfmain_Quaternary
#endif //basicpidinfoconfmain_Quaternary
#ifdef basicpidinfoconfmain_Quaternary_CONSTANT
#undef basicpidinfoconfmain_Quaternary_CONSTANT
#endif //basicpidinfoconfmain_Quaternary_CONSTANT
#ifdef basicpidinfoconfmain_Secondary
#undef basicpidinfoconfmain_Secondary
#endif //basicpidinfoconfmain_Secondary
#ifdef basicpidinfoconfmain_Secondary_CONSTANT
#undef basicpidinfoconfmain_Secondary_CONSTANT
#endif //basicpidinfoconfmain_Secondary_CONSTANT
#ifdef basicpidinfoconfmain_SmallerKey
#undef basicpidinfoconfmain_SmallerKey
#endif //basicpidinfoconfmain_SmallerKey
#ifdef basicpidinfoconfmain_SmallerKey_CONSTANT
#undef basicpidinfoconfmain_SmallerKey_CONSTANT
#endif //basicpidinfoconfmain_SmallerKey_CONSTANT
#ifdef basicpidinfoconfmain_SortCriteria
#undef basicpidinfoconfmain_SortCriteria
#endif //basicpidinfoconfmain_SortCriteria
#ifdef basicpidinfoconfmain_SortCriteria_CONSTANT
#undef basicpidinfoconfmain_SortCriteria_CONSTANT
#endif //basicpidinfoconfmain_SortCriteria_CONSTANT
#ifdef basicpidinfoconfmain_Teritiary
#undef basicpidinfoconfmain_Teritiary
#endif //basicpidinfoconfmain_Teritiary
#ifdef basicpidinfoconfmain_Teritiary_CONSTANT
#undef basicpidinfoconfmain_Teritiary_CONSTANT
#endif //basicpidinfoconfmain_Teritiary_CONSTANT
#ifdef basicpidinfoconfmain_ThreadSafe
#undef basicpidinfoconfmain_ThreadSafe
#endif //basicpidinfoconfmain_ThreadSafe
#ifdef basicpidinfoconfmain_ThreadSafe_CONSTANT
#undef basicpidinfoconfmain_ThreadSafe_CONSTANT
#endif //basicpidinfoconfmain_ThreadSafe_CONSTANT
#ifdef componenttaginfoaux_ICONNECTED
#undef componenttaginfoaux_ICONNECTED
#endif //componenttaginfoaux_ICONNECTED
#ifdef componenttaginfoaux_BiggerKey
#undef componenttaginfoaux_BiggerKey
#endif //componenttaginfoaux_BiggerKey
#ifdef componenttaginfoaux_BiggerKey_CONSTANT
#undef componenttaginfoaux_BiggerKey_CONSTANT
#endif //componenttaginfoaux_BiggerKey_CONSTANT
#ifdef componenttaginfoaux_ElementSize
#undef componenttaginfoaux_ElementSize
#endif //componenttaginfoaux_ElementSize
#ifdef componenttaginfoaux_Equal
#undef componenttaginfoaux_Equal
#endif //componenttaginfoaux_Equal
#ifdef componenttaginfoaux_Equal_CONSTANT
#undef componenttaginfoaux_Equal_CONSTANT
#endif //componenttaginfoaux_Equal_CONSTANT
#ifdef componenttaginfoaux_MaxElements
#undef componenttaginfoaux_MaxElements
#endif //componenttaginfoaux_MaxElements
#ifdef componenttaginfoaux_MaxElements_CONSTANT
#undef componenttaginfoaux_MaxElements_CONSTANT
#endif //componenttaginfoaux_MaxElements_CONSTANT
#ifdef componenttaginfoaux_Primary
#undef componenttaginfoaux_Primary
#endif //componenttaginfoaux_Primary
#ifdef componenttaginfoaux_Primary_CONSTANT
#undef componenttaginfoaux_Primary_CONSTANT
#endif //componenttaginfoaux_Primary_CONSTANT
#ifdef componenttaginfoaux_Quaternary
#undef componenttaginfoaux_Quaternary
#endif //componenttaginfoaux_Quaternary
#ifdef componenttaginfoaux_Quaternary_CONSTANT
#undef componenttaginfoaux_Quaternary_CONSTANT
#endif //componenttaginfoaux_Quaternary_CONSTANT
#ifdef componenttaginfoaux_Secondary
#undef componenttaginfoaux_Secondary
#endif //componenttaginfoaux_Secondary
#ifdef componenttaginfoaux_Secondary_CONSTANT
#undef componenttaginfoaux_Secondary_CONSTANT
#endif //componenttaginfoaux_Secondary_CONSTANT
#ifdef componenttaginfoaux_SmallerKey
#undef componenttaginfoaux_SmallerKey
#endif //componenttaginfoaux_SmallerKey
#ifdef componenttaginfoaux_SmallerKey_CONSTANT
#undef componenttaginfoaux_SmallerKey_CONSTANT
#endif //componenttaginfoaux_SmallerKey_CONSTANT
#ifdef componenttaginfoaux_SortCriteria
#undef componenttaginfoaux_SortCriteria
#endif //componenttaginfoaux_SortCriteria
#ifdef componenttaginfoaux_SortCriteria_CONSTANT
#undef componenttaginfoaux_SortCriteria_CONSTANT
#endif //componenttaginfoaux_SortCriteria_CONSTANT
#ifdef componenttaginfoaux_Teritiary
#undef componenttaginfoaux_Teritiary
#endif //componenttaginfoaux_Teritiary
#ifdef componenttaginfoaux_Teritiary_CONSTANT
#undef componenttaginfoaux_Teritiary_CONSTANT
#endif //componenttaginfoaux_Teritiary_CONSTANT
#ifdef componenttaginfoaux_ThreadSafe
#undef componenttaginfoaux_ThreadSafe
#endif //componenttaginfoaux_ThreadSafe
#ifdef componenttaginfoaux_ThreadSafe_CONSTANT
#undef componenttaginfoaux_ThreadSafe_CONSTANT
#endif //componenttaginfoaux_ThreadSafe_CONSTANT
#ifdef componenttaginfomain_ICONNECTED
#undef componenttaginfomain_ICONNECTED
#endif //componenttaginfomain_ICONNECTED
#ifdef componenttaginfomain_BiggerKey
#undef componenttaginfomain_BiggerKey
#endif //componenttaginfomain_BiggerKey
#ifdef componenttaginfomain_BiggerKey_CONSTANT
#undef componenttaginfomain_BiggerKey_CONSTANT
#endif //componenttaginfomain_BiggerKey_CONSTANT
#ifdef componenttaginfomain_ElementSize
#undef componenttaginfomain_ElementSize
#endif //componenttaginfomain_ElementSize
#ifdef componenttaginfomain_Equal
#undef componenttaginfomain_Equal
#endif //componenttaginfomain_Equal
#ifdef componenttaginfomain_Equal_CONSTANT
#undef componenttaginfomain_Equal_CONSTANT
#endif //componenttaginfomain_Equal_CONSTANT
#ifdef componenttaginfomain_MaxElements
#undef componenttaginfomain_MaxElements
#endif //componenttaginfomain_MaxElements
#ifdef componenttaginfomain_MaxElements_CONSTANT
#undef componenttaginfomain_MaxElements_CONSTANT
#endif //componenttaginfomain_MaxElements_CONSTANT
#ifdef componenttaginfomain_Primary
#undef componenttaginfomain_Primary
#endif //componenttaginfomain_Primary
#ifdef componenttaginfomain_Primary_CONSTANT
#undef componenttaginfomain_Primary_CONSTANT
#endif //componenttaginfomain_Primary_CONSTANT
#ifdef componenttaginfomain_Quaternary
#undef componenttaginfomain_Quaternary
#endif //componenttaginfomain_Quaternary
#ifdef componenttaginfomain_Quaternary_CONSTANT
#undef componenttaginfomain_Quaternary_CONSTANT
#endif //componenttaginfomain_Quaternary_CONSTANT
#ifdef componenttaginfomain_Secondary
#undef componenttaginfomain_Secondary
#endif //componenttaginfomain_Secondary
#ifdef componenttaginfomain_Secondary_CONSTANT
#undef componenttaginfomain_Secondary_CONSTANT
#endif //componenttaginfomain_Secondary_CONSTANT
#ifdef componenttaginfomain_SmallerKey
#undef componenttaginfomain_SmallerKey
#endif //componenttaginfomain_SmallerKey
#ifdef componenttaginfomain_SmallerKey_CONSTANT
#undef componenttaginfomain_SmallerKey_CONSTANT
#endif //componenttaginfomain_SmallerKey_CONSTANT
#ifdef componenttaginfomain_SortCriteria
#undef componenttaginfomain_SortCriteria
#endif //componenttaginfomain_SortCriteria
#ifdef componenttaginfomain_SortCriteria_CONSTANT
#undef componenttaginfomain_SortCriteria_CONSTANT
#endif //componenttaginfomain_SortCriteria_CONSTANT
#ifdef componenttaginfomain_Teritiary
#undef componenttaginfomain_Teritiary
#endif //componenttaginfomain_Teritiary
#ifdef componenttaginfomain_Teritiary_CONSTANT
#undef componenttaginfomain_Teritiary_CONSTANT
#endif //componenttaginfomain_Teritiary_CONSTANT
#ifdef componenttaginfomain_ThreadSafe
#undef componenttaginfomain_ThreadSafe
#endif //componenttaginfomain_ThreadSafe
#ifdef componenttaginfomain_ThreadSafe_CONSTANT
#undef componenttaginfomain_ThreadSafe_CONSTANT
#endif //componenttaginfomain_ThreadSafe_CONSTANT
#ifdef databroadcastinfoaux_ICONNECTED
#undef databroadcastinfoaux_ICONNECTED
#endif //databroadcastinfoaux_ICONNECTED
#ifdef databroadcastinfoaux_BiggerKey
#undef databroadcastinfoaux_BiggerKey
#endif //databroadcastinfoaux_BiggerKey
#ifdef databroadcastinfoaux_BiggerKey_CONSTANT
#undef databroadcastinfoaux_BiggerKey_CONSTANT
#endif //databroadcastinfoaux_BiggerKey_CONSTANT
#ifdef databroadcastinfoaux_ElementSize
#undef databroadcastinfoaux_ElementSize
#endif //databroadcastinfoaux_ElementSize
#ifdef databroadcastinfoaux_Equal
#undef databroadcastinfoaux_Equal
#endif //databroadcastinfoaux_Equal
#ifdef databroadcastinfoaux_Equal_CONSTANT
#undef databroadcastinfoaux_Equal_CONSTANT
#endif //databroadcastinfoaux_Equal_CONSTANT
#ifdef databroadcastinfoaux_MaxElements
#undef databroadcastinfoaux_MaxElements
#endif //databroadcastinfoaux_MaxElements
#ifdef databroadcastinfoaux_MaxElements_CONSTANT
#undef databroadcastinfoaux_MaxElements_CONSTANT
#endif //databroadcastinfoaux_MaxElements_CONSTANT
#ifdef databroadcastinfoaux_Primary
#undef databroadcastinfoaux_Primary
#endif //databroadcastinfoaux_Primary
#ifdef databroadcastinfoaux_Primary_CONSTANT
#undef databroadcastinfoaux_Primary_CONSTANT
#endif //databroadcastinfoaux_Primary_CONSTANT
#ifdef databroadcastinfoaux_Quaternary
#undef databroadcastinfoaux_Quaternary
#endif //databroadcastinfoaux_Quaternary
#ifdef databroadcastinfoaux_Quaternary_CONSTANT
#undef databroadcastinfoaux_Quaternary_CONSTANT
#endif //databroadcastinfoaux_Quaternary_CONSTANT
#ifdef databroadcastinfoaux_Secondary
#undef databroadcastinfoaux_Secondary
#endif //databroadcastinfoaux_Secondary
#ifdef databroadcastinfoaux_Secondary_CONSTANT
#undef databroadcastinfoaux_Secondary_CONSTANT
#endif //databroadcastinfoaux_Secondary_CONSTANT
#ifdef databroadcastinfoaux_SmallerKey
#undef databroadcastinfoaux_SmallerKey
#endif //databroadcastinfoaux_SmallerKey
#ifdef databroadcastinfoaux_SmallerKey_CONSTANT
#undef databroadcastinfoaux_SmallerKey_CONSTANT
#endif //databroadcastinfoaux_SmallerKey_CONSTANT
#ifdef databroadcastinfoaux_SortCriteria
#undef databroadcastinfoaux_SortCriteria
#endif //databroadcastinfoaux_SortCriteria
#ifdef databroadcastinfoaux_SortCriteria_CONSTANT
#undef databroadcastinfoaux_SortCriteria_CONSTANT
#endif //databroadcastinfoaux_SortCriteria_CONSTANT
#ifdef databroadcastinfoaux_Teritiary
#undef databroadcastinfoaux_Teritiary
#endif //databroadcastinfoaux_Teritiary
#ifdef databroadcastinfoaux_Teritiary_CONSTANT
#undef databroadcastinfoaux_Teritiary_CONSTANT
#endif //databroadcastinfoaux_Teritiary_CONSTANT
#ifdef databroadcastinfoaux_ThreadSafe
#undef databroadcastinfoaux_ThreadSafe
#endif //databroadcastinfoaux_ThreadSafe
#ifdef databroadcastinfoaux_ThreadSafe_CONSTANT
#undef databroadcastinfoaux_ThreadSafe_CONSTANT
#endif //databroadcastinfoaux_ThreadSafe_CONSTANT
#ifdef databroadcastinfomain_ICONNECTED
#undef databroadcastinfomain_ICONNECTED
#endif //databroadcastinfomain_ICONNECTED
#ifdef databroadcastinfomain_BiggerKey
#undef databroadcastinfomain_BiggerKey
#endif //databroadcastinfomain_BiggerKey
#ifdef databroadcastinfomain_BiggerKey_CONSTANT
#undef databroadcastinfomain_BiggerKey_CONSTANT
#endif //databroadcastinfomain_BiggerKey_CONSTANT
#ifdef databroadcastinfomain_ElementSize
#undef databroadcastinfomain_ElementSize
#endif //databroadcastinfomain_ElementSize
#ifdef databroadcastinfomain_Equal
#undef databroadcastinfomain_Equal
#endif //databroadcastinfomain_Equal
#ifdef databroadcastinfomain_Equal_CONSTANT
#undef databroadcastinfomain_Equal_CONSTANT
#endif //databroadcastinfomain_Equal_CONSTANT
#ifdef databroadcastinfomain_MaxElements
#undef databroadcastinfomain_MaxElements
#endif //databroadcastinfomain_MaxElements
#ifdef databroadcastinfomain_MaxElements_CONSTANT
#undef databroadcastinfomain_MaxElements_CONSTANT
#endif //databroadcastinfomain_MaxElements_CONSTANT
#ifdef databroadcastinfomain_Primary
#undef databroadcastinfomain_Primary
#endif //databroadcastinfomain_Primary
#ifdef databroadcastinfomain_Primary_CONSTANT
#undef databroadcastinfomain_Primary_CONSTANT
#endif //databroadcastinfomain_Primary_CONSTANT
#ifdef databroadcastinfomain_Quaternary
#undef databroadcastinfomain_Quaternary
#endif //databroadcastinfomain_Quaternary
#ifdef databroadcastinfomain_Quaternary_CONSTANT
#undef databroadcastinfomain_Quaternary_CONSTANT
#endif //databroadcastinfomain_Quaternary_CONSTANT
#ifdef databroadcastinfomain_Secondary
#undef databroadcastinfomain_Secondary
#endif //databroadcastinfomain_Secondary
#ifdef databroadcastinfomain_Secondary_CONSTANT
#undef databroadcastinfomain_Secondary_CONSTANT
#endif //databroadcastinfomain_Secondary_CONSTANT
#ifdef databroadcastinfomain_SmallerKey
#undef databroadcastinfomain_SmallerKey
#endif //databroadcastinfomain_SmallerKey
#ifdef databroadcastinfomain_SmallerKey_CONSTANT
#undef databroadcastinfomain_SmallerKey_CONSTANT
#endif //databroadcastinfomain_SmallerKey_CONSTANT
#ifdef databroadcastinfomain_SortCriteria
#undef databroadcastinfomain_SortCriteria
#endif //databroadcastinfomain_SortCriteria
#ifdef databroadcastinfomain_SortCriteria_CONSTANT
#undef databroadcastinfomain_SortCriteria_CONSTANT
#endif //databroadcastinfomain_SortCriteria_CONSTANT
#ifdef databroadcastinfomain_Teritiary
#undef databroadcastinfomain_Teritiary
#endif //databroadcastinfomain_Teritiary
#ifdef databroadcastinfomain_Teritiary_CONSTANT
#undef databroadcastinfomain_Teritiary_CONSTANT
#endif //databroadcastinfomain_Teritiary_CONSTANT
#ifdef databroadcastinfomain_ThreadSafe
#undef databroadcastinfomain_ThreadSafe
#endif //databroadcastinfomain_ThreadSafe
#ifdef databroadcastinfomain_ThreadSafe_CONSTANT
#undef databroadcastinfomain_ThreadSafe_CONSTANT
#endif //databroadcastinfomain_ThreadSafe_CONSTANT
#ifdef subtitleconfaux_ICONNECTED
#undef subtitleconfaux_ICONNECTED
#endif //subtitleconfaux_ICONNECTED
#ifdef subtitleconfaux_BiggerKey
#undef subtitleconfaux_BiggerKey
#endif //subtitleconfaux_BiggerKey
#ifdef subtitleconfaux_BiggerKey_CONSTANT
#undef subtitleconfaux_BiggerKey_CONSTANT
#endif //subtitleconfaux_BiggerKey_CONSTANT
#ifdef subtitleconfaux_ElementSize
#undef subtitleconfaux_ElementSize
#endif //subtitleconfaux_ElementSize
#ifdef subtitleconfaux_Equal
#undef subtitleconfaux_Equal
#endif //subtitleconfaux_Equal
#ifdef subtitleconfaux_Equal_CONSTANT
#undef subtitleconfaux_Equal_CONSTANT
#endif //subtitleconfaux_Equal_CONSTANT
#ifdef subtitleconfaux_MaxElements
#undef subtitleconfaux_MaxElements
#endif //subtitleconfaux_MaxElements
#ifdef subtitleconfaux_MaxElements_CONSTANT
#undef subtitleconfaux_MaxElements_CONSTANT
#endif //subtitleconfaux_MaxElements_CONSTANT
#ifdef subtitleconfaux_Primary
#undef subtitleconfaux_Primary
#endif //subtitleconfaux_Primary
#ifdef subtitleconfaux_Primary_CONSTANT
#undef subtitleconfaux_Primary_CONSTANT
#endif //subtitleconfaux_Primary_CONSTANT
#ifdef subtitleconfaux_Quaternary
#undef subtitleconfaux_Quaternary
#endif //subtitleconfaux_Quaternary
#ifdef subtitleconfaux_Quaternary_CONSTANT
#undef subtitleconfaux_Quaternary_CONSTANT
#endif //subtitleconfaux_Quaternary_CONSTANT
#ifdef subtitleconfaux_Secondary
#undef subtitleconfaux_Secondary
#endif //subtitleconfaux_Secondary
#ifdef subtitleconfaux_Secondary_CONSTANT
#undef subtitleconfaux_Secondary_CONSTANT
#endif //subtitleconfaux_Secondary_CONSTANT
#ifdef subtitleconfaux_SmallerKey
#undef subtitleconfaux_SmallerKey
#endif //subtitleconfaux_SmallerKey
#ifdef subtitleconfaux_SmallerKey_CONSTANT
#undef subtitleconfaux_SmallerKey_CONSTANT
#endif //subtitleconfaux_SmallerKey_CONSTANT
#ifdef subtitleconfaux_SortCriteria
#undef subtitleconfaux_SortCriteria
#endif //subtitleconfaux_SortCriteria
#ifdef subtitleconfaux_SortCriteria_CONSTANT
#undef subtitleconfaux_SortCriteria_CONSTANT
#endif //subtitleconfaux_SortCriteria_CONSTANT
#ifdef subtitleconfaux_Teritiary
#undef subtitleconfaux_Teritiary
#endif //subtitleconfaux_Teritiary
#ifdef subtitleconfaux_Teritiary_CONSTANT
#undef subtitleconfaux_Teritiary_CONSTANT
#endif //subtitleconfaux_Teritiary_CONSTANT
#ifdef subtitleconfaux_ThreadSafe
#undef subtitleconfaux_ThreadSafe
#endif //subtitleconfaux_ThreadSafe
#ifdef subtitleconfaux_ThreadSafe_CONSTANT
#undef subtitleconfaux_ThreadSafe_CONSTANT
#endif //subtitleconfaux_ThreadSafe_CONSTANT
#ifdef subtitleconfmain_ICONNECTED
#undef subtitleconfmain_ICONNECTED
#endif //subtitleconfmain_ICONNECTED
#ifdef subtitleconfmain_BiggerKey
#undef subtitleconfmain_BiggerKey
#endif //subtitleconfmain_BiggerKey
#ifdef subtitleconfmain_BiggerKey_CONSTANT
#undef subtitleconfmain_BiggerKey_CONSTANT
#endif //subtitleconfmain_BiggerKey_CONSTANT
#ifdef subtitleconfmain_ElementSize
#undef subtitleconfmain_ElementSize
#endif //subtitleconfmain_ElementSize
#ifdef subtitleconfmain_Equal
#undef subtitleconfmain_Equal
#endif //subtitleconfmain_Equal
#ifdef subtitleconfmain_Equal_CONSTANT
#undef subtitleconfmain_Equal_CONSTANT
#endif //subtitleconfmain_Equal_CONSTANT
#ifdef subtitleconfmain_MaxElements
#undef subtitleconfmain_MaxElements
#endif //subtitleconfmain_MaxElements
#ifdef subtitleconfmain_MaxElements_CONSTANT
#undef subtitleconfmain_MaxElements_CONSTANT
#endif //subtitleconfmain_MaxElements_CONSTANT
#ifdef subtitleconfmain_Primary
#undef subtitleconfmain_Primary
#endif //subtitleconfmain_Primary
#ifdef subtitleconfmain_Primary_CONSTANT
#undef subtitleconfmain_Primary_CONSTANT
#endif //subtitleconfmain_Primary_CONSTANT
#ifdef subtitleconfmain_Quaternary
#undef subtitleconfmain_Quaternary
#endif //subtitleconfmain_Quaternary
#ifdef subtitleconfmain_Quaternary_CONSTANT
#undef subtitleconfmain_Quaternary_CONSTANT
#endif //subtitleconfmain_Quaternary_CONSTANT
#ifdef subtitleconfmain_Secondary
#undef subtitleconfmain_Secondary
#endif //subtitleconfmain_Secondary
#ifdef subtitleconfmain_Secondary_CONSTANT
#undef subtitleconfmain_Secondary_CONSTANT
#endif //subtitleconfmain_Secondary_CONSTANT
#ifdef subtitleconfmain_SmallerKey
#undef subtitleconfmain_SmallerKey
#endif //subtitleconfmain_SmallerKey
#ifdef subtitleconfmain_SmallerKey_CONSTANT
#undef subtitleconfmain_SmallerKey_CONSTANT
#endif //subtitleconfmain_SmallerKey_CONSTANT
#ifdef subtitleconfmain_SortCriteria
#undef subtitleconfmain_SortCriteria
#endif //subtitleconfmain_SortCriteria
#ifdef subtitleconfmain_SortCriteria_CONSTANT
#undef subtitleconfmain_SortCriteria_CONSTANT
#endif //subtitleconfmain_SortCriteria_CONSTANT
#ifdef subtitleconfmain_Teritiary
#undef subtitleconfmain_Teritiary
#endif //subtitleconfmain_Teritiary
#ifdef subtitleconfmain_Teritiary_CONSTANT
#undef subtitleconfmain_Teritiary_CONSTANT
#endif //subtitleconfmain_Teritiary_CONSTANT
#ifdef subtitleconfmain_ThreadSafe
#undef subtitleconfmain_ThreadSafe
#endif //subtitleconfmain_ThreadSafe
#ifdef subtitleconfmain_ThreadSafe_CONSTANT
#undef subtitleconfmain_ThreadSafe_CONSTANT
#endif //subtitleconfmain_ThreadSafe_CONSTANT
#ifdef teletextconfaux_ICONNECTED
#undef teletextconfaux_ICONNECTED
#endif //teletextconfaux_ICONNECTED
#ifdef teletextconfaux_BiggerKey
#undef teletextconfaux_BiggerKey
#endif //teletextconfaux_BiggerKey
#ifdef teletextconfaux_BiggerKey_CONSTANT
#undef teletextconfaux_BiggerKey_CONSTANT
#endif //teletextconfaux_BiggerKey_CONSTANT
#ifdef teletextconfaux_ElementSize
#undef teletextconfaux_ElementSize
#endif //teletextconfaux_ElementSize
#ifdef teletextconfaux_Equal
#undef teletextconfaux_Equal
#endif //teletextconfaux_Equal
#ifdef teletextconfaux_Equal_CONSTANT
#undef teletextconfaux_Equal_CONSTANT
#endif //teletextconfaux_Equal_CONSTANT
#ifdef teletextconfaux_MaxElements
#undef teletextconfaux_MaxElements
#endif //teletextconfaux_MaxElements
#ifdef teletextconfaux_MaxElements_CONSTANT
#undef teletextconfaux_MaxElements_CONSTANT
#endif //teletextconfaux_MaxElements_CONSTANT
#ifdef teletextconfaux_Primary
#undef teletextconfaux_Primary
#endif //teletextconfaux_Primary
#ifdef teletextconfaux_Primary_CONSTANT
#undef teletextconfaux_Primary_CONSTANT
#endif //teletextconfaux_Primary_CONSTANT
#ifdef teletextconfaux_Quaternary
#undef teletextconfaux_Quaternary
#endif //teletextconfaux_Quaternary
#ifdef teletextconfaux_Quaternary_CONSTANT
#undef teletextconfaux_Quaternary_CONSTANT
#endif //teletextconfaux_Quaternary_CONSTANT
#ifdef teletextconfaux_Secondary
#undef teletextconfaux_Secondary
#endif //teletextconfaux_Secondary
#ifdef teletextconfaux_Secondary_CONSTANT
#undef teletextconfaux_Secondary_CONSTANT
#endif //teletextconfaux_Secondary_CONSTANT
#ifdef teletextconfaux_SmallerKey
#undef teletextconfaux_SmallerKey
#endif //teletextconfaux_SmallerKey
#ifdef teletextconfaux_SmallerKey_CONSTANT
#undef teletextconfaux_SmallerKey_CONSTANT
#endif //teletextconfaux_SmallerKey_CONSTANT
#ifdef teletextconfaux_SortCriteria
#undef teletextconfaux_SortCriteria
#endif //teletextconfaux_SortCriteria
#ifdef teletextconfaux_SortCriteria_CONSTANT
#undef teletextconfaux_SortCriteria_CONSTANT
#endif //teletextconfaux_SortCriteria_CONSTANT
#ifdef teletextconfaux_Teritiary
#undef teletextconfaux_Teritiary
#endif //teletextconfaux_Teritiary
#ifdef teletextconfaux_Teritiary_CONSTANT
#undef teletextconfaux_Teritiary_CONSTANT
#endif //teletextconfaux_Teritiary_CONSTANT
#ifdef teletextconfaux_ThreadSafe
#undef teletextconfaux_ThreadSafe
#endif //teletextconfaux_ThreadSafe
#ifdef teletextconfaux_ThreadSafe_CONSTANT
#undef teletextconfaux_ThreadSafe_CONSTANT
#endif //teletextconfaux_ThreadSafe_CONSTANT
#ifdef teletextconfmain_ICONNECTED
#undef teletextconfmain_ICONNECTED
#endif //teletextconfmain_ICONNECTED
#ifdef teletextconfmain_BiggerKey
#undef teletextconfmain_BiggerKey
#endif //teletextconfmain_BiggerKey
#ifdef teletextconfmain_BiggerKey_CONSTANT
#undef teletextconfmain_BiggerKey_CONSTANT
#endif //teletextconfmain_BiggerKey_CONSTANT
#ifdef teletextconfmain_ElementSize
#undef teletextconfmain_ElementSize
#endif //teletextconfmain_ElementSize
#ifdef teletextconfmain_Equal
#undef teletextconfmain_Equal
#endif //teletextconfmain_Equal
#ifdef teletextconfmain_Equal_CONSTANT
#undef teletextconfmain_Equal_CONSTANT
#endif //teletextconfmain_Equal_CONSTANT
#ifdef teletextconfmain_MaxElements
#undef teletextconfmain_MaxElements
#endif //teletextconfmain_MaxElements
#ifdef teletextconfmain_MaxElements_CONSTANT
#undef teletextconfmain_MaxElements_CONSTANT
#endif //teletextconfmain_MaxElements_CONSTANT
#ifdef teletextconfmain_Primary
#undef teletextconfmain_Primary
#endif //teletextconfmain_Primary
#ifdef teletextconfmain_Primary_CONSTANT
#undef teletextconfmain_Primary_CONSTANT
#endif //teletextconfmain_Primary_CONSTANT
#ifdef teletextconfmain_Quaternary
#undef teletextconfmain_Quaternary
#endif //teletextconfmain_Quaternary
#ifdef teletextconfmain_Quaternary_CONSTANT
#undef teletextconfmain_Quaternary_CONSTANT
#endif //teletextconfmain_Quaternary_CONSTANT
#ifdef teletextconfmain_Secondary
#undef teletextconfmain_Secondary
#endif //teletextconfmain_Secondary
#ifdef teletextconfmain_Secondary_CONSTANT
#undef teletextconfmain_Secondary_CONSTANT
#endif //teletextconfmain_Secondary_CONSTANT
#ifdef teletextconfmain_SmallerKey
#undef teletextconfmain_SmallerKey
#endif //teletextconfmain_SmallerKey
#ifdef teletextconfmain_SmallerKey_CONSTANT
#undef teletextconfmain_SmallerKey_CONSTANT
#endif //teletextconfmain_SmallerKey_CONSTANT
#ifdef teletextconfmain_SortCriteria
#undef teletextconfmain_SortCriteria
#endif //teletextconfmain_SortCriteria
#ifdef teletextconfmain_SortCriteria_CONSTANT
#undef teletextconfmain_SortCriteria_CONSTANT
#endif //teletextconfmain_SortCriteria_CONSTANT
#ifdef teletextconfmain_Teritiary
#undef teletextconfmain_Teritiary
#endif //teletextconfmain_Teritiary
#ifdef teletextconfmain_Teritiary_CONSTANT
#undef teletextconfmain_Teritiary_CONSTANT
#endif //teletextconfmain_Teritiary_CONSTANT
#ifdef teletextconfmain_ThreadSafe
#undef teletextconfmain_ThreadSafe
#endif //teletextconfmain_ThreadSafe
#ifdef teletextconfmain_ThreadSafe_CONSTANT
#undef teletextconfmain_ThreadSafe_CONSTANT
#endif //teletextconfmain_ThreadSafe_CONSTANT
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#ifdef NOCLASS
#undef NOCLASS
#endif //NOCLASS
#endif //LOCAL_UNDEFINES
