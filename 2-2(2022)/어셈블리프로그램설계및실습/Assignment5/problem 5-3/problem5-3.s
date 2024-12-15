	AREA 	ARMex, CODE, READONLY
		ENTRY
Start
	LDR sp, Address1 ;set start Address
	MOV r0, #10 ;store 10 to r0
	MOV r1, #11 ;store 11 to r1
	MOV r2, #12 ;store 12 to r2
	MOV r3, #13 ;store 13 to r3
	MOV r4, #14 ;store 14 to r4
	MOV r5, #15 ;store 15 to r5
	MOV r6, #16 ;store 16 to r6
	MOV r7, #17 ;store 17 to r7
	MOV r8, #160 ;set register values
	STMFA sp, {r0-r7} ;push

doregister ;index
	ADD r0, r0, #0 ;r0 = r0 + 0
	ADD r1, r1, #1 ;r1 = r1 + 1
	ADD r2, r2, #2 ;r2 = r2 + 2
	ADD r3, r3, #3 ;r3 = r3 + 3
	ADD r4, r4, #4 ;r4 = r4 + 4
	ADD r5, r5, #5 ;r5 = r5 + 5
	ADD r6, r6, #6 ;r6 = r6 + 6
	ADD r7, r7, #7 ;r7 = r7 + 7
	
	ADD r9, r9, r0 ;r9 = r9 + r0
	ADD r9, r9, r1 ;r9 = r9 + r1
	ADD r9, r9, r2 ;r9 = r9 + r2
	ADD r9, r9, r3 ;r9 = r9 + r3
	ADD r9, r9, r4 ;r9 = r9 + r4
	ADD r9, r9, r5 ;r9 = r9 + r5
	ADD r9, r9, r6 ;r9 = r9 + r6
	ADD r9, r9, r7 ;r9 = r9 + r7
	LDMED sp, {r0-r7} ;return(pop)
	
doGCD
	CMP r9, r8 ;r9-r8
	SUBLT r8, r8, r9 ;r8 = r8 - r9
	SUBGT r9, r9, r8 ;r9 = r9 - r8
	BNE doGCD ;r9!=r8 go to DoGCD
	BEQ Done ;r9=r8 go to Done

Done
	ADD r9, r9, r4
	STR r9, [sp]
	
	MOV pc, #0 ;end
	
Address1 & &40000 ;stack start address
	END