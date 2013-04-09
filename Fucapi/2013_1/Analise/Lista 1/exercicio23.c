#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX	0x7F

double multiplicatorio(int*, int);

int main(void) {
	int *array;
	
	srand(time(NULL));
	
	array = (int *) malloc(10 * sizeof(int));
	
	for (int indice = 0; indice < 10; indice++) {
		array[indice] = rand() % MAX;
	}
	
	printf("%.2lf\n", multiplicatorio(array, 10));
	
	free(array);
	
	return 0;
}

double multiplicatorio(int *array, int tamanho) {
	double produto = 1;
	
	for (int indice = 0; indice < tamanho; indice++) {
		produto *= array[indice];
	}
	
	return produto;
}
