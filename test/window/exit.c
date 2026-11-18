#include <system.h>
#include <error.h>
#include "common.h"

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

/* тестовый хук из тестовой сборки бэкенда: нажатие кнопки закрытия окна */
int oku_system_test_display_close();

static int exited = 0;

static int on_exit_update() {
	int result = on_update();
	if(result==oku_system_error_exit) exited = 1;
	return result;
}

int main(void) {
	if(0!=oku_system_create(on_create, on_exit_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось");
		return -1;
	}
	// имитация нажатия на кнопку закрытия окна
	if(0!=oku_system_test_display_close()) {
		printf("%s\n", "[ошибка]: не удалось имитировать закрытие окна");
		return -1;
	}
	if(oku_system_error_exit!=oku_system_display_update()) {
		printf("%s\n", "[ошибка]: закрытие окна не вернуло событие выхода");
		return -1;
	}
	// модуль должен считать событие выхода успешным обновлением
	if(0!=oku_system_update()) {
		printf("%s\n", "[ошибка]: событие выхода провалило обновление модуля");
		return -1;
	}
	if(!exited) {
		printf("%s\n", "[ошибка]: событие выхода не дошло до модуля");
		return -1;
	}
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}
