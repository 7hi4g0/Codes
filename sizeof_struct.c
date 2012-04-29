#include <sys/time.h>
#include <stdio.h>

int main() {
	printf("%lu \n", sizeof(struct timeval));
	printf("%lu \n", sizeof(unsigned short));
	printf("%lu \n", sizeof(unsigned int));
	
	return 0;
}
