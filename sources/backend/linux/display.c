#include <system.h>
#include <error.h>
#include <rgfw.h>

/* поверхность */
#ifndef okd_wayland_client
	#include <wayland-client.h>
	#define okd_wayland_client okd_wayland_client
#endif

#ifndef okd_xdg_shell
	#include <xdg-shell.h>
	#define okd_xdg_shell okd_xdg_shell
#endif

// #ifndef okd_xdg_decoration
//     #include <xdg-decoration.h>
//     #define okd_xdg_decoration
// #endif

#ifndef okd_string
	#include <string.h>
	#define okd_string okd_string
#endif
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
