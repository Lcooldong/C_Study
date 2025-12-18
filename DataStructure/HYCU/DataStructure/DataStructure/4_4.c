#include "4_4.h"

int insertElemnt(int L[], int n, int x)
{
	int i, k = 0, move = 0; // move는 자리이동 횟수 카운터
	// 원소의 크기를 비교하여 삽입 위치 k 찾기
	for (i = 0; i < n; i++)
	{
		if (L[i] <= x && x <= L[i + 1]) 
		{
			k = i + 1;
			break;
		}
	}
	if (i == n) k = n; // 삽입 위치가 가장 큰 원소인 경우

	// 마지막 원소부터 k+1 원소까지 뒤로 자리이동
	for (i = n; i > k; i--)
	{
		L[i] = L[i - 1];
		move++;
	}

	L[k] = x; // 자리 이동하여 만든 자리 k에 삽입 원소 저장
	return move;
}

int deleteElement(int L[], int n, int x)
{

}