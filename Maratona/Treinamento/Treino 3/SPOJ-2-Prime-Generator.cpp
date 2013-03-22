#include <iostream>
#include <cmath>

using namespace std;

bool primo(int numero) {
	if (numero == 1) {
		return false;
	} else if (numero == 2) {
		return true;
	} else if (numero % 2 == 0) {
		return false;
	} else {
		for (int i = 3; i < sqrt(numero) + 1; i++) {
			if (numero % i == 0) {
				return false;
			}
		}
		
		return true;
	}
}

int main() {
	int testes;
	
	cin >> testes;
	
	while (testes--) {
		int comeco;
		int final;
		
		cin >> comeco >> final;
		
		for (int i = comeco; i <= final; i++) {
			if (primo(i)) {
				cout << i << endl;
			}
		}
		
		cout << endl;
	}
	
	return 0;
}
