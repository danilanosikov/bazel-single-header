#include <system.h>
#include <error.h>

bool created = false;

static callback create;
static callback update;
static callback destroy;

int oku_system_create(callback on_create, callback on_update, callback on_destroy) {
	oku_system_guard(created, oku_system_error_created);
	create = on_create;
	update = on_update;
	destroy = on_destroy;
	if(0>create()) return oku_system_error_creation;
	created = true;
	return 0;
}

int oku_system_destroy() {
	oku_system_guard(!created, oku_system_error_destroyed);
	if(0>destroy()) return oku_system_error_destruction;
	created = false;
	return 0;
}

int oku_system_update() {
	oku_system_guard(!created, oku_system_error_destroyed);

	switch(update())
	{
		case 0: case oku_system_error_exit:
			return 0;
		default:
			return 0>oku_system_destroy() ?  oku_system_error_update : oku_system_error_destruction;
	}
	return 0;
}
