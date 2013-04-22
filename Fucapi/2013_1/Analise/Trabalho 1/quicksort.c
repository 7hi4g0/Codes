#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"

void _quicksort(uint16_t*, int, int);
int particao(uint16_t*, int, int);
void troca(uint16_t*, int, int);

void quicksort(uint16_t *entrada, int tamanho) {
	srand(time(NULL));
	_quicksort(entrada, 0, tamanho);
}

void _quicksort(uint16_t *entrada, int esq, int dir) {
	int pivo;
	
	if (dir <= esq) {
		return;
	}
	
	pivo = particao(entrada, esq, dir);
	_quicksort(entrada, esq, pivo);
	_quicksort(entrada, pivo + 1, dir);
}

int particao(uint16_t *entrada, int esq, int dir) {
	int pivo;
	
	pivo = rand() % (dir - esq) + esq;
	
	troca(entrada, pivo, esq);
	pivo = esq;
	
	for (int indice = esq + 1; indice < dir; indice++) {
		if (entrada[indice] < entrada[esq]) {
			pivo++;
			troca(entrada, indice, pivo);
		}
	}
	
	troca(entrada, pivo, esq);
	
	return pivo;
}

void troca(uint16_t *entrada, int A, int B) {
	uint16_t tmp;
	
	tmp = entrada[A];
	entrada[A] = entrada[B];
	entrada[B] = tmp;
}
