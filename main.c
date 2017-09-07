#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

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

//test
void testInsertDadosConta();

Conta conta[TAMCONTA];
int contascadastradas = 0;
int contaatual = 0;

int main(){

	int opcao;
	//	setlocale(LC_ALL, "pt-br");

	printf(" Bem vindo !!  \n \n");

	testInsertDadosConta();
	listarContas();

	do{
		printf(" 1 - Cadastrar conta \n");
		printf(" 2 - Escolher conta \n");
		printf(" 3 - Efetuar opera��o \n");
		if(contaatual =! 0){
			printf(" 4 - Sair da conta \n");
		}else{
			printf(" 4 - Sair do Sistema \n");
		}

		scanf("%d", &opcao);
		setbuf(stdin, NULL);

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
			 printf("\n \n ... | Bye bye |... \n \n");
			 break;
		   default:
		   	 printf(" Op��o invalida digite \n");
		     break;
		}

	}while(opcao != 4);

}

void cadastrarConta(){
	int codigo , opcao;
	char descricao[100];

	printf("\n \n Cadastro de conta \n");
	printf("_________________________ \n");
	printf(" Digite codigo da conta \n");
	scanf("%d", &codigo);
	setbuf(stdin, NULL);

	printf(" Digite descricao da conta \n");
	fgets (descricao, 100, stdin);
	setbuf(stdin, NULL);

	conta[contascadastradas].codigo = codigo;
	strcpy(conta[contascadastradas].descricao , descricao);

	contascadastradas++;

	printf(" Deseja entrar na conta cadastrada ? \n 1 - Sim \n 2 - Não \n\n");

	do{
		scanf("%d", &opcao);

		switch (opcao)
		{

		 case 1:
		   //escolherOperacao();
		   listarContas();
		   break;
		 case 2:
		   main();
		   break;
		 default:
		   printf(" Op��o invalida , tente novamente \n");
		   break;
		}
	}while(opcao != 2);
}

void listarContas(){
	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){

			printf("%s - %s", &conta[i].codigo , &conta[i].descricao );
			printf(" \n _______________________ \n");
		}
	}else{
		printf(" N�o possui nenhuma conta cadastrada \n");
	}

}

void testInsertDadosConta(){

	conta[0].codigo = 123;
	strcpy(conta[0].descricao , "jefferson");

	conta[1].codigo = 321;
	strcpy(conta[1].descricao , "matheus");

	conta[2].codigo = 432;
	strcpy(conta[2].descricao , "deividi");

	contascadastradas = 3;

}


