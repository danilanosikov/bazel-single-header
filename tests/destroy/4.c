#include <okular/system/memory.h>
#include <common.h>

// проверка соответствия размеров освобождённой и зарезервированной памятей
int main(void)
{
	unsigned long returned;
	static void *memory;

	// нельзя проверить возврат памяти, когда она не выделена
	memory = oku_system_memory_create(sample);
	if(!memory) return -__LINE__;

	// количество выделенной и возвращённой памяти не совпадают
	returned = oku_system_memory_destroy(memory, sample);
	if(sample!=returned) return -__LINE__;

	// успешное завершение тестирования
	return 0;
}
