code SEGMENT
	ASSUME cs:code	
LAB2:
	mov ax, 10
	mov bx, 2
	jle ?L0
?L2:
	mov ax, VAR1
	mov bx, VAR2
	je ?L3
	nop
	jmp ?L2
?L3:	nop
	nop
	jmp ?L1
?L0:	nop
	mov ax, 2
	mov bx, LAB22
	lne ?L4
	nop
	jmp ?L5
?L4:	nop
?L6:
	mov ax, VAR1
	mov bx, VAR2
	jg ?L7
	mov ax, 10
	mov bx, 2
	jl ?L8
	nop
	jmp ?L9
?L8:	nop
	nop
?L9:	nop
?L10:
	mov ax, VAR16644
	mov bx, VAR6634342
	je ?L11
	nop
	jmp ?L10
?L11:	nop
	nop
	jmp ?L6
?L7:	nop
	nop
?L5:	nop
?L12:
	mov ax, 4
	mov bx, 56
	lne ?L13
?L14:
	mov ax, VAR166
	mov bx, VAR662
	je ?L15
	nop
	jmp ?L14
?L15:	nop
	nop
	jmp ?L12
?L13:	nop
	nop
?L1:	nop
?L16:
	mov ax, VAR1
	mov bx, VAR2
	jg ?L17
	mov ax, 10
	mov bx, 2
	jl ?L18
	nop
	jmp ?L19
?L18:	nop
	nop
?L19:	nop
?L20:
	mov ax, VAR16644
	mov bx, VAR6634342
	je ?L21
	nop
	jmp ?L20
?L21:	nop
	nop
	jmp ?L16
?L17:	nop
	mov ax, 10
	mov bx, 2
	jle ?L22
	nop
	jmp ?L23
?L22:	nop
	nop
?L23:	nop
	nop
mov ah, 4ch
int 21h
code ends
end LAB2

