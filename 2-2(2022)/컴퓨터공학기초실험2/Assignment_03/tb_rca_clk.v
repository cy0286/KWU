`timescale 1ns/100ps // set simulation time scale

module tb_rca_clk; // rca_clk testbench module
	reg clk;
	reg [31:0] tb_a, tb_b;
	reg tb_ci;
	wire [31:0] tb_s;
	wire tb_co;

	parameter STEP = 10; // set parameter
	
	// load rca_clk module
	rca_clk U0_rca_clk(clk, tb_a, tb_b, tb_ci, tb_s, tb_co);
	
	always # (STEP/2) clk = ~clk;
	
	//set simulation bits
	initial begin
	clk = 1'b1; tb_a = 32'h0; tb_b = 32'h0; tb_ci = 1'b0;
	#(STEP); tb_a = 32'hFFFF_FFFF; tb_b = 32'h0; tb_ci = 1'b1;
	#(STEP); tb_a = 32'h0000_FFFF; tb_b = 32'hFFFF_0000; tb_ci = 1'b0;
	#(STEP); tb_a = 32'h135f_a562; tb_b = 32'h3561_4642; tb_ci = 1'b0;
	#(STEP*2); $stop;
	end
endmodule 