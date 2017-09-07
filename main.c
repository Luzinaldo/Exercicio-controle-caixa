#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#define TAMCONTA 100

typedef struct{
	int codigo;
	char descricao[100];
}Conta;

typedef struct{
	int codigo;
	char descricao[100];
	char tipo;
}Historico;

typedef struct{
	int dia, mes, ano;
	float valor;
	char complemento[100];
}Movimentacao;

    Conta conta[TAMCONTA]; Historico historico[TAMCONTA]; Movimentacao movimentacao[TAMCONTA];

    int cadastrarcontasG = 0;

int main(){
    setlocale(LC_ALL, "Portuguese");

	char opcao;
	printf(" Bem vindo !! ");

	do{
		printf("\n\t 1 - Cadastrar conta ");
		printf("\n\t 2 - Escolher conta ");
		printf("\n\t 3 - Efetuar operação ");
		printf("\n\t 4 - Sair ");
		printf("\n\t\t Escolha uma das opções: ");
		scanf(" %c ", &opcao);

		switch (opcao){
		   case '1': break;

		   case '2': break;

		   case '3': break;

		   case '4': printf("Saindo... "); break;

		   default: printf(" Opção invalida... "); break;
		}

	}while(opcao != 4);
}

void CadastrarConta(){
    int codigo;
    char descricao[100];

    printf("\n Digite o codigo: ");
    scanf("%d", &codigo);
    printf("\n Descricao: ");
    scanf("%s", descricao);

    conta.codigo[cadastrarcontasG] = codigo;
    strcpy(conta.descricao[cadastrarcontasG], descricao);

    cadastrarcontasG++;
}
