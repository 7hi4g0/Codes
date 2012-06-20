#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int letras;
	int repeticoes;
	
	cin >> letras >> repeticoes;
	
	while(letras != 0) {
		vector<int> permutacao(letras);
		int *saida = new int[letras];
		string linha;
		
		for (int i = 0; i < letras; i++) {
			int indice;
			
			cin >> indice;
			
			permutacao[i] = indice - 1;
		}
		
		getline(cin, linha);
		getline(cin, linha);
		
		int periodo;
		
		for (int i = 0; i < letras; i++) {
			saida[i] = i;
		}
		
		int *ant = saida;
		
		saida = new int[letras];
		
		for (int i = 0; i < letras; i++) {
			saida[i] = ant[permutacao[i]];
			
			//cout << permutacao[i];
		}
		
		delete[] ant;
		
		//cout << endl;
		
		int *atual = new int[letras];
		
		for (periodo = 1; periodo < repeticoes; periodo++) {
			bool igual = true;
			
			for (int i = 0; i < letras; i++) {
				atual[i] = saida[permutacao[i]];
				
				//cout << (*atual)[i] << " ";
				
				if (atual[i] != permutacao[i]) {
					igual = false;
				}
			}
			
			//cout << endl;
			
			int *temp;
			
			temp = saida;
			saida = atual;
			atual = temp;
			
			if (igual) {
				break;
			}
		}
		
		//cout << periodo << " " << combinacoes.size() << endl;
		
		int repete;
		
		if (periodo == repeticoes) {
			repete = periodo;
		}else {
			repete = periodo - (repeticoes % periodo);
		}
		
		for (int i = 0; i < letras; i++) {
			saida[i] = i;
		}
		
		for (periodo = 0; periodo < repete; periodo++) {
			
			for (int i = 0; i < letras; i++) {
				atual[i] = saida[permutacao[i]];
			}
			
			int *temp;
			
			temp = saida;
			saida = atual;
			atual = temp;
		}
		
		for (int i = 0; i < letras; i++) {
			cout << linha[saida[i]];
		}
		
		delete[] saida;
		delete[] atual;
		
		cout << endl;
		
		cin >> letras >> repeticoes;
	}
	
	return 0;
}
