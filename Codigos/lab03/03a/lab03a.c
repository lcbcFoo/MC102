/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratório: 03a */

#include <stdio.h>

int main () {

    /*Vetor casta[x] contará os nascimentos da casta x + 1*/
    int casta[9], n, c, count, total = 0;
    char digito;
    double porcentagem;
    
    scanf("%d %d", &n, &c);
    
    /*Loop inicializa variaveis do vetor 'casta' com 0*/
    for(count = 0; count < c; count++)
        casta[count] = 0;
    
    /*Zerando contador e lendo um '\n' para poder realizar o proximo loop*/
    count = 0;
    scanf("%c", &digito);
    
    /*Loop que contabiliza o numero de nascimentos em cada casta*/
    while(count < n) {
        scanf("%c", &digito);
        
        if(digito == '\n') {
            count++;
        }  
        
        else {
            digito = digito - '0';
            casta[digito - 1]++; 
        }    
    }
    
    /*Loop que calcula o total de individuos*/
    for(count = 0; count < c; count++) {
        total = total + casta[count];
    }   
        
    printf("Total: %d individuos\n", total);
    
    /*Imprimindo os nascimentos de cada casta*/
    for(count = 0; count < c; count++) {
        printf("Total da casta %d: %d\n", count + 1, casta[count]);
    }     
    
    /*Calculando e imprimindo a porcentagem de nascimentos por casta*/
    for(count = 0; count < c; count++) {
        porcentagem = (100 * casta[count]) / (double) total;
        printf("Percentual da casta %d: %.2f\n", count + 1, porcentagem);
    }    

    return 0;
    
}