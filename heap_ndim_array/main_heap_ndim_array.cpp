#include <cstdio>
#include <cstdlib>
#include <cassert>

#define ALLOC_SIZE 256

#include "read_line.hpp"

// テキスト行のメモリ割り当て
char** add_line(char** text_data, 
                char* line, 
                int* line_alloc_num, 
                int* line_num) 
{
    assert(*line_alloc_num >= *line_num);

    if (*line_alloc_num == *line_num) 
    {
        // heapメモリ増量のためのメモリの再割当て
        text_data = (char**)realloc(text_data, 
                            (*line_alloc_num + ALLOC_SIZE) * sizeof(char*));
        *line_alloc_num += ALLOC_SIZE;
    }
    text_data[*line_num] = line;
    (*line_num)++;

    return text_data;
}

// 文字列の読み込み
char** read_file(FILE* fp, int* line_num_p)
{
    char** text_data = NULL;
    int line_num = 0;
    int line_alloc_num = 0;
    char* line;

    while ((line = read_line(fp)) != NULL)
    {
        text_data = add_line(text_data,
                             line,
                             &line_alloc_num,
                             &line_num);
    }

    /* text_dataを、本当に必要なサイズまで圧縮 */
    text_data = (char**)realloc(text_data, line_num * sizeof(char*));
    *line_num_p = line_num;

    return text_data;
}


int main(int argc, char** argv)
{
    char** text_data;
    int line_num;
    int i;

    FILE* fp;
    fp = std::fopen("./sample.txt", "r");
    if (fp == NULL)
    {
        printf("Can not open file.\n");
        fclose(fp);
        return -1;
    }

    text_data = read_file(fp, &line_num);

    for (i = 0; i < line_num; ++i)
    {
        printf("%s\n", text_data[i]);
    }
    free_buffer();

    fclose(fp);

    return 0;
}