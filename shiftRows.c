//This file has (or will have) multiple example implementations of shiftRows functions
#include "main.h"
#include "shiftRows.h"


#define SHIFT_ROWS_ALT 1



void shiftRows(byte *block)
{
	if(debug_level > 0)
		printf("\n.:Shift Rows:.\n");
	
	#if SHIFT_ROWS_ALT==1
	SR_1(block,'n');
	#endif
}

void inv_shiftRows(byte *block)
{
	if(debug_level > 0)
		printf("\n.:inv_Shift Rows:.\n");
	
	#if SHIFT_ROWS_ALT==1
	SR_1(block,'i');
	#elif SHIFT_ROWS_ALT==2
	SR_2(block);
	#endif
}
/***********************************************************************/

//alternative implementations:

/* 1 */
void SR_1(byte *block, char type)
{
	unsigned char x,y;
	
	for(x=0;x<BLOCK_ROW_SIZE;x++)
	{
		//shift rows account determined by current row.
		for(y=0;y<x;y++)
		{
			if(type=='i')	//if inverse shift.
				i_shift_row(block+(x*BLOCK_ROW_SIZE), BLOCK_ROW_SIZE);
			else
				shift_row(block+(x*BLOCK_ROW_SIZE), BLOCK_ROW_SIZE);
		}
	}
}

/*2*/

void SR_2a(byte *block, unsigned char row_size, char positions)
{
	byte temp;
	unsigned char x;
	
	#warning "not yet implemented"
}

void SR_2(byte *block, char mult)
//inputs: block to shift, 1 for normal shift, -1 for inverse
{
	
	//make sure mult is correct value:
	if(mult!=1||mult!=-1)
		return;
	
	unsigned char x,y;
	
	for(x=0;x<BLOCK_ROW_SIZE;x++)
	{
		//shift rows account determined by current row.
		SR_2a(block+(x*BLOCK_ROW_SIZE), BLOCK_ROW_SIZE,(x*mult));
	}

}
/**************/
//misc functions:
void shift_row(byte *data, unsigned char row_size)
//shift row by one positon to the left
{
	byte temp;
	unsigned char x;
	
	//store the value of the first byte
	temp=data[0];
	
	//cycle through data, shifting as you go
	for(x=0;(x+1)<row_size;x++)
	{
		data[x]=data[x+1];
	}
	//last byte (after loop exits) is assigned temp byte from start.
	data[x]=temp;
}

void i_shift_row(byte *data, unsigned char row_size)
//shift row one position right
{
	byte temp;
	unsigned char x;
	
	//store the value of the first byte
	temp=data[row_size-1];
	
	//cycle through data, shifting as you go
	for(x=(row_size-1); x>0 ;x--)
	{
		data[x]=data[x-1];
	}
	//last byte (after loop exits) is assigned temp byte from start.
	data[x]=temp;
}
