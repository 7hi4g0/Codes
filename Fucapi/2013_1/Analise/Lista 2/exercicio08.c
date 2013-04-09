#include <stdlib.h>
#include <stdio.h>

void imprimeMatriz(int*, int);
void _imprimeMatriz(int*, int, int, int);

int main(void) {
	int matriz[3][3];
	
	for (int linha = 0; linha < 3; linha ++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			scanf("%d", &matriz[linha][coluna]);
		}
	}
	
	imprimeMatriz((int *) matriz, 3);
	
	return 0;
}

void imprimeMatriz(int *matriz, int ordem) {
	_imprimeMatriz(matriz, ordem, 0, 0);
}

void _imprimeMatriz(int *matriz, int ordem, int linha, int coluna) {
	if (linha == ordem) {
		return;
	}
	
	if (coluna == ordem) {
		printf("\n");
		_imprimeMatriz(matriz, ordem, linha + 1, 0);
		return;
	}
	
	printf("%d ", matriz[linha * ordem + coluna]);
	_imprimeMatriz(matriz, ordem, linha, coluna + 1);
}
