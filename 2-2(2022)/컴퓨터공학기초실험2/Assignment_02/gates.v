module _inv(a,y);// Inverter
input a;
output y;
assign y=~a;
endmodule
	
module _nand2(a,b,y);// NAND gate
input a,b;
output y;
assign y=~(a&b);
endmodule

module _and2(a,b,y);// 2 input AND gate
input a,b;
output y;
assign y=a&b;
endmodule

module _or2(a,b,y);// 2 input OR gate
input a,b;
output y;
assign y=a|b; 
endmodule
	
module _xor2(a,b,y); // 2 input XOR gate
	input a,b;
	output y;
	wire inv_a,int_b;
	wire w0,w1;

	_inv inv0(a,inv_a);
	_inv inv1(b,inv_b);
	_and2 and0(inv_a,b,w0);
	_and2 and1(a,inv_b,w1);
	_or2 or0(w0,w1,y);
endmodule 