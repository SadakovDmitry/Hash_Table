#include <stdio.h>
#include <string.h>

int Find_Num(int* arr, int size);

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Hello world\n");
    for (int i = 0; i < 100; i++)
    {
        printf("now index: %d\n", i);
        if (!strcmp("dima_loh", "ded"))
            printf("dima_loh ,ded ne loh\n");
    }
    Find_Num(arr, 11);
}

int Find_Num(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(arr[i] == 9)
        {
            printf("OK\n");
            return 1;
        }
    }

    return 0;
}

