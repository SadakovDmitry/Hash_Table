#ifndef USED_HTF
#define USED_HTF

#include <immintrin.h>
#include <stdint.h>

#define YES 1;
#define NO  0;
#define red(str)   "\033[31m"#str"\033[0m"
#define green(str) "\033[32m"#str"\033[0m"

union Value
{
    char str[32];
    __m256i reg_str;
};

struct Node
{
    union Value* val;
    int num;
    struct Node* next;
};

struct Hash_Table
{
    struct Node** data;
    size_t size;
    uint32_t (* Calc_Hash) (char*, uint32_t);
};

struct Hash_Table* Hash_Table_Ctor  (const char* file_name, size_t size, uint32_t (Calc_Hash) (char*, uint32_t));
void   Hash_Table_Dtor              (struct Hash_Table* hash_table);
struct Node* Is_in_Hash_Table       (struct Hash_Table* hash_table, union Value* word);
void   Insert_Elem                  (struct Hash_Table* hash_table, union Value* in_word);
void   Delete_Elem                  (struct Hash_Table* hash_table, union Value* del_word);
struct Node* Create_Node            (char* val);
int*   Find_Distribution            (struct Hash_Table* hash_table);
int    Hash_Table_Len               (struct Hash_Table* hash_table);
void   Print_Arr                    (FILE* file, int* data, size_t size);
int    my_strcmp                    (__m256i* str_1, __m256i* str_2);
size_t my_strlen                    (char* str);


#endif
