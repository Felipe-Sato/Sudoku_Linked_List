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
				ant = aux;
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

void printList(List *L) { 
	if (L != NULL) {
		printf("%i\n", L->info);
		printList(L->prox);
	} else {
		printf("Empty List\n");
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

// the functon will return a struct type List with all elements that are possible to be inserted in the quadrant
List *checkQuadrant(int **M, int i, int j) {
	int di = i+3, dj = j+3;
	int p = j;
	List *L = NULL;
	List *resp = NULL;
	L = addElement(L, 9);
	L = addElement(L, 8);
	L = addElement(L, 7);
	L = addElement(L, 6);
	L = addElement(L, 5);
	L = addElement(L, 4);
	L = addElement(L, 3);
	L = addElement(L, 2);
	L = addElement(L, 1);
	printf("\n");

	for ( i = i; i < di; i++) {
		for ( j = p; j < dj; j++) {
			printf("%i\t", M[i][j]);
			if (M[i][j] != 0) {
				resp = equalElement(L, M[i][j]);
			} else {
				resp = L;
			}
		}
	}
	return resp;
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