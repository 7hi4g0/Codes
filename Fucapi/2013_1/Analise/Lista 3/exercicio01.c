#include <stdlib.h>
#include <stdio.h>

typedef struct _avaliacao{
	float nota;
	int peso;
	struct _avaliacao *prox;
} avaliacao;

int main(void) {
	avaliacao aluno;
	
	aluno.nota = 5.5;
	aluno.peso = 5;
	aluno.prox = NULL;
	
	printf("Nota: %.2f\nPeso: %d\n", aluno.nota, aluno.peso);
	
	return 0;
}
