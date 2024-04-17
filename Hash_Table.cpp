#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "hash_table_func.h"
#include "hash_func.h"

const int LOAD_FACTOR = 10;
const int SIZE_TABLE  = 769;
#define red(str)   "\033[31m"#str"\033[0m"
#define green(str) "\033[32m"#str"\033[0m"

uint32_t (* HASH_ARR[7])(char*, uint32_t) = {
                                        Calc_Hash_Zero,
                                        Calc_Hash_First_Letter,
                                        Calc_Hash_Len_Word,
                                        Calc_Hash_Sum_Letters,
                                        Calc_Hash_Rol,
                                        Calc_Hash_Ror,
                                        Calc_Hash_Crc32
                                    };


int main(const int argc, const char* argv[])
{
    if(argc < 3)
    {
        printf(red(ERROR uncorrect num arguments\n));
        return 0;
    }
    const char* file_name = argv[1];
    const int num_hash_func = atoi(argv[2]);

    struct Hash_Table* hash_table_temp = Hash_Table_Ctor(file_name, 10000, Calc_Hash_Rol);
    int num_unique_words = Hash_Table_Len(hash_table_temp);
    printf(green(Num of unique words) " : %d\n", num_unique_words);

    struct Hash_Table* hash_table = Hash_Table_Ctor(file_name, SIZE_TABLE, HASH_ARR[num_hash_func]);
    int* dist = Find_Distribution(hash_table);
    FILE* file = fopen("dist.txt", "w");
    Print_Arr(file, dist, hash_table -> size);
    //return 0;
    /*
    for(int i = 0 ; i < 1000000; i++)
    {
        char str[] = "ciecnie";
        Is_in_Hash_Table(hash_table, str);
    }
    */
    return 0;
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

}

