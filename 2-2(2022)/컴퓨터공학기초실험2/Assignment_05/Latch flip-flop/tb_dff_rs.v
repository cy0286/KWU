`timescale 1ns/100ps //set simulation time scale

module tb_dff_rs; //set/reset d flip-flop testbench module
	reg tb_clk,tb_set_n,tb_reset_n,tb_d;
	wire tb_q;
	
	//load _dff_rs module
	_dff_rs U0_dff_rs(tb_clk, tb_set_n, tb_reset_n, tb_d, tb_q);
	
	initial forever #5 tb_clk=~tb_clk; 
	
	initial begin //set simulation bits
	tb_clk=1'b0;	tb_set_n=1'b0; tb_reset_n=1'b0; tb_d=1'b0;
	#3; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_reset_n=1'b1; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_set_n=1'b1; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; tb_d=1'b0;
	#10; tb_d=1'b1;
	#10; $stop;
	#(STEP*2);	
	$stop;
   end
endmodule 