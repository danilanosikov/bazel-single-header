#include <system.h>
#include <error.h>

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

/* память */
int oku_system_memory_create(size_t bytes) {
	if(initialized) return oku_system_error_initialized;

	static void* result;
	result = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(result == MAP_FAILED) return oku_system_error_memory;

	mem=result;
	result = 0;
	mem_size = bytes;
	return 0;
}
int oku_system_memory_destroy() {
	if(!initialized) return oku_system_error_uninitialized;

	static int result;
	result = munmap(mem, mem_size);
	if(result != 0) return oku_system_error_memory;

	result = 0;
	mem_size = 0;
	return 0;
}
