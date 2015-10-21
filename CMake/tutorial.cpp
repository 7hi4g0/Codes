#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " number" << endl;
		return 1;
	}

	double inputValue = atof(argv[1]);
	double outputValue = sqrt(inputValue);

	cout << "The square root of " << inputValue << " is " << outputValue << "." << endl;

	return 0;
}
