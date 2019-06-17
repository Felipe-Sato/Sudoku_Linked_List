#include<stdio.h>
#include<stdlib.h>

// check line
void checkLine (int **M, int i, int j, int valor) {
    if (i < 9 && j < 9) {
        if (M[i][j] < 0) {
            checkLine(M, i++, j, valor);
        } else {
            int k;
            for (k = 0; k < 9; k++) {
                if (M[i][j] == M[k][j] || M[i][j] == (-1)*(M[k][j])) {
                    M[i][j] = 0;
                } else {
                    M[i][j] = valor;
                }
            }
            checkLine(M, i++, j, valor++);            
        }
    } else {
        checkLine(M, i++, j++, valor++);
    }
}
// check collumn
void checkCollumn (int **M, int i, int j, int valor) {
    if (i < 9 && j < 9) {
        if (M[i][j] < 0) {
            checkCollumn(M, i, j++, valor);
        } else {
            int k;
            for (k = 0; k < 9; k++) {
                if (M[i][j] == M[i][k] || M[i][j] == (-1)*(M[i][k])) {
                    M[i][j] = 0;
                } else {
                    M[i][j] = valor;
                }
            }
            checkCollumn(M, i++, j, valor++);            
        }
    } else {
        checkCollumn(M, i++, j++, valor++);
    }
}

// In progress...:
// check quadrant
void checkQuadrant (int **M, int i, int j, int valor) {
    if (i < (i+3) && j < (j+3)) {
        int k = 0;
        for (i = 0; i < (i+3); i++) {
            if (M[i][k] == M[i][j] || M[i][k] == ((-1)*M[i][j])) {
                M[i][k] = 0;
            }
            ++k;
            ++j;
        }
    }
}

// check quadrant line

// check quadrant collumn

