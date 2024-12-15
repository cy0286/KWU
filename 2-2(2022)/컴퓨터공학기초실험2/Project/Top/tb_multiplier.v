`timescale 1ns/100ps //set simulation timescale

module tb_multiplier; //multiplier testbench
	reg tb_clk,tb_reset_n,tb_op_start,tb_op_clear;
	reg [31:0] tb_multiplicand,tb_multiplier;
	wire tb_op_done;
	wire [63:0] tb_result;
	
	//load multiplier
	multiplier U0_multiplier(tb_clk, tb_reset_n, tb_multiplicand, tb_multiplier, tb_op_start, tb_op_clear, tb_op_done, tb_result);
	
	always #5 tb_clk = ~tb_clk; 
	
	initial
	begin
		tb_clk = 0;	tb_reset_n = 1; tb_multiplicand = 11; tb_multiplier = -11; tb_op_start = 1; tb_op_clear = 0;
		#10; tb_reset_n = 0; tb_op_start = 0;
		#10; tb_reset_n = 1;	tb_op_start = 1;
		#10; tb_op_start = 0;
		#640;																														
		#10; tb_op_clear = 1;
		#10; tb_op_clear = 0;
		#10; tb_multiplicand = 6; tb_multiplier = 6; tb_op_start = 1;
		#10; tb_op_start = 0;
		#600;/*#300*/ tb_op_clear = 1; //tb_op_clear = 0;
		#10; tb_op_clear = 0;
		#10; $stop;
	end
endmodule 