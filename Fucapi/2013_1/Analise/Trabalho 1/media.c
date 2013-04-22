#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	int num;
	double tempos[5];
	
	while (scanf("numeros1000e%d%*c", &num) != EOF) {
		char linha[500];
		int quant;
		
		printf("1000");
		for (int i = 0; i < num; i++) {
			printf("0");
		}
		printf(" números\n");
		num--;
		
		tempos[num] = 0;
		
		for (gets(linha); strcmp(linha, "-----------------------") != 0; gets(linha)) {
			int minutos;
			int segundos;
			double milisegundos;
			
			sscanf(linha, "%d.:", &quant);
			scanf("%d:%d:%lf%*c", &minutos, &segundos, &milisegundos);
			
			milisegundos += minutos * 60000 + segundos * 1000;
			tempos[num] *= (quant - 1.) / quant;
			tempos[num] += milisegundos / quant;
		}
		
		printf("%02d:%02d:%07.3lf\n", (int) tempos[num] / 60000, ((int) tempos[num] / 1000) % 60, tempos[num] - ((long) tempos[num] - ((long) tempos[num] % 1000)));
		printf(linha);
		printf("\n");
	}
	
	return 0;
}
