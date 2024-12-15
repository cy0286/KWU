module shifter8(clk,reset_n,op,shamt,d_in,d_out); //8-bits shifter
	input  clk, reset_n;
	input  [2:0] op;
	input  [1:0] shamt;
	input  [7:0] d_in;
	output [7:0] d_out;
	wire   [7:0] d_next;

	//instances 8-bits register & struct 8-bits shifter
	_register8_r U0_register_r(clk, reset_n, d_next, d_out);
	cc_logic 	 U1_cc_logic(op, shamt, d_in, d_out, d_next);
endmodule 