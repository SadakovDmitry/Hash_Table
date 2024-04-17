#ifndef USED_TP
#define USED_TP

#define red(str)   "\033[31m"#str"\033[0m"

int Text_Processing(const char* from, const char* to);
char* Read_file(int* len_buf, FILE* file, int* file_size);

#endif
