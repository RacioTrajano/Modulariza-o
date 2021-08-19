#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "definitions.h"

//Cria um vetor de Comics e retorna para a função principal, bem como atualiza a variável tam com a quantidade de quadrinhos na base (tamanho do vetor)
Comic* carregar_Base(int* tam){
    Comic* vetor;
    char linha[1000];
    char* parte;
    char* perso;
    int i, cont;

    i = cont = *tam = 0;

FILE* arquivo= fopen("entrada", "r");
if (arquivo == NULL){
  printf("Erro %s ao abrir o arquivo!\n", strerror(errno));
}
else {}
  

    scanf("%d\n", tam);

    vetor = malloc(sizeof(Comic) * *tam);
        
    for(int i=0; i<*tam; i++){
      fgets(linha, 1000, arquivo);

      //Pega o título
      parte = strtok(linha, "|");
      vetor[i].titulo = aloca_e_copia(parte);

      //Pega o número
      parte = strtok(NULL, "|");
      fscanf(arquivo, "%d", &vetor[i].num);

      //Pega a data
      parte = strtok(NULL, "|");
      fscanf(arquivo, "%d/%d", &vetor[i].date.mes, &vetor[i].date.ano);

fclose(arquivo);

      //Marca não lido
      vetor[i].lido = 0;

      //Pega os personagens. Aqui será usado um strtok no pedaço dos personagens, separando por "," para ir pegando de nome em nome e armazenando no vetor de strings do registro
      parte = strtok(NULL, ";");
      perso = strtok(parte, ",");
      vetor[i].personagens = NULL;

      while(perso != NULL){
        vetor[i].personagens = realloc(vetor[i].personagens, sizeof(char*) * cont + 1);
        vetor[i].personagens[cont] = aloca_e_copia(perso);
        cont++;
        perso = strtok(NULL, ",");
      }

      vetor[i].qtd_per = cont;
      cont=0;
    }
    //Retorna o vetor
    return vetor;
}