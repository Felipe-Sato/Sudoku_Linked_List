#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
    struct lista *ant;
} Lista;

typedef struct coluna {
    Lista *l1;
    Lista *prox;
} Coluna;

Lista *criaLinha (Lista *Ref) {
	Lista *new = (Lista*)malloc(sizeof(Lista));
	new->info = 0;
	new->ant = NULL;
	new->prox = Ref;
	if (Ref != NULL) {
		Ref->ant = new;
	}
	return new;
}

Lista *criaQualquerLugar(Lista Ref, int pos, int valor) {
    Lista *new = (Lista*)malloc(sizeof(Lista));
    new->info = valor;
    if (pos == 1)
    {
        /* code */
    }
    

}

int main(int argc, char const *argv[])
{
    Coluna *C = (Coluna*)malloc(sizeof(Coluna));
    C = NULL;
    return 0;
}