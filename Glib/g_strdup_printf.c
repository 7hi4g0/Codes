#include <glib.h>
#include <glib/gprintf.h>

void main() {
	gchar *str;
	gchar *temp;

	str = g_strdup_printf("Test");

	g_printf("%s\n", str);

	temp = str;
	str = g_strdup_printf("Testando g_strdup_printf: \"%s\"\n", str);
	g_free(temp);

	g_printf(str);
}
