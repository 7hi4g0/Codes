#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int sim = 0;
	unsigned int nao = 0;
	unsigned int homem = 0;
	unsigned int mulher = 0;
	double simMulher = 0;
	double naoHomem = 0;
	
	for (unsigned int pessoa = 0; pessoa < 3000; pessoa++) {
		char sexo;
		char resposta;
		
		scanf("%c %c%*c", &sexo, &resposta);
		
		if (resposta == 'S') {
			sim++;
		} else {
			nao++;
		}
		
		if (sexo == 'M') {
			homem++;
			
			if (resposta == 'N') {
				naoHomem++;
			}
		} else {
			mulher++;
			
			if ( resposta == 'S') {
				simMulher++;
			}
		}
	}
	
	simMulher *= 100.0 / mulher;
	naoHomem *= 100.0 / homem;
	
	printf("Responderam SIM: %d\n", sim);
	printf("Responderam NÃO: %d\n", nao);
	printf("Porcentagem de pessoas do sexo feminino que responderam SIM: %.2lf\n", simMulher);
	printf("Porcentagem de pessoas do sexo masculino que responderam NÃO: %.2lf\n", naoHomem);
	
	return 0;
}
