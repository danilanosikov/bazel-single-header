#ifndef oku_system_error
typedef enum {
	oku_system_success = 0,
	oku_system_error_initialization = -1,
	oku_system_error_memory = -2,
	oku_system_error_display_server = -3,
	oku_system_error_display_surface = -4,
	oku_system_error_display_listener = -5,
	oku_system_error_display_roundtrip = -5,
} oku_system_error;
#define oku_system_error oku_system_error
#endif
