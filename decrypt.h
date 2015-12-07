#ifndef DECRYPTION_H_	//make sure it's only included once.
	#define DECRYPTION_H_	
	//"main" for this file:
	void decrypt_block(byte *data, byte *key);
	
	//functions
	void inv_subBytes(byte *block);		//defined in subBytes.c
	void inv_shiftRows(byte *block);	//defined in shiftRows.c
	void inv_mixColumns(byte *block);	//defined in mixColumns.c
#endif
