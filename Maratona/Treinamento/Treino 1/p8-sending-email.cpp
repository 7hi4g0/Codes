#include <iostream>
#include <queue>

using namespace std;

int main() {
	int testes;
	
	cin >> testes;
	
	for (int i = 1; i <= testes; i++ ) {
		int servidores;
		int ligacoes;
		int origem;
		int destino;
		
		cin >> servidores >> ligacoes >> origem >> destino;
		
		int grafo[servidores][servidores];
		
		for (int x = 0; x < servidores; x++) {
			grafo[x][x] = 0;
			
			for (int y = x + 1; y < servidores; y++) {
				grafo[x][y] = grafo[y][x] = -1;
			}
		}
		
		for (int x = 0; x < ligacoes; x++) {
			int origem;
			int destino;
			int peso;
			
			cin >> origem >> destino >> peso;
			
			grafo[origem][destino] = grafo[destino][origem] = peso;
		}
		
		int peso[servidores];
		bool visitado[servidores];
		
		for (int x = 0; x < servidores; x++) {
			peso[x] = -1;
			visitado[x] = false;
		}
		
		priority_queue<pair<int, int> > nodos;
		
		peso[origem] = 0;
		
		nodos.push(pair<int, int> (peso[origem], origem));
		
		while (!nodos.empty()) {
			int servidor = nodos.top().second;
			
			nodos.pop();
			
			if (!visitado[servidor]) {
				visitado[servidor] = true;
				
				for (int x = 0; x < servidores; x++) {
					int temp = peso[servidor] + grafo[servidor][x];
					
					if (grafo[servidor][x] >= 0 && (peso[x] == -1 || peso[x] > temp)) {
						peso[x] = temp;
						
						nodos.push(pair<int, int> (peso[x], x));
					}
				}
			}
		}
		
		cout << "Case #" << i << ": ";
		
		if (peso[destino] != -1) {
			cout << peso[destino] << endl;
		} else {
			cout << "unreachable" << endl;
		}
	}
	
	return 0;
}
