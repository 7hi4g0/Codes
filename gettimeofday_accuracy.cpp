#include <iostream>
#include <ctime>
#include <sys/time.h>
using namespace std;

int main()
{
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    gettimeofday(&t2, NULL);
	
	//while (t1.tv_usec == t2.tv_usec)
    	//gettimeofday(&t2, NULL);
	
    // print resolution
    cout << (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000.0 << " ms." << endl;

    return 0;
}
