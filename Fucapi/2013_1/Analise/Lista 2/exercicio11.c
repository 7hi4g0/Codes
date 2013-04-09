#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX	0xFF

int maiorSomatorio(int*, int*, int*, int);
int _maiorSomatorio(int*, int*, int*, int, int, int, int);

int main(void) {
	int matriz1[3][3];
	int matriz2[3][3];
	int matriz3[3][3];
	
	srand(time(NULL));
	
	for (int linha = 0; linha < 3; linha++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			matriz1[linha][coluna] = rand() % MAX;
			matriz2[linha][coluna] = rand() % MAX;
			matriz3[linha][coluna] = rand() % MAX;
		}
	}
	
	printf("Maior somatório: %d\n", maiorSomatorio((int *) *matriz1, (int *) *matriz2, (int *) *matriz3, 3));
	
	return 0;
}

int maiorSomatorio(int *matriz1, int *matriz2, int *matriz3, int tam) {
	return _maiorSomatorio(matriz1, matriz2, matriz3, tam * tam, 0, 0, 0);
}

int _maiorSomatorio(int *matriz1, int *matriz2, int *matriz3, int tam, int soma1, int soma2, int soma3) {
	if (tam == 0) {
		if (soma1 > soma2 && soma1 > soma3) {
			return soma1;
		} else if (soma2 > soma3) {
			return soma2;
		} else {
			return soma3;
		}
	}
	
	return _maiorSomatorio(matriz1 + 1, matriz2 + 1, matriz3 + 1, tam - 1, soma1 + matriz1[0], soma2 + matriz2[0], soma3 + matriz3[0]);
}
