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

    pFile2 = fopen(output, "w");
    if( pFile2 == NULL )
    {
        printf("File could not be opened!\n");
        return 0;
    }
    header.bpp = 16;
    fwrite(&header, sizeof(header), 1, pFile2);
    
    int times = header.width * 3 + header.width % 4;
    int n_times = header.width;
    uint8_t a, b, c; 
    uint8_t *color = (uint8_t*)malloc(sizeof(uint8_t) * times);    
    uint16_t *n_color = (uint16_t*)malloc(sizeof(uint16_t) * n_times); 
    for(int i = 0; i < header.height; i++)
    {
        fread(color, 1, times, pFile);        
        for(int k = 0; k < times; k+=3)
        {
            for(int l = 0; l < 3; l++)
            {
                if(l == 0)
                    a = (color[k+l] >> 3) << 11;            
                else if(l == 1)
                    b = (color[k+l] >> 2) << 5;
                else  c = color[k+l] >> 3;
            } 
            n_color[k/3] = (a+b+c);
            //printf("%d\n", k);
        }
        fwrite(n_color, 1, n_times, pFile2);       
    }
    fclose(pFile);
    fclose(pFile2);
    return 0;
}
