#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// BUILDING
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

// SOLUTION
typedef struct list {
	int info;
	struct list *prox;
} List;

// Adds a new element in the first position of the list
List *addElement(List *L, int data) {
	List *new = (List*)malloc(sizeof(List));
    new->info = data;
    new->prox = L;
    return new;
}

// Adds a new element in the end of list
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

// Prints the list
void printList(List *L) {
	if (L != NULL) {
		printf("%i\n", L->info);
		printList(L->prox);
	} else {
		printf("Empty List\n");
	}
}

// Removes elements 
List *remElement(List *L, int data) {
	// empy list
	if (L == NULL) {
		return NULL;
	}
	else {
		// first and only one element
		if (L->prox == NULL && L->info == data) {
			free(L);
			return NULL;
		} else {
			List *aux = L;
			List *ant = NULL;
			// first element
			if (aux->info == data) {
				L = aux->prox;
				free(aux);
			} else {
				// updating aux
				ant = L;
				aux = aux->prox;
				// searching
				while (aux->prox != NULL && aux->info != data ) {
					aux = aux->prox;
					ant = ant->prox;
				}
				// last element
				if (aux->prox == NULL && aux->info == data) {
					ant->prox = NULL;
					free(aux);
				}
				// any element
				else if (aux->prox != NULL && aux->info == data) {
					ant->prox = aux->prox;
					free(aux);
				}
				// not found
				else {
					printf("\nElement not found\n");
				}
			}
			return L;
		}
	}
}

// This function will allow only the coodnates of i, j of new quadrants
int possibleQuadrant(int i, int j) {
	if (i == 0 || i == 3 || i == 6) {
		if (j == 0 || j == 3 || j == 6) {
			return 0;
		}
	}
	return 1;
}

// If the element is inside of the range, the function will remove from the list all elements inside of the sudoku
List *equalElement(List *L, int data) {
	if(L->info != data || L->info != -1*data) {
		if (L != NULL) {
			if (data < 0) {
				L = remElement(L, -1*data);
			} else {
				L = remElement(L, data);
			}
		}
	} 
	else {
		L = equalElement(L->prox, data);
	}
	return L;
}

// The functon will return a struct type List with all elements that are possible to be inserted in the quadrant
List *checkQuadrant(int **M, int i, int j) {
	int di = i+3, dj = j+3;
	int p = j;
	List *L = NULL;
	L = addElement(L, 9);
	L = addElement(L, 8);
	L = addElement(L, 7);
	L = addElement(L, 6);
	L = addElement(L, 5);
	L = addElement(L, 4);
	L = addElement(L, 3);
	L = addElement(L, 2);
	L = addElement(L, 1);

	for ( i = i; i < di; i++) {
		for ( j = p; j < dj; j++) {
			// printf("%i\t", M[i][j]);
			if (M[i][j] != 0) {
				L = equalElement(L, M[i][j]);
			}
		}
	}
	return L;
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


// Checks to see if a particular value is presently valid in a given position.
int isValid(int number, int **sudoku, int row, int column) {
	// int i = 0;
	// int modRow = 3*(row/3);
	// int modCol = 3*(column/3);
	// int row1 = (row+2)%3;
	// int row2 = (row+4)%3;
	// int col1 = (column+2)%3;
	// int col2 = (column+4)%3;

	List *line = checkLineColumn(sudoku, row, column);
	List *quad = NULL;
	if (possibleQuadrant(row, column) == 0) {
		quad = checkQuadrant(sudoku, row, column);
	}
	while (line != NULL || quad != NULL) {
		if (line != NULL) {
			if (line->info == number) {
				return 1;
			} else {
				line = line->prox;
			}
		}
		if (quad != NULL) {
			if (quad->info == number)
			{
				return 1;
			} else {
				quad = quad->prox;
			}
		}
	}
	return 0;

	// /* Check for the value in the given row and column */
	// for (i=0; i<9; i++) {
	// 	if (sudoku[i][column] == number) return 0;
	// 	if (sudoku[row][i] == number) return 0;
	// }
	
	// /* Check the remaining four spaces in this sector */
	// if(sudoku[row1+modRow][col1+modCol] == number) return 0;
	// if(sudoku[row2+modRow][col1+modCol] == number) return 0;
	// if(sudoku[row1+modRow][col2+modCol] == number) return 0;
	// if(sudoku[row2+modRow][col2+modCol] == number) return 0;
	// return 1;
}


// A recursive function that does all the gruntwork in solving the sudoku.
int sudokuHelper(int **sudoku, int row, int column) {
	int nextNumber = 1;
	
	if (9 == row) {
		return 1;
	}

	// Is this element already set?  If so, we don't want to change it.
	if (sudoku[row][column]) {
		if (column == 8) {
			if (sudokuHelper(sudoku, row+1, 0)) return 1;
		} else {
			if (sudokuHelper(sudoku, row, column+1)) return 1;
		}
		return 0;
	}

	// Iterate through the possible numbers for this empty cellnand recurse for every valid one, to test if it's part of the valid solution.
	for (; nextNumber<10; nextNumber++) {
		if(isValid(nextNumber, sudoku, row, column)) {
			sudoku[row][column] = nextNumber;
			if (column == 8) {
				if (sudokuHelper(sudoku, row+1, 0)) return 1;
			} else {
				if (sudokuHelper(sudoku, row, column+1)) return 1;
			}
			sudoku[row][column] = 0;
		}
	}
	return 0;
}

// A helper function to call sudokuHelper recursively
int solveSudoku(int **sudoku) {
	return sudokuHelper(sudoku, 0, 0);
}

//A function that compares all elements and looks for commom ones from both lists and returns them on a list
List* equalsLQ(List* line, List* quad){
	List* new = NULL;
	List* aux1 = line;
	List* aux2 = quad;
	if(line != NULL && quad != NULL){
		while(aux1 != NULL){
			while(aux2 != NULL){
				if(aux1->info == aux2->info)
					new = addList(new, aux2->info);	
				
					aux2 = aux2->prox;
			}
			aux1=aux1->prox;
			aux2 = quad;
		}
	}
	return new;
}
//A function that gets 2 different structure lists with possible elements from the checklineColumn and checkQuadrant
int** finalCheck(int** mat){
	int i, j, n=0;
	List* linePos = NULL;
	List* quadPos = NULL;
	List* commom = NULL;
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(mat[i][j] == 0){
				linePos = checkLineColumn(mat, i, j);
				if (possibleQuadrant(i, j) == 0){
					quadPos = checkQuadrant(mat, i, j);
				}
				commom = equalsLQ(linePos, quadPos);
				
				//if common is different then null and only has 1 element it gets add to the sudoku
				if(commom != NULL){
					if(commom->prox == NULL){
						printf("\n------4444----");
						mat[i][j] = commom->info;
					}
				}
			}
		}
	}
	return mat;
}

int main(int argc, char** argv) {
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
	if (solveSudoku(sudoku)) {
		finalCheck(sudoku);
		puts("Sudoku Solved!");
		print(sudoku);
	} else {
		puts("We can't solve this Sudoku");
	}
	end = clock();
	total = end - start;
	printf("\nTime %u ms\n", total);
	
	return 0;
}
