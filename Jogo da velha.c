#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define TAM 3

void mostrar_tabuleiro(char tabuleiro[TAM][TAM]){
	short i, j;
	
	printf("\nTabuleiro: \n");
	printf("\n-------------------");
	for(i = 0; i < TAM; i ++){
		if(i == 0)
			printf("\n|");
		else
			printf("|");
		for(j = 0; j < TAM; j ++)
			printf("  %-3c|", tabuleiro[i][j]);
		printf("\n-------------------\n");
	}
}

void clear(){
	printf("\n");
	system("pause");
	system("cls");
}

// Turno = 1 - jogador 1 (X) | 2 - jogador 2 (O)
int checa_tabuleiro(char tabuleiro[TAM][TAM], short turno){
	short i, j, diagonal[2] = {0, 0}, horizontal[3] = {0, 0, 0}, vertical[3] = {0, 0, 0}, aux = TAM-1;
	// diagonal = 0 - principal | 1 - secundária
	// horizontal = 0 - linha 1 | 1 - linha 2 | 2 - linha 3
	// vertical = 0 - coluna 1 | 1 - coluna 2 | 2 - coluna 3
	// aux = auxilia na contagem da diagonal secundária
	
	short cont = 0;
	// Checagem se todo o tabuleiro está totalmente preenchido
	for(i = 0; i < TAM; i ++){
		for(j = 0; j < TAM; j ++){
			if(tabuleiro[i][j] != ' ')
				cont ++;
		}
	}
	if(cont == 9){
		return 3;
	}
	
	// Jogador 1
	for(i = 0; i < TAM; i ++){
		for(j = 0; j < TAM; j ++){
			if(turno == 1 && tabuleiro[i][j] == 'X'){
				horizontal[i] ++;
				if(j == aux)
					diagonal[1] ++;
				if(turno == 1 && i == j && tabuleiro[i][j] == 'X')
					diagonal[0] ++;
			}
			if(turno == 1 && tabuleiro[j][i] == 'X')
				vertical[i] ++;
		}
		aux --;
	}
	// Verificando se há algum trio na diagonal, vertical e diagonal
	for(i = 0; i < TAM; i ++){
		if(i <= 1){
			if(diagonal[i] == 3)
				return 1;
		}
		if(horizontal[i] == 3 || vertical[i] == 3)
			return 1;
	}
	
	
	// Resetando os valores dos contadores
	for(i = 0; i < TAM; i ++){
		if(i < TAM-1)
			diagonal[i] = 0;
		horizontal[i] = 0;
		vertical[i] = 0;
	}
	aux = TAM-1;
	
	
	// Jogador 2
	for(i = 0; i < TAM; i ++){
		for(j = 0; j < TAM; j ++){
			if(turno == 2 && tabuleiro[i][j] == 'O'){
				horizontal[i] ++;
				if(j == aux)
					diagonal[1] ++;
				if(turno == 2 && i == j && tabuleiro[i][j] == 'O')
					diagonal[0] ++;
			}
			if(turno == 2 && tabuleiro[j][i] == 'O')
				vertical[i] ++;
		}
		aux --;
	}
	// Verificando se há algum trio na diagonal, vertical e diagonal
	for(i = 0; i < TAM; i ++){
		if(i < TAM-1){
			if(diagonal[i] == 3)
				return 2;
		}
		if(horizontal[i] == 3 || vertical[i] == 3)
			return 2;
	}
	
	return 0;
}

int main(){
	setlocale(LC_ALL, "portuguese");
	
	char tabuleiro[TAM][TAM] = {{' ', ' ', ' '},
								{' ', ' ', ' '},
								{' ', ' ', ' '}};
	short linha, coluna, turno = 1, decisao;
	
	while(true){
		while(true){
			mostrar_tabuleiro(tabuleiro);
			printf("\n+=+=+=+=+=+=+=+=+=+=\n");
			printf("Jogador %hd\n", turno);
			printf("+=+=+=+=+=+=+=+=+=+=");
			printf("\n\nSua jogada(escolha uma linha): ");
			scanf("%hd", &linha);
			printf("\nSua jogada(escolha uma coluna): ");
			scanf("%hd", &coluna);
			linha --, coluna --;
			
			if(0 <= linha <= TAM-1 && 0 <= coluna <= TAM-1){
				if(tabuleiro[linha][coluna] == ' '){
					if(turno == 1){
						tabuleiro[linha][coluna] = 'X';
						break;
					}else{
						tabuleiro[linha][coluna] = 'O';
						break;
					}
				}else
					printf("\nEsta posição já está ocupada!\n");
			}else
				printf("\nLinha ou coluna inválida!\n");
			clear();
		}
		clear();
		decisao = checa_tabuleiro(tabuleiro, turno);
		if(decisao == 1){
			mostrar_tabuleiro(tabuleiro);
			printf("+=+=+=+=+=+=+=+=+=+=");
			printf("\nO jogador 1 ganhou!\n");
			printf("+=+=+=+=+=+=+=+=+=+=");
			break;
		}else if(decisao == 2){
			mostrar_tabuleiro(tabuleiro);
			printf("+=+=+=+=+=+=+=+=+=+=+=+=+=");
			printf("\nO jogador 2 ganhou!\n");
			printf("+=+=+=+=+=+=+=+=+=+=+=+=+=");
			break;
		}else if(decisao == 3){
			mostrar_tabuleiro(tabuleiro);
			printf("+=+=+=+=+=+=+=+=+=+=+=+=+=");
			printf("\nO jogo empatou!\n");
			printf("+=+=+=+=+=+=+=+=+=+=+=+=+=");
			break;
		}
		(turno == 1) ? turno ++ : turno --;
	}
	
	printf("\n\nFim do programa!");
	return 0;
}
