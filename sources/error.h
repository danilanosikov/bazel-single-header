#ifndef oku_system_error
	#line 1
	enum {
		oku_system_error_initialized = -__LINE__,
		oku_system_error_uninitialized = -__LINE__,
		oku_system_error_memory = -__LINE__,
		oku_system_error_display = -__LINE__,
		oku_system_error_input = -__LINE__,
	};
	#line 0
	#define oku_system_error oku_system_error
#endif
