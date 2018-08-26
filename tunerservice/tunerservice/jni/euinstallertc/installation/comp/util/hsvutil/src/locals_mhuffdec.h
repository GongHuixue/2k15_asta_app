#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <DtgHuffmanDec.h>

#include <FreeSatTable1.h>

#include <FreeSatTable2.h>

#define ENDOFSTRING   '\x00'

#define ESCAPE        '\x1B'

#define STARTOFSTRING '\x00'

#define ByteBitSize  8

#define IntByteSize  4

#define IntBitSize   ByteBitSize*IntByteSize

union u32bytesdef{
      unsigned int num;
      unsigned char byte[IntByteSize];
};
typedef union u32bytesdef u32bytes;
#define _INCREMENT 16

;
;
;
;
;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
static const int freesat_complete_table_1_len;
static const int freesat_complete_table_2_len;
struct freesat_complete_table *freesat_complete_table_td;
static struct freesat_complete_table *s__freesat_complete_table_td;
int freesat_complete_table_td_len ;
static int s__freesat_complete_table_td_len ;
int FileNr;
static int s__FileNr;
FILE *fname;
static FILE *s__fname;
char * DTG_huffman_decoder_to_string(const unsigned char * src, int size, int *DstLen);
void fillmemory(unsigned int *mem, int *memlen, const unsigned char *src, int srcpos, int srcsize);
void searchtable(char prevchar,unsigned int val, int *vallen, char *curchar);
void handleUncompressed(char prevchar,unsigned int val, int *vallen, char *curchar);
void genFile(const unsigned char * src, int size,const char *fr);
void module__init(void){
	freesat_complete_table_td	=	s__freesat_complete_table_td;
	freesat_complete_table_td_len	=	s__freesat_complete_table_td_len;
	FileNr	=	s__FileNr;
	fname	=	s__fname;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef ENDOFSTRING
#undef ENDOFSTRING
#endif //ENDOFSTRING
#ifdef ESCAPE
#undef ESCAPE
#endif //ESCAPE
#ifdef STARTOFSTRING
#undef STARTOFSTRING
#endif //STARTOFSTRING
#ifdef ByteBitSize
#undef ByteBitSize
#endif //ByteBitSize
#ifdef IntByteSize
#undef IntByteSize
#endif //IntByteSize
#ifdef IntBitSize
#undef IntBitSize
#endif //IntBitSize
#ifdef _INCREMENT
#undef _INCREMENT
#endif //_INCREMENT
#endif //LOCAL_UNDEFINES
