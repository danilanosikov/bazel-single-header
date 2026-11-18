#include <system.h>
#include <error.h>

int oku_system_input_create() {
	oku_system_guard(created, oku_system_error_created);
	return 0;
}
int oku_system_input_update() {
	oku_system_guard(!created, oku_system_error_destroyed);
	return 0;
}
int oku_system_input_destroy() {
	oku_system_guard(!created, oku_system_error_destroyed);
	return 0;
}
