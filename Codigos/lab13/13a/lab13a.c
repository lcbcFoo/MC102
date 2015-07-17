/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 13a */

#include <stdio.h>

/* Funcao que encontra a altura da maior ramificacao da bomba */
int contaNiveis(int ramos){
    
    int i, aux, max = 0, niveis;
  
    /* Ramos indica o numero de ramificacoes geradas nesse nivel, de *
     * forma que quando ramos eh 0 a funcao retorna 1, que eh a altura *
     * do ultimo nivel de uma ramificacao */

    /* Verifica a altura de cada ramo gerado no nivel atual */
    for(i = 0; i < ramos; i++){
        scanf("%d", &niveis);
       
        aux = contaNiveis(niveis);
           
        /* Se ele possuir mais niveis do que max, ele eh o maior ramo gerado *
         * ateh o momento */   
        if(aux > max)
            max = aux;  
    }
    
    /* Retorna a altura do maior ramo que se origina no nivel atual */
    return 1 + max;
}

int main (){
    
    int ramos, max;
    
    /* Recebe quantos niveis sao gerados pelo primeiro nivel */
    scanf("%d", &ramos);

    /* Chama a funcao que encontrara o tamanho da bomba */
    max = contaNiveis(ramos); 

    /* Imprime a altura da bomba */
    printf("%d\n", max);
   
    return 0;
} 