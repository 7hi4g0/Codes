#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX	0xFF

int maiorSomatorio(int*, int*, int*, int);
int _maiorSomatorio(int*, int*, int*, int, int, int, int);

int main(void) {
	int vetor1[10];
	int vetor2[10];
	int vetor3[10];
	
	srand(time(NULL));
	
	for (int indice = 0; indice < 10; indice++) {
		vetor1[indice] = rand() % MAX;
		vetor2[indice] = rand() % MAX;
		vetor3[indice] = rand() % MAX;
	}
	
	printf("Maior somatório: %d\n", maiorSomatorio(vetor1, vetor2, vetor3, 10));
	
	return 0;
}

int maiorSomatorio(int *vetor1, int *vetor2, int *vetor3, int tam) {
	return _maiorSomatorio(vetor1, vetor2, vetor3, tam, 0, 0, 0);
}

int _maiorSomatorio(int *vetor1, int *vetor2, int *vetor3, int tam, int soma1, int soma2, int soma3) {
	if (tam == 0) {
		if (soma1 > soma2 && soma1 > soma3) {
			return soma1;
		} else if (soma2 > soma3) {
			return soma2;
		} else {
			return soma3;
		}
	}
	
	return _maiorSomatorio(vetor1 + 1, vetor2 + 1, vetor3 + 1, tam - 1, soma1 + vetor1[0], soma2 + vetor2[0], soma3 + vetor3[0]);
}
