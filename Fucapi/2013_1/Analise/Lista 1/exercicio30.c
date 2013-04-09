#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int valor;
	int repeticoes;
} frequencia;

int main(void) {
	int vetor[10];
	int maisFrequente;
	int maiorFrequencia = 0;
	frequencia frequencias[10];
	
	for (int indice = 0; indice < 10; indice++) {
		scanf("%d", &vetor[indice]);
		frequencias[indice].valor = 0;
		frequencias[indice].repeticoes = 0;
	}
	
	for (int indice = 0; indice < 10; indice++) {
		int pos = 0;
		
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%d", vetor[indice]);
		
		while (pos < 10 && frequencias[pos].valor != vetor[indice] && frequencias[pos].repeticoes != 0) {
			pos++;
		}
		
		frequencias[pos].valor = vetor[indice];
		frequencias[pos].repeticoes++;
		
		if (frequencias[pos].repeticoes > maiorFrequencia) {
			maiorFrequencia = frequencias[pos].repeticoes;
			maisFrequente = vetor[indice];
		}
	}
	
	printf("]\n");
	printf("Mais frequente: %d\n", maisFrequente);
	
	return 0;
}
