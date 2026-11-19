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
	// тестирование перемещения окна
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	
	if(0!=oku_system_display_move(120, 80)) {
		printf("%s\n", "[ошибка]: не удалось переместить окно");
		oku_system_destroy();
		return -1;
	}
	
	int x = 0, y = 0, w = 0, h = 0;
	int result = oku_system_test_display_geometry_get(&x, &y, &w, &h);
	if(result < 0) {
		printf("%s\n", "[ошибка]: не удалось получить геометрию окна после перемещения");
		oku_system_destroy();
		return -1;
	}
	
	if(x != 120 || y != 80) {
		printf("%s\n", "[ошибка]: координаты окна не совпадают с запрошенными");
		oku_system_destroy();
		return -1;
	}
	
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}