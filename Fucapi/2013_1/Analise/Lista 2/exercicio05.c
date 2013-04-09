#include <stdlib.h>
#include <stdio.h>

unsigned int fatorial(unsigned int);

int main(void) {
	unsigned int num;
	
	scanf("%u", &num);
	
	printf("%u! = %u\n", num, fatorial(num));
	
	return 0;
}

unsigned int fatorial(unsigned int num) {
	if (num <= 1) {
		return 1;
	}
	
	return num * fatorial(num - 1);
}
