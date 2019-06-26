#include<stdio.h>
#include<stdlib.h>

typedef struct list {
	int info;
	struct list *prox;
} List;

List *addElement(List *L, int data) {
	List *new = (List*)malloc(sizeof(List));
    new->info = data;
    new->prox = L;
    return new;
}

void printList(List *L) { 
	if (L != NULL) {
		printf("%i\n", L->info);
		printList(L->prox);
	} else {
		printf("Empty List\n");
	}
}

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


// this function will allow only the coodnates of i, j of new quadrants
int possibleQuadrant(int i, int j) {
	if (i == 0 || i == 3 || i == 6) {
		if (j == 0 || j == 3 || j == 6) {
			return 0;
		}
	}
	return 1;
}
// if the element is inside of the range, the function will remove from the list all elements inside of the sudoku
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

void main(int argc, char* argv[]){
	int** sudoku = createMat();
	sudoku = fillMat(sudoku, argv[1]);
	print(sudoku);
	int i, j;
	List *L = NULL;
	for ( i = 0; i < 9; i++) {
		for ( j = 0; j < 9; j++) {
			if (possibleQuadrant(i, j) == 0) {
				L = checkQuadrant(sudoku, i, j);
				printf("\n\nM[%i][%i]:\n",i,j);
				printList(L);
			}
		}
	}
	sudoku = freeMat(sudoku);
