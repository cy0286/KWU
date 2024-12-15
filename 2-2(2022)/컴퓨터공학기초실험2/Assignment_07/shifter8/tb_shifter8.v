`timescale 1ns/100ps //set simulation timescale
module tb_shifter8; //8-bits shifter testbench
	reg 		 tb_clk, tb_reset_n;
	reg  [2:0] tb_op;
	reg  [1:0] tb_shamt;
	reg  [7:0] tb_d_in;
	wire [7:0] tb_d_out;
	
	//load shifter8
	shifter8 U0_shifter8(tb_clk, tb_reset_n, tb_op, tb_shamt, tb_d_in, tb_d_out);
	
	always #5 tb_clk=~tb_clk; //set clock(clock change per #5)
	
	initial begin//set simulation bits
	tb_clk=1'b1; tb_reset_n=1'b0; tb_op=1'b0; tb_d_in=1'b0; tb_shamt=1'b0;
	#12.5; tb_reset_n=1'b1;
	#10; tb_op=3'b001; tb_d_in=8'b0111_0111;
	#20; tb_op=3'b010;
	#20; tb_shamt=2'b10;
	#30; tb_op=3'b011;
	#15; $stop;
	end
endmodule 