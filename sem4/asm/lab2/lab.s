bits    64
;	Shaker sort
;   Sorting columns of matrix by min elements
section .data
n:
        dq      3
m:
        dq      4

matrix_1:
        dq      -4, 0, 3, 6
        dq      9, -4, 10, 1
        dq      6, 8, 6, -2

matrix_2:
        dq      0, 0, 0, 0
        dq      0, 0, 0, 0
        dq      0, 0, 0, 0

sum:
        dq      0, 0, 0, 0
adress:
	dq	0, 1, 2, 3
section .text
global  _start
_start:
        mov     rcx, [m]
        cmp     rcx, 1
        jle     m15
        mov     rbx, matrix_1
	mov rcx, [m]
        xor rdi, rdi
        xor rsi, rsi
m1:
	mov rax, [rbx]
	mov rcx, [n]
	dec rcx
	test rcx, rcx
	jz m15
	mov rdi, 0
m2:
	mov rcx, [n]
	dec rcx
	mov rax, [matrix_1 + rdi*8]
	mov r9, rdi
        mov rdx, [m]
    	add rdx, rdi
m3:
	mov rbx, [matrix_1 + rdx*8]
	add rdx, [m]
	add rax, rbx
	mov [sum + rdi*8], rax
	loop m3
	add rdi, 1
	cmp [m], rdi
	jne m2
        mov rcx, [m]
        sub rcx, 1
m4:
	xor rsi,rsi
	mov rdi, [m]
	sub rdi, rcx
	mov rax, [sum + 8*rdi]
	mov r9, rdi
	mov rdx, rdi
	dec rdx
m5:
	cmp rdx, rsi
	js m8
	;je m8
	mov r10, rdx
	add r10, rsi
	shr r10, 1
	cmp [sum + 8*r10], rax
	js m7
	je m7
	jmp m6

m6:
	dec r10
	mov rdx, r10
	jmp m5

m7:
	inc r10
	mov rsi, r10
	jmp m5

m8:
        mov r10, rcx
        mov rdx, rsi
	mov rbx, rdi
	sub rbx, rdx
	mov rcx, rbx
	mov r8, rdi
m9:
	test rcx, rcx
	js m10
	jz m10
	mov rdx, [sum + r8*8 - 8]
	mov [sum + r8*8], rdx
        mov rdx, [adress + r8*8 - 8]
        mov [adress + r8*8], rdx
	dec r8
	loop m9
m10:
	mov rcx, r10
	mov [sum + 8*rsi], rax
	mov [adress + 8*rsi], r9
	inc rdi
	dec rcx
	test rcx, rcx
	jnz m4
	mov rcx, [m]
	mov rdi, 0
m11:
	mov rax, [sum + 8*rdi]
	inc rdi
	loop m11
	;mov rcx, [m]
	;mov rdi, 0
	;l2:
	;	mov rax, [adress + 8*rdi]
	;	inc rdi
	;	loop l2
	mov rcx, [m]
	mov rdi, 0
m12:
	mov rax, [adress + 8*rdi]
	mov r10, rcx
	mov r9, rdi
	mov r8, rax
	mov rcx,[n]
	l3:
		mov rbx, [matrix_1 + 8*r8]
		mov [matrix_2 + 8*rdi], rbx
		add r8, [m]
		add rdi, [m]
		loop l3
	mov rdi, r9
	mov rcx, r10
	inc rdi
	loop m12
	mov rcx, [m]
	mov rdi, 0
m13:
	mov r9, rcx
	mov r10, rdi
	mov rcx, [n]
	l4:
		 mov rax, [matrix_2 + 8*rdi]
		 add rdi, [m]
		 loop l4
	mov rcx, r9
	mov rdi, r10
	inc rdi
	loop m13
m14:
	mov rax, 60
	mov rbx, 0
	syscall
m15:
	mov rax, 60
	mov rbx, 1
	syscall
