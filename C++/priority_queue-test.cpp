#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
	
	priority_queue<int, vector<int>, greater<int> > fila;
	
	fila.push(10);
	fila.push(32);
	fila.push(5);
	fila.push(1);
	fila.push(65);
	fila.push(23);
	fila.push(87);
	fila.push(20);
	
	while (!fila.empty()) {
		cout << fila.top() << endl;
		fila.pop();
	}
	
	return 0;
}
