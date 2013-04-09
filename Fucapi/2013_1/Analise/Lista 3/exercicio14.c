#include <stdlib.h>
#include <stdio.h>

//#define	ponderado
#define	notaProcurar	4.5
#define	notaAlterar	9.5
#define	pesoAlterar	3

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
float maiorNotaPonderada(avaliacao*);
float menorNotaPonderada(avaliacao*);
float somatorio(avaliacao*);
float maiorSomatorio(avaliacao*, avaliacao*);
float menorSomatorio(avaliacao*, avaliacao*);
int maior(avaliacao*, avaliacao*);
int peso(avaliacao*, float);
int novoPeso(avaliacao*, float, int);

int main(void) {
	avaliacao *lista;
	avaliacao *lista2;
	
	lista = novaLista(5);
	lista2 = novaLista(5);
	
	imprimeLista(lista);
	printf("Média simples: %.2f\n", mediaSimples(lista));
	printf("Média ponderada: %.2f\n", mediaPonderada(lista));
	printf("Maior nota ponderada: %.2f\n", maiorNotaPonderada(lista));
	printf("Menor nota ponderada: %.2f\n", menorNotaPonderada(lista));
	printf("Somatório: %.2f\n", somatorio(lista));
	printf("Maior somatório: %.2f\n", maiorSomatorio(lista, lista2));
	printf("Menor somatório: %.2f\n", menorSomatorio(lista, lista2));
	printf("Maior: %s\n", maior(lista, lista2) ? "sim" : "não");
	printf("Peso de %.2f: %d\n", notaProcurar, peso(lista, notaProcurar));
	printf("Alterou peso da nota %.2f para %d: %s\n", notaAlterar, pesoAlterar, novoPeso(lista, notaAlterar, pesoAlterar) ? "Sim" : "Não");
	
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

float maiorNotaPonderada(avaliacao *lista) {
	float notaPonderadaAtual;
	float notaPonderadaRecursao;
	
	if (lista == NULL) {
		return 0;
	}
	
	notaPonderadaAtual = lista->nota * lista->peso;
	notaPonderadaRecursao = maiorNotaPonderada(lista->prox);
	
	if (lista->prox == NULL) {
		return notaPonderadaAtual;
	}
	
	return notaPonderadaAtual > notaPonderadaRecursao ? notaPonderadaAtual : notaPonderadaRecursao;
}

float menorNotaPonderada(avaliacao *lista) {
	float notaPonderadaAtual;
	float notaPonderadaRecursao;
	
	if (lista == NULL) {
		return 0;
	}
	
	notaPonderadaAtual = lista->nota * lista->peso;
	notaPonderadaRecursao = menorNotaPonderada(lista->prox);
	
	if (lista->prox == NULL) {
		return notaPonderadaAtual;
	}

	return notaPonderadaAtual < notaPonderadaRecursao ? notaPonderadaAtual : notaPonderadaRecursao;
}

/* Somatório não estś bem definido.
 * Deve ser a soma das notas simplesmente ou das notas ponderadas?
 */
float somatorio(avaliacao *lista) {
	if (lista == NULL) {
		return 0;
	}
	
#ifdef ponderado
	return lista->nota * lista->peso + somatorio(lista->prox);
#else
	return lista->nota + somatorio(lista->prox);
#endif
}

float maiorSomatorio(avaliacao *lista1, avaliacao *lista2) {
	float somatorio1;
	float somatorio2;
	
	somatorio1 = somatorio(lista1);
	somatorio2 = somatorio(lista2);
	
	return somatorio1 > somatorio2 ? somatorio1 : somatorio2;
}

float menorSomatorio(avaliacao *lista1, avaliacao *lista2) {
	float somatorio1;
	float somatorio2;
	
	somatorio1 = somatorio(lista1);
	somatorio2 = somatorio(lista2);
	
	return somatorio1 < somatorio2 ? somatorio1 : somatorio2;
}

int maior(avaliacao *lista1, avaliacao *lista2) {
	avaliacao *lista;
	
	while (lista1 != NULL) {
		lista = lista2;
		
		while (lista != NULL) {
			if (lista1->nota <= lista->nota) {
				return 0;
			}
			
			lista = lista->prox;
		}
		
		lista1 = lista1->prox;
	}
	
	return 1;
}

int peso(avaliacao *lista, float nota) {
	while (lista != NULL) {
		if (lista->nota == nota) {
			return lista->peso;
		}
		
		lista = lista->prox;
	}
	
	return 0;
}

int novoPeso(avaliacao *lista, float nota, int peso) {
	while (lista != NULL) {
		if (lista->nota == nota) {
			lista->peso = peso;
			return 1;
		}
		
		lista = lista->prox;
	}
	
	return 0;
}
