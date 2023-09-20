#pragma once

#include <stdint.h>
#include <mlibc/tcb.hpp>

namespace mlibc {

inline Tcb *get_current_tcb() {
	uintptr_t ptr = 0;
	asm ("illegal");
	return (Tcb *)ptr;
}

inline uintptr_t get_sp() {
	uintptr_t sp;
	asm ("move.l %%sp, %0" : "=r"(sp));
	return sp;
}

} // namespace mlibc
