#include <stdlib.h>
#include <stdio.h>

typedef struct _avaliacao{
	float nota;
	int peso;
	struct _avaliacao *prox;
} avaliacao;

avaliacao* novaAvaliacao(float, int);

int main(void) {
	avaliacao *aluno;
	
	aluno = novaAvaliacao(5.5, 5);
	
	printf("Nota: %.2f\nPeso: %d\n", aluno->nota, aluno->peso);
	
	return 0;
}

avaliacao* novaAvaliacao(float nota, int peso) {
	avaliacao *aluno;
	
	aluno = (avaliacao *) malloc(sizeof(avaliacao));
	
	aluno->nota = nota;
	aluno->peso = peso;
	aluno->prox = NULL;
	
	return aluno;
}

