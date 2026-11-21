#include <okular/system/memory.h>
#include <common.h>

// проверка на первичный возврат памяти
int main(void)
{
	// резервация памяти
	unsigned long returned;
	static void* memory;

	// нельзя проверить возврат памяти, когда она не выделена
	memory = oku_system_memory_create(sample);
	if(!memory) return -__LINE__;

	// первичный возврат памяти
	returned	= oku_system_memory_destroy(memory, sample);

	// если произошла ошибка выделения памяти
	// выдать ошибку
	if(0>returned) return -__LINE__;

	// успрешное окончание тестирования
	return 0;
}
