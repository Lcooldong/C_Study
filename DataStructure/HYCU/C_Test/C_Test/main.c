#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() 
{
	int a = 42, r = 3;

	r = a++;

	printf("a=%d\r\n", a);

	int money = 12365798;

	money = money % 1000;

	printf("%d\r\n", money);

	printf("%d\r\n", 15%6);
	printf("%d\r\n", 26%4);

	int b = 35, c = 12;

	c = b++;
	printf("c = %d\r\n", c);


	int money1 = 323370;
	int m_a = money1 / 50000;
	money1 = money1 % 50000;

	printf("%d\r\n", money1);
	printf("%d\r\n", 1 + 5);
	printf("%d\r\n", 44 %45 + 1);

	int robot = 25; int minsu = 0;
	int win = 4; int loose = 3; int number = 15;

	if (number % 2 == 0) robot = 0;
	else robot = 1;

	if (robot == minsu) win++;
	else loose++;

	printf("%d | %d\r\n", win, loose);
	printf("%d\r\n", sizeof(robot));

	int minsu1 = 2;
	int game1 = 4;
	while (game1)
	{
		printf("한양 \r\n");
		game1--;
	}
	
	int sum1 = 0;
	for (int i = 1; i < 6; i++) sum1 += i;
	printf("%d\r\n", sum1);

	int a1 = -280;
	if (a1) printf("참\r\n");

	printf("%d\r\n", 45 >>3);

	int min = 15 / 5;
	int num = 65 % 6;

	if (num > min) printf("컴\r\n");


	return 0;

}