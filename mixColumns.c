#include "main.h"

#define MIX_COL_ALT 1

//mixMatrix definitions:
byte MixMatrix[BLOCK_SIZE]=	{	2,3,1,1,
								1,2,3,1,
								1,1,2,3,
								3,1,1,2};
							
byte InvMixMatrix[BLOCK_SIZE]={	14, 11, 13,  9,
								 9, 14, 11, 13,
								13,  9, 14, 11,
								11, 13,  9, 14};

//alt implementations:
void mixCol_1(byte *block);
void inv_mixCol_1(byte *block);


/*= MixColumns =*/
void mixColumns(byte *block)
{
	if(debug_level > 0)
		printf("\n.:Mix Columns:.\n");
	
	#if MIX_COL_ALT == 1
	mixCol_1(block);
	#endif
	
}
/*= invMixColumns =*/
void inv_mixColumns(byte *block)
{
	if(debug_level > 0)
		printf("\n.:Inverse Mix Columns:.\n");
	
	#if MIX_COL_ALT == 1
	inv_mixCol_1(block);
	#endif
}

/***********************************************************************/

//alternative implementations:

/* 1 */
void mixCol_1a(byte *block, byte *mixer)
{
	byte block_copy[BLOCK_SIZE];
	unsigned char x,y;
	
	//do quick backup of block:
	for(x=0;x<BLOCK_SIZE;x++)
	{
		block_copy[x]=block[x];
	}
	//also transpose it for ease later:
	matrix_transpose(block_copy,BLOCK_ROW_SIZE);
	if(debug_level > 4)
		printf_block(block_copy, "Copy of block (after transpose)");
	
	//mixColumns:
		//for each column:
	for(x=0;x<BLOCK_ROW_SIZE;x++)
	{
		//
		for(y=0;y<BLOCK_ROW_SIZE;y++)
		{
			if(debug_level > 2)
				printf("\nWriting to position: %d \n",(x+(4*y)));
			
			block[x+(4*y)] = gf_mult_and_sum( block_copy+(x*4), mixer+(4*y), BLOCK_ROW_SIZE);
		}
		
	}
	
}
void mixCol_1(byte *block)
{
	mixCol_1a(block, MixMatrix);
}
void inv_mixCol_1(byte *block)
{
	mixCol_1a(block, InvMixMatrix);
}

/*****************************************/
/* 2 */
