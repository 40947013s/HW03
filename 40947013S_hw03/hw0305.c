#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define exit_program printf("Invaild input.\nExit\n"),\
exit(0);
#define wrong_file printf("File could not be opened!\nExit\n"),\
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

bool check(int a, int b, int m, int n)
{  
    int x = abs((a-1)/m-(b-1)/m), y = abs((a-1)%m-(b-1)%m);
    printf("%d %d %d %d\n", a, b, x, y);
    if((x != 0 && x != 1) || (y != 0 && y != 1) || (x^y) == 0) return false;
    return true;
}

void puzzle(FILE *step, FILE *pFile)
{
    int m, n, count, pivot;
    char line[100];
    Bmpheader header;
    
    counter(step, &m, &n, &count);
    fgets(line, 100, step);
    int cube[count+1][n*m], change[count+1][2];
    bool used[n*m+1];
    for(int i = 0; i < n*m; i++)
    {
        cube[0][i] = i+1;
        used[i] = false;
    } used[n*m] = false;
    for(int i = 0; i < count+1; i++)
        change[i][0] = -1, change[i][1] = 0;
    for(int i = 0; i < n*m; i++)
    {
        fscanf(step, "%d", &cube[1][i]);
        if(used[cube[1][i]] == true)
            exit_program;         
        used[cube[1][i]] = true;
        if(i % n == n-1) fgets(line, 100, step);
    }
    if(used[0] == false) exit_program;
    for(int i = 0; i < n*m+1; i++)
    {
        if(used[i] == false) pivot = i;
        used[i] = false;
    }
    
    for(int i = 2; i < count+1; i++)
    {
        for(int j = 0, c = 0; j < n*m; j++)
        {
            fscanf(step, "%d", &cube[i][j]);
            if(used[cube[i][j]] == true || cube[i][j] == pivot)
                exit_program;
            if(cube[i-1][j] != cube[i][j])
                change[i][c++] = j+1;
            used[cube[i][j]] = true;
        }
    
        if(cube[i][change[i][0]-1] != 0 && cube[i][change[i][1]-1] != 0)
            exit_program;
        if(!check(change[i][0], change[i][1], m, n))
            exit_program;
        for(int j = 0; j < n*m+1; j++)
            used[j] = false;        
    }
    
    FILE *pFile2 = fopen("1.bmp", "w");
    fread(&header, 1, sizeof(Bmpheader), pFile);
    fwrite(&header, 1, sizeof(Bmpheader), pFile2);
    int in_size = ((header.width*header.bpp+31) >> 5) << 2; 
    uint8_t *in_color = (uint8_t *)malloc(header.height *in_size);
    int h = header.height/n, v = header.width/m, space = 0;
    fread(in_color, header.height, in_size, pFile);
    
    for(int i = 0; i < header.height; i++)
    {
        if(i % h == 0 || (i-1) % h == 0 || (i+1) % h == 0)
            for(int j = 0; j < in_size; j+=3)
                for(int k = 0; k < 3; k++)
                    in_color[i*in_size+j+k] = 0;
        else
            for(int j = 0; j < in_size; j+=3)
                if(j/3 % v == 0 || (j/3-1) % v == 0 || (j/3+1) % v == 0)
                    for(int k = 0; k < 3; k++)
                        in_color[i*in_size+j+k] = 0;
                else if((header.height-i)/h == (pivot-1)/n && (j/3)/v == (pivot-1)%n)
                    for(int k = 0; k < 3; k++)
                        in_color[i*in_size+j+k] = 255, space++;
    }
    fwrite(in_color, header.height, in_size, pFile2);
    
    for(int l = 2; l < count+1; l++)
    {
        char old_name[255], new_name[255];
        sprintf(old_name, "%d.bmp", l-1);
        sprintf(new_name, "%d.bmp", l);
        if((pFile = fopen(old_name, "r")) == NULL) wrong_file;
        if((pFile2 = fopen(new_name, "w")) == NULL) wrong_file;
        fread(&header, 1, sizeof(Bmpheader), pFile);
        fwrite(&header, 1, sizeof(Bmpheader), pFile2);
        fread(in_color, header.height, in_size, pFile);
        uint8_t *color = (uint8_t *)malloc(space);
        int count_space = 0, white;
        pivot = cube[l][change[l][0]-1] == 0 ? change[l][1] : change[l][0];
        white = cube[l][change[l][0]-1] == 0 ? change[l][0] : change[l][1];
        for(int i = 0; i < header.height; i++)
        {
            if(i % h == 0 || (i-1) % h == 0 || (i+1) % h == 0) continue;
            else
                for(int j = 0; j < in_size; j+=3)
                    if(j/3 % v == 0 || (j/3-1) % v == 0 || (j/3+1) % v == 0)
                        continue;
                    else if((header.height-i)/h == (white-1)/n && (j/3)/v == (white-1)%n)
                        for(int k = 0; k < 3; k++)
                        {
                            color[count_space++] = in_color[i*in_size+j+k];
                            in_color[i*in_size+j+k] = 255;
                        }                
        }
        count_space = 0;
        for(int i = 0; i < header.height; i++)
        {
            if(i % h == 0 || (i-1) % h == 0 || (i+1) % h == 0)
                continue;
            else
                for(int j = 0; j < in_size; j+=3)
                    if(j/3 % v == 0 || (j/3-1) % v == 0 || (j/3+1) % v == 0)
                        continue;
                    else if((header.height-i)/h == (pivot-1)/n && (j/3)/v == (pivot-1)%n)
                        for(int k = 0, space = 0; k < 3; k++)
                            in_color[i*in_size+j+k] = color[count_space++];              
        }
        fwrite(in_color, header.height, in_size, pFile2);         
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
        wrong_file;

    printf("Please enter the puzzle: ");
    fgets(step_name, 255, stdin);
    if(step_name[strlen(step_name) - 1] == '\n')
        step_name[strlen(step_name) - 1] = 0;
    
    if((step = fopen(step_name, "r")) == NULL)
        wrong_file;
    puzzle(step, bmp_in);
    fclose(step);
    fclose(bmp_in);
}