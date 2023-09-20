
.global _start
_start:
	lea relocateSelf-.-8,%a1
	jsr (%pc,%a1)
	pea.l (%a0)
	lea interpreterMain-.-8,%a1
	jsr (%pc,%a1)

.section .note.GNU-stack,"",%progbits
