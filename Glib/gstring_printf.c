#include <glib.h>
#include <glib/gprintf.h>

void main() {
	GString *str;
	gchar *temp;

	str = g_string_new("Teste");

	g_printf("%s\n", str->str);

	temp = g_strdup(str->str);
	g_string_printf(str, "Testando GString: \"%s\"\n", temp);
	g_free(temp);

	g_printf(str->str);
}
