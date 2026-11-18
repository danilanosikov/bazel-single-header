#include <system.h>
#include <error.h>
#include "common.h"

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

int main(void) {
	// тестирование обновления
	if(0==oku_system_update()) {
		printf("%s\n", "[ошибка]: обновление не выдало ошибку, хотя модуль ещё не инициализирован");
		return -1;
	}
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось");
		return -1;
	}
	// цикл вызовов обновления организует вызывающая сторона
	if(0!=oku_system_update()) {
		printf("%s\n", "[ошибка]: обновление отображения провалилось");
		return -1;
	}
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}
