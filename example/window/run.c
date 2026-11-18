#include <system.h>
#include <error.h>

#ifndef okd__stdio
	#include <stdio.h>
	#define okd__stdio
#endif

int create()
{
	if (0>oku_system_memory_create(4096)) return oku_system_error_memory;
	if (0>oku_system_display_create()) return oku_system_error_display;
	if (0>oku_system_input_create()) return oku_system_error_input;
	return 0;	
}
int update()
{
	// if (0>oku_system_memory_update()) return oku_system_error_memory;
	if (0>oku_system_display_update()) return oku_system_error_display;
	if (0>oku_system_input_update()) return oku_system_error_input;
	return 0;	
}
int destroy()
{
	if (0>oku_system_memory_destroy()) return oku_system_error_memory;
	if (0>oku_system_display_destroy()) return oku_system_error_display;
	if (0>oku_system_input_destroy()) return oku_system_error_input;
	return 0;	
}


int main(void)
{
	if(0!=oku_system_create(create, update, destroy))
	{
		printf("%s\n", "[ошибка]: создание модуля провалилось");
		return -1;
	}
	while(true)
	{
		switch(oku_system_update()) {
			case 0: case oku_system_error_exit: goto loop;
			default: goto exit;
		}
		loop:
	}
	exit:

	if(0!=oku_system_destroy())
	{
		printf("%s\n", "[ошибка]: уничтожение модуля провалилось");
		return -1;
	}
	return 0;
}
