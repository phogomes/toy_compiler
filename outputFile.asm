extern printf
extern scanf

SECTION .data

str0: db "%d",10, 0
str1: db "%s",10, 0
strin0: db "%d", 0
strin1: db "%s", 0

gato: dq 0
macaco: dq 0
abacate: dq 0
i: dq 0
nome: db ''


SECTION .codigo
global main
main:

	push rbp

	mov rax,gato
	mov rdi, strin0
	mov rsi,rax
	call scanf


	mov rax,macaco
	mov rdi, strin0
	mov rsi,rax
	call scanf


	mov rax,abacate
	mov rdi, strin0
	mov rsi,rax
	call scanf


	mov rax,nome
	mov rdi, strin1
	mov rsi,rax
	call scanf


	mov rdi, str1
	mov rsi,nome
	mov rax,0
	call printf


	mov rax,[macaco]
	push rax


	pop rax
	mov rbx,[gato]
	cmp rbx,rax
	jle label0
	push 1
	jmp label1
label0:
	push 0
label1:

	pop rax
	cmp rax, 0
	jz label2

	mov rax,[abacate]
	push rax


	pop rax
	mov rbx,[gato]
	cmp rbx,rax
	jle label4
	push 1
	jmp label5
label4:
	push 0
label5:

	pop rax
	cmp rax, 0
	jz label6

	mov rax,[abacate]
	push rax


	pop rax
	mov rbx,[macaco]
	cmp rbx,rax
	jle label8
	push 1
	jmp label9
label8:
	push 0
label9:

	pop rax
	cmp rax, 0
	jz label10

	mov rax,[abacate]
	push rax

	pop rax
	mov [i],rax

label12:

	mov rax,[gato]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label14
	push 1
	jmp label15
label14:
	push 0
label15:

	pop rax
	cmp rax, 0
	jz label13

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label12
label13:

	jmp label11
label10:

	mov rax,[macaco]
	push rax

	pop rax
	mov [i],rax

label16:

	mov rax,[gato]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label18
	push 1
	jmp label19
label18:
	push 0
label19:

	pop rax
	cmp rax, 0
	jz label17

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label16
label17:

label11:

	jmp label7
label6:

	mov rax,[macaco]
	push rax

	pop rax
	mov [i],rax

label20:

	mov rax,[abacate]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label22
	push 1
	jmp label23
label22:
	push 0
label23:

	pop rax
	cmp rax, 0
	jz label21

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label20
label21:

label7:

	jmp label3
label2:

	mov rax,[abacate]
	push rax


	pop rax
	mov rbx,[macaco]
	cmp rbx,rax
	jle label24
	push 1
	jmp label25
label24:
	push 0
label25:

	pop rax
	cmp rax, 0
	jz label26

	mov rax,[gato]
	push rax


	pop rax
	mov rbx,[abacate]
	cmp rbx,rax
	jle label28
	push 1
	jmp label29
label28:
	push 0
label29:

	pop rax
	cmp rax, 0
	jz label30

	mov rax,[gato]
	push rax

	pop rax
	mov [i],rax

label32:

	mov rax,[macaco]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label34
	push 1
	jmp label35
label34:
	push 0
label35:

	pop rax
	cmp rax, 0
	jz label33

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label32
label33:

	jmp label31
label30:

	mov rax,[abacate]
	push rax

	pop rax
	mov [i],rax

label36:

	mov rax,[macaco]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label38
	push 1
	jmp label39
label38:
	push 0
label39:

	pop rax
	cmp rax, 0
	jz label37

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label36
label37:

label31:

	jmp label27
label26:

	mov rax,[gato]
	push rax

	pop rax
	mov [i],rax

label40:

	mov rax,[abacate]
	push rax


	pop rax
	mov rbx,[i]
	cmp rbx,rax
	jg label42
	push 1
	jmp label43
label42:
	push 0
label43:

	pop rax
	cmp rax, 0
	jz label41

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf


	mov rax,[i]
	push rax

	mov rax,1
	push rax

	pop rax
	pop rbx
	add rax,rbx
	push rax

	pop rax
	mov [i],rax

	jmp label40
label41:

label27:

label3:

	mov rax,10
	push rax

	mov rax,2
	push rax

	pop rax
	pop rbx
	imul rax,rbx
	push rax

	mov rax,10
	push rax

	mov rax,9
	push rax

	pop rax
	pop rbx
	sub rbx,rax
	push rbx

	mov rax,1
	push rax

	pop rax
	pop rbx
	sub rbx,rax
	push rbx

	pop rax
	pop rbx
	sub rbx,rax
	push rbx

	pop rax
	mov [i],rax

	mov rdi, str0
	mov rsi,[i]
	mov rax,0
	call printf

 
	pop rbp
	mov rax,0
	RET