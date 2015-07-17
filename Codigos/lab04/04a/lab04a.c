/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 04a */


#include <stdio.h>

int main () {
   
    int Y[10], Xmax, Ymax, Xatual = 0, count, i = 1, acidente = 1;
    char comando;
    
    /* Recebe o numero de posicoes e o numero maximo de caixa empilhadas */
    scanf("%d %d", &Xmax, &Ymax);
    
    /* Recebe quantas caixas existem inicialmente em cada posicao */
    for(count = 0; count < Xmax; count++) 
        scanf("%d", &Y[count]);
   
    /* "Limpando" espaco em branco antes de receber caracteres */
    scanf(" ");
    
    /* Cada ciclo do loop recebe um comando do jogador e analisa as acoes a *
     * serem tomadas para esse comando, ateh ser parado com o comando '*' */
    while ((comando != '*') && (acidente)) {
        scanf("%c", &comando);
        
        /* Verifica as acoes possivel para o comando 'D' */
        if(comando == 'D') {
            
            /* Verifica se o braco ira pegar uma caixa da pilha atual*/
            if((Y[Xatual] > 0) && (i == 1)) {
                Y[Xatual]--;
                i = 2;
            }
            
            else {
                
                /* Verifica se o braco ira soltar uma caixa na pilha atual */
                if(i == 2) {
                    Y[Xatual]++;
                    i = 1;
                }    
            }
        }    
        
        /* Para o comando 'R', caso o braco possa se mover para a direita, *
         * ele eh movido uma posicao para esse lado */
        if((comando == 'R') && (Xatual < Xmax - 1)) {
            Xatual++;
            
            /* Verifica se isso causara um acidente, caso ocorra, o loop para */
            if((Y[Xatual] == Ymax) && (i == 2)) {
                printf("Um acidente ocorreu\n");
                acidente = 0;
            }
        }
        
        /* Para o comando 'L', caso o braco possa se mover para a esquerda, *
         * ele eh movido uma posicao para esse lado */
        if((comando == 'L') && (Xatual > 0)) {
            Xatual--;
            
            /* Verifica se isso causara um acidente, caso ocorra, o loop para */
            if((Y[Xatual] == Ymax) && (i == 2)) {
                printf("Um acidente ocorreu\n");
                acidente = 0;
            }
        }
    }   
    
    /* Caso nao tenha ocorrido acidente, imprime as caixas empilhadas em cada * 
     * posicao */
    if (acidente) {
        
        for(count = 0; count < Xmax - 1; count++) { 
            printf("%d ", Y[count]);
        }    
        
        /* Imprime a ultima posicao separada para formatacao adequada */
        printf("%d\n", Y[Xmax - 1]);
    }
    
    return 0;
}    
   