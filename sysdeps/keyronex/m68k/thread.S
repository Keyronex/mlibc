.section .text
.global __mlibc_thread_entry
__mlibc_thread_entry:
	#lea __mlibc_thread_trampoline-.-8,%a1
	#jsr (%pc,%a1)
	jbsr __mlibc_thread_trampoline@PLTPC

.section .note.GNU-stack,"",%progbits
