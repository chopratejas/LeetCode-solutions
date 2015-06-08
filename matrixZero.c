#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <limits.h>

#define MATRIX_ROW 50
#define MATRIX_COL 50


void printMatrix(int **matrix, int matrixRowSize, int matrixColSize)
{
    printf("--------------------------------------------------\n");
    for (int j = 0; j < matrixRowSize; j++) {
        for (int i = 0; i < matrixColSize; i++) {
            printf("|%2d|", matrix[i][j]);
        }
        printf("\n");
    }
}

int **createMatrix(int matrixRowSize, int matrixColSize)
{
    int **matrix = calloc(matrixColSize, sizeof(int *));
    for (int i = 0; i < matrixColSize; i++) {
        matrix[i] = calloc(matrixRowSize, sizeof(int));
    }

    for (int i = 0; i < matrixColSize; i++) {
        for (int j = 0; j < matrixRowSize; j++) {
            matrix[i][j] = rand() % 50 + 1;
        }
    }
    return matrix;
}

void freeMatrix(int **matrix, int matrixRowSize, int matrixColSize)
{
    for (int i = 0; i < matrixColSize; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void zeroOutRowCol(int **matrix,
                   bool *matrixRowFlag,
                   bool *matrixColFlag,
                   int matrixRowSize,
                   int matrixColSize)
{
    for (int i = 0; i < matrixColSize; i++) {
        for (int j = 0; j < matrixRowSize; j++) {
            if ((matrixRowFlag[i] == true) || (matrixColFlag[j] == true)) {
                matrix[i][j] = 0;
            }
        }
    }
}

void setZeroes(int** matrix, int matrixRowSize, int matrixColSize)
{
    bool *matrixRowFlag, *matrixColFlag;
    if (matrix == NULL) {
        return;
    }
    if ((matrixColSize <= 1) || (matrixRowSize <= 1)) {
        for (int i = 0; i < matrixColSize; i++) {
            for (int j = 0; j < matrixRowSize; j++) {
                matrix[i][j] = 0;
            }
        }
        return;
    }
    matrixRowFlag = calloc(matrixColSize, sizeof(bool));
    matrixColFlag = calloc(matrixRowSize, sizeof(bool));

    for (int i = 0; i < matrixColSize; i++) {
        for (int j = 0; j < matrixRowSize; j++) {
            if (matrix[i][j] == 0) {
                matrixRowFlag[i] = true;
                matrixColFlag[j] = true;
            }
        }
    }
    zeroOutRowCol(matrix,
                  matrixRowFlag,
                  matrixColFlag,
                  matrixRowSize,
                  matrixColSize);
    free(matrixRowFlag);
    free(matrixColFlag);
}

void setElemZero(int **matrix)
{
    int row = rand() % MATRIX_COL;
    int col = rand() % MATRIX_ROW;
    printf("Setting matrix[%d][%d] : 0\n", row, col);
    matrix[row][col] = 0;
}

int main()
{
    int **matrix = createMatrix(MATRIX_ROW, MATRIX_COL);
    setElemZero(matrix);
    printMatrix(matrix, MATRIX_ROW, MATRIX_COL);
    setZeroes(matrix, MATRIX_ROW, MATRIX_COL);
    printMatrix(matrix, MATRIX_ROW, MATRIX_COL);
    freeMatrix(matrix, MATRIX_ROW, MATRIX_COL);
    return 0;
}
