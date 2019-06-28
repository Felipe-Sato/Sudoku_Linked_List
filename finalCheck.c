#include<stdlib.h>
#include<stdio.h>
//A function that compares all elements and looks for commom ones from both lists and returns them on a list
Lista* equalsLQ(Lista* line, Lista* quad){
	Lista* new = NULL;
	Lista* aux1 = line;
	Lista* aux2 = quad;

	if(line != NULL && quad != NULL){
		
		while(aux1 != NULL){
			while(aux2 != NULL){
				if(aux1->info == aux2->info)
					new = insertAtEnd(new, aux2->info);	
				
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
	Lista* linePos = NULL;
	Lista* quadPos = NULL;
	Lista* commom = NULL;
	
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

int main(int argc, char* argv[]){
	int** sudoku;
	
	sudoku = finalCheck(sudoku);

	return 0;
}
