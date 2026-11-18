#include <system.h>
#include <error.h>

int oku_system_input_create() {
	if(created) return oku_system_error_initialized;
	return 0;
}
int oku_system_input_update() {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_input_destroy() {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
