#include <stdlib.h>
#include <stdio.h>

double media(double*,int);
double _media(double*,int,int,int);

int main(void) {
	double matriz[5][5];
	
	for (int linha = 0; linha < 5; linha++) {
		for (int coluna = 0; coluna < 5; coluna++) {
			scanf("%lf", &matriz[linha][coluna]);
		}
	}
	
	printf("Média: %.2lf\n", media((double *) *matriz, 5));
	
	return 0;
}

double media(double *matriz, int ordem) {
	return _media(matriz, ordem, 0, 0);
}

double _media(double *matriz, int ordem, int linha, int coluna) {
	if (linha == ordem) {
		return 0;
	}
	
	if (coluna == ordem) {
		return _media(matriz, ordem, linha + 1, 0);
	}
	
	return matriz[linha * ordem + coluna] / (ordem * ordem) + _media(matriz, ordem, linha, coluna + 1);
}
