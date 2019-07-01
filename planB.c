/*
 * sudokuSolver.c
 * Copyright (c) Mitchell Johnson (ehntoo@gmail.com), 2012
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Returns a dynamic matrix
int** createMat(){
	int** mat = (int**) malloc(9 * sizeof(int*));
	int i;
	for(i = 0; i < 9; i++)
		mat[i] = (int*) malloc(9 * sizeof(int));
	return mat;
}

// Returns the matrix filled by the characters in the read file
int** fillMat(int** mat, char* filePath){
	FILE* file = fopen(filePath, "r");
	if(file == NULL){
		perror("Erro: fopen");
		exit(EXIT_FAILURE);
	}
	int i, j;
	char c;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			c = fgetc(file);
			mat[i][j] = '0' - c;
			c = fgetc(file);
		}
	}
	return mat;
}

// Checks to see if a particular value is presently valid in a given position.
int isValid(int number, int** mat, int l, int c) {
    int i=0;
    int l1 = l - l%3;
    int l2 = l - l%3 + 2;
    int c1 = c - c%3;
    int c2 = c - c%3 + 2;

    // Check for the value in the given line and column
    for (i = 0; i < 9; i++) {
        if (mat[i][c] == number) return 0;
        if (mat[l][i] == number) return 0;
    }
    
    // Check the remaining four spaces in this sector
    if(mat[l1][c1] == number) return 0;
    if(mat[l1][c2] == number) return 0;
    if(mat[l2][c1] == number) return 0;
    if(mat[l2][c2] == number) return 0;
    return 1;
}

// A recursive function that does all the gruntwork in solving the sudoku.
int sudokuHelper(int** mat, int l, int c) {
    int nextNumber = 1;
    // Have we advanced past the sudoku?  If so, hooray, all previous cells have valid contents!  We're done!
    if (l == 9) {
        return 1;
    }
    // Is this element already set?  If so, we don't want to change it.
    if (mat[l][c]) {
        if (c == 8) {
            if (sudokuHelper(mat, l+1, 0)) return 1;
        } else {
            if (sudokuHelper(mat, l, c+1)) return 1;
        }
        return 0;
    }

    // Iterate through the possible numbers for this empty cell and recurse for every valid one, to test if 
    // it's part of the valid solution.
    for (; nextNumber<10; nextNumber++) {
        if(isValid(nextNumber, mat, l, c)) {
            mat[l][c] = nextNumber;
            if (c == 8) {
                if (sudokuHelper(mat, l+1, 0)) return 1;
            } else {
                if (sudokuHelper(mat, l, c+1)) return 1;
            }
            mat[l][c] = 0;
        }
    }
    return 0;
}

// A helper function to call sudokuHelper recursively
int solveSudoku(int** mat) {
    return sudokuHelper(mat, 0, 0);
}

// Prints the matrix
void print(int** mat){
		int i;
		int j;
	for(i = 0; i < 9; i++){
		if (mat == NULL){
			printf("NULL\n");
			break;
		}
		for (j=0; j<9; j++) {
			if (mat[i][j] < 0)
			{
				if (2 == j || 5 == j) {
					printf("%d | ", -1*mat[i][j]);
				} else if (8 == j) {
					printf("%d\n", -1*mat[i][j]);
				} else {
					printf("%d ", -1*mat[i][j]);
				}
			} else {
				if (2 == j || 5 == j) {
					printf("%d | ", mat[i][j]);
				} else if (8 == j) {
					printf("%d\n", mat[i][j]);
				} else {
					printf("%d ", mat[i][j]);
				}
			}
		}
		if (2 == i || 5 == i) {
			puts("------+-------+------");
		}
	}
}

int main(int argc, char** argv) {
    int** sudoku = createMat();
    sudoku = fillMat(sudoku, argv[1]);

	// Timer
	clock_t start = 0, end = 0;
	clock_t total = 0;

    // Print out the original sudoku, then start solving.
    puts("Original sudoku:");
    print(sudoku);
    puts("Solving...");
    puts("");
	start = clock();

    // If successful, print the solution
    if (solveSudoku(sudoku)) {
        puts("Sudoku Solved!");
    } else {
        puts("Illegal sudoku (or a broken algorithm [not likely])");
    }
    
	end = clock();
	total = end - start;
	print(sudoku);
	printf("\nTime %u ms\n", total);

    return 0;
}
