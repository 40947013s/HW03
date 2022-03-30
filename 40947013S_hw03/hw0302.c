#include "hw0302.h"

int main(void) 
{
    FILE *pFile = NULL;
    char name[127];
    double speed;
    printf("Open a srt file: ");
    scanf("%s", name);
    printf("Speed (0.5-2): ");
    scanf("%lf", &speed);
    if((pFile = fopen(name, "r")) == NULL)
    {
        printf("File could not be opened!\nExit.\n");
        return 0;
    }
    if(speed < 0.5 || speed > 2)
    {
        printf("over the range of speed!\nExit.\n");
    }
    lyric(pFile, speed);
	fclose(pFile);
	return 0;
}