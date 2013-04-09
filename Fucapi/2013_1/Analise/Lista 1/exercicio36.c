#include <stdlib.h>
#include <stdio.h>

int main(void) {
	double num;
	double matriz[3][3];
	
	scanf("%lf", &num);
	
	for (int linha = 0; linha < 3; linha++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			scanf("%lf", &matriz[linha][coluna]);
		}
	}
	
	for (int linha = 0; linha < 3; linha++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			matriz[linha][coluna] *= num;
			printf("%.2lf\t", matriz[linha][coluna]);
		}
		
		printf("\n");
	}
	
	return 0;
}
