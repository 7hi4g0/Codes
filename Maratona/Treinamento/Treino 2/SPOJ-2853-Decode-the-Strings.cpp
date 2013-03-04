#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <string>
=======
#include <string>
#include <vector>
#include <algorithm>
>>>>>>> e0b9ba2b6be6f9aa19561e965d4b461e9a984739

using namespace std;

int main() {
	int letras;
	int repeticoes;
	
	cin >> letras >> repeticoes;
	
<<<<<<< HEAD
	while(letras != 0) {
		vector<int> permutacao(letras);
		vector<int> *saida = new vector<int>(letras);
		string linha;
		
		for (int i = 0; i < letras; i++) {
			int indice;
			
			cin >> indice;
			
			permutacao[i] = indice - 1;
=======
	while (letras != 0 && repeticoes != 0) {
		int ordem[letras];
		string linha;
		
		for (int i = 0; i < letras; i++) {
			int temp;
			
			cin >> temp;
			
			ordem[temp - 1] = i;
>>>>>>> e0b9ba2b6be6f9aa19561e965d4b461e9a984739
		}
		
		getline(cin, linha);
		getline(cin, linha);
		
<<<<<<< HEAD
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
=======
		string saida(linha);
		
		for (int i = 0; i < letras; i++) {
			if (ordem[i] != i) {
				vector<int> mutacao;
				
				while (ordem[i] != i) {
					mutacao.push_back(ordem[i]);
					
					swap(ordem[i], ordem[ordem[i]]);
				}
				
				mutacao.push_back(i);
				
				int periodo = repeticoes % mutacao.size();
				
				for (int i = 0; i < mutacao.size(); i++) {
					saida[mutacao[i]] = linha[mutacao[(i + periodo) % mutacao.size()]];
				}
			}
		}
		
		cout << saida << endl;
>>>>>>> e0b9ba2b6be6f9aa19561e965d4b461e9a984739
		
		cin >> letras >> repeticoes;
	}
	
	return 0;
}
