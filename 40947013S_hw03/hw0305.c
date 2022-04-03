#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define exit_program printf("Invaild input.\n"),\
exit(0);

typedef struct _sBmpheader
{
    char bm[2];
    uint32_t size;
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t hres;
    uint32_t vres;
    uint32_t used;
    uint32_t important;
}__attribute__((__packed__)) Bmpheader;

void counter(FILE *step, int *m, int *n, int *count)
{
    fscanf(step, "%d %d %d", &(*m), &(*n), &(*count));
    return;
}

void printer(int **cube, int n, int m, int count)
{
    /*for(int i = 1; i < count+1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < m; k++)
            {
                printf("%2d ", cube[i][j*m+k]);
            }
            printf("\n");
        }
        printf("\n");
    }*/
}

bool check(FILE *step, FILE *pFile)
{
    int m, n, count, pivot;
    char line[100];
    Bmpheader header;
    
    counter(step, &m, &n, &count);
    fgets(line, 100, step);
    int cube[count+1][n*m];
    bool used[n*m+1];
    for(int i = 0; i < n*m; i++)
    {
        cube[0][i] = i+1;
        used[i] = false;
    } used[n*m] = false;
    for(int i = 0; i < n*m; i++)
    {
        fscanf(step, "%d", &cube[1][i]);
        if(used[cube[1][i]] == true)
            exit_program;         
        used[cube[1][i]] = true;
        if(i % n == n-1) fgets(line, 100, step);
    }
    if(used[0] == false)
        exit_program;
    for(int i = 0; i < n*m+1; i++)
    {
        if(used[i] == false) pivot = i;
        used[i] = false;
    }
    
    for(int i = 2; i < count+1; i++)
    {
        for(int j = 0; j < n*m; j++)
        {
            fscanf(step, "%d", &cube[i][j]);
            if(used[cube[i][j]] == true || cube[i][j] == pivot)
                exit_program;
            used[cube[i][j]] = true;
        }
        for(int j = 0; j < n*m+1; j++)
            used[j] = false;        
    }

    for(int i = 1; i < count+1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < m; k++)
            {
                printf("%2d ", cube[i][j*m+k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    FILE *pFile2 = fopen("1.bmp", "wr");
    fread(&header, 1, sizeof(Bmpheader), pFile);
    fwrite(&header, 1, sizeof(Bmpheader), pFile2);
    int in_size = ((header.width*header.bpp+31) >> 5) << 2; 
    uint8_t *in_color = (uint8_t *)malloc(sizeof(uint8_t) *in_size);
    int h = header.height/n, v = header.width/m;
    for(int i = 0; i < header.height; i++)
    {
        fread(in_color, 1, in_size, pFile);
        if(i % h == 0 || (i-1) % h == 0 || (i+1) % h == 0)
        {
            memset(in_color, 0, in_size);
            fwrite(in_color, 1, in_size, pFile2);
            continue;
        }
        for(int j = 0; j < in_size; j+=3)
        {
            if(j/3 % v == 0 || (j/3-1) % v == 0 || (j/3+1) % v == 0)  
            {
                for(int k = 0; k < 3; k++)
                {
                    in_color[j+k] = 0;
                }
            }
        }
        fwrite(in_color, 1, in_size, pFile2);
    }
    
}

int main()
{
    FILE *step, *bmp_in;
    char step_name[255], input[255];

    printf("Please enter the image: ");
    fgets(input, 255, stdin);
    if(input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = 0;
    
    if((bmp_in = fopen(input, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }


    printf("Please enter the puzzle: ");
    fgets(step_name, 255, stdin);
    if(step_name[strlen(step_name) - 1] == '\n')
        step_name[strlen(step_name) - 1] = 0;
    
    if((step = fopen(step_name, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    check(step, bmp_in);
}