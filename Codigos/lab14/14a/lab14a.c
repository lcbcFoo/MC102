/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 14a */


#include <stdio.h>


/* Essa funcao executa o comando 'D' */
char Comando_D(char posicoes[][10], char braco, int x, int Y) {
    
    /* A funcao recebe como parametros a matriz posicoes, o valor de "braco", *
     * e o tamanho (X, Y) da matriz posicoes */
    int altura;
    
    /* Verifica se o braco esta vazio */
    if (braco == 0) {
        
        /* Caso esteja vazio, verifica se ele pega uma caixa. Caso sim retorna *
         * o novo valor de "braco" */
        for(altura = 0; altura < Y; altura++)
            
            if(posicoes[altura][x] != '.') {
                braco = posicoes[altura][x];
                posicoes[altura][x] = '.';
                return braco;
            }           
    }
    
    /* Caso ele esteja segurando uma caixa, verifica em qual posicao da coluna *
     * ele deve colocar a caixa. Retorna que o braco esta vazio */
    else {
        
        for(altura = 0; altura < Y; altura++) {
            
            if(posicoes[altura][x] != '.'){
                posicoes[altura - 1][x] = braco;
                braco = 0;
                return braco;
            } 
            
            if((posicoes[altura][x] == '.') && (altura == Y - 1)) {
                posicoes[altura][x] = braco;
                braco = 0;
                return braco;
            } 
        }    
    }
    
    return braco;    
}     

/* Essa funcao executa os comandos 'R' e 'L' */
int Comando_R_L(char posicoes[][10], char braco, char comando, int Xatual, 
                int x, int y) {
   
    /* Verifica se o comando dado como parametro foi 'R' */
    if (comando == 'R') {
        
        /* Move o braco para a direita, caso ele ainda nao esteja na ultima *
         * posicao X possivel*/
        if(Xatual < x - 1) {
            Xatual++;
        
            /* Verifica se isso causara um acidente */
            if((posicoes[0][Xatual] != '.') && (braco)) 
                Xatual = -1;

        }
        
        /* Retorna a nova posicao em X */
        return Xatual;
    }    
      
    else {
        if(Xatual > 0) {
            Xatual--;
        
            /* Verifica se isso causara um acidente */
            if((posicoes[0][Xatual] != '.') && (braco)) 
                Xatual = -1;
 
        }
    
        return Xatual;
    }
}  

/* Essa funcao executa os comandos condicionais ('B', 'G', 'Y', 'A' e 'N') */
int Comandos_BGYAN(char comando, char braco) {
    
    /* A funcao recebe como parametros o comando atual e o valor de "braco. */
    
    /* Os comandos condicionais basicamente indicam se o comando seguinte sera *
     * ou nao executado. Essa funcao testa se a condicao eh verdadeira e *
     * retorna 1 (executa proximo comando) ou 2 (pula o proximo comando) */
    
    int j;

    /* Se comando for 'A', testa se o braco segura alguma caixa */   
    if(comando == 'A') {
        
        if(braco)
            j = 1;       
        else
            j = 2;
    } 
    
    /* Se o comando for 'N', testa se o braco esta vazio */    
    else if(comando == 'N') {
        
        if(braco == 0)
            j = 1;   
        else
            j = 2;
    } 
       
    /* Se o comando for 'B', 'Y ou 'G', testa se o braco segura a caixa certa */
    else if(comando == braco) 
            j = 1;        
        else
            j = 2;

    return j;
}    

int NovoPrograma(char posicoes[][10], char Programas[][62], char *braco, 
                 int *Xatual, int * E, int x, int y, int i){
    
    int j = 0, aux, acidente = 0;
    char comando;

    /* Cada volta do loop executa um comando do programa atual. O loop *
     * para quando o comando eh '*' ou quando ocorre um acidente */
    while((Programas[i][j] != '*') && !(acidente) && (*E)) {
        
        /* Para facilitar a leitura, a variavel "comando" recebe o *
         * comando a ser executado nessa volta */
        comando = (char) Programas[i][j];
        
        /* Caso o comando seja 'B', 'G', 'Y', 'A' ou 'N', chama a funcao *
         * que executa esses comandos. "j" eh incrementado de acordo com *
         * o retorno da funcao chamada */
        if((comando == 'B') || (comando == 'Y') || (comando == 'G') ||
            (comando == 'A') || (comando == 'N'))
            j += Comandos_BGYAN(comando, *braco);
        
        /* Caso o comando seja 'D' chama a funcao que executa esse *
         * comando para determinar o que o braco esta segurando e *
         * incrementa "j" */
        else if(comando == 'D') {
            *braco = Comando_D(posicoes, *braco, *Xatual, y);
            j++;
        }
        
        /* Caso o comando seja "R" ou "L", chama a funcao que executa *
         * esses comandos para saber a nova posicao do braco*/
        else if((comando == 'R') || (comando == 'L')) {
            *Xatual = Comando_R_L(posicoes, *braco, comando, *Xatual, x, y);
            
            /* Caso o retorno da funcao seja "-1", um acidente ocorreu. *
             * Aciona flag de acidente */
            if(*Xatual == -1)
                acidente = 1;
            
            /* Caso contrario, incrementa "j" */
            else
                j++;
        }
        
        else{
            
            (*E)--;
            
            if(*E > 0){
                aux = (int) comando - '1';
                
                acidente = NovoPrograma(posicoes, Programas, braco, Xatual,
                                        E, x, y, aux);
                
                j++;
            }
        }
    }  
    
    return acidente;
}
    
int main () {
    
    int x, y, P, C, E, i, j, acidente = 0, Xatual = 0;
    char posicoes[10][10], Programas[9][62], braco = 0;
    
    /* Recebe os valores de x, y, P, C e E descritos no enunciado */
    scanf("%d %d %d %d %d", &x, &y, &P, &C, &E);
    
    /* Le a configuracao inicial das caixas */
    for(i = 0; i < y; i++) 
       
        for(j = 0; j < x; j++)
            scanf(" %c", &posicoes[i][j]);
   
    /* Le a sequencia de comandos de cada programa */    
    for(i = 0; i < P; i++) {
        scanf("%s", Programas[i]);
       
    }
    
    /* Chama a funcao que executa os programas, ela retorna se ocorreu ou nao um acidente */
    acidente = NovoPrograma(posicoes, Programas, &braco, &Xatual, &E, x, y, 0);
    
    /* Caso nao tenha ocorrido acidente, imprime a configuracao das caixas */
    if(acidente == 0) {
        
        for(i = 0; i < y; i ++){
        
            for(j = 0; j < x; j++)
                printf("%c", posicoes[i][j]);
        
            printf("\n");
        }    
    }
    
    /* Caso contrario, imprime que ocorreu um acidente */
    else
        printf("Um acidente ocorreu\n");
    
    return 0;

} 
