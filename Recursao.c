#include <stdio.h>
#include<stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

void imprime (Lista *L) {
    // criterio de parada
    if (L != NULL) {
        printf("%i\n", L->info);
        // autoreferencia
        imprime(L->prox);
    }
}

Lista *criaInicio (Lista *Ref, int valor) {
	Lista *new = (Lista*)malloc(sizeof(Lista));
	new->info = valor;
	new->prox = Ref;
	return new;
}

Lista *criaFinal (Lista *Ref, int valor) {
	if (Ref == NULL) {
        Lista *new = (Lista*)malloc(sizeof(Lista));
	    new->info = valor;
	    new->prox = NULL;
        return new;
    } else {
        Ref->prox = criaFinal(Ref->prox, valor);
        // return Ref;
    }
}

Lista *retiraLista (Lista *Ref, int valor) {
    if (Ref != NULL) {
        if (Ref->info == valor) {
            Lista *aux = Ref;
            Ref = Ref->prox;
            free(aux);
        } else {
            Ref->prox = retiraLista(Ref->prox, valor);
        }
    }
    return Ref;
}

int achaMaior(Lista *Ref) {
    int valor;
    if (Ref == NULL) {
        return -1;
    } else {
        valor = achaMaior(Ref->prox);
        if(Ref->info > valor){
            return Ref->info;
        } else {
            return valor;
        }
    }
}

int main(int argc, char const *argv[]) {

    Lista *M = NULL;
	M = criaFinal(M, 10);
    M = criaFinal(M, 20);
    M = criaFinal(M, 30);
    M = criaFinal(M, 50);
    M = criaFinal(M, 40);
    

    printf("\nLista velha:\n");
    printf("Lista M:\n");
    imprime(M);
    int maior = achaMaior(M);
    printf("\nMaior: %i\n", maior);

    M = retiraLista (M, 30);
    printf("\n");
    imprime(M);
    M = retiraLista (M, 40);
    printf("\n");
    imprime(M);
    M = retiraLista (M, 60);
    printf("\n");
    imprime(M);

	return 0;
}