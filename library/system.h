#ifndef oku__system
	#ifndef okd__stdlib
		#include <stdlib.h>
		#define okd__stdlib
	#endif

	/* проверки состояния модуля: включаются только в тестовой сборке (//library:library_test) */
	#ifdef oku_system_test
		#define oku_system_guard(condition, error) do { if(condition) return error; } while(0)
	#else
		#define oku_system_guard(condition, error) ((void)0)
	#endif

	/* модуль */
	// состояние инициализации модуля
	extern bool created;

	// вызоваемая функция
	typedef typeof(int(void)) *callback;

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
	int oku_system_display_move();
	int oku_system_display_size();

	/* ввод */
	int oku_system_input_create();
	int oku_system_input_update();
	int oku_system_input_destroy();
	#define oku__system
#endif
