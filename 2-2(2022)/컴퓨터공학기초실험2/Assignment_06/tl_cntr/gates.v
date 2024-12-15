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

module _inv_4bits(a,y); // 4 bits inverter
   input[3:0] a;
   output [3:0] y;
   assign y=~a;
endmodule 

module _and2_4bits(a,b,y); // 4 bits 2 input AND gate
   input [3:0] a,b;
   output [3:0] y;
   assign y=a&b;
endmodule

module _or2_4bits(a,b,y); // 4 bits 2 input OR gate
   input [3:0] a,b;
   output [3:0] y;
   assign y=a|b;
endmodule

module _xor2_4bits(a,b,y); // 4 bits 2 input exclusive OR gate
   input [3:0] a,b;
   output [3:0] y;
   _xor2 U0_xor2(a[0], b[0], y[0]);
   _xor2 U1_xor2(a[1], b[1], y[1]);
   _xor2 U2_xor2(a[2], b[2], y[2]);
   _xor2 U3_xor2(a[3], b[3], y[3]);
endmodule

module _xnor2_4bits(a,b,y); // 4 bits 2 input exclusive NOR gate
   input [3:0] a,b;
   output [3:0] y;
   wire [3:0] w0;
   _xor2_4bits U0_xor2_4bits(a, b, w0);
   _inv_4bits U1_inv_4bits(w0, y);
endmodule 