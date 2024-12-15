cr equ 0x00 ;define cr 0x00, 
	AREA 	ARMex, CODE, READONLY   
		ENTRY 
start
	LDR r0, =string ;load string
	LDR r1, Address1 ;load address

loop
	LDRB r2,[r0],#1 ;load into r2
	STRB r2,[r1],#1 ;store into r2
	CMP r2, #cr ;is it terminator?
	BNE loop ;no, read next char
	BEQ endline ;yes, stop loop

endline
	MOV pc, lr ;mark end of line
	
string DCB "Hello, World", 0
Address1 & 0x40000
	END