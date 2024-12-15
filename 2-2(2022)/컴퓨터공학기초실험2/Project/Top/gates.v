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

module _inv_32bits(a,y); // 32 bits inverter
   input [31:0] a;
   output [31:0] y;
   assign y=~a;
endmodule

module _and2_32bits(a,b,y); // 32 bits 2 input AND gate
   input [31:0] a,b;
   output [31:0] y;
   assign y=a&b;
endmodule 

module _or2_32bits(a,b,y); // 32 bits 2 input OR gate
   input [31:0] a,b;
   output [31:0] y;
   assign y=a|b;
endmodule 

module _xor2_32bits(a, b, y); // 32 bits 2 input XOR gate
	input [31:0] a, b;
	output [31:0] y;
	_xor2_4bits U0_xor2_4bits(a[3:0], b[3:0], y[3:0]);
	_xor2_4bits U1_xor2_4bits(a[7:4], b[7:4], y[7:4]);
	_xor2_4bits U2_xor2_4bits(a[11:8], b[11:8], y[11:8]);
	_xor2_4bits U3_xor2_4bits(a[15:12], b[15:12], y[15:12]);
	_xor2_4bits U4_xor2_4bits(a[19:16], b[19:16], y[19:16]);
	_xor2_4bits U5_xor2_4bits(a[23:20], b[23:20], y[23:20]);
	_xor2_4bits U6_xor2_4bits(a[27:24], b[27:24], y[27:24]);
	_xor2_4bits U7_xor2_4bits(a[31:28], b[31:28], y[31:28]);
endmodule 

module _xnor2_32bits(a, b, y); // 32 bits 2 input XNOR gate
	input [31:0] a, b;
	output [31:0] y;
	_xnor2_4bits U0_xnor2_4bits(a[3:0], b[3:0], y[3:0]);
	_xnor2_4bits U1_xnor2_4bits(a[7:4], b[7:4], y[7:4]);
	_xnor2_4bits U2_xnor2_4bits(a[11:8], b[11:8], y[11:8]);
	_xnor2_4bits U3_xnor2_4bits(a[15:12], b[15:12], y[15:12]);
	_xnor2_4bits U4_xnor2_4bits(a[19:16], b[19:16], y[19:16]);
	_xnor2_4bits U5_xnor2_4bits(a[23:20], b[23:20], y[23:20]);
	_xnor2_4bits U6_xnor2_4bits(a[27:24], b[27:24], y[27:24]);
	_xnor2_4bits U7_xnor2_4bits(a[31:28], b[31:28], y[31:28]);
endmodule 