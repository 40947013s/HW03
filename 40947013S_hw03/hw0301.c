#include "hw0301.h"

int main()
{    
    FILE *pFile = NULL;
    char key[1000];
    printf("Please enter the search target: ");
    fgets(key, 1000, stdin);
    key[strlen(key)-1] = 0;
    
    if((pFile = fopen("bible.txt", "r")) == NULL)
    {
        printf("File could not be opened!\nExit.\n");
        return 0;
    }
    search_time(pFile, key);
    search(pFile, key);
	fclose(pFile);
    return 0;
}