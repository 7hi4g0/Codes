#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char sexo;
	char corOlhos[10];
	char corCabelo[10];
	unsigned int idade;
} registroPessoa;

int main(void) {
	registroPessoa pessoas[15];
	unsigned int maiorIdade = 0;
	double porcentagem = 0;
	
	for (int pessoa = 0; pessoa < 15; pessoa++) {
		scanf("%c %s %s %u\n", &pessoas[pessoa].sexo, pessoas[pessoa].corOlhos, pessoas[pessoa].corCabelo, &pessoas[pessoa].idade);
		printf("%c %s %s %u\n", pessoas[pessoa].sexo, pessoas[pessoa].corOlhos, pessoas[pessoa].corCabelo, pessoas[pessoa].idade);
		
		if (pessoas[pessoa].idade > maiorIdade) {
			maiorIdade = pessoas[pessoa].idade;
		}
		
		if (pessoas[pessoa].sexo == 'F' && pessoas[pessoa].idade >= 18 && pessoas[pessoa].idade <= 35 &&
				strcmp(pessoas[pessoa].corOlhos, "verde") == 0 && strcmp(pessoas[pessoa].corCabelo, "louros") == 0) {
			porcentagem++;
		}
	}
	
	porcentagem /= 15;
	porcentagem *= 100;
	
	printf("Maior idade entre os pesquisados: %u\n", maiorIdade);
	printf("Porcentagem de mulheres com idade entre 18 e 35 anos inclusive e que tenham olhos verdes e cabelos louros: %.2lf%%\n", porcentagem);
	
	return 0;
}
