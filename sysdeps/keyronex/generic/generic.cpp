#include <asm/ioctls.h>

#include <bits/ensure.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <frg/logging.hpp>
#include <keyronex/syscall.h>
#include <limits.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/debug.hpp>
#include <stdlib.h>

#include "abi-bits/vm-flags.h"
#include "mlibc/tcb.hpp"

#define STUB_ONLY                                           \
	{                                                   \
		__ensure(!"STUB_ONLY function was called"); \
		__builtin_unreachable();                    \
	}

namespace mlibc {

void
sys_libc_log(const char *message)
{
	syscall1(kKrxDebugMessage, (uintptr_t)message, NULL);
}

[[noreturn]] void
sys_libc_panic()
{
	sys_libc_log("\nMLIBC PANIC\n");
	for (;;)
		;
}

int sys_tcb_set(void *pointer)
{
#if defined(__m68k__)
	syscall1(kKrxTcbSet, (uintptr_t)pointer + 0x7000 + sizeof(Tcb), NULL);
#elif defined(__amd64__)
	syscall1(kKrxTcbSet, (uintptr_t)pointer, NULL);
#elif defined(__aarch64__)
	uintptr_t addr = reinterpret_cast<uintptr_t>(pointer);
	addr += sizeof(Tcb) - 0x10;
	asm volatile("msr tpidr_el0, %0" ::"r"(addr));
#endif
	return 0;
}

[[gnu::weak]] void *sys_tp_get()
{
	return (void*)syscall0(kKrxTcbGet, NULL);
}

extern "C" void *__m68k_read_tp (void)
{
	return sys_tp_get();
}

[[gnu::weak]] int sys_futex_tid()
{
	return syscall0(kKrxGetTid, NULL);
}

int sys_futex_wait(int *pointer, int expected, const struct timespec *time)
{
	(void)time;
	return -syscall3(kKrxFutexWait, (uintptr_t)pointer, expected, 0, NULL);
}

int sys_futex_wake(int *pointer)
{
	return -syscall1(kKrxFutexWake, (uintptr_t)pointer, NULL);
}

[[noreturn]] void sys_exit(int status)
{
	(void)status;
	syscall0(kKrxThreadExit, NULL);
	sys_libc_panic();
}

int sys_anon_allocate(size_t size, void **pointer)
{
	int r;
	uintptr_t out;
	r = syscall1(kKrxVmAllocate, size, &out);
	if (r == 0) {
		*pointer = (void*)out;
		return 0;
	}
	return -r;
}

int sys_anon_free(void *pointer, size_t size)
{
	(void)pointer;
	(void)size;
	STUB_ONLY
}

int sys_open(const char *pathname, int flags, mode_t mode, int *fd)
{
	(void)flags;
	(void)mode;
	int r = syscall1(kKrxFileOpen, (uintptr_t)pathname, NULL);
	if (r >= 0) {
		*fd = r;
		return 0;
	}
	return -r;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read)
{
	int r = syscall3(kKrxFileReadCached, fd, (uintptr_t)buf, count, NULL);
	if (r >= 0) {
		*bytes_read = r;
		return 0;
	}
	return -r;
}

int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written)
{
	int r = syscall3(kKrxFileWriteCached, fd, (uintptr_t)buf, count, NULL);
	if (r >= 0) {
		*bytes_written = r;
		return 0;
	}
	return -r;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset)
{
	off_t r = syscall3(kKrxFileSeek, fd, offset, whence, NULL);
	if (r >= 0) {
		*new_offset = r;
		return 0;
	}
	return -r;
}

int sys_close(int fd)
{
	int r = syscall1(kKrxFileClose, fd, NULL);
	return 0;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window)
{
	uintptr_t addr;
	int r = syscall6(kKrxVmMap, (uintptr_t)hint, size, prot,
	    flags, fd, offset, &addr);
	if (r == 0) {
		*window = (void *)addr;
		return 0;
	}
	return -r;
}


int sys_vm_unmap(void *pointer, size_t size)
{
	STUB_ONLY
}

int sys_clock_get(int clock, time_t *secs, long *nanos)
{
	STUB_ONLY
}

} // namespace mlibc
