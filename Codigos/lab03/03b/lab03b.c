/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 03b */

#include <stdio.h>

int main () {
   
    /*A[x] e B[x] armazenam o intervalo do guardiao X + 1*/
    int A[100], B[100], n, count, count2 = 0, i = 1;
    int sinceros = 0, totalsinceros = 0, guardiao;
   
    /*Le o numero de guardioes*/
    scanf("%d", &n);

    /*Le os intervalos [a, b] de cada guardiao*/
    for(count = 0; count < n; count++) {
        scanf("%d", &A[count]);
        scanf("%d", &B[count]);
    }  
   
    /*O programa se baseia em testar o numero mais frequente nos intervalos  
     dados para determinar qual seria a maior quantidade de guardioes 
     sinceros.*/
    
    /*Seleciona um numero de 1 ate n*/
    for(count = 1; count <= n; count++) {
        
        /*Verifica em quantos intervalos ele aparece*/
        for(count2 = 0; count2 < n; count2++) {
            
            if((count <= B[count2]) && (count >= A[count2])) {
                sinceros++;
            }    
        }
        
        /*Testa se o numero eh igual ao numero de vezes que ele aparece e se 
        ele eh o maior ate o momento. Caso seja, ele eh guardado*/
        if((sinceros > totalsinceros) && (sinceros == count)) {
            totalsinceros = sinceros;
	    guardiao = count; 
        }
        
        sinceros = 0;
    }
    
    /*Imprime resultados*/
    printf("Numero de guardioes sinceros = %d\n", totalsinceros);
    printf("Guardiao %d\n", guardiao);
   
    return 0;
} 
