#define BYTE            8
#define BYTES2          16
#define BYTES3          24
#define BYTES4          32

/*#define NBITS(x)                (0xFFFFFFFF >> (32-x))
#define GETNEXT32(ptr,byt,bit)  (((((ptr[byt + 1])<<BYTES3) | ((ptr[byt+2])<<BYTES2) | ((ptr[byt+3])<<BYTE) | ((ptr[byt+4])))) >> (BYTE-bit))
#define GETCURBITS(ptr,byt,bit) (ptr[byt]<<(BYTES3 + bit))
#define GETFULL32(ptr,byt,bit)  (GETNEXT32(ptr,byt,bit)|GETCURBITS(ptr,byt,bit))
#define GETNBITS(ptr,byt,bit,n) (((GETFULL32(ptr,byt,bit)>>(BYTES4-n))) & (NBITS(n)))*/

#define GETNBITS(bit,n)     (((v32>>(BYTES4-(bit + n)))) & (NBITS(n)))
#define NBITS(x)            (0xFFFFFFFF >> (32-x))

#define GET32(byt)              (((((ptr[byt])<<BYTES3) | ((ptr[byt+1])<<BYTES2) | ((ptr[byt+2])<<BYTE) | (ptr[byt+3]))))
#define GET16(byt)              (((ptr[byt])<<BYTE) | (ptr[byt+1]))

#define GET32PTR(ptr,byt)       (((((ptr[byt])<<BYTES3) | ((ptr[byt+1])<<BYTES2) | ((ptr[byt+2])<<BYTE) | (ptr[byt+3]))))

#define MIN(a,b)                ((a < b)? a : b)

#define HSV_SHOW_WORD(p)                    ( ((*(p))<<8)| (*((p)+1)) )
#define HSV_GETSECTION_LENGTH(p)            ((HSV_SHOW_WORD((p)+1)&0x0fff)+3)
#define GET_PRIVATE_DATA_SPECIFIER(ptr)     ((*(ptr - 6) == 0x5F) ? GET32PTR((ptr - 4),0): 0)



