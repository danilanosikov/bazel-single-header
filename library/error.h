#ifndef oku_system_error
	#line 1
	enum {
		oku_system_error_created = -__LINE__,
		oku_system_error_destroyed  = -__LINE__,

		oku_system_error_creation = -__LINE__,
		oku_system_error_destruction = -__LINE__,

		oku_system_error_update = -__LINE__,
		oku_system_error_updated = -__LINE__,

		oku_system_error_exit = -__LINE__,
		oku_system_error_exited = -__LINE__,

		oku_system_error_memory = -__LINE__,
		oku_system_error_display = -__LINE__,
		oku_system_error_input = -__LINE__,

		oku_system_error_last = -__LINE__,
	};
	#line 0

	#define oku_system_error_initialization oku_system_error_creation
	#define oku_system_error_initialized oku_system_error_created
	#define oku_system_error_deinitialization oku_system_error_destruction
	#define oku_system_error_deinitialized oku_system_error_destroyed
	#define oku_system_error_uninitialization oku_system_error_destruction
	#define oku_system_error_uninitialized oku_system_error_destroyed
	#define oku_system_error_tick oku_system_error_update
	#define oku_system_error_ticked oku_system_error_updated

	#define oku_system_error_max oku_system_error_last

	#define oku_system_error oku_system_error
#endif
