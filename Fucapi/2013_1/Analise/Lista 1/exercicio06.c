#include <stdio.h>
#include <stdlib.h>

void areaPerimetroRetangulo(double, double);

int main(void) {
	areaPerimetroRetangulo(23, 45);
	areaPerimetroRetangulo(23.7, 57.3);
	areaPerimetroRetangulo(2.3, 4.5);
	areaPerimetroRetangulo(78, 31);
	areaPerimetroRetangulo(36, 93);
	areaPerimetroRetangulo(13, 54);
	
	return 0;
}

void areaPerimetroRetangulo(double lado1, double lado2) {
	double perimetro;
	double area;
	
	perimetro = lado1 * 2 + lado2 * 2;
	area = lado1 * lado2;
	
	printf("Perímetro: %.2lf\nÁrea: %.2lf\n", perimetro, area);
}
