module rca_clk(clk,a,b,ci,s,co); // 32-bits RCA with clock module
	input clk;
	input [31:0] a,b;
	input ci;
	output [31:0] s;
	output co;
	
	reg [31:0] reg_a, reg_b;
	reg reg_ci;
	reg [31:0] reg_s;
	reg reg_co;
	wire [31:0] wire_s;
	wire wire_co;
	
	always@(posedge clk)
	
	begin
	reg_a <= a;
	reg_b <= b;
	reg_ci <= ci;
	reg_s <= wire_s;
	reg_co <= wire_co;
	end
	
	//load rca32 module
	rca32 U0_rca32(reg_a, reg_b, reg_ci, wire_s, wire_co);
	
	assign s = reg_s;
	assign co = reg_co;
endmodule
