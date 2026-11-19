#ifndef oku__system
	#ifndef okd__stdlib
		#include <stdlib.h>
		#define okd__stdlib
	#endif

	/* проверки состояния модуля: включаются только в тестовой сборке (//library:library_test) */
	/* Внешний if/else нужен только для того, чтобы макрос был одним оператором
	   в любом контексте: else без скобок «поглощает» точку с запятой вызова. */
	#ifdef oku_system_test
		#define oku_system_assert(condition, error) \
			if (1) { \
				if (condition) { \
					return error; \
				} \
			} else (void)0
	#else
		#define oku_system_assert(condition, error) ((void)0)
	#endif

	/* модуль */
	// состояние инициализации модуля
	extern bool created;

	// вызоваемая функция: 0 - продолжить, oku_system_exit_* - причина выхода, <0 - ошибка
	typedef typeof(int(void)) *callback;

	// причины выхода: битовые флаги, проверяются одним сравнением
	typedef enum {
		oku_system_exit_none   = 0,
		oku_system_exit_error  = 1u << 0, // ошибка подсистемы
		oku_system_exit_input  = 1u << 1, // escape / ввод пользователя
		oku_system_exit_signal = 1u << 2, // SIGTERM, SIGINT, SIGHUP
		oku_system_exit_window = 1u << 3, // кнопка закрытия окна
		oku_system_exit_user   = 1u << 4, // выход запрошен из on_update
		oku_system_exit_all    = (1u << 5) - 1,
	} oku_system_exit;

	typedef unsigned oku_system_exit_state;

	// текущие флаги выхода: одно relaxed-чтение, 0 - выхода нет
	oku_system_exit_state oku_system_exit_state_get();
	// выставить флаг выхода (безопасно из обработчика сигнала)
	void oku_system_exit_raise(oku_system_exit flag);

	// подготавливает модуль к работе
	int oku_system_create(callback on_create, callback on_update, callback on_destroy);
	// подготавливает модуль к завершению работы
	int oku_system_destroy();
	// обновляет состояние модуля и опрашивает его подсистемы
	int oku_system_update();







	/* память */
	int oku_system_memory_create(size_t bytes);
	int oku_system_memory_destroy();
	// запрашивает память у модуля, возвращает номер куска памяти или ошибку
	int oku_system_memory_reserve(unsigned int bytes, size_t chunk_size_in_bytes);
	// отдаёт память обратно модулю 	
	int oku_system_memory_return(int segment);
	// работа с памятью как с кучей
	int oku_system_memory_heap_put(int segment, int offset, void *buffer);
	int oku_system_memory_heap_get_last(int segment, void *buffer);
	int oku_system_memory_heap_get_first(int segment, void *buffer);
	int oku_system_memory_heap_get(int segment, int offset, void *buffer);
	int oku_system_memory_heap_set(int segment, int offset, void *buffer);
	int oku_system_memory_heap_pop(int segment, int offset);
	// работа с памятью как со стопкой
	int oku_system_memory_stack_put(int segment, void *buffer);
	int oku_system_memory_stack_get_last(int segment, void *buffer);
	int oku_system_memory_stack_get_first(int segment, void *buffer);
	int oku_system_memory_stack_get(int segment, int offset, void *buffer);
	int oku_system_memory_stack_set(int segment, void *buffer);
	int oku_system_memory_stack_pop(int segment);
	// работа с памятью как с очередью
	int oku_system_memory_queue_put(int segment, void *buffer);
	int oku_system_memory_queue_get_first(int segment, void *buffer);
	int oku_system_memory_queue_get_last(int segment, void *buffer);
	int oku_system_memory_queue_get(int segment, int offset, void *buffer);
	int oku_system_memory_queue_set(int segment, void *buffer);
	int oku_system_memory_queue_pop(int segment);

	/* вывод */
	int oku_system_display_create();
	int oku_system_display_update();
	int oku_system_display_destroy();
	int oku_system_display_show();
	int oku_system_display_hide();
	int oku_system_display_fullscreen();
	int oku_system_display_windowed();
	int oku_system_display_borderless();
	int oku_system_display_move(int x, int y);
	int oku_system_display_size(int width, int height);

	/* ввод */
	int oku_system_input_create();
	int oku_system_input_update();
	int oku_system_input_destroy();
	#define oku__system
#endif
