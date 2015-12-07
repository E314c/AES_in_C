//AES Implementation
#include "main.h"

//global variables:
extern byte s_box[256];
extern byte inv_s_box[256];

//Debug level
int debug_level = 0;

/*=== MAIN ====*/
int main(int argc, char *argv[])
{
	/*Initialise internals*/
	//datas and key storage:
	byte data[BLOCK_SIZE], key[BLOCK_SIZE];
	
	//sysdata
	unsigned char mode ='e';
	char *in_file_str = 0, *out_file_str = 0;
	//temps and loops:
	int x;
	char *junk_p;
	
	//s_box:
	init_sboxs();
	
	//go through the arguments for setup:
	for(x=1;x<argc;x++)	//ignore arg_0 as that's just the filename
	{
		if(argv[x][0]=='-')
		{
			switch(argv[x][1])
			{
				case 'e':
					mode = 'e';	//set encryption mode
					break;
				case 'd':
					mode = 'd';	//set decryption mode
					break;
				
				case 'i':	//input flag
					in_file_str = argv[x+1];	//file is the next arguement.
					x++;		//increment counter to ignore next argument as we just used it.
					break;
					
				case 'o':	//output flag
					out_file_str = argv[x+1];	//file is the next arguement.
					x++;		//increment counter to ignore next argument as we just used it.
					break;
					
				case 'D':	//debug level
					debug_level= strtol(argv[x+1],&junk_p,10);
					x++;
					break;
					
				default:
					break;
			}
		}
	}
	
	//let them know the debug level set
	if(debug_level>0)
		printf("---Debug level---\n       %3d\n",debug_level);
	
	//if file str has been set, get the data, else default data.
	if(in_file_str)
	{
		printf("Getting data from %s\n",in_file_str);
		get_data(in_file_str, data, key);
	}
	else
	{
		printf("Using default Data\n");
		set_default_data(data, key);
	}
	
	//display starting Block and Key.
	printf_block(data, "Initial Block");
	printf("\n");
	printf_block(key, "Initial Key");
	printf("---------------------------\n");
	
	if(mode=='e')
	{
		//encryption process:
		encrypt_block(data, key);
	}
	else if(mode =='d')
	{
		//decryption process:
		decrypt_block(data, key);
	}
	
	//display final Block and Key.
	printf_block(data, "Final Block");
	printf("\n");
	printf_block(key, "Final Key");
	printf("---------------------------\n");
	
	
	//output to file:
	/**To do**/
}

/******************/
void addRoundKey(byte *block, byte *key)
{
	if(debug_level > 0)
		printf("\n.:AddRoundKey:.\n");
		
	unsigned char x;
	
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block[x]^=key[x];
	}
}


/***********/
//extra functions

byte gf_multiplication(byte A,byte B)
//purpose: provides Gallious field multiplication
//requires: GF_IR_POLY (the irreducible polynomial) by defined.
{
	char i;
	ext_byte output=0;
	
	for(i=8;i>=0;i--)
	{
		if((B>>i)&0x01)//check bit
			output ^= A;	//add A to output.
			
		if(output&0x100) 	//check MSB of Output
			output ^= GF_IR_POLY;	//mod P
		
		if(i!=0)
			output= output << 1;	//left shift output:
	}
	
	if(debug_level > 4)
		printf("Multiplication of %2x and %2x is %2x\n", A, B, (output&0x1FF));
	
	return (byte)(output&0xFF);
}

byte gf_mult_and_sum(byte *A, byte *B, unsigned char length)
//purpose: multiply and sum for matrix dot product
{
	unsigned char x;
	ext_byte output = 0;
	
	for(x=0;x<length;x++)
	{
		output^=gf_multiplication(A[x],B[x]); //sum the output up
		if(debug_level > 4)
			printf("Mult and sum: Sum step %d is %2x\n", x,(output&0x1FF));
	}
	
	
	return (byte)(output&0xFF);
}

void matrix_transpose(byte *matrix, unsigned char row_size)
//purpose: transpose a square matrix
{
	unsigned char x,y,skip=1;	//skip starts at 1 as there is no swap for first value of array.
	byte temp;
	
	if(debug_level > 4)
		printf_block(matrix, "Pre-transpose");
	
	
	//for each collumn
	for(x=0;x<row_size;x++)
	{
		//for each cell, skipped non-swapping ones.
		for(y=skip;y<row_size;y++)
		{
			//full function is ((pos%row_size*)row_size) + (pos/row_size))
			#define SWAP_VAR (( y * row_size) + x )		
			//y is already pos%row_size, x is already (pos/row_size)
			
			if(debug_level > 4)
			printf("Swapping pos %d with %d\n",y+(x*row_size),SWAP_VAR);
			
			//swap the values:
			temp=matrix[y+(x*row_size)];
			matrix[y+(x*row_size)]=matrix[SWAP_VAR];
			matrix[SWAP_VAR]=temp;
		}
		skip++;	//increase the skip for next row.
	}
	
	if(debug_level > 4)
		printf_block(matrix, "Post-transpose");
	
}
