#include <system.h>
#include <error.h>
#include "common.h"

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

int main(void) {
	// тестирование деинициализации
	if(0==oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля до создания, прошло успешно, хтоя должно было выдать ошибку");
		return -1;
	}
	if(0!=oku_system_create(on_create, on_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение созданного модуля провалилось, хотя должно было пройти успешно");
		return -1;
	}
	if(0==oku_system_destroy()) {
		printf("%s\n", "[ошибка]: повторное уничтожение модуля прошло успешно, хотя должно было провалиться");
		return -1;
	}
	return 0;
}
