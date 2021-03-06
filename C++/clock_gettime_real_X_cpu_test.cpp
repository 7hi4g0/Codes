#include <iostream>
#include <ctime>
#include <unistd.h>

using std::cout;
using std::endl;

int main(){
	timespec ts1, ts2, ts3;
	double time1, time2, time3;
	
	clock_getres(CLOCK_REALTIME, &ts1);
	clock_getres(CLOCK_MONOTONIC, &ts2);
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &ts3);
	
	time1 = ts1.tv_sec + static_cast<double>(ts1.tv_nsec) / 1000000000;
	time2 = ts2.tv_sec + static_cast<double>(ts2.tv_nsec) / 1000000000;
	time3 = ts3.tv_sec + static_cast<double>(ts3.tv_nsec) / 1000000000;
	
	cout << "Real: \t\t\t" << time1 << "s" << endl;
	cout << "Monotonic: \t\t" << time2 << "s" << endl;
	cout << "Process CPU time: \t" << time3 << "s" << endl;
	
	clock_gettime(CLOCK_REALTIME, &ts1);
	clock_gettime(CLOCK_MONOTONIC, &ts2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts3);
	
	time1 = ts1.tv_sec + static_cast<double>(ts1.tv_nsec) / 1000000000;
	time2 = ts2.tv_sec + static_cast<double>(ts2.tv_nsec) / 1000000000;
	time3 = ts3.tv_sec + static_cast<double>(ts3.tv_nsec) / 1000000000;
	
	sleep(5);
	
	clock_gettime(CLOCK_REALTIME, &ts1);
	clock_gettime(CLOCK_MONOTONIC, &ts2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts3);
	
	time1 = (ts1.tv_sec + static_cast<double>(ts1.tv_nsec) / 1000000000) - time1;
	time2 = (ts2.tv_sec + static_cast<double>(ts2.tv_nsec) / 1000000000) - time2;
	time3 = (ts3.tv_sec + static_cast<double>(ts3.tv_nsec) / 1000000000) - time3;
	
	cout << "Real: \t" << time1 << "s" << endl;
	cout << "Monotonic: \t" << time2 << "s" << endl;
	cout << "Process CPU time: \t" << time3 << "s" << endl;
}
