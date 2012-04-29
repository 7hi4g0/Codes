#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;

int main(){
	while (1){
		float x, y, z;
		
		cout << "Entre o ponto: ";
		cin >> x >> y >> z;
		
		//float z2 = -sqrt(6.f) * x / 8.f + y / 4.f + sqrt(6.f) * z / 8.f + 1;
		//float x2 = (sqrt(2.f) * x / 2.f + sqrt(3.f) * z / 2.f) / z2;
		//float y2 = (sqrt(2.f) * x / 4.f + sqrt(3.f) * y / 2.f - sqrt(2.f) * z / 4.f) / z2;
		
		float z2 = -0.5f * z + 1;
		float x2 = x / z2;
		float y2 = y / z2;
		
		cout << fixed << setprecision(2) << x2 << ", " << y2 << endl;
	}
}
