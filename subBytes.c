//Definitions of subBytes functions and S_box calculation

#include "main.h"
#include "subBytes.h"

#define SUB_BYTES_ALT 2	//which version of subBytes are we using?
#define SUB_BYTE_ALT 2

//#define GENERATE_SBOX	//chooses whether to generate S_box in initialisation.

/**************************/
/*= subBytes entry point =*/
/**************************/
void subBytes(byte *block)
//purpose:	provides subBytes functionality for AES
///requires: s_box be globally defined.
{
	if(debug_level > 0)
		printf("\n.:Sub Bytes:.\n");
	
	#if SUB_BYTES_ALT == 1
	subBytes_1(block);
	#elif SUB_BYTES_ALT == 2
	subBytes_2(block);
	#endif
}

void inv_subBytes(byte *block)
{
	if(debug_level > 0)
		printf("\n.:inv Sub Bytes:.\n");
	
	#if SUB_BYTES_ALT == 1
	inv_subBytes_1(block);
	#elif SUB_BYTES_ALT == 2
	inv_subBytes_2(block);
	#endif
}

byte subByte(byte data)
{
	#if SUB_BYTE_ALT ==1
	return subByte_1(data);
	#elif SUB_BYTE_ALT==2
	return subByte_2(data);
	#endif
}

byte inv_subByte(byte data)
{
	#if SUB_BYTE_ALT ==1
	return inv_subByte_1(data);
	#elif SUB_BYTE_ALT==2
	return inv_subByte_2(data);
	#endif
}

/*********************************************/
/**             S box Config                **/
/*********************************************/
#ifndef GENERATE_SBOX
//taken from Wikipedia
byte s_box[256] = 
	 {
		0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
		0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
		0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
		0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
		0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
		0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
		0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
		0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
		0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
		0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
		0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
		0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
		0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
		0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
		0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
		0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	 };
#else
	//declare variables
	byte s_box[256];
	//declare functions:
#endif

//Inverse S_box
#ifndef GENERATE_SBOX
//taken from Wikipedia
 byte inv_s_box[256] = 
 {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
 };
#else
	//declare variables
	byte inv_s_box[256];
	//declare functions:
	
#endif


//Initialisation function:
void init_sboxs()
//purpose: initialise the sboxs (which are globals, so pointers don't have to be passed.
{
	#ifdef GENERATE_SBOX	//only needs to be initalised if we're generating them.
	int x;
	for(x=0;x<256;x++)
	{
		s_box[x]=subByte(x);
		inv_s_box[x] =inv_subByte(x);
	}
	
		
	#endif
}

/************/

/*1*/
void subBytes_1(byte *block)
//this version uses the stored lookup tables to determine byte substitution
{
	unsigned char x;
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block[x]= s_box[block[x]];
	}
}
void inv_subBytes_1(byte *block)
{
	unsigned char x;
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block[x]= inv_s_box[block[x]];
	}
}

byte subByte_1(byte data)
{
	return s_box[data];
}

byte inv_subByte_1(byte data)
{
	return inv_s_box[data];
}



/*2*/
//these versions substitute individual bytes
void subBytes_2(byte *block)
{
	unsigned char x;
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block[x]= subByte_2(block[x]);
	}
}


void inv_subBytes_2(byte *block)
{
	unsigned char x;
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block[x]= inv_subByte_2(block[x]);
	}

}


byte subByte_2(byte data)
{
	// create integers and bytes for 
	byte pol_byte, 
	     iso_data,
	     iso_invert_data;	

	//assign data to byte storage
	pol_byte = data;

    //call isomorphic transformation
	iso_data = iso_transform(pol_byte);
	if(debug_level>3)
		printf("iso data= 0x%2x\n",iso_data);
	
	//store the inverted isomoprhic value into a byte of data
	iso_invert_data = Multiplicative_Inverse(iso_data);
	if(debug_level>3)
		printf("iso_invert_data= 0x%2x\n",iso_invert_data);
	
	// do the inverse isomorphic and the affine transformation
	data = inverse_iso_affine(iso_invert_data);
	if(debug_level>2)
		printf("byte substitution= 0x%2x\n",data);
			
	//return the transformed subByte data value back to the point from which it was called
	return data;
}

byte inv_subByte_2(byte data)
{
	// create integers and bytes for 
	byte pol_byte, 
	     iso_data,
	     iso_invert_data;	

	//assign data to byte storage
	pol_byte = data;

    //call isomorphic transformation
	iso_data = iso_inverse_affine(pol_byte);
	if(debug_level>3)
		printf("iso data= 0x%2x\n",iso_data);
		
	//store the inverted isomoprhic value into a byte of data
	iso_invert_data = Multiplicative_Inverse(iso_data);
	if(debug_level>3)
		printf("iso_invert_data= 0x%2x\n",iso_invert_data);
	
	// do the inverse isomorphic and the affine transformation
	data = inverse_iso_transform(iso_invert_data);
	if(debug_level>2)
		printf("byte substitution= 0x%2x\n",data);

	//return the transformed subByte data value back to the point from which it was called
	return data;
}

/*********************************************************/
//extra functions for Sub Byte calaculation

byte Multiplicative_Inverse (byte data){
	
		byte low4_byte,
	     high4_byte,
	     high,
	     low,
	     low_store,
	     invert;
	
	// converts the lower 4 bits into byte data
	low4_byte = (data & 0x0F);
	//converts the higher 4 bits into byte data
	high4_byte = (data & 0xF0)>>4;
    // square the top 4 bits
	high = GF24_Squared(high4_byte);
	// after squaring, times top 4 bits by lamba
	high = Lamba_Multiplication(high);
	// add together the top 4 bits and bottom 4 bits
	low = (low4_byte ^ high4_byte);
	//store this low value for multiplication later
	low_store = low;
	// multiply orignal bottome 4 bits by the XOR value of top and bottom
	low = GF24_Mutiplication(low4_byte, low);
	//XOR the top and the bottom to form inverter input
	invert = high ^ low;
	// call inversion of 4 bits data input
	invert = GF24_Inversion (invert);
	// call the two multipliers
	high = GF24_Mutiplication (invert, high4_byte);
	low  = GF24_Mutiplication (invert, low_store);
	
	//store data in one byte variable
	data = (high<<4) ^ low;
	return data;
}

byte iso_transform (byte data){

	unsigned char x,A,B;

	//array for storing values
	byte q[8] = {0};
	byte iso_array[8];

	//following puts individual bits into an array from the byte of data
	for(x=0;x<8;x++){
		q[x] = 	(data>>x) & 0x01; // poly_array[0] = LSB of data
	}


	//collect repetative terms

    iso_array[0] = q[0] ^ q[1] ^ q[6];
	iso_array[1] = q[1] ^ q[4] ^ q[6];
	iso_array[2] = q[1] ^ q[2] ^ q[3] ^ q[4] ^ q[7];
	iso_array[3] = q[1] ^ q[2] ^ q[6] ^ q[7];
	iso_array[4] = q[1] ^ q[2] ^ q[3] ^ q[5] ^ q[7];
	iso_array[5] = q[2] ^ q[3] ^ q[5] ^ q[7];
	iso_array[6] = q[1] ^ q[2] ^ q[3] ^ q[4] ^ q[6] ^ q[7];
	iso_array[7] = q[5] ^ q[7];

    data = 0;
	for(x=0;x<8;x++){
		data ^= ( iso_array[x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;

}

byte inverse_iso_transform (byte data){

	unsigned char x,A,B;

	//array for storing values
	byte q[8] = {0};
	byte pol_array[8];

	//following puts individual bits into an array from the byte of data
	for(x=0;x<8;x++){
		pol_array[x] = 	(data>>x) & 0x01; // poly_array[0] = LSB of data
	}

	//Iso morphic transformation
	for (x=0;x<8;x++){
		q[x] = pol_array[x];
	}
	//collect repetative terms
	A = q[1] ^ q[2];
	B = q[4] ^ q[5];

	pol_array[0] = q[0] ^ q[2] ^ B    ^ q[6];
	pol_array[1] = B;
	pol_array[2] = A    ^ q[3] ^ q[4] ^ q[7];
	pol_array[3] = A    ^ q[3] ^ B;
	pol_array[4] = A    ^ B    ^ q[6];
	pol_array[5] = q[1] ^ q[5] ^ q[6];
	pol_array[6] = q[2] ^ q[6];
	pol_array[7] = q[1] ^ q[5] ^ q[6] ^ q[7];

	data=0;
	for(x=0;x<8;x++){
		data ^= ( pol_array[x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;

}

byte inverse_iso_affine(byte data){

	unsigned char x,A;

	//array for storing values
	byte q[8] = {0};
	byte pol_array[8];

	//following puts individual bits into an array from the byte of data
	for(x=0;x<8;x++){
		pol_array[x] = 	(data>>x) & 0x01; // poly_array[0] = LSB of data
	}

	//Iso morphic transformation
	for (x=0;x<8;x++){
		q[x] = pol_array[x];
	}

	//collect repetative terms

	A = q[0] ^ q[1];

	pol_array[0] = A    ^ q[2] ^ q[6] ^ q[7] ^ 1;
	pol_array[1] = q[0] ^ q[7] ^ 1;
	pol_array[2] = q[0] ^ q[2] ^ q[3] ^ q[4] ^ q[5] ^ q[6] ^ 0;
	pol_array[3] = A    ^ q[2] ^ 0;
	pol_array[4] = A    ^ q[4] ^ q[7] ^ 0;
	pol_array[5] = q[2] ^ q[7] ^ 1;
	pol_array[6] = q[4] ^ q[5] ^ q[6] ^ q[7] ^ 1;
	pol_array[7] = q[2] ^ q[3] ^ q[7] ^ 0;

	data=0;
	for(x=0;x<8;x++){
		data ^= ( pol_array[x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;
}



byte iso_inverse_affine(byte data){

		unsigned char x,A,B;

	//array for storing values
	byte q[8] = {0};
	byte iso_array[8];

	//following puts individual bits into an array from the byte of data
	for(x=0;x<8;x++){
		iso_array[x] = 	(data>>x) & 0x01; // poly_array[0] = LSB of data
	}

	//Iso morphic transformation
	for (x=0;x<8;x++){
		q[x] = iso_array[x];
	}

	//collect repetative terms

	iso_array[0] = q[2] ^ q[6] ^ q[7] ^ 1;
	iso_array[1] = q[1] ^ q[3] ^ q[5] ^ 0;
	iso_array[2] = q[1] ^ q[2] ^ q[5] ^ q[6] ^ q[7] ^ 1;
	iso_array[3] = q[5] ^ q[7] ^ 1;
	iso_array[4] = q[3] ^ q[4] ^ q[5] ^ 1;
	iso_array[5] = q[0] ^ q[4] ^ q[5] ^ q[6] ^ 1;
	iso_array[6] = q[0] ^ q[1] ^ q[2] ^ q[3] ^ q[6] ^ q[7] ^ 1;
	iso_array[7] = q[1] ^ q[2] ^ q[6] ^ q[7] ^ 0;

	data=0;
	for(x=0;x<8;x++){
		data ^= ( iso_array[x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;
}


byte GF24_Squared (byte data){

	unsigned char x;

	byte q[4] = {0};
	byte iso_high4[4];

	//assign values to temporary array
	for (x=0;x<4;x++){
		iso_high4[x] = (data>>x)& 0x01;
		q[x] = iso_high4[x];
	}
    //squared function:
	iso_high4 [0] = (q[0] ^ q[1]) ^q[3];
	iso_high4 [1] = q[1] ^ q[2];
	iso_high4 [2] = q[2] ^ q[3];
	iso_high4 [3] = q[3];

	//pol_high4 now contains the squared high values
	//convert pol_high4 back to a byte
	data=0; 
	for(x=0;x<4;x++){
		data ^= ( iso_high4 [x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;

}

byte GF24_Mutiplication(byte data1, byte data2){

	byte data1_high,
	     data1_low,
	     data2_high,
	     data2_low,
	     high,
	     mid,
	     low,
	     data;

	//split data into high and low 2 bits
	data1_high = (data1 & 0x0C)>>2;
	data1_low  = data1 & 0x03;
	data2_high = (data2 & 0x0C)>>2;
	data2_low  = data2 & 0x03;

	//calculate the additions before calling GF2 multiplier
	high = (data1_high ^ data1_low);
	low  =  (data2_high ^ data2_low);

	///call multipliers providing values before hand and storing in values for later use
	mid  = GF2_Multiplication(high, low);
	high = GF2_Multiplication(data1_high, data2_high);
	low  = GF2_Multiplication(data1_low, data2_low);

	//multiplt the top output by delta
	high = delta_multiplication(high);

	//XOR values to get the top and bottom 2 bit outputs
	mid ^=low;
	low ^=high;

	//shift middle left 2 places so it becomes the top 2 bits for a 4 bit output
	mid = mid<<2;

    //XOR values to add the two together for a 4 bit data output
	data = mid ^ low;

	return data;

}

byte Lamba_Multiplication(byte data){

	unsigned char x;

	byte q[4] = {0};
	byte iso_high4[4];

	//assign values to temporary array
	for (x=0;x<4;x++){
		iso_high4[x] = (data>>x) & 0x01;
		q[x] = iso_high4[x];
	}

	//calculate the lamba multiplication for the irreducible polynomial
	iso_high4 [0] = q[2];
	iso_high4 [1] = q[3];
	iso_high4 [2] = (q[1] ^ q[3]) ^ (q[0] ^ q[2]);
	iso_high4 [3] = q[0] ^ q[2];

	//pol_high4 now contains the value after the lamba multiplication
	//convert back to byte format
	data=0;
	for(x=0;x<4;x++){
		data ^= ( iso_high4 [x]<< x)& 0xFF; // converts the lower 4 bits into byte data
	}

	return data;



}

byte delta_multiplication(byte data){

	byte high,
		 low,
		 lowop;

	high = (data & 0x02)>>1;
	low  = data & 0x01;

	lowop = high;
	high ^=low;

	data = (high<<1) ^ lowop;

	return data;


}

byte GF2_Multiplication(byte data1, byte data2){

		byte data1_high,
	     data1_low,
	     data2_high,
	     data2_low,
	     high,
	     mid,
	     low,
	     data;

	//split data into high and low 1 bits
	data1_high = (data1 & 0x02)>>1;
	data1_low  = data1 & 0x01;
	data2_high = (data2 & 0x02)>>1;
	data2_low  = data2 & 0x01;

	//calculate the additions before AND gates
	high = (data1_high ^ data1_low);
	low  =  (data2_high ^ data2_low);

	///call multipliers providing values before hand and storing in values for later use
	mid  = high & low;
	high = data1_high & data2_high;
	low  = data1_low & data2_low;


	//XOR values to get the top and bottom 1 bit outputs
	mid ^=low;
	low ^=high;

    //XOR values to add the two together for a 4 bit data output
	data = (mid<<1) ^ low;

	return data;

}

byte GF24_Inversion(byte data){

	// inclusive function parameters
	unsigned char x;

    // array for use for logic manipulation
	byte q[4] = {0};
	byte Inv_array[4];

 	//move data individual bits into temp array
	for(x=0;x<4;x++){
		q[x] = (data>>x) & 0x01;
	}

	// the following is simplified logic to invert a GF24 polynomial
	// MSB Inverted Bit 
	Inv_array [3] = q[3] ^ (q[3] & q[2] & q[1]) ^ (q[3] & q[0]) ^ q[2];
	Inv_array [2] = (q[3] & q[2] & q[1]) ^ (q[3] & q[2] & q[0]) ^ q[2] ^ (q[3] & q[0]) ^ (q[2] & q[1]);
	Inv_array [1] = q[3] ^ (q[3] & q[2] & q[1]) ^ (q[3] & q[1] & q[0]) ^ q[2] ^ (q[2] & q[0]) ^ q[1];
	Inv_array [0] = (q[3] & q[2] & q[1]) ^ (q[3] & q[2] & q[0]) ^ (q[3] & q[1]) ^ (q[3] & q[1] & q[0]) ^
	 				(q[3] & q[0]) ^ q[2] ^ (q[2] & q[1]) ^ (q[2] & q[1] & q[0]) ^ q[1] ^ q[0];


	data=0;
	for (x=0;x<4;x++){
		data ^= (Inv_array [x]<<x) & 0xFF;
	}

	return data;

}
