`timescale 1ns/100ps //set simulation timescale
module  tb_tl_cntr; //traffic light controller testbench module
	reg  tb_clk,tb_reset_n,tb_Ta,tb_Tb;
	wire [1:0]tb_La,tb_Lb;
	
	//load tl_cntr module
	tl_cntr U0_tl_cntr(tb_clk, tb_reset_n, tb_Ta, tb_Tb, tb_La, tb_Lb);

	always #5 tb_clk=~tb_clk; 

	initial begin //set simulation bits
	tb_clk=0; tb_reset_n=1; tb_Ta=0; tb_Tb=0; 
	#2.5 tb_Ta=1; tb_reset_n=0; 
	#10  tb_reset_n=1;
	#10  tb_Tb=1;
	#10  tb_Ta=0;
	#30  tb_Ta=1; tb_Tb=0;
	#30  tb_Ta=0;
	#10  $stop;
	end
endmodule
