#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isLadosTriangulo(float A, float B, float C);
void tipoTriangulo(float A, float B, float C);

int main(void) {
	tipoTriangulo(3.4, 40.5, 40.5);
	tipoTriangulo(23, 23, 23);
	tipoTriangulo(54.65, 947.2, 40.5);
	tipoTriangulo(67.2, 53.2, 43.7);
	tipoTriangulo(12, 23, 12);
	tipoTriangulo(37, 40.5, 5.5);
	
	return 0;
}

bool isLadosTriangulo(float A, float B, float C) {
	if (A + B <= C) {
		return false;
	}
	
	if (A + C <= B) {
		return false;
	}
	
	if (B + C <= A) {
		return false;
	}
	
	return true;
}

void tipoTriangulo(float A, float B, float C) {
	if (isLadosTriangulo(A, B, C)) {
		if (A == B && B == C) {
			printf("Triângulo equilátero\n");
		} else if (A == B || A == C || B == C) {
			printf("Triângulo isósceles\n");
		} else {
			printf("Triângulo escaleno\n");
		}
	} else {
		printf("Não é triângulo\n");
	}
}
