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
	// тестирование скрытия окна
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	
	int hidden = oku_system_test_display_hidden_get();
	if(hidden < 0) {
		printf("%s\n", "[ошибка]: не удалось получить состояние окна до скрытия");
		oku_system_destroy();
		return -1;
	}
	if(hidden != 0) {
		printf("%s\n", "[ошибка]: окно было скрыто при создании");
		oku_system_destroy();
		return -1;
	}
	
	if(0!=oku_system_display_hide()) {
		printf("%s\n", "[ошибка]: не удалось скрыть окно");
		oku_system_destroy();
		return -1;
	}
	
	hidden = oku_system_test_display_hidden_get();
	if(hidden < 0) {
		printf("%s\n", "[ошибка]: не удалось получить состояние окна после скрытия");
		oku_system_destroy();
		return -1;
	}
	if(hidden != 1) {
		printf("%s\n", "[ошибка]: окно не скрылось после вызова скрытия");
		oku_system_destroy();
		return -1;
	}
	
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}