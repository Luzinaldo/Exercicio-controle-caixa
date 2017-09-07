#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	Conta conta;
	Historico historico;
	float valor;
	char complemento[100];
} Movimentacao;

void listarContas();
void cadastrarConta();
void escolherOperacao();
void efetuarOperacao();

Conta conta[TAMCONTA];
int contascadastradas = 0;
int contaatual = 0;

int main(){

	int opcao;
	printf(" Bem vindo !!  \n \n");

	do{
		printf(" 1 - Cadastrar conta \n");
		printf(" 2 - Escolher conta \n");
		printf(" 3 - Efetuar operação \n");
		if(contaatual =! 0){
			printf(" 4 - Sair da conta \n");
		}else{
			printf(" 4 - Sair do Sistema ");
		}

		scanf(" %d ", &opcao);

		switch (opcao)
		{
		   case 1:
			 cadastrarConta();
			 break;
		   case 2:
			 //escolherOperacao();
			 break;
		   case 3:
		     //efetuarOperacao();
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
	setbuf(stdin, NULL);

	printf(" Digite descricao da conta ");
	scanf(" %s ", &descricao);
	setbuf(stdin, NULL);

	conta[contascadastradas].codigo = codigo;
	printf(" %s",descricao);
//	conta[contascadastradas].descricao = descricao;

	contascadastradas++;
	printf(" Deseja entrar na conta cadastrada ? 1 - Sim , 2 - Não");

	do{
		switch (opcao)
		{

		 case 1:
		   //escolherOperacao();
		   break;
		 case 2:
		   main();
		   break;
		 default:
		   printf(" Opção invalida ");
		   break;
		}
	}while(opcao != 2);
}

void listarContas(){
	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){

		}
	}else{
		printf(" Não possui nenhuma conta cadastrada ");
	}

}
