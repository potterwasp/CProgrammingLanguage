#include<stdio.h>
#include<ctype.h>
int main(int argC , char ** argV)
{
    char buff[128];
    int count = 0;
    char * ptr = argV[0];
    char * tmp = buff;
    while(*ptr!='\0')
    {
        *tmp = toupper(*ptr);
        tmp++;
        ptr++;
    }
    *tmp = '\0';
    printf("\n%s\n",buff);
    return 0;
}