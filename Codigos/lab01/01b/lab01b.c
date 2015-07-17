/* Nome: Lucas de Camargo Barros de Castro
 * RA: 172678
 * Laboratorio: 01b */


#include <stdio.h>

int main () {
    /*C se refere a consumo, V ao valor da conta*/
    
    int C_passado, C_atual;
    double V_original, V_final;
    
    scanf("%d %d", &C_passado, &C_atual);
    
    /*Caso em que o consumo e menor ou igual que 10l */
    if(C_atual <= 10 ) {
        V_original = 17.34;
    } 
    
    else {
        /*Caso em que o consumo esta entre 11 e 20l */ 
        
         if((C_atual >= 11) && (C_atual <= 20)) {
            V_original = 17.34 + 2.41 * (C_atual - 10);
         }
                  
        else {
            /*Caso em que o consumo esta entre 21 e 50l */
            
            if((C_atual >= 21) && (C_atual <= 50)) {
                V_original = 17.34 + 24.1 + (C_atual - 20) * 3.70;
            }
            /*Caso em que o consumo e maior que 50l*/
            
            else {
                V_original = 17.34 + 24.1 + 111 + ((C_atual - 50) * 4.43);
            }   
        }       
    }
    
    /*Casos em que o consumidor ganha desconto*/
    
    if(C_atual <= 0.9 * C_passado) {
        /*Para reducao de 10 a 15% do consumo*/
        
        if(C_atual > 0.85 * C_passado) {
            V_final = 0.9 * V_original;
        }
        
        else {
            /*Para reducao de 15 a 20% do consumo*/
            
            if(C_atual > 0.8 * C_passado) {
                V_final = 0.8 * V_original;
            }
            
            else {
                /*Para reducao de mais de 20% do consumo*/
                
                V_final = 0.7 * V_original;
            }   
        }
    }
    
    /*Caso em que o consumidor ganha multa ou paga o valor original*/

    else {
        /*Para aumento de ate 20% do consumo*/
        
        if((C_atual > C_passado) && (C_atual < 1.2 * C_passado)) {
            V_final = 1.4 * V_original;
        }
        else {
            /*Para aumento de mais de 20% do consumo*/
            
            if((C_atual > C_passado) && (C_atual >= 1.2 * C_passado)) {
                V_final = 2 * V_original;
            }
            else {
                /*Para consumo que nao se enquadra em desconto nem em multa*/
                
                V_final = V_original;
            }    
        }
    }
    
     printf("Valor original = %.2f\n", V_original);
     printf("Valor final = %.2f\n", V_final);
    
    return 0;
} 