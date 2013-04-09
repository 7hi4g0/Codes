#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int ordem;
	int *A;
	int *B;
	int *C;
	
	scanf("%u", &ordem);
	
	A = (int *) malloc(ordem * ordem * sizeof(int));
	B = (int *) malloc(ordem * ordem * sizeof(int));
	C = (int *) malloc(ordem * ordem * sizeof(int));
	
	for (unsigned int linha = 0; linha < ordem; linha++) {
		for (unsigned int coluna = 0; coluna < ordem; coluna++) {
			scanf("%d", &A[linha * ordem + coluna]);
		}
	}
	
	for (unsigned int linha = 0; linha < ordem; linha++) {
		for (unsigned int coluna = 0; coluna < ordem; coluna++) {
			scanf("%d", &B[linha * ordem + coluna]);
			
			C[linha * ordem + coluna] =	A[linha * ordem + coluna] + B[linha * ordem + coluna];
		}
	}
	
	for (unsigned int linha = 0; linha < ordem; linha++) {
		for (unsigned int coluna = 0; coluna < ordem; coluna++) {
			printf("%d\t", A[linha * ordem + coluna]);
		}
		
		printf("\t");
		
		for (unsigned int coluna = 0; coluna < ordem; coluna++) {
			printf("%d\t", B[linha * ordem + coluna]);
		}
		
		for (unsigned int coluna = 0; coluna < ordem; coluna++) {
			printf("\t%d", C[linha * ordem + coluna]);
		}
		
		printf("\n");
	}
	
	return 0;
}
