#include <stdio.h>

union ints {
	int fourBytes;
	char oneByte[4];
};

int main() {
	int fourBytes = 0x12345678;

	printf("%ld bytes\n", sizeof(fourBytes));

	char *oneByte = (char *) &fourBytes;

	printf("\nPointer:\n");
	printf("0x%08x - 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx\n", fourBytes, oneByte[0], oneByte[1], oneByte[2], oneByte[3]);

	union ints intUnion = (union ints) fourBytes;

	printf("\nUnion:\n");
	printf("0x%08x - 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx\n",
			intUnion.fourBytes, intUnion.oneByte[0], intUnion.oneByte[1], intUnion.oneByte[2], intUnion.oneByte[3]);
}
