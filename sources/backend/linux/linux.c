#include <system.h>
#include <error.h>

#ifndef okd__sys_mman
	#include <sys/mman.h>
	#define okd__sys_mman
#endif
#ifndef okd__stdlib
	#include <stdlib.h>
	#define okd__stdlib
#endif
static void* mem;
static size_t mem_size;
static bool initialized = false;

int oku_system_create(size_t memory) {
	static void* result;

	if(initialized) return oku_system_error_initialization;

	// memory
	result = mmap(NULL, memory, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(result == MAP_FAILED) return oku_system_error_memory;
	mem=result;
	result = 0;
	mem_size = memory;

	initialized = true;
	return oku_system_success;
}
int oku_system_destroy() {
	static int result;

	if(!initialized) return oku_system_error_initialization;

	// memory
	result = munmap(mem, mem_size);
	if(result != 0) return oku_system_error_memory;
	result = 0;
	mem_size = 0;

	initialized = false;
	return oku_system_success;
}
int oku_system_update() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}




// поверхность
#ifndef okd__xdg_shell
	#include <xdg-shell.h>
	#define okd__xdg_shell okd__xdg_shell
#endif

#ifndef okd__wayland_client
	#include <wayland-client.h>
	#define okd__wayland_client okd__wayland_client
#endif

#ifndef okd__stdint
	#include <stdint.h>
	#define okd__stdint okd__stdint
#endif



static struct {
	struct wl_display *server;
	struct wl_registry *registry;
} display;

static void oku_system_display_registry_global_remove_callback(void *data, struct wl_registry *registry, uint32_t name) {

}
static void oku_system_display_registry_global_callback(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version) {
	printf("Найден интерфейс: '%s' (версия %u)\n", interface, version);	
}
static const struct wl_registry_listener display_listener = {
	.global = oku_system_display_registry_global_callback,
	.global_remove = oku_system_display_registry_global_remove_callback,
};

int oku_system_display_create() {
	if(!initialized) return oku_system_error_initialization;

	display.server = wl_display_connect(NULL);
	if(!display.server) return oku_system_error_display_server;

	display.registry = wl_display_get_registry(display.server);
	if(!display.registry) return oku_system_error_display_surface;
	if(0!=wl_registry_add_listener(display.registry, &display_listener, NULL)) return oku_system_error_display_listener;
	if(0!=wl_display_roundtrip(display.server)) return oku_system_error_display_roundtrip;
	
	return oku_system_success;
}
int oku_system_display_update() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
int oku_system_display_destroy() {
	if(!initialized) return oku_system_error_initialization;
	wl_display_disconnect(display.server);
	return oku_system_success;
}



int oku_system_display_show() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
int oku_system_display_hide() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
int oku_system_display_full() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
int oku_system_display_move() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
int oku_system_display_size() {
	if(!initialized) return oku_system_error_initialization;
	return oku_system_success;
}
