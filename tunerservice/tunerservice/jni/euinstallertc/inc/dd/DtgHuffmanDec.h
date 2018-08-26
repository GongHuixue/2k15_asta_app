#ifndef _FREESAT_HUFFMAN_DEC_H_
#define _FREESAT_HUFFMAN_DEC_H_

struct freesat_complete_table {
    char prev;
	unsigned int value;
	int valuelen;//length of the run-length code.. leading zeros are significant
    char cur;
};


//char * DTG_huffman_decoder_to_string(const unsigned char * src, int size, int *DstLen);

#endif // _FREESAT_HUFFMAN_DEC_H_
