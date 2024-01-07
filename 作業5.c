#include <stdio.h>

#define SIZE 8

void printChess(int chess[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", chess[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 翻轉棋子
void flipPieces(int chess[SIZE][SIZE], int i, int j, int user) {
    int flips = countFlips(chess, i, j, user);

    if (flips > 0) {
        // 翻轉棋子
        chess[i][j] = user;

        // 上
        for (int k = 1; k <= flips; k++) {
            chess[i - k][j] = user;
        }
        // 下
        for (int k = 1; k <= flips; k++) {
            chess[i + k][j] = user;
        }
        // 左
        for (int k = 1; k <= flips; k++) {
            chess[i][j - k] = user;
        }
        // 右
        for (int k = 1; k <= flips; k++) {
            chess[i][j + k] = user;
        }
        // 左上
        for (int k = 1; k <= flips; k++) {
            chess[i - k][j - k] = user;
        }
        // 右上
        for (int k = 1; k <= flips; k++) {
            chess[i - k][j + k] = user;
        }
        // 左下
        for (int k = 1; k <= flips; k++) {
            chess[i + k][j - k] = user;
        }
        // 右下
        for (int k = 1; k <= flips; k++) {
            chess[i + k][j + k] = user;
        }
    } else {
        printf("無效的移動。\n");
    }
}

// 計算可翻轉的數量
int countFlips(int chess[SIZE][SIZE], int i, int j, int user) {
    if (chess[i][j] != 0) {
        return 0;
    }

    int flips = 0;

    // 上
    for (int k = 1; i - k >= 0 && chess[i - k][j] != 0 && chess[i - k][j] != user; k++) {
        if (chess[i - k][j] == user) {
            flips += k - 1;
            break;
        }
    }
    // 下
    for (int k = 1; i + k < SIZE && chess[i + k][j] != 0 && chess[i + k][j] != user; k++) {
        if (chess[i + k][j] == user) {
            flips += k - 1;
            break;
        }
    }
    // 左
    for (int k = 1; j - k >= 0 && chess[i][j - k] != 0 && chess[i][j - k] != user; k++) {
        if (chess[i][j - k] == user) {
            flips += k - 1;
            break;
        }
    }
    // 右
    for (int k = 1; j + k < SIZE && chess[i][j + k] != 0 && chess[i][j + k] != user; k++) {
        if (chess[i][j + k] == user) {
            flips += k - 1;
            break;
        }
    }
    // 左上
    for (int k = 1; i - k >= 0 && j - k >= 0 && chess[i - k][j - k] != 0 && chess[i - k][j - k] != user; k++) {
        if (chess[i - k][j - k] == user) {
            flips += k - 1;
            break;
        }
    }
    // 右上
    for (int k = 1; i - k >= 0 && j + k < SIZE && chess[i - k][j + k] != 0 && chess[i - k][j + k] != user; k++) {
        if (chess[i - k][j + k] == user) {
            flips += k - 1;
            break;
        }
    }
    // 左下
    for (int k = 1; i + k < SIZE && j - k >= 0 && chess[i + k][j - k] != 0 && chess[i + k][j - k] != user; k++) {
        if (chess[i + k][j - k] == user) {
            flips += k - 1;
            break;
        }
    }
    // 右下
    for (int k = 1; i+ k < SIZE && j + k < SIZE && chess[i + k][j + k] != 0 && chess[i + k][j + k] != user; k++) {
        if (chess[i + k][j + k] == user) {
            flips += k - 1;
            break;
        }
    }

    return flips;
}

int main() {
    int chess[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 1, 0, 0, 0},
        {0, 0, 0, 1, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    printf("原始棋盤:\n");
    printChess(chess);

    int i, j;
    int user = 1;           // 假設黑子先下

    printf("請輸入要下的位置 (i j): ");   
    scanf("%d %d", &i, &j);

    flipPieces(chess, i, j, user);
    
    printf("翻轉後的棋盤:\n");
    printChess(chess);

    return 0;
}