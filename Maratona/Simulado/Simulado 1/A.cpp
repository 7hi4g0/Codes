#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

int main() {
	int testes;
	
	cin >> testes;
	
	for (int teste = 1; teste <= testes; teste++) {
		int primeira;
		int segunda;
		
		cin >> primeira >> segunda;
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		map<string, int> ling;
		
		for (int i = 0; i < primeira; i++) {
			string palavra;
			
			getline(cin, palavra);
			
			ling[palavra]++;
		}
		
	//	primeira = ling.size();
	//	ling.clear();
		
		for (int i = 0; i < segunda; i++) {
			string palavra;
			
			getline(cin, palavra);
			
			ling[palavra]++;
		}
		
	//	segunda = ling.size();
	//	ling.clear();
		
		cout << "Case " << teste << ": " << primeira * segunda  << endl;
	}
	
	return 0;
}
