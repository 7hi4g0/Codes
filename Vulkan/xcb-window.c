#include <xcb/xcb.h>

#include "window.h"

xcb_connection_t		*conn;
xcb_window_t			win;
xcb_screen_t			*screen;

VkXcbSurfaceCreateInfoKHR createWindow() {
	const xcb_setup_t		*setup;
	int						scr;
	xcb_screen_iterator_t	iter;

	conn = xcb_connect(NULL, &scr);

	setup = xcb_get_setup(conn);
	iter = xcb_setup_roots_iterator(setup);
	while (scr-- > 0) {
		xcb_screen_next(&iter);
	}
	screen = iter.data;

	win = xcb_generate_id(conn);

	xcb_create_window(conn, XCB_COPY_FROM_PARENT, win,
					  screen->root, 0, 0, 100, 100, 0,
					  XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
					  0, NULL);
	xcb_map_window(conn, win);

	xcb_flush(conn);

	VkXcbSurfaceCreateInfoKHR surface_info = {};
	surface_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	surface_info.pNext = NULL;
	surface_info.flags = 0;
	surface_info.connection = conn;
	surface_info.window = win;

	return surface_info;
}

void destroyWindow() {
	xcb_destroy_window(conn, win);
	xcb_disconnect(conn);
}
