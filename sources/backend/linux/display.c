#include <system.h>
#include <error.h>

#ifndef okd_rgfw
	#include <rgfw.h>
	#define okd_rgfw okd_rgfw
#endif

static RGFW_window* window = NULL;

int oku_system_display_create() {
	if(initialized) return oku_system_error_initialized;
	// if(0>RGFW_createWindow("okular", 0, 0, 800, 640, RGFW_windowCenter | RGFW_windowNoResize)) return oku_system_error_display;
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
