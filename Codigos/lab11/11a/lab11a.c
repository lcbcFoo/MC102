/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 11a */


#include <stdio.h>
#include <stdlib.h>

/* Define o registro que guarda as informacoes de cada cliente: conta, nome, * 
 * sobrenome e saldo */
typedef struct{
    
    int conta, agencia;
    char nome[21];
    char sobrenome[21];
    double saldo;
} Cliente;

/* Procura se a conta existe e retorna a sua posicao no vetor, caso nao * 
 * exista retorna -1 */
int buscaConta(Cliente vet[], int n, int chave, int agencia) {
    int i;
    
    for (i = 0; i < n; i++)
        if ((vet[i].conta == chave) && (vet[i].agencia == agencia))
            return i;
        
    return -1;
}

int main (){
    
    Cliente *clientes;
    int c, t, i, contaOrig, contaDest, agOrig, agDest;
    double valor;
    
    /* Recebe numero de clientes e de transacoes */
    scanf("%d %d", &c, &t);
    
    /* Aloca o vetor de clientes */
    clientes = malloc(c * sizeof(Cliente));
    
    /* Recebe os dados de cada cliente */
    for(i = 0; i < c; i++){
        scanf("%d@%d", &clientes[i].conta, &clientes[i].agencia); 
        scanf(" %s %s", clientes[i].nome, clientes[i].sobrenome);
        scanf("%lf", &clientes[i].saldo);
    }
       
    /* Cada volta do loop verifica se a transacao pode ser realizada e a *
     * realiza */
    for(i = 0; i < t; i++){
        scanf("%d@%d >> %lf >> %d@%d", &contaOrig, &agOrig, &valor, &contaDest, 
              &agDest);
        
        /* Verifica se as contas da transacao existem e sua agencias sao as * 
         * mesmas da transacao */
        contaOrig = buscaConta(clientes, c, contaOrig, agOrig);
        contaDest = buscaConta(clientes, c, contaDest, agDest);
       
        /* Se as contas e agencias forem as corretas, continua a transacao */
        if((contaOrig != -1) && (contaDest != -1))    
                
            /* Caso a conta de origem possua saldo suficiente, efetua a *
             * transacao */
            if(clientes[contaOrig].saldo >= valor){
                clientes[contaOrig].saldo -= valor;
                clientes[contaDest].saldo += valor;
            } 
    }
    
    /* Imprime a situacao final de cada cliente */
    for(i = 0; i < c; i++){
        printf("%d@%d ", clientes[i].conta, clientes[i].agencia);
        printf("%s %s ", clientes[i].nome, clientes[i].sobrenome);
        printf("%.2f\n", clientes[i].saldo);
    }
    
    /* Desaloca o vetor de clientes */
    free(clientes);
    
    return 0;
}