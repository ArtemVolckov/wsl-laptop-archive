bits	64
;	Insertion sort
section	.data
n:
	dd	10
mas:
	dd	8, 7, 1, 9, 5, 2, 6, 0, 4, 3
section	.text
global	_start
_start:
	mov	ebx, mas
	mov	ecx, [n]
	dec	ecx
	jle	m4
	xor	edi, edi
m1:
	inc	edi
	mov	eax, [rbx+rdi*4]
	mov	esi, edi
m2:
	dec	esi
	js	m3
	cmp	eax, [rbx+rsi*4]
	jge	m3
	mov	edx, [rbx+rsi*4]
	mov	[rbx+rsi*4+4], edx
	jmp	m2
m3:
	inc	esi
	mov	[rbx+rsi*4], eax
	loop	m1
m4:
	mov	eax, 60
	mov	edi, 0
	syscall