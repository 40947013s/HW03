#include <stdio.h>
#include <setjmp.h>

jmp_buf jmpbuffer;

void bigger_than_zero(int v) 
{
    if(v > 0) longjmp(jmpbuffer, 1);
    return;
}
void smaller_than_zero(int v) 
{
    if(v < 0) longjmp(jmpbuffer, 2);
    return;
}
void is_zero(int v) 
{
    if(v == 0) longjmp(jmpbuffer, 3);
    return;
}


int main() 
{
    printf("Input integer : ");
    int v; scanf("%d", &v);
    int jmpVal = setjmp(jmpbuffer);    
    switch(jmpVal)
    {
        case 1:
            printf("positive\n"); return 0;
        case 2:
            printf("negative\n"); return 0;
        case 3:
            printf("is zero\n"); return 0;
    }    
    bigger_than_zero(v);
    smaller_than_zero(v);
    is_zero(v);   
        
    return 0;
}