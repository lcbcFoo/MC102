/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 10b */

#include <stdio.h>
#include <stdlib.h>


/* Encontra o indice do menor elemento do vetor durante a ordenacao */
int indiceMenor(int vet[], int n, int inicio) {
    
    int i, min = inicio;
    
    for(i = inicio + 1; i < n; i ++)
        
        if(vet[min] > vet[i])
            min = i;
        
    return min;
}

/* Troca a posicao de dois elementos do vetor durante a ordenacao */
void troca(int *a, int *b) {
    
    int aux;
    
    aux = *a;
    *a = *b;
    *b = aux;
}

/* Ordena os vetores dos homens e das mulheres da menor para a maior nota por * 
 * selection sort */
void OrdenaVetores(int vet[], int n) {
    
    int i, min;
    
    for(i = 0; i < n; i++){
        min = indiceMenor(vet, n, i);
        troca(&vet[min], &vet[i]);
    }
}     
    
int main () {
    
    int H, M, D, i, j, count = 0, *homens, *mulheres, flag;
    
    /* Recebe o numero de homens, de mulheres e a diferenca maxima de notas */
    scanf("%d %d %d", &H, &M, &D);
    
    /* Aloca os vetores que guardam as notas e recebe as notas dos homens e *
     * das mulheres, respectivamente */
    homens = malloc(H * sizeof(int));
    mulheres = malloc(M * sizeof(int));
    
    for(i = 0; i < H; i++)
        scanf("%d", &homens[i]);
    
    for(i = 0; i < M; i++)
        scanf("%d", &mulheres[i]);
    
    
    /* Ordena os dois vetores da menor para a maior nota */
    OrdenaVetores(homens, H);
    OrdenaVetores(mulheres, M);
      
    j = 0;
    /* Cada volta do loop seleciona a nota de um homem */
    for(i = 0; i < H; i++){
        flag = 1;
        
        /* Verifica se existe alguma mulher cuja nota tenha uma diferenca *
         * menor ou igual a pedida. O loop para quando chega ao fim do vetor *
         * ou quando a nota da mulher atual eh maior do que a do homem em *
         * mais de 'D' unidades ou quando uma mulher possui uma nota que *
         * satisfaca a diferenca */
        while ((j < M) && (mulheres[j] - homens[i] <= D) && (flag)){
            
            /* Quando uma nota de uma mulher eh utilizada em um par *
             * equilibrado, flag eh zerada e count incrementado */
                
            if((homens[i] - mulheres[j] <= D) &&        
                (mulheres[j] - homens[i] >= -D)){
                
                count++;
                flag = 0;
            }

            /* Como os vetores estao ordenados, nao ha necessidade de * 
             * zerar o indice j a cada nota de homem a ser testada */
            j++;
        }  
    }
    
    /* Imprime o numero de duplas equilibradas */
    printf("Numero maximo de duplas equilibradas = %d\n", count);
    
    return 0;
}    
  