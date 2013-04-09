#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
	int *array;
	
	srand(time(NULL));
	array = (int *) malloc(10 * sizeof(int));
	
	for (int indice = 0; indice < 10; indice++) {
		array[indice] = rand() + rand();
	}
	
	for (int indice = 0; indice < 10; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%d", array[indice]);
	}
	
	printf("]\n");
	
	return 0;
}
