#ifndef DEF
#define DEF

//Tipo de dado para a data
typedef struct{
    int mes;
    int ano;
} Data;

//Tipo de dado para o quadrinho
typedef struct{
    char* titulo;
    int num;
    Data date;
    int lido;
    char** personagens;
    int qtd_per;
} Comic;

#endif