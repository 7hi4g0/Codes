#include <stdio.h>
#include <stdlib.h>

int* maiorMenor(int, int);
	
int main(void) {
	int *conjunto;
	
	conjunto = maiorMenor(23, 56);
	
	printf("Maior: %d \tMenor: %d\n", conjunto[0], conjunto[1]);
	
	conjunto = maiorMenor(56, 23);
	
	printf("Maior: %d \tMenor: %d\n", conjunto[0], conjunto[1]);
	
	conjunto = maiorMenor(1, 0);
	
	printf("Maior: %d \tMenor: %d\n", conjunto[0], conjunto[1]);
	
	conjunto = maiorMenor(-1, 97);
	
	printf("Maior: %d \tMenor: %d\n", conjunto[0], conjunto[1]);
	
	conjunto = maiorMenor(-56, -34);
	
	printf("Maior: %d \tMenor: %d\n", conjunto[0], conjunto[1]);
	
	return 0;
}

int* maiorMenor(int num1, int num2) {
	int *maiorMenor;
	
	maiorMenor = (int*) malloc(2 * sizeof(int));
	
	if (num1 > num2) {
		maiorMenor[0] = num1;
		maiorMenor[1] = num2;
	} else {
		maiorMenor[0] = num2;
		maiorMenor[1] = num1;
	}
	
	return maiorMenor;
}
