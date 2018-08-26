
#include "_hsvutil_mhuffdec.h"

#include "stdio.h"

#include "stdlib.h"

#include "DtgHuffmanDec.h"

#include "FreeSatTable1.h"

#include "FreeSatTable2.h"



#ifndef __cplusplus


#endif
/*typedef enum booldef bool;*/



const int CHsvUtil_mhuffdec_Priv::freesat_complete_table_1_len=(sizeof(freesat_complete_table_1))/sizeof(struct freesat_complete_table);

const int CHsvUtil_mhuffdec_Priv::freesat_complete_table_2_len=(sizeof(freesat_complete_table_2))/sizeof(struct freesat_complete_table);


struct freesat_complete_table *CHsvUtil_mhuffdec_Priv::s__freesat_complete_table_td;

int CHsvUtil_mhuffdec_Priv::s__freesat_complete_table_td_len ;






// the number of bytes the result will be increased






int CHsvUtil_mhuffdec_Priv::s__FileNr=0;

FILE *CHsvUtil_mhuffdec_Priv::s__fname=NULL;





char * CHsvUtil_mhuffdec_Priv::DTG_huffman_decoder_to_string(const unsigned char * src, int size, int *DstLen)
{
    int resultlen=0;
    int resultpos=0;
    char prevchar=STARTOFSTRING;
    char curchar=STARTOFSTRING;
    unsigned int val=0;
    int vallen;
    int srcbitpos=0;//process all of the bytes
    // shift register that must kept full
    // full from MSB to LSB: so shift upwards
    unsigned int mem;
    int memlen=0; // number of bits used in the memory
    bool busy=true;
    bool escaping=false;
    int spos=0;
    int pos = 0;
    int offs = 0;
    int i=0;


    char *result= (char *)malloc(1);
    result[0]='\0';
    if (size<3) return result;
    if ((src[0]!=0x1F)&&(((src[1]!=1)||(src[1]!=2)))) return result;  

    resultlen = size*3;
    result = (char*)realloc(result,resultlen);
    result[resultlen-1]='\0';
    resultpos=0;
    prevchar=STARTOFSTRING;
    curchar=STARTOFSTRING;
    val=0;
    srcbitpos=0;//process all of the bytes
    // shift register that must kept full
    // full from MSB to LSB: so shift upwards
    mem=0;
    memlen=0; // number of bits used in the memory
    busy=true;

   

    if (src[1] == 1)
    {
        freesat_complete_table_td = freesat_complete_table_1;
        freesat_complete_table_td_len = freesat_complete_table_1_len;
    } else {
        freesat_complete_table_td = freesat_complete_table_2;
        freesat_complete_table_td_len = freesat_complete_table_2_len;

    };

  
    srcbitpos=2*ByteBitSize;

    escaping=false;
    //normal stop condition is when a '\0' has been reached. 
    while (busy){
        fillmemory(&mem,&memlen,src,srcbitpos,size);
        if (escaping==false){
          searchtable(prevchar,mem,&vallen,&curchar);
        }else{
          handleUncompressed(prevchar,mem,&vallen,&curchar);
        }
        
        //check if 2 can be placed: always leave one left for the zero ending
        if (resultpos+2 >= resultlen){
                resultlen+=_INCREMENT;
                result = (char*)realloc(result,resultlen);
                result[resultlen-1]='\0';

        };

        if (escaping==false){
            if (vallen==0)
                busy=false;//unknown transition;
            if (curchar==ESCAPE){
                escaping=true;
            }else{
                result[resultpos]=curchar;
                resultpos++;
            };
        }else{
            if (((unsigned char)curchar)<0x80){
                escaping=false;
            };
            result[resultpos]=curchar;
            resultpos++;
        };
    
        srcbitpos += vallen; 
        prevchar = curchar;

        spos = srcbitpos/ByteBitSize;

        if ((spos>=size)||(curchar==ENDOFSTRING)) 
            busy=false;

    };
    if (vallen==0){
         if (resultpos+4 >= resultlen){
                resultlen+=4;
                result = (char*)realloc(result,resultlen);
         }else{
             result[resultpos+0]='{';
             result[resultpos+1]='?';
             result[resultpos+2]='}';
             resultpos+=3;
         };

    }else{
        if (curchar==ESCAPE){
            //overwrite the curchar because that's the Escape Character
             resultpos--;
            //go to the next whole byte
             pos = srcbitpos/ByteBitSize;
             offs = srcbitpos%ByteBitSize;
             srcbitpos += ByteBitSize-offs;
             if (offs==0)srcbitpos-=ByteBitSize;
             pos = srcbitpos/ByteBitSize;
             if (resultpos+size-pos+1 >= resultlen){
                    resultlen+=size-pos+1;
                    result = (char*)realloc(result,resultlen);
                    result[resultlen-1]='\0';

            };
             for (i=pos;i<size;i++){
                 if (src[i]==ESCAPE){
                     result[resultpos]='{';
                     break;
                 }else{
                    result[resultpos]=src[i];
                }
                 resultpos++;
             };
        };
    };
    result[resultpos]='\0';
    resultlen = ++resultpos;
    result = (char *)realloc(result,resultlen);
    result[resultlen-1]='\0';

#ifdef _DUMPSTRINGS
    genFile(src,size,result);
#endif

    *DstLen = resultlen;
    return result;

}

void CHsvUtil_mhuffdec_Priv::fillmemory(unsigned int *mem, int *memlen, const unsigned char *src, int srcpos, int srcsize){
    //access the byte in src
    int pos=0;
    int maxp=0;
    int i=0;
    int bits=0;
    int shiftnr=0;


    u32bytes tmp; tmp.num=0;
    pos = srcpos/ByteBitSize;
    maxp = srcsize-pos;
    maxp = (IntByteSize < maxp)? IntByteSize : maxp;
    for (i=0;i<maxp;i++){
        tmp.byte[IntByteSize-1-i]=src[pos+i];
    };
    bits = srcpos%ByteBitSize;
    shiftnr = bits;
    (*mem) = tmp.num << shiftnr;
    (*memlen) = sizeof(*mem)- shiftnr;


}

void CHsvUtil_mhuffdec_Priv::searchtable(char prevchar,unsigned int val, int *vallen, char *curchar){

    //run through the entire table

    char tcur=0;
    unsigned int tv=0;
    unsigned int mv=0;
    bool searching=true;
    int pos = 0;
    int tvallen=0;
    unsigned int mask=0;
    unsigned int IntMask = 0xFFFFFFFF;
    while (searching){
        if (freesat_complete_table_td[pos].prev==prevchar){
            tvallen = freesat_complete_table_td[pos].valuelen;
            mask = IntMask << (IntBitSize - tvallen);
            tv = freesat_complete_table_td[pos].value;
            mv = mask&val;
            tcur = freesat_complete_table_td[pos].cur;

            if (mv==tv){
                searching=false;
                (*vallen) = tvallen;
                (*curchar) = freesat_complete_table_td[pos].cur;
                break;
            };

        };
        pos++;
        if (pos>=freesat_complete_table_td_len){
            searching=false;
            (*vallen)=0;
            (*curchar)='{';
        };
    };
 

}


void CHsvUtil_mhuffdec_Priv::handleUncompressed(char prevchar,unsigned int val, int *vallen, char *curchar){

    //run through the entire table
    int tvallen=0;
    unsigned int mask=0;
    unsigned int IntMask = 0xFFFFFFFF;
    unsigned int mv=0;

    UNUSED(prevchar);

    tvallen = ByteBitSize;
    mask = IntMask << (IntBitSize - tvallen);
    mv = mask&val;
    (*vallen) = tvallen;
    (*curchar) = (char)((mv >>(IntBitSize-ByteBitSize))&0xFF);
    

}

void CHsvUtil_mhuffdec_Priv::genFile(const unsigned char * src, int size,const char *fr)
{
    FILE *fRES = NULL;
    FILE *fSRC = NULL;
    char filename[1200];
    int i=0;


    sprintf(filename,"FreeSatTitleFileRES_%03i.txt",FileNr);
    fRES=fopen(filename,"w");
    if (fRES==NULL) return;
    fprintf(fRES,"%s",fr);

    fclose(fRES);

    sprintf(filename,"FreeSatTitleFileSRC_%03i.txt",FileNr);
    fSRC=fopen(filename,"w + b");
    if (fSRC==NULL) return;
    for (i=0;i<size;i++){
        fputc(src[i],fSRC);
    };
    fclose(fSRC);

    FileNr++;

}

void CHsvUtil_mhuffdec_Priv::istringdec_DtgHuffmanDecoderToString(Nat8* src, Address* dstBuf, int size, int *dstSize)
{
    *dstBuf = DTG_huffman_decoder_to_string(src, size, dstSize);
}
/******************************************************************************/
