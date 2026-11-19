#include <system.h>
#include <error.h>
#include "common.h"

/* тестовые хуки из тестовой сборки бэкенда */
int oku_system_test_display_hidden_get();
int oku_system_test_display_mode_get();
int oku_system_test_display_geometry_get(int *x, int *y, int *w, int *h);

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

int main(void) {
	// тестирование обычного режима окна
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	
	// Переводим в эксклюзивный полноэкранный режим для проверки взаимоисключения
	if(0!=oku_system_display_fullscreen()) {
		printf("%s\n", "[ошибка]: не удалось войти в эксклюзивный полноэкранный режим");
		oku_system_destroy();
		return -1;
	}
	
	int mode = oku_system_test_display_mode_get();
	if(mode < 0) {
		printf("%s\n", "[ошибка]: не удалось получить режим окна после полноэкранного режима");
		oku_system_destroy();
		return -1;
	}
	if(mode != 1) {
		printf("%s\n", "[ошибка]: режим не соответствует эксклюзивному полноэкранному");
		oku_system_destroy();
		return -1;
	}
	
	// Переход к обычному режиму окна
	if(0!=oku_system_display_windowed()) {
		printf("%s\n", "[ошибка]: не удалось перейти в обычный режим окна");
		oku_system_destroy();
		return -1;
	}
	
	mode = oku_system_test_display_mode_get();
	if(mode < 0) {
		printf("%s\n", "[ошибка]: не удалось получить режим окна после обычного режима");
		oku_system_destroy();
		return -1;
	}
	if(mode != 0) {
		printf("%s\n", "[ошибка]: обычный режим окна не восстановлен");
		oku_system_destroy();
		return -1;
	}
	
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}