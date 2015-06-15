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
			fprintf(stderr, "Unknown type flag");
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

	while ((entry = readdir(directory)) != NULL) {
		if (endsWith(entry->d_name, "-event-joystick") == 0) {
			unsigned int pathLength;
			char *joystick;
			struct libevdev *dev;
			int js;

			pathLength = strlen("/dev/input/by-path/") + strlen(entry->d_name) + 1;
			joystick = (char *) malloc(sizeof(char) * pathLength);
			strcpy(joystick, "/dev/input/by-path/");
			strcat(joystick, entry->d_name);

			printf("%s - %s\n", joystick, typeString(entry->d_type));

			js = open(joystick, O_RDONLY|O_NONBLOCK);
			libevdev_new_from_fd(js, &dev);

			printf("%s\n", libevdev_get_name(dev));
			if (libevdev_has_event_code(dev, EV_KEY, BTN_GAMEPAD)) {
				printf("\tIs a gamepad\n");
			}

			struct input_event ev;
			while (1) {
				libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
				if (ev.type == EV_KEY) {
					char *codeName = libevdev_event_code_get_name(ev.type, ev.code);
					printf("%s(%x)\n", codeName != NULL ? codeName : "Unknown", ev.code);
				}
			}
		}
	}

	closedir(directory);
}
