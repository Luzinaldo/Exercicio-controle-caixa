#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define TAMCONTA 100
#define TAMMOVIMENTACAO 100
#define TAMHISTORICO 10
#define CODDEBITO "D"
#define CODCREDITO "C"

typedef struct{
	int codigo;
	char descricao[100];;
} Conta;

typedef struct{
	int codigo;
	char descricao[100];;
	char tipo[1];
} Historico;

typedef struct{
	int dia, mes, ano;
	Conta conta;
	Historico historico;
	float valor;
	char complemento[100];
} Movimentacao;

/* funções conta */
void listarContas();
void cadastrarConta();
void auxEscolherConta(int numeroconta);
void escolherConta();

/* funções historicos */
void listarHistoricos();
void cadastrarHistorico();
int buscaHistorico(int codigo);
void escolherOperacao();
void efetuarOperacao();

/* testes */
void testInsertDadosConta();
void testInsertDadosHistorico();

Conta conta[TAMCONTA];
int contascadastradas = 0;
int contaAtual = 0;

Historico historico[TAMHISTORICO];
int historicoscadastrados = 0;

Movimentacao movimentacao[TAMMOVIMENTACAO];
int movimentacaocadastradas = 0;


int main(){

	int opcao;
	setlocale(LC_ALL, "portuguese");

	if(contaAtual != 0){
		printf(" Menu Principal !! , %s \n \n", conta[contaAtual].descricao);
	}else{
		printf(" Menu Principal !! \n \n");
	}

	testInsertDadosConta();
	testInsertDadosHistorico();
	//listarContas();

	do{
		printf(" 1 - Cadastrar conta \n");
		printf(" 2 - Escolher conta \n");
		printf(" 3 - Lista de historico \n");
		printf(" 4 - Cadastrar historico \n");
		printf(" 5 - Efetuar operação \n");
		printf(" 6 - Sair do Sistema \n");
		if(contaAtual != 0){
			printf(" 7 - Sair da conta \n");
		}


		scanf("%d", &opcao);
		setbuf(stdin, NULL);

		switch (opcao)
		{
		   case 1:
			 cadastrarConta();
			 break;
		   case 2:
			 escolherConta();
			 break;
		   case 3:
			 listarHistoricos();
			 break;
		   case 4:
			 cadastrarHistorico();
			 break;
		   case 5:
		     efetuarOperacao();
		     break;
		   case 6:
			 printf("\n \n ... | Bye bye |... \n \n");
			 break;
		   case 7:
			 contaAtual = 0;
			 break;
		   default:
		   	 printf(" Opção invalida \n Digite um numero valido \n");
		     break;
		}

	}while(opcao != 6);

}

void cadastrarConta(){
	int codigo , opcao;
	char descricao[100];

	printf("\n \n Cadastro de conta \n");
	printf("_________________________ \n");
	do{
		printf(" Digite codigo da conta \n");
		scanf("%d", &codigo);
		setbuf(stdin, NULL);
	}while(codigo == 0);

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
		   efetuarOperacao();
		   break;
		 case 2:
		   main();
		   break;
		 default:
        	 printf(" Opção invalida \n Digite um numero valido \n");
		   break;
		}
	}while(opcao != 2);
}

void cadastrarHistorico(){
		int codigo ;
		char descricao[100];
		char tipo[2];

		printf("\n \n Cadastro de historico \n");
		printf("_________________________ \n");

		do{
			printf(" Digite codigo do historico \n");
			scanf("%d", &codigo);
			setbuf(stdin, NULL);
		}while(codigo == 0);

		printf(" Digite descricao do historico \n");
		fgets(descricao, 100, stdin);
		setbuf(stdin, NULL);

		printf(" Escolha o tipo de historico \n");
		printf(" %s - CREDITO \n", CODCREDITO );
		printf(" %s - DEBITO \n", CODDEBITO );

		while(1){
			scanf("%s",&tipo);
			setbuf(stdin, NULL);
			if((strcmp(tipo,"C") == 0) || (strcmp(tipo,"D") == 0)){
				break;
			}else{
				printf("Valor invalido , digite um dos valores disoniveis !! \n");
			}
		}


		historico[historicoscadastrados].codigo = codigo;
		strcpy(historico[historicoscadastrados].descricao , descricao);
		strcpy(historico[historicoscadastrados].tipo , tipo);

		historicoscadastrados++;

		main();

}

void escolherConta(){
	int numeroconta;

	printf("Digite sua conta \n ");
	scanf("%d", &numeroconta);
	printf(" \n");

	auxEscolherConta(numeroconta);

	if(contaAtual){
		efetuarOperacao();
	}

}

void auxEscolherConta(int numeroconta){
	int booleantentarnovamente;

	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){
			if(conta[i].codigo == numeroconta){
				contaAtual = conta[i].codigo;
				break;
			}
		}

		if(contaAtual == 0){
			printf(" Conta não encontrada \n \n ");
			printf(" Deseja tentar novamente ? \n 1 - sim \t 2 - não ");
			scanf("%d", &booleantentarnovamente);
			printf("\n \n ");
			if(booleantentarnovamente == 1){
				escolherConta();
			}else{
				main();
			}
		}

	}else{
		printf(" Não  possui nenhuma conta cadastrada \n \n");
	}

}

void efetuarOperacao(){
	int codigoOperacao;
	int operacaoEncontrada = 0;
	listarHistoricos();
	do{
		printf(" Digite o codigo da operação que deseja ?");
		scanf("%d", &codigoOperacao);

		operacaoEncontrada = buscaHistorico(codigoOperacao);
		movimentacao[movimentacaocadastradas].historico = historico[(operacaoEncontrada - 1)];

		/*
		printf("1 - %d \n" , movimentacao[movimentacaocadastradas].historico.codigo );
		printf("2 - %s \n" , movimentacao[movimentacaocadastradas].historico.descricao );
		printf("3 - %s \n" , movimentacao[movimentacaocadastradas].historico.tipo );
		*/

	}while(operacaoEncontrada);

}

int buscaHistorico(int codigo){
	for(int i = 0; i < historicoscadastrados; i++){
		if(historico[i].codigo == codigo){
			return i + 1;
		}
	}
	return 0;
}

void listarHistoricos(){
	char descricaoTipo[20];

	if(historicoscadastrados > 0){
			printf(" \n Lista de Historicos \n \n");
			for(int i = 0; i < historicoscadastrados; i++){

				if(strcmp(historico[i].tipo,CODDEBITO) == 0){
					strcpy(descricaoTipo,"DEBITO");
				}else{
					strcpy(descricaoTipo,"CREDITO");
				}
				printf("%d - \t %s \t %s \n",
						historico[i].codigo,
						historico[i].descricao,
						descricaoTipo
				);
			}
			printf(" \n \n");
	}else{
		printf(" Não existe nenhuma historico cadastrado \n \n");
	}
}

void listarContas(){
	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){
			printf("%d - %s \n", conta[i].codigo , conta[i].descricao );
		}
	}else{
		printf(" N�o possui nenhuma conta cadastrada \n");
	}

}


/* funções teste rapido */

void testInsertDadosConta(){

	conta[0].codigo = 123;
	strcpy(conta[0].descricao , "jefferson");

	conta[1].codigo = 321;
	strcpy(conta[1].descricao , "matheus");

	conta[2].codigo = 432;
	strcpy(conta[2].descricao , "deividi");

	contascadastradas = 3;

}

void testInsertDadosHistorico(){

	historico[0].codigo = 1;
	strcpy(historico[0].descricao , "PAG_2");
	strcpy(historico[0].tipo , "D");

	historico[1].codigo = 2;
	strcpy(historico[1].descricao , "RECEBIMENTO");
	strcpy(historico[1].tipo , "C");

	historico[2].codigo = 3;
	strcpy(historico[2].descricao , "PAG_1");
	strcpy(historico[2].tipo , "D");

	historicoscadastrados = 3;

}




