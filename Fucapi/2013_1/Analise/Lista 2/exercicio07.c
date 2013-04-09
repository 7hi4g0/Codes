#include <stdlib.h>
#include <stdio.h>

int tempo(double);

int main(void) {
	double massa;
	int horas;
	int minutos;
	int segundos;
	
	scanf("%lf", &massa);
	
	segundos = tempo(massa);
	
	minutos = segundos / 60;
	segundos %= 60;
	
	horas = minutos / 60;
	minutos %= 60;
	
	printf("%02d:%02d:%02d\n", horas, minutos, segundos);
	
	return 0;
}

int tempo(double massa) {
	if (massa <= 0.5) {
		return 0;
	}
	
	return 50 + tempo(massa / 2);
}
