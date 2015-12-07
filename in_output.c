//In_output.c
/*
This file is here to provide input/output handling for the AES test system.
*/
#include "main.h"

#define IS_VALID_HEXCHAR(x) (x>='0'&&x<='9')||(x>='A'&&x<='F')||(x>='a'&&x<='f')
#define IS_DELIMITER(x)	( x==' ' || x=='\n' || x=='\t')

//local-only function prototypes:
byte char_to_hex(char character);

void get_data(char *string, byte *data, byte *key)
//purpose: extract the data and key from the file supplied
{
	FILE *file;
	int x,y, i=0;
	byte *pointer = data;
	//open the file
	file = fopen(string,"r");
	
	/******FILE HANDLING*******/
    while  ( ( x = fgetc( file ) ) != EOF )
    {
		if (IS_DELIMITER(x))
        {
        	i++;
        	//treat multiple delimiters as single delimiter:
        	while(IS_DELIMITER(x) && (x != EOF ))
        	{
        		x = fgetc(file);
			}
		}
        if(i>=BLOCK_SIZE) //reached the end of block
        {
        	i=0;
			if(pointer==data)	//finished writing to data, now write to key
        		pointer=key;
        	else
        		break;	//break out of while loop
		}
        if(IS_VALID_HEXCHAR(x))
        {
        	
        	//if suitable hex value
        	pointer[i]=char_to_hex((char)x)<<4;		
        	x = fgetc(file);	//get next character
        	pointer[i]+=char_to_hex((char)x);
		}
    }
	//close the file
	fclose(file);
}

void write_data(char *file_str, byte *data)
//purpose: append the data to the given file.
{
	FILE *file;
	
	file = fopen(file_str,"a");
	
	
	fclose(file);
}

void printf_block_xy(byte *block,char *name, int x_size , int y_size)
{
	unsigned char x, y;
	
	printf("\"%s\" :\n",name);
	for(x=0;x<x_size;x++)
	{
		printf("| ");
		for(y=0;y<y_size;y++)
		{
			printf("%2x | ",block[(x*x_size)+y]);
		}
		printf("\n");
	}
}

void printf_block(byte *block,char *name)
{
	printf_block_xy(block, name, BLOCK_ROW_SIZE , BLOCK_ROW_SIZE);	 
}



#ifdef FIPS_DEFAULT_DATA
#warning "FIPS data strings are read down columns, not along rows."
char def_data[BLOCK_SIZE]={
0x00, 0x44, 0x88, 0xcc,
0x11, 0x55, 0x99, 0xdd, 
0x22, 0x66, 0xaa, 0xee, 
0x33, 0x77, 0xbb, 0xff
};
char def_key[BLOCK_SIZE]={
0x00 , 0x04 , 0x08 , 0x0c , 
0x01 , 0x05 , 0x09 , 0x0d , 
0x02 , 0x06 , 0x0a , 0x0e , 
0x03 , 0x07 , 0x0b , 0x0f
};
#else
#warning "using default data from animation"
char def_data[BLOCK_SIZE]={
0x32, 0x88, 0x31, 0xe0,
0x43, 0x5a, 0x31, 0x37, 
0xf6, 0x30, 0x98, 0x07, 
0xa8, 0x8d, 0xa2, 0x34
};
char def_key[BLOCK_SIZE]={
0x2b, 0x28, 0xab, 0x09, 
0x7e, 0xae, 0xf7, 0xcf, 
0x15, 0xd2, 0x15, 0x4f, 
0x16, 0xa6, 0x88, 0x3c
#endif


void set_default_data(byte *data, byte *key)
{
	unsigned char x;
	for(x=0;x<BLOCK_SIZE;x++)
	{
		data[x]	= def_data[x];
		key[x]	= def_key[x];
	}
}


byte char_to_hex(char character)
{
	if(character>='0'&&character<='9')
		character-='0';
	else if(character>='A'&&character<='F')
		character-=('A'-10);
	else if(character>='a'&&character<='f')
		character-=('a'-10);
	else
		return 0;
		
	return (byte) character;
}
