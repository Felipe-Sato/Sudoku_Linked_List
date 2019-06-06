// After compiling the code, type in the terminal "./a.out" + the example file's path (for linux)
#include<stdio.h>
#include<stdlib.h>

// Returns a dynamic matrix
int** createMat(){
	int** mat = (int**) malloc(9 * sizeof(int*));
	for(int i = 0; i < 9; i++)
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
	for(int i = 0; i < 9; i++){
		if (mat == NULL){
			printf("NULL\n");
			break;
		}
		for(int j = 0; j < 9; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

// Frees the memory where the matrix was allocated
int** freeMat(int** mat){
	for(int i = 0; i < 9; i++)
		free(mat[i]);
	free(mat);
	return NULL;
}

void main(int argc, char* argv[]){
	int** sudoku = createMat();
	sudoku = fillMat(sudoku, argv[1]);
	print(sudoku);
	sudoku = freeMat(sudoku);
}
