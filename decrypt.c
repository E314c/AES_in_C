/*Decryption Module*/
/*
*/

//includes:
#include "main.h"

void decrypt_block(byte *data, byte *key)
{
	//temps and loops:
	unsigned char x;
	char str_buff[128];

	//first schedule key 10 times
	for(x=0;x<AES_ROUNDS;x++)
	{
		get_next_key(key);
	}
	
	for(x=0; x<AES_ROUNDS; x++)
	{
		
		/*Decryption stages*/
		
		if(debug_level > 0)
		{
			printf("\n------------------\n");
			//print the initial state of this round
			sprintf(str_buff,"Data Block, beginning of round %d", x);
			printf_block(data, str_buff);
		}
		
		//process/set key for this round
		
		
		if(debug_level > 1) 
			printf_block(key, "Key for this round");		
		
		//inv_addRoundKey (which === addRoundKey)
		addRoundKey(data,key);
		if(debug_level > 1) 
			printf_block(data, "Data after addRoundKey");
		
        //inv_mixColumns
		if(x!=0)
		{
	        inv_mixColumns(data);
			if(debug_level > 1 )
				printf_block(data, "Data after inv_mixColumns");
        }
        	
		//inv_shifRows
		inv_shiftRows(data);
		if(debug_level > 1) 
			printf_block(data, "Data after inv_shiftRows");
		
		//subBytes
		inv_subBytes(data);
		if(debug_level > 1)
			printf_block(data, "Data after inv_subBytes");
		
		get_decrypt_key(key);
	}
	addRoundKey(data,key);
}
