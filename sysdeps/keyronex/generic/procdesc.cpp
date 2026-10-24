#include <keyronex/syscall.h>


#include <mlibc/all-sysdeps.hpp>
#include <mlibc/debug.hpp>
#include <mlibc/tcb.hpp>

namespace mlibc {

int
Sysdeps<Pdfork>::operator()(int *fdp, int flags, pid_t *child)
{
	int r = syscall2(SYS_pdfork, (uintptr_t)fdp, flags, NULL);
	if (r < 0)
		return -r;
	*child = r;
	return 0;
}

int
Sysdeps<Pdkill>::operator()(int fd, int sig)
{
	int r = syscall2(SYS_pdkill, fd, sig, NULL);
	if (r < 0)
		return -r;
	return 0;
}

int
Sysdeps<Pdwait>::operator()(int fd, int *status, int options, struct __wrusage *rusage, siginfo_t *info)
{
	int r = syscall5(SYS_pdwait, fd, (uintptr_t)status, options,
	    (uintptr_t)rusage, (uintptr_t)info, NULL);
	if (r < 0)
		return -r;
	return 0;
}

// int sys_pdgetpid(int fd, pid_t *pidp);
struct Pdgetpid {};

} // namespace mlibc