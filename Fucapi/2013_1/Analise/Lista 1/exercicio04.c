#include <stdio.h>
#include <stdlib.h>

int main(void) {
	double nota1, nota2, nota3;
	double media;
	
	scanf("%lf %lf %lf", &nota1, &nota2, &nota3);
	
	media = nota1 + 2 * nota2 + 3 * nota3;
	media /= 6;
	
	printf("Média %.2lf\n", media);
	
	return 0;
}
