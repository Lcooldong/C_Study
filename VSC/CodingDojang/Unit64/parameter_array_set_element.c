#include <stdio.h>

void setElement(int arr[])
{
    arr[2] = 300;
}

int main()
{
    int numArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    setElement(numArr); // 배열 = 포인터 -> 주소 전달

    printf("%d\n", numArr[2]);

    return 0;
}