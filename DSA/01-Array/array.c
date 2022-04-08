#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int arr[5][4];

    srand(time(0));


    printf("Enter array 20 elements : \n");
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("Using 2 for loops\n");
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
        printf("\n");
    }

    printf("Using single for loops\n");
    for(int i = 0; i < 20; i++)
    {
        printf("*(arr) + %d = %d\n", i, *(*arr + i));
    }

    return 0;
}