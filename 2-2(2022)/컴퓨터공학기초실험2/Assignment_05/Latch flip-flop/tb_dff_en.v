`timescale 1ns/100ps //set simulation time scale 

module tb_dff_en; //enabled d flip-flop testbench module
	reg 	tb_clk,tb_en,tb_d;
	wire 	tb_q;
		
	//load _dff_en module
	_dff_en U0_dff_en(tb_clk, tb_en, tb_d, tb_q); 
	
	initial forever #5 tb_clk=~tb_clk;//set clk
	
	initial begin //set simulation bits
	tb_clk=1'b0; tb_en=1'b1; tb_d=1'b0;
	#3; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0; tb_en=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#15; $stop;
   end
endmodule 