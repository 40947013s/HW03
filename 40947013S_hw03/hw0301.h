#ifndef HW0301_H_INCLUDE
#define HW0301_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct base
{
    int chapter;
    int verse;
    char *text;
    char *book_id;
}Base;

int count_lines(FILE * pFile);
char *lower(char *str);
void search(FILE *pFile, char *Key);
void search_time(FILE *pFile, char *key);

#endif

