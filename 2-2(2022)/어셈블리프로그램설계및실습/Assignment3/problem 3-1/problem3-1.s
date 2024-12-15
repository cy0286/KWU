   AREA    ARMex, CODE, READONLY
      ENTRY
start
   LDR r0, Address1    	 ;load address1 into register r0
   LDR r1, = Arr1      	 ;load arr1 address into r1
   LDR r2, = Arr2      	 ;load arr2 address into r2
   MOV r3, #10         	 ;same word
   MOV r4, #11         	 ;different word
   
Loop
   LDRB r5, [r1], #1   
   LDRB r6, [r2], #1   
   CMP r5, r6
   BNE different       	 ;if r1 != r2 go to different
   BEQ equal         	 ;ir r1 == r2 go to equal
   
different
   STR r4, [r0]        	 ;store 11
   B Endline           	 ;end loop

equal
   CMP r5, #0          	 ;check end of word
   BEQ Endline         	 ;end loop
   STR r3, [r0]        	 ;store 10
   B Loop              	 ;loop
   
Endline
   MOV pc, lr		   	 ;go to first instruction
   
Address1 & &4000
Arr1 DCB "Hello_wolrd",0 ;store into Arr1
Arr2 DCB "Hello_wolrd",0 ;sotre into Arr2
;case 1 Hello_wolrd, Hello_wolrd
;case 2 Hello_wolrd, Hello_earth
;case 3 Hello_wolrd, aaaaa_bbbbb

   END					 ;Mark end of file