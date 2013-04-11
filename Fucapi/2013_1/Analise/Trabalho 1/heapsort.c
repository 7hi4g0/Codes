#include <stdlib.h>
#include "ordenacao.h"

void heapify(uint16_t*, int, int);

void heapsort(uint16_t *entrada, int tamanho) {
	for (int pai = (tamanho / 2) - 1; pai >= 0; pai--) {
		heapify(entrada, pai, tamanho);
	}
	
	for (tamanho--; tamanho > 0; tamanho--) {
		uint16_t maior;
		
		maior = entrada[0];
		entrada[0] = entrada[tamanho];
		entrada[tamanho] = maior;
		
		heapify(entrada, 0, tamanho);
	}
}

void heapify(uint16_t *entrada, int pai, int tamanho) {
	uint16_t valorPai;
	int filho;
	
	valorPai = entrada[pai];
	filho = pai * 2 + 1;
	
	while (filho < tamanho) {
		if ((filho + 1 < tamanho) && (entrada[filho + 1] > entrada[filho])) {
			filho++;
		}
		if (entrada[filho] > valorPai) {
			entrada[pai] = entrada[filho];
			pai = filho;
			filho = pai * 2 + 1;
		} else {
			break;
		}
	}
	
	entrada[pai] = valorPai;
}
