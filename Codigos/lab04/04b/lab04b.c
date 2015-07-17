/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 04b */

#include <stdio.h>

int main () {
    int Valor[100], Capital, CapFinal, Dias, count, count2, count3, count4;
    int aux, compradas, compradas2, TesteCapital, Resto, Resto2;
 
    /* Recebendo o numero de dias e o capital inicial */
    scanf("%d %d", &Dias, &Capital);
    
    /* Recebendo o valor das acoes em cada dia */
    for(count = 0; count < Dias; count++) {
        scanf("%d", &Valor[count]);
    }
    
    /* Guarda valor de Capital e inicializa CapFinal com o valor de Capital */
    aux = Capital;
    CapFinal = Capital;
    
    
    /* Sao avaliados todas as possibilidades de compra e venda de acoes e eh *
     * guardada a possibilidade em que o capital final eh maior */
    
    /* O loop 1 seleciona o dia da primeira compra e verifica quantas acoes sao* 
     * compradas nesse dia */
    for(count = 0; count < Dias; count++) {
        Capital = aux;
        compradas = Capital / Valor[count];
        Resto = Capital % Valor[count];
       
        /* O loop 2 seleciona o dia da primeira venda e o capital adquirido */
        for(count2 = count +1; count2 < Dias; count2++) {
            Capital = compradas * Valor[count2] + Resto;
            
            /* Verifica se na primeira compra/venda ja existe lucro */
            if(Capital > CapFinal) {
                CapFinal = Capital;
            }   
               
            /* O loop 3 seleciona o dia da segunda compra quantas acoes sao *
             * compradas nesse dia */
            for(count3 = count2 + 1; count3 < Dias; count3++) {
                compradas2 = Capital / Valor[count3];
                Resto2 = Capital % Valor[count3];
                
                /* O loop 4 seleciona o dia da segunda venda e o capital total *
                 * adquirido depois da segunda venda */
                for(count4 = count3 + 1; count4 < Dias; count4++) {
                    TesteCapital = compradas2 * Valor[count4] + Resto2;
                    
                    /* Testa se esse eh o maior valor ateh o momento */
                    if(TesteCapital > CapFinal) 
                        CapFinal = TesteCapital;
                }
            }
        }
    }
    
    /* Testa se houve lucro e imprime resultados */
    if(CapFinal > aux) 
        printf("Capital final = R$%d\n", CapFinal);
  
    else
        printf("Melhor nao investir agora, cara!\n");
    
    return 0;
    
} 