#ifndef oku__system
	#ifndef okd__stdlib
		#include <stdlib.h>
		#define okd__stdlib
	#endif

	// подготавливает модуль к работе
	int oku_system_create(size_t memory);
	// подготавливает модуль к завершению работы
	int oku_system_destroy();
	// обновляет состояние модуля и опрашивает его подсистемы
	int oku_system_update();



	// запрашивает память у модуля
	int oku_system_memory_get();
	// задаёт значение памяти
	int oku_system_memory_set();
	// отдаёт память обратно модулю 	
	int oku_system_memory_put();
	#define oku__system
#endif
