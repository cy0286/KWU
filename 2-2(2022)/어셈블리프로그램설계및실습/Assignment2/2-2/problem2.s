	AREA    ARMex, CODE, READONLY
	   ENTRY
start
   
   MOV   r0,#1        ;store integer 1 to r0
   MOV   r1,#2        ;store integer 2 to r1
   MOV   r2,#3        ;store integer 3 to r2
   MOV   r3,#4        ;store integer 4 to r3

   LDR   r4,TEMPADDR  ;load memory address into r4
   STRB  r0,[r4]      ;store 01 into 0x40000
   STRB  r1,[r4,#1]   ;store 02 into 0x40001
   STRB  r2,[r4,#2]   ;store 03 into 0x40002
   STRB  r3,[r4,#3]   ;store 04 into 0x40003
   LDR 	 r5,[r4]      ;store 0x04030201 into r5

   STRB  r0,[r4,#3]      
   STRB  r1,[r4,#2]
   STRB  r2,[r4,#1]
   STRB  r3,[r4]
   LDR   r6,[r4]         
   
TEMPADDR & &40000      ;memory address

   MOV   pc,lr         ;go to first instruction
   END                 ;Mark end of file