	AREA 	ARMex, CODE, READONLY
		ENTRY
start
;using loop
	LDR r0, Address1		;load address1 into r0
	MOV r1, #1				;r1=1
	MOV r2, r1, LSL #1		;r2=2
	MOV r2, r2, LSL #1		;r2=4
	ADD r2, r2, #1			;r2=5
	ADD r2, r1, r2, LSL #1	;r2=11
	
	ADD r3, r2, #1			;r3=12
	ADD r3, r3, #1			;r3=13
	ADD r3, r3, #1			;r3=14
	MOV r3, r3, LSL #1		;r3=28
	ADD r3, r3, #1			;r3=29
	
loop
	ADD r4, r4, r2			;r4=r4+r2
	CMP r2, r3				;r2-r3
	BEQ endline				;if r2==r3, go to endline
	ADD r2, r2, r1, LSL #1	;r2=r2+r1*2
	BNE loop				;if r2!=r3, go to loop

endline
	STR r4, [r0]			;store sum into r0
	MOV pc, lr				;go to first instruction

Address1 & &4000  			;memory address
	END						;Mark end of file