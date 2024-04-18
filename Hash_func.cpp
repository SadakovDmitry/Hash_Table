#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdint.h>
#include "hash_func.h"

uint32_t Calc_Hash_First_Letter(char* x, uint32_t size)
{
    uint32_t hash = (uint32_t) x[0];
    return hash % size;
}

uint32_t Calc_Hash_Zero(char* x, uint32_t size)
{
    return (0 * (uint32_t) x[0]) / size;
}

uint32_t Calc_Hash_Len_Word(char* x, uint32_t size)
{
    return strlen(x) % size;
}

uint32_t Calc_Hash_Sum_Letters(char* x, uint32_t size)
{
    uint32_t sum = 0;
    size_t i = 0;
    while(x[i] != '\0')
    {
        sum += (uint32_t) x[i];
        i++;
    }
    return sum % size;
}

uint32_t Calc_Hash_Rol(char* x, uint32_t size)
{
    uint32_t hash = 0;
    for (size_t i = 0; i < strlen(x); i++)
    {
        hash = Rot_left(hash, 1) ^ (uint32_t) x[i];
    }
    return hash % size;
}

uint32_t Calc_Hash_Ror(char* x, uint32_t size)
{
    uint32_t hash = 0;
    for (size_t i = 0; i < strlen(x); i++)
    {
        hash = Rot_right(hash, 1) ^ (uint32_t) x[i];
    }
    return hash % size;
}

uint32_t Rot_left(uint32_t num, uint32_t n)
{
    n = n % 32;
    return (num << n) | (num >> (32 - n));
}

uint32_t Rot_right(uint32_t num, uint32_t n)
{
    n = n % 32;
    return (num >> n) | (num << (32 - n));
}

uint32_t Calc_Hash_Crc32(char* x, uint32_t size)
{
    #ifndef WITH_MY_CRC32
    uint32_t crc = 0xFFFFFFFFUL;
    size_t len = strlen(x);

    while (len--)
        crc = (crc >> 8) ^ Crc32_Table[(crc ^ *x++) & 0xFF];
    #else
    unsigned long len = strlen(x);

    uint32_t crc = my_crc32(x, len);
    #endif
    return crc % size;
}

uint32_t Calc_Hash_My_Crc32(char* x, uint32_t size)
{
    unsigned long len = strlen(x);

    uint32_t hash = my_crc32(x, len);
    return hash % size;
}


