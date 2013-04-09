#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * Fórmula: massa = massaInicial / (2 ** (tempo / 50))
 * 			tempo = 50 * log2(massaInicial / massa)
 * 
 * Para tempo em segundo e massas em gramas.
 */

int main(void) {
	double massaInicial;
	double tempo;
	unsigned int horas;
	unsigned int minutos;
	unsigned int segundos;
	
	scanf("%lf", &massaInicial);
	
	tempo =  50 * log2(massaInicial / 0.5);
	
	segundos = (unsigned int) tempo % 60;
	tempo = (tempo - segundos) / 60;
	
	minutos = (unsigned int) tempo % 60;
	tempo = (tempo - minutos) / 60;
	
	horas = (unsigned int) tempo;
	
	printf("Tempo necessário: > %02u:%02u:%02u\n", horas, minutos, segundos);
	
	return 0;
}
