#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	TAM_MAX	256
#define	MAX	0xFF

double media(int*, int);
double _media(int*, int, int);

int main(void) {
	int *array;
	int tam;
	
	srand(time(NULL));
	
	tam = rand() % TAM_MAX + 1;
	
	array = (int *) malloc(tam * sizeof(int));
	
	for (int indice = 0; indice < tam; indice++) {
		array[indice] = rand() % MAX;
	}
	
	printf("%.2lf\n", media(array, tam));
	
	return 0;
}

double media(int *vetor, int tam) {
	return _media(vetor, tam, 0);
}

double _media(int *vetor, int tam, int pos) {
	if (pos == tam - 1) {
		return (double) vetor[pos] / tam;
	}
	
	return (double) vetor[pos] / tam + _media(vetor, tam, pos + 1);
}
