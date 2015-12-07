///Build settings

//typedefs:
typedef unsigned char byte;
typedef unsigned int ext_byte;	//extended byte needed for some operations.

//global variables:
extern int debug_level;			//used to set how much debug output

//define default key/encryption block sizes:
#define BLOCK_ROW_SIZE 4
#define BLOCK_SIZE (BLOCK_ROW_SIZE * BLOCK_ROW_SIZE)

//define rounds:
#define AES_ROUNDS 10

#define FIPS_DEFAULT_DATA	//choose whether to use FIPS default data set or animation's default data set


//define the irreducible polynomial used:
#define GF_IR_POLY 0x011B	//this is the polynomial x^8+x^4+x^3+x+1 (specified for AES) [0001 0001 1101]

#include <stdio.h>
#include <stdlib.h>
#include "encrypt.h"	//encryption headers.
#include "decrypt.h"	//decryption header
#include "in_output.h"	//debug input-output
#include "key_schedule.h"	//key scheduling stuff


/***********/
void addRoundKey(byte *block, byte *key);	//defined in main.c
//extra functions

byte gf_multiplication(byte A,byte B);

byte gf_mult_and_sum(byte *A, byte *B, unsigned char length);

void matrix_transpose(byte *matrix, unsigned char row_size);
