#ifndef MLIBC_ARCH_DEFS_HPP
#define MLIBC_ARCH_DEFS_HPP

#include <stddef.h>

namespace mlibc {

/* this isn't actually true; it can be 4k or 8k on 68040, and more on 030! */
inline constexpr size_t page_size = 0x1000;

} // namespace mlibc

#endif // MLIBC_ARCH_DEFS_HPP
