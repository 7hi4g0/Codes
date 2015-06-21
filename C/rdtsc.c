#include <stdio.h>
#include <unistd.h>

static inline unsigned long long rdtsc() {
#if __x86_64__
	unsigned int tickh, tickl;
	asm volatile ("rdtsc": "=a"(tickl), "=d"(tickh));
	return ((unsigned long long)tickh << 32) | tickl;
#else
	unsigned long long tick;
	asm volatile ("rdtsc": "=A"(tick));
	return tick;
#endif
}

int main() {
	unsigned long long tick = rdtsc();

	printf("%lu (%lx)\n", tick, tick);

	sleep(5);

	tick = rdtsc();

	printf("%lu (%lx)\n", tick, tick);

	return 0;
}
