#ifndef oku__error
	#define oku__error

	#line 1
	enum {
		oku_system_error_created = -__LINE__,
		oku_system_error_destroyed  = -__LINE__,

		oku_system_error_creation = -__LINE__,
		oku_system_error_destruction = -__LINE__,

		oku_system_error_update = -__LINE__,
		oku_system_error_updated = -__LINE__,

		oku_system_error_memory = -__LINE__,
		oku_system_error_display = -__LINE__,
		oku_system_error_input = -__LINE__,

		oku_system_error_last = -__LINE__,
	};
	#line 0
#endif
