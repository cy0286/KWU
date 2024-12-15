module _inv(a,y);// Inverter
	input a;
	output y;
	assign y=~a;
endmodule
	
module _nand2(a,b,y);// 2 input NAND gate
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

module _and3(a,b,c,y); // 3 input AND gate
	input a,b,c;
	output y;
	assign y=a&b&c;
endmodule

module _and4(a,b,c,d,y); // 4 input AND gate
	input a,b,c,d;
	output y;
	assign y=a&b&c&d;
endmodule

module _and5(a,b,c,d,e,y); // 5 input AND gate
	input a,b,c,d,e;
	output y;
	assign y=a&b&c&d&e;
endmodule

module _or3(a,b,c,y); // 3 input OR gate
	input a,b,c;
	output y;
	assign y=a|b|c;
endmodule

module _or4(a,b,c,d,y); // 4 input OR gate
	input a,b,c,d;
	output y;
	assign y=a|b|c|d;
endmodule

module _or5(a,b,c,d,e,y); // 5 input OR gate
	input a,b,c,d,e;
	output y;
	assign y=a|b|c|d|e;
endmodule 