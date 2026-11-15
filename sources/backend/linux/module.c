#include <system.h>
#include <error.h>

bool initialized = false;

int oku_system_create(size_t memory) {
	if(initialized) return oku_system_error_initialized;

	if(0>oku_system_memory_create(memory)) return oku_system_error_memory;
	if(0>oku_system_display_create()) return oku_system_error_display;

	initialized = true;
	return 0;
}
int oku_system_destroy() {
	if(!initialized) return oku_system_error_uninitialized;

	if(0>oku_system_display_destroy()) return oku_system_error_display;
	if(0>oku_system_memory_destroy()) return oku_system_error_memory;

	initialized = false;
	return 0;
}
int oku_system_update() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
