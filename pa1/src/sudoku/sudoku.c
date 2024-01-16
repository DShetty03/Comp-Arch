#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 9


bool isValid(int board[SIZE][SIZE], int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num || board[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}

//check if sudoku is completed but not if it is correct or incorect
bool isCompleted(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                return false; // empty cell found = not completed
            }
        }
    }
    return true; 
}

bool solveSudoku(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0; 
                    }
                }
                return false; //
            }
        }
    }
    return true; 
}

// Check if it is completede and correct
bool CorrectlyCompletedAndCorrect(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int num = board[row][col];
            board[row][col] = 0; 
            if (num != 0 && !isValid(board, row, col, num)) {
                board[row][col] = num; 
                return false; 
            }
            board[row][col] = num; 
        }
    }
    return true; 
}
// Check if Completed but not incorrect
bool CorrectButIncorrect(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int num = board[row][col];
            board[row][col] = 0; 
            if (num != 0 && !isValid(board, row, col, num)) {
                board[row][col] = num; 
                return true; 
            }
            board[row][col] = num; 
        }
    }
    return false; 
}

//will check empty cells. Use it in to see if solvable
int countEmptyCells(int board[SIZE][SIZE]) {
    int count = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                count++;
            }
        }
    }
    return count;
}
//checks if partially completed sudoku is solvable. if false output = "unsolvable"
bool isSolvable(int board[SIZE][SIZE]) {
    int emptyCellCount = countEmptyCells(board);
    if (emptyCellCount != 1) {
        return false; 
    }
    return solveSudoku(board);
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Provide a file name \n" );
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File is NULL \n");
        return EXIT_FAILURE;
    }

   int board[SIZE][SIZE]; //store current state of sudoku for other functions to use
    for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
        char cell = fgetc(file);
        if (cell == EOF) {
            fclose(file);
            printf("Error \n");
            return EXIT_FAILURE;
        }
        if (cell == '_') { // read "_" as an empty cell
            board[row][col] = 0; // Replace the  "_" with 0 for empty cells
        } else if (cell >= '1' && cell <= '9') {
            board[row][col] = cell - '0'; 
        
        } else {
            fclose(file);
            printf("Error2 \n");
            return EXIT_FAILURE;
        }
    }
    char newline = fgetc(file);
    if (newline != '\n') {
        fclose(file);
        printf("Error3 \n");
        return EXIT_FAILURE;
    }
}
    fclose(file);

 if (isCompleted(board)) {
        if (CorrectlyCompletedAndCorrect(board)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    } else {
        if (isSolvable(board)) {
            printf("solvable\n");
        } else {
            printf("unsolvable\n");
        }
    }



 EXIT_SUCCESS;
}