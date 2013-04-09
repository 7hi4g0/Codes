#include <stdlib.h>
#include <stdio.h>

void inverte(double*, int);

int main(void) {
	double vetor[10];
	
	for (int indice = 0; indice < 10; indice++) {
		scanf("%lf", &vetor[indice]);
	}
	
	inverte(vetor, 10);
	
	for (int indice = 0; indice < 10; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%.2lf", vetor[indice]);
	}
	
	printf("]\n");
	
	return 0;
}

void inverte(double *vetor, int tam) {
	int metade = tam / 2;
	
	for (int indice = 0; indice < metade; indice++) {
		double swap;
		
		swap = vetor[indice];
		vetor[indice] = vetor[tam - indice - 1];
		vetor[tam - indice - 1] = swap;
	}
}
