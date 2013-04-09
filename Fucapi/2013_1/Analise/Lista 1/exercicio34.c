#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define	TAM_MAX	32
#define	MAX	0xFF

int* ordena(int*, unsigned int);

int main(void) {
	int *vetor;
	int *ordenado;
	unsigned int tam;
	
	srand(time(NULL));
	
	tam = rand() % TAM_MAX + 1;
	
	vetor = (int *) malloc(tam * sizeof(int));
	
	for (unsigned int indice = 0; indice < tam; indice++) {
		vetor[indice] = rand() % MAX;
	}
	
	ordenado = ordena(vetor, tam);
	
	for (unsigned int indice = 0; indice < tam; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%d", vetor[indice]);
	}
	
	printf("]\n");
	
	for (unsigned int indice = 0; indice < tam; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%d", ordenado[indice]);
	}
	
	printf("]\n");
	
	free(vetor);
	free(ordenado);
	
	return 0;
}

int* ordena(int *vetor, unsigned int tam) {
	int *ordenado;
	bool *ok;
	
	ordenado = (int *) malloc(tam * sizeof(int));
	ok = (bool *) malloc(tam * sizeof(bool));
	
	for (unsigned int indice = 0; indice < tam; indice++) {
		ok[indice] = true;
	}
	
	for (unsigned int ultimo = tam; ultimo > 0;) {
		unsigned int maior;
		int maiorValor;
		
		ultimo--;
		
		maior = tam;
		
		for (unsigned int indice = 0; indice < tam; indice++) {
			if (ok[indice]) {
				if (maior == tam) {
					maiorValor = vetor[indice];
					maior = indice;
				} else if (vetor[indice] > maiorValor) {
					maiorValor = vetor[indice];
					maior = indice;
				}
			}
		}
		
		ok[maior] = false;
		ordenado[ultimo] = maiorValor;
		
		printf("%d\n", maiorValor);
	}
	
	return ordenado;
}
