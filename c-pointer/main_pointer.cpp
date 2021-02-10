#include <iostream>
#include <cstdio>

void get_xy(double *x_p, double *y_p)
{
    printf("x_p..%p, y_p..%p\n", (void*)x_p, (void*)y_p); // アドレス
    printf("&x_p..%p, &y_p..%p\n", (void*)&x_p, (void*)&y_p); // ポインタのアドレス
    *x_p = 1.0;
    *y_p = 2.0;
}


int main(int argc, const char * argv[]) 
{
    std::cout << "Hello, World!\n";
    
    // ポインタ演算
    int hoge;
    int *hoge_p;
    printf("sizeof(int*):%d\n", (int)sizeof(int*));

    hoge_p = &hoge;
    printf("hoge_p...%p\n", (void*)hoge_p);

    hoge_p++; // 未定義
    printf("hoge_p...%p\n", (void*)hoge_p); // 未定義
    printf("hoge_p...%p\n", (void*)(hoge_p + 3)); // 未定義
    
    // NULL : すべてのビットが0であるバイト, char型
    // '\0' :　文字定数, 定数0 つまり int型
    // #define NULL ((void*))
    // Cでは「0という定数は、ポインタとして扱うべき文脈では、ヌルポインタとして扱われる」
    
    // ポインタと関数
    double x;
    double y;
    printf("&x_p..%p, &y_p..%p\n", (void*)&x, (void*)&y);
    get_xy(&x, &y);
    printf("x..%f, y..%f\n", x, y);
    
    // 配列
    int array[5];
    for (int i = 0; i < 5; i++)
    {
        array[i] = i;
    }
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", array[i]);
    }
    
    for (int i = 0; i < 5; i++)
    {
        printf("&array[%d]... %p\n", i, (void*)&array[i]);
    }
    
    return 0;
}
