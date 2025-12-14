#include <stdio.h>

int maxIn3() 
{
	int a, b, c;

	printf("세 정수의 최대값을 구합니다.\n");
	printf("a값: "); scanf_s("%d", &a);
	printf("b값: "); scanf_s("%d", &b);
	printf("c값: "); scanf_s("%d", &c);

	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;

	printf("최대값은 %d입니다.\n", max);
	
	return max;
}


int signCheck() 
{
	int n;

	printf("정수: ");
	scanf_s("%d", &n);

	if (n > 0) 
	{
		printf("양수입니다. \n");
		return 1;
	}
	else if (n < 0)
	{
		printf("음수입니다. \n");
		return -1;
	}

	else 
	{
		printf("0입니다.");
		return 0;
	}
}

int drawIsoscelesTriangle() 
{
	int size = 0;

	do
	{
		printf("몇단 이등변 삼각형입니다?: ");
		scanf_s("%d", &size);
	} while (size <= 0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf(" * ");
		}
		putchar('\n');
	}

	return size;
}