#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 9;
const int MINES = 10;

struct Cell {
    int isMine;
    int isRevealed;
    int neighborMines;
};

Cell board[SIZE][SIZE];
int dx[8] = {-1,-1,-1,0,1,1,1,0};
int dy[8] = {-1,0,1,1,1,0,-1,-1};

int placeMines() {
    srand(time(0));
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y].isMine == 0) {
            board[x][y].isMine = 1;
            count++;
        }
    }
    return 0;
}

int countNeighbors() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            if (board[x][y].isMine == 1) continue;
            int count = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && ny >= 0 && nx < SIZE && ny < SIZE) {
                    if (board[nx][ny].isMine == 1) count++;
                }
            }
            board[x][y].neighborMines = count;
        }
    }
    return 0;
}

int reveal(int x, int y) {
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE) return 0;
    if (board[x][y].isRevealed == 1) return 0;

    board[x][y].isRevealed = 1;

    if (board[x][y].neighborMines == 0 && board[x][y].isMine == 0) {
        for (int i = 0; i < 8; i++) {
            reveal(x + dx[i], y + dy[i]);
        }
    }

    return 0;
}

int checkWin() {
    int hidden = 0;
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
            if (board[x][y].isRevealed == 0 && board[x][y].isMine == 0)
                hidden++;
    return hidden == 0;
}

int printBoard(int revealAll) {
    cout << "   ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << endl;

    for (int x = 0; x < SIZE; x++) {
        cout << x << " |";
        for (int y = 0; y < SIZE; y++) {
            if (revealAll == 1 || board[x][y].isRevealed == 1) {
                if (board[x][y].isMine == 1) {
                    printf("\033[41;30m* \033[0m"); // Красный фон, чёрная звезда
                }
                else if (board[x][y].neighborMines > 0) {
                    printf("\033[33m%d \033[0m", board[x][y].neighborMines); // Жёлтая цифра
                }
                else {
                    printf("\033[37m. \033[0m"); // Белая пустая
                }
            } else {
                printf("\033[46m  \033[0m"); // Голубой фон, без символа
            }
        }
        cout << endl;
    }
    return 0;
}

int main() {
    placeMines();
    countNeighbors();

    // Первый заголовок и поле
    printf("\033[36;40m");
    cout << "============================\n";
    cout << "     MINESWEEPER GAME\n";
    cout << "============================\n";
    printf("\033[0m");
    printBoard(0);

    while (1) {
        system("clear || cls");
        printf("\033[36;40m");
        cout << "============================\n";
        cout << "     MINESWEEPER GAME\n";
        cout << "============================\n";
        printf("\033[0m");
        printBoard(0);

        int x, y;
        cout << "Enter coordinates (row column): ";
        cin >> x >> y;

        if (x < 0 || y < 0 || x >= SIZE || y >= SIZE) {
            cout << "Invalid coordinates.\n";
            continue;
        }

        if (board[x][y].isMine == 1) {
            system("clear || cls");
            printf("\033[31m\n💥 You hit a mine! Game Over.\n\033[0m");
            printBoard(1);
            break;
        }

        reveal(x, y);

        if (checkWin() == 1) {
            system("clear || cls");
            printf("\033[32m\n🎉 You win! All safe cells revealed.\n\033[0m");
            printBoard(1);
            break;
        }
    }

    return 0;
}
