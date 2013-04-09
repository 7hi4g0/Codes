#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int avaliacoes;
	double media = 0;
	int totalPesos = 0;
	
	printf("Informe o número de avaliações: ");
	scanf("%d", &avaliacoes);
	
	for (int avaliacao = 0; avaliacao < avaliacoes; avaliacao++) {
		int peso;
		double nota;
		
		printf("Informe a nota %d e o peso: ", avaliacao + 1);
		scanf("%lf %d", &nota, &peso);
		
		totalPesos += peso;
		media += nota * peso;
	}
	
	media /= totalPesos;
	
	printf("Média: %lf\n", media);
	
	return 0;
}

