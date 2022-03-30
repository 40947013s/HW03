#include "hw0302.h"

int count_lines(FILE * pFile)
{
    char line[1000];
    int Line = 0;
    while(fgets(line,1000,pFile) != NULL)
        if(strstr(line, " --> "))
            Line++;
    return Line;
}

void table(T *nodeA, T *nodeB, char *time)
{
    nodeA->hour = (time[0]-48)*10 + (time[1]-48);
    nodeA->min = (time[3]-48)*10 + (time[4]-48);
    nodeA->sec = (time[6]-48)*10 + (time[7]-48);
    nodeA->msec = (time[9]-48)*100 + (time[10]-48)*10 + (time[11]-48);

    nodeB->hour = (time[17]-48)*10 + (time[18]-48);
    nodeB->min = (time[20]-48)*10 + (time[21]-48);
    nodeB->sec = (time[23]-48)*10 + (time[24]-48);
    nodeB->msec = (time[26]-48)*100 + (time[27]-48)*10 + (time[28]-48);
}

int to_double(T *nodeA, T *nodeB, double speed)
{
    int hour = nodeB->hour - nodeA->hour;
    int min = nodeB->min - nodeA->min;
    int sec = nodeB->sec - nodeA->sec;
    int msec = nodeB->msec - nodeA->msec;
    int res = ((hour*3600+min*60+sec) * 1000000 + msec * 1000) / speed;
    return res;
}

void lyric(FILE * pFile, double speed)
{
    int count = count_lines(pFile), LineN = 0, state = 0;
	char line[1000], Lyric[count][1000];
    T node[count+1][2]; 
    node[0][1].hour = 0, node[0][1].min = 0;
    node [0][1].sec = 0, node[0][1].msec = 0;
    rewind(pFile);
    while(fgets(line,1000,pFile) != NULL)
    {
        if(strstr(line, " --> "))
        {
            table(&node[LineN+1][0], &node[LineN+1][1], line);
            state = 1;
        }
        else if(state)
        {
            strncpy(Lyric[LineN], line, sizeof(line));
            state = 0, LineN++;
        }
    }    
    for(int i = 1; i < LineN+1; i++)
    {
        system("clear");
        usleep(to_double(&node[i-1][1], &node[i][0], speed));
        printf("%s",Lyric[i-1]);
        usleep(to_double(&node[i][0], &node[i][1], speed));
    }
    system("clear");
}