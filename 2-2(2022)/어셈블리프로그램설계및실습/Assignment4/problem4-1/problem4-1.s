	AREA	 ARMex, CODE, READONLY
		ENTRY
start	
	ldr r0, tempaddr ;load tempaddr into register r0
	mov r1, #1 ; r1 = 1
	add r2, r1, lsl #1 ; r2 = 1*2 = 2 = 2!
	add r3, r2, r2, lsl #1 ; r3 = 2 + 2*2 = 6 = 3!
	mov r4, r3, lsl #2 ; r4 = 6*4 = 24 = 4!
	add r5, r4, r4, lsl #2 ; r5 = 24 + 24*4 = 120 = 5!
	add r6, r5, r5, lsl #2 ; r6 = 120 + 120*4 = 600
	add r6, r6, r5 ; r6 = 600 + 120 = 720;
	rsb r7, r6, r6, lsl #3 ; r7 = 5040 = 7!
	add r8, r7, lsl #3 ; r8 = 40320 = 8!
	add r9, r8, r8, lsl #3 ; r9 = 362880 = 9!
	add r10, r9, r9, lsl #3; r10 = 3265920
	add r10, r10, r9 ; r10 = 3628800
	
	str r10, [r0] ;store into r0
	
	mov pc, lr ;Mark end of file
tempaddr & &40000
	end