#include <okular/system/memory.h>
#include <common.h>

// проверка поведения функции destroy при вторичном вызове с предварительной отчисткой
int main(void)
{
	unsigned long returned0, returned1;
	static void *memory0, *memory1;

	// первичное выделение
	memory0 = oku_system_memory_create(sample);
	// вторичное выделение
	memory1 = oku_system_memory_create(sample);

	// нельзя проводить проверку если память не удалось выделить
	// так как нельзя гарантировать корректность теста в таком случае
	if(!memory0 || !memory1) return -__LINE__;

	// первичное освобождение
	returned0 = oku_system_memory_destroy(memory0, sample);

	// вторичное освобождение
	returned0 = oku_system_memory_destroy(memory1, sample);

	// отчистка памяти провалилась без предпосылок
	if(0>=returned0 || 0>=returned1) return -__LINE__;

	// успешное окончание тестирования
	return 0;
}
