#include <stdio.h>
#define BOARD_SIZE 8

char board[BOARD_SIZE][BOARD_SIZE];

// 函數原型
void initializeBoard();
void printBoard();
int isValidMove(int x, int y, int player);
void flipTiles(int x, int y, int player);
int isGameOver();
void computerMove();
int countTiles(int player);

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }

    // 初始局面
    board[3][3] = board[4][4] = 2;
    board[3][4] = board[4][3] = 1;
}

void printBoard() {
    printf("\n  0 1 2 3 4 5 6 7\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isValidMove(int i, int j, int player) {
    //檢查移動是否合法
    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
    for (int k = 0; k < 8; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (board[x][y] != player){   //判斷旁邊是否有白棋
            for (int l = 2; l < 8; ++l) {
                int a = i + l*dx[k];
                int b = j + l*dy[k];
                if (board[a][b] == player){    //判斷白棋後方是否有黑棋
                    return 1;
                }
            }
        }
        else return 0;
    }
}

void flipTiles(int i, int j, int player) {
    //翻轉對手的棋子
    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
    for (int k = 0; k < 8; ++k) {
      for (int l = 1; l < 8; ++l) {
        int x = i + l*dx[k];
        int y = j + l*dy[k];
        if (board[x][y] != player){   //判斷後面是否為不同棋子
            for (int o = 1; l < 8; ++o) {
                int a = x + o*dx[k];
                int b = y + o*dy[k];
                if (board[a][b] == player){    //判斷不同棋子後方是否有相同棋子
                    board[x][y] == player;
                }
            }
        }
    }
 }
}
int isGameOver() {
    //檢查遊戲是否結束
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (board[i][j] == 0){
          return 1;
        }
      }
    }
    return 0;
}

void computerMove() {
    //電腦下白棋的邏輯
    char drop_point[BOARD_SIZE][BOARD_SIZE];
    int w = 0;
    int z = 0;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
        int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
        if (board[i][j] == 0){
          for (int k = 0; k < 8; ++k) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (board[x][y] == 1){   //判斷旁邊是否有黑棋
                for (int l = 2; l < 8; ++l) {
                    int a = i + l*dx[k];
                    int b = j + l*dy[k];
                    if (board[a][b] == 2){    //判斷黑棋後方是否有白棋
                        drop_point[i][j] == 1;  //紀錄可以下的點位
                    }
                }
            }
          }
        }
      }
    }
    int exitLoop = 0;
    for (int i = rand() % 8; !exitLoop;) {
      for (int j = rand() % 8;) {
        if (drop_point[i][j] == 1){    //隨機選取可以下的點位
          w = i;
          z = j;
          exitLoop = 1; // 設定標誌變數，表示要跳出迴圈
          break;
        }
      }
    }
    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
    for (int k = 0; k < 8; ++k) {
        for (int l = 1; l < 8; ++l) {
            int x = w + l*dx[k];
            int y = z + l*dy[k];
            if (board[x][y] == 1){   //判斷後面是否為不同棋子
                for (int o = 1; l < 8; ++o) {
                    int a = x + o*dx[k];
                    int b = y + o*dy[k];
                    if (board[a][b] == 2){    //判斷不同棋子後方是否有相同棋子
                        board[x][y] == 2;
                    }
                }
            }
        }
    }
}
int countTiles(int player) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int currentPlayer = 1;  // 黑棋先行
    int x, y;

    initializeBoard();

    while (!isGameOver()) {
        printBoard();

        if (currentPlayer == 1) {
            // 玩家下黑棋
            printf("請輸入下棋位置（行 列）：");
            scanf("%d %d", &x, &y);

            if (isValidMove(x, y, currentPlayer)) {
                board[x][y] = 1;
                flipTiles(x, y, currentPlayer);
                currentPlayer = 2;  // 換白棋下
            } else {
                printf("無效的移動，請重試。\n");
            }
        } else {
            // 電腦下白棋
            computerMove();
            currentPlayer = 1;  // 換黑棋下
        }
    }

    printBoard();
    printf("遊戲結束，黑棋：%d，白棋：%d。\n", countTiles(1), countTiles(2));

    return 0;
}