#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define MINES 5

char mine[SIZE][SIZE];
char show[SIZE][SIZE];

void init() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            mine[i][j] = '0';
            show[i][j] = '*';
        }
    }
}

void placeMines() {
    int count = 0, r, c;
    while (count < MINES) {
        r = rand() % SIZE;
        c = rand() % SIZE;
        if (mine[r][c] != 'M') {
            mine[r][c] = 'M';
            count++;
        }
    }
}

int countMines(int r, int c) {
    int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++) {
        for (j = c - 1; j <= c + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (mine[i][j] == 'M')
                    count++;
            }
        }
    }
    return count;
}

void printBoard() {
    int i, j;
    printf("\n  0 1 2 3 4\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (j = 0; j < SIZE; j++) {
            printf("%c ", show[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int row, col, moves = 0;

    srand(time(0));
    init();
    placeMines();

    while (1) {
        printBoard();
        printf("\nEnter row and column: ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid move!\n");
            continue;
        }

        if (mine[row][col] == 'M') {
            printf("\n💥 Game Over! You hit a mine.\n");
            break;
        }

        show[row][col] = countMines(row, col) + '0';
        moves++;

        if (moves == SIZE * SIZE - MINES) {
            printf("\n🎉 You WIN!\n");
            break;
        }
    }

    return 0;
}
