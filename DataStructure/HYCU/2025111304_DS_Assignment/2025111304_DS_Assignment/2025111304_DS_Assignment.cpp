#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int timestamp;  // 로그 시간 (ms)
    int value;      // 예: 센서값, 이벤트 코드 등
} Log;

// =======================
// 1. 편향 이진 검색 트리 (BST)
// =======================

typedef struct BstNode {
    Log log;
    struct BstNode* left;
    struct BstNode* right;
} BstNode;

BstNode* bst_new_node(Log log) {
    BstNode* n = (BstNode*)malloc(sizeof(BstNode));
    n->log = log;
    n->left = n->right = NULL;
    return n;
}

// 균형을 전혀 잡지 않는 단순 BST 삽입
BstNode* bst_insert(BstNode* node, Log log) {
    if (node == NULL)
        return bst_new_node(log);

    if (log.timestamp < node->log.timestamp)
        node->left = bst_insert(node->left, log);
    else if (log.timestamp > node->log.timestamp)
        node->right = bst_insert(node->right, log);
    // 같으면 무시 (단순화)
    return node;
}

// BST 탐색 (비교 횟수 세기)
Log* bst_search(BstNode* root, int timestamp, int* comparisons) {
    BstNode* cur = root;
    while (cur != NULL) {
        (*comparisons)++;
        if (timestamp == cur->log.timestamp) {
            return &cur->log;
        }
        else if (timestamp < cur->log.timestamp) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    return NULL;
}

// =======================
// 2. AVL 트리 (균형 이진 검색 트리)
// =======================

typedef struct AvlNode {
    Log log;
    struct AvlNode* left;
    struct AvlNode* right;
    int height;
} AvlNode;

int height(AvlNode* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AvlNode* avl_new_node(Log log) {
    AvlNode* n = (AvlNode*)malloc(sizeof(AvlNode));
    n->log = log;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

// 오른쪽 회전
AvlNode* rotate_right(AvlNode* y) {
    AvlNode* x = y->left;
    AvlNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// 왼쪽 회전
AvlNode* rotate_left(AvlNode* x) {
    AvlNode* y = x->right;
    AvlNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int get_balance(AvlNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// AVL 삽입 (키: timestamp)
AvlNode* avl_insert(AvlNode* node, Log log) {
    if (node == NULL)
        return avl_new_node(log);

    if (log.timestamp < node->log.timestamp)
        node->left = avl_insert(node->left, log);
    else if (log.timestamp > node->log.timestamp)
        node->right = avl_insert(node->right, log);
    else
        return node; // 중복 키는 무시

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Left Left
    if (balance > 1 && log.timestamp < node->left->log.timestamp)
        return rotate_right(node);

    // Right Right
    if (balance < -1 && log.timestamp > node->right->log.timestamp)
        return rotate_left(node);

    // Left Right
    if (balance > 1 && log.timestamp > node->left->log.timestamp) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // Right Left
    if (balance < -1 && log.timestamp < node->right->log.timestamp) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

// AVL 탐색 (비교 횟수 세기)
Log* avl_search(AvlNode* root, int timestamp, int* comparisons) {
    AvlNode* cur = root;
    while (cur != NULL) {
        (*comparisons)++;
        if (timestamp == cur->log.timestamp) {
            return &cur->log;
        }
        else if (timestamp < cur->log.timestamp) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    return NULL;
}

// 디버그용 중위 순회 (정렬 확인)
void bst_inorder(BstNode* root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->log.timestamp);
    bst_inorder(root->right);
}

void avl_inorder(AvlNode* root) {
    if (!root) return;
    avl_inorder(root->left);
    printf("%d ", root->log.timestamp);
    avl_inorder(root->right);
}


int fib(int n) {
    if (n <= 2) {
        return 1;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}



int factorial() 
{

    return 0;
}



int main() {
    const int N = 32;      // 노드 수 (조금 크게 해서 차이를 더 잘 보이게)
    Log logs[N];

    // 0, 10, 20, ... 정렬된 로그 생성
    for (int i = 0; i < N; i++) {
        logs[i].timestamp = i * 10;
        logs[i].value = i;
    }

    // 1) 편향 BST 구성 (정렬된 데이터 그대로 순서대로 삽입 → 오른쪽으로 쭉 늘어짐)
    BstNode* bstRoot = NULL;
    for (int i = 0; i < N; i++) {
        bstRoot = bst_insert(bstRoot, logs[i]);
    }

    // 2) AVL 트리 구성 (같은 순서로 삽입하지만 회전으로 균형 유지)
    AvlNode* avlRoot = NULL;
    for (int i = 0; i < N; i++) {
        avlRoot = avl_insert(avlRoot, logs[i]);
    }

    printf("BST inorder timestamps : ");
    bst_inorder(bstRoot);
    printf("\n");

    printf("AVL inorder timestamps : ");
    avl_inorder(avlRoot);
    printf("\n");

    // 최악에 가까운 케이스: 마지막 원소 찾기 (timestamp = (N-1)*10)
    int targetTime = (N - 1) * 10;

    int bst_comp = 0;
    int avl_comp = 0;

    Log* r1 = bst_search(bstRoot, targetTime, &bst_comp);
    Log* r2 = avl_search(avlRoot, targetTime, &avl_comp);

    printf("\n=== 검색 대상 timestamp = %d ===\n", targetTime);

    if (r1)
        printf("편향 BST 탐색: value = %d, 비교 횟수 = %d\n", r1->value, bst_comp);
    else
        printf("편향 BST 탐색: 찾지 못함, 비교 횟수 = %d\n", bst_comp);

    if (r2)
        printf("AVL  탐색   : value = %d, 비교 횟수 = %d\n", r2->value, avl_comp);
    else
        printf("AVL  탐색   : 찾지 못함, 비교 횟수 = %d\n", avl_comp);

    printf("\n이론적 시간 복잡도 (N = %d):\n", N);
    printf("  편향 BST  : O(N)  (여기서는 사실상 연결 리스트)\n");
    printf("  AVL 트리  : O(log N)\n");


    int n = 3;

    for (int i = 1; i <= n; i++) {
        printf("%d ", fib(i));
    }
    printf("\n");

    int f1 = 1, f2 = 1, f3;

    for (int j = 1; j <= n; j++)
    {
        if (j <= 2)
        {
            printf("%d ", f2);
        }
        else
        {
            f3 = f1 + f2;
            printf("%d ", f3);
            f1 = f2;
            f2 = f3;
        }
    }
    printf("\n");

    


    return 0;
}
