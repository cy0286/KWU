module fa(a,b,ci,s,co); // full adder
	input a,b,ci;
	output s,co;
	wire c1, c2, sm;
	
	ha U0_ha(b,ci,sm,c1); // sm = (b XOR ci), c1 = (b AND ci)
	ha U1_ha(a,sm,s,c2); // s = (a XOR sm), c2 = (a AND sm)
	_or2 U2_or2(c1,c2,co); // co = (c1 OR c2)
endmodule 