#include <stdlib.h>
#include <stdio.h>

#define TAMCONTA 100

typedef struct{
	int codigo;
	char descricao[100];;
} Conta;

typedef struct{
	int codigo;
	char descricao[100];;
	char tipo;
} Historico;

typedef struct{
	int dia, mes, ano;
	Conta conta[1];
	Historico historico[1];
	float valor;
	char complemento[100];
};

void cadastrarConta();
void escolherOperacao();
void efetuarOperacao();

Conta conta[TAMCONTA];
int contascadastradas = 0;
int contacorrente = 0;

int main(){

	int opcao;
	printf(" Bem vindo !! ");

	do{
		printf(" 1 - Cadastrar conta ");
		printf(" 2 - Escolher conta ");
		printf(" 3 - Efetuar operação ");
		printf(" 4 - Sair ");
		scanf(" %d ", &opcao);

		switch (opcao)
		{
		   case 1:
			 cadastrarConta();
			 break;
		   case 2:
			 escolherOperacao();
			 break;
		   case 3:
		     efetuarOperacao();
		     break;
		   case 4:
			 printf(" ... | Bye bye |... ");
			 break;
		   default:
		   	 printf(" Opção invalida digite ");
		     break;
		}

	}while(opcao != 4);

}

void cadastrarConta(){
	int codigo , opcao;
	char descricao;

	printf(" Digite codigo da conta ");
	scanf(" %d ", &codigo);

	printf(" Digite descricao da conta ");
	scanf(" %d ", &descricao);

	conta[contascadastradas].codigo = codigo;
	conta[contascadastradas].descricao = descricao;

	contascadastradas++;
	printf(" Deseja entrar na conta cadastrada ? 1 - Sim , 2 - Não");
	do{
		switch (opcao)
		{
		 case 1:
		   escolherOperacao();
		   break;
		 case 2:
		   main();
		   break;
		 default:
		   printf(" Opção invalida ");
		   break;
		}
	}while(opcao != 2)
}
