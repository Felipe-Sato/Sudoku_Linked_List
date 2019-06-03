#include<stdio.h>
#include<stdlib.h>

int** criaMatDin(int l, int c){
	int** matDin = (int**) malloc(l * sizeof(int*));
	for(int i = 0; i < l; i++)
		matDin[i] = (int*) malloc(c * sizeof(int));
	return matDin;
}

int** preencheMatDin(int** matDin, int l, int c){
	for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++)
			scanf("%d", &matDin[i][j]);
	return matDin;
}

void imprimeMatDin(int** matDin, int l, int c){
	for(int i = 0; i < l; i++){
		if (matDin == NULL){
			printf("NULL\n");
			break;
		}
		for(int j = 0; j < c; j++)
			printf("%d ", matDin[i][j]);
		printf("\n");
	}
}

int** liberaMatDin(int** matDin, int l){
	for(int i = 0; i < l; i++)
		free(matDin[i]);
	free(matDin);
	return NULL;
}

void main(){
	int l, c;
	scanf("%d", &l);
	scanf("%d", &c);
	int** sudoku = criaMatDin(l, c);
	sudoku = preencheMatDin(sudoku, l, c);
	imprimeMatDin(sudoku, l, c);
	sudoku = liberaMatDin(sudoku, l);
	imprimeMatDin(sudoku, l, c);
}