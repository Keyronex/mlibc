
#include <sys/random.h>
#include <bits/ensure.h>

#include <mlibc/debug.hpp>
#include <mlibc/posix-sysdeps.hpp>

#include <errno.h>

ssize_t getrandom(void *buffer, size_t max_size, unsigned int flags) {
	if(flags & ~(GRND_RANDOM | GRND_NONBLOCK)) {
		errno = EINVAL;
		return -1;
	}
	if(!mlibc::sys_getentropy) {
		MLIBC_MISSING_SYSDEP();
		errno = ENOSYS;
		return -1;
	}
	if(int e = mlibc::sys_getentropy(buffer, max_size); e) {
		errno = e;
		return -1;
	}
	return max_size;
}

