`timescale 1ns/100ps // set simulation time scale
	
	module tb_cla4; // cla4 testbench module
	reg [3:0] tb_a, tb_b; 
	reg tb_ci; // carry in
	wire [3:0] tb_s; // output sum
	wire tb_co; // output carry out
	wire [4:0] tb_result; // result
	
	assign tb_result = {tb_co, tb_s};
	
	//load cla4 module
	cla4 U0_cla4(tb_a, tb_b, tb_ci, tb_s, tb_co);
	
	initial begin // set simulation bits
	tb_a = 0; tb_b = 0; tb_ci = 0;
	#10; tb_a = 4'h3; tb_b = 4'h5; tb_ci = 0;
	#10; tb_a = 4'h7; tb_b = 4'h9; tb_ci = 0;
	#10; tb_a = 4'h5; tb_b = 4'h5; tb_ci = 1;
	#10; tb_a = 4'h8; tb_b = 4'h7; tb_ci = 1;
	#10; tb_a = 4'hf; tb_b = 4'hf; tb_ci = 0;
	#10; tb_a = 4'hf; tb_b = 4'hf; tb_ci = 1;
	#10; $stop;
	end
endmodule
