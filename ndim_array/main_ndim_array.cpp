#include <stdio.h>
#include <stdlib.h>

// 配列[3]型の引数
void func(int (*hoge)[3])
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d, ", hoge[i][j]);
        }
        putchar('\n');
    }
}

// 配列[size2]型の引数
template <size_t SIZE2>
void func2(int size1, int (*hoge)[SIZE2])
{
    int i, j;
    
    for (i = 0; i < size1; i++)
    {
        for (j = 0; j < SIZE2; j++)
        {
            printf("%d, ", hoge[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, const char * argv[]) {
    
    int hoge[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
    };
    
    func(hoge);
    func2(4, hoge);
    
    
    /*縦横可変の２次元配列をmalloc()で確保する*/
    int size;
    printf("board size?\n");
    scanf("%d", &size);
    printf("Obtained size -> %d\n", size);
    
    return 0;
}