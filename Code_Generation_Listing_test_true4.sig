code SEGMENT
	ASSUME cs:code	
LAB2OPT:
?L0:
	mov ax, VAR1
	mov bx, VAR4
	cmp ax, bx
	lne ?L1
	mov ax, 24
	mov bx, 56
	cmp ax, bx
	jg ?L2
	nop
	jmp ?L3
?L2:	nop
?L4:
	mov ax, VAR1
	mov bx, VAR4
	cmp ax, bx
	lne ?L5
	nop
	jmp ?L4
?L5:	nop
	nop
?L3:	nop
	nop
	jmp ?L0
?L1:	nop
	nop
mov ah, 4ch
int 21h
code ends
end LAB2OPT

