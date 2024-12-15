`timescale 1ns/100ps //set simulation timescale

module tb_Register_file; //Register file testbench
	reg  tb_clk,tb_reset_n,tb_we;	
	reg  [2:0]tb_wAddr,tb_rAddr;	
	reg  [31:0]tb_wData;	
	wire [31:0]tb_rData;
	
	//load Register_file
	Register_file U0_Register_file(tb_clk, tb_reset_n, tb_wAddr, tb_wData, tb_we, tb_rAddr, tb_rData);
	
	always #5 tb_clk=~tb_clk; //clk change per #5
	initial begin //set simulation bits
	tb_clk=0;
				tb_reset_n=0; tb_we=0; tb_wAddr=3'b000; tb_rAddr=3'b000; tb_wData=32'h0; #8;
				tb_reset_n=1; tb_we=1; 												tb_wData=32'h11111111; 
	#10; 									  tb_wAddr=3'b001; 						tb_wData=32'hff00ff00; 
	#10; 									  tb_wAddr=3'b010; 						tb_wData=32'h00ff00ff; 
	#10; 						  			  tb_wAddr=3'b011;
	#10; 															  
	#10; 															 
	#10; $stop;
	end
endmodule 