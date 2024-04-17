#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "text_processing.h"

int main(const int argc, const char* argv[])
{
    if(argc < 3)
    {
        printf(red(ERROR\n));
        return 0;
    }

    Text_Processing(argv[1], argv[2]);
    return 0;
}

int Text_Processing(const char* from, const char* to)
{
    int size_of_file = 0;
    int len_buf = 0;
    FILE* input_file = fopen(from, "r");
    assert(input_file);
    char* buf = Read_file(&len_buf, input_file, &size_of_file);
    //printf("%d", len_buf);
    //getchar();
    fclose(input_file);

    //fprintf(stderr, "ERROR\n");

    FILE* output_file = fopen(to, "w");
    assert(output_file);
    int num_words = 0;
    /*
    //for (int i = 0; i < len_buf - 1; i++)
    for (int i = 0; i != '\0'; i++)
    {
        //while (buf[i] == ' ')
        fprintf(stderr, "%d)ERROR\n", i);
        while(!isalpha(buf[i]))
            i++;

        //if (i >= len_buf - 1) break;
        if (buf[i] == '\0') break;

        if(buf[i] != ' ')
            fprintf(output_file, "%c", buf[i]);

        //if (i < len_buf - 1 && (ispunct(buf[i + 1]) || isspace(buf[i + 1])))
        if (buf[i] != '\0' && (ispunct(buf[i + 1]) || isspace(buf[i + 1])))
        {
            fprintf(output_file, "\n");
            num_words++;
        }
    }
    fclose(output_file);
    return num_words;
*/

    int len = 0;
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if(isalpha(buf[i]) || buf[i] == '-')
        {
            fprintf(output_file, "%c", buf[i]);
            len++;
        }
        else if((isspace(buf[i]) || ispunct(buf[i])) && isalpha(buf[i + 1]))
        {
            while(len < 32 && len != 0)
            {
                fprintf(output_file, "\0");
                len++;
            }
            fprintf(output_file, "\n");
            len = 0;
        }
        else
        {
            while(len < 32 && len != 0)
            {
                fprintf(output_file, "\0");
                len++;
            }
        }
    }
    free(buf);
    fclose(output_file);
    return num_words;
}

char* Read_file(int* len_buf, FILE* file, int* file_size)
{
    struct stat st = {};

    fstat(file->_file, &st);
    *len_buf = st.st_size;
    *(file_size) = st.st_size;

    char* buf = (char*) calloc(st.st_size + 1, sizeof(char));
    fread(buf, sizeof (char), st.st_size, file);

    //printf("\nBUF = %s\n", buf);

    return buf;
}
