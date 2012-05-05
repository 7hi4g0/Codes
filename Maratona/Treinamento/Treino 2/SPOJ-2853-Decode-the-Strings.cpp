#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int letras;
	int repeticoes;
	
	cin >> letras >> repeticoes;
	
	while (letras != 0 && repeticoes != 0) {
		int ordem[letras];
		string linha;
		
		for (int i = 0; i < letras; i++) {
			int temp;
			
			cin >> temp;
			
			ordem[temp - 1] = i;
		}
		
		getline(cin, linha);
		getline(cin, linha);
		
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
		
		cin >> letras >> repeticoes;
	}
	
	return 0;
}
