#ifndef HW0302_H_INCLUDE
#define HW0302_H_INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct time
{
    int hour;
    int min;
    int sec;
    int msec;
}T;

int count_lines(FILE * pFile);
void table(T *nodeA, T *nodeB, char *time);
int to_double(T *nodeA, T *nodeB, double speed);
void lyric(FILE * pFile, double speed);

#endif

