module fa(a,b, ci, s, co); //full adder module for rca
	input a, b, ci;
	output s, co;
	wire [2:0]w;

	ha U0_ha(b, ci, w[0], w[1]);  //w[0] = (b XOR ci), w[1] = (b AND ci)
	ha U1_ha(a, w[0], s, w[2]);  //s = (a XOR w[0]), w[2] = (a AND w[0])
	_or2 U2_or(w[1], w[2], co); //co = (w[1] OR w[2])
endmodule
