#include <system.h>
#include <error.h>

#ifndef okd_rgfw
	#include <rgfw.h>
	#define okd_rgfw okd_rgfw
#endif

static RGFW_window* window = NULL;






int oku_system_display_create() {
	oku_system_guard(created, oku_system_error_created);
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
// тестовые хуки для наблюдения за состоянием окна (только для тестовой сборки)
int oku_system_test_display_hidden_get() {
	if(!window) return oku_system_error_display;
	return (window->internal.flags & RGFW_windowHide) ? 1 : 0;
}
int oku_system_test_display_mode_get() {
	if(!window) return oku_system_error_display;
	if(window->internal.flags & RGFW_windowFullscreen) return 1; // эксклюзивный полноэкранный режим
	if((window->internal.flags & RGFW_windowedFullscreen) == RGFW_windowedFullscreen) return 2; // безрамочный режим
	return 0; // обычное окно
}
int oku_system_test_display_geometry_get(int *x, int *y, int *w, int *h) {
	if(!window) return oku_system_error_display;
	if(!x || !y || !w || !h) return oku_system_error_display;
	*x = window->x;
	*y = window->y;
	*w = window->w;
	*h = window->h;
	return 0;
}
#endif
int oku_system_display_update() {
	oku_system_guard(!created, oku_system_error_destroyed);
	if(!window) return oku_system_error_display;

	if(RGFW_window_shouldClose(window)) {
		oku_system_exit_raise(oku_system_exit_window);
		return oku_system_exit_window;
	}
	RGFW_pollEvents();

	// @задача: перевести отдать на реализацию пользователю
	if(RGFW_isKeyPressed(RGFW_escape)) {
		oku_system_exit_raise(oku_system_exit_input);
		return oku_system_exit_input;
	}

	return 0;
}
int oku_system_display_destroy() {
	oku_system_guard(!created, oku_system_error_destroyed);
	if(!window) return oku_system_error_display;
	RGFW_window_close(window);
	window = NULL;
	return 0;
}

int oku_system_display_show() {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_show(window);
	return 0;
}
int oku_system_display_hide() {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_hide(window);
	return 0;
}
int oku_system_display_fullscreen() {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_setFlags(window, RGFW_windowFullscreen);
	return 0;
}
int oku_system_display_windowed() {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_setFlags(window, 0);
	return 0;
}
int oku_system_display_borderless() {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_setFlags(window, RGFW_windowedFullscreen);
	return 0;
}
int oku_system_display_move(int x, int y) {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	RGFW_window_move(window, x, y);
	return 0;
}
int oku_system_display_size(int width, int height) {
	oku_system_guard(!created, oku_system_error_destroyed);
	oku_system_guard(!window, oku_system_error_display);
	oku_system_guard(width <= 0 || height <= 0, oku_system_error_display);
	RGFW_window_resize(window, width, height);
	return 0;
}
