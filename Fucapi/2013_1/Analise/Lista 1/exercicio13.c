#include <stdlib.h>
#include <stdio.h>

void fibonacci(unsigned int);

int main(void) {
	fibonacci(15);
	
	return 0;
}

void fibonacci(unsigned int termos) {
	unsigned int ant = 0;
	unsigned int atual = 1;
	
	for (unsigned int termo = 0; termo < termos; termo++) {
		unsigned int aux;
		
		if (termo != 0) {
			printf(", ");
		}
		
		printf("%d", atual);
		
		aux = atual;
		atual = atual + ant;
		ant = aux;
	}
	
	printf("\n");
}
