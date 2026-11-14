#include <system.h>

#ifndef okd__sys_mman
	#include <sys/mman.h>
	#define okd__sys_mman
#endif
#ifndef okd__stdlib
	#include <stdlib.h>
	#define okd__stdlib
#endif
static void* mem;
static size_t mem_size;
static bool initialized = false;

int oku_system_create(size_t memory)
{
	static void* result;

	if(initialized) return -1;

	// memory
	result = mmap(NULL, memory, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(result == MAP_FAILED) return -2;
	mem=result;
	result = 0;
	mem_size = memory;

	initialized = true;
	return 0;
}

int oku_system_destroy()
{
	static int result;

	if(!initialized) return -1;

	// memory
	result = munmap(mem, mem_size);
	if(result != 0) return -2;
	result = 0;
	mem_size = 0;

	initialized = false;
	return 0;
}

int oku_system_update()
{
	if(!initialized) return -1;
	return 0;
}

int oku_system_memory_get()
{
	if(!initialized) return -1;
	return 0;
}
int oku_system_memory_set()
{
	if(!initialized) return -1;
	return 0;
}
int oku_system_memory_put()
{
	if(!initialized) return -1;
	return 0;
}
