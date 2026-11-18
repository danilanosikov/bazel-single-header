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
	if(created) return oku_system_error_initialized;

	static void* result;
	result = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(result == MAP_FAILED) return oku_system_error_memory;

	mem=result;
	result = 0;
	mem_size = bytes;
	return 0;
}
int oku_system_memory_destroy() {
	if(!created) return oku_system_error_uninitialized;

	static int result;
	result = munmap(mem, mem_size);
	if(result != 0) return oku_system_error_memory;

	result = 0;
	mem_size = 0;
	return 0;
}

// запрашивает память у модуля, возвращает номер куска памяти или ошибку
int oku_system_memory_reserve(unsigned int bytes, size_t chunk_size_in_bytes) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}

// отдаёт память обратно модулю 	
int oku_system_memory_return(int segment) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}

// работа с памятью как с кучей
int oku_system_memory_heap_put(int segment, int offset, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_heap_get_last(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_heap_get_first(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_heap_get(int segment, int offset, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_heap_set(int segment, int offset, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_heap_pop(int segment, int offset) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}

// работа с памятью как со стопкой
int oku_system_memory_stack_put(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_stack_get_last(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_stack_get_first(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_stack_get(int segment, int offset, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_stack_set(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_stack_pop(int segment) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}

// работа с памятью как с очередью
int oku_system_memory_queue_put(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_queue_get_first(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_queue_get_last(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_queue_get(int segment, int offset, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_queue_set(int segment, void *buffer) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
int oku_system_memory_queue_pop(int segment) {
	if(!created) return oku_system_error_uninitialized;
	return 0;
}
