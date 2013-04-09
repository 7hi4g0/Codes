#include <stdlib.h>
#include <stdio.h>

int main(void) {
	double alturas[20];
	double maior;
	unsigned short int mocas = 1;
	
	for (int moca = 0; moca < 20; moca++) {
		scanf("%lf", &alturas[moca]);
		
		if (moca == 0) {
			maior = alturas[moca];
		} else if (alturas[moca] == maior) {
			mocas++;
		} else if (alturas[moca] > maior) {
			maior = alturas[moca];
			mocas = 1;
		}
	}
	
	printf("Maior altura: %.2lf\n", maior);
	printf("Quantidade de moças com a maior altura: %u\n", mocas);
	
	return 0;
}
