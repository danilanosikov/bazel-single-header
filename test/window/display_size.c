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
	// тестирование изменения размера окна
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	
	if(0!=oku_system_display_size(640, 480)) {
		printf("%s\n", "[ошибка]: не удалось изменить размер окна");
		oku_system_destroy();
		return -1;
	}
	
	int x = 0, y = 0, w = 0, h = 0;
	int result = oku_system_test_display_geometry_get(&x, &y, &w, &h);
	if(result < 0) {
		printf("%s\n", "[ошибка]: не удалось получить геометрию окна после изменения размера");
		oku_system_destroy();
		return -1;
	}
	
	if(w != 640 || h != 480) {
		printf("%s\n", "[ошибка]: размер окна не совпадает с запрошенным");
		oku_system_destroy();
		return -1;
	}
	
	// Проверка валидации аргументов - попытка установить нулевой размер
	int error_result = oku_system_display_size(0, 480);
	if(error_result != oku_system_error_display) {
		printf("%s\n", "[ошибка]: некорректный размер окна не был отклонён");
		oku_system_destroy();
		return -1;
	}
	
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}