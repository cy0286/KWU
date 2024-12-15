`include "FullAdder.v"

module RippleCarryAdder(a, b, c_out, sum);
	input [3:0] a, b;
	output c_out;
	output [3:0] sum;
	
	wire c0, c1, c2;

	FullAdder fa0(a[0], b[0], 1'b0, c0, sum[0]);
	FullAdder fa1(a[1], b[1], c0, c1, sum[1]);
	FullAdder fa2(a[2], b[2], c1, c2, sum[2]);
	FullAdder fa3(a[3], b[3], c2, c_out, sum[3]);
endmodule