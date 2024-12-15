`timescale 1ns/100ps //set simulation timescale

module tb_bus; //bus testbench
	reg tb_clk, tb_reset_n, tb_M_req, tb_M_wr;
	reg [7:0] tb_M_addr;
	reg [31:0] tb_M_dout, tb_S0_dout, tb_S1_dout;
	wire tb_M_grant, tb_S0_sel, tb_S1_sel, tb_S_wr;
	wire [7:0] tb_S_addr;
	wire [31:0] tb_M_din, tb_S_din;
	
	//load bus
	BUS U0_BUS(tb_clk, tb_reset_n, tb_M_req, tb_M_wr, tb_M_addr, tb_M_dout, tb_S0_dout, tb_S1_dout, tb_M_grant, tb_S0_sel, tb_S1_sel, tb_S_wr, tb_S_addr, tb_M_din, tb_S_din);
	
	always #5 tb_clk = ~tb_clk; //set clock
	initial
	begin
	tb_clk=1; tb_reset_n=0; tb_M_req=0; tb_M_addr=8'b00000000; tb_M_wr=0; tb_M_dout=32'h00000000; 
	tb_S0_dout=32'h00000000; tb_S1_dout=32'h00000000;
	#17 tb_reset_n=1;
	#10 tb_M_req=1; tb_S0_dout=32'h00000001; tb_S1_dout=32'h00000002;
	#10 tb_M_wr=1;
	#10 tb_M_addr=8'h01; tb_M_dout=32'h00000002;
	#10 tb_M_addr=8'h02; tb_M_dout=32'h00000004;
	#10 tb_M_addr=8'h03; tb_M_dout=32'h00000006;
	#10 tb_M_addr=8'h20; tb_M_dout=32'h00000020;
	#10 tb_M_addr=8'h21; tb_M_dout=32'h00000022;
	#10 tb_M_addr=8'h22; tb_M_dout=32'h00000024;
	#10 tb_M_addr=8'h23; tb_M_dout=32'h00000026;
	#10 tb_M_addr=8'ha0; tb_M_dout=32'h000000ff;
	#10 $stop;
   end
endmodule 