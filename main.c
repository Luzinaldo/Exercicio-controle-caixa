#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAMCONTA 100

typedef struct{
    int codigo;
    char descricao[100];
}Conta;
    Conta conta[TAMCONTA];

typedef struct{
    int  codigo;
    char descricao[100];
    char tipo; //Credito ou Debito
}Historico;
    Historico historico[TAMCONTA];

typedef struct{
    int data; //dia, mes, ano
    Conta conta;
    Historico historico;
    float valor;
    char complemento[100];
}Movimentacao;
    Movimentacao movimentacao[TAMCONTA];

    int contascadastradasG = 0, contMov = 0, cont_operacao = 0;

void CadastroConta();
void AcessarConta();
void Operacao();
void FuncMovimentacaoCred();
void FuncMovimentacaoDeb();
void ListarMovContaEspecif();
int _buscarConta(int codigo);
//void listarMovPorConta();
//int ExisteCodigo(int codigo, Conta *conta);

int main(){
    int opcao;
    setlocale(LC_ALL, "Portuguese");

    	//listarMovPorConta();

        do{
            printf("\n\t -------------- Fluxo de Caixa --------------\n");
            printf("\n\t1 - Cadastro: ");
            printf("\n\t2 - Acessar Conta: ");
            printf("\n\t3 - Efetuar Operação");
            printf("\n\t4 - Listar Movimentações");
            printf("\n\t5 - Sair");
            printf("\n\t\t Escolha uma opção: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

            switch(opcao){

                case 1: CadastroConta(); break;
                case 2: AcessarConta(); break;
                case 3: Operacao(); break;
                case 4: ListarMovContaEspecif(); break;
                case 5: printf("\n Saindo..."); break;
                default: printf("\nOpçao inválida !! "); break;
            }
        }while(opcao != 5);
    return 0;
}

void CadastroConta(){
    int codigo;
    char descricao[100];

    do{
    printf("\nDigite o codigo da conta: ");
	scanf("%d", &codigo);
	setbuf(stdin, NULL);

        if(_buscarConta(codigo) == 1){
            printf("\t >> Codigo já existe << ");
        }

	}while(_buscarConta(codigo) == 1);


	printf("Digite a descricao da conta: ");
	scanf("%s", &descricao);
	setbuf(stdin, NULL);

	conta[contascadastradasG].codigo = codigo;
	strcpy(conta[contascadastradasG].descricao, descricao);
	contascadastradasG++; //Incremento de quantas contas serão cadastradas
}

void AcessarConta(){

    int codigo, LINHA;
    int pos = contascadastradasG;
    printf("Digite o codigo da conta: ");
    scanf("%d", &codigo);

    for(LINHA = 0; LINHA < pos; LINHA++){
        if(codigo == conta[LINHA].codigo){
            printf("\n\t>>>>>> Dados Da conta <<<<<< \n");
         printf("\nConta: %d", conta[LINHA].codigo);
         printf("\nDescrição: %s", conta[LINHA].descricao);
         printf("\nSaldo: %0.2f", movimentacao[LINHA].valor);
         break;
        }else if(codigo != conta[LINHA].codigo){
            printf("\n\t>>    Essa conta não existe    <<\n");
            printf("\t---------------------------------\n");
            break;
        }
    }
}

void Operacao(){
    setlocale(LC_ALL, "Portuguese");
    char operacao;

    printf("Tipo de operação: ");
    printf("D - Débito || C - Credito: ");
    scanf("%c", &operacao);

    historico[cont_operacao].tipo = operacao;

    switch(historico[cont_operacao].tipo){

        case 'D': FuncMovimentacaoDeb(); break;
        case 'C': FuncMovimentacaoCred(); break;
        default: printf("TIPO DE OPERAÇÃO INVÁLIDA "); break;
    }
    cont_operacao++;
}

void FuncMovimentacaoDeb(){
    int data, codigo, LINHA, pos, ACHOU = 0, ACHOU2 = 0;
    float valor;
    char descricao[100];

        printf("\n\t Informe o codigo da conta: ");
        scanf("%d", &codigo);

    for(LINHA = 0; LINHA < contascadastradasG; LINHA++){
        if(codigo == conta[LINHA].codigo){
            ACHOU = 1;
            ACHOU2 = LINHA;
        }
    }

    if(ACHOU == 1){
        /*printf("\nDia: ");
        scanf("%d", &data);*/
        printf("Valor: ");
        scanf("%f", &valor);
        printf("O que foi feito: ");
        scanf("%s", &descricao);

        movimentacao[contMov].conta.codigo = conta[ACHOU2].codigo;
        movimentacao[contMov].conta.descricao = conta[ACHOU2].descricao;
        movimentacao[contMov].valor = movimentacao[contMov].valor - valor;
        strcpy(movimentacao[contMov].complemento, descricao);

    } else {
        printf("\n\t Conta não existe << ");
    }
    contMov++;
}

void FuncMovimentacaoCred(){
    int /*data*/codigo, LINHA, ACHOU = 0, ACHOU2 = 0;
    float valor;
    char descricao[100];

        printf("\n\t Informe o codigo da conta: ");
        scanf("%d", &codigo);
    for(LINHA = 0; LINHA < contascadastradasG; LINHA++){
        if(codigo == conta[LINHA].codigo){
            ACHOU = 1;
            ACHOU2 = LINHA;
        }
    }

    if(ACHOU == 1){
        /*printf("\nDia: ");
        scanf("%d", &data);*/
        printf("Valor: ");
        scanf("%f", &valor);
        printf("O que foi feito: ");
        scanf("%s", &descricao);

        movimentacao[contMov].conta.codigo = conta[ACHOU2].codigo;
        movimentacao[contMov].conta.descricao = conta[ACHOU2].descricao;
        movimentacao[contMov].valor = movimentacao[contMov].valor + valor;
        strcpy(movimentacao[contMov].complemento, descricao);
    }else{
        printf("\n\t Conta não existe << ");
    }
    contMov++;

}

void ListarMovContaEspecif(){
    int codigo, LINHA;

    //printf("Digite o codigo da conta: ");
    //scanf("%d", &codigo);

    for(LINHA = 0; LINHA < contMov; LINHA++){
        //if(codigo == conta[LINHA].codigo){
                    printf("\n\t\t Listagem de Movimentação da sua conta ");
        printf("\n\t Movimentações %d -- Conta: %s", LINHA+1, movimentacao[LINHA].conta.descricao);
        printf("\n\t Descrição: %s", movimentacao[LINHA].complemento);
        printf("\n\t Tipo da Movimentação: %c", historico[LINHA].tipo);
        printf("\n\t Valor da movimentação: %0.2f", movimentacao[LINHA].valor);
        printf("\n\n");
        //}
    }
}

/*void listarMovPorConta(){
	 int codigo;

	 printf("Digite o codigo da conta: ");
	 scanf("%d", &codigo);

	Conta contaFiltro = conta[_buscarConta(codigo)];

	for(int j = 0; j < (contmovDeb + contmovCred); j++){
		if(movimentacao[j].conta.codigo == contaFiltro.codigo){
			printf("\n\t\t Listagem de Movimentação da sua conta ");
			printf("\n\t Movimentações %d -- Conta: %d -- Descrição da conta: %s ", j+1, movimentacao[j].conta.codigo, movimentacao[j].conta.descricao);
			printf("\n\t Descrição: %s", movimentacao[j].complemento);
			printf("\n\t Tipo da Movimentação: %c", movimentacao[j].historico.tipo);
			printf("\n\t Valor da movimentação: %0.2f", movimentacao[j].valor);
			printf("\n\n");
		}
	}
}*/

int _buscarConta(int codigo){
    int ACHOU = 0;
	for(int j = 0; j < contascadastradasG ; j++){
		if(conta[j].codigo == codigo){
            ACHOU = 1;
		}
	}
	/* tratamento de erro ... */
	return ACHOU;
}

/*int ExisteCodigo(int codigo, Conta *conta){
    int LINHA, ACHOU = 0;

    for (LINHA = 0; LINHA < contascadastradasG; LINHA++){
        if(conta[LINHA].codigo == codigo){
            ACHOU = 1;
        }
    }

    return ACHOU;
}*/

/*void CadastroHistorico(){

    printf("")



}*/
