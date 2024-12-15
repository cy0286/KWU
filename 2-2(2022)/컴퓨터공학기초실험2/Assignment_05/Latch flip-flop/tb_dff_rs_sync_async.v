`timescale 1ns/100ps //set simulation timescale
module tb_dff_rs_sync_async;
	reg	tb_clk,tb_set_n,tb_reset_n,tb_d;
	wire	tb_q_sync,tb_q_async;
	
	//load _dff_rs_sync_async module
	_dff_rs_sync_async U0_dff_rs_sync_async(tb_clk, tb_set_n, tb_reset_n, tb_d, tb_q_sync, tb_q_async);
	
	initial forever #5 tb_clk=~tb_clk;
	
	initial begin //set simulation bits
	tb_clk=1'b0; tb_set_n=1'b0; tb_reset_n=1'b0; tb_d=1'b0;
	#3; 	tb_d= 1'b1;
	#10; 	tb_d= 1'b0;
	#10;	tb_d= 1'b1;
	#10;	tb_d= 1'b0;
	#10;	tb_reset_n= 1'b1; tb_d= 1'b1;
	#10;	tb_reset_n=1'b0;
	#10;	tb_reset_n=1'b1;
	#10; 	tb_d= 1'b0;
	#10; 	tb_d= 1'b1;
	#10; 	tb_d= 1'b0;
	#10;	tb_set_n= 1'b1; tb_d= 1'b1;
	#10; 	tb_d= 1'b0;
	#10; 	tb_d= 1'b1;
	#10; 	tb_d= 1'b0;
	#10;	tb_d= 1'b1;
	#10; $stop;
	end 
endmodule 