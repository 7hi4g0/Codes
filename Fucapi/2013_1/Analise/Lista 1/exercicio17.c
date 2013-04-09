#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int pessoas = 0;
	double maior;
	double menor;
	double altura;
	double mediaMulheres = 0;
	unsigned int quantidadeHomens = 0;
	char sexo;
	
	while (scanf("%lf %c%*c", &altura, &sexo) != EOF) {
		if (pessoas == 0) {
			maior = menor = altura;
		} else if (altura > maior) {
			maior = altura;
		} else if (altura < menor) {
			menor = altura;
		}
		
		if (sexo == 'F') {
			mediaMulheres += altura;
		} else {
			quantidadeHomens++;
		}
		
		pessoas++;
	}
	
	mediaMulheres /= pessoas - quantidadeHomens;
	
	printf("%u pessoas:\n", pessoas);
	printf("Maior altura: %.2lf\n", maior);
	printf("Menor altura: %.2lf\n", menor);
	printf("Média de altura das mulheres: %.2lf\n", mediaMulheres);
	printf("Quantidade de homens: %u\n", quantidadeHomens);
	
	return 0;
}
