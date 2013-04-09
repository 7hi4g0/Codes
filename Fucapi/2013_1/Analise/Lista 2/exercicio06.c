#include <stdlib.h>
#include <stdio.h>

void fibonacci(unsigned int);
void fib(unsigned int, unsigned int, unsigned int);

int main(void) {
	unsigned int num;
	
	scanf("%u", &num);
	
	fibonacci(num);

	return 0;
}

void fibonacci(unsigned int num) {
	fib(0, 1, num);
}

void fib(unsigned int ant, unsigned int atual, unsigned int num) {
	if (num == 0) {
		printf("\n");
		return;
	}
	
	printf("%u ", atual);
	fib(atual, atual + ant, num - 1);
}
