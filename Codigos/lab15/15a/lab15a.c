/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 15a */

 #include <stdio.h>
 #include <stdlib.h>


/* Define o struct de cada posicao. Permite que cada posicao da matriz armazene as *
 * direcoes que o robo pode se mover quando estiver naquela posicao */
typedef struct{

	int up, down, left, right, trap;

}Move;

/* Decodifica a entrada e armazena os caminhos permitidos pela posicao do tabuleiro no *
 * struct que guarda os movimentos permitidos em cada posicao */
void MovementRead(Move * position, int number){

	/* Veirica se a posicao eh ou nao uma armadilha */
	if(number == 0)
		(*position).trap = 1;

	else
		(*position).trap = 0;

	/* Verifica se o robo pode andar para a esquerda */
	if(number % 2)
		(*position).left = 1;

	else
		(*position).left = 0;

	number /= 2;

	/* Verifica se o robo pode andar para baixo */	
	if(number % 2)
		(*position).down = 1;

	else
		(*position).down = 0;

	number /= 2;

	/* Verifica se o robo pode andar para a direita */
	if(number % 2)
		(*position).right = 1;

	else
		(*position).right = 0;

	number /= 2;

	/* Verifica se o robo pode andar para cima */
	if(number % 2)
		(*position).up = 1;

	else
		(*position).up = 0;
}

/* Inicializa a matriz auxiliar com -1 em todas as posicoes */
void inicializate(int ** mat, int n, int m){

	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			mat[i][j] = -1;
}

/* Funcao que verifica todos os caminhos possiveis de serem tomados pelo robo */
int Walking(int **M, Move **move, int Li, int Ci, int Cf, int energy) {

	int L, C, k, saiu;

	/* Caso a energia acabe, retorna falso e nao realiza mais nenhum teste nessa posicao */
	if(energy == 0)
		return 0;

	/* Caso o robo esteja na coluna mais a direita e a posicao permita que *
	 * ele ande para a direita, retorna verdadeiro */
	if ((Ci == Cf) && (move[Li][Ci].right))
		return 1;

	/* Testa todos os movimentos a partir da posicao atual. A cada volta do loop o robo *
	 * ira para uma direcao diferente */
	for (k = 0; k < 4; k++) {

		/* Seta a nova posicao do rovo para cima */
		if(k == 0){
			L = Li - move[Li][Ci].up;
			C = Ci;
		}

		/* Seta a nova posicao do robo para baixo */
		else if(k == 1){
			L = Li + move[Li][Ci].down;
			C = Ci;
		}

		/* Seta a nova posicao do robo para a direita */
		else if(k == 2){
			L = Li;
			C = Ci + move[Li][Ci].right;
		}

		/* Seta a nova posicao do robo para a esquerda */
		else if(k == 3){
			L = Li;
			C = Ci - move[Li][Ci].left;
		}

		/* Verifica se a posicao permite que o robo va para posicao setada */
		if((Li != L) || (C != Ci)){

			/* Verifica se o robo ja passou por aquela posicao com um numero maior de *
			 * passos ou se ele nunca passou por la */
			if ((M[L][C] == -1) || (M[L][C] > M[Li][Ci] + 1)) {

				/* Por fim, se a posicao nao for uma armadilha marca o numero de passos *
				 * na posicao e chama a recursao novamente */
				if(move[L][C].trap == 0){
					M[L][C] = M[Li][Ci] + 1;
					saiu = Walking(M, move, L, C, Cf, energy - 1);

					/* Caso ele possa sair por esse caminho, retorna verdadeiro */
					if(saiu)
						return 1;
				}
			}
		}	
	}

	/* Caso ele termine o loop e nao encontre nenhuma saida, retorna falso */
	return 0;
}


int main(){

    int n, m, i, j,energy, aux, **mat;
	Move **field;

	/* Recebe tamanho do tabuleiro e a enrgia do robo */
    scanf("%d %d %d", &n, &m, &energy);

    /* Aloca a matriz que guarda os possiveis movmentos do robo em cada posicao e *
     * a matriz que marca os passos do robo */
	field = malloc(n * sizeof(Move*));
	mat = malloc(n * sizeof(int*));

	for(i = 0; i < n; i++){

		/* Aloca as colunas das matrizes */
		field[i] = malloc(m * sizeof(Move));
		mat[i] = malloc(m * sizeof(int));

		/* Recebe a entrada */
		for(j = 0; j < m; j++){
			scanf("%d", &aux);

			/* Chama a funcao que decodifica a entrada */
			MovementRead(&field[i][j], aux);
		}	
	}

	/* Cada volta do loop testa os possiveis caminhos que o robo realiza saindo da *
	 * posicao mais a esquerda em cada linha da matriz */
	for(i = 0; i < n; i++){

		/* Inicializa a mtriz inteira com -1 e identifica a primeira posicao com 0 */
		inicializate(mat, n, m);
		mat[i][0] = 0;

		/* Caso a funcao retorna verdadeiro, o robo pode sair vivo */
		if(Walking(mat, field, i, 0, m - 1, energy))
			printf("Sim\n");

		/* Caso contrario nao ha caminho possivel */
		else
			printf("Nao\n");
	}

 	return 0;
 }