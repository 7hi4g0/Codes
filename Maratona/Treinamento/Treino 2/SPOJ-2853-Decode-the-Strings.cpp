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
		vector<int> *saida = new vector<int>(letras);
		string linha;
		
		for (int i = 0; i < letras; i++) {
			int indice;
			
			cin >> indice;
			
			permutacao[i] = indice - 1;
		}
		
		getline(cin, linha);
		getline(cin, linha);
		
		vector< vector<int>* > combinacoes;
		int periodo;
		
		for (int i = 0; i < letras; i++) {
			(*saida)[i] = i;
		}
		
		combinacoes.push_back(saida);
		saida = new vector<int>(letras);
		
		for (int i = 0; i < letras; i++) {
			vector<int> *ant = combinacoes.back();
			
			(*saida)[i] = (*ant)[permutacao[i]];
			
			//cout << permutacao[i];
		}
		
		//cout << endl;
		
		combinacoes.push_back(saida);
		
		for (periodo = 1; periodo < repeticoes; periodo++) {
			vector<int> *atual = new vector<int>(letras);
			
			combinacoes.push_back(atual);
			
			bool igual = true;
			
			for (int i = 0; i < letras; i++) {
				(*atual)[i] = (*saida)[permutacao[i]];
				
				//cout << (*atual)[i] << " ";
				
				if ((*atual)[i] != permutacao[i]) {
					igual = false;
				}
			}
			
			//cout << endl;
			
			saida = atual;
			
			if (igual) {
				break;
			}
		}
		
		//cout << periodo << " " << combinacoes.size() << endl;

		if (periodo == repeticoes) {
			saida = combinacoes[periodo];
		}else {
			saida = combinacoes[periodo - (repeticoes % periodo)];
		}
		
		for (int i = 0; i < letras; i++) {
			cout << linha[(*saida)[i]];
		}
		
		while (!combinacoes.empty()) {
			delete combinacoes.back();
			
			combinacoes.pop_back();
		}
		
		cout << endl;
		
		cin >> letras >> repeticoes;
	}
	
	return 0;
}
