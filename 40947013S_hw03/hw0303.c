#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

int main()
{
    FILE *pFile , *pFile2;
    char input[255] , output[255];
    double x, y, r;
    Bmpheader header;
    printf("Please enter the input image name: ");
    fgets(input , 255, stdin);
    if(input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = 0;
    
    pFile = fopen(input,"r");
    if(pFile == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    fread(&header, sizeof(header), 1, pFile);
    if(header.bm[0]!= 'B' || header.bm[1]!= 'M')
    {
        printf("This is not bmp file!\n");
        return 0;
    }

    printf("Please enter the output image name: ");
    fgets(output, 255, stdin);
    if(output[strlen(output) - 1] == '\n')
        output[strlen(output) - 1] = 0;

    printf("Please enter the center: ");
    fscanf(stdin, "(%lf, %lf)", &x, &y);

    printf("Please enter the radius: ");
    scanf("%lf", &r);

    pFile2 = fopen(output, "wb");
    if( pFile2 == NULL )
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    fwrite(&header, sizeof(header), 1, pFile2);
    
    int times = header.width * 3 + header.width % 4;
    uint8_t *color = (uint8_t*)malloc(sizeof(uint8_t) * times);    
    uint8_t *n_color = (uint8_t*)malloc(sizeof(uint8_t) * times); 
    for(int i = 0; i < header.height; i++)
    {
        fread(color, 1, times, pFile);        
        for(int k = 0; k < times; k+=3)
        {
            double dx = k/3-x;
            double dy = (header.height-i)-y;
            for(int l = 0; l < 3; l++)
            {
                if((dx*dx + dy*dy) <= (r*r))
                    n_color[k+l] = color[k+l];
                else    
                    n_color[k+l] = 255;
            }            
        }
        fwrite(n_color, 1, times, pFile2);       
    }
    fclose(pFile);
    fclose(pFile2);
    return 0;
}
