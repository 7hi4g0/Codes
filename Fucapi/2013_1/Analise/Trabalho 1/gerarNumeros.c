#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

int main(int argc, char* argv[]) {
	FILE *arquivo;
	char *saida;
	int quant;
	
	saida = "numeros";
	quant = 10000;
	
	switch (argc) {
		case 3:
			saida = argv[2];
		case 2:
			quant = atoi(argv[1]);
			break;
	}
	
	arquivo = fopen(saida, "w");
	if (arquivo == NULL) {
		printf("Erro ao criar saida!\n");
		return 0;
	}
	
	srand(time(NULL));
	
	for (int indice = 0; indice < quant; indice++) {
		fprintf(arquivo, "%d\n", rand() % UINT16_MAX);
	}
	
	fclose(arquivo);
	
	return 0;
}
