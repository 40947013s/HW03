#include "hw0301.h"

int count_lines(FILE * pFile)
{
    char line[2000];
    int Line = 0;
    while(fgets(line,2000,pFile) != NULL)
        Line++;
    rewind(pFile);
    return Line;
}

void search_time(FILE *pFile, char *key)
{
    int count = count_lines(pFile), Line = 0, Counter = 1;
	char line[2000];
    while(fgets(line,2000,pFile) != NULL)
    {        
        int text_s = 0, td_s = 0, bi_s = 0, bn_s = 0;
        char *text = strstr(line, "text\":\"");
        text += 7; text_s = strlen(line) - strlen(text);
        text = strstr(text, "translation_id\":\"");
        text += 17; td_s = strlen(line) - strlen(text);
        text = strstr(text, "book_id\":\"");
        text += 10; bi_s = strlen(line) - strlen(text);
        text = strstr(text, "book_name\":\"");
        text += 12; bn_s = strlen(line) - strlen(text);

        text = malloc(td_s-20-text_s+1); int counter = 0;
        for(int i = text_s; i < td_s-20; i++)
            text[counter++] = line[i];
        text[counter] = 0;
        if(strcasestr(text, key))         
            Counter++;
    }
    printf("Find %d times\n", Counter-1);
    rewind(pFile);
}

void search(FILE *pFile, char *key)
{
    int count = count_lines(pFile), Line = 0, Counter = 1;
	char line[2000];
    Base node[count]; 
    while(fgets(line,2000,pFile) != NULL)
    {        
        char *copy_line = malloc(strlen(line)+1);
        strcpy(copy_line, line);
        char *token = strtok(copy_line, ",");
        for(int i = 0; i < 2; i++)
        {
            char *copy = malloc(strlen(token)+1);
            strcpy(copy, token);
            char *temp = strstr(copy, ":");
            temp++;
            if(i == 0) node[Line].chapter = atoi(temp);
            else node[Line].verse = atoi(temp);
            token = strtok(NULL, ",");
        }
        strcpy(copy_line, line);
        int text_s = 0, td_s = 0, bi_s = 0, bn_s = 0;
        char *text = strstr(copy_line, "text\":\"");
        text += 7; text_s = strlen(line) - strlen(text);
        text = strstr(text, "translation_id\":\"");
        text += 17; td_s = strlen(line) - strlen(text);
        text = strstr(text, "book_id\":\"");
        text += 10; bi_s = strlen(line) - strlen(text);
        text = strstr(text, "book_name\":\"");
        text += 12; bn_s = strlen(line) - strlen(text);

        text = malloc(td_s-20-text_s+1); int counter = 0;
        for(int i = text_s; i < td_s-20; i++)
            text[counter++] = line[i];
        text[counter] = 0;
        if(strcasestr(text, key) == NULL) 
        {
            Line++; continue;            
        }        
        node[Line].text = text;
        text = malloc(bn_s-15-bi_s+1); counter = 0;
        for(int i = bi_s; i < bn_s-15; i++)
            text[counter++] = line[i];
        text[counter] = 0;
        node[Line].book_id = text;
        printf("%d %s %d:%d %s\n", Counter, node[Line].book_id, node[Line].chapter, node[Line].verse, node[Line].text);
        Counter++;
        Line++;
    }
}