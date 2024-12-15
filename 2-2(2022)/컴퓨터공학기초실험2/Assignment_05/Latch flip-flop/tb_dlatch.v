`timescale 1ns/100ps //set simulation time scale

module tb_dlatch; //d latch testbench module
	reg tb_clk,tb_d;
	wire tb_q,tb_q_bar;

	//load _dlatch module
	_dlatch U0_dlatch(tb_clk, tb_d, tb_q, tb_q_bar);
	
	initial forever #5 tb_clk=~tb_clk;
	
	initial begin //set simulation bits
	tb_clk=1'b0; tb_d=1'b0;
	#3; tb_d=1'b1;
	#3; tb_d=1'b0;
	#6; tb_d=1'b1;
	#2; tb_d=1'b0;
	#3; tb_d=1'b1;
	#4; tb_d=1'b0;
	#8; $stop;
	end
endmodule 	