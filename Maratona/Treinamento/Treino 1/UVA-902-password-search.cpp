#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
	int tamanho;
	
	while (cin >> tamanho) {
		string mensagem;
		map<string, int> substrings;
		
		cin >> mensagem;
		
		for (int i = 0; i < mensagem.length() - tamanho; i++) {
			substrings[mensagem.substr(i, tamanho)]++;
		}
		
		int count = 0;
		string senha;
		
		for (map<string, int>::iterator it = substrings.begin(); it != substrings.end(); it++){
			if (it->second > count) {
				count = it->second;
				senha = it->first;
			}
		}
		
		cout << senha << endl;
	}
	
	return 0;
}
