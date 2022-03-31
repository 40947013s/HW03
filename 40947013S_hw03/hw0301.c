#include "hw0301.h"

int main()
{    
    FILE *pFile = NULL;
    char key[1000];
    printf("Please enter the search target: ");
    scanf("%s", key);
    
    if((pFile = fopen("bible.txt", "r")) == NULL)
    {
        printf("File could not be opened!\nExit.\n");
        return 0;
    }
    search(pFile, key);
	fclose(pFile);
    return 0;
}