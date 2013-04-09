#include <stdlib.h>
#include <stdio.h>

double somatorio(double*, int);
double _somatorio(double*, int, int, int);

int main(void) {
	double matriz[4][4];
	
	for (int linha = 0; linha < 4; linha++) {
		for (int coluna = 0; coluna < 4; coluna++) {
			 scanf("%lf", &matriz[linha][coluna]);
		}
	}
	
	printf("Somatório: %.2lf\n", somatorio((double *) *matriz, 4));
	
	return 0;
}

double somatorio(double *matriz, int ordem) {
	return _somatorio(matriz, ordem, 0, 0);
}

double _somatorio(double *matriz, int ordem, int linha, int coluna) {
	if (linha == ordem) {
		return 0;
	}
	
	if (coluna == ordem) {
		return _somatorio(matriz, ordem, linha + 1, 0);
	}
	
	return matriz[linha * ordem + coluna] + _somatorio(matriz, ordem, linha, coluna + 1);
}
