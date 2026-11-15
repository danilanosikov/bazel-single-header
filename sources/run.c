#include <system.h>

int main(void)
{
	oku_system_create(4096);
	oku_system_display_create();
	oku_system_display_destroy();
	oku_system_destroy();
}
