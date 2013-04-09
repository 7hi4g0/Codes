#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned int individuos;
	unsigned int maior;
	unsigned int menor;
	double media;
	
	scanf("%u", &individuos);
	
	scanf("%u", &maior);
	
	media = menor = maior;
	
	for (unsigned int individuo = 1; individuo < individuos; individuo++) {
		unsigned int idade;
		
		scanf("%u", &idade);
		
		media += idade;
		
		if (idade > maior) {
			maior = idade;
		} else if (idade < menor) {
			menor = idade;
		}
	}
	
	media /= individuos;
	
	printf("Maior; %u\n", maior);
	printf("Menor; %u\n", menor);
	printf("Media; %.2lf\n", media);
	
	return 0;
}
