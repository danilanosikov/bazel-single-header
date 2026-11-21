#include <okular/system/memory.h>
#include <common.h>

// проверка ошибки при передаче несоответствующего размера зарезервированной памяти возвращённой
int main(void)
{
	unsigned long returned;
	static void *memory;

	// нельзя проверить возврат памяти, когда она не выделена
	memory = oku_system_memory_create(sample);
	if(!memory) return -__LINE__;

	// количество выделенной и возвращённой памяти совпадают, хотя передано неверное значение
	returned = oku_system_memory_destroy(memory, sample+1);
	if(sample==returned) return -__LINE__;

	return 0;
}
