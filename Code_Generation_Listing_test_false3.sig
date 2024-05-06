code SEGMENT
	ASSUME cs:code	
OPT2:
?L0:
	mov ax, VAR1
	mov bx, VAR2
	cmp ax, bx
	lne ?L1
	error: <variable-identifier> can`t equal name of program 
	jg ?L2
?L4:
	mov ax, VAR1
	mov bx, VAR2
	cmp ax, bx
	lne ?L5
	nop
	jmp ?L4
?L5:	nop
	nop
	jmp ?L3
?L2:	nop
	nop
?L3:	nop
	nop
	jmp ?L0
?L1:	nop
	nop
mov ah, 4ch
int 21h
code ends
end OPT2

Error generate comparation operator : Row 7 column 22

