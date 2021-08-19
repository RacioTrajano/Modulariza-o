#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

// funções de impressão##########################################################################################
// impreme_quadrino
void imprime_quadrinho(Comic* q){
    int i;

    printf("Titulo: %s\n", q->titulo);
    printf("Numero: %d\n", q->num);
    printf("Data de lancamento: %02d/%d\n", q->date.mes, q->date.ano);

    printf("Status da leitura: ");
    q->lido == 0 ? printf("Nao lido\n"):printf("Lido\n");

    printf("Personagens:\n");

    for(i=0; i < q->qtd_per; i++)
        printf("--> %s\n", q->personagens[i]);
}

//imprime_Consultas
void imprime_Consultas(){
    printf("\n\nMenu de Consultas Gerais\n");
    printf("4.1 - Listar Quadrinhos por ano\n");
    printf("4.2 - Listar Quadrinhos por Periodo\n");
    printf("4.3 - Listar Quadrinhos por Serie/Titulo\n");
    printf("4.4 - Listar aparicoes de Personagem em ordem cronologica\n");
    printf("4.5 - Listar quadrinhos lidos\n");
    printf("Digite a opcao (de 1 a 5): ");
}

//imprime_Menu
void imprime_Menu(){
    printf("\n\nMarvel Unlimited!\n");
    printf("MENU\n");
    printf("1 - Adicionar Quadrinho\n");
    printf("2 - Remover Quadrinho\n");
    printf("3 - Conultar um quadrinho\n");
    printf("4 - Consultas Gerais\n");
    printf("5 - Marcar quadrinho como lido\n");
    printf("6 - Sair\n\n");
    printf("Digite a opcao: ");
}

// função de alocação

char* aloca_e_copia(char* string){
  char* copy = malloc(sizeof(char) * strlen(string) + 1);
  strcpy(copy, string);
  return copy;
}

//funções que alteram dados ###################################################################################
//recupera quadrinho
Comic* recupera_quadrinho(Comic* banco, int tam, char* nome, int num){
    int i;
    Comic *temp = NULL;

    for(i=0; i<tam; i++){
        if(banco[i].num == num && strcmp(banco[i].titulo, nome) == 0){
          temp = &banco[i];
          break;
        }
    }

    return temp;
}
// adiciona_quadrinho

Comic* adiciona_quadrinho(Comic* banco, int* tam){
    char title[500], personagem[100];
    int number;
    int j;
    Comic* aux;

    //Pega as informações necessárias
    printf("\nInsira o titulo do quadrinho: ");
    scanf(" %[^\n]", title);

    printf("\nInsira o numero do quadrinho: ");
    scanf("%d", &number);

    //Verifica se o quadrinho a ser inserido já existe
    aux = recupera_quadrinho(banco, *tam, title, number);

    //Se o quadrinho não existe...
    if(aux == NULL){
        //Aumenta o tamanho do vetor de quadrinhos em um, para caber o novo
        banco = realloc(banco, sizeof(Comic) * (*tam + 1));
        banco[*tam].titulo = aloca_e_copia(title);
        banco[*tam].num = number;
        banco[*tam].lido = 0;

        //Pede as novas informações
        printf("\nInsira a data de publicaocao (MM/AAAA): ");
        scanf("%d/%d", &banco[*tam].date.mes, &banco[*tam].date.ano);

        printf("\nQuantos personagens estao na revista? ");
        scanf("%d", &banco[*tam].qtd_per);
        banco[*tam].personagens = malloc(sizeof(char*) * banco[*tam].qtd_per);

        printf("Digite os personagens (um por linha):\n");
        for(j=0; j<banco[*tam].qtd_per; j++){
            scanf(" %[^\n]", personagem);
            banco[*tam].personagens[j] = aloca_e_copia(personagem);
        }

        //Ajusta o tamanho
        (*tam)++;
    }
    //Se já existe...
    else{
        printf("Quadrinho ja existe na base de dados!\n");
    }

    return banco;
}

//remove quadrinho
Comic* remove_quadrinho(Comic* banco, int* tam){
    Comic* novo;
    //Variável achou marcará se o quadrinho foi encontrado na base ou não
    int i,j, ins, number, achou = 0;
    char title[100];

    //Cria um novo vetor de quadrinhos. A lógica que vamos usar é copiar todos os valores do vetor antigo para o novo, menos o quadrinho selecionado para remoção.
    novo = malloc(sizeof(Comic) * (*tam-1));

    //pega as informações
    printf("Digite o titulo do quadrinho a ser removido: ");
    scanf(" %[^\n]s", title);

    printf("Digite o numero do quadirnho a ser removido: ");
    scanf("%d", &number);

    //Procura o quadrinho
    for(i=0, ins=0; i<*tam; i++){
        //Se encontrar, marca na variável achou
        if(banco[i].num == number && strcmp(banco[i].titulo, title) == 0){
            achou = 1;
            free(banco[i].titulo);
            for(j=0; j<banco[i].qtd_per; j++)
                free(banco[i].personagens[j]);
        }
        //Se não for igual, copia para o novo vetor
        else{
            novo[ins].titulo = aloca_e_copia(banco[i].titulo);
            free(banco[i].titulo);

            novo[ins].num = banco[i].num;
            novo[ins].lido = banco[i].lido;
            novo[ins].date = banco[i].date;
            novo[ins].qtd_per = banco[i].qtd_per;
            novo[ins].personagens = malloc(sizeof(char *) * banco[i].qtd_per);

            for(j=0; j<banco[i].qtd_per; j++){
                novo[ins].personagens[j] = aloca_e_copia(banco[i].personagens[j]);
                free(banco[i].personagens[j]);
            }

            ins++;
        }
    }

    //Impressão de mensagem para o usuário
    if(achou == 0)
        printf("Quadrinho nao encontrado na base!\n");
    else
        printf("Remocao realizada com sucesso\n");

    //Libera memória do vetor antigo
    free(banco);
    //Atualiza para o novo tamanho
    *tam = ins;

    return novo;
}

void marcar_leitura(Comic* banco, int tam){
    int i, number, achou = 0;
    char title[1000];
    Comic* quad;

    //Solicita as informações
    printf("Informe o titulo do quadrinho: ");
    scanf(" %[^\n]s", title);

    printf("Informa o numero do quadrinho: ");
    scanf("%d", &number);

    //Busca pelo quadrinho
    quad = recupera_quadrinho(banco, tam, title, number);

    if(quad != NULL){ 
      quad->lido = 1;
      printf("Marcacao feita com sucesso\n\n");
    }
    else printf("Quadrinho nao encontrado na base\n\n");
}

//consulta#########################################################################################################
//consulta_quadrinho
void consulta_quadrinho(Comic* banco, int tam){
    Comic* aux;
    char title[1000];
    int number;

    //Pega as informações
    printf("Informe o titulo do quadrinho: ");
    scanf(" %[^\n]", title);

    printf("Informe o numero do quadrinho: ");
    scanf("%d", &number);

    //Busca o quadrinho
    aux = recupera_quadrinho(banco, tam, title, number);

    //Se não existir, imprime mensagem de erro
    if(aux == NULL){
        printf("Quadrinho nao encontrado na base de dados!\n");
    }
    //Se existir, imprime as informações do quadrinho
    else{
        printf("Informacoes do quadrinho:\n");
        imprime_quadrinho(aux);
    }
}
// filtra_lista
void filtra_lista(Comic* banco, int tam, int param, void* valor){
    //Imprime verificará se algum quadrinho foi impresso
    int i, j, imprime = 0;
    int aux;
    int* vetor;
    char* texto;

    printf("\nLista de quadrinhos:\n");

    //Verifica qual foi o tipo de listagem solicitado
    switch(param){
        //Por ano
        case 1:
            //Converte o valor para inteiro
            aux = *((int*)valor);

            //Procura os quadrinhos que foram lançados naquele ano
            for(i=0; i<tam; i++)
                if(banco[i].date.ano == aux){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }

            break;
        //Por período
        case 2:
            //Converte o valor para um vetor
            vetor = (int*) valor;

            //Verifica os quadrinhos que foram lançados dentro do intervalo solicitado
            for(i=0; i<tam; i++){
                //Ano entre o intervalo
                if(banco[i].date.ano > vetor[1] && banco[i].date.ano < vetor[3]){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }
                //Se o ano é igual ao inicial
                else if(banco[i].date.ano == vetor[1]){
                    //Verifica se o mês é igual ou maior
                    if(banco[i].date.mes >= vetor[0]){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }
                //Se o ano é igual ao final
                else if(banco[i].date.ano == vetor[3]){
                    //Verifica se o mês é menor ou igual
                    if(banco[i].date.mes <= vetor[2]){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }
            }

            break;
        //Por título
        case 3:
            //Converte para string
            texto = (char*)valor;

            for(i=0; i<tam; i++){
                if(strcmp(banco[i].titulo, texto) == 0){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }
            }

            break;
        //Por personagem
        case 4:
            texto = (char*)valor;

            for(i=0; i<tam; i++)
                for(j=0; j<banco[i].qtd_per; j++){
                    if(strcmp(banco[i].personagens[j], texto) == 0){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }

            break;
        //Por status da leitura
        case 5:
            aux = *((int*)valor);

            for(i=0; i<tam; i++)
                if(banco[i].lido == aux){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }

            break;
    }

    //Se não houver nenhuma impressão, avisa que nenhum quadrinho foi encontrado de acordo com os parâmetros solicitados
    if(imprime == 0)
        printf("Nenhum quadrinho encontrado com os parametros de busca!\n\n");
}





