#include <stdio.h>
#include <fcntl.h>
#include <linux/joystick.h>

void showEvent(struct js_event ev) {
		printf("{\n\ttime: %d\n\tvalue: %d\n\ttype: %s\n\tnumber: %d (%x)\n}\n",
				ev.time, ev.value,
				ev.type == JS_EVENT_INIT ? "JS_EVENT_INIT" : (ev.type == JS_EVENT_AXIS ? "JS_EVENT_AXIS" : "JS_EVENT_BUTTON"),
				ev.number, ev.number);
}

int main() {
	int js = open("/dev/input/js1", O_RDONLY);

	struct js_event ev;
	while (1) {
		read(js, &ev, sizeof(struct js_event));

		if (ev.type != JS_EVENT_AXIS) {
			showEvent(ev);
		}
	}

	close(js);
}
