#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *allocMemory()     // void포인터 100bytes 동적할당 함수
{
    void *ptr = malloc(100);

    return ptr;
}

void *allocMemory2()
{
    return malloc(100);
}

int main()
{
    char *s1 = allocMemory();
    strcpy(s1, "Hello, World!");
    printf("%s\n", s1);
    free(s1);

    int *numPtr1 = allocMemory();
    numPtr1[0] = 10;    //동적할당이라 추가가능
    numPtr1[1] = 20;
    printf("%d %d\n", numPtr1[0], numPtr1[1]);
    free(numPtr1);

    return 0;
}