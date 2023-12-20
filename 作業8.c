#include <stdio.h>

#define MAX_N 10
#define STACK_SIZE (MAX_N * MAX_N)

int maze[MAX_N][MAX_N] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

//定義
typedef struct {
    int x, y;
} Point;

//定義Stack
typedef struct {
    Point array[STACK_SIZE];
    int size;
} Stack;

// 初始化堆疊
void initStack(Stack *stack) {
    stack->size = 0;
}

// 將座標推入堆疊
void push(Stack *stack, int x, int y) {
    Point p = {x, y};
    stack->array[stack->size++] = p;
}

// 從堆疊彈出座標
Point pop(Stack *stack) {
    return stack->array[--stack->size];
}

// 堆疊是否為空
int isEmpty(Stack *stack) {
    return stack->size == 0;
}

// 檢查座標是否可通移過去
int Move(int x, int y) {
    return (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && maze[x][y] == 0);
}

// 印出迷宮
void printMaze() {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            printf("%c ", (maze[i][j] == 1) ? '#' : ((maze[i][j] == 0) ? '.' : 'x'));
        }
        printf("\n");
    }
    printf("\n");
}

// 刪除多餘的步數
void change(int startX, int startY, int endX, int endY){
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            if (maze[i][j] == 'x' && (i != startX && j != startY) && (i != endX && j != endY)){ //迴圈判斷是否為走過的路徑X
                if (i == 0 && j == 0) {     //若是在最左上角的x
                    int space = 0;
                    if (maze[i+1][j] == 'x'){
                        space += 1;
                    }
                    if (maze[i][j+1] == 'x'){
                        space += 1;
                    }
                    if (space == 1){        //若只有與其他一個x相連代表是多餘的路徑
                        maze[i][j] == 1;     //重製成牆壁
                    }
                }
                if (i == 9 && j == 9) {     //若是在最右下角的x
                    int space = 0;
                    if (maze[i-1][j] == 'x'){
                        space += 1;
                    }
                    if (maze[i][j-1] == 'x'){
                        space += 1;
                    }
                    if (space == 1){
                        maze[i][j] == 1;
                    }
                }
                if (i == 0 && j == 9) {     //若是在最右上角的x
                    int space = 0;
                    if (maze[i][j-1] == 'x'){
                        space += 1;
                    }
                    if (maze[i+1][j] == 'x'){
                        space += 1;
                    }
                    if (space == 1){
                        maze[i][j] == 1;
                    }
                }
                if (i == 9 && j == 0) {     //若是在最左下角的x
                    int space = 0;
                    if (maze[i][j+1] == 'x'){
                        space += 1;
                    }
                    if (maze[i-1][j] == 'x'){
                        space += 1;
                    }
                    if (space == 1){
                        maze[i][j] == 1;
                    }
                }
                if (i == 0 || i == 9){      //若是在上下兩邊的x
                    int space = 0;
                    if (maze[i][j+1] == 'x'){
                        space += 1;
                    }
                    if (maze[i][j-1] == 'x'){
                        space += 1;
                    }
                    if (space == 1){
                        maze[i][j] == 1;
                    }
                }
                if (j == 0 || j == 9){      //若是在左右兩邊的x
                    int space = 0;
                    if (maze[i+1][j] == 'x'){
                        space += 1;
                    }
                    if (maze[i-1][j] == 'x'){
                        space += 1;
                    }
                    if (space == 1){
                        maze[i][j] == 1;
                    }
                }
            }
        }
    }
}

//比較找出最短部步數
int shorteststeps(int startX, int startY, int endX, int endY) {
    int step = 1;
    int newstep = 0;    //設定新舊步數
    while (step != newstep){    //重複直到新舊步數一樣
        step = newstep; //更新步數
        change(startX, startY, endX, endY); //刪除多餘的步數
        for (int i = 0; i < MAX_N; i++) {
            for (int j = 0; j < MAX_N; j++) {
                if (maze[i][j] == 'x') {    //計算所有步數
                    newstep += 1;
                }
            }
        }
    }
    return step;   //回傳最小步數
}

// 使用堆疊找出老鼠走過的路徑
int findMosesteps(int startX, int startY, int endX, int endY) {
    Stack stack;
    initStack(&stack);
    push(&stack, startX, startY);   //初始化後放入起點

    while (!isEmpty(&stack)) {  //當堆疊內還有路徑可以走
        Point current = pop(&stack);    //拿出可以走的座標並定義
        int x = current.x;
        int y = current.y;

        // 如果走到出口，則印出路徑和最小步數並結束
        if (x == endX && y == endY) {
            maze[x][y] = 'x';
            int ans = shorteststeps(startX, startY, endX, endY);
            printf("宮入口至出口老鼠所走過的路徑(x):\n");
            printMaze();
            printf("一共走了%d步\n", ans);
            return 1; // 返回 1 代表找到路徑
        }

        // 標記目前位置為走過的路徑
        maze[x][y] = 'x';
        // 嘗試往上、下、左、右四個方向判斷是否可以通行並加入堆疊
        if (Move(x - 1, y)) push(&stack, x - 1, y);
        if (Move(x + 1, y)) push(&stack, x + 1, y);
        if (Move(x, y - 1)) push(&stack, x, y - 1);
        if (Move(x, y + 1)) push(&stack, x, y + 1);
    }

    // 若程式執行到這裡，代表沒有找到路徑
    printf("找不到路徑。\n");
    return 0; // 返回 0 代表未找到路徑
}

int main() {

    printf("迷宮入口至出口老鼠所走過的路徑：\n");
    findMosesteps(6, 9, 1, 0);
    return 0;
}
