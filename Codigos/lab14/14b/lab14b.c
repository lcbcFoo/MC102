/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 14b */

#include <stdio.h>
#include <stdlib.h>

void AliciaParlamentares(int n, int min, int *temp, int **influencia, int *valor,
                         int *usados, int next, int size, int atual, int *melhor){
    
    int i, j, aux;

    /* Caso sejam escolhidos mais que o minimo, um novo menor valor foi encontrado */
    if (size >= min)
        *melhor = atual;

    /* Caso contrario, ainda precisam ser aliciados novos parlamentares */
    else{ 

        /* Escolhe um parlamentar para receber pagamento */       
        for (i = next; i < n; i++) {
            aux = 0;

            /* Caso o novo preco ainda seja menor do que o menor ateh o momento, continua *
             * o teste utilizando esse parlamentar */
            if(atual + valor[i] < *melhor){
            
                /* Alicia todos os parlamentares influenciados pelo parlamentar pago */
                for(j = 0; j < n; j++)
                
                    /* Incrementa aux do numero de aliciados nessa chamada e sinaliza que *
                     * os parlamentares estao sendo usados */
                    if((influencia[i][j] == 1) && (usados[j] == 0)){
                            usados[j]++;
                            temp[size + aux] = j;
                            aux++; 
                    }    
                  
                /* Chama a recursao mandando o novo preco atual e o numero de parlamentares *
                 * ja aliciados */  
                AliciaParlamentares(n, min, temp, influencia, valor, usados, i + 1, size + aux, 
                                    atual + valor[i], melhor);

                /* Sinaliza que todos os parlamentares usados no teste anterior estao livres */
                for(j = 0; j < aux; j++)
                    usados[temp[size + j]] = 0;
            }    
        }
    }    
}        

int main (){
    
    int n, i, j, min, *valor, **influencia, *temp, *usados, melhor = 0;
    
    /* Recebe numero de parlamentares e de partidos */
    scanf("%d %d", &n, &min);
    
    /* Aloca vetores auxiliares e recebe a entrada */
    valor = malloc (n * sizeof(int));
    temp = malloc (n * sizeof(int));
    usados = malloc (n * sizeof(int));
   
    for(i = 0; i < n; i++)
        scanf("%d", &valor[i]);

    influencia = malloc (n * sizeof(int*));
    
    for(i = 0; i < n; i++){
        influencia[i] = malloc(n * sizeof(int)); 
        
        for(j = 0; j < n; j++)
            scanf("%d", &influencia[i][j]);
    }
    
    /* Inicializa menor com o maior preco possivel */
    for(i = 0; i < n; i++)
        melhor += valor[i];
    
    /* Executa a funcao que determina qual o menor preco possivel */
    AliciaParlamentares(n, min, temp, influencia, valor, usados, 0, 0, 0, &melhor);
    
    /* Imprime o resultado */
    printf("%d\n", melhor);  
    
    /* Desaloca os vetores auxiliares usados */
    for(i = 0; i < n; i++)
        free(influencia[i]); 
        
    free(influencia);
    free(valor);
    free(temp);
    free(usados);
    
    return 0;
}    
    
