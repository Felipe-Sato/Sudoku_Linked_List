#include<stdlib.h>
#include<stdio.h>

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

int** finalCheck(int** mat){
	int i, j, n=0;
	Lista* linePos = NULL;
	Lista* quadPos = NULL;
	Lista* comun = NULL;
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(mat[i][j] == 0){
				linePos = checkLineColumn(mat, i, j);
				
				if (possibleQuadrant(i, j) == 0){
				quadPos = checkQuadrant(mat, i, j);
				}
				
				comun = equalsLQ(linePos, quadPos);
				
				if(comun != NULL){
					if(comun->prox == NULL){
						printf("\n------4444----");
						mat[i][j] = comun->info;
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