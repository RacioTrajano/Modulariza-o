#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "arquivo.h"
#include "aplicativos.h"
// MARVEL UNLIMITED - C EDITION











//Função principal
int main(){
    //Vetor de quadrinhos que conterá uma copia da base de dados em operação no programa. Inicializado com o valor nulo.
    Comic* quadrinhos = NULL;
    //qtd armazenará a quantidade de quadrinhos existentes na base, op lerá qual a operação digitada pelo usuário no menu
    //subop será usada quando precisar de uma opção do submenu
    int qtd, op, subop;

    //Variáveis auxiliares para armazenar leituras da entrada
    int ano;
    int periodo[4];
    char title[1000];

    quadrinhos = carregar_Base(&qtd);

    if(quadrinhos != NULL)
      printf("Base carregada com sucesso!\n\n");
    else{
      printf("Erro ao carregar\n");
      return -1;
    }

    //Laço principal do programa
    do{
        //Imprime o menu do programa
        imprime_Menu();

        scanf("%d", &op);

        //Verifica a escolha no menu
        switch(op){
           //Adiciona um quadrinho
            case 1: quadrinhos = adiciona_quadrinho(quadrinhos, &qtd); break;
            //Remove o quadrinho
            case 2: quadrinhos = remove_quadrinho(quadrinhos, &qtd); break;
            //Pega as informações de um quadrinho
            case 3: consulta_quadrinho(quadrinhos, qtd); break;
            //Abre os menus para consultas gerais
            case 4:
                //Imprime o menu de subconsultas
                imprime_Consultas();

                scanf("%d", &subop);

                //Verifica a opção de consulta escolhida
                switch(subop){
                    //Listar por ano
                    case 1:
                        printf("Digite o ano desejado: ");
                        scanf("%d", &ano);
                        filtra_lista(quadrinhos, qtd, 1, &ano);
                        break;
                    //Lista por periodo
                    case 2:
                        printf("Digite o intervalo desejado (formato MM/AAAA - MM/AAAA): ");
                        scanf("%d/%d - %d/%d", &periodo[0], &periodo[1], &periodo[2], &periodo[3]);
                        filtra_lista(quadrinhos, qtd, 2, periodo);
                        break;
                    //Lista por titulos dos quadrinhos
                    case 3:
                        printf("Digite o titulo da serie de quadrinhos desejado: ");
                        scanf(" %[^\n]s", title);
                        filtra_lista(quadrinhos, qtd, 3, title);
                        break;
                    //Lista quadrinhos que possuem determinado personagem
                    case 4:
                        printf("Digite o nome do personagem: ");
                        scanf(" %[^\n]s", title);
                        filtra_lista(quadrinhos, qtd, 4, title);
                        break;
                    //Lista os quadrinhos que já foram lidos
                    case 5:
                        ano = 1;
                        filtra_lista(quadrinhos, qtd, 5, &ano);
                        break;
                    default: printf("Opcao invalida!\n");
                }
                break;
            //Marca um quadrinho como lido
            case 5: marcar_leitura(quadrinhos, qtd); break;
            //Se for sair, não precisa fazer nada
            case 6: break;
            //Se for digitada outra coisa
            default:
                printf("Opcao Invalida!\n\n");
                getchar(); getchar();
        }
    }while(op != 6);

    //Ao encerrar o programa, salva a versão mais atual da base

    if(quadrinhos != NULL)
        free(quadrinhos);

    return 0;
}






