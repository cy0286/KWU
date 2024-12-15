module ha(a,b,s,co); // half adder
	input a,b;
	output s,co;
	
	_xor2 S(a,b,s); // s = (a XOR b)
	_and2 C0(a,b,co); // co = (a AND b)
endmodule 