#include <stdlib.h>
#include <stdio.h>

int main(void ) {
	int matriz[4][4];
	int transposta[4][4];
	
	for (int linha = 0; linha < 4; linha++) {
		for (int coluna = 0; coluna < 4; coluna++) {
			scanf("%d", &matriz[linha][coluna]);
			transposta[coluna][linha] = matriz[linha][coluna];
		}
	}
	
	for (int linha = 0; linha < 4; linha++) {
		for (int coluna = 0; coluna < 4; coluna++) {
			printf("%d\t", matriz[linha][coluna]);
		}
		
		for (int coluna = 0; coluna < 4; coluna++) {
			printf("\t%d", transposta[linha][coluna]);
		}
		
		printf("\n");
	}
	
	return 0;
}
