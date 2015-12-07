//init functions
void init_sboxs();

//available alternatives:
void subBytes_1(byte *block);
void inv_subBytes_1(byte *block);
void inv_subBytes(byte *block);
byte subByte(byte data);
byte inv_subByte(byte data);
byte subByte_1(byte data);
byte inv_subByte_1(byte data);
void subBytes_2(byte *block);
void inv_subBytes_2(byte *block);
byte subByte_2(byte data);
byte inv_subByte_2(byte data);

//extra for SubByte Generation
byte Multiplicative_Inverse (byte data);
byte iso_transform (byte data);
byte inverse_iso_transform (byte data);
byte inverse_iso_affine(byte data);
byte iso_inverse_affine(byte data);
byte GF24_Squared (byte data);
byte GF24_Mutiplication(byte data1, byte data2);
byte Lamba_Multiplication(byte data);
byte delta_multiplication(byte data);
byte GF2_Multiplication(byte data1, byte data2);
byte GF24_Inversion(byte data);



