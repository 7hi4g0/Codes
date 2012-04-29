#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int frequencias;
	int programas;
	int energia;
	int tempo;
	
	scanf("%d %d %d %d", &frequencias, &programas, &energia, &tempo);
	
	while (frequencias) {
		int energiaTempo[programas][frequencias];
		
		for (int p = 0; p < programas; p++) {
			for (int f = 0; f < frequencias; f++) {
				int energia;
				int tempo;
				
				scanf("%d %d", &energia, &tempo);
				
				energiaTempo[p][f] = energia * tempo;
			}
		}
		
		int enTem = energia * tempo;
		
		energiaTempo[0][0] = energiaTempo[0][0];
		
		for (int f = 1; f < frequencias; f++) {
			energiaTempo[0][f] = energiaTempo[0][f] + enTem;
		}
		
		for (int p = 1; p < programas; p++) {
			for (int f = 0; f < frequencias; f++) {
				int valor = energiaTempo[p - 1][f] + energiaTempo[p][f];
				
				for (int f2 = 0; f2 < frequencias; f2++) {
					int x = energiaTempo[p - 1][f2] + energiaTempo[p][f] + enTem;
					
					if (x < valor) {
						 valor = x;
					}
				}
				
				energiaTempo[p][f] = valor;
			}
		}
		
		int minimo = energiaTempo[programas - 1][0];
		
		for (int f = 1; f < frequencias; f++) {
			if (energiaTempo[programas - 1][f] < minimo) {
				minimo = energiaTempo[programas - 1][f];
			}
		}
		
		cout << minimo << endl;
		
		scanf("%d %d %d %d", &frequencias, &programas, &energia, &tempo);
	}
	
	return 0;
}


