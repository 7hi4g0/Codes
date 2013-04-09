#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int dif = 12 - 7;
	
	printf("2, 7, 12");
	
	for (unsigned int termo = 12, count = 0; count < 5; count++) {
		termo += dif;
		printf(", %d", termo);
	}
	
	printf("\n");
	
	return 0;
}
