#include <iostream>
#include <stdio.h>
#include <random>
#include <cstdlib>
using namespace std;
const int N = 8;
int chese[N][N];
int S[] = {0,0,1,2};
//判斷格子
int checkChessColor(int i, int j) {
    return chese[i][j];
}
//判斷黑棋周圍8格是否可下和是否夾住
int b_around(int i,int j){
    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
    for (int k = 0; k < 8; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (chese[x][y] == 2){
            for (int l = 2; l < 8; ++l) {
                int a = i + l*dx[k];
                int b = j + l*dy[k];
                if (chese[a][b] == 1){
                    return 1;
                }
            }
        }
    }
 }
//判斷白棋周圍8格是否可下和是否夾住
int w_around(int i,int j){
    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
    for (int k = 0; k < 8; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (chese[x][y] == 1){
            for (int l = 2; l < 8; ++l) {
                int a = i + l*dx[k];
                int b = j + l*dy[k];
                if (chese[a][b] == 2){
                    return 1;
                }
            }
        }
    }
}
//執行
int main(){
    //隨機生成棋盤
    int myArray[] = {0,0,1,2};
    int arraySize = sizeof(myArray) / sizeof(myArray[0]);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, arraySize - 1);
    for (int i= 0; i<N; i++){
        for(int j= 0;j<N;j++){
            int randomIndex = distribution(gen);
            int randomChoice = myArray[randomIndex];
            chese[i][j] = randomChoice;
        }
    }  
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << chese[i][j] << ' '; // 输出每个元素的值，用空格分隔
        }
        std::cout << std::endl; // 换行，表示新的一行
    }
    int quit = 0;
    while(quit = 0){
        printf("請輸入想要落子的格子\n");
        int I,J;
        cin>>I>>J;
        if(checkChessColor(I,J) == 0){
            printf("%d",I);
            printf("%d",J);
            printf("為空格\n");
        }
        if(checkChessColor(I,J) == 1){
            printf("%d",I);
            printf("%d",J);
            printf("為黑棋,請重新輸入\n");
            continue;
        }
        if(checkChessColor(I,J) == 2){
            printf("%d",I);
            printf("%d",J);
            printf("為白棋,請重新輸入\n");
            continue;
        }
        printf("請輸入該格子想下的棋子(1為黑棋,2為白棋)\n");
        int color;
        cin>>color;
        if(color == 1){
            if(b_around(I,J) == 1){
                printf("黑棋可以下在");
                printf("%d",I);
                printf("%d\n",J);
                break;
            }
            else{
                printf("黑棋不可下在");
                printf("%d",I);
                printf("%d",J);
                printf("請重新輸入格子\n");
                continue;
            }
        }
        if(color == 2){
            if(b_around(I,J) == 1){
                printf("白棋可以下在");
                printf("%d",I);
                printf("%d\n",J);
                break;
            }
            else{
                printf("白棋不可下在");
                printf("%d",I);
                printf("%d",J);
                printf("請重新輸入格子\n");
                continue;
            }
        }
    }  
}
