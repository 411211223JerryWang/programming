#include <iostream>
#include <vector>

using namespace std;

const int N = 8;

int chess[N][N];

int checkChessColor(int i, int j) {
    return chess[i][j];
}

vector<pair<int, int>> findValidMoves(int i, int j) {
    vector<pair<int, int>> validMoves;
    int currentColor = checkChessColor(i, j);

    if (currentColor == 0) {
        return validMoves;
    }

    int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};

    for (int k = 0; k < 8; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];

        while (x >= 0 && x < N && y >= 0 && y < N) {
            if (chess[x][y] == 0) {
                if (currentColor == 1 || currentColor == 2) {
                    validMoves.push_back(make_pair(x, y));
                }
                break;
            } else if (chess[x][y] == currentColor) {
                break;
            }
            x += dx[k];
            y += dy[k];
        }
    }

    return validMoves;
}

int main() {
    
    int i = 3, j = 3;

    int chessColor = checkChessColor(i, j);
    vector<pair<int, int>> validMoves = findValidMoves(i, j);

    cout << "(" << i << ", " << j << ") 是" << (chessColor == 1 ? "黑棋" : (chessColor == 2 ? "白棋" : "空白")) << endl;
    
    cout << "(" << i << ", " << j << ") 的可下子位置為：";
    for (pair<int, int> move : validMoves) {
        cout << "(" << move.first << ", " << move.second << ") ";
    }
    cout << endl;

    return 0;
}
