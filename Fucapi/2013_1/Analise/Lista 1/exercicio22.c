#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	TAM_MAX	256
#define	MAX	0xFFFF

double media(int*, int);

int main(void) {
	int *array;
	int tamanho;
	
	srand(time(NULL));
	
	tamanho = rand() % TAM_MAX;
	
	array = (int *) malloc(tamanho * sizeof(int));
	
	for (int indice = 0; indice < tamanho; indice++) {
		array[indice] = rand() % MAX;
	}
	
	printf("%.2lf\n", media(array, tamanho));
	
	free(array);

	return 0;
}

double media(int *array, int tamanho) {
	int soma = 0;
	
	for (int indice = 0; indice < tamanho; indice++) {
		soma += array[indice];
	}
	
	return (double) soma / tamanho;
}
