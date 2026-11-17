#include <system.h>
#include <error.h>

#ifndef okd_rgfw
	#include <rgfw.h>
	#define okd_rgfw okd_rgfw
#endif

static RGFW_window* window = NULL;
int oku_system_display_create() {
	if(initialized) return oku_system_error_initialized;
	window = RGFW_createWindow("okular", 0, 0, 800, 640, RGFW_windowCenter | RGFW_windowNoResize);
	if(!window) return oku_system_error_display;
	return 0;
}
int oku_system_display_update() {
	if(!initialized) return oku_system_error_uninitialized;
	if(!window) return oku_system_error_display;
	while(!RGFW_window_shouldClose(window)) {
		RGFW_pollEvents();
		if(RGFW_isKeyPressed(RGFW_escape)) break;
	}
	return 0;
}
int oku_system_display_destroy() {
	if(!initialized) return oku_system_error_uninitialized;
	if(!window) return oku_system_error_display;
	RGFW_window_close(window);
	window = NULL;
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
int oku_system_display_fullscreen() {
	if(!initialized) return oku_system_error_uninitialized;
	// window->internal.flags |= RGFW_windowedFullscreen;
	return 0;
}
int oku_system_display_windowed() {
	if(!initialized) return oku_system_error_uninitialized;
	// window->internal.flags &= ~RGFW_windowedFullscreen;
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
