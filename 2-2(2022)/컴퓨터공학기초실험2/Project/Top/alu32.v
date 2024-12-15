module alu32(a,b,op,result); //alu32 module
   input [31:0] a,b;
   input [3:0] op;
   output [31:0] result;
   
   wire [31:0] w_add_b;
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, less, greater, lsl, lsr, asr, w_add;
	wire co;

   //load modules
   _inv_32bits      U0_NOTA(a, w_not_a); //NOT A
   _inv_32bits      U1_NOTB(b, w_not_b); //NOT B
   _and2_32bits     U2_AND(a, b, w_and); //AND
   _or2_32bits      U3_OR(a, b, w_or); //OR
   _xor2_32bits     U4_XOR(a, b, w_xor); //XOR
   _xnor2_32bits    U5_XNOR(a, b, w_xnor); //XNOR
	less_than	  	  U6_slt(a, b, less); //set less than
	greater_than 	  U7_sgt(a, b, greater); //set greater than
	LSL32				  U8_LSL(b, 2'b01, lsl); //shift left logical
	LSR32				  U9_LSR(b, 2'b01, lsr); //shift right logical
	ASR32				  U10_ASR(b, 2'b01, asr); //shift right arithmetic
	mx2_32bits 		  U11_ADD_SUB(b, w_not_b, op[2], w_add_b); //add & sub
	cla32         	  U12_cla32(a, w_add_b, op[2], w_add, co);	
   mx16_32bits      U13_(w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, less, greater, lsl, lsr, asr, w_add, w_add, 32'bx, 32'bx, 32'bx, op[3], op[2], op[1], op[0], result);
endmodule 