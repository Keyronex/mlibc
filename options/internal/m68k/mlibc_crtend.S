
.hidden __mlibc_do_ctors
.hidden __mlibc_do_dtors

.section .init
	lea __mlibc_do_ctors-.-8,%a1
	jsr (%pc,%a1)
	rts

.section .fini
	lea __mlibc_do_dtors-.-8,%a1
	jsr (%pc,%a1)
	rts

.section .ctors
.hidden __CTOR_END__
.global __CTOR_END__
__CTOR_END__:

.section .dtors
.hidden __DTOR_END__
.global __DTOR_END__
__DTOR_END__:

.section .note.GNU-stack,"",%progbits
