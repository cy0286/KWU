   AREA    ARMex, CODE, READONLY
      ENTRY

start
;unrolling
   LDR r0, Address1       ;load address1 into r0
   LDR r1, =Arr1          ;load arr1 to r1

   LDR r3,[r1],#4         ;load data into r3
   ADD r2,r2,r3           ;r2=r2+r3
   LDR r3,[r1],#4
   ADD r2,r2,r3
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   LDR r3,[r1],#4
   ADD r2,r2,r3      
   STR r2,[r0]           ;store r2 into r0
   
endline 
   MOV pc, lr            ;go to first instruction

Arr1 DCD 11,13,15,17,19,21,23,25,27,29
Address1 & &4000         ;memory address
   END                   ;Mark end of file