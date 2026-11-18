#include <system.h>
#include <error.h>
#include "common.h"

#include <signal.h>

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

/* тестовый хук из тестовой сборки бэкенда: нажатие кнопки закрытия окна */
int oku_system_test_display_close();

static int user_exit = 0;

static int on_exit_update() {
	if(user_exit) return oku_system_exit_user;
	return on_update();
}

int main(void) {
	if(0!=oku_system_create(on_create, on_exit_update, on_destroy)) {
		printf("%s\n", "[ошибка]: создание модуля провалилось");
		return -1;
	}
	if(0!=oku_system_exit_state_get()) {
		printf("%s\n", "[ошибка]: флаги выхода установлены до обновления");
		return -1;
	}
	// имитация нажатия на кнопку закрытия окна
	if(0!=oku_system_test_display_close()) {
		printf("%s\n", "[ошибка]: не удалось имитировать закрытие окна");
		return -1;
	}
	if(oku_system_exit_window!=oku_system_display_update()) {
		printf("%s\n", "[ошибка]: закрытие окна не вернуло причину выхода");
		return -1;
	}
	if(!(oku_system_exit_state_get() & oku_system_exit_window)) {
		printf("%s\n", "[ошибка]: флаг закрытия окна не выставлен");
		return -1;
	}
	int reason = oku_system_update();
	if(!(reason & oku_system_exit_window)) {
		printf("%s\n", "[ошибка]: обновление не вернуло закрытие окна");
		return -1;
	}
	// выход из самой реализации on_update должен отличаться от кнопки окна
	user_exit = 1;
	reason = oku_system_update();
	if(!(reason & oku_system_exit_user) || (reason & oku_system_exit_signal)) {
		printf("%s\n", "[ошибка]: выход из on_update не определён");
		return -1;
	}
	// сигнал приходит асинхронно и должен фиксироваться без опроса подсистем
	if(0!=raise(SIGTERM)) {
		printf("%s\n", "[ошибка]: не удалось отправить SIGTERM");
		return -1;
	}
	if(!(oku_system_exit_state_get() & oku_system_exit_signal)) {
		printf("%s\n", "[ошибка]: сигнал не выставил флаг выхода");
		return -1;
	}
	reason = oku_system_update();
	if(!(reason & oku_system_exit_signal)) {
		printf("%s\n", "[ошибка]: обновление не вернуло сигнал");
		return -1;
	}
	if(0!=oku_system_destroy()) {
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}
