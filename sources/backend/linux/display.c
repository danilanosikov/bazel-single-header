#include <system.h>
#include <error.h>

/* поверхность */
#ifndef okd__wayland_client
	#include <wayland-client.h>
	#define okd__wayland_client okd__wayland_client
#endif

#ifndef okd__xdg_shell
	#include <xdg-shell.h>
	#define okd__xdg_shell okd__xdg_shell
#endif

// #ifndef okd__xdg_decoration
//     #include <xdg-decoration.h>
//     #define okd__xdg_decoration
// #endif

int oku_system_display_create() {
	if(initialized) return oku_system_error_initialized;
	return 0;
}
int oku_system_display_update() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_display_destroy() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}


int oku_system_display_show() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_display_hide() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_display_full() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_display_move() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_display_size() {
	if(!initialized) return oku_system_error_uninitialized;
	return 0;
}
