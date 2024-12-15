   AREA    ARMex, CODE, READONLY
      ENTRY
start
	ldr r0, tempaddr ;load tempaddr into register r0
	mov r1, #1 ;r1 = 1
	mov r10, #2 ;r2 = 2
	mul r2, r1, r10 ;r2 = 1*2
	add r10, r10, #1
	mul r3, r2, r10 ;r3 = 1*2*3
	add r10, r10, #1
	mul r4, r3, r10 ;r4 = 1*2*3*4
	add r10, r10, #1
	mul r5, r4, r10 ;r5 = 1*2*3*4*5
	add r10, r10, #1
	mul r6, r5, r10 ;r6 = 1*2*3*4*5*6
	add r10, r10, #1
	mul r7, r6, r10 ;r7 = 1*2*3*4*5*6*7
	add r10, r10, #1
	mul r8, r7, r10 ;r8 = 1*2*3*4*5*6*7*8
	add r10, r10, #1
	mul r9, r8, r10 ;r9 = 1*2*3*4*5*6*7*8*9
	add r10, r10, #1
	mul r11, r9, r10 ; r11 = 1*2*3*4*5*6*7*8*9*10
	
	str r11, [r0] ;store into r0
	
	mov pc, lr  ;Mark end of file
tempaddr & &40000 
	end