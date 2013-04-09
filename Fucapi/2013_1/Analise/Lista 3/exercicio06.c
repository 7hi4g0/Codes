#include <stdlib.h>
#include <stdio.h>

typedef struct _avaliacao{
	float nota;
	int peso;
	struct _avaliacao *prox;
} avaliacao;

avaliacao* novaAvaliacao(float, int);
avaliacao* novaLista(int);
void imprimeLista(avaliacao*);
float mediaSimples(avaliacao*);
float _mediaSimples(avaliacao*, float, int);
float mediaPonderada(avaliacao*);
float _mediaPonderada(avaliacao*, float, int);

int main(void) {
	avaliacao *lista;
	
	lista = novaLista(5);
	
	imprimeLista(lista);
	printf("Média simples: %.2f\n", mediaSimples(lista));
	printf("Média ponderada: %.2f\n", mediaPonderada(lista));
	
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

void imprimeLista(avaliacao *lista) {
	if (lista == NULL) {
		return;
	}
	
	printf("Nota: %.2f\nPeso: %d\n", lista->nota, lista->peso);
	imprimeLista(lista->prox);
}

float mediaSimples(avaliacao *lista) {
	return _mediaSimples(lista, 0, 0);
}

float _mediaSimples(avaliacao *lista, float soma, int notas) {
	if (lista == NULL) {
		return soma / notas;
	}
	
	return _mediaSimples(lista->prox, soma + lista->nota, notas + 1);
}

float mediaPonderada(avaliacao *lista) {
	return _mediaPonderada(lista, 0, 0);
}

float _mediaPonderada(avaliacao *lista, float soma, int pesos) {
	if (lista == NULL) {
		return soma / pesos;
	}
	
	return _mediaPonderada(lista->prox, soma + (lista->nota * lista->peso), pesos + lista->peso);
}
