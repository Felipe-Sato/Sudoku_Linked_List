// After compiling the code, type in the terminal "./a.out" + the example file's path (for linux)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

// Prints the matrix
void print(int** mat){
		int i;
		int j;
	for(i = 0; i < 9; i++){
		if (mat == NULL){
			printf("NULL\n");
			break;
		}
		for(j = 0; j < 9; j++)
			printf("%d\t", mat[i][j]);
		printf("\n");
	}
}

// Frees the memory where the matrix was allocated
int** freeMat(int** mat){
	int i;
	for(i = 0; i < 9; i++)
		free(mat[i]);
	free(mat);
	return NULL;
}

// SOLUTION

int checkColumn(int **M, int i, int j) {
    for (i = 0; i < 9; i++) {
		if (M[i][j] > 0) {
			int k;
			for (k = 0; k < 9; k++) {
				if (M[i][j] == M[k][j] || M[i][j] == (-1)*M[k][j]) {
					printf("Column Nega\n");
					return 1;
				}
			}
		}
    }
	return 0;
}

int checkLine(int **M, int i, int j) {
	for (j = 0; j < 9; j++) {
		if (M[i][j] > 0) {
			int k;
			for (k = 0; k < 9; k++) {
				if (M[i][j] == M[i][k] || M[i][j] == (-1)*M[i][k]) {
					printf("Line Nega\n");
					return 1;
				}
			}
		}
	}
	return 0;
}

void Line (int **M, int i, int j, int valor) {
    if (valor <= 9) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
				if (M[i][j] < 0) {
					++j;
				} else {
					if (checkColumn(M, 0, j) == 0 && checkLine(M, i, 0) == 0) {
						printf("\nAprova\n");
						M[i][j] = valor;
						printf("\n\nValor: %i\n", valor);
						print(M);
					}
				}
            }
        }
		// printf("\n\nValor: %i\n", valor);
		// print(M);
		Line(M,0,0,(valor+1));
    }
}

void recall (int **M, int i, int j) {
    for ( i = 0; i < 9; i++) {
        for ( j = 0; j < 3; j++) {
            if (M[i][j] == 0) {
                Line( M, 0, 0, 1);
            }
        }
    }
}

void main(int argc, char* argv[]){
	int** sudoku = createMat();
	sudoku = fillMat(sudoku, argv[1]);
	print(sudoku);
	recall(sudoku, 0,0);
	printf("\n\n");
	print(sudoku);
	sudoku = freeMat(sudoku);
}
