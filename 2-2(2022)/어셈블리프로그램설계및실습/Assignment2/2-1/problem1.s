   AREA   ARMex, CODE, READONLY
      ENTRY
start
      MOV    r0, #8         ;store integer 8 to register r0
      MOV    r1, #10        ;store integer 10 to register r1
      MOV    r2, #12        ;store integer 12 to register r2
      
      LDR    r3, TEMPADDR   ;load meomry address into r3
      STRB   r0, [r3]      	;store 8 into 0x40000
      STRB   r1, [r3, #1]   ;store 10 into 0x40001
      STRB   r2, [r3, #2]   ;store 12 into 0x40002
      
      LDRB   r4, [r3]      	;store 1byte from 0x4000 into r4
      CMP    r4, #10        ;compare r4-10
      MOVGT	 r5, #1         ;if r4>10, move 1 into r5 
      MOVLT  r5, #2         ;if r4<10, move 2 into r5 
      MOVEQ  r5, #3         ;if r4==10, move 3 into r5 
      
      LDRB   r4, [r3, #1]   ;store 1byte form 0x4000 into r4
      CMP    r4, #10        ;compare r4-10
      MOVGT  r5, #1         ;if r4>10, move 1 into r5 
      MOVLT  r5, #2       	;if r4<10, move 2 into r5 
      MOVEQ  r5, #3        	;if r4==10, move 3 into r5 
      
      LDRB   r4, [r3, #2]   ;store 1byte form 0x4000 into r4
      CMP    r4, #10        ;compare r4-10
      MOVGT  r5, #1         ;if r4>10, move 1 into r5 
      MOVLT  r5, #2         ;if r4<10, move 2 into r5 
      MOVEQ  r5, #3         ;if r4==10, move 3 into r5 

TEMPADDR & &40000         	;memory address
      MOV    pc, lr         ;go to first instruction
      END             		;Mark end of file