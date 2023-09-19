.section .text
.global __mlibc_start_thread
__mlibc_start_thread:
jsr __mlibc_thread_trampoline ; Call __mlibc_thread_trampoline