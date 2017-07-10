#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<poll.h>

#include<libinput.h>

static bool stop = false;

static void signal_handler(int signo) {
	stop = true;
	printf("Captured SIGINT\n");
}

static int open_restricted(const char *path, int flags, void *user_data) {
	int fd = open(path, flags);

	if (fd < 0) {
		fprintf(stderr, "Failed to open %s (%s)\n", path, strerror(errno));
	}

	return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void *user_data) {
	close(fd);
}

static const struct libinput_interface interface = {
	.open_restricted = open_restricted,
	.close_restricted = close_restricted,
};

int main(int argc, char *argv[]) {
	struct libinput *li;
	struct udev *udev;

	udev = udev_new();
	li = libinput_udev_create_context(&interface, NULL, udev);

	if (libinput_udev_assign_seat(li, "seat0")) {
		fprintf(stderr, "Failed to set seat\n");
		libinput_unref(li);
		li = NULL;
	}

	udev_unref(udev);

	if (!li) {
		return 1;
	}

	struct sigaction act = {0};
	act.sa_handler = signal_handler;

	sigaction(SIGINT, &act, NULL);

	struct pollfd fds = {0};
	fds.fd = libinput_get_fd(li);
	fds.events = POLLIN;
	fds.revents = 0;

	while (!stop && poll(&fds, 1, -1) > -1) {
		struct libinput_event *ev;

		libinput_dispatch(li);
		while (ev = libinput_get_event(li)) {
			struct libinput_event_keyboard *kev;
			uint32_t keycode;

			switch (libinput_event_get_type(ev)) {
				case LIBINPUT_EVENT_KEYBOARD_KEY:
					kev = libinput_event_get_keyboard_event(ev);
					keycode = libinput_event_keyboard_get_key(kev);
					printf("Captured key %d\n", keycode);
					break;
				default:
					//printf("Untreated event captured\n");
					break;
			}
			libinput_event_destroy(ev);
			libinput_dispatch(li);
		}
	}

	printf("Exiting!\n");

	libinput_unref(li);

	return 0;
}
