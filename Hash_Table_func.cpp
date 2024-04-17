#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "hash_func.h"
#include "hash_table_func.h"

struct Hash_Table* Hash_Table_Ctor(const char* file_name, int size, int (Calc_Hash) (char*, int))
{
    FILE* file = fopen(file_name, "r");
    assert(file);
    char* str = (char*) calloc(100, sizeof(char));
    struct Hash_Table* hash_table = (struct Hash_Table*) calloc(1, sizeof(struct Hash_Table));
    hash_table -> data = (struct Node**) calloc(size, sizeof(struct Node*));
    hash_table -> Calc_Hash = Calc_Hash;
    hash_table -> size = size;

    for (int i = 0; i < size; i++)
        hash_table -> data[i] = NULL;

    //for (int i = 0; i < num_words * LOAD_FACTOR; i++)
    while (fscanf(file, "%s", str) == 1)
        Insert_Elem(hash_table, str);

    return hash_table;
}

struct Node* Is_in_Hash_Table(struct Hash_Table* hash_table, char* val)
{
    int index = hash_table -> Calc_Hash(val, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];

    while(now_node != NULL)
    {
        if(!strcmp(val, now_node -> val))
            return now_node;

        now_node = now_node -> next;
    }
    return NULL;
}

void Insert_Elem(struct Hash_Table* hash_table, char* val)
{
    int index = hash_table -> Calc_Hash(val, hash_table -> size);

    struct Node* find_node = Is_in_Hash_Table(hash_table, val);
    if(find_node)
    {
        (find_node -> num)++;
        return;
    }

    struct Node* new_node = Create_Node(val);
    new_node -> next = hash_table -> data[index];
    hash_table -> data[index] = new_node;
    //printf("%s\n", new_node -> val);
}

void Delete_Elem(struct Hash_Table* hash_table, char* val)
{
    int index = hash_table -> Calc_Hash(val, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];
    struct Node* prev_node = NULL;

    if(!Is_in_Hash_Table(hash_table, val))
        return;

    while(now_node != NULL)
    {
        if(!strcmp(val, now_node -> val))
        {
            if(prev_node != NULL)
                prev_node -> next = now_node -> next;
            else
                hash_table -> data[index] = now_node -> next;

            free(now_node -> val);
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
    for (int i = 0; i < hash_table -> size; i++)
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
    new_node -> val = strdup(val); // TODO: mop up mem leak
    new_node -> num = 1;
    new_node -> next = NULL;
    return new_node;
}

void Print_Arr(FILE* file, int* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", data[i]);
    }
    //fprintf(file, "\n");
}

int Hash_Table_Len(struct Hash_Table* hash_table)
{
    int len = 0;
    for (int i = 0; i < hash_table -> size; i++)
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