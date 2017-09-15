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
Conta dadosConta(int numeroconta);
void escolherConta();
void exibirSaldo();

/* funções historicos */
void listarHistoricos();
void cadastrarHistorico();
int buscaHistorico(int codigo);
void efetuarOperacao();

/* funções listar movimentação */
void listarMovimentacoes();

/* função auxiliar */
void parseData(char data[11], int *dia , int *mes , int *ano);

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


	printf(" Menu Principal !! \n \n");

	testInsertDadosConta();
	testInsertDadosHistorico();
	//listarContas();

	do{
		if(contaAtual != 0){
			printf(" %s \n" , dadosConta(contaAtual).descricao);
		}
		printf(" 1 - Cadastrar conta \n");
		printf(" 2 - Escolher conta \n");
		printf(" 3 - Lista de historico \n");
		printf(" 4 - Cadastrar historico \n \n");
		if(contaAtual != 0){
			printf(" 5 - Efetuar operação \n");
			printf(" 6 - Listar minhas movimentações \n");
			printf(" 7 - Meu saldo \n");
			printf(" 8 - Sair da conta \n \n");
		}
		printf(" 9 - Sair do Sistema \n");


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
			 listarMovimentacoes();
			 break;
		   case 7:
			 exibirSaldo();
			 break;
		   case 8:
			 contaAtual = 0;
			 printf(" \n \n \n \n");
			 break;
		   case 9:
			 printf("\n \n ... | Bye bye |... \n \n");
			 break;
		   default:
		   	 printf(" Opção invalida \n Digite um numero valido \n");
		     break;
		}

	}while(opcao != 9);

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

Conta dadosConta(int numeroconta){
	for(int i = 0; i < contascadastradas; i++){
		if(conta[i].codigo == numeroconta){
			return conta[i];
		}
	}
}

void efetuarOperacao(){
	int codigoOperacao;
	int operacaoEncontrada = 0;
	float valorMovimentacao;
	char data[11] , complemento[100];
	int opcao;

	listarHistoricos();
	do{
		printf(" \n Digite o codigo da operação que deseja ? \n ");
		scanf("%d", &codigoOperacao);
		setbuf(stdin, NULL);

		printf(" \n Digite o valor da movimentação \n ");
		scanf("%f", &valorMovimentacao);
		setbuf(stdin, NULL);

		printf(" \n Digite a data da movimentação no formato 01/01/1999 \n ");
		fgets(data, 11, stdin);
		setbuf(stdin, NULL);

		printf(" \n Digite imformações adicionais referente a movimentação \n ");
		fgets(complemento, 100, stdin);
		setbuf(stdin, NULL);

		operacaoEncontrada = buscaHistorico(codigoOperacao);
		movimentacao[movimentacaocadastradas].historico = historico[(operacaoEncontrada - 1)];
		movimentacao[movimentacaocadastradas].conta = dadosConta(contaAtual);
		movimentacao[movimentacaocadastradas].valor = valorMovimentacao;
		strcpy(movimentacao[movimentacaocadastradas].complemento,complemento);
		parseData(data,
			&movimentacao[movimentacaocadastradas].dia ,
			&movimentacao[movimentacaocadastradas].mes ,
			&movimentacao[movimentacaocadastradas].ano);

		movimentacaocadastradas++;

		printf(" Caso deseja não efetuar mais alguma operação 1 - sair ou qualquer tecla para continuar ... \n\n");
		scanf("%d", &opcao);

	}while(opcao != 1);

}

void exibirSaldo(){
	float saldo = 0;
	for(int h = 0 ; h < movimentacaocadastradas; h++){
		if(movimentacao[h].conta.codigo == dadosConta(contaAtual).codigo){
			if(strcmp(movimentacao[h].historico.tipo,CODDEBITO) == 0){
				saldo = saldo - movimentacao[h].valor;
			}else{
				saldo = saldo + movimentacao[h].valor;
			}
		}
	}

	printf(" \n Seu saldo atual é de R$ %s %.2f.", saldo , ((saldo < 0) ? "-" : " "));
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

void listarMovimentacoes(){
	char descricaoTipo[20];

	if(movimentacaocadastradas > 0){
		printf(" \n Lista de Movimentações \n \n");
		for(int i = 0; i < movimentacaocadastradas; i++){
			if(movimentacao[i].conta.codigo == dadosConta(contaAtual).codigo){
				if(strcmp(movimentacao[i].historico.tipo,CODDEBITO) == 0){
					strcpy(descricaoTipo,"DEBITO");
				}else{
					strcpy(descricaoTipo,"CREDITO");
				}

				printf("Descrição \t %s \n", movimentacao[i].historico.descricao);
				printf("Data \t %d  %d  %d \n",
						movimentacao[i].dia,
						movimentacao[i].mes,
						movimentacao[i].ano
				);

				printf("Tipo \t %s \n", descricaoTipo);
				printf("Complemento \t %s \n", movimentacao[i].complemento);
				printf("Valor \t %.2f \n", movimentacao[i].valor);
				printf(" \n \n");
			}
		}
	}else{
		printf(" Não existe nenhuma historico cadastrado \n \n");
	}
}

/*
void auxListarMovimentacoes(){

}
*/

void listarContas(){
	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){
			printf("%d - %s \n", conta[i].codigo , conta[i].descricao );
		}
	}else{
		printf(" N�o possui nenhuma conta cadastrada \n");
	}

}


void parseData(char data[11], int *dia , int *mes , int *ano)
{

	// 01/01/1999

	// 0, 1 = dia
	// 2    = /
	// 3, 4 = mes
	// 5    = /
	// 6, 7 , 8 , 9 = ano
	// 10    = NULO

	char _dia[3] = {
		data[0],
		data[1],
		0
	};
	char _mes[3] = {
		data[3],
		data[4],
		0
	};
	char _ano[5] = {
		data[6],
		data[7],
		data[8],
		data[9],
		0
	};


	*dia = atoi(_dia);
	*mes = atoi(_mes);
	*ano = atoi(_ano);

	return;

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




