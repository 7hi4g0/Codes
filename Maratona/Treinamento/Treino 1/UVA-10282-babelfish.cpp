#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main() {
	string linha;
	string ingles;
	string estrangeiro;
	map< string, string> dicionario;
	
	getline(cin, linha);
	
	while (linha.length() > 0) {
		stringstream entrada(linha);
		
		entrada >> ingles;
		entrada >> estrangeiro;
		
		dicionario[estrangeiro] = ingles;
		
		getline(cin, linha);
	}
	
	while (cin >> linha) {
		if (dicionario.count(linha) > 0) {
			cout << dicionario[linha];
		} else {
			cout << "eh";
		}
		
		cout << endl;
	}
	
	return 0;
}
