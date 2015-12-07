#AES example in C

This project is for reference, showing how to process AES encryption.

Flags for executable
-i <input_file_path>	Use the supplied text file as the input data to the system (see example data for file layout)
-o <output_file_path>	Use the supplied file path to output the data from the operation #Non_functional#
-e						Run the encryption process
-d						Run the decryption process
-D <debug_level>		Set the process debug level, affecting what data is printed to STDOUT

To test, run batch files found in /tests/.
They will run encryption/decryption with standard data sets and open the results. Standard debug level for these tests is 2, though you can change debug level by passing debug level as an arguement to the batch file.

If no file input is specified, default data is used:
Depending on define in main.h, default data is either based on [FIPS data](http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf) set 
or it is set is based on [this animation](http://hercules.shef.ac.uk/eee/teach/resources/eee6225/files/Rijndael_Animation_2004.swf) which is also available on [youtube](https://www.youtube.com/watch?v=mlzxpkdXP58), so check them for what the data should look like.



This project has been built in [Dev-C++](http://sourceforge.net/projects/orwelldevcpp/) using GCC.