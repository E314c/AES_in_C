//Key schedule File
#include "main.h"


//defines
#define RCON_ROW_SIZE 10
#define RCON_COLUMN_SIZE 4
#define RCON_TABLE //define to use a LUT for the rcon value, uncomment to use shifted bits for rcon
//globals:
#ifdef RCON_TABLE
    byte rcon[40] =
 	{
   	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
   	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 	};
#endif
#ifndef RCON_TABLE
static int rcon; //rcon value
#endif
static int key_count=0;		//used to count which key we're on
static int i=0;     //for loop counter
static byte temp=0; //holding values when shifting
byte rotword[BLOCK_ROW_SIZE]; //4x1 block
byte new_key[BLOCK_SIZE];     //4x4 block


void get_next_key(byte *block)
//purpose: put next round key into the provided array space
{
	if(debug_level > 0)
		printf("\n.:KeyScheduler:.\n");
	if(debug_level > 2)
		printf("Generating key: %2d\n",key_count+1);
		
		
	
	//rightmost column of key copied
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
		rotword[i] = block[(i*BLOCK_ROW_SIZE)+(BLOCK_ROW_SIZE-1)];
	}
	
	if(debug_level>3)
	{
		printf("printing rotword\n");
		for(i=0;i<BLOCK_ROW_SIZE;i++)
		{
			printf("rotword[%d]=%0x\n",i,rotword[i]);                 
		}
	}
	
	//top entry of copied column moved to bottom of column, all others shifted up
	temp = rotword[0];
	
	for(i=0;i<BLOCK_ROW_SIZE-1;i++)
	{
		rotword[i]=rotword[i+1];
	}
	rotword[BLOCK_ROW_SIZE-1]=temp;
	
	if(debug_level>4)
	{
		printf("printing shifted rotword\n");
		for(i=0;i<BLOCK_ROW_SIZE;i++)
		{
			printf("rotword[%d]=%0x\n",i,rotword[i]);                 
		}
	}
	
	//do subBytes on the column
	subBytes(rotword);
	if(debug_level>3)
	{
		printf("printing subbytes rotword\n");
		for(i=0;i<BLOCK_ROW_SIZE;i++)
		{
			printf("rotword[%d]=%0x\n",i,rotword[i]);                 
		}
	}
	
	//xor with leftmost column of key and rcon(4) (first column of rcon)
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
        #ifdef RCON_TABLE
        rotword[i]^=(block[i*BLOCK_ROW_SIZE]^rcon[(i*RCON_ROW_SIZE)+key_count]);
        #endif
        #ifndef RCON_TABLE
        if(i=0){
            rcon=(1<<key_count);
        }
        else{
        rcon=0;
        }
        rotword[i]^=block[i*BLOCK_ROW_SIZE]^rcon;
        #endif
	}
	if(debug_level>3)
	{
		printf("printing xor'd rotword\n");
		for(i=0;i<BLOCK_ROW_SIZE;i++)
		{
			printf("rotword[%d]=%0x\n",i,rotword[i]);                 
		}
	}
	
	//set this as first column of first roundkey
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
		new_key[i*BLOCK_ROW_SIZE]=rotword[i];
	}
	
	//xor first column of roundkey with second column of key
	//this is second column of roundkey
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
		new_key[(i*BLOCK_ROW_SIZE)+1]=block[(i*BLOCK_ROW_SIZE)+1]^new_key[i*BLOCK_ROW_SIZE];
	}

	
	//xor second column of roundkey with third column of key
	//this is third column of roundkey
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
		new_key[(i*BLOCK_ROW_SIZE)+2]=block[(i*BLOCK_ROW_SIZE)+2]^new_key[(i*BLOCK_ROW_SIZE)+1];
	}
	
	//xor third column of roundkey with fourth column of key
	//this is fourth column of the roundkey
	for(i=0;i<BLOCK_ROW_SIZE;i++)
	{
		new_key[(i*BLOCK_ROW_SIZE)+3]=block[(i*BLOCK_ROW_SIZE)+3]^new_key[(i*BLOCK_ROW_SIZE)+2];
	}
	
	if(debug_level>3)
	{
		//print new key
		printf_block(new_key, "New_key:");
	}
	
	//write new key back to block
	for(i=0;i<BLOCK_SIZE;i++)
	{
		block[i]=new_key[i];
	} 
	
	
	//ROUNDKEY COMPLETE
	key_count++;
	
}

void get_decrypt_key(byte *block)
{
	if(debug_level>0)
    	printf("\n.:Generating Decrypt Key %d:.\n", AES_ROUNDS-key_count);
	//new_key columns 1-3 made of block column i XOR block column i-1
    for(i=0;i<BLOCK_ROW_SIZE;i++){
	   new_key[(BLOCK_ROW_SIZE*i)+3]=block[(BLOCK_ROW_SIZE*i)+3]^block[(BLOCK_ROW_SIZE*i)+2];
    }
    for(i=0;i<BLOCK_ROW_SIZE;i++){
	   new_key[(BLOCK_ROW_SIZE*i)+2]=block[(BLOCK_ROW_SIZE*i)+2]^block[(BLOCK_ROW_SIZE*i)+1];
    }
    for(i=0;i<BLOCK_ROW_SIZE;i++){
	   new_key[(BLOCK_ROW_SIZE*i)+1]=block[(BLOCK_ROW_SIZE*i)+1]^block[(BLOCK_ROW_SIZE*i)];
    }
    
    //forward = take W(i-1) column (column 3 of new_key) (rotword)
    //          top to bottom, shift all up
    //          subBytes
    //          XOR with W(i-4) column (column 0 of new_key) and rotword
    
    //new_key column 0 generation
    //copy block, we want the rotword which is made using the final column of new_key
    byte copy_block[BLOCK_SIZE];
    for(i=0;i<BLOCK_ROW_SIZE;i++)
    {
    	copy_block[i*BLOCK_ROW_SIZE]=new_key[i*BLOCK_ROW_SIZE+3];
	}
	
    //moving the bottom element of the rotword to the top and shift all down one
    temp=copy_block[0];
    
    for(i=0;i<BLOCK_ROW_SIZE-1;i++){
        copy_block[i*BLOCK_ROW_SIZE]=copy_block[(i+1)*BLOCK_ROW_SIZE];
    }
    
    copy_block[3*BLOCK_ROW_SIZE]=temp;

    //sub-bytes on the rotword
    subBytes(copy_block);
    
    //column 0 made of sub-byted & shifted rotword XOR with column 0 of the block XOR with specified rcon 
    for(i=0;i<BLOCK_ROW_SIZE;i++){
        #ifdef RCON_TABLE
            new_key[i*BLOCK_ROW_SIZE]=copy_block[i*BLOCK_ROW_SIZE]^block[i*BLOCK_ROW_SIZE]^rcon[(i*RCON_ROW_SIZE)+key_count-1];
        #endif
        #ifndef RCON_TABLE
        if(i=0){
            rcon=(1<<(key_count-1));
        }
        else{
        rcon=0;
        }
        new_key[i*BLOCK_ROW_SIZE]=copy_block[i*BLOCK_ROW_SIZE]^block[i*BLOCK_ROW_SIZE]^rcon;
        #endif
    }
	
	if(debug_level>3)
	{
		//print new key
		printf_block(new_key, "Decrypt key:");
	}
	
	//write new key back to block
	for(i=0;i<BLOCK_SIZE;i++)
	{
		block[i]=new_key[i];
	} 
	
	//next_ROUNDKEY COMPLETE
	key_count--;
}
