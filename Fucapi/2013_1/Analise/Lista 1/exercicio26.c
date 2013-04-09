#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	TAM_MAX	256
#define	DOUBLE_MIN	-500.0
#define	DOUBLE_MAX	500.0

double escalar(double*, double*, unsigned int);

int main(void) {
	double *vetor1;
	double *vetor2;
	unsigned int tamanho;
	
	srand(time(NULL));
	
	tamanho = rand() % TAM_MAX;
	
	vetor1 = (double *) malloc(tamanho * sizeof(double));
	vetor2 = (double *) malloc(tamanho * sizeof(double));
	
	for (unsigned int indice = 0; indice < tamanho; indice++) {
		vetor1[indice] = ((double) rand() / RAND_MAX) * (DOUBLE_MAX - DOUBLE_MIN) + DOUBLE_MIN;
		vetor2[indice] = ((double) rand() / RAND_MAX) * (DOUBLE_MAX - DOUBLE_MIN) + DOUBLE_MIN;
	}
	
	printf("Produto escalar: %.2lf\n", escalar(vetor1, vetor2, tamanho));
	
	free(vetor1);
	free(vetor2);
	
	return 0;
}

double escalar(double *vetor1, double *vetor2, unsigned int tamanho) {
	double produtoEscalar = 0;
	
	for (unsigned int indice = 0; indice < tamanho; indice++) {
		produtoEscalar += vetor1[indice] * vetor2[indice];
	}
	
	return produtoEscalar;
}
