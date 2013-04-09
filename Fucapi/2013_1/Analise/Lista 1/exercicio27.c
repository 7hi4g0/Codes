#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int arrayInteiros[] = {55, 27, 33, 45, 92, 100, 3, 8, 11, 70};
	
	for (unsigned int indice = 1; indice < 10; indice++) {
		while (indice > 0 && arrayInteiros[indice] < arrayInteiros[indice - 1]) {
			int swap = arrayInteiros[indice];
			
			arrayInteiros[indice] = arrayInteiros[indice - 1];
			arrayInteiros[indice - 1] = swap;
			
			indice--;
		}
	}
	
	for (unsigned int indice = 0; indice < 10; indice++) {
		if (indice == 0) {
			printf("[");
		} else {
			printf(", ");
		}
		
		printf("%d", arrayInteiros[indice]);
	}
	
	printf("]\n");
	
	return 0;
}
