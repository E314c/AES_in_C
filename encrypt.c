/*Encryption Module*/
/*


*/

//includes:
#include "main.h"

void encrypt_block(byte *data, byte *key)
{
	//temps and loops:
	unsigned char x;
	char str_buff[128];
	
	//initial addRoundKey
	addRoundKey(data,key);
	
	for(x=0; x<AES_ROUNDS; x++)
	{
		printf("\n");

		if(debug_level > 0)
		{
			printf("\n------------------\n");
			sprintf(str_buff,"Data Block, beginning of round %d", x);
			printf_block(data, str_buff);
		}
		
		//process/set key for this round
		get_next_key(key);
		
		//encryption process:
		//subBytes
		subBytes(data);
		if(debug_level > 1)
			printf_block(data, "Data after subBytes");
		
		
		//shiftRows
		shiftRows(data);
		if(debug_level > 1) 
			printf_block(data, "Data after shiftRows");
		
		if(x<(AES_ROUNDS-1))
		{
			//mixColumns
			mixColumns(data);
			if(debug_level > 1)
				printf_block(data, "Data after mixColumns");
		}
		
		//addRoundKey
		addRoundKey(data,key);
	}
}
