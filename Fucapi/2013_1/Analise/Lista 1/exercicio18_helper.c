#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
	FILE *pesquisa;
	
	pesquisa = fopen("exercicio18.in", "w");
	
	srand(time(NULL));
	
	for (unsigned int registro = 0; registro < 3000; registro++) {
		char sexo;
		char resposta;
		
		sexo = rand() % 2 ? 'F' : 'M';
		resposta = rand() % 2 ? 'S' : 'N';
		
		fprintf(pesquisa, "%c %c\n", sexo, resposta);
	}
	
	fclose(pesquisa);
	
	return 0;
}
