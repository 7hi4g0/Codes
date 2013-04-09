#include <stdlib.h>
#include <stdio.h>

int main (void) {
	int lados;
	double perimetro = 0;
	
	printf("Informe a quantidade de lados: ");
	scanf("%d", &lados);
	
	printf("Informe as medidas dos %d lados:\n", lados);
	
	for (int lado = 0; lado < lados; lado++) {
		double medidaLado;
		
		scanf("%lf", &medidaLado);
		
		perimetro += medidaLado;
	}
	
	printf("Peŕmetro; %.2lf\n", perimetro);
	
	return 0;
}
