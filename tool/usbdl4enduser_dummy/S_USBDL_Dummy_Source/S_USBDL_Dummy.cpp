// S_USBDL_Dummy.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

//
//	Sample code here just to add dummy signature pattern (ex: 256 bytes).
//  Therefore, skip the processing for K2.bin and K3.bin files.
//
#define SIGNATURE_SIZE 256
int main(int argc, char* argv[])
{
	// the program should be given 4 parameters.
	if(argc != 5)
	{
		fprintf(stderr, "ERROR: Argument error!!!");
		return 2;
	}

	string pathEncryptedBin = argv[1];		// encrypting DA region
	string pathAsymKeyBin = argv[2];		// K2.bin for asymmetric key
	string pathSymKeyBin = argv[3];			// K3.bin for symmetric key
	string pathOutput = argv[4];			// output encrypted DA region
		
	FILE *fInput = NULL;
	FILE *fOutput = NULL;

	if( (fInput = fopen(pathEncryptedBin.c_str(), "rb")) == NULL) 
	{
		fprintf(stderr, "ERROR: Can't open file(\"%s\")!\n\n", pathEncryptedBin.c_str());
		return 3;		
	} 

	if( (fOutput = fopen(pathOutput.c_str(), "wb")) == NULL) 
	{
		fprintf(stderr, "ERROR: Can't open file(\"%s\")!\n\n", pathOutput.c_str());
		return 4;		
	} 

	// read the input encrypting DA region files
	fseek( fInput , 0 , SEEK_END );
	int fileSize = ftell(fInput);
	unsigned char *pBuf = new unsigned char[fileSize];	
	fseek( fInput , 0 , SEEK_SET );
	fread( pBuf, 1, fileSize , fInput);
	
	// prepare dummy signature
	unsigned char sigature[SIGNATURE_SIZE];
	memset(&sigature, 0, sizeof(unsigned char)*SIGNATURE_SIZE);

	// add dummy pattern to output encrypted DA region
	fwrite(pBuf, 1, fileSize, fOutput);
	fwrite(&sigature, 1, sizeof(unsigned char)*SIGNATURE_SIZE, fOutput);
	
	delete[] pBuf;
	// close file handle
	fflush(fInput);
	fflush(fOutput);
	fclose(fInput);
	fclose(fOutput);

	return 0;
}