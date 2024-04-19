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

    char* in_str = (char*) calloc(32, sizeof(char));
    struct Hash_Table* hash_table = (struct Hash_Table*) calloc(1, sizeof(struct Hash_Table));
    hash_table -> data = (struct Node**) calloc(size, sizeof(struct Node*));
    hash_table -> Calc_Hash = Calc_Hash;
    hash_table -> size = size;

    for (size_t i = 0; i < size; i++)
        hash_table -> data[i] = NULL;

    while (fscanf(file, "%s", in_str) == 1)
    {
        #ifdef WITH_MY_STRLEN
        size_t len = strlen_simd(in_str);
        #else
        size_t len = strlen(in_str);
        #endif
        memset(in_str + len, '\0', 32 - len);
        Insert_Elem(hash_table, in_str);
    }

    free(in_str);

    return hash_table;
}

void Hash_Table_Dtor(struct Hash_Table* hash_table)
{
    for (size_t i = 0; i < hash_table -> size; i++)
    {
        struct Node* temp_node = hash_table -> data[i];
        while(hash_table -> data[i] != NULL)
        {
            temp_node = hash_table -> data[i];
            hash_table -> data[i] = (hash_table -> data[i]) -> next;

            free(temp_node);
        }
    }
    free(hash_table -> data);
    free(hash_table);
}

struct Node* Is_in_Hash_Table(struct Hash_Table* hash_table, char* str)
{
    int index = hash_table -> Calc_Hash(str, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];

    while(now_node != NULL)
    {
        #ifdef WITH_MY_STRCMP
            if(!my_strcmp((__m256i*)(str), (__m256i*)(now_node -> str)))
        #else
            if(!strcmp(str, now_node -> str))
        #endif
                return now_node;

        now_node = now_node -> next;
    }
    return NULL;
}

void Insert_Elem(struct Hash_Table* hash_table, char* in_str)
{

    struct Node* find_node = Is_in_Hash_Table(hash_table, in_str);
    if(find_node)
    {
        (find_node -> num)++;
        return;
    }

    int index = hash_table -> Calc_Hash(in_str, hash_table -> size);

    struct Node* new_node = Create_Node(in_str);
    new_node -> next = hash_table -> data[index];
    hash_table -> data[index] = new_node;
}

void Delete_Elem(struct Hash_Table* hash_table, char* del_str)
{
    int index = hash_table -> Calc_Hash(del_str, hash_table -> size);
    struct Node* now_node = hash_table -> data[index];
    struct Node* prev_node = NULL;

    if(!Is_in_Hash_Table(hash_table, del_str))
        return;

    while(now_node != NULL)
    {
        #ifdef WITH_MY_STRCMP
            if(!my_strcmp((__m256i*) del_str, (__m256i*)(now_node -> str)))
        #else
            if(!strcmp(del_str, now_node -> str))
        #endif
        {
            if(prev_node != NULL)
                prev_node -> next = now_node -> next;
            else
                hash_table -> data[index] = now_node -> next;

            free(now_node -> str);
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
    strncpy(new_node -> str, val, 32);
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

int my_strcmp(__m256i* str_1, __m256i* str_2)
{
    __m256i str_reg_1 = _mm256_lddqu_si256(str_1);
    __m256i str_reg_2 = _mm256_lddqu_si256(str_2);

    __m256i res_cmp = _mm256_cmpeq_epi8(str_reg_1, str_reg_2);
    int mask = ~_mm256_movemask_epi8(res_cmp);

    return mask;
}

size_t my_strlen(char* str)
{
    size_t len = 0;
    /*
    asm volatile(
        ".intel_syntax noprefix\n\t"

        "mov rdi, %1\n\t"
        "xor rcx, rcx\n"
        ".next%=: \n\t"
        "cmp byte ptr [rdi], 0\n\t"
        "je .end%=\n\t"
        "cmp byte ptr [rdi], 13\n\t"
        "je .end%=\n\t"

        "inc rcx\n\t"
        "inc rdi\n\t"
        "jmp .next%=\n"
        ".end%=: \n\t"
        "mov %0, rcx\n\t"

        ".att_syntax prefix\n"

        : "=r" (len)
        : "r" (str)
        : "%rcx", "%rdi", "cc"
    );
    */
    return len;
}

size_t strlen_simd(char* str)
{
    __m256i zero    = _mm256_setzero_si256();
    __m256i xmm_str = _mm256_lddqu_si256((__m256i*) str);
    int mask = _mm256_movemask_epi8( _mm256_cmpeq_epi8(xmm_str, zero));

    if (mask != 0)
    {
        const char* zero_byte = (const char*) str + __builtin_ffs(mask) - 1;
        return zero_byte - str;
    }
    return 0;
}
