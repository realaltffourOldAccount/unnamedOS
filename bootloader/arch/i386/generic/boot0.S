	.code16
	.globl _start, start;
_start:
	jmp .

	.space 510-(.-_start)
	.word 0xaa55
