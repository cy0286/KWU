`timescale 1ns/100ps //set simuation timescale
module tb_cntr8; //8-bit loadable up/down counter testbench
	reg 		  tb_clk, tb_reset_n, tb_inc, tb_load; 
	reg  [7:0] tb_d_in;
	wire [7:0] tb_d_out;	 
	wire [2:0] tb_o_state;
	
	//load cntr8
	cntr8 U0_cntr8(tb_clk, tb_reset_n, tb_inc, tb_load, tb_d_in, tb_d_out, tb_o_state);

	always #5 tb_clk=~tb_clk; //set clock(clock change per #5)
	
	initial begin //set simulation bits
	tb_clk=1'b1;tb_reset_n=1'b0;tb_inc=1'b0;tb_load=1'b0;tb_d_in=0; 
	#22.5; tb_reset_n=1'b1;tb_inc=1'b1;
	#50;tb_inc=1'b0;tb_d_in=8'b00001111;
   #10;tb_load=1'b0; 	//if load 0
	//#10;tb_load=1'b1;  //if load 1
	#30;$stop;
	end 	
endmodule 