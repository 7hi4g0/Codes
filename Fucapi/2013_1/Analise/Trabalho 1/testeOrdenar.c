#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <sys/time.h>
#include "ordenacao.h"

uint16_t* montarVetor(FILE*, int*);
int linhas(FILE*);
void ajuda(char*);

char *programa;

int main(int argc, char* argv[]) {
	FILE *arquivoTeste;
	char *metodo;
	char *entradaTeste;
	char *saidaTeste;
	funcaoOrdenar ordenar;
	uint16_t *vetor;
	int tamanho;
	struct timeval tempoInicio;
	struct timeval tempoFim;
	double tempoTotal;
	
	programa = argv[0];
	
	if (argc < 3) {
		ajuda("Faltam parâmetros!");
		return 0;
	}
	metodo = argv[1];
	entradaTeste = argv[2];
	
	if (argc >= 4) {
		saidaTeste = argv[3];
	} else {
		saidaTeste = NULL;
	}
	
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
	
	fclose(arquivoTeste);
	
	fprintf(stderr, "Lidos %d números de %s\n", tamanho, entradaTeste);
	
	gettimeofday(&tempoInicio, NULL);
	
	ordenar(vetor, tamanho);
	
	gettimeofday(&tempoFim, NULL);
	
	tempoTotal = (tempoFim.tv_sec - tempoInicio.tv_sec) * 1000.0 + (tempoFim.tv_usec -  tempoInicio.tv_usec) / 1000.0;
	
	fprintf(stderr, "Execução completa!\nTempo total de execução: ");
	
	fprintf(stderr, "%02ld:%02ld:%07.3lf\n", (long) tempoTotal / 60000, ((long) tempoTotal / 1000) % 60, tempoTotal - ((long) tempoTotal - ((long) tempoTotal % 1000)));
	printf("%02ld:%02ld:%07.3lf\n", (long) tempoTotal / 60000, ((long) tempoTotal / 1000) % 60, tempoTotal - ((long) tempoTotal - ((long) tempoTotal % 1000)));
	
	if (saidaTeste != NULL) {
		arquivoTeste = fopen(saidaTeste, "w");
		if (arquivoTeste == NULL) {
			printf("*** Erro ao criar arquivo de saída! ***");
			return 0;
		}
		
		for (int indice = 0; indice < tamanho; indice++) {
			fprintf(arquivoTeste, "%" PRIu16 "\n", vetor[indice]);
		}
		
		fclose(arquivoTeste);
	}
	
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
