#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX	0xFFF

int somatorio(int*, int);

int main(void) {
	int vetor[10];
	
	srand(time(NULL));
	
	for (int indice = 0; indice < 10; indice++) {
		vetor[indice] = rand() % MAX;
	}
	
	printf("Somatório: %d\n", somatorio(vetor, 10));
	
	return 0;
}

int somatorio(int *vetor, int tam) {
	if (tam == 1) {
		return vetor[0];
	}
	
	return vetor[0] + somatorio(vetor + 1, tam - 1);
}
