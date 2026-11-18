#include <system.h>
#include <error.h>

#include <signal.h>
#include <stdatomic.h>

_Static_assert(ATOMIC_INT_LOCK_FREE == 2, "exit state must be lock-free for signal handlers");

bool created = false;

static callback create;
static callback update;
static callback destroy;

static _Atomic oku_system_exit_state exit_state = 0;

#define exit_signals_count 3
static const int exit_signals[exit_signals_count] = { SIGTERM, SIGINT, SIGHUP };
static struct sigaction previous[exit_signals_count];
static int signals_installed = 0;

oku_system_exit_state oku_system_exit_state_get() {
	return atomic_load_explicit(&exit_state, memory_order_relaxed);
}

void oku_system_exit_raise(oku_system_exit flag) {
	atomic_fetch_or_explicit(&exit_state, flag, memory_order_relaxed);
}

static void on_exit_signal(int signal) {
	(void)signal;
	oku_system_exit_raise(oku_system_exit_signal);
}

static void install_signals() {
	struct sigaction action = {0};
	action.sa_handler = on_exit_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	while(signals_installed<exit_signals_count) {
		if(0!=sigaction(exit_signals[signals_installed], &action, &previous[signals_installed])) break;
		signals_installed++;
	}
}

static void restore_signals() {
	while(signals_installed>0) {
		signals_installed--;
		sigaction(exit_signals[signals_installed], &previous[signals_installed], NULL);
	}
}

int oku_system_create(callback on_create, callback on_update, callback on_destroy) {
	oku_system_guard(created, oku_system_error_created);
	create = on_create;
	update = on_update;
	destroy = on_destroy;
	atomic_store_explicit(&exit_state, oku_system_exit_none, memory_order_relaxed);
	install_signals();
	if(0>create()) {
		restore_signals();
		return oku_system_error_creation;
	}
	created = true;
	return 0;
}

int oku_system_destroy() {
	oku_system_guard(!created, oku_system_error_destroyed);
	if(0>destroy()) return oku_system_error_destruction;
	created = false;
	restore_signals();
	return 0;
}

int oku_system_update() {
	oku_system_guard(!created, oku_system_error_destroyed);

	int result = update();
	if(result>0) oku_system_exit_raise(result & oku_system_exit_all);
	else if(result<0) {
		oku_system_exit_raise(oku_system_exit_error);
		if(0>oku_system_destroy()) return oku_system_error_destruction;
		return oku_system_exit_error;
	}
	return (int)oku_system_exit_state_get();
}
