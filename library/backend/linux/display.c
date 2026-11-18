#include <system.h>
#include <error.h>

#ifndef okd_rgfw
	#include <rgfw.h>
	#define okd_rgfw okd_rgfw
#endif

static RGFW_window* window = NULL;
int oku_system_display_create() {
	oku_system_guard(created, oku_system_error_initialized);
	window = RGFW_createWindow("okular", 0, 0, 800, 640, RGFW_windowCenter | RGFW_windowNoResize);
	if(!window) return oku_system_error_display;
	return 0;
}
#ifdef oku_system_test
// имитация нажатия кнопки закрытия окна
int oku_system_test_display_close() {
	if(!window) return oku_system_error_display;
	RGFW_window_setShouldClose(window, RGFW_TRUE);
	return 0;
}
#endif
int oku_system_display_update() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	if(!window) return oku_system_error_display;

	if(RGFW_window_shouldClose(window)) return oku_system_error_exit;
	RGFW_pollEvents();

	// @задача: перевести отдать на реализацию пользователю
	if(RGFW_isKeyPressed(RGFW_escape)) return oku_system_error_exit;

	return 0;
}
int oku_system_display_destroy() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	if(!window) return oku_system_error_display;
	RGFW_window_close(window);
	window = NULL;
	return 0;
}

int oku_system_display_show() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	return 0;
}
int oku_system_display_hide() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	return 0;
}
int oku_system_display_fullscreen() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	// window->internal.flags |= RGFW_windowedFullscreen;
	return 0;
}
int oku_system_display_windowed() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	// window->internal.flags &= ~RGFW_windowedFullscreen;
	return 0;
}
int oku_system_display_move() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	return 0;
}
int oku_system_display_size() {
	oku_system_guard(!created, oku_system_error_uninitialized);
	return 0;
}
