#include <iostream>
#include <algorithm>

using namespace std;

long int table[33][33][100];
int bits;
int modulo;

long int test(char resto, char uns, char zeros) {
	
	if (table[uns][zeros][resto] != -1) {
		return table[uns][zeros][resto];
	} else {
		long int count = 0;
	
		if (uns < bits / 2) {
			count += test(((resto << 1) + 1) % modulo, uns + 1, zeros);
		}
	
		if (zeros < bits / 2) {
			count += test((resto << 1) % modulo, uns, zeros + 1);
		}
		
		return table[uns][zeros][resto] = count;
	}
}

int main() {
	int testes;
	
	cin >> testes;
	
	for (int caso = 1; caso <= testes; caso++) {
		cout << "Case " << caso << ": ";
		
		fill_n(**table, 33 * 33 * 100, -1);
		
		cin >> bits >> modulo;
		
		table[bits / 2][bits / 2][0] = 1;
		
		cout << (((modulo > 0) && (bits % 2 == 0)) ? test(1 % modulo, 1, 0) : 0) << endl;
	}
	
	return 0;
}
