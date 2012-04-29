#include <iostream>
#include <limits>
#include <cstdio>

using namespace std;

const int maximo = numeric_limits<int>::max();

int main() {
	int frequencias;
	int programas;
	int energia;
	int tempo;
	
	scanf("%d %d %d %d", &frequencias, &programas, &energia, &tempo);
	
	while (frequencias) {
		int grafo[programas][frequencias];
		
		for (int p = 0; p < programas; p++) {
			for (int f = 0; f < frequencias; f++) {
				int energia;
				int tempo;
				
				scanf("%d %d", &energia, &tempo);
				
				grafo[p][f] = energia * tempo;
			}
		}
		
		int energiaTempo[programas][frequencias];
		int enTem = energia * tempo;
		
		for (int p = 0; p < programas; p++) {
			for (int f = 0; f < frequencias; f++) {
				energiaTempo[p][f] = maximo;	
			}
		}
		
		energiaTempo[0][0] = grafo[0][0];
		
		for (int f = 1; f < frequencias; f++) {
			energiaTempo[0][f] = grafo[0][f] + enTem;
		}
		
		for (int p = 1; p < programas; p++) {
			for (int f = 0; f < frequencias; f++) {
				for (int f2 = 0; f2 < frequencias; f2++) {
					int temp = enTem;
					
					if (f2 == f) {
						temp = 0;
					}
					
					if (energiaTempo[p - 1][f2] + grafo[p][f] + temp < energiaTempo[p][f]) {
						 energiaTempo[p][f] = energiaTempo[p - 1][f2] + grafo[p][f] + temp;
					}
				}
			}
		}
		
		int minimo = maximo;
		
		for (int f = 0; f < frequencias; f++) {
			if (energiaTempo[programas - 1][f] < minimo) {
				minimo = energiaTempo[programas - 1][f];
			}
		}
		
		cout << minimo << endl;
		
		scanf("%d %d %d %d", &frequencias, &programas, &energia, &tempo);
	}
	
	return 0;
}
