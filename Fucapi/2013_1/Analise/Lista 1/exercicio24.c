#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX	0x7F

void imprimeArray(int*, int);
int* inverteArray(int*, int);

int main(void) {
	int *array1;
	int *array2;
	
	srand(time(NULL));
	
	array1 = (int *) malloc(10 * sizeof(int));
	
	for (int indice = 0; indice < 10; indice++) {
		array1[indice] = rand() % MAX;
	}
	
	array2 = inverteArray(array1, 10);
	imprimeArray(array1, 10); printf("\n");
	imprimeArray(array2, 10); printf("\n");
	
	free(array1);
	free(array2);
	
	return 0;
}

void imprimeArray(int *array, int tamanho) {
	for (int indice = 0; indice < tamanho; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");	
		}
		
		printf("%d", array[indice]);
	}
	
	printf("]");
}

int* inverteArray(int *array, int tamanho) {
	int *novo;
	
	novo = (int *) malloc(tamanho * sizeof(int));
	
	for (int indice = 0; indice < tamanho; indice++) {
		novo[tamanho - indice - 1] = array[indice];
	}
	
	return novo;
}
