#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define	test_bit(bit, bits)	((bit % 8) & (bits[bit / 8]))
#define	NBYTES(x)	(((x - 1)/8) + 1)
int main(int argc, char *argv[]) {
	int fd;

	if (argc < 2) {
		fprintf(stderr, "Inform the event device\n");
		exit(-1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Couldn't open %s\n", argv[1]);
		exit(-1);
	}

	unsigned char evbit[NBYTES(EV_MAX)] = {0};
	unsigned char keybit[NBYTES(KEY_MAX)] = {0};
	unsigned char absbit[NBYTES(ABS_MAX)] = {0};

	if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) < 0) {
		fprintf(stderr, "Couldn't get key info\n");
		exit(-1);
	}

	int key;
	for (key = 0; key < KEY_MAX; key++) {
		if(test_bit(key, keybit)) {
			printf("Found key 0x%03x\n", key);
		}
	}

	close(fd);

	return 0;
}
