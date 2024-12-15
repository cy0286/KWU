module ha(a, b, s, co); // half adder
	input a, b;
	output s, co;

	assign s = a ^ b; // s = (a XOR b)
	assign co = a & b; // co = (a AND b)
endmodule 