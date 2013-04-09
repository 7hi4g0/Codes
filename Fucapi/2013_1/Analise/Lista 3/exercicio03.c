#include <stdlib.h>
#include <stdio.h>

typedef struct _avaliacao{
	float nota;
	int peso;
	struct _avaliacao *prox;
} avaliacao;

avaliacao* novaAvaliacao(float, int);
avaliacao* novaLista(int);

int main(void) {
	avaliacao *lista;
	int cont = 0;
	
	lista = novaLista(5);
	
	while (lista != NULL) {
		cont++;
		
		printf("-=%d=-\nNota: %.2f\nPeso: %d\n", cont, lista->nota, lista->peso);
		lista = lista->prox;
	}
	
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

avaliacao* novaLista(int alunos) {
	avaliacao *lista;
	
	lista = NULL;
	
	for (int contador = 0; contador < alunos; contador++) {
		float nota;
		int peso;
		avaliacao *novo;
		
		scanf("%f %d", &nota, &peso);
		
		novo = novaAvaliacao(nota, peso);
		novo->prox = lista;
		
		lista = novo;
	}
	
	return lista;
}
