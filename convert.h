/**
* Author: Tim Bradt
* Header file for convert
* Contains function decelerations
*/

#ifndef CONVERT_H
#define CONVERT_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    CHAR = 0x00,
    INT = 0x01,
    FLOAT = 0x02,
    EXIT = 0x03
} type_t;

uint8_t currentByte;
uint64_t currPos;


/**
*	Opens file.dat
*	returns false if file does not open
*/
bool 	openFile(void);

/**
*	Closes file.dat
*/
void 	closeFile(void);

/**
*	Reads in 1 byte
*/
void 	readInByte(uint8_t* data);

/**
*	Reads in 1 bit
*	Increments bit position
*	returns either 1 or 0
*/
uint8_t	readInBit(void);

/**
*	Reads the type of value
*	returns the header type
*/
uint8_t	readHeader(void);

/**
*	Reads in char in 7 bits
*	returns charater
*/
uint8_t	readChar(void);

/**
*	Reads in int size and then the int
*	returns integer
*/
int32_t	readInt(void);

/**
*	Reads in float
*	returns float
*/
float	readFloat(void);
#endif