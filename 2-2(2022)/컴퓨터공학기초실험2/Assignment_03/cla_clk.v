module cla_clk(clk, a, b, ci, s, co); // 32-bits CLA with register
	input clk; // clock input
	input [31:0] a, b;
	input ci; // input carry in
	output [31:0] s;
	output co;
	
	//declare register & wire
	reg [31:0] reg_a, reg_b;
	reg reg_ci;
	reg [31:0] reg_s;
	reg reg_co;
	wire [31:0] wire_s;
	wire wire_co;
	
	always @ (posedge clk) // clock act at positive edge
	
	begin
	reg_a <= a;
	reg_b <= b;
	reg_ci <= ci;
	reg_s <= wire_s;
	reg_co <= wire_co;
	end
	
	//load cla32 module
	cla32 U0_cla32(reg_a, reg_b, reg_ci, wire_s, wire_co);
	
	assign s = reg_s;
	assign co = reg_co;
endmodule 