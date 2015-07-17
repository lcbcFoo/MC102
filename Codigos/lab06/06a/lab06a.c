/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 06a */

#include <stdio.h>

int main () {
    
    int m, n, raio, z, k, i, j, habit[50][50], count, atingidos = 0;
    
    /* Le as dimensoes m e n da matriz e o raio de acao da maquina */
    scanf("%d %d %d", &m, &n, &raio);
   
    /* Recebe o numero de habitantes de cada posicao da matriz */
    for(i = 0; i < m; i++) 
        
        for(j = 0; j < n; j++) 
            scanf("%d", &habit[i][j]);
    
        
    /* Primeiro loop seleciona as linhas onde a maquina pode ser colocada */
    for(k = raio; k < m - raio; k++) {
        
        /* Segundo loop seleciona as colunas onde a maquina pode ser colocada */
        for(z = raio; z < n - raio; z++) {
             
            /* Contador eh zerado pois eh usado, nos proximos loops, para contar *
             * o numero de habitantes no raio de acao da maquina */
            count = 0;
            
            /* Os dois proximos loops contam os habitantes na regiao delimitada *
             * pelo raio de acao da maquina na a posicao em que ela se encontra */
            for(i = k - raio; i <= k + raio; i++) {
                
                for(j = z - raio; j <= z + raio; j++) 
                    count = count + habit[i][j]; 
                    
            }
            
            /* Testa se nessa posicao existem mais alvos que nas anteriores */
            if(count > atingidos)
                atingidos = count; 
            
        }        
    }
    
    /* Imprime a maior quantidade de pessoas que podem ser atingidas */
    printf("%d\n", atingidos);
    
    return 0;
  
}  