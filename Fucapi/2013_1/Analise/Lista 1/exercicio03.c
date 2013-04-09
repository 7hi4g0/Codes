#include <stdlib.h>
#include <stdio.h>

int main(void) {
	unsigned int soma = 0;
	for (int nums = 0; nums < 10; nums++) {
		unsigned int num;
		
		scanf("%u", &num);
		
		soma += num;
	}
	
	printf("Média: %.2f\n", (float) soma / 10);
	
	return 0;
}
