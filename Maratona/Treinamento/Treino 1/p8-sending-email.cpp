#include <iostream>
#include <queue>
#include <limits>

using namespace std;

unsigned int distancia[20000];

class Compare {
	public:
		bool operator() (int a, int b) {
			return distancia[a] > distancia[b];
		}
};

int main() {
	int testes;
	unsigned int maximo = numeric_limits<unsigned int>::max();
	
	cin >> testes;

	for (int i = 1; i <= testes; i++) {
		int servidores;
		int ligacoes;
		int origem;
		int destino;

		cin >> servidores >> ligacoes >> origem >> destino;

		unsigned int grafo[servidores][servidores];

		for (int x = 0; x < servidores; x++) {
			for (int y = 0; y < servidores; y++) {
				grafo[x][y] = maximo;
			}
		}

		for (int x = 0; x < ligacoes; x++) {
			int origem;
			int destino;
			unsigned int peso;
			
			cin >> origem >> destino >> peso;

			if (grafo[origem][destino] > peso) {
				grafo[origem][destino] = grafo[destino][origem] = peso;
			}
		}
		
		bool visitado[servidores];
		
		priority_queue<int, vector<int>, Compare> nodos;
		
		for (int x = 0; x < servidores; x++) {
			visitado[x] = false;
			distancia[x] = maximo;
		}
		
		distancia[origem] = 0;
		nodos.push(origem);
		
		while (!nodos.empty()) {
			int atual = nodos.top();
			
			nodos.pop();
			
			if (!visitado[atual]) {
				visitado[atual] = true;
				
				for (int x = 0; x < servidores; x++) {
					if (grafo[atual][x] < maximo && (distancia[x] == maximo || grafo[atual][x] + distancia[atual] < distancia[x])) {
						distancia[x] = grafo[atual][x] + distancia[atual];
						
						nodos.push(x);
					}
				}
			}
		}
		
		cout << "Case #" << i << ": ";
		
		if (distancia[destino] < maximo) {
			cout << distancia[destino];
		} else {
			cout << "unreachable";
		}
		
		cout << endl;
		
	}
	
	return 0;
}
