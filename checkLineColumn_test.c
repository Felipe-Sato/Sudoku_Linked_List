// After compiling the code, type in the terminal "./a.out" + the example file's path (for linux)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct list{
	int info;
	struct list* prox;
}List;

// Prints the list
void printList(List* Ref){
	List* aux = Ref;
	while(aux != NULL){
		printf("%d ", aux->info);
		aux = aux->prox;
	}
	printf("\n");
}

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
void printMat(int** mat){
	for(int i = 0; i < 9; i++){
		if (mat == NULL){
			printf("NULL\n");
			break;
		}
		for(int j = 0; j < 9; j++)
			printf("%d   ", mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

// Frees the memory where the matrix was allocated
int** freeMat(int** mat){
	for(int i = 0; i < 9; i++)
		free(mat[i]);
	free(mat);
	return NULL;
}

// Adds a new element in the list
List* addList(List* Ref, int value){
	List* new = (List*) malloc (sizeof(List));
	new->info = value;
	new->prox = NULL;
	if(Ref == NULL) return new;
	else{
		List* aux = Ref;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = new;
		return Ref;
	}
}

// Creates a list containing all the numbers that can fill an empty space in the matrix
void checkLineColumn(int **M, int l, int c){
	List* candidates = NULL;
	for(int k = 1; k < 10; k++){
		int i;
		for(i = 0; i < 9; i++)
			if(sqrt(pow(M[l][i],2)) == k || sqrt(pow(M[i][c],2)) == k) break;	
		if(i == 9) candidates = addList(candidates, k);
	}
	printList(candidates);
	free(candidates);
}

void main(int argc, char* argv[]){
	int** sudoku = createMat();
	sudoku = fillMat(sudoku, argv[1]);
	printMat(sudoku);
	checkLineColumn(sudoku, 0, 4);
	sudoku = freeMat(sudoku);
}