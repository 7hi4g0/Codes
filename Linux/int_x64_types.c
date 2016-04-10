#include <stdio.h>
#include <inttypes.h>
#include <linux/input.h>

int main() {
	printf("__s8:                      \t%lu bytes\n", sizeof(__s8));
	printf("__s16:                     \t%lu bytes\n", sizeof(__s16));
	printf("__s32:                     \t%lu bytes\n", sizeof(__s32));
	printf("__s64:                     \t%lu bytes\n", sizeof(__s64));

	printf("\n");
	printf("__u8:                      \t%lu bytes\n", sizeof(__u8));
	printf("__16:                      \t%lu bytes\n", sizeof(__u16));
	printf("__u32:                     \t%lu bytes\n", sizeof(__u32));
	printf("__u64:                     \t%lu bytes\n", sizeof(__u64));

	printf("\n");
	printf("int8_t:                    \t%lu bytes\n", sizeof(int8_t));
	printf("int16_t:                   \t%lu bytes\n", sizeof(int16_t));
	printf("int32_t:                   \t%lu bytes\n", sizeof(int32_t));
	printf("int64_t:                   \t%lu bytes\n", sizeof(int64_t));

	printf("\n");
	printf("uint8_t:                   \t%lu bytes\n", sizeof(uint8_t));
	printf("uint16_t:                  \t%lu bytes\n", sizeof(uint16_t));
	printf("uint32_t:                  \t%lu bytes\n", sizeof(uint32_t));
	printf("uint64_t:                  \t%lu bytes\n", sizeof(uint64_t));

	printf("\n");
	printf("char:                      \t%lu bytes\n", sizeof(char));
	printf("short int:                 \t%lu bytes\n", sizeof(short int));
	printf("short:                     \t%lu bytes\n", sizeof(short));
	printf("int:                       \t%lu bytes\n", sizeof(int));
	printf("long int:                  \t%lu bytes\n", sizeof(long int));
	printf("long:                      \t%lu bytes\n", sizeof(long));
	printf("long long int:             \t%lu bytes\n", sizeof(long long int));
	printf("long long:                 \t%lu bytes\n", sizeof(long long));

	printf("\n");
	printf("unsigned char:             \t%lu bytes\n", sizeof(unsigned char));
	printf("unsigned short int:        \t%lu bytes\n", sizeof(unsigned short int));
	printf("unsigned short:            \t%lu bytes\n", sizeof(unsigned short));
	printf("unsigned int:              \t%lu bytes\n", sizeof(unsigned int));
	printf("unsigned long int:         \t%lu bytes\n", sizeof(unsigned long int));
	printf("unsigned long:             \t%lu bytes\n", sizeof(unsigned long));
	printf("unsigned long long int:    \t%lu bytes\n", sizeof(unsigned long long int));
	printf("unsigned long long:        \t%lu bytes\n", sizeof(unsigned long long));

	printf("\n");

	return 0;
}
