module fa_v2(a, b, ci, s); // Full adder module for cla
	input a, b, ci;
	output s;
	wire w0;

	_xor2 U0_xor2(a, b, w0); // w0 = (a XOR b)
	_xor2 U1_xor2(w0, ci, s); // s = (w0 XOR ci)
endmodule 