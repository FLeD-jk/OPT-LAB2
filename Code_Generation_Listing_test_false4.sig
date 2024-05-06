code SEGMENT
	ASSUME cs:code	
OPT2:
?L0:
	error: <variable-identifier> can`t equal name of program 
	lne ?L1
	nop
	jmp ?L0
?L1:	nop
	nop
mov ah, 4ch
int 21h
code ends
end OPT2

Error generate comparation operator : Row 3 column 16

