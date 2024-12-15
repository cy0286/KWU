`timescale 1ns/100ps //set simulation timescale

module tb_bus; //bus testbench 1
	reg tb_clk, tb_reset_n, tb_m0_req, tb_m0_wr, tb_m1_wr, tb_m1_req;
	reg [7:0] tb_m0_address, tb_m1_address;
	reg [31:0] tb_m0_dout, tb_m1_dout, tb_s0_dout, tb_s1_dout;
	wire tb_m0_grant, tb_m1_grant, tb_s0_sel, tb_s1_sel, tb_s_wr;
	wire [7:0] tb_s_address;
	wire [31:0] tb_m_din, tb_s_din;
	
	//load bus
	bus U0_bus(tb_clk, tb_reset_n, tb_m0_req, tb_m0_address, tb_m0_wr, tb_m0_dout, tb_m0_grant, tb_m1_req, tb_m1_address, tb_m1_wr, tb_m1_dout, tb_m1_grant, tb_m_din, tb_s0_sel, tb_s1_sel, tb_s_address, tb_s_wr, tb_s_din, tb_s0_dout, tb_s1_dout);
	
	always #5 tb_clk = ~tb_clk; //set clock
	initial
	begin
	tb_clk=1; tb_reset_n=0; tb_m0_req=0; tb_m0_address=8'b00000000; tb_m0_wr=0; tb_m0_dout=32'h00000000; 
	tb_m1_req=0; tb_m1_address=8'b00000000; tb_m1_wr=0; tb_m1_dout=32'h00000000; tb_s0_dout=32'h00000000; tb_s1_dout=32'h00000000;
	#17 tb_reset_n=1;
	#10 tb_m0_req=1; tb_s0_dout=32'h00000001; tb_s1_dout=32'h00000002;
	#10 tb_m0_wr=1;
	#10 tb_m0_address=8'h01; tb_m0_dout=32'h00000002;
	#10 tb_m0_address=8'h02; tb_m0_dout=32'h00000004;
	#10 tb_m0_address=8'h03; tb_m0_dout=32'h00000006;
	#10 tb_m0_address=8'h20; tb_m0_dout=32'h00000020;
	#10 tb_m0_address=8'h21; tb_m0_dout=32'h00000022;
	#10 tb_m0_address=8'h22; tb_m0_dout=32'h00000024;
	#10 tb_m0_address=8'h23; tb_m0_dout=32'h00000026;
	#10 tb_m0_address=8'ha0; tb_m0_dout=32'h000000ff;
	#10 $stop;
   end
endmodule 