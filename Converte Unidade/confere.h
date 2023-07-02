#ifndef _CONFERE_H_
#define _CONFERE_H_

void copiaMedida(medida_t *destino,medida_t *origem);

void confere(medida_t *original,medida_t *nova,unidComp_t conversao, int retorno);

void sorteiaMedida(medida_t *x);
unidComp_t sorteiaUnidade(void);

void init(void);
#endif // _CONFERE_H_
