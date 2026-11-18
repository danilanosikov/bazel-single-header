#include <system.h>
#include <error.h>

int on_create() {
	if (0>oku_system_memory_create(4096)) return oku_system_error_memory;
	if (0>oku_system_display_create()) return oku_system_error_display;
	if (0>oku_system_input_create()) return oku_system_error_input;
	return 0;
}

int on_update() {
	// if (0>oku_system_memory_update()) return oku_system_error_memory;
	if (0>oku_system_display_update()) return oku_system_error_display;
	if (0>oku_system_input_update()) return oku_system_error_input;
	return 0;
}

int on_destroy() {
	if (0>oku_system_memory_destroy()) return oku_system_error_memory;
	if (0>oku_system_display_destroy()) return oku_system_error_display;
	if (0>oku_system_input_destroy()) return oku_system_error_input;
	return 0;
}
