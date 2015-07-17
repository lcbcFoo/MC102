/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 10a */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    int frequencia;
    char *word;

}Elemento;

int indiceMaior(Elemento palavras[], int n, int inicio) {

    int j, max = inicio;

    for (j = inicio + 1; j < n; j++){
        if (palavras[max].frequencia < palavras[j].frequencia)
            max = j;

        if(palavras[max].frequencia == palavras[j].frequencia)
            if(strcmp(palavras[max].word, palavras[j].word) > 0)
                max = j;
    }

    return max;
}

void troca(Elemento *a, Elemento *b) {

    Elemento aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void ordenando(Elemento palavras[], int n) {
    int i, max;

    for (i = 0; i < n; i++) {
        max = indiceMaior(palavras, n, i);
        troca(&palavras[i], &palavras[max]);
    }
}

int main() {

    int D, F, L, M, count = 0, flag, i;
    char *leitura;
    Elemento *palavras;

    scanf("%d %d %d %d", &D, &F, &L, &M);

    leitura = malloc((M + 1) * sizeof(char));
    palavras = malloc(D  * sizeof(Elemento));

    for(i = 0; i < D; i++){
        palavras[i].word = malloc((M + 1) * sizeof(char));
        palavras[i].frequencia = 0;
    }

    do{
        scanf(" ");
        scanf("%s", leitura);

        if((leitura[0] != '*') && (strlen(leitura) >= L)){
            flag = 1;

            for(i = 0; (flag) && (i < count); i++){

                if(strcmp(palavras[i].word, leitura) == 0){
                    palavras[i].frequencia++;
                    flag = 0;
                }
            }

            if(flag){
                strcpy(palavras[count].word, leitura);
                palavras[count].frequencia++;
                count++;
            }
        }
    }while(leitura[0] != '*');

    free(leitura);

    ordenando(palavras, count);

    for(i = 0; i < count; i++){

        if(palavras[i].frequencia >= F)
            printf("%s %d\n", palavras[i].word, palavras[i].frequencia);

    }


    free(palavras);

    return 0;
} 