#include <stdlib.h>
#include <stdio.h>
#include <float.h>

int main(void) {
	unsigned int num;
	double maior = DBL_MIN;
	double menor = DBL_MAX;
	double diferenca;
	double soma = 0;
	double media;
	
	scanf("%u", &num);
	
	for (unsigned int indice = 0; indice < num; indice++) {
		double valor;
		
		scanf("%lf", &valor);
		
		if (valor > maior) {
			maior = valor;
		} else if (valor < menor) {
			menor = valor;
		}
		
		soma += valor;
	}
	
	diferenca = maior - menor;
	media = soma / num;
	
	printf("Maior: %.2lf\tMenor: %.2lf\t Diferença: %.2lf\n", maior, menor, diferenca);
	printf("Soma; %.2lf\tMédia: %.2lf\n", soma, media);
	
	return 0;
}
