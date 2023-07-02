#include <stdio.h>
#include <stdlib.h>



/**
Relações entre unidades de medida
pe = 0.3048 m
jarda = 0.9144 m
milha = 1609.34 m
*/

#define TNUN 3

typedef enum {METRO=0,PE,JARDA,MILHA} unidComp_t;

const char abrevUni[][TNUN]={"m","ft","yd","mi"};


typedef struct {
                float valor;        // valor de comprimento
                unidComp_t unidade; // unidade utilizada
                char uni[TNUN];   // abreviatura da unidade
                } medida_t;

#include "confere.h"

/*
Converte o valor da medida x para a unid desejada
x - medida de comprimento
unid - unidade para qual se deseja conversão
retorno da função:
0 - conversão foi realizada
1 - não foi necessario converter
*/
int convUnidComp(medida_t *x, unidComp_t unid);

/*
Exibe na tela valor da medida x, com 2 casas decimais seguida de
espaço e da abreviatura

*/
void exibeUnid(medida_t *x);


int main()
{
medida_t m;
medida_t original;
unidComp_t paraEsta;
int resposta;  // variavel que armazena retorno da função convUnidComp
int analise;
int i;

printf("----Conversor Unidades----\n");

init();

for (i=0;i<5;i++)
{
    sorteiaMedida(&m);   //valor inicial
    paraEsta=sorteiaUnidade(); // para qual unidade converter

    copiaMedida(&original,&m);

  /* Insira aqui:

  Exiba o valor da variavel m usando a funcao ExibeUnid
  Use a função  convUnidComp para converter m para a unidadde paraEsta, atribuindo a resposta o retorno doa função
    Exiba o valor da variavel m usando a funcao ExibeUnid

  */

    exibeUnid(&m);
    resposta = convUnidComp(&m, paraEsta);
    exibeUnid(&m);

    confere(&original,&m,paraEsta,resposta);
    printf("\n");
    }


}

/* Implemente aqui as funções especificadas */
void exibeUnid(medida_t *x){
    printf("%.2f %s\n", x->valor, x->uni);
}



int convUnidComp(medida_t *x, unidComp_t unid){

    float resultado;//em metros


    switch(x->unidade){
    case 0: //metro para metro
        resultado = x->valor;
        break;

    case 1://pe para metro
        resultado = (x->valor*0.3048);
        break;

    case 2://jarda para metro
        resultado = (x->valor*0.9144);
        break;

    case 3://milhas para metro
        resultado = (x->valor*1609.34);
        break;
    }



    switch(unid){
        case 0: //metro para metro;
            x->valor = resultado; //valor em metro é o próprio resultado

        break;

        case 1://metro para pe
            x->valor = (resultado/0.3048);

        break;

        case 2://metro para jarda
            x->valor = (resultado/0.9144);

        break;

        case 3://metro para milhas
            x->valor = (resultado/1609.34);

        break;
    }
    return x->valor;
}




