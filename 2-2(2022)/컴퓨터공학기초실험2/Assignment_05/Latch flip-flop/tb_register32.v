`timescale 1ns/100ps //set simulation timescale

module tb_register32; //32-bits register testbench module
	reg 			 tb_clk;
	reg	[31:0] tb_d;
	wire	[31:0] tb_q;
	
	_register32 U0_register32(tb_clk, tb_d, tb_q); //load 32-bits register module
	
	initial forever #13 tb_clk=~tb_clk;
	
	initial begin //set simulation bits
	
	tb_clk=1'b0;
	#0; tb_d = 32'h1234_5678;
	#7; tb_d = 32'h9876_5432;
	#7; tb_d = 32'hffee_ddcc;
	#15; tb_d = 32'hbbaa_ccdd;
	#5; tb_d = 32'h7766_5544;
	#10; tb_d = 32'h3322_1100;
	#10; tb_d = 32'h1234_5678;
	#20; $stop;
	end
endmodule 