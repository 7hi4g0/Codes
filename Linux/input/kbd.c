#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include <linux/input.h>
#include <libevdev-1.0/libevdev/libevdev.h>

char *types[] = {
	"DT_UNKNOWN",
	"DT_REG",
	"DT_DIR",
	"DT_FIFO",
	"DT_SOCK",
	"DT_CHR",
	"DT_BLK",
	"DT_LNK"
};

char *codes[] = {
	"KEY_A",
	"KEY_B",
	"KEY_C",
	"KEY_D",
	"KEY_E",
	"KEY_F",
	"KEY_G",
	"KEY_H",
	"KEY_I",
	"KEY_J",
	"KEY_K",
	"KEY_L",
	"KEY_M",
	"KEY_N",
	"KEY_O",
	"KEY_P",
	"KEY_Q",
	"KEY_R",
	"KEY_S",
	"KEY_T",
	"KEY_U",
	"KEY_V",
	"KEY_W",
	"KEY_X",
	"KEY_Y",
	"KEY_Z"
};

char * typeString(unsigned char type) {
	switch (type) {
		case DT_UNKNOWN:
			return types[0];
		case DT_REG:
			return types[1];
		case DT_DIR:
			return types[2];
		case DT_FIFO:
			return types[3];
		case DT_SOCK:
			return types[4];
		case DT_CHR:
			return types[5];
		case DT_BLK:
			return types[6];
		case DT_LNK:
			return types[7];
		default:
			fprintf(stderr, "Unknown type flag\n");
			return NULL;
	}
}

char * codeString(unsigned short code) {
	switch (code) {
		case KEY_A:
			return codes[0];
		case KEY_B:
			return codes[1];
		case KEY_C:
			return codes[2];
		case KEY_D:
			return codes[3];
		case KEY_E:
			return codes[4];
		case KEY_F:
			return codes[5];
		case KEY_G:
			return codes[6];
		case KEY_H:
			return codes[7];
		case KEY_I:
			return codes[8];
		case KEY_J:
			return codes[9];
		case KEY_K:
			return codes[10];
		case KEY_L:
			return codes[11];
		case KEY_M:
			return codes[12];
		case KEY_N:
			return codes[13];
		case KEY_O:
			return codes[14];
		case KEY_P:
			return codes[15];
		case KEY_Q:
			return codes[16];
		case KEY_R:
			return codes[17];
		case KEY_S:
			return codes[18];
		case KEY_T:
			return codes[19];
		case KEY_U:
			return codes[20];
		case KEY_V:
			return codes[21];
		case KEY_W:
			return codes[22];
		case KEY_X:
			return codes[23];
		case KEY_Y:
			return codes[24];
		case KEY_Z:
			return codes[25];
		default:
			fprintf(stderr, "Unknown code\n");
			return NULL;
	}
}

int endsWith(char *string, char *subString) {
	int length = strlen(string);
	int subLength = strlen(subString);
	return strcmp(string + (length - subLength), subString);
}

int main() {
	struct dirent *entry;
	DIR *directory;

	directory = opendir("/dev/input/by-path/");

	if (directory == NULL) {
		fprintf(stderr, "Error opening devices directory");
		exit(-1);
	}

	char *keyboard = NULL;

	while ((entry = readdir(directory)) != NULL) {
		if (endsWith(entry->d_name, "-event-kbd") == 0) {
			unsigned int pathLength;

			pathLength = strlen("/dev/input/by-path/") + strlen(entry->d_name) + 1;
			keyboard = (char *) malloc(sizeof(char) * pathLength);
			strcpy(keyboard, "/dev/input/by-path/");
			strcat(keyboard, entry->d_name);

			break;
		}
	}

	closedir(directory);

	if (keyboard == NULL) {
		fprintf(stderr, "Keyboard not found!\n");
	}

	struct libevdev *dev;
	int kbd;

	printf("%s - %s\n", keyboard, typeString(entry->d_type));

	kbd = open(keyboard, O_RDONLY);
	if (kbd == -1) {
		fprintf(stderr, "Unable to open device\n");
		exit(-1);
	}
	libevdev_new_from_fd(kbd, &dev);

	printf("%s\n", libevdev_get_name(dev));

	struct input_event ev;
	while (1) {
		libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL | LIBEVDEV_READ_FLAG_BLOCKING, &ev);
		if (ev.type == EV_KEY) {
			char *codeName = codeString(ev.code);
			printf("%s(%d - 0x%x)\n", codeName != NULL ? codeName : "Unknown", ev.code, ev.code);
		}
	}
}
