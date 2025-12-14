#include <stdio.h>

#define MAX_N 92  // long long으로 안전한 최대 n (Fib(93)부터 오버플로우)

// -------------------------------------------------
// 1. 순수 재귀 (Naive Recursive)
// -------------------------------------------------
long long fib_recursive(int n, long long* call_count) {
    (*call_count)++;              // 함수가 호출될 때마다 증가

    if (n <= 1) return n;
    return fib_recursive(n - 1, call_count)
        + fib_recursive(n - 2, call_count);
}

// -------------------------------------------------
// 2. 하향식 DP (Top-Down, 메모이제이션)
// -------------------------------------------------
long long memo[MAX_N + 1];

void init_memo() {
    for (int i = 0; i <= MAX_N; i++) {
        memo[i] = -1;
    }
}

long long fib_top_down(int n, long long* call_count) {
    (*call_count)++;              // 함수 호출 횟수 기록

    if (n <= 1) return n;

    if (memo[n] != -1) {          // 이미 계산된 값이면 바로 사용
        return memo[n];
    }

    memo[n] = fib_top_down(n - 1, call_count)
        + fib_top_down(n - 2, call_count);
    return memo[n];
}

// -------------------------------------------------
// 3. 상향식 DP (Bottom-Up, 배열 사용)
// -------------------------------------------------
long long fib_bottom_up_array(int n, long long* loop_count) {
    if (n <= 1) {
        *loop_count = 0;
        return n;
    }

    long long dp[MAX_N + 1];      // n <= MAX_N이라고 가정
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        (*loop_count)++;          // 루프 한 번 돌 때마다 증가
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// -------------------------------------------------
// 4. 상향식 DP (Bottom-Up, 메모리 최적화: O(1) 공간)
// -------------------------------------------------
long long fib_bottom_up_optimized(int n, long long* loop_count) {
    if (n <= 1) {
        *loop_count = 0;
        return n;
    }

    long long prev = 0; // F(0)
    long long curr = 1; // F(1)
    long long next;

    for (int i = 2; i <= n; i++) {
        (*loop_count)++;
        next = prev + curr;   // F(i)
        prev = curr;
        curr = next;
    }
    return curr;              // F(n)
}

// -------------------------------------------------
// 5. 피보나치 수열 전체 출력 (0 ~ n)
//    메모리 최적화 Bottom-Up 방식 사용
// -------------------------------------------------
void print_fib_sequence(int n) {
    printf("\n[Sequence] Fibonacci 0..%d:\n", n);

    if (n >= 0) printf("F(0) = 0\n");
    if (n >= 1) printf("F(1) = 1\n");

    long long prev = 0;
    long long curr = 1;
    long long next;

    for (int i = 2; i <= n; i++) {
        next = prev + curr;       // F(i)
        printf("F(%d) = %lld\n", i, next);
        prev = curr;
        curr = next;
    }
}

// -------------------------------------------------
// main: 네 가지 방식 성능 비교 + 수열 출력
// -------------------------------------------------
int main(void) {
    int n = 5;
    //printf("n을 입력하세요 (0 ~ %d, naive 재귀는 40 이하 권장): ", MAX_N);
    //if (scanf("%d", &n) != 1 || n < 0 || n > MAX_N) {
    //    printf("잘못된 입력입니다.\n");
    //    return 1;
    //}

    long long result;
    long long count_recursive = 0;
    long long count_topdown = 0;
    long long count_bottomupArr = 0;
    long long count_bottomupOpt = 0;

    // 1) 순수 재귀
    result = fib_recursive(n, &count_recursive);
    printf("\n[Naive Recursive]\n");
    printf("F(%d) = %lld\n", n, result);
    printf("함수 호출 횟수 = %lld\n", count_recursive);

    // 2) 하향식 DP (Top-Down, 메모이제이션)
    init_memo();
    result = fib_top_down(n, &count_topdown);
    printf("\n[Top-Down DP (Memoization)]\n");
    printf("F(%d) = %lld\n", n, result);
    printf("함수 호출 횟수 = %lld\n", count_topdown);

    // 3) 상향식 DP (Bottom-Up, 배열 사용)
    result = fib_bottom_up_array(n, &count_bottomupArr);
    printf("\n[Bottom-Up DP (Array)]\n");
    printf("F(%d) = %lld\n", n, result);
    printf("루프 횟수 = %lld\n", count_bottomupArr);

    // 4) 상향식 DP (Bottom-Up, 메모리 최적화)
    result = fib_bottom_up_optimized(n, &count_bottomupOpt);
    printf("\n[Bottom-Up DP (Optimized, O(1) Memory)]\n");
    printf("F(%d) = %lld\n", n, result);
    printf("루프 횟수 = %lld\n", count_bottomupOpt);

    printf("\n이론적 시간 복잡도:\n");
    printf("  Naive Recursive           : 대략 O(phi^n) (지수 시간)\n");
    printf("  Top-Down DP (Memoization) : O(n)\n");
    printf("  Bottom-Up DP (Array)      : O(n)\n");
    printf("  Bottom-Up DP (Optimized)  : O(n), 공간 O(1)\n");

    // 피보나치 수열 전체 출력
    print_fib_sequence(n);

    return 0;
}
