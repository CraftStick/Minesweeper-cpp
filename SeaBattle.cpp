#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int ships[10][10] = {0};
    int x, y;

    srand(time(0));
    for (int i = 0; i < 5; ) {
        x = rand() % 10;
        y = rand() % 10;
        if (ships[x][y] == 0) {
            ships[x][y] = 1;
            i++;
        }
    }

    while (1) {
        system("clear || cls");
        printf("\033[36;40m");
        cout << "===========================\n";
        cout << "       SEA BATTLE GAME\n";
        cout << "===========================\n";
        printf("\033[0m");

        printf("\033[33;40m  ");
        for (int i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");

        for (int i = 0; i < 10; i++) {
            printf("\033[33;40m%d ", i);
            for (int j = 0; j < 10; j++) {
                if (ships[i][j] == 0 || ships[i][j] == 1) {
                    printf("\033[34;44m  ");
                }
                else if (ships[i][j] == 2) {
                    printf("\033[31;47mX ");
                }
                else {
                    printf("\033[30;47mO ");
                }
            }
            printf("\n");
        }
        printf("\033[0m");

        int ships_left = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (ships[i][j] == 1) ships_left++;
            }
        }
        if (ships_left == 0) {
            printf("\033[32;40m");
            cout << "\nCongratulations! You sank all the ships!\n";
            printf("\033[0m");
            break;
        }

        printf("\033[33;40m");
        cout << "\nShips remaining: " << ships_left << endl;
        printf("\033[37;40m");
        cout << "Enter shot coordinates (row column): ";
        cin >> x >> y;

        if (x < 0 || x > 9 || y < 0 || y > 9) {
            printf("\033[31;40m");
            cout << "Invalid coordinates! Use numbers from 0 to 9.\n";
            printf("\033[0m");
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        if (ships[x][y] == 1) {
            ships[x][y] = 2;
            printf("\033[32;40m");
            cout << "Hit!\n";
            printf("\033[0m");
        }
        else if (ships[x][y] == 0) {
            ships[x][y] = 3;
            printf("\033[31;40m");
            cout << "Miss!\n";
            printf("\033[0m");
        }
        else {
            printf("\033[33;40m");
            cout << "You already shot here!\n";
            printf("\033[0m");
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
