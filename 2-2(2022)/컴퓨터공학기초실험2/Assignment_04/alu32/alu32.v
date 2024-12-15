module alu32(a,b,op,result,c,n,z,v); //alu32 module
   input [31:0] a,b;
   input [2:0] op;
   output [31:0] result;
   output c,n,z,v;
   
   wire [31:0] w_add_b;
	wire [31:0] w_not_a,w_not_b, w_and, w_or, w_xor, w_xnor, w_add;
	wire co_prev, co_add;

      
   //load modules
   _inv_32bits      U0_inv_32bits(a, w_not_a);
   _inv_32bits      U1_inv_32bits(b, w_not_b);
   _and2_32bits     U2_and2_32bits(a, b, w_and);
   _or2_32bits      U3_or2_32bits(a, b, w_or);
   _xor2_32bits     U4_xor2_32bits(a, b, w_xor);
   _xnor2_32bits    U5_xnor2_32bits(a, b, w_xnor);
	mx2_32bits 		  U6_mux_b(b, w_not_b, op[0], w_add_b);
   cla32_ov         U7_add(a, w_add_b, op[0], w_add, co_prev, co_add);
   mx8_32bits       U8_mx8_32bits(w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_add, op[2], op[1], op[0], result);
	cal_flags32 	  U8_cal_flags32 (op, result, co_add, co_prev, c, n, z, v);
endmodule 