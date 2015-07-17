/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 13b */

#include <stdio.h>
#include <stdlib.h>

/* Funcao que verifica regioes homogeneas */
int quadtree(int** imagem, int tamI, int tamJ, int I, int J){
    
    int i, j, flag = 1, padrao, regioes = 0;
   
    /* Seleciona o primeiro elemento do quadrante como o padrao */
    padrao = imagem[I][J];
    
    /* Verifica se ha algum elemento diferente do padrao */
    for(i = I; (flag) && (i < tamI); i++)
        for(j = J; (flag) && (j < tamJ); j++)
            if(imagem[i][j] != padrao)
                flag = 0;
       
    /* Caso todos sejam iguais, retorna 1, indicando que esse eh um quadrante *
     * homogeneo */                                
    if(flag)
        return 1; 

    /* Caso contrario, divide o quadrante atual em 4 novos e verifica a homogeneidade *
     * desses novos quadrantes */
    regioes += quadtree(imagem, ((tamI - I)/2) + I, ((tamJ - J)/2) + J, I, J);
    regioes += quadtree(imagem, tamI, ((tamJ - J)/2) + J, ((tamI - I)/2) + I, J); 
    regioes += quadtree(imagem, ((tamI - I)/2) + I, tamJ, I, ((tamJ - J)/2) + J);
    regioes += quadtree(imagem, tamI, tamJ, ((tamI - I)/2) + I, ((tamJ - J)/2) + J);
    
    /* Retorna a soma do numero de regioes homogeneas nos 4 quadrantes criados */
    return regioes;
}     

int main(){
    
    int n, i, j, **imagem, regioes;
    
    /* Recebe o tamanho da imagem */
    scanf("%d", &n);
    
    /* Aloca a matriz da imagem e recebe seus elementos */
    imagem = malloc(n * sizeof(int*));
    
    for(i = 0; i < n; i++){
        imagem[i] = malloc(n * sizeof(int));
        
        for(j = 0; j < n; j++)
            scanf("%d", &imagem[i][j]);
    }

    /* Verifica quantas sao as regioes homogeneas */
    regioes = quadtree(imagem, n, n, 0, 0);

    /* Desaloca a matriz */
    for(i = 0; i < n; i++)
        free(imagem[i]);
    
    free(imagem);
    
    /* Imprime o numero de regioes homogeneas */
    printf("Numero de regioes = %d\n", regioes);
    
    return 0;
}