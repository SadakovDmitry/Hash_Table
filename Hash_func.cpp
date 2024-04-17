#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "hash_func.h"


int Calc_Hash_First_Letter(char* x, int size)
{
    int hash = (int) x[0];
    return hash % size;
}

int Calc_Hash_Zero(char* x, int size)
{
    return (0 * (int) x[0]) / size;
}

int Calc_Hash_Len_Word(char* x, int size)
{
    return strlen(x) % size;
}

int Calc_Hash_Sum_Letters(char* x, int size)
{
    int sum = 0;
    int i = 0;
    while(x[i] != '\0')
    {
        sum += (int) x[i];
        i++;
    }
    return sum % size;
}

int Calc_Hash_Ror_Left(char* x, int size)
{
    int hash = 0;
    for (size_t i = 0; i < strlen(x); i++)
    {
        hash = Rot_left(hash, 1) ^ (int) x[i];
    }
    return hash % size;
}

int Calc_Hash_Ror_Right(char* x, int size)
{
    int hash = 0;
    for (size_t i = 0; i < strlen(x); i++)
    {
        hash = Rot_right(hash, 1) ^ (int) x[i];
    }
    return hash % size;
}

int Rot_left(int num, int n)
{
    n = n % 32;
    return (num << n) | (num >> (32 - n));
}

int Rot_right(int num, int n)
{
    n = n % 32;
    return (num >> n) | (num << (32 - n));
}
