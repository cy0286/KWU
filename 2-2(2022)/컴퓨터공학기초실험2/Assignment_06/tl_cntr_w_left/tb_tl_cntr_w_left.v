`timescale 1ns/100ps //set simulation timescale
module  tb_tl_cntr_w_left; //traffic light controller with left signals testbench module
	reg  tb_clk,tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl;
	wire [1:0]tb_La,tb_Lb;
	
	//load tl_cntr_w_left module
	tl_cntr_w_left U0_tl_cntr_w_left(tb_clk, tb_reset_n, tb_Ta, tb_Tal, tb_Tb, tb_Tbl, tb_La, tb_Lb);

	always #5 tb_clk=~tb_clk; 

	initial begin //set simulation bits
	tb_clk=0; tb_reset_n=1; tb_Ta=0; tb_Tb=0; tb_Tal=0; tb_Tbl=0; 
	#2.5 tb_Ta=1; tb_reset_n=0; 
	#10  tb_reset_n=1;
	#10  tb_Tal=1;
	#10  tb_Ta=0;
	#30  tb_Ta=1; tb_Tal=0;
	#10  tb_Tal=1;
	#10  tb_Tb=1;
	#10  tb_Tal=0;
	#30  tb_Tal=1; tb_Tb=0;
	#10  tb_Tb=1;
	#10  tb_Tbl=1;
	#10  tb_Tb=0;
	#30  tb_Tb=1; tb_Tb=0;
	#10  tb_Ta=0;
	#10  $stop; 
	end 
endmodule 