#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int numero;
	double somatorio;
	
	printf("Informe um número inteiro: ");
	scanf("%d", &numero);
	
	somatorio = numero;
	
	for (double denominador = 1; denominador <= 20; denominador++) {
		somatorio += numero / denominador;
		printf("Somatório: %.2lf\n", somatorio);
	}
	
	printf("Somatório: %.2lf\n", somatorio);
	
	return 0;
}
