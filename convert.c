/**
* Author: Tim Bradt
* Contains the file defs
* Contains the main function
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "convert.h"


FILE* fp;



int main(int argc, char** args)
{
	currPos = 0;
	if(!openFile())
	{
		printf("File could not be opened...Exiting\n");
		return 1;
	}
	
	bool exit = false;
	while(!exit)
	{
		//Reads Header Type
		uint8_t header = readHeader();
		
		//Parses Header Type
		switch(header)
		{
			case CHAR:
			{
				//Reads char
				uint8_t charData = readChar();
				printf("char = '%c'\n", charData);
				break;
			}
			case INT:
			{
				//Reads int
				int32_t intData = readInt();
				printf("int = %d\n", intData);
				break;
			}
			case FLOAT:
			{
				//Reads float
				float floatData = readFloat();
				printf("float = %f\n", floatData);
				break;
			}
			case EXIT:
			{
				//Exits
				exit = true;
				break;
			}
		}
		
	}
	
	//Closes file
	closeFile();
}

bool openFile()
{
	if((fp = fopen("./file.dat", "r")) == NULL)
	{
		return false;
	}
	return true;
}

void closeFile()
{
	fclose(fp);
}

void readInByte(uint8_t* data)
{
	int result = fread (data,1,1,fp);
	if (result != sizeof(uint8_t) * 1) {printf("Reading error\n");}
}

uint8_t readInBit(void)
{
	if(currPos % 8 == 0)
	{
		readInByte(&currentByte);
	}
	uint8_t offset = (7 - (currPos % 8));
	uint8_t ret = (currentByte & (1 << offset)) >> offset;
	currPos++;
	return ret;
	
}

uint8_t readHeader(void)
{
	uint8_t dataRead = 0;
	for(int i = 0; i < 2; i++)
	{
		dataRead <<= 1;
		uint8_t newBit = readInBit();
		dataRead |= newBit;
	}
	return dataRead;
}

uint8_t readChar(void)
{
	uint8_t dataRead = 0;
	for(int i = 0; i < 7; i++)
	{
		dataRead <<= 1;
		uint8_t newBit = readInBit();
		dataRead |= newBit;
	}
	return dataRead;
}

int32_t readInt(void)
{
	uint8_t dataSize = 0;
	for(int i = 0; i < 5; i++)
	{
		dataSize <<= 1;
		uint8_t newBit = readInBit();
		dataSize |= newBit;
	}
	int32_t dataRead = 0;
	for(int i = 0; i <= dataSize; i++)
	{
		dataRead <<= 1;
		uint8_t newBit = readInBit();
		dataRead |= newBit;
	}
	return dataRead;
}

float readFloat(void)
{
	uint32_t dataRead;
	for(int i = 0; i < 32; i++)
	{
		dataRead <<= 1;
		uint8_t newBit = readInBit();
		dataRead |= newBit;
	}
	return *((float*)(&dataRead));
}

