	AREA 	ARMex, CODE, READONLY
		ENTRY
start
	LDR r0, Address1 ;load Address1 into register r0
	LDR r1, value1 ;load floating point value1
	LDR r2, value2 ;load floating point value2
	LDR r12, mantissa
	
	;store value1 of sign bit, exponent, mantissa
	MOV r3, r1, LSR #31
	MOV r4, r1, LSR #23
	MOV r4, r4, LSL #24
	MOV r4, r4, LSR #1
	MOV r5, r1, LSL #9
	MOV r5, r5, LSR #1
	ADD r5, r5, #0x80000000 ;add 1 to mantissa
	
	;store value2 of sign bit, exponenet, mantissa
	MOV r7, r2, LSR #31
	MOV r8, r2, LSR #23
	MOV r8, r8, LSL #24
	MOV r8, r8, LSR #1
	MOV r9, r2, LSL #9
	MOV r9, r9, LSR #1
	ADD r9, r9, #0x80000000 ;add 1 to mantissa
	
	CMP r4, r8 ;compare exponent
	SUBGT r10, r4, r8
	SUBLT r10, r8, r4
	MOV r10, r10, LSR #23
	MOVLT r5, r5, LSR r10
	MOVGT r9, r9, LSR r10

	MOVLT r4, r8
	
	CMP r3, r7
	BEQ equal
	BNE notequal
	
equal ;sign same
	ADDS r11, r5, r9
	ADDCS r4, r4, r12 ;add 1
	MOVCS r11, r11, LSR #1
	MOV r11, r11, LSL #1
	MOV r11, r11, LSR #9 ;bit clear
	B finish
	
notequal ;sign differnt
	MOV r5, r5, LSR #9
	MOV r9, r9, LSR #9
	CMP r5, r9
	BEQ endline ;r5=r9
	
	SUBGT r11, r5, r9
	SUBLT r11, r9, r5
	MOVLT r3, r7
	CMP r11, #0x1000000
	ADDCS r4, r4, r12 ;add 1
	MOVCS r11, r11, LSR #1
	BCS finish
	B normalize

normalize ;normalize mantisa
	CMP r11, r12, LSL #1
	MOVLS r11, r11, LSL #1;
	SUBLS r4, r4, r12
	BLO normalize
	BHS finish
	
finish
	MOV r3, r3, LSL #31
	ADD r11, r11, r3 ;add sign bit
	ADD r11, r11, r4 ;add exponent
	STR r11, [r0] ;store into r0
	MOV pc, lr ;mark end of file

endline
	STR r11,[r0] ;store value into r0
	MOV pc, lr ;mark end of file

;case 1 same sign bit & different value
value1 & 0x3FC00000 ;1.5
value2 & 0x40500000 ;3.25

;case 2 same sign bit & same value
;value1 & 0x42680000 ;58
;value2 & 0x42680000 ;58

;case 3 different sign bit
;value1 & 0x42680000 ;58
;value2 & 0xC2680000 ;-58

mantissa & 0x00800000
Address1 & 0x00040000
	END