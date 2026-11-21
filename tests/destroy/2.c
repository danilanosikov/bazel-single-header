#include <okular/system/memory.h>
#include <common.h>

// проверка поведения функции destroy при вторичном вызове без предварительной отчистки
int main(void)
{
	// резервация памяти
	static const int sample = sizeof(int);
	unsigned long returned;
	static void *memory;

	// нельзя проверить возврат памяти, когда она не выделена
	memory = oku_system_memory_create(sample);
	if(!memory) return -__LINE__;

	// первичное освобождение, не проверяется
	oku_system_memory_destroy(memory, sample);

	// вторичный вызов
	returned = oku_system_memory_destroy(memory, sample);

	// память не была отдана, но функция не сообщила об этом
	if(0>=returned) return -__LINE__;

	return 0;
}
