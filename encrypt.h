#ifndef ENCRYPTION_H_	//make sure it's only included once.
	#define ENCRYPTION_H_
	
	//"main" for this file:
	void encrypt_block(byte *data, byte *key);
	
	
	//functions
	void subBytes(byte *block);		//defined in subBytes.c
	void shiftRows(byte *block);	//defined in shiftRows.c
	void mixColumns(byte *block);	//defined in mixColumns.c
#endif
