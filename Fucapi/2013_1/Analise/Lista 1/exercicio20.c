#include <stdlib.h>
#include <stdio.h>

int *diasMes = (int []) {
	0,		//	31,
	31,		//	28,
	59,		//	31,
	90,		//	30,
	120,	//	31,
	151,	//	30,
	181,	//	31,
	212,	//	31,
	243,	//	30,
	273,	//	31,
	304,	//	30,
	334		//	31
};

int main(void) {
	int dia1;
	int mes1;
	int ano1;
	int dia2;
	int mes2;
	int ano2;
	
	scanf("%d/%d/%d", &dia1, &mes1, &ano1);
	scanf("%d/%d/%d", &dia2, &mes2, &ano2);
	
	dia1 += diasMes[mes1 - 1] + ano1 * 365 - (ano1 / 4 - ano1 / 100 + ano1 / 400);
	dia2 += diasMes[mes2 - 1] + ano2 * 365 - (ano2 / 4 - ano2 / 100 + ano2 / 400);
	
	if (mes1 > 2 && (ano1 % 400 == 0 || (ano1 % 4 == 0 && ano1 % 100 != 0))) {
		dia1++;
	}
	if (mes2 > 2 && (ano2 % 400 == 0 || (ano2 % 4 == 0 && ano2 % 100 != 0))) {
		dia2++;
	}
	
	printf("%d\n", dia2 - dia1);
	
	return 0;
}
