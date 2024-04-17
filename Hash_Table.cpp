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
#define red(str)   "\033[31m"#str"\033[0m"
#define green(str) "\033[32m"#str"\033[0m"


int main(const int argc, const char* argv[])
{
    if(argc < 2)
    {
        printf(red(ERROR uncorrect num arguments\n));
        return 0;
    }
    const char* file_name = argv[1];

    struct Hash_Table* hash_table_temp = Hash_Table_Ctor(file_name, 10000, Calc_Hash_Ror_Left);
    int num_unique_words = Hash_Table_Len(hash_table_temp);
    printf(green(Num of unique words) " : %d\n", num_unique_words);

    struct Hash_Table* hash_table = Hash_Table_Ctor(file_name, num_unique_words / LOAD_FACTOR, Calc_Hash_Ror_Left); // TODO: array of hash funcs
    int* dist = Find_Distribution(hash_table);
    FILE* file = fopen("dist.txt", "w");
    Print_Arr(file, dist, hash_table -> size);
    //return 0;
    for(int i = 0 ; i < 1000000; i++)
    {
        /*
        struct Node* find_node = Is_in_Hash_Table(hash_table, "chveheb");
        if(find_node)
            printf(green(YES)"(num = %d)\n", find_node -> num);
        else
            printf(red(NO\n));
        */
        char str[] = "ciecnie";
        Is_in_Hash_Table(hash_table, str);
    }
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

