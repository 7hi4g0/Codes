#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>

extern xcb_connection_t		*conn;
extern xcb_window_t			win;
extern xcb_screen_t			*screen;

VkXcbSurfaceCreateInfoKHR createWindow();
void destroyWindow();
