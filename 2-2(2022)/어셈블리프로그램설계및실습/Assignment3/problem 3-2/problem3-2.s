	AREA 	ARMex, CODE, READONLY
		ENTRY
start
	LDR r0, Address1 	;load address1 into r0
	LDR r1, = Arr1		;load the Arr1
	LDR r2, [r1], #36 	;store form the back

loop
	LDR r2, [r1], #-4 	;load array from the back
	STRB r2, [r0], #1 	;sotre r2 into r0
	CMP r2, #10 		;compare r2 for check the program is end

end
	BEQ finish 			;if  r2 == 10 go to finish
	BNE loop 			;if r2 != 10 go to loop

finish
	MOV pc, lr 			;go to first instruction

Arr1 DCD 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
Address1 & &4000 		;memory address
	END 				;Mark end of file