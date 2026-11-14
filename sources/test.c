#include <system.h>

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

int main(void)
{
	// инициализация
	if(0==oku_system_destroy())
	{
		printf("%s\n", "[ошибка]: уничтожение модуля до создания, прошло успешно, хтоя должно было выдать ошибку");
		return -1;
	}
	if(0!=oku_system_create(4096))
	{
		printf("%s\n", "[ошибка]: создание модуля провалилось, хотя модуль ещё не создан");
		return -1;
	}
	if(0==oku_system_create(4096))
	{
		printf("%s\n", "[ошибка]: повторное создание модуля прошло успешно, хотя должно было провалиться");
		return -1;
	}


	// обновление
	// oku_system_update();

	// работа с памятью
	// oku_system_memory_get();
	// oku_system_memory_set();
	// oku_system_memory_put();


	// деинициализация
	if(0!=oku_system_destroy())
	{
		printf("%s\n", "[ошибка]: уничтожение созданного модуля провалилось, хотя должно было пройти успешно");
		return -1;
	}
	if(0==oku_system_destroy())
	{
		printf("%s\n", "[ошибка]: повторное уничтожение модуля прошло успешно, хотя должно было провалиться");
		return -1;
	}
	return 0;
}
