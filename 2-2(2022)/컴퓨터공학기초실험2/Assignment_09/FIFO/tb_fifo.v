`timescale 1ns/100ps //set simulation timescale  

module tb_fifo; //fifo testbench
   //input
	reg tb_clk,tb_reset_n,tb_rd_en,tb_wr_en;
	reg [31:0] tb_d_in;
	//output
	wire [31:0] tb_d_out;
	wire [3:0] tb_data_count;	
	wire tb_full,tb_empty, tb_wr_ack,tb_wr_err,tb_rd_ack,tb_rd_err;   
   
	//load fifo module
	fifo U0_fifo(.clk(tb_clk),.reset_n(tb_reset_n),.rd_en(tb_rd_en),.wr_en(tb_wr_en),.d_in(tb_d_in),.d_out(tb_d_out),.data_count(tb_data_count),.full(tb_full),.empty(tb_empty),.wr_ack(tb_wr_ack),.wr_err(tb_wr_err),.rd_ack(tb_rd_ack),.rd_err(tb_rd_err));

	always # 5 tb_clk=~tb_clk;
   
	//set simulation bits
	initial
	begin
	tb_clk=1'b0; tb_reset_n = 0; tb_rd_en=0; tb_wr_en=0; tb_d_in=32'b0;
	#12; tb_reset_n=1; tb_wr_en=1; tb_d_in=32'h00000011;
	#10; tb_d_in=32'h00000022; 
	#10; tb_d_in=32'h00000033;
	#10; tb_d_in=32'h00000044; 
	#10; tb_d_in=32'h00000055; 
	#10; tb_d_in=32'h00000066; 
	#10; tb_d_in=32'h00000077; 
	#10; tb_d_in=32'h00000088; 
	#10; tb_d_in=32'h00000099;
	#10; tb_d_in=32'h000000aa;
	#10;
	$stop;
	end  
endmodule 