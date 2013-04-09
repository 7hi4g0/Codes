#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "ordenacao.h"

uint16_t* montarVetor(FILE*, int*);
int linhas(FILE*);
void ajuda(char*);

char *programa;

int main(int argc, char* argv[]) {
	FILE *arquivoTeste;
	char *entradaTeste;
	char *metodo;
	void (*ordenar)(uint16_t*);
	uint16_t *vetor;
	int tamanho;
	time_t tempoInicio;
	time_t tempoFim;
	
	programa = argv[0];
	
	if (argc < 3) {
		ajuda("Faltam parâmetros!");
		return 0;
	}
	metodo = argv[1];
	entradaTeste = argv[2];
	
	if (strcmp(metodo, "heap") == 0) {
		ordenar = heapsort;
	} else if (strcmp(metodo, "merge") == 0) {
		ordenar = mergesort;
	} else if (strcmp(metodo, "quick") == 0) {
		ordenar = quicksort;
	} else {
		ajuda("Método de ordenação inválido!");
		return 0;
	}
	
	arquivoTeste = fopen(entradaTeste, "r");
	if (arquivoTeste == NULL) {
		printf("*** Arquivo inexistente! ***\n");
		return 0;
	}
	vetor = montarVetor(arquivoTeste, &tamanho);
	
	printf("Lidos %d números de %s\n", tamanho, entradaTeste);
	
	tempoInicio = time(NULL);
	
	ordenar(vetor);
	
	tempoFim = time(NULL);
	
	return 0;
}

uint16_t* montarVetor(FILE *arquivo, int *tamanho) {
	uint16_t *vetor;
	uint16_t valor;
	
	*tamanho = linhas(arquivo);
	
	vetor = (uint16_t *) malloc(sizeof(uint16_t) * (*tamanho));
	
	for (int indice = 0; fscanf(arquivo, "%" SCNu16 "%*c", &valor) != EOF; indice++) {
		vetor[indice] = valor;
	}
	
	return vetor;
}

int linhas(FILE *arquivo) {
	char c;
	int linhas = 0;
	
	fseek(arquivo, 0, SEEK_SET);
	
	while ((c = fgetc(arquivo)) != EOF) {
		if (c == '\n') {
			linhas++;
		}
	}
	
	fseek(arquivo, 0, SEEK_SET);
	
	return linhas;
}

void ajuda(char *mensagem) {
	if (mensagem != NULL) {
		printf("*** %s ***\n", mensagem);
	}
	printf("Uso:\n\t%s METODO ARQUIVO\n\n", programa);
	printf("\tMETODO: \t{heap|merge|quick}\n");
	printf("\tARQUIVO:\tArquivo com números entre 0 e 65535 para serem ordenados.\n");
}
