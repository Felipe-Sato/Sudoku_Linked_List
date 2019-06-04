// https://pt.wikibooks.org/wiki/Programar_em_C/Entrada_e_sa%C3%ADda_em_arquivos

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fl;
    int c;

    if((fl = fopen("caminho/do/arquivo", "r")) == NULL)
    {
        perror("Erro: fopen");
        exit(EXIT_FAILURE);
    }

    while((c = fgetc(fl)) != EOF)
        printf("Caractere lido: %c\n", c);

    if((c == EOF) && (feof(fl) == 0) && (ferror(fl) != 0))
        perror("Erro: fgetc");
        

    fclose(fl);
    return EXIT_SUCCESS;
}
