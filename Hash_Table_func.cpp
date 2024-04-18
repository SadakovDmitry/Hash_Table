#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "hash_table_func.h"
#include "hash_func.h"



struct Hash_Table* Hash_Table_Ctor(const char* file_name, size_t size, uint32_t (Calc_Hash) (char*, uint32_t))
{
    FILE* file = fopen(file_name, "r");
    assert(file);

    union Value* in_word = (union Value*) calloc(1, 256);
    struct Hash_Table* hash_table = (struct Hash_Table*) calloc(1, sizeof(struct Hash_Table));
    hash_table -> data = (struct Node**) calloc(size, sizeof(struct Node*));
    hash_table -> Calc_Hash = Calc_Hash;
    hash_table -> size = size;

    for (size_t i = 0; i < size; i++)
        hash_table -> data[i] = NULL;

    while (fscanf(file, "%s", in_word -> str) == 1)
    {
        int len = strlen(in_word -> str);
        memset(in_word -> str + len, '\0', 32 - len);
        Insert_Elem(hash_table, in_word);
    }

    return hash_table;
}

struct Node* Is_in_Hash_Table(struct Hash_Table* hash_table, union Value* word)
{
    int index = hash_table -> Calc_Hash(word -> str, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];

    while(now_node != NULL)
    {
        #ifdef WITH_MY_STRCMP
            if(!my_strcmp(word -> reg_str, (now_node -> val) -> reg_str))
        #else
            if(!strcmp(word -> str, (now_node -> val) -> str))
        #endif
            return now_node;

        now_node = now_node -> next;
    }
    return NULL;
}

void Insert_Elem(struct Hash_Table* hash_table, union Value* in_word)
{

    struct Node* find_node = Is_in_Hash_Table(hash_table, in_word);
    if(find_node)
    {
        (find_node -> num)++;
        return;
    }

    int index = hash_table -> Calc_Hash(in_word -> str, hash_table -> size);

    struct Node* new_node = Create_Node(in_word -> str);
    new_node -> next = hash_table -> data[index];
    hash_table -> data[index] = new_node;
    //printf("%s\n", new_node -> val);
}

void Delete_Elem(struct Hash_Table* hash_table, union Value* del_word)
{
    int index = hash_table -> Calc_Hash(del_word -> str, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];
    struct Node* prev_node = NULL;

    if(!Is_in_Hash_Table(hash_table, del_word))
        return;

    while(now_node != NULL)
    {
        #ifdef WITH_MY_STRCMP
            if(!my_strcmp(del_word -> reg_str, (now_node -> val) -> reg_str))
        #else
            if(!strcmp(del_word -> str, (now_node -> val) -> str))
        #endif
        {
            if(prev_node != NULL)
                prev_node -> next = now_node -> next;
            else
                hash_table -> data[index] = now_node -> next;

            free((now_node -> val) -> str);
            free(now_node);
            return;
        }
        prev_node = now_node;
        now_node = now_node -> next;
    }
}


int* Find_Distribution(struct Hash_Table* hash_table)
{
    int* dist = (int*) calloc(hash_table -> size, sizeof(int));
    for (size_t i = 0; i < hash_table -> size; i++)
    {
        struct Node* now_node = hash_table -> data[i];
        int count = 0;
        while(now_node != NULL)
        {
            now_node = now_node -> next;
            count++;
        }
        dist[i] = count;
    }
    return dist;
}

struct Node* Create_Node(char* val)
{
    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));
    new_node -> val = (union Value*) calloc(1, sizeof(union Value));
    //new_node -> val = strndup(val, 32); // TODO: mop up mem leak
    strncpy((new_node -> val) -> str, val, 32);
    new_node -> num = 1;
    new_node -> next = NULL;
    return new_node;
}

void Print_Arr(FILE* file, int* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", data[i]);
    }
    //fprintf(file, "\n");
}

int Hash_Table_Len(struct Hash_Table* hash_table)
{
    int len = 0;
    for (size_t i = 0; i < hash_table -> size; i++)
    {
        struct Node* now_node = hash_table -> data[i];
        while(now_node != NULL)
        {
            now_node = now_node -> next;
            len++;
        }
    }
    return len;
}

int my_strcmp(__m256 str_1, __m256 str_2)
{
    __m256i res_cmp = _mm256_cmpeq_epi8(str_1, str_2);
    int mask = ~_mm256_movemask_epi8(res_cmp);

    return mask;
}
