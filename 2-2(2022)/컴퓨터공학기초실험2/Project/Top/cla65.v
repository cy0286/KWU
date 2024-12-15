module cla65(a, b, ci, s, co); // 65-bits carry look-ahead adder
	input [64:0] a, b;
	input ci; // input carry in
	output [64:0] s;
	output co;
	wire c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16; 
	
	//load cla4 module
	cla4 U0_cla4(a[3:0], b[3:0], ci, s[3:0], c1);
	cla4 U1_cla4(a[7:4], b[7:4], c1, s[7:4], c2);
	cla4 U2_cla4(a[11:8], b[11:8], c2, s[11:8], c3);
	cla4 U3_cla4(a[15:12], b[15:12], c3, s[15:12], c4);
	cla4 U4_cla4(a[19:16], b[19:16], c4, s[19:16], c5);
	cla4 U5_cla4(a[23:20], b[23:20], c5, s[23:20], c6);
	cla4 U6_cla4(a[27:24], b[27:24], c6, s[27:24], c7);
	cla4 U7_cla4(a[31:28], b[31:28], c7, s[31:28], c8);
	cla4 U8_cla4(a[35:32], b[35:32], c8, s[35:32], c9);
	cla4 U9_cla4(a[39:36], b[39:36], c9, s[39:36], c10);
	cla4 U10_cla4(a[43:40], b[43:40], c10, s[43:40], c11);
	cla4 U11_cla4(a[47:44], b[47:44], c11, s[47:44], c12);
	cla4 U12_cla4(a[51:48], b[51:48], c12, s[51:48], c13);
	cla4 U13_cla4(a[55:52], b[55:52], c13, s[55:52], c14);
	cla4 U14_cla4(a[59:56], b[59:56], c14, s[59:56], c15);
	cla4 U15_cla4(a[63:60], b[63:60], c15, s[63:60], c16);
	//load fa_v2 to match 65 bit
	fa_v2 U16_fa_v2(a[64], b[64], c16, s[64]);
endmodule 