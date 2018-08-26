#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#ifndef MIN

#define MIN(a,b)    ((a) < (b) ? (a) : (b))

#endif

#define WINDOWS_C1_TABLE_SIZE   0x20

#define WINDOWS_C1_TABLE_OFFSET 0x80

#define	WINDOWS_C1_TABLE_ENTRIES	(5)

#define   NB_TABLES             ( sizeof(CharSetControls)/sizeof(CharSetControls[0]) )

#define   NB_LEGACY_TABLES      ( ( NB_TABLES > 8 ) ? 8 : NB_TABLES )

#define		NB_ACCCENTEDCHARMAPPING	(181)

typedef struct
{
    Nat8    PrimaryChar;
    Nat16   UnicodeChar;
} AccentedCharMapping;
#define	NUM_UCS_ENTRIES	(23730)
/* added by vdixit */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef MIN

#endif

static const Nat16 CharSetControls[ ][ 96 ];
Nat16 windowsC1Table[WINDOWS_C1_TABLE_ENTRIES ][ WINDOWS_C1_TABLE_SIZE ];
static Nat16 s__windowsC1Table[WINDOWS_C1_TABLE_ENTRIES ][ WINDOWS_C1_TABLE_SIZE ];
AccentedCharMapping m_RepertoireCode[NB_ACCCENTEDCHARMAPPING];
static AccentedCharMapping s__m_RepertoireCode[NB_ACCCENTEDCHARMAPPING];
unsigned short GB2312toUCS[NUM_UCS_ENTRIES];
static unsigned short s__GB2312toUCS[NUM_UCS_ENTRIES];
FResult UCStoUTF8( Nat16 *ucsstr, Nat32 ucslen, Nat8 *utfstr, Nat32 *utflen );
FResult UTF8toUCS( Nat8 *utfstr, Nat32 utflen, Nat16 *ucsstr, Nat32 *ucslen );
void module__init(void){
#ifndef MIN

#endif

	memcpy((void*)windowsC1Table,(void*)s__windowsC1Table,sizeof(windowsC1Table));
	memcpy((void*)m_RepertoireCode,(void*)s__m_RepertoireCode,sizeof(m_RepertoireCode));
	memcpy((void*)GB2312toUCS,(void*)s__GB2312toUCS,sizeof(GB2312toUCS));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MIN(a,b)
#undef MIN(a,b)
#endif //MIN(a,b)
#ifdef WINDOWS_C1_TABLE_SIZE
#undef WINDOWS_C1_TABLE_SIZE
#endif //WINDOWS_C1_TABLE_SIZE
#ifdef WINDOWS_C1_TABLE_OFFSET
#undef WINDOWS_C1_TABLE_OFFSET
#endif //WINDOWS_C1_TABLE_OFFSET
#ifdef WINDOWS_C1_TABLE_ENTRIES
#undef WINDOWS_C1_TABLE_ENTRIES
#endif //WINDOWS_C1_TABLE_ENTRIES
#ifdef NB_TABLES
#undef NB_TABLES
#endif //NB_TABLES
#ifdef NB_LEGACY_TABLES
#undef NB_LEGACY_TABLES
#endif //NB_LEGACY_TABLES
#ifdef NB_ACCCENTEDCHARMAPPING
#undef NB_ACCCENTEDCHARMAPPING
#endif //NB_ACCCENTEDCHARMAPPING
#ifdef NUM_UCS_ENTRIES
#undef NUM_UCS_ENTRIES
#endif //NUM_UCS_ENTRIES
#endif //LOCAL_UNDEFINES
