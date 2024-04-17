#ifndef USED_HTF
#define USED_HTF

struct Node
{
    char* val;
    int num;
    struct Node* next;
};

struct Hash_Table
{
    struct Node** data;
    size_t size;
    uint32_t (* Calc_Hash) (char*, uint32_t);
};

#define YES 1;
#define NO  0;

struct Hash_Table* Hash_Table_Ctor(const char* file_name, size_t size, uint32_t (Calc_Hash) (char*, uint32_t));
struct Node* Is_in_Hash_Table(struct Hash_Table* hash_table, char* val);
void Insert_Elem(struct Hash_Table* hash_table, char* val);
void Delete_Elem(struct Hash_Table* hash_table, char* val);
struct Node* Create_Node(char* val);
int* Find_Distribution(struct Hash_Table* hash_table);
int Hash_Table_Len(struct Hash_Table* hash_table);
void Print_Arr(FILE* file, int* data, size_t size);

#endif
