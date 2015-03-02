#include <stdio.h>

int main()
{
    char name[50];
        printf("entre name : ");
        //scanf("%c",&name);
        fgets(name,50,stdin);
        printf("Hello %s",name);
}

