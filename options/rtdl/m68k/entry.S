
#define LEA_LCL(name,reg)	lea	(name,%pc),reg
#define GOT_SETUP(reg)		lea	(_GLOBAL_OFFSET_TABLE_@GOTPC,%pc),reg

.global _start
_start:
#	lea	(_GLOBAL_OFFSET_TABLE_@GOTPC,%pc),%a0
#	lea relocateSelf-.-8,%a1
#	jsr (%pc,%a1)
	GOT_SETUP(%a0)
	LEA_LCL(_DYNAMIC,%a1)

	movel	%a1,%a5
	subl	(%a0),%a5

	movel	%a5,-(%sp)		| relocbase
	movel	%a1,-(%sp)		| &_DYNAMIC
	jbsr	_rtld_relocate_nonplt_self@PLTPC
	addql	#8,%sp			| pop arguments

	#pea.l (%a0)
	MOVE.L %sp, -(%sp)
	lea interpreterMain-.-8,%a1
	jsr (%pc,%a1)

.section .note.GNU-stack,"",%progbits
