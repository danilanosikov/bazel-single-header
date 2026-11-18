#include <system.h>
#include <error.h>

bool created = false;

static callback create;
static callback update;
static callback destroy;

int oku_system_create(callback on_create, callback on_destroy, callback on_update) {
	if(created) return oku_system_error_created;
	create = on_create;
	update = on_update;
	destroy = on_destroy;
	if(0>create()) return oku_system_error_creation;
	created = true;
	return 0;
}
int oku_system_destroy() {
	if(!created) return oku_system_error_destroyed;
	if(0>destroy()) return oku_system_error_destruction;
	created = false;
	return 0;
}
int oku_system_update() {
	if(!created) return oku_system_error_destroyed;
	if(0>update()) {
		if(0>oku_system_destroy()) return oku_system_error_destruction;
		return oku_system_error_update;
	}
	return 0;
}
