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

void change(Bmpheader *header, FILE *fp)
{
	uint32_t info_size = (((uint32_t)header->width*16+31) >> 5) << 2;
	uint32_t head_size = sizeof(Bmpheader) + 12;
	uint8_t mask[12] = {0, 248, 0, 0, 224, 7, 0, 0, 31, 0, 0, 0}; 

	header->bpp = 16;
	header->compression = 3 ; 
	header->bitmap_size = header->height * info_size;
	header->size = (head_size + header->bitmap_size);
	header->offset = head_size;

	fwrite(header, 1, sizeof(Bmpheader), fp);
	fwrite(mask, 1, sizeof(mask), fp);
}

int main()
{
    FILE *pFile, *pFile2;
    char input[255], output[255];
    Bmpheader header;
    
    printf("Please enter the input image name: ");
    fgets(input, 255, stdin);
    if(input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = 0;
    
    if((pFile = fopen(input, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    fread(&header, sizeof(uint8_t), sizeof(header), pFile);
    if(header.bm[0]!= 'B' || header.bm[1]!= 'M')
    {
        printf("This is not bmp file!\n");
        return 0;
    }
    if(header.bpp != 24)
    {
        printf("This is not a 24-bit bmp file!\n");
        return 0;
    }

    printf("Please enter the output image name: ");
    fgets(output, 255, stdin);
    if(output[strlen(output) - 1] == '\n')
        output[strlen(output) - 1] = 0;

    if((pFile2 = fopen(output, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    int in_size = ((header.width*header.bpp+31) >> 5) << 2;
    int out_size = ((header.width*16+31) >> 5) << 2;
    uint8_t *in_color = (uint8_t *)malloc(sizeof(uint8_t) *in_size);
    uint8_t *out_color = (uint8_t *)malloc(sizeof(uint8_t) *out_size*header.height);
    int count = 0;
    
    change(&header, pFile2);   
    for(int i = 0; i < header.height; i++)
    {
        fread(in_color, 1, in_size, pFile);        
        for(int j = 0; j < header.width; j++)
        {
            uint16_t sum = ((in_color[3*j+2] >> 3) << 11)+((in_color[3*j+1] >> 2) << 5)+(in_color[3*j] >> 3);         
            out_color[count++] = sum & 0xFF;
            out_color[count++] = sum >> 8;
        }
    }
    
    fwrite(out_color, out_size, header.height, pFile2);    
    fclose(pFile);
    fclose(pFile2);
    return 0;
}
