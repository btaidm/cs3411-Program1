#ifndef CONVERT_H
#define CONVERT_H

#include <stdint.h>
#include <stdbool.h>

typedef union
{
    uint8_t u8[4];
    uint16_t u16[2];
    uint32_t u32;
    float fl;
} allTypes_t;

typedef enum
{
    CHAR = 0x00,
    INT = 0x01,
    FLOAT = 0x02,
    EXIT = 0x03
} type_t;

uint8_t currentByte;
uint64_t currPos;

bool openFile(void);
void closeFile(void);
void readInByte(uint8_t* data);
uint8_t readInBit(void);
uint8_t readHeader(void);
uint8_t readChar(void);
uint32_t readInt(void);
float readFloat(void);
#endif