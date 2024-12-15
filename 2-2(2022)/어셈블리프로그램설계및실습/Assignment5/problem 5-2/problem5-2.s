	AREA	 ARMex, CODE, READONLY
		ENTRY
Start
	LDR sp, Address1 ;set start address	
	MOV r0, #0 ;store 0 to r0
	MOV r1, #1 ;store 1 to r1
	MOV r2, #2 ;store 2 to r2
	MOV r3, #3 ;store 3 to r3
	MOV r4, #4 ;store 4 to r4
	MOV r5, #5 ;store 5 to r5
	MOV r6, #6 ;store 6 to r6
	MOV r7, #7 ;store 7 to r7
	
	STMEA sp!, {r0-r7}	;push
	
	LDMEA sp!, {r5} ;load from stack(pop)
	LDMEA sp!, {r4}
	LDMEA sp!, {r3}
	LDMEA sp!, {r7}
	LDMEA sp!, {r2}
	LDMEA sp!, {r0}
	LDMEA sp!, {r6}
	LDMEA sp!, {r1}

	MOV pc, #0 ;end
Address1 & &40000 ;stack start address
	END