#include <iostream>
#include <stack>
#include <limits>

using namespace std;

int main() {
	int vagoes;
	
	cin >> vagoes;
	
	while (vagoes) {
		int vagao;
		stack<int> estacao;
		stack<int> trem;
		
		cin >> vagao;
		
		while (vagao) {
			
			for (int i = vagoes; i > 0; i--) {
				trem.push(i);
			}
			
			bool possivel = true;
			
			for (int i = 1; i < vagoes; i++) {
				while (estacao.empty() || estacao.top() < vagao) {
					estacao.push(trem.top());
					trem.pop();
				}
				
				if (estacao.top() == vagao) {
					estacao.pop();
				} else {
					possivel = false;
					while (!estacao.empty()) {
						estacao.pop();
					}
					while (!trem.empty()) {
						trem.pop();
					}
					break;
				}
				
				cin >> vagao;
			}
			
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			
			if (possivel) {
				cout << "Yes";
			} else {
				cout << "No";
			}
			
			cout << endl;
			
			cin >> vagao;
		}
		
		cin >> vagoes;
		
		if (vagoes > 0) {
			cout << endl;
		}
	}
	
	return 0;
}
