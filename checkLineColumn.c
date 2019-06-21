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
	if(candidates->prox == NULL) M[l][c] = candidates->info;
	free(candidates);
}
