#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool estaContido(int*, unsigned int, int*, unsigned int);

int main(void) {
	int vetor1[10];
	int vetor2[5];
	
	for (unsigned int indice = 0; indice < 10; indice++) {
		scanf("%d", &vetor1[indice]);
	}
	
	for (unsigned int indice = 0; indice < 10; indice++) {
		scanf("%d", &vetor2[indice]);
	}
	
	printf("Está contido: %s\n", estaContido(vetor1, 10, vetor2, 5) ? "Sim" : "Não");
	
	return 0;
}

bool estaContido(int *vetor1, unsigned int tamanho1, int *vetor2, unsigned int tamanho2) {
	for (unsigned int indice1 = 0; indice1 < tamanho1 - tamanho2; indice1++) {
		unsigned int indice2;

		for (indice2 = 0; indice2 < tamanho2; indice2++) {
			if (vetor2[indice2] != vetor1[indice1 + indice2]) {
				break;
			}
		}
		
		if (indice2 == tamanho2) {
			return true;
		}
	}
	
	return false;
}
