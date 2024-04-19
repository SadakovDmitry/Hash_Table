#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <time.h>
#include "hash_table_func.h"
#include "hash_func.h"

const int SIZE_TABLE  = 769;

uint32_t (* HASH_ARR[8])(char*, uint32_t) = {
                                            Calc_Hash_Zero,         //0
                                            Calc_Hash_First_Letter, //1
                                            Calc_Hash_Len_Word,     //2
                                            Calc_Hash_Sum_Letters,  //3
                                            Calc_Hash_Rol,          //4
                                            Calc_Hash_Ror,          //5
                                            Calc_Hash_Crc32,        //6
                                            Calc_Hash_My_Crc32      //7
                                            };


int main(const int argc, const char* argv[])
{
    if(argc != 3)
    {
        printf(red(ERROR uncorrect num arguments\n));
        return 0;
    }

    const char* file_name = argv[1];
    const int num_hash_func = atoi(argv[2]);

    char str[32] = {};
    struct Hash_Table* hash_table_temp = Hash_Table_Ctor(file_name, 10000, Calc_Hash_Rol);
    int num_unique_words = Hash_Table_Len(hash_table_temp);
    printf(green(Num of unique words) " : %d\n", num_unique_words);
    Hash_Table_Dtor(hash_table_temp);

    struct Hash_Table* hash_table = Hash_Table_Ctor(file_name, SIZE_TABLE, HASH_ARR[num_hash_func]);
    int* dist = Find_Distribution(hash_table);
    FILE* file = fopen("dist.txt", "w");
    Print_Arr(file, dist, hash_table -> size);
    //Hash_Table_Dtor(hash_table);
    //return 0;

    double time = 0.0;
    time_t start = clock();

    for(int i = 0 ; i < 100000000; i++)
    {
        strncpy(str, "ciecnie", 32);
        Is_in_Hash_Table(hash_table, str);
    }

    time_t end = clock();
    time += (double) (end - start) / CLOCKS_PER_SEC;
    printf(green(time)" = %f\n", time);

    Hash_Table_Dtor(hash_table);
    return 0;
/*
    for(int i = 0 ; i < 1000; i++)
    {
        char* str = (char*) calloc(100, sizeof(char));
        char op = '?';
        //char str[] = "hcbocenec";

        fflush(stdin);
        scanf("%c %s", &op, str);
        if(op == '+')
            Insert_Elem(hash_table, str);
        else if(op == '-')
            Delete_Elem(hash_table, str);
        else if(op == '?')
        {
            struct Node* find_node = Is_in_Hash_Table(hash_table, str);
            if(find_node)
                printf(green(YES)"(num = %d)\n", find_node -> num);
            else
                printf(red(NO\n));
        }
        else if(op == '*')
            break;
        else
        {
            printf("nothing readed");
            printf(":%c %s\n", op, str);
        }

    }
*/
}

