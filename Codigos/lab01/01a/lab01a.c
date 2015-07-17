/* Nome: Lucas de Camargo Barros de Castro
 * RA: 172678
 * Laboratorio: 01a */

#include <stdio.h> 
#include <math.h>

int main () {
    
    /* a variavel calculo1 apenas realiza uma operacao */
    
    double C, i, M, Mesp, calculo1;
    int n, nesp;
   
    scanf("%lf %lf %d %lf", &C, &i, &n, &Mesp);
    
    /* realizando o calculo do montante final com base em C, i e n fornecidos */

    calculo1 = i / 100 + 1;
    M = C * pow(calculo1,n);
    
    /* calculando o numero de lotes nesp para um montante Mesp fornecido */
      
    nesp = ceil(log(Mesp / C) / log(i / 100 + 1));
    
   /* imprimindo resultados */
   
    printf("Montante = %.2f\n", M);
    printf("%d lote(s)\n", nesp);
    
    return 0;
    
}