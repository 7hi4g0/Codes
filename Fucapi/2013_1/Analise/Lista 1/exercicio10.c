#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int numero;
	unsigned int fatorial = 1;
	
	scanf("%u", &numero);
	
	for (unsigned int fator = numero; fator > 0; fator--) {
		fatorial *= fator;
	}
	
	printf("%u! = %u\n", numero, fatorial);
	
	return 0;
}
