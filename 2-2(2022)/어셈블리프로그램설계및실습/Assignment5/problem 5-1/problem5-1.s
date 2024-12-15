	AREA 	ARMex, CODE, READONLY
		ENTRY
Start
	LDR sp, Address1 ;set start address	
	MOV r0, #1 ;store 1 to r0
	MOV r1, #1 ;store 1 to r1
	MOV r2, #11 ;store 11 to r2(compare)

Factorial
	MUL r3, r0, r1 ;r3 = r0 * r1
	ADD r0, r0, #1 ;r0 = r0 + 1
	MOV r1, r3
	
	CMP r0, r2
	
	BNE Factorial ;r0!=11 go to Factorial
	BEQ Done ;r0=11 go to Done
	
Done
	STMEA sp, {r3} ;store r3 to stack(push)
	MOV pc, #0 ;end

Address1 & &40000 ;stack start address
	END