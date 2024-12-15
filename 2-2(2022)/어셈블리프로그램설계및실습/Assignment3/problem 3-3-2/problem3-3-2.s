	AREA 	ARMex, CODE, READONLY
		ENTRY
start
;using n(n+10)
	LDR r0, Address1		;load address1 into r0
	MOV r1, #1				;r1=1
	MOV r2, r1, LSL #1		;r2=2
	MOV r2, r2, LSL #1		;r2=4
	ADD r2, r2, #1			;r2=5
	MOV r2, r2, LSL #1		;r2=10
	
	ADD r3, r2, r2			;r3=20
	MUL r4, r2, r3			;r4=n(n+10)=200
	STR r4, [r0]			;store r4 into r0
	
	MOV pc,lr				;go to first instruction
	
Address1 & &4000			;memory address
	END 					;Mark end of file