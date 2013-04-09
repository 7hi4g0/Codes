#include <stdlib.h>
#include <stdio.h>

double media(double*, int*, int);
double _media(double*, int*, int, double, int);

int main(void) {
	double notas[5];
	int pesos[5];
	
	for (int indice = 0; indice < 5; indice++) {
		scanf("%lf", &notas[indice]);
	}
	
	for (int indice = 0; indice < 5; indice++) {
		scanf("%d", &pesos[indice]);
	}
	
	printf("Média: %.2lf\n", media(notas, pesos, 5));
	
	return 0;
}

double media(double *notas, int *pesos, int tam) {
	return _media(notas, pesos, tam, 0, 0);
}

double _media(double *notas, int *pesos, int tam, double soma, int somaPesos) {
	if (tam == 1) {
		return (soma + notas[0] * pesos[0]) / (somaPesos + pesos[0]);
	}
	
	return _media(notas + 1, pesos + 1, tam - 1, soma + notas[0] * pesos[0], somaPesos + pesos[0]);
}
