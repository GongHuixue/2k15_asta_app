#ifndef IMULTILINGUALSTRINGCONVERSION_H
#define IMULTILINGUALSTRINGCONVERSION_H
#include <intfparam.h>
#include <provreq.h>
class IMultiLingualStringConversion
{
public:
	virtual ~IMultiLingualStringConversion(){}
	#define IMultiLingualStringConversion_RESULT_OK		((int)0 )
	#define IMultiLingualStringConversion_RESULT_ERROR_INVALID_TABLE		((int)1 )
	#define IMultiLingualStringConversion_RESULT_DESTINATION_TOO_SMALL		((int)2 )
	#define IMultiLingualStringConversion_RESULT_NON_EVEN_SIZE		((int)3 )
	#define IMultiLingualStringConversion_TableDefault		((Nat8)0x00 )
	#define IMultiLingualStringConversion_TableLatin1		((Nat8)0x81 )
	#define IMultiLingualStringConversion_TableISO8859_1		((Nat8)0x81 )
	#define IMultiLingualStringConversion_TableLatin2		((Nat8)0x82 )
	#define IMultiLingualStringConversion_TableISO8859_2		((Nat8)0x82 )
	#define IMultiLingualStringConversion_TableLatin3		((Nat8)0x83 )
	#define IMultiLingualStringConversion_TableISO8859_3		((Nat8)0x83 )
	#define IMultiLingualStringConversion_TableLatin4		((Nat8)0x84 )
	#define IMultiLingualStringConversion_TableISO8859_4		((Nat8)0x84 )
	#define IMultiLingualStringConversion_TableCyrillic		((Nat8)0x85 )
	#define IMultiLingualStringConversion_TableISO8859_5		((Nat8)0x85 )
	#define IMultiLingualStringConversion_TableArabic		((Nat8)0x86 )
	#define IMultiLingualStringConversion_TableISO8859_6		((Nat8)0x86 )
	#define IMultiLingualStringConversion_TableGreek		((Nat8)0x87 )
	#define IMultiLingualStringConversion_TableISO8859_7		((Nat8)0x87 )
	#define IMultiLingualStringConversion_TableHebrew		((Nat8)0x88 )
	#define IMultiLingualStringConversion_TableISO8859_8		((Nat8)0x88 )
	#define IMultiLingualStringConversion_TableLatin5		((Nat8)0x89 )
	#define IMultiLingualStringConversion_TableISO8859_9		((Nat8)0x89 )
	#define IMultiLingualStringConversion_TableLatin6		((Nat8)0x8A )
	#define IMultiLingualStringConversion_TableISO8859_10		((Nat8)0x8A )
	#define IMultiLingualStringConversion_TableThai		((Nat8)0x8B )
	#define IMultiLingualStringConversion_TableISO8859_11		((Nat8)0x8B )
	#define IMultiLingualStringConversion_TableLatin7		((Nat8)0x8D )
	#define IMultiLingualStringConversion_TableISO8859_13		((Nat8)0x8D )
	#define IMultiLingualStringConversion_TableLatin8		((Nat8)0x8E )
	#define IMultiLingualStringConversion_TableISO8859_14		((Nat8)0x8E )
	#define IMultiLingualStringConversion_TableLatin9		((Nat8)0x8F )
	#define IMultiLingualStringConversion_TableISO8859_15		((Nat8)0x8F )
	#define IMultiLingualStringConversion_TableLatin10		((Nat8)0x90 )
	#define IMultiLingualStringConversion_TableISO8859_16		((Nat8)0x90 )
	#define IMultiLingualStringConversion_TableLegacyCyrillic		((Nat8)0x01 )
	#define IMultiLingualStringConversion_TableLegacyArabic		((Nat8)0x02 )
	#define IMultiLingualStringConversion_TableLegacyGreek		((Nat8)0x03 )
	#define IMultiLingualStringConversion_TableLegacyHebrew		((Nat8)0x04 )
	#define IMultiLingualStringConversion_TableLegacyLatin5		((Nat8)0x05 )
	#define IMultiLingualStringConversion_TableLegacyLatin2		((Nat8)0x06 )
	#define IMultiLingualStringConversion_TableUcs2		((Nat8)0x11 )
	#define IMultiLingualStringConversion_TableChinese		((Nat8)0x13 )
	#define IMultiLingualStringConversion_TableUtf8		((Nat8)0x15 )
	#define IMultiLingualStringConversion_TableWindows1250		((Nat8)0x91 )
	#define IMultiLingualStringConversion_TableWindows1251		((Nat8)0x92 )
	#define IMultiLingualStringConversion_TableWindows1252		((Nat8)0x93 )
	#define IMultiLingualStringConversion_TableWindows1253		((Nat8)0x94 )
	#define IMultiLingualStringConversion_TableWindows1254		((Nat8)0x95 )
	virtual FResult MbToWc(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen)= 0;
	virtual FResult MbToWcEx(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool skipcontrols)= 0;
	virtual FResult WcToMb(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen)= 0;
	virtual FResult WcToMbEx(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen,Bool skipcontrols)= 0;
	virtual FResult MbToWcChina(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen)= 0;
};


#define IMultiLingualStringConversionImpl(Comp,intf)    \
virtual FResult intf ## _MbToWc(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen);\
virtual FResult intf ## _MbToWcEx(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool skipcontrols);\
virtual FResult intf ## _WcToMb(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen);\
virtual FResult intf ## _WcToMbEx(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen,Bool skipcontrols);\
virtual FResult intf ## _MbToWcChina(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen);\
class Comp ## _ ## intf : public IMultiLingualStringConversion \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult MbToWc(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen){ return m_parent->intf ## _MbToWc(table,mbstr,mblen,wcstr,wclen);}\
virtual FResult MbToWcEx(Nat8 table,Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool skipcontrols){ return m_parent->intf ## _MbToWcEx(table,mbstr,mblen,wcstr,wclen,skipcontrols);}\
virtual FResult WcToMb(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen){ return m_parent->intf ## _WcToMb(table,wcstr,wclen,mbstr,mblen);}\
virtual FResult WcToMbEx(Nat8 table,Nat16 * wcstr,int wclen,Nat8 * mbstr,int * mblen,Bool skipcontrols){ return m_parent->intf ## _WcToMbEx(table,wcstr,wclen,mbstr,mblen,skipcontrols);}\
virtual FResult MbToWcChina(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen){ return m_parent->intf ## _MbToWcChina(mbstr,mblen,wcstr,wclen);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
