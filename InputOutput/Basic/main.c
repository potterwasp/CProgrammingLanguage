#include<stdio.h>

//get char 
void GetCharDemo();
//put char
void PutCharDemo();
int main()
{
    //GetCharDemo();
    PutCharDemo();
    return 0;
}

void GetCharDemo()
{
    int c ;
    while( (c = getchar()) != EOF )
    {
        printf("%c\n",c);
    }
   printf("%d\n",c);
}

void PutCharDemo()
{
    int c;
    while( (c = getchar()) != EOF )
    {
        putchar(c);
    }

    putchar(c);
}