#include <stdlib.h>
#include <stdio.h>

#define	Tamanho	5

int main(void) {
	int A[] = {1, 2, 3, 4, 5};
	int B[] = {5, 4, 3, 2, 1};
	int C[Tamanho];
	
	for (int indice = 0; indice < Tamanho; indice++) {
		C[indice] = A[indice] + B[indice];
		printf("%d ", C[indice]);
	}
	
	printf("\n");
	
	return 0;
}
