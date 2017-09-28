#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define TAMCONTA 100
#define QTDMAXIMAMOVIMENTACAODIA 20
#define TAMMOVIMENTACAO 100
#define TAMHISTORICO 10
#define CODDEBITO "D"
#define CODCREDITO "C"

typedef struct{
	int codigo;
	char descricao[100];
} Conta;

typedef struct{
	int codigo;
	char descricao[100];
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
void alterarConta();
void excluirConta();
void auxEscolherConta(int numeroconta);
int buscaConta(int numeroconta);
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
void movimentacoesHoje();
void minhasMovimentacoesHoje();
void minhasMovimentacoesFiltroDia();
int verificaSeExecedeuMovimentacoes(char data[11]);
void _listagemMovimentacaoComFiltro(char filtroData[11] , char tipoData[2] , int filtroIndexConta);

/* função auxiliar */
void parseData(char data[11], int *dia , int *mes , int *ano);
void parseDataUSA(char data[11], int *dia , int *mes , int *ano);

/* testes */
void testInsertDadosConta();
void testInsertDadosHistorico();
void testInsertDadosMovimentacao();

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

	printf("\t\t----------------------------------------------------\n");
	printf("\t\t------------------ FLUXO DE CAIXA ------------------\n");
	printf("\t\t----------------------------------------------------\n");
	printf("\t\t\t      BEM VINDO ao Menu Principal !! \n \n");

	//testInsertDadosConta();
	//testInsertDadosHistorico();
	//testInsertDadosMovimentacao();
	//contaAtual = 123;
	//movimentacoesHoje();
	//listarContas();

	do{
		if(contaAtual != 0){
			printf(" %s \n" , dadosConta(contaAtual).descricao);
		}
		printf("\t 1 - Cadastrar conta \n");
		printf("\t 2 - Excluir conta \n");
		printf("\t 3 - Escolher conta \n");
		printf("\t 4 - Listar contas \n");
		printf("\t 5 - Movimentações do dia \n");
		printf("\t 6 - Lista de historico \n");
		printf("\t 7 - Cadastrar historico \n \n");
		if(contaAtual != 0){
			printf("\t 8 - Efetuar operação \n");
			printf("\t 9 - Listar minhas movimentações \n");
			printf("\t 10 - Alterar minha conta \n");
			printf("\t 11 - Meu saldo \n");
			printf("\t 12 - Minhas movimentacões de hoje \n");
			printf("\t 13 - Minhas movimentações (Filtro Data) \n");
			printf("\t 14 - Sair da conta \n \n");
		}
		printf("\t 15 - Sair do Sistema \n");
		printf("\n\t Digite uma opção: ");

		scanf("%d", &opcao);
		setbuf(stdin, NULL);

		switch (opcao)
		{
		   case 1:
			 cadastrarConta();
			 break;
		   case 2:
			 excluirConta();
			 break;
		   case 3:
			 escolherConta();
			 break;
		   case 4:
			 listarContas();
			 break;
		   case 5:
			 movimentacoesHoje();
			 break;
		   case 6:
			 listarHistoricos();
			 break;
		   case 7:
			 cadastrarHistorico();
			 break;
		   case 8:
		     efetuarOperacao();
		     break;
		   case 9:
			 listarMovimentacoes();
			 break;
		   case 10:
			 alterarConta();
			 break;
		   case 11:
			 exibirSaldo();
			 break;
		   case 12:
			 minhasMovimentacoesHoje();
			 break;
		   case 13:
			 minhasMovimentacoesFiltroDia();
			 break;
		   case 14:
			 contaAtual = 0;
			 printf(" \n \n \n \n");
			 break;
		   case 15:
			 printf("\n \n ... | Bye bye |... \n \n");
			 break;
		   default:
		   	 printf(" Opção invalida \n Digite um numero valido \n");
		     break;
		}

	}while(opcao != 15);

}

void cadastrarConta(){
	int codigo , opcao;
	char descricao[100];

	printf("\n \n \t Cadastro de conta\n");
	do{
		printf("\t Digite codigo da conta: ");
		scanf("%d", &codigo);
		setbuf(stdin, NULL);
		if(buscaConta(codigo) == 1){
            printf("\t Codigo de conta já existente\n");
		}
	}while(buscaConta(codigo) == 1);

	printf("\t Digite descricao da conta: ");
	fgets (descricao, 100, stdin);
	setbuf(stdin, NULL);

	conta[contascadastradas].codigo = codigo;
	strcpy(conta[contascadastradas].descricao,descricao);

	contascadastradas++;

	printf(" Deseja entrar na conta cadastrada? ");
	printf("\n Sim - 1 \n Nao - 2\n");
	printf(" Opção: ");
	do{
		scanf("%d", &opcao);

		switch (opcao)
		{
		 case 1:
		   efetuarOperacao(); break;
		 case 2:
		   main(); break;
		   printf("\n\n\n");
		 default:
        	 printf(" Opção invalida !! \t Digite um numero valido \n"); break;
		}
	}while(opcao != 2);
}

void alterarConta(){
	int opcaoAlterar;
	int index = buscaConta(contaAtual);
	--index;
	printf("Deseja alterar o codigo? "); printf("\t \n Sim - 1 || \n Não - 0 \n");
	scanf("%d", &opcaoAlterar);
	setbuf(stdin, NULL);
	if(opcaoAlterar){
		printf("Digite o codigo da conta");
		scanf("%d", conta[index].codigo);
		setbuf(stdin, NULL);
		opcaoAlterar = 0;
	}
	printf("Deseja alterar a descrição?"); printf("\t \n Sim - 1 || \n Não - 0 \n");
	scanf("%d",&opcaoAlterar);
	setbuf(stdin, NULL);
	if(opcaoAlterar){
		printf("Digite a descrição da conta");
		fgets(conta[index].descricao, 100, stdin);
		setbuf(stdin, NULL);
	}

	printf("Conta alterada com sucesso !! \n");
}

void excluirConta(){
	int removerconta;
	int contaencontrada = 0;

	printf("Digite o codigo da conta que deseja remover : \n");
	scanf("%d",&removerconta);

	for(int i=0;i < contascadastradas;i++)
	{
	    if(conta[i].codigo == removerconta)
	    {
	       contaencontrada = 1;

	       for(int j=i; j<contascadastradas-1; j++){
	    	   conta[j].codigo = conta[j+1].codigo;
	    	   strcpy(conta[j].descricao, conta[j+1].descricao);
	       }
	       contascadastradas--;
	    }
	}

	if(contaencontrada){
		printf("Conta deletada com sucesso : \n");
	}else{
		printf("Conta não encontrada : \n");
	}

}

void listarContas(){
	if(contascadastradas > 0){
		for(int i = 0; i < contascadastradas; i++){
			printf("%d - %s \n", conta[i].codigo , conta[i].descricao );
		}
	}else{
		printf(" Não possui nenhuma conta cadastrada \n");
	}
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

int buscaConta(int numeroconta){
    int achei = 0;
	for(int i = 0; i < contascadastradas; i++){
		if(conta[i].codigo == numeroconta){
			achei = 1;
		}
	}
	return achei;
}

Conta dadosConta(int numeroconta){
	int index = buscaConta(numeroconta);
	return conta[--index];
}

int verificaSeExecedeuMovimentacoes(char data[11]){
	int qtdmovimentacao = 0;
	int diadata , mesdata, anodata;

	parseData(data, &diadata, &mesdata , &anodata);

	if(movimentacaocadastradas > 0){
		for(int i = 0; i < movimentacaocadastradas; i++){
			/*  */
			if(!(movimentacao[i].dia == diadata &&
			   movimentacao[i].mes == mesdata &&
			   movimentacao[i].ano == anodata )){

				qtdmovimentacao++;
			}
		}
	}

	if(qtdmovimentacao <= QTDMAXIMAMOVIMENTACAODIA){
		return 0;
	}

	return 1;

}

void efetuarOperacao(){
	int codigoOperacao;
	int operacaoEncontrada = 0;
	float valorMovimentacao;
	char data[11] , complemento[100];
	char opcao;

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
		if(verificaSeExecedeuMovimentacoes(data)){
			printf(" \n Limite de movimentações para esta dia excedeu !! \n ");
			main();
		}

		printf("\n Digite informações adicionais referente a movimentação \n ");
		fgets(complemento, 100, stdin);
		setbuf(stdin, NULL);

		operacaoEncontrada = buscaHistorico(codigoOperacao);
		movimentacao[movimentacaocadastradas].historico = historico[(operacaoEncontrada - 1)];
		movimentacao[movimentacaocadastradas].conta = dadosConta(contaAtual);
		movimentacao[movimentacaocadastradas].valor = valorMovimentacao;
		strcpy(movimentacao[movimentacaocadastradas].complemento, complemento);
		parseData(data,
			&movimentacao[movimentacaocadastradas].dia ,
			&movimentacao[movimentacaocadastradas].mes ,
			&movimentacao[movimentacaocadastradas].ano);

		movimentacaocadastradas++;

		printf(" \n Deseja efetuar mais alguma operação? \n");
		printf(" SIM - 1 >><< Caso não deseje, aperte qualquer tecla\n ");
		printf(" Opção: ");
		scanf("%c", &opcao);

        if(opcao != '1'){
            main();
        }
	}while(opcao == '1');

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

	 /* printf(" \n Seu saldo atual é de R$ %c %.2f.", (saldo < 0) ? '-' : ' ' , saldo); */
	printf(" \n Seu saldo atual é de R$ %c %.2f.", (saldo < 0) ? '-' : ' ' , saldo);
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
		printf(" \t Não existe nenhuma historico cadastrado \n \n");
	}
}


void movimentacoesHoje(){
	char dataatual[11];
	//_strdate(dataatual);
	_listagemMovimentacaoComFiltro(dataatual , "U", 0);
}

void minhasMovimentacoesHoje(){
	int index;
	char dataatual[11];
	//_strdate(dataatual);

	index = buscaConta(contaAtual);
	_listagemMovimentacaoComFiltro(dataatual ,"U", index);
}

void minhasMovimentacoesFiltroDia(){
	int index;
	char data[11];
	printf(" \n Digite o valor do filtro movimentações no formato 01/01/1999 \n ");
	fgets(data, 11, stdin);
	setbuf(stdin, NULL);

	index = buscaConta(contaAtual);
	_listagemMovimentacaoComFiltro(data ,"B", index);
}

/*
 * filtroConta <> 0
 * tipoData = 'U' - 12/30/17 ,  'B' - 30/12/2017
 *
 * */
void _listagemMovimentacaoComFiltro(char filtroData[11] , char tipoData[2] , int filtroIndexConta){
	char datamovimentacao[11];
	int diadatafiltro , mesdatafiltro, anodatafltro;
	int index;

	if(strcmp(tipoData,"U") == 0){
		parseDataUSA(filtroData, &diadatafiltro, &mesdatafiltro , &anodatafltro);
		anodatafltro = anodatafltro + 2000;
	}else{
		parseData(filtroData, &diadatafiltro, &mesdatafiltro , &anodatafltro);
	}

	/* Padronizacao para comparacao */
	char descricaoTipo[20];
	float totalCredito = 0,totalDebito = 0,totalSaldo = 0;

	if(movimentacaocadastradas > 0){
		printf(" \n Lista transações do dia %d/%d/%d \n \n",diadatafiltro,mesdatafiltro,anodatafltro);
		for(int i = 0; i < movimentacaocadastradas; i++){
			int exibir = 1;

			/* verifica o filtro da data */
			if(!(movimentacao[i].dia == diadatafiltro &&
			   movimentacao[i].mes == mesdatafiltro &&
			   movimentacao[i].ano == anodatafltro ))
				exibir = 0;

			/* verifica o filtro de Conta */
			if(filtroIndexConta != 0){
				if(conta[--filtroIndexConta].codigo != movimentacao[i].conta.codigo)
				exibir = 0;
			}

			if(exibir){
				if(strcmp(movimentacao[i].historico.tipo,CODDEBITO) == 0){
					strcpy(descricaoTipo,"DEBITO");
					totalDebito -= movimentacao[i].valor;
					totalSaldo -= movimentacao[i].valor;
				}else{
					strcpy(descricaoTipo,"CREDITO");
					totalCredito += movimentacao[i].valor;
					totalSaldo += movimentacao[i].valor;
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
		printf(" *********** Totais *********** \n");
		printf(" Credito :  \t %.2f  \n", totalCredito);
		printf(" Debito :  \t %.2f  \n", totalDebito);
		printf(" Saldo :  \t %.2f  \n \n \n", totalSaldo);

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

void parseDataUSA(char data[11], int *dia , int *mes , int *ano)
{

	//01/30/1999

	// 0, 1 = mes
	// 2    = /
	// 3, 4 = dia
	// 5    = /
	// 6, 7 = ano
	// 8   = NULO

	char _dia[3] = {
		data[3],
		data[4],
		0
	};
	char _mes[3] = {
		data[0],
		data[1],
		0
	};
	char _ano[5] = {
		data[6],
		data[7],
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

void testInsertDadosMovimentacao(){

	/* JEFFERSON */

	/* MOVIMENTAÇÃO POSITIVA */
	movimentacao[0].ano = 2017;
	movimentacao[0].dia = 27;
	movimentacao[0].mes = 9;
	movimentacao[0].historico = historico[1];
	movimentacao[0].conta = conta[0];
	movimentacao[0].valor = 150.0;
	strcpy(movimentacao[0].complemento, "Recebi um pagamento");

	movimentacao[1].ano = 2017;
	movimentacao[1].dia = 27;
	movimentacao[1].mes = 9;
	movimentacao[1].historico = historico[1];
	movimentacao[1].conta = conta[0];
	movimentacao[1].valor = 150.0;
	strcpy(movimentacao[1].complemento, "Recebi um pagamento");

	/* MOVIMENTAÇÃO NEGAIIVA */
	movimentacao[2].ano = 2017;
	movimentacao[2].dia = 27;
	movimentacao[2].mes = 9;
	movimentacao[2].historico = historico[0];
	movimentacao[2].conta = conta[0];
	movimentacao[2].valor = 50.0;
	strcpy(movimentacao[2].complemento, "paguei uma conta");

	/* COM DATA DIFERENTE */
	movimentacao[3].ano = 2017;
	movimentacao[3].dia = 20;
	movimentacao[3].mes = 9;
	movimentacao[3].historico = historico[0];
	movimentacao[3].conta = conta[0];
	movimentacao[3].valor = 50.0;
	strcpy(movimentacao[3].complemento, "paguei uma conta");


	movimentacaocadastradas = 4;

}
