#include <cstdio>
#include "keytables.cc"

using namespace logkeys;

int main() {
	
	wchar_t wch;
	
	for (int i = 30; i < 42; i++) {
		wch = char_keys[to_char_keys_index(i)];
		fprintf(stdout, "%lc", wch);
	}
	
	return 0;
}
