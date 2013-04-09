#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	TAM_MAX	0xFFFF
#define	MAX	500.0
#define	MIN	-500.0

int main(void) {
	unsigned int tam;
	FILE *valores;
	
	valores = fopen("exercicio33.in", "w");
	
	srand(time(NULL));
	
	tam = rand() % TAM_MAX + 1;
	fprintf(valores, "%u\n", tam);
	
	for (unsigned int indice = 0; indice < tam; indice++) {
		fprintf(valores, "%lf\n", ((double) rand() / RAND_MAX) * (MAX - MIN) + MIN);
	}
	
	fclose(valores);
	
	return 0;
}
