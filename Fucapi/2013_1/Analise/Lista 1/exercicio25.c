#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define	TAM_MAX	256
#define	MAX	0x7FF

bool comparaVetores(bool*, unsigned int, bool*, unsigned int);

int main(void) {
	bool *vetor1;
	bool *vetor2;
	bool iguais;
	unsigned int tamanho1;
	unsigned int tamanho2;
	
	srand(time(NULL));
	
	iguais = rand() % 2;
	
	tamanho1 = rand() % TAM_MAX;
	
	if (iguais) {
		tamanho2 = tamanho1;
	} else {
		tamanho2 = rand() % TAM_MAX;
	}
	
	vetor1 = (bool *) malloc(tamanho1 * sizeof(bool));
	vetor2 = (bool *) malloc(tamanho2 * sizeof(bool));
	
	for (unsigned int indice = 0; indice < tamanho1; indice++) {
		vetor1[indice] = rand() % 2;
		if (iguais) {
			vetor2[indice] = vetor1[indice];
		}
	}
	
	if (!iguais) {
		for (unsigned int indice = 0; indice < tamanho2; indice++) {
			vetor2[indice] = rand() % 2;
		}
	}
	
	if (comparaVetores(vetor1, tamanho1, vetor2, tamanho2)) {
		printf("São idênticos\n");
	} else {
		printf("São diferentes\n");
	}
	
	return 0;
}

bool comparaVetores(bool *vetor1, unsigned int tamanho1, bool *vetor2, unsigned int tamanho2) {
	if (tamanho1 != tamanho2) {
		return false;
	}
	
	for (unsigned int indice = 0; indice < tamanho1; indice++) {
		if (vetor1[indice] != vetor2[indice]) {
			return false;
		}
	}
	
	return true;
}
