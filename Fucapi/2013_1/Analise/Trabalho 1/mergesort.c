#include <stdlib.h>
#include "ordenacao.h"

void _mergesort(uint16_t*, int, int);
void merge(uint16_t*, int, int, int);

void mergesort(uint16_t *entrada, int tamanho) {
	_mergesort(entrada, 0, tamanho);
}

void _mergesort(uint16_t *entrada, int inicio, int fim) {
	int meio;
	
	if ((fim - inicio) <= 1) {
		return;
	}
	
	meio = (inicio + fim) / 2;
	
	_mergesort(entrada, inicio, meio);
	_mergesort(entrada, meio, fim);
	merge(entrada, inicio, meio, fim);
}

void merge(uint16_t *entrada, int inicio, int meio, int fim) {
	int posEsq;
	int posDir;
	int tamEsq;
	int tamDir;
	uint16_t *esq;
	uint16_t *dir;
	
	posEsq = 0;
	posDir = 0;
	tamEsq = meio - inicio;
	tamDir = fim - meio;
	
	esq = (uint16_t *) malloc(sizeof(uint16_t) * tamEsq);
	
	for (int indice = 0; indice < tamEsq; indice++) {
		esq[indice] = entrada[indice + inicio];
	}
	
	dir = (uint16_t *) malloc(sizeof(uint16_t) * tamDir);
	
	for (int indice = 0; indice < tamDir; indice++) {
		dir[indice] = entrada[indice + meio];
	}
	
	for (int pos = inicio; pos < fim; pos++) {
		if (posEsq < tamEsq) {
			if (posDir < tamDir && dir[posDir] < esq[posEsq]) {
				entrada[pos] = dir[posDir];
				posDir++;
			} else {
				entrada[pos] = esq[posEsq];
				posEsq++;
			}
		} else {
			entrada[pos] = dir[posDir];
			posDir++;
		}
	}
	
	free(esq);
	free(dir);
}
