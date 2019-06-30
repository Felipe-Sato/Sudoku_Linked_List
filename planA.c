#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct list {
	int info;
	struct list *prox;
} List;

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

// Frees the memory where the matrix was allocated
int** freeMat(int** mat){
	int i;
	for(i = 0; i < 9; i++)
		free(mat[i]);
	free(mat);
	return NULL;
}

// Adds a new element in the first position of the list
List *addElement(List *L, int data) {
	List *new = (List*)malloc(sizeof(List));
    new->info = data;
    new->prox = L;
    return new;
}

// Creates a list containing all the numbers that can fill an empty space in the matrix
List *checkLineColumn(int **M, int l, int c){
	List* candidates = NULL;
	int k;
	for(k = 1; k < 10; k++) {
		int i;
		for(i = 0; i < 9; i++) {
			if(sqrt(pow(M[l][i],2)) == k || sqrt(pow(M[i][c],2)) == k) { 
				break;
			}
		}
		if(i == 9) {
			candidates = addElement(candidates, k);
		}
	}
	return candidates;
}

// Creates a list containing all the numbers that can fill an empty space in the matrix
List *checkQuadrant(int **M, int l, int c){
	List* candidates = NULL;
	int k;
	for(k = 1; k < 10; k++){
		int i, j;
		for(i = l - l % 3; i < l - l % 3 + 3; i++){
			for(j = c - c % 3; j < c - c % 3 + 3; j++)
				if(sqrt(pow(M[i][j],2)) == k || sqrt(pow(M[i][j],2)) == k) break;
			if(j != c - c % 3 + 3) break;
		}
		if(i == l - l % 3 + 3 && j == c - c % 3 + 3) candidates = addElement(candidates, k);
	}
	return candidates;
}

// Verify if the sudoku is completely filled
int verifySolution(int** mat){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(mat[i][j] == 0) return 1;
	return 0;
}

// Return a list from the intersection of others two.
List* intersect(List* line, List* quad){
	List* new = NULL;
	List* aux1 = line;
	List* aux2 = quad;
	if(line != NULL && quad != NULL){
		while(aux1 != NULL){
			while(aux2 != NULL){
				if(aux1->info == aux2->info)
					new = addElement(new, aux2->info);	
				
					aux2 = aux2->prox;
			}
			aux1=aux1->prox;
			aux2 = quad;
		}
	}
	return new;
}

// A function that gets 3 different structure lists with possible elements for the free spaces in the sudoku
void findCandidates(int** mat, int i, int j){
	List* linePos = checkLineColumn(mat, i, j);
	if(linePos != NULL)
		if(linePos->prox == NULL)
			mat[i][j] = linePos->info;
	else{
		List* quadPos = checkQuadrant(mat, i, j);
		if(quadPos != NULL)
			if(quadPos->prox == NULL)
				mat[i][j] = quadPos->info;
		else{
			List* commom = intersect(linePos, quadPos);
			if(commom != NULL)
				if(commom->prox == NULL)
					mat[i][j] = commom->info;
		}
	}
}

// Gets the solution
int** solver(int** mat){
	int i, j;
	while(verifySolution(mat)){
		for(i = 0;i < 9; i++)
			for(j = 0;j < 9; j++)
				if(mat[i][j] == 0)
					findCandidates(mat, i, j);
	}
	return mat;
}

void main(int argc, char** argv) {
	int** sudoku = createMat();
	sudoku = fillMat(sudoku, argv[1]);

	/* Timer */
	clock_t start = 0, end = 0;
	clock_t total = 0;

	/* Print out the original sudoku, then start solving. */
	puts("Original Sudoku:");

	print(sudoku);
	start = clock();
	puts("Started");
	puts("");

	// If successful, print the solution
	sudoku = solver(sudoku);
	puts("Sudoku Solved!");
	print(sudoku);
	
	end = clock();
	total = end - start;
	printf("\nTime %u ms\n", total);
}