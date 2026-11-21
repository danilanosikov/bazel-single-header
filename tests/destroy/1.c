#include <okular/system/memory.h>
#include <common.h>

// проеврка передачи некорректных адресов
int main(void)
{
	// резервация памяти
	unsigned long returned;
	static void *memory;

	// задаём заведомо неверный адрес
	void* address = ((void*)(int*)0);

	// нельзя проверить возврат памяти, когда она не выделена
	memory = oku_system_memory_create(sample);
	if(!memory) return -__LINE__;

	// передаём неверную ссылку
	returned	= oku_system_memory_destroy(address, sample);
	if(0>=returned) return -__LINE__;

	return 0;
}
