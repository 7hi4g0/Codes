#include <iostream>
#include <queue>

using namespace std;

int main() {
	int tamanho;
	
	cin >> tamanho;
	
	while (tamanho) {
		queue<int> deck;
		
		for (int i = 1; i <= tamanho; i++) {
			deck.push(i);
		}
		
		cout << "Discarded cards:";
		
		while (deck.size() > 1) {
			cout << " " << deck.front();
			deck.pop();
			
			if (deck.size() != 1) {
				cout << ",";
			}
			
			deck.push(deck.front());
			deck.pop();
		}
		
		cout << endl;
		cout << "Remaining card: " << deck.front() << endl;
		
		deck.pop();
		
		cin >> tamanho;
	}
	
	return 0;
}
